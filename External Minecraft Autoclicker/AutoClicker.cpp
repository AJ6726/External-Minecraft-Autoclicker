#include "AutoClicker.h"
#include <Windows.h>
#include <random>
#include "UConfigs.h"


enum ClickMode : int
{
	TOGGLE = 0,
	HOLD
};

void Clicker()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
	input.mi.time = 0;

	std::random_device rd;
	std::mt19937 gen(rd());

	bool click = false;

	while (true)
	{
		if (AutoClicker::on)
		{
			if (AutoClicker::mode == TOGGLE)
			{
				if (GetAsyncKeyState(AutoClicker::keyBind) & 1)
					click = !click;

				if (click)
				{
					SendInput(1, &input, sizeof(input));
					std::uniform_int_distribution<> dis(AutoClicker::minDelay, AutoClicker::maxDelay);
					Sleep(dis(gen));
				}
			}
		}

		if (AutoClicker::mode == HOLD)
		{
			if (GetAsyncKeyState(AutoClicker::keyBind))
			{
				SendInput(1, &input, sizeof(input));
				{
					SendInput(1, &input, sizeof(input));
					std::uniform_int_distribution<> dis(AutoClicker::minDelay, AutoClicker::maxDelay);
					Sleep(dis(gen));
				}
			}
		}
	}
}