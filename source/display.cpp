// Most code by Lukas


#include "display.hpp"
#include "game.hpp"
#include <locale.h>
#include <cstring>
#include <cctype>
#include <assert.h>
#include <cstdlib>
#include <time.h>
#include "Player.h"


bool Display::isGridDifferent = true;


void Display::enableDisplay()
{
	// Number of character for the "driver" and max rows and collumns
	int ch, row_max, col_max;

	// Initialization
	setlocale(LC_ALL, "");
	initscr();
        //from grid.cpp
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK); // WATER 
        init_pair(2, COLOR_GREEN, COLOR_BLACK); // GRID, gooseberry and cabbage
        init_pair(3, COLOR_RED, COLOR_BLACK); // apple and carrot
        init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // strawberry 
        init_pair(5, COLOR_WHITE, COLOR_BLACK); // EMPTY and ROCK
        init_pair(6, COLOR_YELLOW, COLOR_BLACK); // scarecrow and potato
        init_pair(7, COLOR_BLUE, COLOR_BLACK); // blackberry

	// Options
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	// Create windows
	getmaxyx(stdscr, row_max, col_max);
	mainScreen = newwin(row_max-3, col_max/2, 0, 0);
	statusScreen = newwin(row_max-3, col_max/2, 0, col_max/2);
	commandScreen = newwin(3, col_max, row_max - 3, 0);

	// Create fields, first one is the command field, last one alwats needs to be null
	commandFields[0] = new_field(1, col_max - 2, row_max - 2, 1, 0, 0);
	commandFields[1] = NULL;
	assert(commandFields[0] != NULL);

	// Options: Field is displayed, letters displayed as entered, editable and is visited during processing, do not skip another field
	set_field_opts(commandFields[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
	field_opts_off(commandFields[0], O_AUTOSKIP);

	// Create form out of fields
	commandForm = new_form(commandFields);
	assert(commandForm != NULL);

	// Assign form to window, post it and move cursor
	set_form_win(commandForm, commandScreen);
	post_form(commandForm);
	wmove(commandScreen, 1, 1);

	// Refresh so all the changes get applied
	refresh();

	//Write all the commands on status screen
	prepareStatusScreen();

	// Show grid initially
	showGrid();

	// Key check loop
	while ((Game::inGame) && (ch = getch()))
		driver(ch);

	// Freeing memory, ending
	unpost_form(commandForm);
	free_form(commandForm);
	free_field(commandFields[0]);
	delwin(mainScreen);
	delwin(commandScreen);
	endwin();

}

//function by Arielle
void Display::genValCol(int i, int j)
{
    wattroff(mainScreen,COLOR_PAIR(2));

    if (Game::grid[i][j].getSpecies() == 'W')
        wattron(mainScreen,COLOR_PAIR(1));

    else if (Game::grid[i][j].getSpecies() == 'E')
        wattron(mainScreen,COLOR_PAIR(5));

    else if (Game::grid[i][j].getSpecies() == 'R')
        wattron(mainScreen,COLOR_PAIR(5));

    else if (Game::grid[i][j].getSpecies() == 'T')
        wattron(mainScreen,COLOR_PAIR(2));

    else if (Game::grid[i][j].getSpecies() == 'A')
        wattron(mainScreen,COLOR_PAIR(3));

    else if (Game::grid[i][j].getSpecies() == 'C')
        wattron(mainScreen,COLOR_PAIR(3));

    else if (Game::grid[i][j].getSpecies() == 'G')
        wattron(mainScreen,COLOR_PAIR(2));

    else if (Game::grid[i][j].getSpecies() == '@')
        wattron(mainScreen,COLOR_PAIR(2));

    else if (Game::grid[i][j].getSpecies() == 'S')
        wattron(mainScreen,COLOR_PAIR(4));

    else if (Game::grid[i][j].getSpecies() == '$')
        wattron(mainScreen,COLOR_PAIR(6));

    else if (Game::grid[i][j].getSpecies() == 'P')
        wattron(mainScreen,COLOR_PAIR(6));

    else if (Game::grid[i][j].getSpecies() == 'B')
        wattron(mainScreen,COLOR_PAIR(7));
}

// Function by Arielle
void Display::showGrid()
{
	int tempY, tempX;

    wmove(mainScreen, 1, 1);

    wprintw(mainScreen, "\u0020");
    for (int i=0;i<Game::gridSize;i++)
    {   
        wprintw(mainScreen, "\u0020\u0020");
        if (i < 10)
            wprintw(mainScreen, "\u0020");
        wprintw(mainScreen, "%d",i);
    }
    wprintw(mainScreen, "\n");

    getyx(mainScreen, tempY, tempX);
    wmove(mainScreen, tempY, 1);

    // topPart
    wattron(mainScreen,COLOR_PAIR(2));
    wprintw(mainScreen, "\u0020\u0020\u2554");
    for (int i=0; i<Game::gridSize-1; i++)
    {
        wprintw(mainScreen, "\u2550\u2550\u2550\u2566");
    }
    wprintw(mainScreen, "\u2550\u2550\u2550\u2557");
    wprintw(mainScreen, "\n");
    
    getyx(mainScreen, tempY, tempX);
    wmove(mainScreen, tempY, 1);

    for (int i=0; i<Game::gridSize-1; i++)
    {
            //midPart
            wattroff(mainScreen,COLOR_PAIR(2));
            wprintw(mainScreen, "%d",i);
            wattron(mainScreen,COLOR_PAIR(2));
            if (i < 10)
                wprintw(mainScreen, "\u0020");
            for (int j=0; j<Game::gridSize; j++)
            {
                wprintw(mainScreen, "\u2551\u0020");
                wattroff(mainScreen,COLOR_PAIR(2));
                genValCol(i,j);
                waddch(mainScreen, Game::grid[i][j].getSpecies());
                wattron(mainScreen,COLOR_PAIR(2));
                wprintw(mainScreen, "\u0020");
            }
            wprintw(mainScreen, "\u2551");
            wprintw(mainScreen, "\n");  

            getyx(mainScreen, tempY, tempX);
    		wmove(mainScreen, tempY, 1);

            //botmidPart
            wprintw(mainScreen, "\u0020\u0020");
            wprintw(mainScreen, "\u2560");
            for (int i=0; i<Game::gridSize-1; i++)
            {
                wprintw(mainScreen, "\u2550\u2550\u2550\u256c");
            }
            wprintw(mainScreen, "\u2550\u2550\u2550\u2563");
            wprintw(mainScreen, "\n");

            getyx(mainScreen, tempY, tempX);
    		wmove(mainScreen, tempY, 1);
    }
    
    //botPart
    int b = Game::gridSize-1;
    wattroff(mainScreen,COLOR_PAIR(2));
    wprintw(mainScreen, "%d",b);
    wattron(mainScreen,COLOR_PAIR(2));

    if (b < 10)
        wprintw(mainScreen, "\u0020");

    for (int i=0; i<Game::gridSize; i++)
    {
        wprintw(mainScreen, "\u2551\u0020");
        wattroff(mainScreen,COLOR_PAIR(2));
        genValCol(b,i);
        waddch(mainScreen, Game::grid[b][i].getSpecies());
        wattron(mainScreen,COLOR_PAIR(2));
        wprintw(mainScreen, "\u0020");
    }

    wprintw(mainScreen, "\u2551");
    wprintw(mainScreen, "\n");

    getyx(mainScreen, tempY, tempX);
    wmove(mainScreen, tempY, 1);  
    
    wprintw(mainScreen, "\u0020\u0020");
    wprintw(mainScreen, "\u255a"); 
    for (int i=0; i<Game::gridSize-1; i++)
    {
        wprintw(mainScreen, "\u2550\u2550\u2550\u2569");
    }

    wprintw(mainScreen, "\u2550\u2550\u2550\u255d");
    wprintw(mainScreen, "\n");
    wattroff(mainScreen,COLOR_PAIR(2));

   	isGridDifferent = false;

    // If not drawn at the end some parts of the border get pushed out
    // Also automatically refreshes
    drawBorders();

}

// Irrelevant for now because grid is made up of plant objects
//from grid.cpp (arielle)
/*void Display::setValue(int row, int col, char value)
{
    Game::grid[row][col].getSpecies() = value;
}*/

//from grid.cpp (arielle)
int Display::intcharv(int number)
{
    return (int)((char)number - '0');
}

//from grid.cpp (arielle)
bool Display::checkIntValue(int intval)
{
    if (intval>=0 && intval<Game::gridSize)
        return true;

    return false;
}

//from grid.cpp (arielle)
bool Display::checkValValue(int value)
{
    if (value>0 && value<=8)
    {
    	return true;
    }
    return false;
}

//from grid.cpp (arielle)
/*void Display::changeValue(John name, int row, int col, int value)
{
    int rowv = intcharv(row);
    int colv = intcharv(col);
    int nvalue = intcharv(value);
    char charVal;
    if (checkIntValue(rowv) && checkIntValue(colv))
    {
        if (Game::grid[rowv][colv].getSpecies() == 'E')
        {
            if (checkValValue(nvalue))
            {
                switch(nvalue)
                {
                    case 1:
                        if (name.checkInInv("Carrots"))
                        {
                            charVal = 'C';
                            setValue(rowv,colv,charVal);
                            showGrid();
                            break;
                        }
                        else
                        {
                            sendMessage("This item is not in your inventory");
                            break;
                        }
                    case 2:
                        if (name.checkInInv("Cabbage"))
                        {
                            charVal = '@';
                            setValue(rowv,colv,charVal);
                            showGrid();
                            break;
                        }
                        else
                        {
                            sendMessage("This item is not in your inventory");
                            break;
                        }
                    case 3:
                        if (name.checkInInv("Potatoes"))
                        {
                            charVal = 'P';
                            setValue(rowv,colv,charVal);
                            showGrid();
                            break;
                        }
                        else
                        {
                            sendMessage("This item is not in your inventory");
                            break;
                        }
                    case 4:
                        if (name.checkInInv("Gooseberries"))
                        {
                            charVal = 'G';
                            setValue(rowv,colv,charVal);
                            showGrid();
                            break;
                        }
                        else
                        {
                            sendMessage("This item is not in your inventory");
                            break;
                        }
                    case 5:
                        if (name.checkInInv("Blackberries"))
                        {
                            charVal = 'B';
                            setValue(rowv,colv,charVal);
                            showGrid();
                            break;
                        }
                        else
                        {
                            sendMessage("This item is not in your inventory");
                            break;
                        }
                    case 6:
                        if (name.checkInInv("Strawberries"))
                        {
                            charVal = 'S';
                            setValue(rowv,colv,charVal);
                            showGrid();
                            break;
                        }
                        else
                        {
                            sendMessage("This item is not in your inventory");
                            break;
                        }
                    case 7:
                        if (name.checkInInv("Apple Tree"))
                        {
                            charVal = 'A';
                            setValue(rowv,colv,charVal);
                            showGrid();
                            break;
                        }
                        else
                        {
                            sendMessage("This item is not in your inventory");
                            break;
                        }
                    case 8:
                        if (name.checkInInv("Scarecrow"))
                        {
                            charVal = '$';
                            setValue(rowv,colv,charVal);
                            showGrid();
                            break;
                        }
                        else
                        {
                            sendMessage("This item is not in your inventory");
                            break;
                        }
                 }
            }
            else
            {
                sendMessage("That item is not listed");
            }
        }
        else
        {
            if (!checkValValue(nvalue))
            {
                sendMessage("Sorry but this location is not empty and item not listed");
            }
            else 
            {
                printw("Sorry but this location is not empty\n");
            }
        }
     }
     else if (!checkIntValue(rowv) && !checkIntValue(colv))
     {
         if (checkValValue(nvalue))
         {
             sendMessage("Invalid value for row and column");
         }
         else
         {
             sendMessage("Invalid value for row, column and item");
         }
     }
     else if (!checkIntValue(rowv))
     {
         if (checkValValue(nvalue))
         {
             sendMessage("Invalid value for row");
         }
         else
         {
             sendMessage("Invalid value for row and item");
         }
     }
     else if (!checkIntValue(colv))
     {
         if (checkValValue(nvalue))
         {
             sendMessage("Invalid value for column");
         }
         else
         {
             sendMessage("Invalid value for column and item");
         }
     }
     else
     {
         sendMessage("Invalid value");
     }
  drawBorders();
}*/

//from grid.cpp (arielle)
/*void Display::removeValue(int row, int col)
{
    { 
    int rowv = intcharv(row);
    int colv = intcharv(col);
    if (checkIntValue(rowv) && checkIntValue(colv))
    {
        if (Game::grid[rowv][colv].getSpecies() != 'E')
        {
            char nvalue = 'E';
            setValue(rowv,colv,nvalue);
            showGrid();
        }
        else
        {
            sendMessage("This location is already empty");
        }
    } 
    else if (!checkIntValue(rowv) && !checkIntValue(colv))
    {
        sendMessage("Invalid value for row and column");
    }
    else if (!checkIntValue(rowv))    
    {
        sendMessage("Invalid value for row");
    }
    else if (!checkIntValue(colv))
    {
        sendMessage("Invalid value for column");
    }
    else
    {
        sendMessage("Invalid value");
    }
    }
  drawBorders();
}*/

// An edit of a function from an example by Aan Mushi, 2014. Reference URL: https://gist.github.com/alan-mushi/c8a6f34d1df18574f643
char* Display::trim_whitespaces(char *str)
{
	char *end;

	// trim leading space
	while(isspace(*str))
		str++;

	if(*str == 0) // all spaces?
		return str;

	// trim trailing space
	end = str + strnlen(str, 128) - 1;

	while(end > str && isspace(*end))
		end--;

	// write new null terminator
	*(end+1) = '\0';

	return str;
}

// An edit of a function from an example by Aan Mushi, 2014. Reference URL: https://gist.github.com/alan-mushi/c8a6f34d1df18574f643
// A function that controls the cursor in the textbox
void Display::driver(int ch)
{
	int i;

	switch (ch) 
	{
		case KEY_LEFT:
			form_driver(commandForm, REQ_PREV_CHAR);
			break;

		case KEY_RIGHT:
			form_driver(commandForm, REQ_NEXT_CHAR);
			break;

		// Delete the char before cursor
		case KEY_BACKSPACE:
		case 127:
			form_driver(commandForm, REQ_DEL_PREV);
			break;

		// Delete the char under the cursor
		case KEY_DC:
			form_driver(commandForm, REQ_DEL_CHAR);
			break;

		case 10:	// Enter key
			// Field isn't in sync if this is not done
			form_driver(commandForm, REQ_VALIDATION);

			Game::handleInput(trim_whitespaces(field_buffer(commandFields[0], 0)));

			form_driver(commandForm, REQ_CLR_FIELD);
			break;

		default:
			form_driver(commandForm, ch);

			if(isGridDifferent)
				showGrid();

			wrefresh(mainScreen);
			break;
	}
}


void Display::drawBorders()
{
	box(mainScreen, 0, 0);
	box(statusScreen, 0, 0);
	box(commandScreen, 0, 0);

	wrefresh(mainScreen);
	wrefresh(statusScreen);
	wrefresh(commandScreen);
}


// Function that takes in a string and sends a status message according to it
void Display::sendMessage(std::string message)
{
	// Borders take up the first space and the status message have 3
	// last lines dedicated to them
	int y, x;	

	getmaxyx(statusScreen, y, x);
	x = 1;
	y -= 4;

	werase(statusScreen);
	prepareStatusScreen();

	wattron(statusScreen, WA_BOLD);
	mvwprintw(statusScreen, y, x, message.c_str());
	wattroff(statusScreen, WA_BOLD);

	drawBorders();
}


void Display::prepareStatusScreen()
{
	// Border takes up the first space
	int y = 1, x = 1;

	mvwprintw(statusScreen, y, x, "Commands:\n\n plant [kind] [x] [y]\n harvest\n buy [item]\n sell [item]\n quit");

	drawBorders();
}
