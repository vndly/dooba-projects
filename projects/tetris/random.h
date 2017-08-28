int random_int(int min, int max)
{
	return min + rand() % (max - min + 1);
}