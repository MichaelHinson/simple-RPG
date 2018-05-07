#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ctgmath>
#include <fstream>
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

void itemShop(Character& hero);//Allows hero to only restore health currently using earned gold

void menuList(Character& hero);//Hero may fight an enemy or visit the item shop

void characterNamer(Character& hero) //Allows the user to name the character, Loops until user is satisfied.
{
	string heroName,heroLastName, extra, extraa;
	int menuChoice = 0;
	do
	{
		cout << "Enter a name for your hero(No Spaces)" << endl;
		cin >> heroName; //>> heroLastName >> extra >> extraa;
		//heroName = heroName + " " + heroLastName + " " + extra + " " + extraa;
		hero.SetName(heroName);
		cout << "Your hero is now named " << hero.GetName() << ". Is this correct? \n1.Yes \n2.No" << endl;
		cin >> menuChoice;
	} while (menuChoice == 2);//Loop continues until user enters a number other than 2

} 
void initializer(Character& hero)//Called from main to allow for future hero rebirths (can pass the object to this I don't know of a way to pass an
//object to main. deathScreen() could call this with a new object if the user chose to be reborn.
{	
	characterNamer(hero);
	do 
	{
		menuList(hero);//Brings up main menu loop

	} while (hero.GetCurrentHealth() > 0);//Continues until the Hero dies
}
int main()
{
	Character Hero1("Hero", 20, 3, 5, 80, 5, 3, .2, 5, 0, 0, 1);

	srand(time(NULL));//Seed the random number Generator

	initializer(Hero1);

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
		gameState.SetHeroCount(gameState.GetHeroCount() + 1);// Ups hero count, may use this later to empower monsters
		initializer(Hero);//Sends the new hero to start the game
	}

	
	exit(0);//Hero is dead and the program exits
}
void heroStatSelection(Character& hero)//Allows the user to improve the hero upon leveling up
{
	char menuChoice;
	cout << "\nCongratulations! Your hero has leveled up. Please select your reward!" << endl;
	cout << "Hero Max Health is: " << hero.GetMaxHealth() << " Minimum damage is: " << hero.GetMinDamage() << " Maximum damage is: " << hero.GetMaxDamage() << endl;
	cout << "Hit Chance is: " << hero.GetHitChance() << " Speed is: " << hero.GetSpeed() << " Mana is: " << hero.GetMaxMana() << " Defense is: " << hero.GetDefense() * 100 << "%";
	cout << " Crit Chance is: " << hero.GetCritChance() << "%" << endl;
	cout << "\n1.+5 Max Health  2.+1 Minimum Damage  3.+1 Maximum Damage  4.+5% Hit Chance \n5.+1 Speed       6.+5 Max Mana        7.+5% Defense        8.+2% Crit Chance" << endl;
	cin >> menuChoice;

	switch (menuChoice) {
	case '1':
		hero.SetMaxHealth(hero.GetMaxHealth() + 5);//Adds 5 to hero max health
		hero.SetCurrentHealth(hero.GetCurrentHealth() + 5);//Also adds 5 to current health
		cout << "Your Hero now has " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " Health" << endl;
		break;
	case '2':
		if (hero.GetMinDamage() < hero.GetMaxDamage()) 
		{
			hero.SetMinDamage(hero.GetMinDamage() + 1);
			cout << "Your Hero now has " << hero.GetMinDamage() << " Minimum Damage" << endl;
		}
		else//Prevents min damage from exceeding max damage
		{
			cout << "Minimum damage may not exceed maximum damage please select another attribute" << endl;
			heroStatSelection(hero);
		}
		break;
	case '3':
		hero.SetMaxDamage(hero.GetMaxDamage() + 1);//Adds 1 to max damage
		cout << hero.GetName() << " now has " << hero.GetMaxDamage() << " Maximum Damage" << endl;
		break;
	case '4':
		hero.SetHitChance(hero.GetHitChance() + 5);//Adds 5% to hitChance
		cout << hero.GetName() << " now has a(n)" << hero.GetHitChance() << "% Hit Chance" << endl;
		break;
	case '5':
		hero.SetSpeed(hero.GetSpeed() + 1);//Adds 1 to speed
		cout << hero.GetName() << " now has " << hero.GetSpeed() << " Speed" << endl;
		break;
	case '6':
		hero.SetMaxMana(hero.GetMaxMana() + 5);
		hero.SetCurrentMana(hero.GetCurrentMana() + 5);//Adds 5 to max and current mana
		cout << hero.GetName() << " now has " << hero.GetCurrentMana() << "/" << hero.GetMaxMana() << " Mana" << endl;
		break;
	case '7':
		hero.SetDefense(hero.GetDefense() + .05);//Adds 5% to hero defense
		cout << hero.GetName() << " now has " << hero.GetDefense()*100 << "% Defense" << endl;
		break;
	case '8':
		hero.SetCritChance(hero.GetCritChance() + 2);//Adds 2% to crit chance
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
		if (hero.GetLevel() == gameState.GetLevelReq() && hero.GetExp() >= gameState.GetXpReq())//Checks hero level and xp currently linear (10xp per level)
		{

			hero.SetLevel(hero.GetLevel() + 1);//Raises hero level
			heroStatSelection(hero);//Sends hero to level up screen
			gameState.SetXpReq(gameState.GetXpReq() + 10);//Increases required xp
			gameState.SetLevelReq(gameState.GetLevelReq() + 1);//Increases required level
			
		}
	}while (hero.GetExp() >= gameState.GetXpReq());//Loop is for reborn heroes to spend all level ups
}
void itemShop(Character& hero) //Allows user to spend gold only to restore health at the moment WIP
{
	char menuChoice;
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
				hero.SetGold(hero.GetGold() - 5);
				hero.SetCurrentHealth(hero.GetCurrentHealth() + 5);
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
			hero.SetGold(hero.GetGold() - (hero.GetMaxHealth() - hero.GetCurrentHealth()));
			hero.SetCurrentHealth(hero.GetMaxHealth());
			cout << hero.GetName() << " has " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " health and " << hero.GetGold() << " gold" << endl;	
		}
		else
		{
			cout << "You don't have enough gold for that" << endl;
		}
	default:
		menuList(hero);
	}
}
void menuList(Character& hero)
{
	heroLeveler(hero);//Allows reborn heroes to spend xp
	char menuChoice = 0;
	cout << "\nSelect an action from the following menu" << endl << endl;
	cout << hero.GetName() << " currently has " << hero.GetGold() << " gold and " << hero.GetExp() << " EXP";
	cout << " and " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " Health" << endl;
	cout << "1.Fight a random enemy \n2.Visit the item shop" << endl;
	cin >> menuChoice;
	
	switch (menuChoice) {
	case '1':
		fightPicker(hero);
		break;
	case '2':
		itemShop(hero);
	default:
		menuList(hero);
	}

}
