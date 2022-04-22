#include "Board_Tile.h"

#include <tuple>
Board_Tile::Board_Tile(const string& config) {
	for (int i = 0; i < 9; ++i) {
		int row = floor(i / 3);
		int col = i % 3;
		this->tile_board[row][col] = (int)config[i];
	}
}

Board_Tile::Board_Tile(vector<vector<int>> board, string moves, int total_moves)
{
	this->tile_board = board;
	this->moves_from_start = moves;
	this->num_moves = total_moves;
}

bool Board_Tile::operator==(const Board_Tile& board2) {

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
	for (auto& direction: directions) {
		tie(dir_row, dir_col, dir) = direction;
		if (this->check_within_bounds(dir_row, dir_col) == true) {
			vector<vector<int>> new_board = this->tile_board;
			int blank_row, int blank_col;

			tie(blank_row, blank_col) = this->blank_pos;
			swap(new_board[dir_row][dir_col], new_board[blank_row][blank_col]);

			next_configs.push_back(new Board_Tile(new_board, this->moves_from_start + dir, this->num_moves + 1));
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
			manhattan_distance += abs(pos.first - row) + abs(pos.second - col);

			/* Since this function will be called before we find next configs of a state so we can rest assured that
			each state will have a blank_pos value */
			if (key == 0) {
				this->blank_pos = make_pair(row, col);
			}
		}
	}

	return manhattan_distance;
}


int Board_Tile::get_num_moves() {
	return this->num_moves;
}


bool Board_Tile::check_within_bounds(int row, int col) {
	return row >= 0 && row < 3 && col >= 0 && col < 3;
}