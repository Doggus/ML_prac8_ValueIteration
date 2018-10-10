#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

class grid
{

public:

	struct state
	{
		std::string name;
		std::pair<int,int> position;
		std::vector<state> adjacentStates;

		state() {}

		state(std::string n, std::pair<int,int> p)
		{
			name = n;
			position = p;
		}
	};

	std::vector<state> gridStates;
	std::vector<std::string> gridActions; 
	float discount;

	std::map<std::pair<int,int>, std::string> gridMap;
	std::vector<state> visitedStates;

	grid(std::vector<state> gS, float d)
	{
		gridStates = gS;
		gridActions = {"up","down","left","right"};
		discount = d;

		for (int i = 0; i < gS.size(); ++i)
		{
			gridMap.insert(std::make_pair(gS[i].position, gS[i].name));
			//gridMap[gS[i].position] = gS[i];
		}
	}

	std::string stateTransition(state currentState, std::string action)
	{
		//returns goal state given current state and action
		if (action == "up")
		{
			std::pair<int,int> p = std::make_pair(currentState.position.first, currentState.position.second+1);
			return gridMap[p];
		}
		else if (action == "down")
		{
			std::pair<int,int> p = std::make_pair(currentState.position.first, currentState.position.second-1);
			return gridMap[p];
		}
		else if (action == "left")
		{
			std::pair<int,int> p = std::make_pair(currentState.position.first-1, currentState.position.second);
			return gridMap[p];
		}
		else if (action == "right")
		{
			std::pair<int,int> p = std::make_pair(currentState.position.first+1, currentState.position.second);
			return gridMap[p];
		}
		else
		{
			return "Error, incorrect action";
		}
	}

	float rewardFunction(state currentState, state goalState)
	{
		//return reward
		if (goalState.name != "s3")
		{
			return 0;
		}
		else
		{
			if (currentState.name == "s2")
			{
				return 50;
			}
			else if(currentState.name == "s6")
			{
				return 100;
			}
			else
			{
				return 0;
			}
		}
	}
};

