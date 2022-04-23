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
	cout << this->calculate_heuristic_value(this->starting_board) << endl;
	this->visited.insert(this->board_to_vector(starting_board));

	while (!this->tile_queue.empty()) {
		pair<int, Board_Tile*> min_board = this->tile_queue.top();
		Board_Tile* board = min_board.second;
		cout << *board;
		this->tile_queue.pop();


		if (*board == *final_board) {
			return make_pair(board->get_num_moves(), board->get_moves_from_start());
		}

		for (auto* next_board : board->get_next_configs()) {
			vector<int> key = this->board_to_vector(next_board);
			if (!visited.count(key)) {
				int heuristic_distance = this->calculate_heuristic_value(next_board);
				cout << heuristic_distance << endl;
				this->tile_queue.push(make_pair(heuristic_distance, next_board));
				this->visited.insert(key);
			}			
		}
	}

	return make_pair(-1, "");
}


int Sliding_Solver::calculate_heuristic_value(Board_Tile* board) {
	return board->get_num_moves() + board->get_manhattan_distance(this->goal_config_map);
}

// store the states in a set. convert the state into a tuple of 9 values.
vector<int> Sliding_Solver::board_to_vector(Board_Tile* board) {
	vector<vector<int>> b = board->get_tile_board();
	vector<int> board_vector = {
		b[0][0], b[0][1], b[0][2],
		b[1][0], b[1][1], b[1][2],
		b[2][0], b[2][1], b[2][2],
	};
	return board_vector;
}