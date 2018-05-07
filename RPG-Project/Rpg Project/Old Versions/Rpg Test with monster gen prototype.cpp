#include <iostream>
#include <ctime>
#include <cstdlib>
#include <array>
#include <string>

using namespace std;
bool hitChanceRoll(int hitChance);
int deathScreen();
int numberOfFights = 1;
void monsterCreation(); 
void fightPicker();
void menuList();


class Character 
{
 public: int health, attack, hitChance;
		 double defense;
		 string name;
		 Character::Character()
		 {

		 }
		 Character::Character(string n, int h, int a, int hC, double d)
		{
			 name = n;
			health = h;
			attack = a;
			hitChance = hC;
			defense = d;
		}
		 void SetName(string newName)
		 {
			 name = newName;
		 }
		 string GetName()
		 {
			 return name;
		 }
		void SetHealth(int newHealth)
		 {
			 health = newHealth;
		 }

		 int GetHealth()
		 {
			 return health;
		 }
		 int GetAttack()
		 {
			 return attack;
		 }
		 double GetDefense()
		 {
			 return defense;
		 }
		 int GetHitChance()
		 {
			 return hitChance;
		 }
		 
};
Character Hero1("Hero",10, 4, 80, .5);
std::array<Character, 30> Skeleton;
std::array<Character, 30> Slime;
std::array<Character, 30> Zombie;
std::array<Character, 30> Imp;
int main()
{
	srand(time(NULL));
	monsterCreation();
	do 
	{
		menuList();

	} while (Hero1.GetHealth() > 0);

}

void fight(int heroHealth, int heroAttack, int heroHitChance, double heroDefense,
	string monsterName, int monsterHealth, int monsterAttack, int monsterHitChance, double monsterDefense)
{
	cout << "Hero Health is: " << heroHealth << " Attack is: " << heroAttack << endl;
	cout << "Hit Chance is: " << heroHitChance << " Defense is: " << heroDefense * 100 << "%" << endl;
	cout << monsterName << numberOfFights << " Health is: " << monsterHealth << " Attack is: " << monsterAttack << endl;
	cout << "Hit Chance is: " << monsterHitChance << " Defense is: " << monsterDefense * 100 << "%" << endl << endl;
	
	int round = 1;
	do
	{
		
		cout << "\nFight " << numberOfFights << " Round " << round << endl;
		bool heroHit = hitChanceRoll(heroHitChance);
		if (heroHit == true)
		{
			monsterHealth = monsterHealth - heroAttack* (1 - monsterDefense);
			cout << "Hero hit for " << heroAttack* (1 - monsterDefense);
			cout << " the " << monsterName << "'s armor absorbed " << heroAttack*monsterDefense << " point(s) of damage" << endl;
		}
		else if (heroHit == false)
		{
			cout << "The hero misses!" << endl;
		}
		bool monsterHit = hitChanceRoll(monsterHitChance);
		if(monsterHit == true)
		{
			if (monsterAttack % 2 == 0)
			{
				heroHealth = heroHealth - monsterAttack * (1 - heroDefense);
				cout << monsterName << " hit for " << monsterAttack* (1 - heroDefense);
				cout << " the hero's armor absorbed " << monsterAttack*heroDefense << " point(s) of damage" << endl;
			}
			else if (monsterAttack % 2 == 1)
			{
				int truncMonsterAttack = monsterAttack * (1 - heroDefense);
				heroHealth = heroHealth - truncMonsterAttack;
				cout << monsterName << " hit for " << truncMonsterAttack;
				cout << " the hero's armor absorbed " << monsterAttack-truncMonsterAttack << " point(s) of damage" << endl;
			}
		}
		else if (monsterHit == false)
		{
			cout << "The " << monsterName << " misses!" << endl;
		}
		
		
		Hero1.SetHealth(heroHealth);
		if (heroHealth > 0)
		{
			cout << "Hero Health: " << heroHealth << endl;
		}
		else if (heroHealth <= 0)
		{
			deathScreen();
		}

		if (monsterHealth > 0)
		{
			cout <<  monsterName << " Health: " << monsterHealth << endl;
		}
		else if (monsterHealth <= 0)
		{
			cout  << monsterName << " Health: 0" << endl;
		}
		cout << endl;
		round++;
	} while (heroHealth > 0 && monsterHealth > 0);
	numberOfFights++;
}

bool hitChanceRoll(int hitChance)
{
	int hitRoll = rand() % 100 + 0;
	if (hitRoll < hitChance)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int deathScreen()
{
	cout << "\n\t\tYour hero has died!" << endl;
	cout << "\t\tThey defeated " << numberOfFights << " monster(s)";
	exit(0);
}
void monsterCreation()
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
}
void fightPicker()
{
	int fightDeterminant = rand() % 4 + 1;

	if (fightDeterminant == 1)
	{
		fight(Hero1.GetHealth(), Hero1.GetAttack(), Hero1.GetHitChance(), Hero1.GetDefense(),
			Skeleton[numberOfFights].GetName(),Skeleton[numberOfFights].GetHealth(), Skeleton[numberOfFights].GetAttack(), Skeleton[numberOfFights].GetHitChance(),
			Skeleton[numberOfFights].GetDefense());
	}
	else if (fightDeterminant == 2)
	{
		fight(Hero1.GetHealth(), Hero1.GetAttack(), Hero1.GetHitChance(), Hero1.GetDefense(),
			Slime[numberOfFights].GetName(), Slime[numberOfFights].GetHealth(), Slime[numberOfFights].GetAttack(), Slime[numberOfFights].GetHitChance(),
			Slime[numberOfFights].GetDefense());
	}
	else if (fightDeterminant == 3)
	{
		fight(Hero1.GetHealth(), Hero1.GetAttack(), Hero1.GetHitChance(), Hero1.GetDefense(),
			Zombie[numberOfFights].GetName(), Zombie[numberOfFights].GetHealth(), Zombie[numberOfFights].GetAttack(), Zombie[numberOfFights].GetHitChance(),
			Zombie[numberOfFights].GetDefense());
	}
	else if (fightDeterminant == 4)
	{
		fight(Hero1.GetHealth(), Hero1.GetAttack(), Hero1.GetHitChance(), Hero1.GetDefense(),
			Zombie[numberOfFights].GetName(), Imp[numberOfFights].GetHealth(), Imp[numberOfFights].GetAttack(), Imp[numberOfFights].GetHitChance(),
			Imp[numberOfFights].GetDefense());
	}
}
void itemShop()
{
	int maxHealthDifference;
	char menuChoice;
	cout << "Your hero has " << Hero1.GetHealth() << " health" << endl;
	cout << "Welcome to the item shop please select from the following menu" << endl;
	cout << "1. Buy a health potion(+5hp) \n2. Refill missing health \n3. Exit the Item Shop" << endl;
	cin >> menuChoice;
	switch (menuChoice) {
	case '1':
		if (Hero1.GetHealth() + 5 > 10)
		{
			maxHealthDifference = 10 - Hero1.GetHealth();
			Hero1.SetHealth(Hero1.GetHealth() + maxHealthDifference);
			cout << "Your hero now has " << Hero1.GetHealth() << " health" << endl;
			menuList();
		}
		else
		{
			Hero1.SetHealth(Hero1.GetHealth() + 5);
			cout << "Your hero now has " << Hero1.GetHealth() << " health" << endl;
			menuList();
		}
		break;
	case '2':
		maxHealthDifference = 10 - Hero1.GetHealth();
		Hero1.SetHealth(Hero1.GetHealth() + maxHealthDifference);
		cout << "Your hero now has " << Hero1.GetHealth() << " health" << endl;
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
	cout << "Select from an action from the following menu" << endl;
	cout << "1.Fight a random enemy \n2.Visit the item shop" << endl;
	cin >> menuChoice;
	
	switch (menuChoice) {
	case '1':
		fightPicker();
		break;
	case '2':
		itemShop();
	default:
		cout << "\nPlease enter an option from the list";
		menuList();
	}

}