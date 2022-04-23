#include "Sliding_Solver.h"


Sliding_Solver::Sliding_Solver(const string& start_config, string& goal_config) {
	this->starting_board = new Board_Tile(start_config);
	this->final_board = new Board_Tile(goal_config);

	for (int i = 0; i < 9; ++i) {
		int row = floor(i / 3);
		int col = i % 3;
		pair<int, int> pos = make_pair(row, col);
		this->goal_config_map[goal_config[i] - '0'] = pos;
	}
}

pair<int, string> Sliding_Solver::solve_puzzle()
{
	this->tile_queue.push(
		make_pair(this->calculate_heuristic_value(this->starting_board), this->starting_board)
	);

	while (!this->tile_queue.empty()) {
		pair<int, Board_Tile*> min_board = this->tile_queue.top();
		Board_Tile* board = min_board.second;
		cout << *board;
		this->tile_queue.pop();


		if (min_board.second == this->final_board) {
			return make_pair(board->get_num_moves(), board->get_moves_from_start());
		}

		for (Board_Tile& next_board : board->get_next_configs()) {
			Board_Tile* next = &next_board;
			cout << *next;
			int heuristic_distance = this->calculate_heuristic_value(next);
			this->tile_queue.push(make_pair(heuristic_distance, next));
		}
	}

	return make_pair(-1, "");
}


int Sliding_Solver::calculate_heuristic_value(Board_Tile* board) {
	return board->get_num_moves() + board->get_manhattan_distance(this->goal_config_map);
}