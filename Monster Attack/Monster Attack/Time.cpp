#include "Time.h"

system_clock::time_point Time::a = system_clock::now();
system_clock::time_point Time::b = system_clock::now();
double Time::timeWait = 20;
double Time::deltaTime = 0;

//https://stackoverflow.com/questions/38730273/how-to-limit-fps-in-a-loop-with-c
void Time::FpsCap() {
	//find the amount of time that has passed since this function was last called
	a = system_clock::now();
	duration<double, milli> work_time = a - b;

	//if the amount of time that has passed is smaller than the time to wait it'll find out how long it needs to wait and stop the program from running for a certain amoount of time
	if (work_time.count() < timeWait) {
		duration<double, milli> delta_ms(timeWait - work_time.count());
		milliseconds delta_ms_duration = duration_cast<milliseconds>(delta_ms);
		sleep_for(milliseconds(delta_ms_duration.count()));
	}

	//finds how long the system has slept/stopped, then adds the length of the since this function's last call which gives delta time
	b = system_clock::now();
	duration<double, milli> sleep_time = b - a;
	deltaTime = (work_time + sleep_time).count();
	deltaTime /= 1000;
}