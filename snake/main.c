#include <ionode/ionode.h>
#include <util/delay.h>
#include <i2c/i2c.h>
#include <ssd1306/ssd1306.h>
#include <ssd1306/fb.h>
#include <ssd1306/txt.h>
#include <fiddle/fiddle.h>
#include <fiddle/ui.h>
#include <stdio.h>

#define MAP_H        42
#define MAP_V        10
#define TILE_SIZE    3
#define INITIAL_SIZE 5

typedef struct {
   int x;
   int y;
} position;

int velocity_x;
int velocity_y;

position body[MAP_H * MAP_V];
int size;

position apple;

position new_position(int x, int y)
{
	position result;
	result.x = x;
	result.y = y;

	return result;
}

void restart()
{
	velocity_x = 1;
	velocity_y = 0;

	int half_vertical = MAP_V / 2;

	size = INITIAL_SIZE;

	int i;

	for (i = 0; i < INITIAL_SIZE; i++)
	{
		body[i] = new_position((MAP_H / 3) + (INITIAL_SIZE - i) - 1, half_vertical);
	}

	apple = new_position(MAP_H / 4, half_vertical);
}

void show_result()
{
	char points[12];
	sprintf(points, "POINTS: %d", size - INITIAL_SIZE);

	clear_display();
	ssd1306_txt(points, 25, 14);
	update_display();
	_delay_ms(1000);
	restart();
}

void init()
{
    i2c_init();
    ssd1306_init();
    fiddle_init();
    restart();
}

void advance()
{
    int i;

	for (i = 0; i < size - 1; i++)
	{
		body[size - i - 1] = body[size - i - 2];
	}

	body[0].x += velocity_x;
    body[0].y += velocity_y;
}

void check_boundaries()
{
	if (body[0].x < 0)
    {
    	body[0].x = MAP_H - 1;
    }
    else if (body[0].x > MAP_H - 1)
    {
    	body[0].x = 0;
    }

    if (body[0].y < 0)
    {
    	body[0].y = MAP_V - 1;
    }
    else if (body[0].y > MAP_V - 1)
    {
    	body[0].y = 0;
    }
}

int is_in_body(position position)
{
	int i;

	for (i = 1; i < size; i++)
	{
		if ((body[i].x == position.x) && (body[i].y == position.y))
		{
			return 1;
		}
	}

	return 0;
}

void check_self_eating()
{
	if (is_in_body(body[0]))
	{
		show_result();
	}
}

int random_int(int min, int max)
{
   return min + rand() % (max - min + 1);
}

position random_position()
{
	return new_position(random_int(0, MAP_H - 1), random_int(0, MAP_V - 1));
}

void check_apple()
{
	if ((body[0].x == apple.x) && (body[0].y == apple.y))
	{
		size++;
		body[size - 1] = body[size - 2];

		position position = random_position();

		while (is_in_body(position))
		{
			position = random_position();
		}

		apple.x = position.x;
		apple.y = position.y;
	}
}

void update_snake()
{
	advance();
	check_boundaries();
	check_apple();
	check_self_eating();
}

void read_input()
{
	uint8_t input = input();

	if (is_down_pressed(input))
    {
    	velocity_x=0;
    	velocity_y=1;
    }
    else if (is_up_pressed(input))
    {
    	velocity_x=0;
    	velocity_y=-1;
    }
    else if (is_left_pressed(input))
    {
    	velocity_x=-1;
    	velocity_y=0;
	}
	else if (is_right_pressed(input))
    {
    	velocity_x=1;
    	velocity_y=0;
    }
}

void draw_cell(position position)
{
	int x = position.x * TILE_SIZE;
	int y = position.y * TILE_SIZE;

	int i;
	int j;

	for (i = 0; i < TILE_SIZE; i++)
	{
		for (j = 0; j < TILE_SIZE; j++)
		{
			ssd1306_fb_plot(x + i, y + j, 1);
		}
	}
}

void draw_snake()
{
	int i;

	for (i = 0; i < size; i++)
	{
		draw_cell(body[i]);
	}
}

void draw_apple()
{
	draw_cell(apple);
}

void loop()
{
    clear_display();

    read_input();

    update_snake();

    draw_snake();

    draw_apple();

    update_display();

    _delay_ms(33);
}