#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;
//bool hitChanceRoll(int hitChance);
//int deathScreen();
int numberOfFights = 1;
//void fightPicker();
void menuList();
//int damageRoll(int minDamage, int maxDamage);


class Character //Base Object all entities are created from
{
 public: int maxHealth, currentHealth, minDamage, maxDamage, hitChance, speed, maxMana, currentMana, gold, exp, level;
		 double defense;
		 string name;
		 Character::Character()
		 {

		 }
		 Character::Character(string n, int h, int minD, int maxD, int hC, int s, double d,int mp, int g, int xp, int l)
		{
			 name = n;
			 maxHealth = h;
			currentHealth = maxHealth;
			minDamage = minD;
			maxDamage = maxD;
			hitChance = hC;
			speed = s;
			defense = d;
			maxMana = mp;
			currentMana = maxMana;
			gold = g;
			exp = xp;
			level = l;
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
//Name, Max Health, Min Damage, Max Damage, Hit Chance, Speed, Defense, Mana, Gold, EXP, Level
Character Hero1("Hero",			100, 3, 5, 80, 3, .2, 5, 0, 0, 1);
Character Skeleton("Skeleton",   5, 1, 3, 70, 3, .1, 5, 20,2,1);
Character Zombie("Zombie",		10, 3, 5, 50, 1, .2, 5, 50,3,1);
Character Slime("Slime",		 6, 1, 2, 60, 4, .5, 5, 20,1,1);
Character Imp("Imp",			 3, 1, 2, 80, 6, 0, 20, 15,2,1);
int main()
{
	srand(time(NULL));//Seed the random number Generator
	do 
	{
		menuList();//Brings up main menu loop

	} while (Hero1.GetCurrentHealth() > 0);//Continues until the Hero dies

}
int deathScreen()
{
	cout << "\n\t\tYour hero has died!" << endl;
	cout << "\t\tThey defeated " << numberOfFights -1 << " monster(s)";
	exit(0);
}
int damageRoll(int minDamage, int maxDamage)//Rolls to see damage output
{
	int dmgRoll = rand() % ((maxDamage - minDamage)+1) + minDamage;//Uses the max-min damages as the range and the min damage as the start point
	//ex. 5 min damage and 7 max is and range of 2
	return dmgRoll;
}
bool hitChanceRoll(int hitChance)//Rolls to see if the entity hits
{
	int hitRoll = rand() % 100 + 0;
	if (hitRoll <= hitChance)//Compares the roll to the hit chance eg if the roll is 50 and hit chance is 60 it is a hit. Roll of 61 or higher would be a miss
	{
		return true;
	}
	else
	{
		return false;
	}
}
void heroStatSelection()//Allows the user to improve the hero upon leveling up
{
	char menuChoice;
	cout << "\nCongratulations! Your hero has leveled up. Please select your reward!" << endl;
	cout << "Hero Max Health is: " << Hero1.GetMaxHealth() << " Minimum damage is: " << Hero1.GetMinDamage() << " Maximum damage is: " << Hero1.GetMaxDamage() << endl;
	cout << "Hit Chance is: " << Hero1.GetHitChance() << " Speed is: " << Hero1.GetSpeed() << " Mana is: " << Hero1.GetMaxMana() << " Defense is: " << Hero1.GetDefense() * 100 << "%" << endl;
	cout << "\n1.+5 Max Health  2.+1 Minimum Damage  3.+1 Maximum Damage  4.+5% Hit Chance \n5.+1 Speed       6.+5 Max Mana        7.+5% Defense" << endl;
	cin >> menuChoice;

	switch (menuChoice) {
	case '1':
		Hero1.SetMaxHealth(Hero1.GetMaxHealth() + 5);
		Hero1.SetCurrentHealth(Hero1.GetCurrentHealth() + 5);
		cout << "Your Hero now has " << Hero1.GetCurrentHealth() << "/" << Hero1.GetMaxHealth() << " Health" << endl;
		break;
	case '2':
		Hero1.SetMinDamage(Hero1.GetMinDamage() + 1);
		cout << "Your Hero now has " << Hero1.GetMinDamage() << " Minimum Damage" << endl;
		break;
	case '3':
		Hero1.SetMaxDamage(Hero1.GetMaxDamage() + 1);
		cout << "Your Hero now has " << Hero1.GetMaxDamage() << " Maximum Damage" << endl;
		break;
	case '4':
		Hero1.SetHitChance(Hero1.GetHitChance() + 5);
		cout << "Your Hero now has a(n)" << Hero1.GetHitChance() << "% Hit Chance" << endl;
		break;
	case '5':
		Hero1.SetSpeed(Hero1.GetSpeed() + 1);
		cout << "Your Hero now has " << Hero1.GetSpeed() << " Speed" << endl;
		break;
	case '6':
		Hero1.SetMaxMana(Hero1.GetMaxMana() + 5);
		Hero1.SetCurrentMana(Hero1.GetCurrentMana() + 5);
		cout << "Your Hero now has " << Hero1.GetCurrentMana() << "/" << Hero1.GetMaxMana() << " Mana" << endl;
		break;
	case '7':
		Hero1.SetDefense(Hero1.GetDefense() + .05);
		cout << "Your Hero now has " << Hero1.GetDefense()*100 << "% Defense" << endl;
		break;
	default:
		cout << "\nPlease enter an option from the list";
		menuList();
	}

}
void heroLeveler(int heroLevel, int heroExp)//Determines if the hero has leveled up or not
{
	if (heroLevel == 1)
	{
		if (heroExp >= 10)
		{
			Hero1.SetLevel(Hero1.GetLevel() + 1);
			heroStatSelection();
		}
	}
	if (heroLevel == 2)
	{
		if (heroExp >= 25)
		{
			Hero1.SetLevel(Hero1.GetLevel() + 1);
			heroStatSelection();
		}
	}
	if (heroLevel == 3)
	{
		if (heroExp >= 40)
		{
			Hero1.SetLevel(Hero1.GetLevel() + 1);
			heroStatSelection();
		}
	}
	if (heroLevel == 4)
	{
		if (heroExp >= 55)
		{
			Hero1.SetLevel(Hero1.GetLevel() + 1);
			heroStatSelection();
		}
	}
	if (heroLevel == 5)
	{
		if (heroExp >= 70)
		{
			Hero1.SetLevel(Hero1.GetLevel() + 1);
			heroStatSelection();
		}
	}
	if (heroLevel == 6)
	{
		if (heroExp >= 90)
		{
			Hero1.SetLevel(Hero1.GetLevel() + 1);
			heroStatSelection();
		}
	}
}
void fight(int heroHealth, int heroMinDamage, int heroMaxDamage, int heroHitChance, int heroSpeed, double heroDefense, int heroMana,
	string monsterName, int monsterHealth, int monsterMinDamage, int monsterMaxDamage, int monsterHitChance, int monsterSpeed,
	int monsterMana, int monsterGold, int monsterExp, double monsterDefense)
{
	cout << "\nHero Health is: " << heroHealth << " Minimum damage is: " << heroMinDamage << " Maximum damage is: " << heroMaxDamage << endl;
	cout << "Hit Chance is: " << heroHitChance << " Speed is: " << heroSpeed << " Mana is: " << heroMana << " Defense is: " << heroDefense * 100 << "%" << endl;
	cout << monsterName<< " Health is: " << monsterHealth << " Minimum damage is: " << monsterMinDamage << " Maximum damage is: " << monsterMaxDamage << endl;
	cout << "Hit Chance is: " << monsterHitChance << " Speed is: " << monsterSpeed << " Mana is: " << monsterMana << " Defense is: " << monsterDefense * 100 << "%" << endl;
	
	int round = 1, heroDamageDealt,monsterDamageDealt; //Storage for damage rolls for hero and monster
	do
	{
		
		cout << "\nFight " << numberOfFights << " Round " << round << endl;
		bool heroHit = hitChanceRoll(heroHitChance);//Rolls to see if a hit lands for the hero
		if (heroHit == true)
		{
			heroDamageDealt = damageRoll(heroMinDamage, heroMaxDamage);//Rolls to see how much damage is dealt by hero before defenses
			if (heroDamageDealt % 2 == 0)//Need a better way to remove decimals and round damage
			{
				monsterHealth = monsterHealth - heroDamageDealt * (1 - monsterDefense);
				cout << "Hero hit for " << heroDamageDealt* (1 - monsterDefense);
				cout << " the " << monsterName << "'s armor absorbed " << heroDamageDealt*monsterDefense << " point(s) of damage" << endl;
			}
			else if (heroDamageDealt % 2 == 1)
			{
				int truncHeroAttack = heroDamageDealt * (1 - monsterDefense);
				monsterHealth = monsterHealth - truncHeroAttack;
				cout << "Hero hit for " << truncHeroAttack;
				cout << " the " << monsterName << "'s armor absorbed " << heroDamageDealt-truncHeroAttack << " point(s) of damage" << endl;
			}
		}
			
		
		else if (heroHit == false)
		{
			cout << "The hero misses!" << endl;
		}
		bool monsterHit = hitChanceRoll(monsterHitChance);
		if(monsterHit == true)
		{
			monsterDamageDealt = damageRoll(monsterMinDamage, heroMaxDamage);
			if (monsterDamageDealt % 2 == 0)
			{
				heroHealth = heroHealth - monsterDamageDealt * (1 - heroDefense);
				cout << monsterName << " hit for " << monsterDamageDealt* (1 - heroDefense);
				cout << " the hero's armor absorbed " << monsterDamageDealt*heroDefense << " point(s) of damage" << endl;
			}
			else if (monsterDamageDealt % 2 == 1)
			{
				int truncMonsterAttack = monsterDamageDealt * (1 - heroDefense);
				heroHealth = heroHealth - truncMonsterAttack;
				cout << monsterName << " hit for " << truncMonsterAttack;
				cout << " the hero's armor absorbed " << monsterDamageDealt -truncMonsterAttack << " point(s) of damage" << endl;
			}
		}
		else if (monsterHit == false)
		{
			cout << "The " << monsterName << " misses!" << endl;
		}
		
		
		Hero1.SetCurrentHealth(heroHealth);//Updates hero's current health to object
		if (heroHealth > 0)//Check to see if the hero survived the round
		{
			cout << "Hero Health: " << heroHealth << endl;
		}
		else if (heroHealth <= 0)
		{
			deathScreen();
		}

		if (monsterHealth > 0)//Check to see if monster survived the round
		{
			cout <<  monsterName << " Health: " << monsterHealth << endl;
		}
		else if (monsterHealth <= 0)
		{
			cout  << monsterName << " Has been slain!" << endl;
		}
		cout << endl;
		round++;
	} while (heroHealth > 0 && monsterHealth > 0);//The fight continues until the monster or hero has died
	numberOfFights++;

	cout << "The Hero gained " << monsterGold << " gold and " << monsterExp << " EXP" << endl;
	Hero1.SetGold(Hero1.GetGold() + monsterGold);
	Hero1.SetExp(Hero1.GetExp() + monsterExp);
	heroLeveler(Hero1.GetLevel(), Hero1.GetExp());
}
/*void monsterCreation()
{
	for (int i = 1; i < 30; i++) {
		Skeleton[i] = Character("Skeleton",6,2,65,0);
	}
	for (int i = 1; i < 30; i++) {
		Zombie[i] = Character("Zombie", 10, 5, 30, .25);
	}
	for (int i = 1; i < 30; i++) {
		Slime[i] = Character("Slime", 8, 1, 70, 0);
	}
	for (int i = 1; i < 30; i++) {
		Imp[i] = Character("Imp", 2, 3, 50, 0);
	}
}*/
void fightPicker()
{
	int fightDeterminant = rand() % 4 + 1;

	if (fightDeterminant == 1)//Skeleton
	{
		fight(Hero1.GetCurrentHealth(), Hero1.GetMinDamage(), Hero1.GetMaxDamage(), Hero1.GetHitChance(), Hero1.GetSpeed(), Hero1.GetDefense(), Hero1.GetCurrentMana(),
			Skeleton.GetName(), Skeleton.GetCurrentHealth(), Skeleton.GetMinDamage(), Skeleton.GetMaxDamage(), Skeleton.GetHitChance(), Skeleton.GetSpeed(),
			Skeleton.GetCurrentMana(), Skeleton.GetGold(), Skeleton.GetExp(), Skeleton.GetDefense());
	}
	else if (fightDeterminant == 2)//Slime
	{
		fight(Hero1.GetCurrentHealth(), Hero1.GetMinDamage(), Hero1.GetMaxDamage(), Hero1.GetHitChance(), Hero1.GetSpeed(), Hero1.GetDefense(), Hero1.GetCurrentMana(),
			Slime.GetName(), Slime.GetCurrentHealth(), Slime.GetMinDamage(), Slime.GetMaxDamage(), Slime.GetHitChance(), Slime.GetSpeed(),
			Slime.GetCurrentMana(), Slime.GetGold(), Slime.GetExp(), Slime.GetDefense());
	}
	else if (fightDeterminant == 3)//Zombie
	{
		fight(Hero1.GetCurrentHealth(), Hero1.GetMinDamage(), Hero1.GetMaxDamage(), Hero1.GetHitChance(), Hero1.GetSpeed(), Hero1.GetDefense(), Hero1.GetCurrentMana(),
			Zombie.GetName(), Zombie.GetCurrentHealth(), Zombie.GetMinDamage(), Zombie.GetMaxDamage(), Zombie.GetHitChance(), Zombie.GetSpeed(),
			Zombie.GetCurrentMana(), Zombie.GetGold(), Zombie.GetExp(), Zombie.GetDefense());
	}
	else if (fightDeterminant == 4)//Imp
	{
		fight(Hero1.GetCurrentHealth(), Hero1.GetMinDamage(), Hero1.GetMaxDamage(), Hero1.GetHitChance(), Hero1.GetSpeed(), Hero1.GetDefense(), Hero1.GetCurrentMana(),
			Imp.GetName(), Imp.GetCurrentHealth(), Imp.GetMinDamage(), Imp.GetMaxDamage(), Imp.GetHitChance(), Imp.GetSpeed(),
			Imp.GetCurrentMana(), Imp.GetGold(), Imp.GetExp(), Imp.GetDefense());
	}
}
void itemShop()
{
	int maxHealthDifference;
	char menuChoice;
	cout << "Your hero has " << Hero1.GetCurrentHealth() << "/" << Hero1.GetMaxHealth() << " health" << endl;
	cout << "Welcome to the item shop please select from the following menu" << endl;
	cout << "1. Buy a health potion(+5hp) \n2. Refill missing health \n3. Exit the Item Shop" << endl;
	cin >> menuChoice;
	switch (menuChoice) {
	case '1':
		if (Hero1.GetCurrentHealth() + 5 > Hero1.GetMaxHealth())
		{
			Hero1.SetCurrentHealth(Hero1.GetMaxHealth());
			cout << "Your hero has " << Hero1.GetCurrentHealth() << "/" << Hero1.GetMaxHealth() << " health" << endl;
			menuList();
		}
		else
		{
			Hero1.SetCurrentHealth(Hero1.GetCurrentHealth() + 5);
			cout << "Your hero has " << Hero1.GetCurrentHealth() << "/" << Hero1.GetMaxHealth() << " health" << endl;
			menuList();
		}
		break;
	case '2':
		Hero1.SetCurrentHealth(Hero1.GetMaxHealth());
		cout << "Your hero has " << Hero1.GetCurrentHealth() << "/" << Hero1.GetMaxHealth() << " health" << endl;
		menuList();
	case '3':
		menuList();
	default:
		menuList();
		
	}
}
void menuList()
{
	char menuChoice;
	cout << "\nSelect an action from the following menu" << endl << endl;
	cout << "Your Hero currently has " << Hero1.GetGold() << " gold and " << Hero1.GetExp() << " EXP";
	cout << " and " << Hero1.GetCurrentHealth() << "/" << Hero1.GetMaxHealth() << " Health" << endl;
	cout << "1.Fight a random enemy \n2.Visit the item shop" << endl;
	cin >> menuChoice;
	
	switch (menuChoice) {
	case '1':
		fightPicker();
		break;
	case '2':
		itemShop();
	default:
		menuList();
	}

}