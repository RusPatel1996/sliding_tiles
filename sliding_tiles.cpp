// sliding_tiles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Sliding_Solver.h"


int main()
{
	string start = "123745086";
	string goal = "123456780";

	Sliding_Solver* solver = new Sliding_Solver(start, goal);
	Board_Tile* board = new Board_Tile(start);
	//cout << *board;
	//vector<Board_Tile> next = board->get_next_configs();
	//for (auto& n : next) {
	//	cout << n;
	//}
	solver->solve_puzzle();
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
