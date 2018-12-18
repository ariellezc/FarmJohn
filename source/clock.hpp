// Code by Lukas

#pragma once

#include <chrono>

class Clock
{

typedef std::chrono::steady_clock::time_point time;

public:
	static time createTimer();
	// Check how long the object was created for
	static int getDuration(time creationTime);
	// Check if an object is expired
	static bool isExpired(time creationTime, int existsFor);

	// Initial timepoint that is initalized when game starts
	static time gameStartTime;


protected:

private:

};
