#pragma once

#include <queue>
#include <set>
#include "Board_Tile.h"

typedef pair<int, Board_Tile*> pib;

class Sliding_Solver {
private:
	priority_queue<pib, vector<pib>, greater<pib>> tile_queue;
	Board_Tile* starting_board;
	Board_Tile* final_board;
	unordered_map<int, pair<int, int>> goal_state_map;
	set<vector<int>> visited;

public:
	Sliding_Solver(const string& start_state, string& goal_state);
	pair<int, string> solve_puzzle();
	int get_heuristic_distance(Board_Tile* board);
};