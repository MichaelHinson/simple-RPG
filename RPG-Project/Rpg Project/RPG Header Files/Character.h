#pragma once
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Character //Base Object all entities are created from
{
public: int maxHealth, currentHealth, minDamage, maxDamage, hitChance, critChance, speed, maxMana, currentMana, gold, exp, level;
		double defense;
		string name;
		Character(string Name)
		{
			name = Name;
			maxHealth = 0;
			currentHealth = maxHealth;
			minDamage = 0;
			maxDamage = 0;
			hitChance = 0;
			critChance = 0;
			speed = 0;
			defense = 0;
			maxMana = 0;
			currentMana = maxMana;
			gold = 0;
			exp = 0;
			level = 1;
		}
		Character(string Name, int Health, int MinDamage, int MaxDamage, int HitChance, int CritChance, int Speed, double Defense,
			int Mana, int Gold, int Exp, int Level)//Could add constructor with 
		{
			name = Name;
			maxHealth = Health;
			currentHealth = maxHealth;
			minDamage = MinDamage;
			maxDamage = MaxDamage;
			hitChance = HitChance;
			critChance = CritChance;
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
		int GetCritChance()
		{
			return critChance;
		}
		void SetCritChance(int newCritChance)
		{
			critChance = newCritChance;
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