/**
* This file is part of SerialController. 
* Copyright (C) 2021 Xie Yang. 
* All rights reserved. 
* 
* @file     keyboard.cpp
* @brief    处理键盘按键
*   
* @author   谢阳 (Xie Yang)
* @version  1.0
* @email    200320620@stu.hit.edu.cn
* @date     2021/09/12
* 
* SerialController is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* any later version.
*
* SerialController is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with SerialController; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <iostream>
#include "keyboard.h"

using namespace std;

void KeyInput::up(bool IsDown)
{
	if (IsDown && key_up) // 持续长按
	{
		if (GetDirKeyNum() == 1)
		{
			dir = Direct::up;
		}
	}
	else if (IsDown && !key_up) // 按下瞬间
	{
		dir = Direct::up;
	}
	else // 未按下
	{
	}

	key_up = IsDown;
	return;
}

void KeyInput::down(bool IsDown)
{
	if (IsDown && key_down) // 持续长按
	{
		if (GetDirKeyNum() == 1)
		{
			dir = Direct::down;
		}
	}
	else if (IsDown && !key_down) // 按下瞬间
	{
		dir = Direct::down;
	}
	else // 未按下
	{
	}

	key_down = IsDown;
	return;
}

void KeyInput::left(bool IsDown)
{
	if (IsDown && key_left) // 持续长按
	{
		if (GetDirKeyNum() == 1)
		{
			dir = Direct::left;
		}
	}
	else if (IsDown && !key_left) // 按下瞬间
	{
		dir = Direct::left;
	}
	else // 未按下
	{
	}

	key_left = IsDown;
	return;
}

void KeyInput::right(bool IsDown)
{
	if (IsDown && key_right) // 持续长按
	{
		if (GetDirKeyNum() == 1)
		{
			dir = Direct::right;
		}
	}
	else if (IsDown && !key_right) // 按下瞬间
	{
		dir = Direct::right;
	}
	else // 未按下
	{
	}

	key_right = IsDown;
	return;
}

void KeyInput::brake(bool IsDown)
{
	if (IsDown && key_brake) // 持续长按
	{
		if (GetDirKeyNum() == 1)
		{
			dir = Direct::brake;
		}
	}
	else if (IsDown && !key_brake) // 按下瞬间
	{
		dir = Direct::brake;
	}
	else // 未按下
	{
	}

	key_brake = IsDown;
	return;
}

void KeyInput::stop(bool IsDown)
{
	if (IsDown && key_stop) // 持续长按
	{
		if (GetDirKeyNum() == 1)
		{
			dir = Direct::stop;
		}
	}
	else if (IsDown && !key_stop) // 按下瞬间
	{
		dir = Direct::stop;
	}
	else // 未按下
	{
	}

	key_stop = IsDown;
	return;
}

Direct KeyInput::GetDir()
{
	if (GetDirKeyNum() != 0)
	{
		return dir;
	}

	return Direct::unassign;
}

int KeyInput::GetDirKeyNum()
{
	int result = 0;
	if (key_right) result++;
	if (key_left) result++;
	if (key_up) result++;
	if (key_down) result++;
	if (key_brake) result++;
	if (key_stop) result++;
	return result;
}
