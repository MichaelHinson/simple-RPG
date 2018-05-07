#include <iostream>
#include <ctime>
#include <cstdlib>
#include <array>

using namespace std;
void fight(int heroHealth, int heroAttack, int heroHitChance, double heroDefense,
	int monsterHealth, int monsterAttack, int monsterHitChance, double monsterDefense);
bool hitChanceRoll(int hitChance);
int deathScreen();
int numberOfFights = 1;
void monsterCreation();


class Character 
{
 public: int health, attack, hitChance;
		 double defense;
		 Character::Character()
		 {

		 }
		 Character::Character(int h, int a, int hC, double d)
		{
			health = h;
			attack = a;
			hitChance = hC;
			defense = d;
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
Character Hero1(10, 4, 80, .5);
std::array<Character, 20> Monster;
int main()
{
	srand(time(NULL));
	monsterCreation();
	do 
	{
		fight(Hero1.GetHealth(), Hero1.GetAttack(), Hero1.GetHitChance(), Hero1.GetDefense(),
			Monster[numberOfFights].GetHealth(), Monster[numberOfFights].GetAttack(), Monster[numberOfFights].GetHitChance(),
			Monster[numberOfFights].GetDefense());

	} while (Hero1.GetHealth() > 0);

}

void fight(int heroHealth, int heroAttack, int heroHitChance, double heroDefense,
	int monsterHealth, int monsterAttack, int monsterHitChance, double monsterDefense)
{
	cout << "Hero Health is " << heroHealth << endl;
	cout << "Hero Attack is " << heroAttack << endl;
	cout << "Monster" << numberOfFights << " Health is " << monsterHealth << endl;
	cout << "Monster" << numberOfFights << " Attack is " << monsterAttack << endl << endl;
	
	int round = 1;
	do
	{
		
		cout << "\nFight " << numberOfFights << " Round " << round << endl;
		bool heroHit = hitChanceRoll(heroHitChance);
		if (heroHit == true)
		{
			monsterHealth = monsterHealth - heroAttack* (1 - monsterDefense);
			cout << "Hero hit for " << heroAttack* (1 - monsterDefense);
			cout << " the monster's armor absorbed " << heroAttack*monsterDefense << " point(s) of damage" << endl;
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
				cout << "Monster hit for " << monsterAttack* (1 - heroDefense);
				cout << " the hero's armor absorbed " << monsterAttack*heroDefense << " point(s) of damage" << endl;
			}
			else if (monsterAttack % 2 == 1)
			{
				int truncMonsterAttack = monsterAttack * (1 - heroDefense);
				heroHealth = heroHealth - truncMonsterAttack;
				cout << "Monster hit for " << truncMonsterAttack;
				cout << " the hero's armor absorbed " << monsterAttack-truncMonsterAttack << " point(s) of damage" << endl;
			}
		}
		else if (monsterHit == false)
		{
			cout << "The monster misses!" << endl;
		}
		
		
		Hero1.SetHealth(heroHealth);
		Monster[numberOfFights].SetHealth(monsterHealth);
		if (heroHealth > 0)
		{
			cout << "Hero Health: " << Hero1.GetHealth() << endl;
		}
		else if (heroHealth <= 0)
		{
			deathScreen();
		}

		if (monsterHealth > 0)
		{
			cout << "Monster Health: " << Monster[numberOfFights].GetHealth() << endl;
		}
		else if (monsterHealth <= 0)
		{
			cout << "Monster Health: 0" << endl;
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
	for (int i = 1; i < 20; i++) {
		Monster[i] = Character(i,i,60,0);
	}
}