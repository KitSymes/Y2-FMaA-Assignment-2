#include <iostream>
#include <sstream>
#include <map>

using namespace std;

void BruteForce(string path, int cost, int weight, int currentWaypoint);

void SetGraph(int x, int y, int value);
int GetGraph(int x, int y);
void DefaultGraph();

// In Million KM
int _graph[5][5];
// In Tonnes
const int _loads[5] = { 20,40,70,10,30 };
// Fuel Cost Per Tonne Per Million KM
const int fuelCost = 25;
map<string, int> _bruteForce;

int main()
{
	DefaultGraph();

	cout << "Brute Forcing" << endl;
	BruteForce("", 0, 0, 0);
	cout << "Took " << _bruteForce.size() << " combinations" << endl;
	string shortestPath;
	int shortestCost = INT_MAX;
	for (pair<string, int> pair : _bruteForce)
	{
		if (pair.second >= shortestCost)
			continue;

		shortestPath = pair.first;
		shortestCost = pair.second;
	}
	cout << "Shortest Path is " << shortestPath << " which costs " << (fuelCost * shortestCost) << endl;
}

void BruteForce(string path, int cost, int weight, int currentWaypoint)
{
	for (int i = 0; i < 5; i++)
	{
		stringstream id;
		id << i;
		if (path.find(id.str()) != std::string::npos)
			continue;
		stringstream newPath;
		newPath << path << i;
		BruteForce(newPath.str(), cost + weight * GetGraph(currentWaypoint, i), weight + _loads[i], i);
	}
	if (path.length() >= 5)
	{
		_bruteForce[path] = cost;
		cout << path << " " << cost << endl;
	}
}

void DefaultGraph()
{
	SetGraph(0, 1, 10);
	SetGraph(0, 2, 15);
	SetGraph(0, 3, 12);
	SetGraph(0, 4, 20);;

	SetGraph(1, 2, 12);
	SetGraph(1, 3, 25);
	SetGraph(1, 4, 14);

	SetGraph(2, 3, 16);
	SetGraph(2, 4, 28);

	SetGraph(3, 4, 17);
}

void SetGraph(int x, int y, int value)
{
	_graph[x][y] = value;
	// Graph is bidirectional, so set the same value for the swapped co-ordinates
	_graph[y][x] = value;
}

int GetGraph(int x, int y)
{
	return _graph[x][y];
}