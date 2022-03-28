#include <iostream>

using namespace std;

void SetGraph(int x, int y, int value);
int GetGraph(int x, int y);
void DefaultGraph();

void BruteForce();

int _graph[64];
int _products[5] = { 20, 40, 70, 10, 30 };

int main()
{
	for (int i = 0; i < 64; i++)
		_graph[i] = -1;

	DefaultGraph();

	//cout << "" << i << endl;
}

void BruteForce()
{
	int w1, w2, w3, w4;
	
	cout << "Enter the first waypoint" << endl;
	cin >> w1;
	cout << "Enter the second waypoint" << endl;
	cin >> w2;
	cout << "Enter the third waypoint" << endl;
	cin >> w3;
	cout << "Enter the fourth waypoint" << endl;
	cin >> w4;



}

void DefaultGraph()
{
	SetGraph(1, 2, 12);
	SetGraph(1, 3, 45);
	SetGraph(1, 4, 78);
	SetGraph(1, 5, 23);
	SetGraph(1, 6, 56);
	SetGraph(1, 7, 78);
	SetGraph(1, 8, 123);

	SetGraph(2, 3, 34);
	SetGraph(2, 4, 10);
	SetGraph(2, 5, 89);
	SetGraph(2, 6, 25);
	SetGraph(2, 7, 15);
	SetGraph(2, 8, 70);

	SetGraph(3, 4, 67);
	SetGraph(3, 5, 45);
	SetGraph(3, 6, 45);
	SetGraph(3, 7, 43);
	SetGraph(3, 8, 65);

	SetGraph(4, 5, 124);
	SetGraph(4, 6, 56);
	SetGraph(4, 7, 76);
	SetGraph(4, 8, 35);

	SetGraph(5, 6, 33);
	SetGraph(5, 7, 55);
	SetGraph(5, 8, 80);

	SetGraph(6, 7, 9);
	SetGraph(6, 8, 90);

	SetGraph(7, 8, 100);
}

void SetGraph(int x, int y, int value)
{
	_graph[(x - 1) + ((y - 1) * 8)] = value;
	// Graph is bidirectional, so set the same value for the swapped co-ordinates
	_graph[(y - 1) + ((x - 1) * 8)] = value;
}

int GetGraph(int x, int y)
{
	return _graph[(x - 1) + ((y - 1) * 8)];
}