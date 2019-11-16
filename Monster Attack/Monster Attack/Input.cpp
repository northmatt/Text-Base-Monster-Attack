#include "Input.h"

vector<WORD> Input::pressedInps;
vector<WORD> Input::toBeAddedInps;

void Input::updateInps() {
	for (WORD curr : toBeAddedInps)
		if (!CheckInps(pressedInps, curr))
			pressedInps.push_back(curr);

	toBeAddedInps.clear();

	for (size_t i = 0; i < pressedInps.size(); i++) {
		if (!(GetKeyState(pressedInps[i]) & 0x8000)) {
			pressedInps.erase(pressedInps.begin() + i);
			i = 0;
		}
	}
}

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

	return 0;
	/*#include<stdio.h>
	#include<conio.h>
	WORD vk = inp.ReadVkCode(hConsole);

	if (vk > 1 && inputs.size() == 0)
		inputs.push_back(vk);
	else if (vk == 1 && inputs.size() >= 1)
		inputs.erase(inputs.begin());

	if (inputs.size() >= 1)
		cout << inputs[0];*/
}

bool Input::GetKey(WORD chr) {
	//GetKeyState is a toggle, 0x800 makes it so that it is only a keydown
	if (GetKeyState(chr) & 0x8000) {
		if (!CheckInps(toBeAddedInps, chr))
			toBeAddedInps.push_back(chr);

		return true;
	}

	return false;
}

bool Input::GetKeyDown(WORD chr) {
	if (GetKeyState(chr) & 0x8000 && !CheckInps(pressedInps, chr)) {
		if (!CheckInps(toBeAddedInps, chr))
			toBeAddedInps.push_back(chr);
		
		return true;
	}

	return false;
}

bool Input::CheckInps(vector<WORD> vecToCheck, WORD charIn) {
	for (WORD currentInp : vecToCheck)
		if (currentInp == charIn)
			return true;

	return false;
}
