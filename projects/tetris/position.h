typedef struct {
   int x;
   int y;
} Position;

Position new_position(int x, int y)
{
   Position result;
   result.x = x;
   result.y = y;

   return result;
}

Position move_position(Position position, int x, int y)
{
   Position result;
   result.x = position.x + x;
   result.y = position.y + y;

   return result;
}