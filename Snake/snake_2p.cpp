#include"snake_2p.h"
class Item;
extern Item* food;
extern std::vector<Snake*> global_snake_list;

void Snake2P::on_input(const ExMessage& msg)
{
	Direction last_dir = snake_move_current_direction;
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case VK_LEFT://'A'
			last_dir = Left;
			break;

		case VK_RIGHT://'D'
			last_dir = Right;
			break;

		case VK_UP://'W'
			last_dir = Up;
			break;

		case VK_DOWN://'S' 
			last_dir = Down;
			break;

		case VK_NUMPAD0://'J'
			is_snake_accelerate = true;
			break;
		default:

			break;
		}
		if (canChangeDirection(last_dir))
		{
			updateSnakeMoveDirectionDeque(last_dir);
		}
	}
	else if (msg.message == WM_KEYUP)
	{
		if (msg.vkcode == 0x4A)
		{
			is_snake_accelerate = false;
		}
	}

}