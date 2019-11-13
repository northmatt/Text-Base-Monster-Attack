#pragma once

#include <cstdio>
#include <chrono>
#include <thread>

using std::milli;
using std::chrono::system_clock;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

class Time abstract {
public:
	static void FpsCap();
	static double timeWait, deltaTime;
	static system_clock::time_point a, b;
};