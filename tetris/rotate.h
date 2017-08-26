void apply_angle(Piece *piece)
{
   if (piece->type == 0)
   {
      if (piece->angle == 0)
      {
         piece->a = move_position(piece->o, 0,  1);
         piece->b = move_position(piece->o, 0, -1);
         piece->c = move_position(piece->o, 0, -2);
      }
      else if (piece->angle == 90)
      {
         piece->a = move_position(piece->o, -2, 0);
         piece->b = move_position(piece->o, -1, 0);
         piece->c = move_position(piece->o,  1, 0);
      }
      else if (piece->angle == 180)
      {
         piece->a = move_position(piece->o, 0,  2);
         piece->b = move_position(piece->o, 0,  1);
         piece->c = move_position(piece->o, 0, -1);
      }
      else if (piece->angle == 270)
      {
         piece->a = move_position(piece->o, -1, 0);
         piece->b = move_position(piece->o,  1, 0);
         piece->c = move_position(piece->o,  2, 0);
      }
   }
   else if (piece->type == 1)
   {
      // always the same (square)
      piece->a = move_position(piece->o, 1,  0);
      piece->b = move_position(piece->o, 0, -1);
      piece->c = move_position(piece->o, 1, -1);
   }
   else if (piece->type == 2)
   {
      if (piece->angle == 0)
      {
         piece->a = move_position(piece->o, 0,  1);
         piece->b = move_position(piece->o, 1,  0);
         piece->c = move_position(piece->o, 0, -1);
      }
      else if (piece->angle == 90)
      {
         piece->a = move_position(piece->o, -1,  0);
         piece->b = move_position(piece->o,  1,  0);
         piece->c = move_position(piece->o,  0, -1);
      }
      else if (piece->angle == 180)
      {
         piece->a = move_position(piece->o,  0,  1);
         piece->b = move_position(piece->o, -1,  0);
         piece->c = move_position(piece->o,  0, -1);
      }
      else if (piece->angle == 270)
      {
         piece->a = move_position(piece->o,  0, 1);
         piece->b = move_position(piece->o, -1, 0);
         piece->c = move_position(piece->o,  1, 0);
      }
   }
   else if (piece->type == 3)
   {
      if (piece->angle == 0)
      {
         piece->a = move_position(piece->o, 0,  1);
         piece->b = move_position(piece->o, 1,  1);
         piece->c = move_position(piece->o, 0, -1);
      }
      else if (piece->angle == 90)
      {
         piece->a = move_position(piece->o, -1,  0);
         piece->b = move_position(piece->o,  1,  0);
         piece->c = move_position(piece->o,  1, -1);
      }
      else if (piece->angle == 180)
      {
         piece->a = move_position(piece->o,  0,  1);
         piece->b = move_position(piece->o, -1, -1);
         piece->c = move_position(piece->o,  0, -1);
      }
      else if (piece->angle == 270)
      {
         piece->a = move_position(piece->o, -1, 1);
         piece->b = move_position(piece->o, -1, 0);
         piece->c = move_position(piece->o,  1, 0);
      }
   }
   else if (piece->type == 4)
   {
      if (piece->angle == 0)
      {
         piece->a = move_position(piece->o,  0,  1);
         piece->b = move_position(piece->o, -1,  1);
         piece->c = move_position(piece->o,  0, -1);
      }
      else if (piece->angle == 90)
      {
         piece->a = move_position(piece->o,  1, 1);
         piece->b = move_position(piece->o, -1, 0);
         piece->c = move_position(piece->o,  1, 0);
      }
      else if (piece->angle == 180)
      {
         piece->a = move_position(piece->o, 0,  1);
         piece->b = move_position(piece->o, 0, -1);
         piece->c = move_position(piece->o, 1, -1);
      }
      else if (piece->angle == 270)
      {
         piece->a = move_position(piece->o, -1,  0);
         piece->b = move_position(piece->o,  1,  0);
         piece->c = move_position(piece->o, -1, -1);
      }
   }
   else if (piece->type == 5)
   {
      if (piece->angle == 0)
      {
         piece->a = move_position(piece->o, 0,  1);
         piece->b = move_position(piece->o, 1,  0);
         piece->c = move_position(piece->o, 1, -1);
      }
      else if (piece->angle == 90)
      {
         piece->a = move_position(piece->o,  1,  0);
         piece->b = move_position(piece->o,  0, -1);
         piece->c = move_position(piece->o, -1, -1);
      }
      else if (piece->angle == 180)
      {
         piece->a = move_position(piece->o, 0,  1);
         piece->b = move_position(piece->o, 1,  0);
         piece->c = move_position(piece->o, 1, -1);
      }
      else if (piece->angle == 270)
      {
         piece->a = move_position(piece->o,  1,  0);
         piece->b = move_position(piece->o,  0, -1);
         piece->c = move_position(piece->o, -1, -1);
      }
   }
   else if (piece->type == 6)
   {
      if (piece->angle == 0)
      {
         piece->a = move_position(piece->o,  0,  1);
         piece->b = move_position(piece->o, -1,  0);
         piece->c = move_position(piece->o, -1, -1);
      }
      else if (piece->angle == 90)
      {
         piece->a = move_position(piece->o, -1, 1);
         piece->b = move_position(piece->o,  0, 1);
         piece->c = move_position(piece->o,  1, 0);
      }
      else if (piece->angle == 180)
      {
         piece->a = move_position(piece->o,  0,  1);
         piece->b = move_position(piece->o, -1,  0);
         piece->c = move_position(piece->o, -1, -1);
      }
      else if (piece->angle == 270)
      {
         piece->a = move_position(piece->o, -1, 1);
         piece->b = move_position(piece->o,  0, 1);
         piece->c = move_position(piece->o,  1, 0);
      }
   }
}