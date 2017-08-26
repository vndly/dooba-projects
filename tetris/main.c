#include <ionode/ionode.h>
#include <util/delay.h>
#include <i2c/i2c.h>
#include <ssd1306/ssd1306.h>
#include <ssd1306/fb.h>
#include <ssd1306/txt.h>
#include <fiddle/fiddle.h>
#include <fiddle/ui.h>
#include <stdio.h>

#include "input.h"
#include "position.h"
#include "cell.h"
#include "random.h"

#define SCREEN_WIDTH  8
#define SCREEN_HEIGHT 32
#define CELL_SIZE     4
#define NORMAL_SPEED  100

typedef struct {
	int type;
	int angle;
	Position o;
	Position a;
	Position b;
	Position c;
} Piece;

#include "rotate.h"

int map[SCREEN_WIDTH][SCREEN_HEIGHT];
Piece piece;
int sleep_time = NORMAL_SPEED;
int points = 0;

void clear_map()
{
	int i;
	int j;

	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		for (j = 0; j < SCREEN_HEIGHT; j++)
		{
			map[i][j] = 0;	
		}
	}
}

Piece create_piece()
{
	Piece piece;
	piece.type  = random_int(0, 6);
	piece.angle = 0;
	piece.o     = new_position(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 2);

	apply_angle(&piece);

	return piece;
}

void restart()
{
	points = 0;

	clear_map();

	piece = create_piece();
}

void show_result()
{
	char string[12];
	sprintf(string, "POINTS: %d", points);

	clear_display();
	ssd1306_txt(string, 25, 14);
	update_display();
	_delay_ms(1500);
	restart();
}

void init()
{
	i2c_init();
    ssd1306_init();
    fiddle_init();
    restart();
}

int is_piece_touching_on(Piece piece, int x, int y)
{
	int o_touching = map[piece.o.x + x][piece.o.y + y];
	int a_touching = map[piece.a.x + x][piece.a.y + y];
	int b_touching = map[piece.b.x + x][piece.b.y + y];
	int c_touching = map[piece.c.x + x][piece.c.y + y];

	return (o_touching || a_touching || b_touching || c_touching);
}

int is_cell_outside(Position position)
{
	int left_or_right = (position.x < 0) || (position.x >= SCREEN_WIDTH);

	return left_or_right || (position.y < 0);
}

int is_piece_outside(Piece piece)
{
	return (is_cell_outside(piece.o) || is_cell_outside(piece.a) || is_cell_outside(piece.b) || is_cell_outside(piece.c));
}

int is_cell_intersecting(Position position)
{
	return map[position.x][position.y];
}

int is_piece_intersecting(Piece piece)
{
	return (is_cell_intersecting(piece.o) || is_cell_intersecting(piece.a) || is_cell_intersecting(piece.b) || is_cell_intersecting(piece.c));
}

void move_block(Input input)
{
	piece.o.y--;
	piece.a.y--;
	piece.b.y--;
	piece.c.y--;

	if (input.down)
	{
		sleep_time = 0;
	}
	else
	{
		sleep_time = NORMAL_SPEED;
	}
	
	if (input.right)
	{
		if ((piece.o.x < (SCREEN_WIDTH - 1)) && (piece.a.x < (SCREEN_WIDTH - 1)) && (piece.b.x < (SCREEN_WIDTH - 1)) && (piece.c.x < (SCREEN_WIDTH - 1)))
		{
			if (!is_piece_touching_on(piece, 1, 0))
			{
				piece.o.x++;
				piece.a.x++;
				piece.b.x++;
				piece.c.x++;
			}
		}
	}
	else if (input.left)
	{
		if ((piece.o.x > 0) && (piece.a.x > 0) && (piece.b.x > 0) && (piece.c.x > 0))
		{
			if (!is_piece_touching_on(piece, -1, 0))
			{
				piece.o.x--;
				piece.a.x--;
				piece.b.x--;
				piece.c.x--;
			}
		}
	}
	else if (input.center || input.a || input.b)
	{
		piece.angle = (piece.angle + 90) % 360;
		apply_angle(&piece);

		if (is_piece_outside(piece) || is_piece_intersecting(piece))
		{
			piece.angle = (piece.angle - 90) % 360;
			apply_angle(&piece);
		}
	}
}

int is_at_bottom(Piece piece)
{
	return (piece.o.y == 0) || (piece.a.y == 0) || (piece.b.y == 0) || (piece.c.y == 0);
}

int is_piece_touching(Piece piece)
{
	return is_at_bottom(piece) || is_piece_touching_on(piece, 0, -1);
}

void add_piece_to_map(Piece piece)
{
	map[piece.o.x][piece.o.y] = 1;
	map[piece.a.x][piece.a.y] = 1;
	map[piece.b.x][piece.b.y] = 1;
	map[piece.c.x][piece.c.y] = 1;
}

int is_row_full(int j)
{
	int i;
	int count = 0;

	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		count += map[i][j];
	}

	return (count == SCREEN_WIDTH);
}

void clear_row(int j)
{
	int i;

	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		map[i][j] = 0;
	}

	points++;
}

void check_if_rows_exists()
{
	int j;
	int move_from_row = -1;
	int rows_to_move  = 0;

	for (j = 0; j < SCREEN_HEIGHT; j++)
	{
		if (is_row_full(j))
		{
			clear_row(j);
			rows_to_move++;
			move_from_row = j + 1;
		}
	}

	if (move_from_row != -1)
	{
		for (j = move_from_row; j < SCREEN_HEIGHT; j++)
		{
			int i;

			for (i = 0; i < SCREEN_WIDTH; i++)
			{
				map[i][j - rows_to_move] = map[i][j];
			}
		}
	}
}

void update_block(Input input)
{
	if (is_piece_touching(piece))
	{
		if (piece.o.y == (SCREEN_HEIGHT - 2))
		{
			show_result();
		}
		else
		{
			add_piece_to_map(piece);
			check_if_rows_exists();
			piece = create_piece();
		}
	}
	else
	{
		move_block(input);	
	}
}

void draw_piece(Piece piece)
{
	draw_cell(piece.o, CELL_SIZE);
	draw_cell(piece.a, CELL_SIZE);
	draw_cell(piece.b, CELL_SIZE);
	draw_cell(piece.c, CELL_SIZE);
}

void draw_map()
{
	int i;
	int j;

	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		for (j = 0; j < SCREEN_HEIGHT; j++)
		{
			if (map[i][j])
			{
				Position position = new_position(i, j);
				draw_cell(position, CELL_SIZE);
			}
		}
	}
}

void loop()
{
    clear_display();

    Input input = read_input();

    update_block(input);

    draw_map();

    draw_piece(piece);

    update_display();

    if (sleep_time > 0)
    {
    	_delay_ms(sleep_time);
	}
}