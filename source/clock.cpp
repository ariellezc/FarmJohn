// Code by Lukas


#include "clock.hpp"

// Game starting point
std::chrono::steady_clock::time_point Clock::gameStartTime = Clock::createTimer();


std::chrono::steady_clock::time_point Clock::createTimer()
{
    return std::chrono::steady_clock::now();
}


int Clock::getDuration(std::chrono::steady_clock::time_point creationTime)
{
	//Formula taken from http://www.cplusplus.com/reference/chrono/steady_clock/ examples and customized specifically for the program
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - creationTime);
	return time_span.count();
}


// Function that checks if time point is older than the number of seconds given in the second argument
bool Clock::isExpired(std::chrono::steady_clock::time_point creationTime, int existsFor)
{
    int seconds = getDuration(creationTime);
    
    return (seconds >= existsFor);
}
