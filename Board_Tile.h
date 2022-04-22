#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <tuple>

using namespace std;


class Board_Tile {
private:
	vector<vector<int>> tile_board;
	int num_moves;
	string moves_from_start;
	pair<int, int> blank_pos;

public:
	Board_Tile(const string& config);
	Board_Tile(vector<vector<int>> board, string direction_moved, int total_moves, pair<int, int> blank_pos);
	bool operator==(const Board_Tile& board2);
	// bool operator<(const Board_Tile& board2);
	friend ostream& operator<<(ostream& os, const Board_Tile& board);
	vector<Board_Tile*> get_next_configs();
	int get_manhattan_distance(const unordered_map<int, pair<int, int>>& goal_config);
	int get_num_moves();
	bool check_within_bounds(int row, int col);
};