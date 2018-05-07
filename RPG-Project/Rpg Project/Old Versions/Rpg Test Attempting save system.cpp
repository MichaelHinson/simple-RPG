#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ctgmath>
#include <fstream>
#include <iomanip>
#include <string>
#include "RPG Header Files\Character.h"
#include "RPG Header Files\GameState.h"
#include "RPG Header Files\FightFunctions.h"//Contains all Fight related functions
using namespace std;
void characterNamer(Character& hero);//Lets the user name the character, loops until user is satisfied. Name can not have spaces

void initializer(Character& hero);//Starts the game and sends character to menulist

int deathScreen(Character hero);/*Displays monsters slain, asks whether to be reborn. If reborn new character has base stats and previous hero gold
and 1/2 previous hero XP*/

void heroStatSelection(Character& hero);//Upon leveling up hero picks which stat to upgrade in this function

void heroLeveler(Character& hero);//Determines whether hero levels up after each fight. Currently 10xp per level

void itemShop(Character& hero);/*Allows hero to only restore health currently using earned gold
Contains a switchcase*/
void menuList(Character& hero);//Hero may fight an enemy or visit the item shop

void saveGame(Character& hero);//Saves data to a text file

void beastiary();//Displays monster stats for the player

void characterNamer(Character& hero) //Allows the user to name the character, Loops until user is satisfied.
{
	string heroName,heroLastName, extra, extraa;
	int menuChoice = 0;
	do
	{
		cout << "Enter a name for your hero(No Spaces)" << endl;
		cin >> heroName; 
		hero.SetName(heroName);
		cout << "Your hero is now named " << hero.GetName() << ". Is this correct? \n1.Yes \n2.No" << endl;
		cin >> menuChoice;
	} while (menuChoice == 2);//Loop continues until user enters a number other than 2

} 
void initializer(Character& hero)//Called from main to allow for future hero rebirths (can pass the object to this I don't know of a way to pass an
//object to main. deathScreen() could call this with a new object if the user chose to be reborn.
{	
	if (hero.GetName() == "Hero")//If default name sends user to namer, helps with loading.
	{
		characterNamer(hero);
	}
	
	do 
	{
		menuList(hero);//Brings up main menu loop

	} while (hero.GetCurrentHealth() > 0);//Continues until the Hero dies
}
int main()
{
	srand(time(NULL));//Seed the random number Generator

	ifstream saveData;
	saveData.open("Save Data.txt");
	if (saveData.fail())//If no save data, start game with basic stats
	{
		cout << "No Save data found. Starting New Game\n";
		Character Hero1("Hero", 20, 3, 5, 80, 5, 3, .2, 5, 0, 0, 1);
		saveData.close();
		initializer(Hero1);
	}
	else //Save data exists
	{
		int menuChoice = 0;
		cout << "Save data found. Would you like to load the game?\n1.Yes\n2.No\n";
		cin >> menuChoice;
		
		if (menuChoice == 2)//User chose not to load game, new game created with basic stats
		{
			cout << "New game created. Saving will overwrite previous character!" << endl;
			Character Hero1("Hero", 20, 3, 5, 80, 5, 3, .2, 5, 0, 0, 1);
			saveData.close();
			initializer(Hero1);
		}
		else//User chose to load game. Previous stats used currently does not import name
		{
			cout << "Load succesful" << endl;
			int currentHealth, maxHealth, minDamage, maxDamage, hitChance, critChance, speed, maxMana, currentMana, gold, exp, level, fightCount, xpReq, levelReq, heroCount;
			double defense;
			string name;

			//Read data from text file
			saveData >> name >> currentHealth >> maxHealth >> minDamage >> maxDamage >> hitChance >> critChance >> speed >> defense >> maxMana >> gold >> exp >> level
				>> fightCount >> xpReq >> levelReq >> heroCount;

			//Create hero object using prior stats. Currently restores current health to max. MUST FIX
			Character Hero1(name, maxHealth, minDamage, maxDamage, hitChance, critChance, speed, defense, maxMana, gold, exp, level);
			Hero1.SetCurrentHealth(currentHealth);//Janky fix to current health = max health when loading

			//Establish prior gamestate
			gameState.SetFightCount(fightCount);
			gameState.SetXpReq(xpReq);
			gameState.SetLevelReq(levelReq);
			gameState.SetHeroCount(heroCount);
			saveData.close();
			
			initializer(Hero1);
		}
	}

}
int deathScreen(Character hero)//If Hero reaches 0 health during fight() this screen is displayed showing monsters killed
{
	int menuChoice = 0;
	cout << "\n\t\t" << hero.GetName() << " has died!" << endl;
	cout << "\t\tThey defeated " << gameState.GetFightCount() -1 << " monster(s)" << endl;
	cout << "\t\tWould you like to be reborn? 1.Yes 2.No" << endl; //Rebirths hero
	cin >> menuChoice;
	if (menuChoice == 1)//Hero is reborn
	{
		Character Hero("Hero", 20, 3, 5, 80, 5, 3, .2, 5, hero.GetGold(), hero.GetExp()/2, 1);//Hero recieves gold of previous hero and 1/2 of xp
		gameState.SetXpReq(10);//Resets Exp required to level up
		gameState.SetLevelReq(1);//Resets hero level
		gameState.SetFightCount(1);//Resets fight Count
		gameState.SetHeroCount(gameState.GetHeroCount() + 1);// Ups hero count, may use this later to empower monsters
		initializer(Hero);//Sends the new hero to start the game
	}

	
	exit(0);//Hero is dead and the program exits
}
void heroStatSelection(Character& hero)//Allows the user to improve the hero upon leveling up
{
	char menuChoice;
	cout << "\nCongratulations! Your hero has leveled up. Please select your reward!" << endl;
	statDisplay(hero);
	cout << "\n1.+5 Max Health  2.+1 Minimum Damage  3.+1 Maximum Damage  4.+5% Hit Chance \n5.+1 Speed       6.+5 Max Mana        7.+5% Defense        8.+2% Crit Chance" << endl;
	cin >> menuChoice;

	//Leveling Modifiers, amount gained if user selects attribute for level up
	int maxHealthGain = 5;
	int minDamageGain = 1;
	int maxDamageGain = 1;
	int hitChanceGain = 5;
	int critChanceGain = 2;
	int speedGain = 1;
	int manaGain = 5;
	double defenseGain = .05;

	switch (menuChoice) {
	case '1':
		hero.SetMaxHealth(hero.GetMaxHealth() + maxHealthGain);//Adds 5 to hero max health
		hero.SetCurrentHealth(hero.GetCurrentHealth() + maxHealthGain);//Also adds 5 to current health
		cout << "Your Hero now has " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " Health" << endl;
		break;
	case '2':
		if (hero.GetMinDamage() < hero.GetMaxDamage()) 
		{
			hero.SetMinDamage(hero.GetMinDamage() + minDamageGain);
			cout << hero.GetName() <<" now has " << hero.GetMinDamage() << " Minimum Damage" << endl;
		}
		else//Prevents min damage from exceeding max damage
		{
			cout << "Minimum damage may not exceed maximum damage please select another attribute" << endl;
			heroStatSelection(hero);
		}
		break;
	case '3':
		hero.SetMaxDamage(hero.GetMaxDamage() + maxDamageGain);//Adds 1 to max damage
		cout << hero.GetName() << " now has " << hero.GetMaxDamage() << " Maximum Damage" << endl;
		break;
	case '4':
		hero.SetHitChance(hero.GetHitChance() + hitChanceGain);//Adds 5% to hitChance
		cout << hero.GetName() << " now has a(n)" << hero.GetHitChance() << "% Hit Chance" << endl;
		break;
	case '5':
		hero.SetSpeed(hero.GetSpeed() + speedGain);//Adds 1 to speed
		cout << hero.GetName() << " now has " << hero.GetSpeed() << " Speed" << endl;
		break;
	case '6':
		hero.SetMaxMana(hero.GetMaxMana() + manaGain);
		hero.SetCurrentMana(hero.GetCurrentMana() + manaGain);//Adds 5 to max and current mana
		cout << hero.GetName() << " now has " << hero.GetCurrentMana() << "/" << hero.GetMaxMana() << " Mana" << endl;
		break;
	case '7':
		hero.SetDefense(hero.GetDefense() + defenseGain);//Adds 5% to hero defense
		cout << hero.GetName() << " now has " << hero.GetDefense()*100 << "% Defense" << endl;
		break;
	case '8':
		hero.SetCritChance(hero.GetCritChance() + critChanceGain);//Adds 2% to crit chance
		cout << hero.GetName() << " now has " << hero.GetCritChance() << "% Crit Chance" << endl;
	default:
		cout << "\nPlease enter an option from the list";
		menuList(hero);
	}

}
void heroLeveler(Character& hero)//Determines if the hero has leveled up or not
{
	

	do
	{
		if (hero.GetExp() >= gameState.GetXpReq())//Checks hero level and xp currently linear (10xp per level)
		{

			hero.SetLevel(hero.GetLevel() + 1);//Raises hero level
			heroStatSelection(hero);//Sends hero to level up screen
			gameState.SetXpReq(gameState.GetXpReq() + 10);//Increases required xp
			gameState.SetLevelReq(gameState.GetLevelReq() + 1);//Increases required level, CURRENTLY USELESS
			
		}
	}while (hero.GetExp() >= gameState.GetXpReq());//Loop is for reborn heroes to spend all level ups
}
void itemShop(Character& hero) //Allows user to spend gold only to restore health at the moment WIP
{
	char menuChoice;
	//Displays hero health and item menu
	cout << hero.GetName() << " has " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " health and " << hero.GetGold() << " gold" << endl;//Out puts hero gold and current health/Max health
	cout << "Welcome to the item shop please select from the following menu" << endl;
	cout << "1. Buy a health potion(+5hp) 5 Gold \n2. Refill missing health 1 gold per missing Health \n3. Exit the Item Shop" << endl;
	cin >> menuChoice;

	switch (menuChoice) {
	case '1':
		if (hero.GetGold() >= 5)//Ensures the user has enough gold
		{
			if (hero.GetCurrentHealth() + 5 > hero.GetMaxHealth())//Prevents hero from gaining more than the maximum health
			{
				hero.SetGold(hero.GetGold() - 5);//Subtracts 5 from hero gold
				hero.SetCurrentHealth(hero.GetMaxHealth());//Sets current health to max health
				cout << hero.GetName() << " has " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " health and " << hero.GetGold() << " gold" << endl;
			}
			else
			{
				hero.SetGold(hero.GetGold() - 5);//Subtracts 5 from hero gold
				hero.SetCurrentHealth(hero.GetCurrentHealth() + 5);//Increases current health by 5
				cout << hero.GetName() << " has " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " health and " << hero.GetGold() << " gold" << endl;
			}
		}
		else
		{
			cout << "You don't have enough gold for that" << endl;
		}
		break;
	case '2':
		if (hero.GetMaxHealth() - hero.GetCurrentHealth() <= hero.GetGold())//Ensures the user has enough gold. 1 gold per 1 health missing
		{
			//Removes gold based on difference between max and current health. Currently 1 gold is 1 health
			hero.SetGold(hero.GetGold() - (hero.GetMaxHealth() - hero.GetCurrentHealth()));
			hero.SetCurrentHealth(hero.GetMaxHealth());//Fills hero health
			cout << hero.GetName() << " has " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " health and " << hero.GetGold() << " gold" << endl;	
		}
		else
		{
			cout << "You don't have enough gold for that" << endl;//User does not have enough gold
		}
	default:
		menuList(hero);
	}
}
void menuList(Character& hero)
{
	heroLeveler(hero);//Allows reborn heroes to spend xp
	char menuChoice = 0;
	//Displays menu list
	cout << "\nSelect an action from the following menu" << endl << endl;
	cout << hero.GetName() << " currently has " << hero.GetGold() << " gold and " << hero.GetExp() << " EXP";
	cout << " and " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " Health" << endl;
	cout << "1.Fight a random enemy \n2.Visit the item shop \n3.Save Game \n4.Show Hero Stats\n5.Beastiary" << endl;
	cin >> menuChoice;
	
	switch (menuChoice) {
	case '1':
		fightPicker(hero);//Hero fights a random enemy
		break;
	case '2':
		itemShop(hero);//Hero visits the item shop
		break;
	case '3':
		saveGame(hero);//Game saves to text file "Save Data.txt"
		break;
	case '4':
		statDisplay(hero);//Displays all hero stats
		break;
	case '5':
		beastiary();//Allows user to view monster stats
		break;
	default:
		menuList(hero);//Defaults to menu list
	}

}
void saveGame(Character& hero)
{
	ofstream saveData;
	saveData.open("Save Data.txt");
	//Should format this better
		saveData << hero.GetName() << " " << hero.GetCurrentHealth() << " " << hero.GetMaxHealth() 
		<< " "  << hero.GetMinDamage() << " " << hero.GetMaxDamage() << " " << hero.GetHitChance() 
		<< " " << hero.GetCritChance() << " " << hero.GetSpeed() << " " << hero.GetDefense() << " " 
		<< hero.GetMaxMana() << " " << hero.GetGold() << " " << hero.GetExp() << " " << hero.GetLevel()
		<< " " << gameState.GetFightCount() << " " << gameState.GetXpReq() << " " << gameState.GetLevelReq() 
		<< " " << gameState.GetHeroCount();
		
	saveData.close();
	cout << "\nSave Successful" << endl << endl;
	// maxHealth, minDamage, maxDamage, hitChance, critChance, speed, defense, maxMana, gold, exp, level
}
void beastiary()
{
	char menuChoice = 0;
	int wSize = 14;//Buffer Size for 2 column effect

	cout.setf(ios::left);
	cout << "Which monster would you like to examine?\n" << setw(wSize) << "1.Skeleton" << "2.Slime" << endl;
	cout << setw(wSize) << "3.Imp" << "4.Zombie" << endl;
	cout << setw(wSize) << "5.Fallen Hero" << "6.Strong Fallen Hero" << endl;
	cout << "0.Exit" << endl;
	cin >> menuChoice;

	switch (menuChoice) {
	case '1':
		statDisplay(Skeleton);
		beastiary();
		break;
	case '2':
		statDisplay(Slime);
		beastiary();
		break;
	case '3':
		statDisplay(Imp);
		beastiary();
		break;
	case '4':
		statDisplay(Zombie);
		beastiary();
		break;
	case '5':
		statDisplay(FallenHero);
		beastiary();
		break;
	case '6':
		cout << "Strong Fallen Hero scales off the hero's stats" << endl;
		beastiary();
		break;
	default:
		;
	}
}

