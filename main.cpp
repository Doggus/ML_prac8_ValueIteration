#include "grid.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

typedef grid::state state;

int main(int argc, char const *argv[])
{
 	cout << "Value Iteration: " << endl;
 	cout << "\n";

 	//All states in the given grid
 	std::vector<state> states;
 	states.push_back(state("s1",make_pair(0,1), 0.0f, false));
 	states.push_back(state("s2",make_pair(1,1), 0.0f, false));
 	states.push_back(state("s3",make_pair(2,1), 0.0f, true));
 	states.push_back(state("s4",make_pair(0,0), 0.0f, false));
 	states.push_back(state("s5",make_pair(1,0), 0.0f, false));
 	states.push_back(state("s6",make_pair(2,0), 0.0f, false));

 	//create grid (3 x 2) from states with a discount value of 0.8
 	grid stateGrid(states, 0.8f, 3, 2);


 	//Adding the adjacent states for every state in the grid
 	for (int x = 0; x < stateGrid.gridX; ++x)
 	{
 		for (int y = 0; y < stateGrid.gridY; ++y)
 		{
 			//if there is an existing state left, right, downwards or upwards of current state then add it is adjacent to that state
 			std::vector<pair<int,int>> neighborStates;

 			//left
 			if (stateGrid.gridMap[make_pair(x - 1, y)].name != "")
 			{
 				neighborStates.push_back(make_pair(x - 1, y));
 			}
 			//right
 			if (stateGrid.gridMap[make_pair(x + 1, y)].name != "")
 			{
 				neighborStates.push_back(make_pair(x - 1, y));
 			}
 			//down
 			if (stateGrid.gridMap[make_pair(x, y - 1)].name != "")
 			{
 				neighborStates.push_back(make_pair(x, y - 1));
 			}
 			//up
 			if (stateGrid.gridMap[make_pair(x, y + 1)].name != "")
 			{
 				neighborStates.push_back(make_pair(x, y + 1));
 			}

 			stateGrid.gridMap[make_pair(x, y)].adjacentStates = neighborStates;
 		}
 	}

 	// Now that we have a populated grid and every state knows their neighbors
 	// we can use Value iteration to find the optimal path to the terminal node
 	// with the best reward.

 	// for (int i = 0; i < stateGrid.gridStates[0].adjacentStates.size(); ++i)
 	// {
 	// 	cout << stateGrid.gridMap[stateGrid.gridStates[0].adjacentStates[i]].name << endl;
 	// }
 	//pair<int,int> p = stateGrid.gridStates[0].adjacentStates[0];
 	//cout << stateGrid.gridMap[p].name << endl;
 	
 	stateGrid.gridLearn();

 	return 0;

}