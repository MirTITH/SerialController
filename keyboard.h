#pragma once

#include <Windows.h>

enum class Direct
{
	unassign,
	up,
	down,
	left,
	right,
	brake,
	stop
};

// 按键输入
class KeyInput
{
public:
	KeyInput()
	{
		dir = Direct::unassign;
	}

	void Update()
	{
		up(GetAsyncKeyState(87));// w
		down(GetAsyncKeyState(83));// s
		left(GetAsyncKeyState(65));// a
		right(GetAsyncKeyState(68));// d
		brake(GetAsyncKeyState(32));// space
		stop(GetAsyncKeyState(20));// Cape Lock
	}

	void up(bool IsDown);
	void down(bool IsDown);
	void left(bool IsDown);
	void right(bool IsDown);
	void brake(bool IsDown);
	void stop(bool IsDown);
	Direct GetDir();//获取方向
	int GetDirKeyNum(); //获取同时按下的方向键数量
private:
	bool key_up = false;
	bool key_down = false;
	bool key_left = false;
	bool key_right = false;
	bool key_brake = false;
	bool key_stop = false;
	Direct dir;
};

// 按键输入速度控制
class KeyInputSpeed
{
public:
	KeyInputSpeed()
	{
		dir = Direct::unassign;
	}

	void Update()
	{
		up(GetAsyncKeyState(87));// w
		down(GetAsyncKeyState(83));// s
	}

	void up(bool IsDown)
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

	void down(bool IsDown)
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

	Direct GetDir()//获取方向
	{
		if (GetDirKeyNum() != 0)
		{
			return dir;
		}

		return Direct::unassign;
	}


	int GetDirKeyNum() //获取同时按下的方向键数量
	{
		int result = 0;
		if (key_up) result++;
		if (key_down) result++;
		return result;
	}
private:
	bool key_up = false;
	bool key_down = false;
	Direct dir;
};

// 按键输入转向控制
class KeyInputTurnRatio
{
public:
	KeyInputTurnRatio()
	{
		dir = Direct::unassign;
	}

	void Update()
	{
		left(GetAsyncKeyState(65));// a
		right(GetAsyncKeyState(68));// d
	}

	void left(bool IsDown)
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

	void right(bool IsDown)
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

	Direct GetDir()//获取方向
	{
		if (GetDirKeyNum() != 0)
		{
			return dir;
		}

		return Direct::unassign;
	}


	int GetDirKeyNum() //获取同时按下的方向键数量
	{
		int result = 0;
		if (key_left) result++;
		if (key_right) result++;
		return result;
	}
private:
	bool key_left = false;
	bool key_right = false;
	Direct dir;
};

// 按键输入紧急控制
class KeyInputEmergency
{
public:
	KeyInputEmergency()
	{
		dir = Direct::unassign;
	}

	void Update()
	{
		brake(GetAsyncKeyState(32));// space
		stop(GetAsyncKeyState(20));// Cape Lock
	}

	void brake(bool IsDown)
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

	void stop(bool IsDown)
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

	Direct GetDir()//获取方向
	{
		if (GetDirKeyNum() != 0)
		{
			return dir;
		}

		return Direct::unassign;
	}

	int GetDirKeyNum() //获取同时按下的方向键数量
	{
		int result = 0;
		if (key_brake) result++;
		if (key_stop) result++;
		return result;
	}

private:
	bool key_brake = false;
	bool key_stop = false;
	Direct dir;
};