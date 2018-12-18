// Code by Lukas


#include "display.hpp"
#include "plant.hpp"
#include "clock.hpp"
#include "game.hpp"
#include "libsqlite.hpp"
#include <iostream>

using namespace std;

int main()
{
	Game game;
    cout << "Game class initialization successful ✔" << endl;

	Display testDisplay;
	cout << "Display class initialization successful ✔" << endl;

	Plant testPlant(1, 5, 10, 3, 15);
	cout << "Plant class initialization successful ✔" << endl;
    
    Clock clock;
    cout << "Clock class initialization successful ✔" << endl;


	int choice;

	cout << endl << "What do you want to test?" << endl;
	cout << "1. Start the screen (Should spew out a fault)" << endl;
	cout << "2. Call plant getters" << endl;
    cout << "3. Test clock class functions" << endl;
    cout << "4. Test game object SQL function" << endl;
	cout << "> ";
	cin >> choice;

	switch(choice)
	{
		case 1:
			testDisplay.enableDisplay();
            break;

		case 2:
			cout << endl << "Settings: testPlant(1, 5, 10, 3, 15)" << endl;
			cout << "Getter results: (" << testPlant.getCoord().first << ", " 
				 						<< testPlant.getCoord().second << ", " 
				 						<< testPlant.getGrowth() << ", " 
				 						<< testPlant.getCost() << ", " 
										<< testPlant.getSellPrice() << ") " << endl;
            cout << "Is the plant mature? " << boolalpha<< testPlant.isMature() << endl;
            cout << "How many plants are there? " << Plant::getCount() << endl;
            break;

       case 3:
            cout << "How long has it been since the program started running: " << Clock::getDuration(Clock::gameStartTime) << " seconds." << endl;
            cout << "Have 5 seconds passed? " << boolalpha << Clock::isExpired(Clock::gameStartTime, 5) << std::endl;
            break;

       case 4:
       		Game::retrieveObjectCoord();
	}

	return 0;
}
