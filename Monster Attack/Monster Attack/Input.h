#pragma once

#include <iostream>
#include <windows.h>
#include <vector>

using std::vector;

class Input abstract {
public:
	static void updateInps();
	static WORD ReadVkCode(HANDLE hIn);
	static bool GetKey(WORD chr);
	static bool GetKeyDown(WORD chr);
	static vector<WORD> pressedInps;
	static vector<WORD> toBeAddedInps;
private:
	static bool CheckInps(vector<WORD> vecToCheck, WORD charIn);

};