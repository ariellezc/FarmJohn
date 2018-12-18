#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#include "libsqlite.hpp" //The libsqlite library
#ifndef PLAYER_H
#define PLAYER_H

class John 
{
  private:
    int gold; //Define the variables for the player's balance, name and inventory 
    string farmName;
    vector<pair<string, int>>  inventory;
    
  public:
    John()
    {
        gold = 500; //Set a default balance and inventory
        inventory = {{"Shovel",1}};
    }
    
    void outputGold() //Print player's current balance
    {
        cout << gold << " gold" << endl;
    }
    
    void addGold(int amount) //Add gold to the balance and output the new balance
    {
      gold += amount;
      outputGold();
    }
    
    void subtractGold(int amount) //Take gold from the balance and output the new balance
    {
        gold -= amount;
        outputGold();
    }
    
    int getGold() //Return the current balance
    {
        return gold;
    }
    
    string setFarmName(string name) //Update the farm name
    {
        farmName = name;
        return farmName;
    }
    
    void addToInv(string item, int quantity) //Add an item to the inventory
    {
        bool found = false;
        
        for (int i = 0; i < inventory.size(); i++) //Look at each item in the inventory
        {
            if(inventory[i].first == item) //Check if the item is already in the inventory
            {
              inventory[i].second += quantity; //If the item is in the inventory, update the quantity
              found = true;
            }
        }
        
        if (found == false) //If the item is not already in the inventory
        {
            inventory.emplace_back(item, quantity); //Add the new item to the inventory
        }
    }
    
    void takeFromInv(string item, int quantity) //Take an item from the inventory
    {
        quantity -= 1;
        
        for (int i = 0; i < inventory.size(); i++) //Look at each item in the inventory
        {
            if (inventory[i].first == item)
            {
                if (inventory[i].second -= quantity > 0) //Check if there will still be more than one of the item lest
                {
                    inventory[i].second -= quantity; //If there is enough, update the quantity 
                }
                else
                {
                    inventory.erase(inventory.begin() + i); //Otherwise, delelte the item from the list
                }
                break;
            }
        }
    }
    
    void outputInv() //Print the contents of the inventory
    {
        for (int i = 0; i < inventory.size(); i++)
        {
            cout << inventory[i].first << ": " << inventory[i].second << endl;
        }
    }
    
    vector<pair<string, int>> getInventory() //Returns the inventory
    {
        return inventory;
    }
    
    bool checkInInv(string item) //Check if an item is in the inventory
    {
        for (int i = 0; i < inventory.size(); i++)
        {
            if (inventory[i].first == item)
            {
                return true; //If the item is found, return true
            }
        }
        return false; //If the item is not found, return false
    }
    
    void save() //Save the contents of the player's inventory to the database
    {    
      try
      {
          int count;

          sqlite::sqlite db("FarmJohnDatabase.sqlite"); //Connect to the database file
          auto cur = db.get_statement(); //Create a cursor

          for (int i = 0; i < inventory.size(); i++) //Go through each item in the inventor
          {
              cur -> set_sql("SELECT count(*) " 
                             "FROM UserInventory "
                             "WHERE PlayerName = ? "
                             "AND ItemName = ?"); //Query to check if the item is already in the database

              cur -> prepare(); 
              cur -> bind(1, farmName); //Assign the values to the query
              cur -> bind(2, inventory[i].first);
              cur -> step();

              int count = cur -> get_int(0); //Found out if the item was found in the database

              cur -> reset(); //Reset the cursor

              if (count == 0) //If the item is not in the database
              {
                  cur -> set_sql("INSERT INTO UserInventory Values (?, ?, ?);"); //Add the item to the database
                  cur -> prepare();
                  cur -> bind(1, farmName);
                  cur -> bind(2, inventory[i].first);
                  cur -> bind(3, inventory[i].second);
                  cur -> step();
              }
              else //If the item is already in the database
              {
                  cur -> set_sql("UPDATE UserInventory "
                                 "SET NumInInventory = ? "
                                 "WHERE PlayerName = ? "
                                 "AND ItemName = ?"); //Update the quantity in the database
                  cur -> prepare();
                  cur -> bind(1, inventory[i].second);
                  cur -> bind(2, farmName);
                  cur -> bind(3, inventory[i].first);
                  cur -> step();
              }

              cur -> reset();
          }
      }
      catch(sqlite::exception e) //Catch any exceptions that occur
      {
          std::cerr << e.what() << std::endl; //Output the error
      }
    }
};

#endif

/*int main()
{
    John t;
    t.outputInv();
    t.addToInv("Carrots", 10);
    t.outputInv();
    
    return 0;   
}*/
