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
	int num_moves;
	int blank_pos;
	int manhattan_distance;
	string moves_from_start;
	vector<int> tile_board;

public:
	Board_Tile(const string& state);
	Board_Tile(const vector<int>& board, const string& direction_moved, const int total_moves, const int blank_pos);
	friend bool operator==(const Board_Tile& board1, const Board_Tile& board2);
	friend ostream& operator<<(ostream& os, const Board_Tile& board);
	vector<Board_Tile*> get_next_states(const unordered_map<int, pair<int, int> >& goal_state_map);
	bool check_within_bounds(const int i, const char dir);
	void set_manhattan_distance(const unordered_map<int, pair<int, int> >& goal_state_map);
	int get_num_moves();
	int get_manhattan_distance();
	string get_moves_from_start();
	vector<int> get_board();
};