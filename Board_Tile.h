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
	Board_Tile(const vector<vector<int>>& board, const string& direction_moved, const int total_moves, const pair<int, int>& blank_pos);
	bool operator==(const Board_Tile& board2);
	friend ostream& operator<<(ostream& os, const Board_Tile& board);
	vector<Board_Tile> get_next_configs();
	bool check_within_bounds(int row, int col);
	int get_manhattan_distance(const unordered_map<int, pair<int, int>>& goal_config);
	int get_num_moves();
	string get_moves_from_start();
};