#include "Board_Tile.h"


// Board_Tile Constructor used for creating a object state from a string, typically used to initialize the start state and goal state
// @params: String representing a state
Board_Tile::Board_Tile(const string& state) {
	for (int i = 0; i < 9; ++i) {
		int num = state[i] - '0';

		this->tile_board.push_back(num);
		if (num == 0) {
			this->blank_pos = i;
		}
	}

	this->moves_from_start = "";
	this->num_moves = 0;
}


// Board_Tile Constructor for creating subsequent objects with initialized data members.
// @params 2D Vector Board, String indicating direction moved, Int indicating total moves leading up to the current state, pair of ints indicating the new blank space position
Board_Tile::Board_Tile(const vector<int>& board, const string& direction_moved, const int total_moves, const int blank_pos)
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
	for (int i = 0; i < 9; ++i) {
		if (board1.tile_board[i] != board2.tile_board[i]) {
			return false;
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
	int count = 0;
	for (int i = 0; i < 9; ++i) {
		out << "| ";
		out << board.tile_board[i] << " ";
		count++;
		if (count % 3 == 0) {
			out << "|";
			out << endl;
			out << "-------------" << endl;
		}
	}
	out << endl;
	out << "Number of moves: " << board.num_moves << endl;
	out << "Moves from start: " << board.moves_from_start << endl;
	out << "Blank position at x: " << floor(board.blank_pos / 3) << ", y: " << board.blank_pos % 3 << endl;
	out << endl;
	return out;
}


// Gets a vector of Board_Tile objects with the blank tile swapped with it's
// neighbor elements and data members updated
// 
// @return Vector of Board_Tile object pointers
vector<Board_Tile*> Board_Tile::get_next_states() {
	vector<pair<int, char> > directions = {
		make_pair(-3,'U'),
		make_pair( 3,'D'),
		make_pair( 1,'R'),
		make_pair(-1,'L')
	};
	vector<Board_Tile*> next_states;
	int blank_pos = this->blank_pos;

	for (pair<int, int> direction : directions) {
		int next_pos = blank_pos + direction.first;
		char dir = direction.second;

		if (check_within_bounds(next_pos, dir)) {
			vector<int> new_board = this->tile_board;

			// swap tiles
			swap(new_board[next_pos], new_board[blank_pos]);

			string updated_moves = this->moves_from_start + dir;
			int total_moves = this->num_moves + 1;

			// create and append new object with updated values
			next_states.push_back(
				new Board_Tile(new_board, updated_moves, total_moves, next_pos)
			);
		}
	}
	return next_states;
}

// function to check if the next direction's row and column indexes are valid
// 
// @param row index and column index
// @return bool indicating if valid or not
bool Board_Tile::check_within_bounds(int i, char dir) {
	switch (dir) {
	case 'U':
		return i >= 0;
	case 'D':
		return i < 9;
	case 'R':
		return (i % 3) != 0;
	case 'L':
		return (i % 3) != 2 && i >= 0;
		// reason for the extra i >= 0 condition is that C++ unlike Python 
		// uses different method of calculating modulus for negative numbers
		// so -1 % 2 == -1 in C++ and -1 % 2 == 2 in Python...
	}
}


// Manhattan distance is calculated by comparing the position each elment of the current state against 
// position retrieved from the goal state map using the element as key
// 
// @params a unordered map, mapping int elements in the goal state to their final positions
// @return total manhattan distance calculated from adding thn manhattan distance of each element
int Board_Tile::get_manhattan_distance(const unordered_map<int, pair<int, int> >& goal_state) {
	int manhattan_distance = 0;
	for (int i = 0; i < 9; ++i) {
		pair<int, int> pos = goal_state.at(this->tile_board[i]);
		manhattan_distance += abs(floor(i / 3) - pos.first) + abs((i % 3) - pos.second);
	}
	return manhattan_distance;
}


/*** Getter methods ***/

int Board_Tile::get_num_moves() {
	return this->num_moves;
}

string Board_Tile::get_moves_from_start() {
	return this->moves_from_start;
}

vector<int> Board_Tile::get_board() {
	return this->tile_board;
}