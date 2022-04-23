#include "Sliding_Solver.h"
#include <chrono>

using namespace std::chrono;


int main()
{
	string start = "436871052";
	string goal = "123456780";

	Sliding_Solver* solver = new Sliding_Solver(start, goal);
	Board_Tile* board = new Board_Tile(start);

	time_point<high_resolution_clock> start_point, end_point;
	// Time Start
	start_point = high_resolution_clock::now();

	pair<int, string> result = solver->solve_puzzle();

	// Time Stop
	end_point = high_resolution_clock::now();
	auto diff = time_point_cast<nanoseconds>(end_point).time_since_epoch().count() - time_point_cast<nanoseconds>(start_point).time_since_epoch().count();

	cout << "Number of Moves: " << result.first << endl;
	cout << "Moves: " << result.second << endl;
	cout << "Time taken = " << diff << " nanoseconds" << endl;

	return 0;
}