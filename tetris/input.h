typedef struct {
   int up;
   int down;
   int left;
   int right;
   int center;
   int a;
   int b;
} Input;

Input read_input()
{
	uint8_t input = input();

	Input result;

   result.left   = is_up_pressed(input);
   result.right  = is_down_pressed(input);
   result.down   = is_left_pressed(input);
   result.up     = is_right_pressed(input);
   result.center = is_center_pressed(input);
   result.a      = is_btn1_pressed(input);
   result.b      = is_btn2_pressed(input);
    
   return result;
}