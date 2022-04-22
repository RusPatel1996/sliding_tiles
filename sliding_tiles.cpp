// sliding_tiles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Sliding_Solver.h"


int main()
{
	string start = "123745086";
	string goal = "123456780";

	Sliding_Solver solver(start, goal);
	unordered_map<int, pair<int, int>> m = solver.get_map();
	for (auto& i : m)
	{
		cout << i.first << ": " << i.second.first << " " << i.second.second << endl;
	}
	Board_Tile board(start);

	cout << board << endl;
	cout << board << endl;
	cout << board.get_manhattan_distance(m) << endl;

	vector<Board_Tile*> v = board.get_next_configs();
	for (auto& i : v) {
		cout << *i;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
