#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <ctgmath>

using namespace std;

class GameState //Object to Store basic game state. Xp required to level up, current level, and number of fights.
{
	public: int fightCount, xpReq, levelReq;
	GameState::GameState()
	{

	}
	GameState::GameState(int fights, int reqXp, int reqLevel)
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
}; 
class Character //Base Object all entities are created from
{
 public: int maxHealth, currentHealth, minDamage, maxDamage, hitChance, speed, maxMana, currentMana, gold, exp, level;
		 double defense;
		 string name;
		 Character::Character()
		 {

		 }
		 Character::Character(string Name, int Health, int MinDamage, int MaxDamage, int HitChance, int Speed, double Defense,
			 int Mana, int Gold, int Exp, int Level)
		{
			 name = Name;
			 maxHealth = Health;
			currentHealth = maxHealth;
			minDamage = MinDamage;
			maxDamage = MaxDamage;
			hitChance = HitChance;
			speed = Speed;
			defense = Defense;
			maxMana = Mana;
			currentMana = maxMana;
			gold = Gold;
			exp = Exp;
			level = Level;
		}
		 void SetName(string newName)
		 {
			 name = newName;
		 }
		 string GetName()
		 {
			 return name;
		 }
		void SetCurrentHealth(int newCurrentHealth)
		 {
			 currentHealth = newCurrentHealth;
		 }
		void SetMaxHealth(int newMaxHealth)
		{
			maxHealth = newMaxHealth;
		}
		 int GetCurrentHealth()
		 {
			 return currentHealth;
		 }
		 int GetMaxHealth()
		 {
			 return maxHealth;
		 }
		 int GetMinDamage()
		 {
			 return minDamage;
		 }
		 void SetMinDamage(int newMinDamage)
		 {
			 minDamage = newMinDamage;
		 }
		 int GetMaxDamage()
		 {
			 return maxDamage;
		 }
		 void SetMaxDamage(int newMaxDamage)
		 {
			 maxDamage = newMaxDamage;
		 }
		 double GetDefense()
		 {
			 return defense;
		 }
		 void SetDefense(double newDefense)
		 {
			 defense = newDefense;
		 }
		 int GetHitChance()
		 {
			 return hitChance;
		 }
		 void SetHitChance(int newHitChance)
		 {
			 hitChance = newHitChance;
		 }
		 int GetSpeed()
		 {
			 return speed;
		 }
		 void SetSpeed(int newSpeed)
		 {
			 speed = newSpeed;
		 }
		 int GetGold()
		 {
			 return gold;
		 }
		 void SetGold(int newGold)
		 {
			 gold = newGold;
		 }
		 int GetMaxMana()
		 {
			 return maxMana;
		 }
		 void SetMaxMana(int newMaxMana)
		 {
			 maxMana = newMaxMana;
		 }
		 int GetCurrentMana()
		 {
			 return currentMana;
		 }
		 void SetCurrentMana(int newCurrentMana)
		 {
			 currentMana = newCurrentMana;
		 }
		 int GetExp()
		 {
			 return exp;
		 }
		 void SetExp(int newExp)
		 {
			 exp = newExp;
		 }
		 int GetLevel()
		 {
			 return level;
		 }
		 void SetLevel(int newLevel)
		 {
			 level = newLevel;
		 }

};
GameState gameState(1, 15, 1);
//Name, Max Health, Min Damage, Max Damage, Hit Chance, Speed, Defense, Mana, Gold, EXP, Level
Character Hero1(   "Hero",		100, 3, 5, 80, 3, .2, 5,  0, 0, 1);
Character Skeleton("Skeleton",    5, 1, 3, 70, 3, .1, 5, 20, 2, 1);
Character Zombie(  "Zombie",	 10, 3, 5, 50, 1, .2, 5, 50, 3, 1);
Character Slime(   "Slime",		  6, 1, 2, 60, 4, .5, 5, 20, 1, 1);
Character Imp(     "Imp",		  3, 1, 2, 80, 6, 0, 20, 15, 2, 1);	 
void menuList(Character& hero);
/*void turnDecider(Character hero, Character monster) //Need to figure out a way to decide speed and do a turn order while attempting to keep
fight() small or avoiding fight() with multiple versions ie heroFirstFight() monsterFirstFight()
{
	int turnOrder = 5;
	if (hero.GetSpeed() > monster.GetSpeed())
	{

	}
	else if (hero.GetSpeed() == monster.GetSpeed())
	{
		turnOrder = rand() % 2 + 1;

	}
	else
	{

	}
}*/
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
	cout << "\n\t\t" << hero.GetName() << " has died!" << endl;
	cout << "\t\tThey defeated " << gameState.GetFightCount() -1 << " monster(s)";
	exit(0);
}
int damageRoll(Character hero)//Rolls to see damage output
{
	int dmgRoll = rand() % ((hero.GetMaxDamage() - hero.GetMinDamage())+1) + hero.GetMinDamage();//Uses the max-min damages as the range and the min damage as the start point
	//ex. 5 min damage and 7 max is and range of 2
	return dmgRoll;
}
bool hitChanceRoll(int hitChance)//Rolls to see if the entity hits
{
	int hitRoll = rand() % 100 + 1; //range of 1-100
	if (hitRoll <= hitChance)//Compares the roll to the hit chance eg if the roll is 50 and hit chance is 60 it is a hit. Roll of 61 or higher would be a miss
	{
		return true;//Entity hits
	}
	else
	{
		return false;//Entity misses
	}
}
void heroStatSelection(Character& hero)//Allows the user to improve the hero upon leveling up
{
	char menuChoice;
	cout << "\nCongratulations! Your hero has leveled up. Please select your reward!" << endl;
	cout << "Hero Max Health is: " << hero.GetMaxHealth() << " Minimum damage is: " << hero.GetMinDamage() << " Maximum damage is: " << hero.GetMaxDamage() << endl;
	cout << "Hit Chance is: " << hero.GetHitChance() << " Speed is: " << hero.GetSpeed() << " Mana is: " << hero.GetMaxMana() << " Defense is: " << hero.GetDefense() * 100 << "%" << endl;
	cout << "\n1.+5 Max Health  2.+1 Minimum Damage  3.+1 Maximum Damage  4.+5% Hit Chance \n5.+1 Speed       6.+5 Max Mana        7.+5% Defense" << endl;
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
		cout << "Your Hero now has " << hero.GetMaxDamage() << " Maximum Damage" << endl;
		break;
	case '4':
		hero.SetHitChance(hero.GetHitChance() + 5);
		cout << "Your Hero now has a(n)" << hero.GetHitChance() << "% Hit Chance" << endl;
		break;
	case '5':
		hero.SetSpeed(hero.GetSpeed() + 1);
		cout << "Your Hero now has " << hero.GetSpeed() << " Speed" << endl;
		break;
	case '6':
		hero.SetMaxMana(hero.GetMaxMana() + 5);
		hero.SetCurrentMana(hero.GetCurrentMana() + 5);
		cout << "Your Hero now has " << hero.GetCurrentMana() << "/" << hero.GetMaxMana() << " Mana" << endl;
		break;
	case '7':
		hero.SetDefense(hero.GetDefense() + .05);
		cout << "Your Hero now has " << hero.GetDefense()*100 << "% Defense" << endl;
		break;
	default:
		cout << "\nPlease enter an option from the list";
		menuList(hero);
	}

}
void heroLeveler(Character& hero)//Determines if the hero has leveled up or not
{
	

	
	if (hero.GetLevel() == gameState.GetLevelReq())
	{
		if (hero.GetExp() >= gameState.GetXpReq())
		{
			hero.SetLevel(hero.GetLevel() + 1);
			heroStatSelection(hero);
			gameState.SetXpReq(gameState.GetXpReq()+15);
			gameState.SetLevelReq(gameState.GetLevelReq() +1);
		}
	}
	
}
//fight(Hero1, Skeleton)
void fight(Character& hero, Character& monster)
{
	cout << "\n" << hero.GetName() << " Health is: " << hero.GetCurrentHealth() << " Minimum damage is: " << hero.GetMinDamage() << " Maximum damage is: " << hero.GetMaxDamage() << endl;
	cout << "Hit Chance is: " << hero.GetHitChance() << " Speed is: " << hero.GetSpeed() << " Mana is: " << hero.GetCurrentMana() << " Defense is: " << hero.GetDefense() * 100 << "%" << endl;
	cout << monster.GetName() << " Health is: " << monster.GetCurrentHealth() << " Minimum damage is: " << monster.GetMinDamage() << " Maximum damage is: " << monster.GetMaxDamage() << endl;
	cout << "Hit Chance is: " << monster.GetHitChance() << " Speed is: " << monster.GetSpeed() << " Mana is: " << monster.GetCurrentMana() << " Defense is: " << monster.GetDefense() * 100 << "%" << endl;
	
	int round = 1, heroDamageDealt,monsterDamageDealt; //Storage for damage rolls for hero and monster
	do
	{
		
		cout << "\nFight " << gameState.GetFightCount() << " Round " << round << endl;
		bool heroHit = hitChanceRoll(hero.GetHitChance());//Rolls to see if a hit lands for the hero
		if (heroHit == true)
		{
			heroDamageDealt = damageRoll(hero);//Rolls to see how much damage is dealt by hero before defenses
			if (heroDamageDealt % 2 == 0)//need a better way to remove decimals and round damage as this does not work
			{
				monster.SetCurrentHealth(monster.GetCurrentHealth() - heroDamageDealt * (1 - monster.GetDefense()));
				cout <<  hero.GetName() << " hit for " << heroDamageDealt* (1 - monster.GetDefense());
				cout << " the " << monster.GetName() << "'s armor absorbed " << heroDamageDealt*monster.GetDefense() << " point(s) of damage" << endl;
			}
			else if (heroDamageDealt % 2 == 1)
			{
				int truncHeroAttack = heroDamageDealt * (1 - monster.GetDefense());
				monster.SetCurrentHealth(monster.GetCurrentHealth() - truncHeroAttack);
				cout << hero.GetName() << " hit for " << truncHeroAttack;
				cout << " the " << monster.GetName() << "'s armor absorbed " << heroDamageDealt-truncHeroAttack << " point(s) of damage" << endl;
			}
		}
			
		
		else if (heroHit == false)
		{
			cout << hero.GetName() << " misses!" << endl;
		}
		bool monsterHit = hitChanceRoll(monster.GetHitChance());
		if(monsterHit == true)
		{
			monsterDamageDealt = damageRoll(monster);
			if (monsterDamageDealt % 2 == 0)
			{
				hero.SetCurrentHealth(hero.GetCurrentHealth() - monsterDamageDealt * (1 - hero.GetDefense()));
				cout << monster.GetName() << " hit for " << monsterDamageDealt* (1 - hero.GetDefense()) << " ";
				cout << hero.GetName() << "'s  armor absorbed " << monsterDamageDealt*hero.GetDefense() << " point(s) of damage" << endl;
			}
			else if (monsterDamageDealt % 2 == 1)
			{
				int truncMonsterAttack = monsterDamageDealt * (1 - hero.GetDefense());
				hero.SetCurrentHealth(hero.GetCurrentHealth() - truncMonsterAttack);
				cout << monster.GetName() << " hit for " << truncMonsterAttack << " ";
				cout << hero.GetName() << " 's armor absorbed " << monsterDamageDealt -truncMonsterAttack << " point(s) of damage" << endl;
			}
		}
		else if (monsterHit == false)
		{
			cout << "The " << monster.GetName() << " misses!" << endl;
		}
		
		
		if (hero.GetCurrentHealth() > 0)//Check to see if the hero survived the round
		{
			cout << hero.GetName() << "'s Health: " << hero.GetCurrentHealth() << endl;
		}
		else if (hero.GetCurrentHealth() <= 0)//Hero has died and sends user to the death screen
		{
			deathScreen(hero);
		}

		if (monster.GetCurrentHealth() > 0)//Check to see if monster survived the round
		{
			cout <<  monster.GetName() << " Health: " << monster.GetCurrentHealth() << endl;
		}
		else if (monster.GetCurrentHealth() <= 0)//Monster has died outputs monster name and death
		{
			cout  << monster.GetName() << " Has been slain!" << endl;
		}
		cout << endl;
		round++;
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
