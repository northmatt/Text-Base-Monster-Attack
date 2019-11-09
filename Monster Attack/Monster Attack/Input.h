#pragma once

#include <iostream>
#include <stdexcept>
#include <windows.h>
#include<stdio.h>
#include<conio.h>

using std::runtime_error;

class Input {
public:
	WORD ReadVkCode(HANDLE hIn);
	bool GetKeyDown(WORD chr);
};