//By Niamh

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Player.h"
using namespace std;

void buy(John &t, vector<pair<string, int>> list) //Function to allow the player to buy an item
{
    int choice, cost, amount;
    
    for (int i = 0; i < list.size(); i++) //Display the items on sale and their price
    {
        cout << i+1 << ". " << list[i].first << ": " << list[i].second << " gold" << endl;
    }
    cout << "Choose an item: ";
    cin >> choice; //Player enters their choice
    cout << endl;
    
    if (choice > list.size()) //Check the player entered a valid number for an item
    {
        cout << "Not an option" << endl << endl; 
        buy(t, list); //If the number was not vaild, ask the player to try again
    }
    
    cout << "How many would you like to buy? ";
    cin >> amount; //Player enters how many of the item they want to buy
    cout << endl;
    
    cost = list[choice-1].second; //Find the cost of the item
    cost *= amount; //Find the cost for the quantity the player asked for
    
    if (t.getGold() < cost) //Check they player has enough gold
    {
       cout << "You do not have enough gold" << endl << endl;
       buy(t, list);
    }
     
    //If the player has enough gold 
    t.addToInv(list[choice-1].first, amount); //Add the item to their inventory
    t.subtractGold(cost);// Take the gold from their inventory
    

}

void buyMenu(John &t)
{
    typedef vector<pair<string, int>>  List; //Define a type for the following lists
    
    List cropsList = {{"Carrots", 10}, {"Potatoes", 20}, {"Cabbage", 10}}; //Lists of the items on sale and their prices
    List bushesList = {{"Strawberries",100}, {"Blackberries",110}, {"Gooseberries", 120}};
    List treesList = {{"Apple", 200}};
    List defenceList = {{"Scarecrow", 250}};
    int choice;
    
    cout << "1. Crops" << endl;
    cout << "2. Bushes" << endl;
    cout << "3. Trees" << endl;
    cout << "4. Defence" << endl;
    cout << "Choose an option: ";
    cin >> choice; //Player enters their choice
    cout << endl;
    
    switch(choice) //Use the corresponding list to the option the player chose
    {
        case 1:
            buy(t, cropsList);
            break;
        case 2:
            buy(t, bushesList);
            break;
        case 3:
            buy(t, treesList);
            break;
        case 4:
            buy(t, defenceList);
            break;
        default: //If the player entered a number that was not an option
            cout << "Not an option" << endl << endl; //Ask them to try again
            buyMenu(t);
            break;
    }       
}

void sell(John &t, vector<pair<string, int>> list) //Function to allow the player to sell an item
{
    int choice, cost, amount;
    
    for (int i = 0; i < list.size(); i++) //Display the items to sell and their price
    {
        cout << i+1 << ". " << list[i].first << ": " << list[i].second << " gold" << endl;
    }
    cout << "Choose an item: ";
    cin >> choice; //Player enters their choice
    cout << endl;
    
    if (choice > list.size()) //Check the player entered a valid number for an item
    {
        cout << "Not an option" << endl << endl;
        sell(t, list); //If the number was not valid, ask the player to try again
    }
    
    cout << "How many would you like to sell? ";
    cin >> amount; //Player enters how many of the item they want to sell
    cout << endl;
    
    vector<pair<string, int>> inventory = t.getInventory(); //Get the player's inventory
    
    for (int i = 0; i < inventory.size(); i++) //Check that the player has enough of the item to sell
    {
        if (inventory[i].first == list[choice-1].first)
        {
            if (inventory[i].second < amount)
            {
                cout << "You don't have enough to sell" << endl << endl;
                sell(t, list); //If they don't have enough, ask them to try again
            }
            break;
        }
    }
    
    //If the player has enough of the item to sell
    t.takeFromInv(list[choice-1].first, amount); //Take the item from the player's inventory
    
    cost = list[choice-1].second; //Find the selling price of the item
    cost *= amount; //Find the selling price for the quanity the player asked to sell
    
    t.addGold(cost); //Give the gold to the player
}

void sellMenu(John &t)
{
    typedef vector<pair<string, int>>  List; //Define a type for the following lists
    
    List cropsList = {{"Carrots", 20}, {"Potatoes", 40}, {"Cabbage", 60}}; //List of the items to sell and their prices
    List bushesList = {{"Strawberries", 10}, {"Blackberries", 11}, {"Gooseberries", 12}};
    List treesList = {{"Apple", 200}};
    int choice;
    
    cout << "1. Crops" << endl;
    cout << "2. Bushes" << endl;
    cout << "3. Trees" << endl;
    cout << "Choose an option: ";
    cin >> choice; //Player enters their choice
    cout << endl;
    
    switch(choice) //Use the corresponding list to the option the player chose
    {
        case 1:
            sell(t, cropsList);
            break;
        case 2:
            sell(t, bushesList);
            break;
        case 3:
            sell(t, treesList);
            break;
        default: //If the player entered  a number that was not an option
            cout << "Not an option" << endl << endl; //Ask them to try again
            sellMenu(t);
            break;
    } 
}

void menu(John &t)
{
    int choice;
    cout << "1. Buy" << endl;
    cout << "2. Sell" << endl;
    cout << "Choose an option: ";
    cin >> choice; //Player enters their choice
    cout << endl;
    if (choice == 1)
    {
        buyMenu(t); //Display the buy menu
    }
    else if (choice == 2)
    {
        sellMenu(t); //Display the sell menu
    }
    else //If the player entered a number that was not an option
    {
        cout << "Not an option" << endl << endl; //Ask them to try again
        menu(t);
    }
}

int main()
{
    John t;
    
    t.outputGold();
    t.addToInv("Carrots", 5);
    t.outputInv();

    menu(t);
    
    t.outputInv();
    
    return 0;
}
