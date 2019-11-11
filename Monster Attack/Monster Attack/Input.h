#pragma once

#include <iostream>
#include <windows.h>

class Input abstract {
public:
	static WORD ReadVkCode(HANDLE hIn);
	static bool GetKeyDown(WORD chr);
};