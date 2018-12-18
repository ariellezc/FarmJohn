## Presenting C1 group project:

# FarmJohn

## Description:
A classic farming game with a twist, be the ultimate farmer - **John**. Buy seeds, plants, bushes, samplings, plant them, watch them grow and then harvest them. Experience farming like you never did before! 

<sub><sup>(Disclaimer: Game is in early access, developers are not responsible for any negative consequences like: disappointment, regret, shame, tears, etc.)</sup></sub>

## Features:

    1. Amazingly crisp grid graphics keeping you up to date with everything that happens in your field.
    2. Intuitive and snappy command interface, perfectly supplementing the gameplay, it's as if you're there!
    3. Revolutionary inventory system making all that pesky item management a breeze.
    4. A database so safe, it could keep all your data in a nuclear fallout. No need to fear them 
       Russi... ahem, unidentified forces from interrupting your game and resulting in a loss of progress.
    5. All that in your natively supported linux terminal!
    
    
<sub><sup>(Disclaimer: Features that either don't work as intended or aren't fully supported: Buy command, Sell command, Harvest command, Plant command, Sell command, inventory system, player system, game saves, player saves, statistics, database saves integration, database statistics updates, sorry.)</sup></sub>

## Installation:

You're surely at the edge of your seat now, so only one question remains, how to run this amazing piece of software? Well here's what you have to do:

First of all install the libraries the game depends on :
```sh
sudo apt update && sudo apt upgrade --yes
sudo apt install make g++ libncurses5-dev libncursesw5-dev libsqlite3-dev --yes
```
   
Then clone this very repository by executing : 
```sh
git clone https://github.coventry.ac.uk/baltal/C1-ALL-project.git
```
Change your directory to the correct one with this command :
```sh
cd C1-ALL-project/source/
```

## Usage:

Now, after all this effort you can finally compile and run it with a simple command:
```sh
make run
```
Enjoy!

![image](https://blog.codinghorror.com/content/images/uploads/2007/03/6a0120a85dcdae970b0128776ff992970c-pi.png)


### Useful links:

### [Sprint tracker sheet](https://docs.google.com/spreadsheets/d/1rwF_t4ydviTUIc80xQ2edGfqYZJjUNIqPkwecgWJdkI/edit?ts=5a65b77a#gid=741081008)
