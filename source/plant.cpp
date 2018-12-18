// Code by Lukas


#include "plant.hpp"
#include "clock.hpp"

int Plant::count = 0;


// Constructor for establishing all the initial variables
Plant::Plant(int x_coord, int y_coord, char species, int growth, int cos, int sell_pric)  
{
    Plant::count++;
    coord = std::make_pair(x_coord, y_coord);
    speciesLetter = species;
    growth_time = growth;
    cost = cos;
    sell_price = sell_pric;
    start_t = Clock::createTimer();
}


std::pair <int, int> Plant::getCoord()  
{ 
    return coord; 
}


int Plant::getGrowth()   
{
    return growth_time;
}


int Plant::getCost()      
{
    return cost;
}


int Plant::getSellPrice() 
{
    return sell_price;
}


bool Plant::isMature() 
{
    return Clock::isExpired(start_t, growth_time);
}


char Plant::getSpecies()
{
    return speciesLetter;
}


int Plant::getCount()   
{
    return Plant::count;
}
