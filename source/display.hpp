//Most code by Lukas


#pragma once

#include <ncurses.h>

#include <form.h>
#include <vector>
#include <string>
#include "Player.h"

class Display
{
	public:
		void enableDisplay();
	    void genValCol(int,int);
		void showGrid();
	    //void setValue(int,int,char);
	    int intcharv(int);
	   	bool checkIntValue(int);
        bool checkValValue(int);
	    //void changeValue(John, int, int, int);
		//void removeValue(int,int);
		void prepareStatusScreen();
		// Show a status message for the player
		void sendMessage(std::string message);

		// Variable that keeps track if the grid changed between loops
		static bool isGridDifferent;


	protected:

	private:
	/*	Initialize windows, fields array and a form:
		Windows: mainScreen - main screen used to display actual graphics
		commandScreen - screen used for text box and entering commands	
		Fields array: 1 - Used for typing in and submitting commands, 2 - NULL, last one has to be null
		Form: Used to join up all the fields and post them */
		WINDOW *mainScreen, *commandScreen, *statusScreen;	
		FIELD *commandFields[2];
		FORM *commandForm;

	/*	driver function controls cursor in the textform and deletes, displays characters as needed*/
		char* trim_whitespaces(char *str);
		void driver(int ch);
		void drawBorders();
};
