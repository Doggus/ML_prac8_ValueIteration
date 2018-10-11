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
		float value;
		bool isTerminal;
		std::vector<std::pair<int,int>> adjacentStates;

		state() {}

		state(std::string n, std::pair<int,int> p)
		{
			name = n;
			position = p;
		}

		state(std::string n, std::pair<int,int> p, float v, bool t)
		{
			name = n;
			position = p;
			value = v;
			isTerminal = t;
		}

		std::string toString() 
		{ 
			return name + ": " + std::to_string((int)value);
		}
	};

	std::vector<state> gridStates;
	std::vector<std::string> gridActions; 
	float discount;
	int gridX, gridY;
	std::map<std::pair<int,int>, state> gridMap;
	std::vector<state> visitedStates;

	grid(std::vector<state> gS, float d , int x, int y)
	{
		gridStates = gS;
		gridActions = {"up","down","left","right"};
		discount = d;
		gridX = x;
		gridY = y;

		for (int i = 0; i < gS.size(); ++i)
		{
			gridMap.insert(std::make_pair(gS[i].position, gS[i]));
		}
	}

	state stateTransition(const state &currentState, const std::string &action)
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
			std::cout << "Error, non-existent action" << std::endl;
			return state("Error State", std::make_pair(-1,-1));
		}
	}

	float rewardFunction(const state &currentState, const state &goalState)
	{
		//return reward
		if (goalState.name != "s3")
		{
			return goalState.value;
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
				//this will never be called due to layout of given grid
				return 0;
			}
		}
	}

	void stateLearn(state &currentState, const float &dis)
	{
		//if we are currently in terminal state then skip
		if (currentState.isTerminal) {return;}

		//state learns new reward to find optimal path  
		for (int i = 0; i < currentState.adjacentStates.size(); ++i)
		{
			float tReward = rewardFunction(currentState, gridMap[currentState.adjacentStates[i]]) * dis;
			//std::cout << tReward << std::endl;
			currentState.value = std::max(currentState.value, tReward);
		}

		std::cout << currentState.name << ": " << currentState.value << std::endl;
	}

	float gridLearn()
	{
		//vi equals the number of value iterations you want to preform (e.g. 4)
		for (int vi = 0; vi < 4; ++vi)
		{
			std::cout << "\n";
			std::cout << "Value Iteration: " << vi << std::endl;
			//looping y
			for (int y = 0; y < gridY; ++y)
			{
				//looping x
				for (int x = 0; x < gridX; ++x)
				{
					//first iteration assigns initial given reward values to any states (so musnt use discount)
					if (vi == 0)
					{
						stateLearn(gridMap[std::make_pair(x,y)], 1);
					}
					else //next iterations will propogate reward values across all states
					{
						stateLearn(gridMap[std::make_pair(x,y)], discount);
					}
					
				}

				
			}

		}
	}
};

