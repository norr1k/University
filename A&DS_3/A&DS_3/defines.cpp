#pragma once

namespace my {
	enum KeyInput
	{
	ESC = 27,
	ENTER = 13,
	UP = 72,
	DOWN = 80,
	};

	int get_max(int a, int b)
	{
		return a > b ? a : b;
	}

	int get_min(int a, int b)
	{
		return a < b ? a : b;
	}
}