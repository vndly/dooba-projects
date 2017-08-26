void draw_cell(Position position, int size)
{
	int x = position.x * size;
	int y = position.y * size;

	int i;
	int j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			ssd1306_fb_plot(y + j, x + i, 1);
		}
	}
}