#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <ctgmath>
#include <iomanip>
#include "Character.h"
#include "GameState.h"

using namespace std;

//initialization of gamestate object. Stores fight Count, xpReq, levelReq, heroCount
GameState gameState(1, 10, 1, 1);

//Initialization of Character objects to create hero1 and monsters
//Name, Max Health, Min Damage, Max Damage, Hit Chance, Crit Chance, Speed, Defense, Mana, Gold, EXP, Level
Character Skeleton("Skeleton",	 5,	 1, 3, 70,  3, 3, .1,  5,  5, 2, 1);
Character Zombie(  "Zombie",	10,  3, 5, 50,  1, 1, .2,  5, 10, 3, 1);
Character Slime(   "Slime",		 6,  1, 2, 60,  2, 4, .5,  5,  5, 1, 1);
Character Imp(     "Imp",		 3,  1, 2, 80, 10, 6,  0, 20,  3, 2, 1);
Character FallenHero("Fallen Hero", 20, 3, 5, 80, 5, 3, .2, 5, 15, 10, 1);
Character Dragon("Dragon", 30, 4, 6, 70, 5, 4, .2, 5, 100, 100, 1);

/*Example Skeleton
 Character Skeleton("Skeleton" = Name,	 5= Max Health,	 1 = Min Damage, 3 = Max Damage,
 70 = Hit Chance,  3 = Crit Chance, 3 = Speed, .1 = Defense,  5 = Mana,  5 = Gold, 2 = EXP, 1 = Level)*/

//Functions from main file that are referenced
int deathScreen(Character& hero); 
void heroLeveler(Character& hero);
void menuList(Character& hero);//Hero may fight an enemy or visit the item shop

//Prototypes
bool turnDecider(Character hero, Character monster);//Determines move order each round

int damageRoll(Character entity);//Determines damage dealt before armor check

bool chanceRoll(int Chance);//Used for hit and crit. Chance out of 100 based on entities stats

void monsterBasicAttack(Character& hero, Character& monster);//Monster attacks hero with a basic attack

void heroBasicAttack(Character& hero, Character& monster);//Hero attacks monster with a basic attack

void fight(Character& hero, Character& monster);//Fight loop. Currently only basic attacks and automated

void fightPicker(Character& hero);//Determines which enemy the hero will fight

void statDisplay(Character hero, Character monster);//Displays hero and monster stats

void statDisplay(Character hero);//Displays only hero stats

bool turnDecider(Character hero, Character monster) //True == Hero moves first. False == Monster moves first
{
	int turnOrder = 5;
	int heroSpeed = hero.GetSpeed();
	int monsterSpeed = monster.GetSpeed();
	int randomSpeed;
	randomSpeed = rand() % 4 + 0;//Allows for more variation in who attacks first by random rolls. Faster things still have an advantage
	heroSpeed += randomSpeed;
	randomSpeed = rand() % 4 + 0;
	monsterSpeed += randomSpeed;


	if (heroSpeed == monsterSpeed) //Thanks Josh, I got it once I looked at it more and this is a lot better
		return (rand() % 2) == 0;
	else 
		return heroSpeed > monsterSpeed;

}
int damageRoll(Character entity)//Rolls to see damage output
{
	//Uses the max-min damages as the range and the min damage as the start point. + 1 is to be inclusive of both min and max
	return rand() % ((entity.GetMaxDamage() - entity.GetMinDamage()) + 1) + entity.GetMinDamage();
}
bool chanceRoll(int Chance)//Rolls to see if the entity hits/crits
{
 return rand() % 100 + 1<= Chance; //range of 1-100
}
void monsterBasicAttack(Character& hero, Character& monster)//Small rounding errors make combat a little weird
{
	int monsterDamageDealt;//Stores monster damage dealt

	//Checks if the monster hit and crit. Could move monster crit to under true if statement to avoid an unneccessary check
	bool monsterHit = chanceRoll(monster.GetHitChance()), monsterCrit = chanceRoll(monster.GetCritChance());

	if (monsterHit == true)//Monster hit
	{
		monsterDamageDealt = damageRoll(monster);
		if (monsterCrit == true)//Monster hit and CRIT
		{
			monsterDamageDealt = monsterDamageDealt * 2;//Crit causes entity to deal *2 damage
			//Damage value are rounded to disallow decimal health losses and make combat transparent
			//Since defense is a decimal the damage dealt is (1-defense)*damage eg(5 damage vs .2 defense deals 4 damage)
			cout << monster.GetName() << " CRIT for " << round(monsterDamageDealt* (1 - hero.GetDefense())) << " ";
			cout << hero.GetName() << "'s armor absorbed " << round(monsterDamageDealt*hero.GetDefense()) << " point(s) of damage" << endl;
		}
		else//Monster hit but did not crit
		{
			cout << monster.GetName() << " hit for " << round(monsterDamageDealt* (1 - hero.GetDefense())) << " ";
			cout << hero.GetName() << "'s armor absorbed " << round(monsterDamageDealt*hero.GetDefense()) << " point(s) of damage" << endl;
		}
		hero.SetCurrentHealth(hero.GetCurrentHealth() - round(monsterDamageDealt * (1 - hero.GetDefense())));
	}
	else if (monsterHit == false)//Monster missed
		cout << "The " << monster.GetName() << " misses!" << endl;
}
void heroBasicAttack(Character& hero, Character& monster)
{
	int heroDamageDealt, menuChoice; //Storage for damage rolls for hero and monster

	bool heroHit = chanceRoll(hero.GetHitChance()), heroCrit = chanceRoll(hero.GetCritChance());//Rolls to see if a hit lands for the hero
	if (heroHit == true)
	{
		heroDamageDealt = damageRoll(hero);//Rolls to see how much damage is dealt by hero before defenses
		if (heroCrit == true)//Hero hit and crit
		{
			heroDamageDealt = heroDamageDealt * 2;//Crit multiplies damage dealt by 2
			/*Damage value are rounded to disallow decimal health losses and make combat easier to read
			Since defense is a decimal the damage dealt is (1-defense)*damage eg(5 damage vs .2 defense deals 4 damage)
			Currently seems to have issues on certain decimals. Must test more*/

			cout << hero.GetName() << " CRIT for " << round(heroDamageDealt* (1 - monster.GetDefense())) << " ";
			cout << "the " << monster.GetName() << "'s armor absorbed " << round(heroDamageDealt*monster.GetDefense()) << " point(s) of damage" << endl;

		}
		else//Hero hit but did not crit
		{
			cout << hero.GetName() << " hit for " << round(heroDamageDealt* (1 - monster.GetDefense())) << " ";
			cout << "the " << monster.GetName() << "'s armor absorbed " << round(heroDamageDealt*monster.GetDefense()) << " point(s) of damage" << endl;
		}
		monster.SetCurrentHealth(monster.GetCurrentHealth() - round(heroDamageDealt * (1 - monster.GetDefense())));
	}
	else if (heroHit == false)//Hero missed
		cout << hero.GetName() << " misses!" << endl;
}
void fight(Character& hero, Character& monster)
{
	bool turnOrder = true;//Initialized to avoid possible errors as "if" statements operate off this value
	int turn = 1;//Sets turn count to 1

	statDisplay(hero, monster);
	do
	{

		cout << "Fight " << gameState.GetFightCount() << "  Round " << turn << endl;
		turnOrder = turnDecider(hero, monster);//Determines which entity moves first
		if (turnOrder == true)//Hero moves first
		{
			heroBasicAttack(hero, monster);
			if (monster.GetCurrentHealth() > 0)//If the monster is alive after the hero attack it gets to move
				monsterBasicAttack(hero, monster);
		}
		else if (turnOrder == false)//Monster moves first
		{
			monsterBasicAttack(hero, monster);
			if (hero.GetCurrentHealth() > 0)//If the hero is alive after the monster attack they get to move
				heroBasicAttack(hero, monster);
		}


		if (hero.GetCurrentHealth() > 0)//Check to see if the hero survived the turn
			cout << hero.GetName() << "'s Health: " << hero.GetCurrentHealth() << endl;
		else if (hero.GetCurrentHealth() <= 0)//Hero has died and sends user to the death screen
			deathScreen(hero);


		if (monster.GetCurrentHealth() > 0)//Check to see if monster survived the turn
			cout << monster.GetName() << " Health: " << monster.GetCurrentHealth() << endl;
		else if (monster.GetCurrentHealth() <= 0)//Monster has died outputs monster name and death
			cout << monster.GetName() << " Has been slain!" << endl;

		cout << endl;
		turn++;
	} while (hero.GetCurrentHealth() > 0 && monster.GetCurrentHealth() > 0);//The fight continues until the monster or hero has died
	gameState.IncrementFightCount();

	cout << hero.GetName() << " gained " << monster.GetGold() << " gold and " << monster.GetExp() << " EXP" << endl;
	hero.SetGold(hero.GetGold() + monster.GetGold());//Hero gold rises by monster gold value
	hero.SetExp(hero.GetExp() + monster.GetExp());//Hero xp rises by monster xp value
	heroLeveler(hero);//Checks to see if the hero has leveled up
	monster.SetCurrentHealth(monster.GetMaxHealth());//Resets monsters health for future use
}
void statDisplay(Character hero, Character monster)//Hero and monster
{
	int fB = 17;//First Buffer

	cout.setf(ios::left);
	cout << "\n" << setw(fB)  << " "<< setw(15) << hero.GetName() << setw(17) << monster.GetName() << endl;
	cout << setw(fB) <<"Health" << setw(15) << hero.GetCurrentHealth() << monster.GetCurrentHealth() << endl;
	cout << setw(fB) <<"Min/Max Damage" << hero.GetMinDamage()<< "/" << setw(8)<< hero.GetMaxDamage() << setw(5) << " " << monster.GetMinDamage() << "/" << monster.GetMaxDamage() << endl;
	cout << setw(fB) <<"Hit/Crit Chance" <<  hero.GetHitChance() <<"/" << hero.GetCritChance() <<setw(10) << "%" << setw(1) << " " << monster.GetHitChance() <<"/" <<monster.GetCritChance() << "%" << endl;
	cout << setw(fB) <<"Speed" << setw(10) << hero.GetSpeed() << setw(5) << " " << monster.GetSpeed() << endl;
	cout << setw(fB) <<"Mana" << setw(10) << hero.GetCurrentMana()  << setw(5) << " " << monster.GetCurrentMana() << endl;
	cout << setw(fB) <<"Defense" <<  hero.GetDefense()*100 <<setw(8) <<"%" << setw(5) << " " << monster.GetDefense()*100<< "%" << endl << endl;
}
void statDisplay(Character entity)//single entity
{
	int fB = 17;//First Buffer

	cout.setf(ios::left);
	cout << "\n" << setw(fB) << entity.GetName()<< endl;
	cout << setw(fB) << "Health" << entity.GetCurrentHealth()<<"/" << entity.GetMaxHealth() << endl;
	cout << setw(fB) <<"Min/Max Damage" << entity.GetMinDamage() << "/" << entity.GetMaxDamage()<< endl;
	cout <<  setw(fB)<<"Hit/Crit Chance"  << entity.GetHitChance() << "/" << entity.GetCritChance() << "%" << endl;
	cout << setw(fB)<<"Speed"   << entity.GetSpeed() << endl;
	cout << setw(fB) <<"Mana" << entity.GetCurrentMana() << endl;
	cout << setw(fB) <<"Defense" << entity.GetDefense() * 100 << "%" << endl << endl;
}
void fightPicker(Character& hero)
{
	int numberOfMonsters = 7;//Quicker change for random function when adding more monsters
	int fightDeterminant = 7;//rand() % numberOfMonsters + 1; //Random roll between 1-numberOfMonsters to determine fight

	if (fightDeterminant == 1)//Skeleton
		fight(hero, Skeleton);
	else if (fightDeterminant == 2)//Slime
		fight(hero, Slime);
	else if (fightDeterminant == 3)//Zombie
		fight(hero, Zombie);
	else if (fightDeterminant == 4)//Imp
		fight(hero, Imp);
	else if (fightDeterminant == 5)//Scaling "Strong Fallen Hero"
	{
		Character FallenHero("Strong Fallen Hero", hero.GetMaxHealth() - 5, hero.GetMinDamage() - 1, hero.GetMaxDamage() - 1,
			hero.GetHitChance() - 10, hero.GetCritChance() - 2, hero.GetSpeed() - 1, hero.GetDefense(), hero.GetMaxMana(),
			50, 20, 1);
		fight(hero, FallenHero);
	}
	else if (fightDeterminant == 6)//Fallen Hero
		fight(hero, FallenHero);
	else if (fightDeterminant == 7)
		fight(hero, Dragon);
}


