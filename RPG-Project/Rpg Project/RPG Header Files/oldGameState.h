#pragma once
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class GameState //Object to Store basic game state. Xp required to level up, current level, and number of fights.
{
public: int fightCount, xpReq, levelReq, heroCount;
		GameState::GameState(int fights, int reqXp, int reqLevel, int HeroCount)
		{
			fightCount = fights;
			xpReq = reqXp;
			levelReq = reqLevel;
			heroCount = HeroCount;
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
};