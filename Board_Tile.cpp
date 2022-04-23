#include "Board_Tile.h"


// Board_Tile Constructor used for creating a object state from a string, typically used to initialize the start state and goal state
// @params: String representing a state
Board_Tile::Board_Tile(const string& state) {
	vector<int> row;

	// convert state string to the 2D int tile board
	for (int i = 0; i < 9; ++i) {
		int num = state[i] - '0';

		row.push_back(num);

		if (row.size() == 3) {
			this->tile_board.push_back(row);
			row.clear();
		}

		if (num == 0) {
			this->blank_pos = make_pair(floor(i / 3), i % 3);
		}
	}

	this->moves_from_start = "";
	this->num_moves = 0;
}


// Board_Tile Constructor for creating subsequent objects with initialized data members.
// @params 2D Vector Board, String indicating direction moved, Int indicating total moves leading up to the current state, pair of ints indicating the new blank space position
Board_Tile::Board_Tile(const vector<vector<int>>& board, const string& direction_moved, const int total_moves, const pair<int, int>& blank_pos)
{
	this->tile_board = board;
	this->moves_from_start = direction_moved;
	this->num_moves = total_moves;
	this->blank_pos = blank_pos;
}


// Equality operator overload to check if two Board_Tile objects are the same
// 
// ** Currently not being used
// 
// @params two Board_Tile objects
// @return bool indicating if they are same or not
bool operator==(const Board_Tile& board1, const Board_Tile& board2) {
	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 3; ++col) {
			if (board1.tile_board[row][col] != board2.tile_board[row][col]) {
				return false;
			}
		}
	}

	return true;
}

// Output stream operator overload to pretty-print a tile board with relevant information
// 
// ** Currently not being used
// 
// @params output stream function which can print to screen and a Board_Tile object
ostream& operator<<(ostream& out, const Board_Tile& board) {
	out << "Current board:" << endl;
	out << "-------------" << endl;
	for (auto& row : board.tile_board) {
		out << "| ";
		for (auto& val : row) {
			out << val << " | ";
		}
		out << endl;
		out << "-------------" << endl;
	}
	out << endl;
	out << "Number of moves: " << board.num_moves << endl;
	out << "Moves from start: " << board.moves_from_start << endl;
	out << "Blank position at x: " << board.blank_pos.first << ", y: " << board.blank_pos.second << endl;
	out << endl;
	return out;
}


// Gets a vector of Board_Tile objects with the blank tile swapped with it's
// neighbor elements and data members updated
// 
// @return Vector of Board_Tile object pointers
vector<Board_Tile*> Board_Tile::get_next_states() {
	vector<tuple<int, int, char>> directions = {
		make_tuple(-1,0,'U'),
		make_tuple(0, 1,'R'),
		make_tuple(1, 0,'D'),
		make_tuple(0,-1,'L')
	};
	vector<Board_Tile*> next_states;
	int dir_row; int dir_col; char dir;
	int blank_row; int blank_col;

	tie(blank_row, blank_col) = this->blank_pos;

	for (auto& direction : directions) {
		tie(dir_row, dir_col, dir) = direction;
		dir_row += blank_row;
		dir_col += blank_col;

		if (check_within_bounds(dir_row, dir_col)) {
			vector<vector<int>> new_board = this->tile_board;

			// swap tiles
			swap(new_board[dir_row][dir_col], new_board[blank_row][blank_col]);

			string updated_moves = this->moves_from_start + dir;
			int moves = this->num_moves + 1;
			pair<int, int> new_pos = make_pair(dir_row, dir_col);

			// create and append new object with updated values
			next_states.push_back(
				new Board_Tile(new_board, updated_moves, moves, new_pos)
			);
		}
	}

	return next_states;
}

// function to check if the next direction's row and column indexes are valid
// 
// @param row index and column index
// @return bool indicating if valid or not
bool Board_Tile::check_within_bounds(int row, int col) {
	return row >= 0 && row < 3 && col >= 0 && col < 3;
}


// Manhattan distance is calculated by comparing the position each elment of the current state against 
// position retrieved from the goal state map using the element as key
// 
// @params a unordered map, mapping int elements in the goal state to their final positions
// @return total manhattan distance calculated from adding thn manhattan distance of each element
int Board_Tile::get_manhattan_distance(const unordered_map<int, pair<int, int>>& goal_state) {
	int manhattan_distance = 0;

	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 3; ++col) {
			int key = this->tile_board[row][col];
			pair<int, int> pos = goal_state.at(key);
			manhattan_distance += abs(row - pos.first) + abs(col - pos.second);
		}
	}

	return manhattan_distance;
}


/*** Getter methods ***/

int Board_Tile::get_num_moves() {
	return this->num_moves;
}

pair<int, int> Board_Tile::get_blank_position() {
	return this->blank_pos;
}

string Board_Tile::get_moves_from_start() {
	return this->moves_from_start;
}

vector<vector<int>> Board_Tile::get_tile_board() {
	return this->tile_board;
}
