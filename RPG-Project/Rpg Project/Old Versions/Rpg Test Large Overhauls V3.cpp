#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <ctgmath>
#include "Character.h"
#include "GameState.h"

using namespace std;

/*class GameState //Object to Store basic game state. Xp required to level up, current level, and number of fights.
{
	public: int fightCount, xpReq, levelReq, heroCount;
	GameState::GameState()
	{

	}
	GameState::GameState(int fights, int reqXp, int reqLevel, int HeroCount)
	{
		fightCount = fights;
		xpReq = reqXp;
		levelReq = reqLevel;
	}
	void SetFightCount(int newFightCount)
	{
		fightCount = newFightCount;
	}
	void IncrementFightCount()
	{
		fightCount++;
	}
	int GetFightCount()
	{
		return fightCount;
	}
	void SetXpReq(int newXpReq)
	{
		xpReq = newXpReq;
	}
	int GetXpReq()
	{
		return xpReq;
	}
	void SetLevelReq(int newLevelReq)
	{
		levelReq = newLevelReq;
	}
	int GetLevelReq()
	{
		return levelReq;
	}
	void SetHeroCount(int newHeroCount)
	{
		heroCount = newHeroCount;
	}
	int GetHeroCount()
	{
		return heroCount;
	}
}; */

GameState gameState(1, 10, 1, 1);
//Name, Max Health, Min Damage, Max Damage, Hit Chance, Crit Chance, Speed, Defense, Mana, Gold, EXP, Level
Character Hero1(   "Hero",		 20, 3, 5, 80, 5, 3, .2, 5,  0, 0, 1);
Character Skeleton("Skeleton",    5, 1, 3, 70, 3, 3, .1, 5, 20, 2, 1);
Character Zombie(  "Zombie",	 10, 3, 5, 50, 1, 1, .2, 5, 50, 3, 1);
Character Slime(   "Slime",		  6, 1, 2, 60, 2, 4, .5, 5, 20, 1, 1);
Character Imp(     "Imp",		  3, 1, 2, 80, 2, 6, 0, 20, 15, 2, 1);	 
void menuList(Character& hero);
bool turnDecider(Character hero, Character monster) //True == Hero moves first. False == Monster moves first

{
	int turnOrder = 5, heroSpeed = hero.GetSpeed(), monsterSpeed = monster.GetSpeed(), randomSpeed;
	randomSpeed = rand() % 4 + 0;//Allows for more variation in who attacks first by random rolls. Faster things still have an advantage
	heroSpeed += randomSpeed;
	randomSpeed = rand() % 4 + 0;
	monsterSpeed += randomSpeed;

	if (heroSpeed > monsterSpeed)
	{
		return true;
	}
	else if (heroSpeed == monsterSpeed)
	{
		turnOrder = rand() % 2 + 1;
		if (turnOrder == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
void characterNamer(Character& hero) //Allows the user to name the character, Loops until user is satisfied.
{
	string heroName;
	int menuChoice = 0;
	do
	{
		cout << "Enter a name for your hero" << endl;
		cin >> heroName;
		hero.SetName(heroName);
		cout << "Your hero is now named " << hero.GetName() << ". Is this correct? \n1.Yes \n2.No" << endl;
		cin >> menuChoice;
	} while (menuChoice == 2);

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
	if (menuChoice == 1)
	{
		Character Hero("Hero", 10, 3, 5, 80, 5, 3, .2, 5, hero.GetGold(), hero.GetExp()/2, 1);//Hero recieves gold of previous hero and 1/2 of xp
		gameState.SetXpReq(10);
		gameState.SetLevelReq(1);
		gameState.SetHeroCount(gameState.GetHeroCount() + 1);
		initializer(Hero);
	}

	
	exit(0);
}
int damageRoll(Character entity)//Rolls to see damage output
{
	int dmgRoll = rand() % ((entity.GetMaxDamage() - entity.GetMinDamage())+1) + entity.GetMinDamage();//Uses the max-min damages as the range and the min damage as the start point
	//ex. 5 min damage and 7 max is and range of 2
	return dmgRoll;
}
bool chanceRoll(int Chance)//Rolls to see if the entity hits/crits
{
	int hitRoll = rand() % 100 + 1; //range of 1-100
	if (hitRoll <= Chance)//Compares the roll to the hit chance eg if the roll is 50 and hit chance is 60 it is a hit. Roll of 61 or higher would be a miss
	{
		return true;//Entity hits and or crits
	}
	else
	{
		return false;//Entity misses and or hits normally
	}
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
		//if (hero.GetMinDamage < hero.GetMaxDamage) //Why does this if statement break all the cout? makes them ambiguous
		//{
			hero.SetMinDamage(hero.GetMinDamage() + 1);
			cout << "Your Hero now has " << hero.GetMinDamage() << " Minimum Damage" << endl;
		/*}
		else
		{
			cout << "Minimum damage may not exceed maximum damage please select another attribute" << endl;
			heroStatSelection(hero);
		}*/
		break;
	case '3':
		hero.SetMaxDamage(hero.GetMaxDamage() + 1);
		cout << hero.GetName() << " now has " << hero.GetMaxDamage() << " Maximum Damage" << endl;
		break;
	case '4':
		hero.SetHitChance(hero.GetHitChance() + 5);
		cout << hero.GetName() << " now has a(n)" << hero.GetHitChance() << "% Hit Chance" << endl;
		break;
	case '5':
		hero.SetSpeed(hero.GetSpeed() + 1);
		cout << hero.GetName() << " now has " << hero.GetSpeed() << " Speed" << endl;
		break;
	case '6':
		hero.SetMaxMana(hero.GetMaxMana() + 5);
		hero.SetCurrentMana(hero.GetCurrentMana() + 5);
		cout << hero.GetName() << " now has " << hero.GetCurrentMana() << "/" << hero.GetMaxMana() << " Mana" << endl;
		break;
	case '7':
		hero.SetDefense(hero.GetDefense() + .05);
		cout << hero.GetName() << " now has " << hero.GetDefense()*100 << "% Defense" << endl;
		break;
	case '8':
		hero.SetCritChance(hero.GetCritChance() + 2);
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
		if (hero.GetLevel() == gameState.GetLevelReq() && hero.GetExp() >= gameState.GetXpReq())
		{

			hero.SetLevel(hero.GetLevel() + 1);
			heroStatSelection(hero);
			gameState.SetXpReq(gameState.GetXpReq() + 10);
			gameState.SetLevelReq(gameState.GetLevelReq() + 1);
			
		}
	}while (hero.GetExp() >= gameState.GetXpReq());
}
void monsterTurn(Character& hero, Character& monster)
{
	int monsterDamageDealt;
	bool monsterHit = chanceRoll(monster.GetHitChance()), monsterCrit = chanceRoll(monster.GetCritChance());
	
	if (monsterHit == true)
	{
		monsterDamageDealt = damageRoll(monster);
		if(monsterCrit == true)
		{
			monsterDamageDealt = monsterDamageDealt * 2;
			cout << monster.GetName() << " CRIT for " << round(monsterDamageDealt* (1 - hero.GetDefense())) << " ";
			cout << hero.GetName() << "'s  armor absorbed " << round(monsterDamageDealt*hero.GetDefense()) << " point(s) of damage" << endl;
		}
		else
		{
			cout << monster.GetName() << " hit for " << round(monsterDamageDealt* (1 - hero.GetDefense())) << " ";
			cout << hero.GetName() << "'s  armor absorbed " << round(monsterDamageDealt*hero.GetDefense()) << " point(s) of damage" << endl;
		}
		hero.SetCurrentHealth(hero.GetCurrentHealth() - round(monsterDamageDealt * (1 - hero.GetDefense())));
	}
	else if (monsterHit == false)
	{
		cout << "The " << monster.GetName() << " misses!" << endl;
	}
}
void heroTurn(Character& hero, Character& monster)
{
	int heroDamageDealt, menuChoice; //Storage for damage rolls for hero and monster

	bool heroHit = chanceRoll(hero.GetHitChance()), heroCrit = chanceRoll(hero.GetCritChance());//Rolls to see if a hit lands for the hero
	if (heroHit == true)
	{
		heroDamageDealt = damageRoll(hero);//Rolls to see how much damage is dealt by hero before defenses
		if (heroCrit == true)
		{
			heroDamageDealt = heroDamageDealt * 2;
			monster.SetCurrentHealth(monster.GetCurrentHealth() - round(heroDamageDealt * (1 - monster.GetDefense())));
			cout << hero.GetName() << " CRIT for " << round(heroDamageDealt* (1 - monster.GetDefense()));
			cout << " the " << monster.GetName() << "'s armor absorbed " << round(heroDamageDealt*monster.GetDefense()) << " point(s) of damage" << endl;

		}
		else
		{
			monster.SetCurrentHealth(monster.GetCurrentHealth() - round(heroDamageDealt * (1 - monster.GetDefense())));
			cout << hero.GetName() << " hit for " << round(heroDamageDealt* (1 - monster.GetDefense()));
			cout << " the " << monster.GetName() << "'s armor absorbed " << round(heroDamageDealt*monster.GetDefense()) << " point(s) of damage" << endl;
		}
	}
		else if (heroHit == false)
		{
			cout << hero.GetName() << " misses!" << endl;
		}
}
void fight(Character& hero, Character& monster)
{
	bool turnOrder = true;
	int turn = 1;
	cout << "\n" << hero.GetName() << " Health is: " << hero.GetCurrentHealth() << " Minimum damage is: " << hero.GetMinDamage() << " Maximum damage is: " << hero.GetMaxDamage() << endl;
	cout << "Hit Chance is: " << hero.GetHitChance() << " Speed is: " << hero.GetSpeed() << " Mana is: " << hero.GetCurrentMana() << " Defense is: " << hero.GetDefense() * 100 << "%";
	cout << " Crit Chance is: " << hero.GetCritChance() << "%" << endl;
	
	cout << monster.GetName() << " Health is: " << monster.GetCurrentHealth() << " Minimum damage is: " << monster.GetMinDamage() << " Maximum damage is: " << monster.GetMaxDamage() << endl;
	cout << "Hit Chance is: " << monster.GetHitChance() << " Speed is: " << monster.GetSpeed() << " Mana is: " << monster.GetCurrentMana() << " Defense is: " << monster.GetDefense() * 100 << "%";
	cout << " Crit Chance is: " << monster.GetCritChance() << "%" << endl << endl;
	
	do
	{
		
		cout << "Fight " << gameState.GetFightCount() << "  Round " << turn << endl;
		turnOrder = turnDecider(hero, monster);
		if (turnOrder == true)
		{
			heroTurn(hero, monster);
			if (monster.GetCurrentHealth() > 0)
			{
				monsterTurn(hero, monster);
			}
		}
		else if (turnOrder == false)
		{
			monsterTurn(hero, monster);
			if (hero.GetCurrentHealth() > 0)
			{
				heroTurn(hero, monster);
			}
		}
	
		if (hero.GetCurrentHealth() > 0)//Check to see if the hero survived the turn
		{
			cout << hero.GetName() << "'s Health: " << hero.GetCurrentHealth() << endl;
		}
		else if (hero.GetCurrentHealth() <= 0)//Hero has died and sends user to the death screen
		{
			deathScreen(hero);
		}

		if (monster.GetCurrentHealth() > 0)//Check to see if monster survived the turn
		{
			cout <<  monster.GetName() << " Health: " << monster.GetCurrentHealth() << endl;
		}
		else if (monster.GetCurrentHealth() <= 0)//Monster has died outputs monster name and death
		{
			cout  << monster.GetName() << " Has been slain!" << endl;
		}
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
void fightPicker(Character& hero)
{
	int fightDeterminant = rand() % 4 + 1; //Random roll between 1-4 to determine fight

	if (fightDeterminant == 1)//Skeleton
	{
		fight(hero, Skeleton);
	}
	else if (fightDeterminant == 2)//Slime
	{
		fight(hero, Slime);
	}
	else if (fightDeterminant == 3)//Zombie
	{
		fight(hero, Zombie);
	}
	else if (fightDeterminant == 4)//Imp
	{
		fight(hero, Imp);
	}
}
void itemShop(Character& hero) //Allows user to spend gold only to restore health at the moment WIP
{
	int maxHealthDifference;
	char menuChoice;
	cout << hero.GetName() << " has " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " health and " << hero.GetGold() << " gold" << endl;
	cout << "Welcome to the item shop please select from the following menu" << endl;
	cout << "1. Buy a health potion(+5hp) 5 Gold \n2. Refill missing health 1 gold per missing Health \n3. Exit the Item Shop" << endl;
	cin >> menuChoice;
	switch (menuChoice) {
	case '1':
		if (hero.GetGold() >= 5)//Ensures the user has enough gold
		{
			if (hero.GetCurrentHealth() + 5 > hero.GetMaxHealth())//Prevents hero from gaining more than the maximum health
			{
				hero.SetGold(hero.GetGold() - 5);
				hero.SetCurrentHealth(hero.GetMaxHealth());
				cout << hero.GetName() << " has " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " health and " << hero.GetGold() << " gold" << endl;
				menuList(hero);


			}
			else
			{
				hero.SetGold(hero.GetGold() - 5);
				hero.SetCurrentHealth(hero.GetCurrentHealth() + 5);
				cout << hero.GetName() << " has " << hero.GetCurrentHealth() << "/" << hero.GetMaxHealth() << " health and " << hero.GetGold() << " gold" << endl;
				menuList(hero);

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
			menuList(hero);
		}
		else
		{
			cout << "You don't have enough gold for that" << endl;
		}
	case '3'://This may be redundant
		menuList(hero);
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
