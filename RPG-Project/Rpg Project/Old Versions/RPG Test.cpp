#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void fight(int heroHealth, int heroAttack, int heroHitChance, double heroDefense,
	int monsterHealth, int monsterAttack, int monsterHitChance, double monsterDefense);
bool hitChanceRoll(int hitChance);
int deathScreen();
int numberOfFights = 1;

/*class Hero 

{
public: int health = 10, hitChance = 80, attack = 4;
		double defense = .5;
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
		

}; */
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
Character Monster1(8, 6, 60, .25);
Character Monster2(4, 2, 40, 0);
Character Monster3(4, 2, 40, 0);
Character Monster4(4, 2, 40, 0);
int main()
{
	srand(time(NULL));
	fight(Hero1.GetHealth(), Hero1.GetAttack(),Hero1.GetHitChance(), Hero1.GetDefense(),
		Monster1.GetHealth(), Monster1.GetAttack(),Monster1.GetHitChance(), Monster1.GetDefense());
	fight(Hero1.GetHealth(), Hero1.GetAttack(), Hero1.GetHitChance(), Hero1.GetDefense(),
		Monster2.GetHealth(), Monster2.GetAttack(), Monster2.GetHitChance(), Monster2.GetDefense());
	fight(Hero1.GetHealth(), Hero1.GetAttack(), Hero1.GetHitChance(), Hero1.GetDefense(),
		Monster3.GetHealth(), Monster3.GetAttack(), Monster3.GetHitChance(), Monster3.GetDefense());
	fight(Hero1.GetHealth(), Hero1.GetAttack(), Hero1.GetHitChance(), Hero1.GetDefense(),
		Monster4.GetHealth(), Monster4.GetAttack(), Monster4.GetHitChance(), Monster4.GetDefense());
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
		cout << "\nRound " << round << endl;
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
			heroHealth = heroHealth - monsterAttack * (1 - heroDefense);
			cout << "Monster hit for " << monsterAttack* (1 - heroDefense);
			cout << " the hero's armor absorbed " << monsterAttack*heroDefense << " point(s) of damage" << endl;
		}
		else if (monsterHit == false)
		{
			cout << "The monster misses!" << endl;
		}
		
		
		Hero1.SetHealth(heroHealth);
		Monster1.SetHealth(monsterHealth);
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
			cout << "Monster Health: " << Monster1.GetHealth() << endl;
		}
		else if (monsterHealth <= 0)
		{
			cout << "Monster Health: 0" << endl;
		}
		cout << endl;
		round++;
		//cout << "Monster2 Health After Fight " << Monster2.GetHealth() << endl;
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
	return 1;
}