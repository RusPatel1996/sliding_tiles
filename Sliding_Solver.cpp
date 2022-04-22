#include "Sliding_Solver.h"


Sliding_Solver::Sliding_Solver(const string& start_config, string& goal_config) {
	this->starting_board = new Board_Tile(start_config);

	for (int i = 0; i < 9; ++i) {
		int row = floor(i / 3);
		int col = i % 3;
		pair<int, int> pos = make_pair(row, col);
		this->goal_config_map[goal_config[i] - '0'] = pos;
	}
}


//pair<int, string> Sliding_Solver::solve_puzzle() {
//
//}


int Sliding_Solver::calculate_heuristic_value(Board_Tile* board) {
	return board->get_num_moves() + board->get_manhattan_distance(this->goal_config_map);
}

unordered_map<int, pair<int, int>> Sliding_Solver::get_map() {
	return this->goal_config_map;
}