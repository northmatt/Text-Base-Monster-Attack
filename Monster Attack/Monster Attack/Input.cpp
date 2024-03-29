#include "Input.h"

WORD Input::ReadVkCode(HANDLE hIn) {
	//returns the key you're pressing. GetKeyState became preferred due to not having to deal with the key inputs repeating when you hold down the key
	INPUT_RECORD rec;
	DWORD numRead;

		PeekConsoleInput(hIn, &rec, 1, &numRead);

		if (numRead == 0)
			return 0;

		ReadConsoleInput(hIn, &rec, 1, &numRead);
		if (rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown) {
			return rec.Event.KeyEvent.wVirtualKeyCode;
		}
		/*
#include<stdio.h>
#include<conio.h>
		WORD vk = inp.ReadVkCode(hConsole);

	if (vk > 1 && inputs.size() == 0)
		inputs.push_back(vk);
	else if (vk == 1 && inputs.size() >= 1)
		inputs.erase(inputs.begin());

	if (inputs.size() >= 1)
		cout << inputs[0];*/
}

bool Input::GetKeyDown(WORD chr) {
	//GetKeyState is a toggle, 0x800 makes it so that it is only a keydown
	return GetKeyState(chr) & 0x8000;
}
