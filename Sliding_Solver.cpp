#include "Sliding_Solver.h"


Sliding_Solver::Sliding_Solver(const string& start_state, string& goal_state) {
	this->starting_board = new Board_Tile(start_state);
	this->final_board = new Board_Tile(goal_state);

	for (int i = 0; i < 9; ++i) {
		pair<int, int> pos = make_pair(floor(i / 3), i % 3);
		this->goal_state_map[goal_state[i] - '0'] = pos;
	}
}

pair<int, string> Sliding_Solver::solve_puzzle()
{
	// unchanging data members can be stated as variables to reduce function call overhead
	Board_Tile* start_state = this->starting_board;
	set<vector<int> > goal_state = { this->final_board->get_board() };

	this->tile_queue.push(
		make_pair(get_heuristic_distance(start_state), start_state)
	);
	this->visited.insert(starting_board->get_board());

	// edge case: check for start case being the goal state
	if (goal_state.count(start_state->get_board())) {
		cout << "Number of A* operations: " << 0 << endl;
		return make_pair(starting_board->get_num_moves(), starting_board->get_moves_from_start());
	}

	// cout << *start_state << endl; // uncomment to peek under the hood

	int number_of_ops = 0; // counts the number of times the loop is executed
	while (!this->tile_queue.empty()) {
		number_of_ops++;

		pair<int, Board_Tile*> min_board = this->tile_queue.top();
		Board_Tile* board = min_board.second;
		this->tile_queue.pop();

		for (Board_Tile* next_board : board->get_next_states()) {
			vector<int> key = next_board->get_board();
			if (!visited.count(key)) {
				// cout << *next_board << endl; // uncomment to peek under the hood
				if (goal_state.count(key)) {
					cout << "Number of A* executions: " << number_of_ops << endl;
					return make_pair(next_board->get_num_moves(), next_board->get_moves_from_start());
				}
				int heuristic_distance = get_heuristic_distance(next_board);
				this->tile_queue.push(make_pair(heuristic_distance, next_board));
				this->visited.insert(key);
			}
		}
	}

	return make_pair(-1, "");
}


int Sliding_Solver::get_heuristic_distance(Board_Tile* board) {
	return board->get_num_moves() + board->get_manhattan_distance(this->goal_state_map);
}
