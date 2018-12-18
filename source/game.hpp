// Code by Lukas


#pragma once

#include "display.hpp"
//#include "Player.h"
//#include "DatabaseConnection.cpp"
//#include "DatabaseFuntions.cpp"
#include <string>
#include "plant.hpp"

class Game
{
    public:
        Game();
        ~Game();
    
        void start();

        // Handles player input and executes commands according to it
        static void handleInput(std::string input);

        // A variable to check if the game is still on-going
        static bool inGame;
        static std::vector<std::vector<Plant>> grid;
	      static std::vector<char> listChar;
	      static int gridSize;

    protected:

   	private:


   		void menu();
       //grid.cpp
	    void retrieveObjectChar();
   		// A Function for creating a vector of random Plant objects
   		void randomPlants();

   		static Display display;
};
