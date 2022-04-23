#include "Board_Tile.h"



Board_Tile::Board_Tile(const string& config) {
	vector<int> row;
	for (int i = 0; i < 9; ++i) {
		int num = config[i] - '0';

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


Board_Tile::Board_Tile(const vector<vector<int>>& board, const string& direction_moved, const int total_moves, const pair<int, int>& blank_pos)
{
	this->tile_board = board;
	this->moves_from_start = direction_moved;
	this->num_moves = total_moves;
	this->blank_pos = blank_pos;
}


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


vector<Board_Tile*> Board_Tile::get_next_configs() {
	vector<tuple<int, int, char>> directions = { // top, right, down, left
		make_tuple(-1,0,'U'),
		make_tuple(0, 1,'R'),
		make_tuple(1, 0,'D'),
		make_tuple(0,-1,'L')
	};
	vector<Board_Tile*> next_configs;
	int dir_row; int dir_col; char dir;
	int blank_row; int blank_col;

	tie(blank_row, blank_col) = this->blank_pos;

	for (auto& direction: directions) {
		tie(dir_row, dir_col, dir) = direction;
		dir_row += blank_row;
		dir_col += blank_col;

		if (this->check_within_bounds(dir_row, dir_col)) {
			vector<vector<int>> new_board;

			for (auto& row : this->tile_board) {
				vector<int> r;
				for (auto& val : row) {
					r.push_back(val);
				}
				new_board.push_back(r);
			}
			swap(new_board[dir_row][dir_col], new_board[blank_row][blank_col]);

			string updated_moves = this->moves_from_start + dir;
			int moves = this->num_moves + 1;
			pair<int, int> new_pos = make_pair(dir_row, dir_col);

			next_configs.push_back(
				new Board_Tile(new_board, updated_moves, moves, new_pos)
			);
		}
	}

	return next_configs;
}


int Board_Tile::get_manhattan_distance(const unordered_map<int, pair<int, int>>& goal_config) {
	int manhattan_distance = 0;

	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 3; ++col) {
			int key = this->tile_board[row][col];
			pair<int, int> pos = goal_config.at(key);
			manhattan_distance += abs(row - pos.first) + abs(col - pos.second);
		}
	}

	return manhattan_distance;
}


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

bool Board_Tile::check_within_bounds(int row, int col) {
	return row >= 0 && row < 3 && col >= 0 && col < 3;
}