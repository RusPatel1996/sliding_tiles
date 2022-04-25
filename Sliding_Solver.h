#pragma once

#include <queue>
#include <set>
#include "Board_Tile.h"

typedef pair<int, Board_Tile*> pib; // int represents heuristic distance

class Sliding_Solver {
private:
	priority_queue<pib, vector<pib>, greater<pib> > tile_queue; // min-heap
	Board_Tile* starting_board;
	Board_Tile* final_board;
	// convert the final board into a map so we can easily 
	// lookup the location of the final positions
	unordered_map<int, pair<int, int> > goal_state_map;
	set<vector<int> > visited; // visited set stores the positions of the tile_board

public:
	Sliding_Solver(const string& start_state, string& goal_state);
	pair<int, string> solve_puzzle();
	int get_heuristic_distance(Board_Tile* board);
};