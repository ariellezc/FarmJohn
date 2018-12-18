// Most code by Lukas


#include <iostream>
#include <iterator>
#include <sstream>
#include "game.hpp"
#include "clock.hpp"
#include "libsqlite.hpp"

bool Game::inGame = true;
std::vector<std::vector<Plant>> Game::grid={};
std::vector<char> Game::listChar = {};
int Game::gridSize = 8;

Display Game::display;

Game::Game()
{
	system("clear");
	std::cout << "Welcome to FarmJohn! Version: 0.01" << std::endl << std::endl;
}

Game::~Game()
{
	std::cout << "Thank you for playing!" << std::endl;
}

void Game::start()
{	
	// Enter menu
	menu();

	// Generate random map
	randomPlants();

	// Start the clock
	Clock clock;

	// Start the in-game display
	display.enableDisplay();
}

void Game::menu()
{
	bool inMenuScreen = true;

	while (inMenuScreen)
	{
		std::cout << "1. New game" << std::endl;
		std::cout << "2. Exit" << std::endl;
		std::cout << std::endl << "Enter your option: ";

		int option;
		std::cin >> option;

		if (option == 1)
			inMenuScreen = false;

		else if (option == 2)
        {
            inMenuScreen = false;
            inGame = false;
        }
			
	}
}

//function by Arielle
//function to retrieve value from the database and insert it to the vector listChar
void Game::retrieveObjectChar()
{
    try
    {   
        sqlite::sqlite db("databases/FarmJohnDatabase.sqlite");
        auto cur = db.get_statement(); 
        
        cur->set_sql("SELECT Object_Type FROM Objects"); 
        cur->prepare();
        while(cur->step()) 
        {
            std::string name = cur->get_text(0);
            char newVal = name[0];
            listChar.emplace_back(newVal);
        }

    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << std::endl; 
    }
}

// Code written by Arielle and Filip
// A function that generates random character array to display in a grid
void Game::randomPlants()
{
    //Machine generated value
    retrieveObjectChar();

    //srand for random value and different seeds
    srand((int)time(0));

    //resizing the vector
    grid.resize(gridSize);

    //Generating values for the 2D Vector
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            char species = listChar[(rand()%3)];
            int growth = 5; //TODO Change to a database stored value
            int cost = 10; //TODO Change to a database stored value
            int sell_price = 15; //TODO Change to a database stored value
            grid[i].push_back(Plant(i, j, species, growth, cost, sell_price));
        }
    }
}


// A function that takes in a string (usually player input in a textbox) and executes commands according to it
void Game::handleInput(std::string input)
{
	//Code to split string into words taken from an example. Reference https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
	// Split input into different words
	std::istringstream inputss(input);
	std::vector<std::string> words(std::istream_iterator<std::string>{inputss}, std::istream_iterator<std::string>());

	display.sendMessage(input);

	// Otherwise produces a segmentation fault if input is empty
	if (!input.empty())
	{
		if (words[0] == "quit")
			inGame = false;

		/*if (words[0] == "plant")
		{
	
		}
	
		else if (words[0] == "harvest")
		{

		}

		else if (words[0] == "buy")
		{

		}

		else if (words[0] == "sell")
		{
	
		}*/
	}
	

}
