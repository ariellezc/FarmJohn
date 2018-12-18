#include <iostream>
#include <string>

using namespace std;

#include "libsqlite.hpp"    

void modifyShoppingInventory(string ItemName, int ItemCost, int NumOfItemAvailable)
{
    sqlite::sqlite db("FarmJohn_database.sqlite");    //opens the database

    auto cur = db.get_statement();            //creates the query
    cur->set_sql( "INSERT INTO ShopInventory (ItemName, ItemCost, NumOfItemAvailable)"
                  "VALUES (?,?,?);" );
    cur->prepare();
    
    cur->bind(ItemName);                //sets the placeholders
    cur->bind(ItemCost);
    cur->bind(NumOfItemAvailable);
    cur->step();                       //runs the query
}
