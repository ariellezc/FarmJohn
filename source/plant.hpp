// Code by Lukas


#pragma once

#include <ctime>
#include <ratio>
#include <chrono>
#include <utility>


class Plant
{
    // General class overarching all the plants
    public:
        static int count;

        // Constructor for initializing all the starting variables
        Plant(int x_coord, int y_coord, char species, int growth, int cos, int sell_pric);
        
        std::pair <int, int> getCoord();
        int getGrowth();
        int getCost();
        int getSellPrice();
        bool isMature();
        char getSpecies();

        static int getCount();


    protected:
        std::pair <int, int> coord;
        int growth_time;  // Time it takes the plant to mature, you can harvest vegetables right after, while trees and bushes have their own fruit bearing times
        int cost;         // How much it costs to buy seeds/samplings in gold coins
        int sell_price;   // How much gold coins you gain after selling it
        char speciesLetter;     // Letter of the plant to be displayed
        std::chrono::steady_clock::time_point start_t;  // Starting time

        
    private:  
        
};
