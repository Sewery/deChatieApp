#pragma once
#include <chrono>
#include <thread>
#include "Config.h"
class Timer
{
private:
	int tStartTime;

	//The ticks stored when the timer was paused
	int tPausedTime;

	//The timer status
	bool tPaused;
	bool tStarted;
public:
	Timer();

	void start();
	void pause();
	void unpause();
	void stop();

	//Return ticks
	int getTicks();

	//Checks the status of the timer
	bool isStarted() { return tStarted;  }
	bool isPaused() { return tPaused; }

	static void waitFor(int);
};

