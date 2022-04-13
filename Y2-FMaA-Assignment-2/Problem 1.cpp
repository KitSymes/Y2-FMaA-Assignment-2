/*#include <iostream>
#include <sstream>
#include <map>

using namespace std;

struct Waypoint
{
	int id;
	int productA = 0;
	int productB = 0;
	int productC = 0;
	int productD = 0;
	int productE = 0;
};

struct Node
{
	int distance = INT_MAX;
	string path;
};

void SetGraph(int x, int y, int value);
int GetGraph(int x, int y);
void DefaultGraph();

void DynamicPath(Waypoint home, Waypoint w1, Waypoint w2, Waypoint w3, Waypoint w4, Node simplified[5][5],
	int currentWaypoint, int currentValue, string currentPath);
Node DynamicDistance(int start, int end);
int BruteForceDistance(int start, int end);

int _graph[64];
int _products[5] = { 20, 40, 70, 10, 30 };

int bestValue;
string bestPath;

int main()
{
	for (int i = 0; i < 64; i++)
		_graph[i] = -1;

	DefaultGraph();

	//cout << "" << pos4 << endl;

	Waypoint w1, w2, w3, w4, h;

	cout << "Enter the home waypoint" << endl;
	cin >> h.id;
	cout << "Enter the first waypoint" << endl;
	cin >> w1.id;
	cout << "Enter the second waypoint" << endl;
	cin >> w2.id;
	cout << "Enter the third waypoint" << endl;
	cin >> w3.id;
	cout << "Enter the fourth waypoint" << endl;
	cin >> w4.id;

	Node simplified[5][5];

	/*simplified[0, 1] = BruteForceDistance(h, w1);
	simplified[0, 2] = BruteForceDistance(h, w2);
	simplified[0, 3] = BruteForceDistance(h, w3);
	simplified[0, 4] = BruteForceDistance(h, w4);

	simplified[1, 2] = BruteForceDistance(w1, w2);
	simplified[1, 3] = BruteForceDistance(w1, w3);
	simplified[1, 4] = BruteForceDistance(w1, w4);

	simplified[2, 3] = BruteForceDistance(w2, w3);
	simplified[2, 4] = BruteForceDistance(w2, w4);

	simplified[3, 4] = BruteForceDistance(w3, w4);

	cout << "Now Dynamic" << endl;/

	simplified[0][1] = DynamicDistance(h.id, w1.id);
	simplified[0][2] = DynamicDistance(h.id, w2.id);
	simplified[0][3] = DynamicDistance(h.id, w3.id);
	simplified[0][4] = DynamicDistance(h.id, w4.id);

	simplified[1][2] = DynamicDistance(w1.id, w2.id);
	simplified[1][3] = DynamicDistance(w1.id, w3.id);
	simplified[1][4] = DynamicDistance(w1.id, w4.id);

	simplified[2][3] = DynamicDistance(w2.id, w3.id);
	simplified[2][4] = DynamicDistance(w2.id, w4.id);

	simplified[3][4] = DynamicDistance(w3.id, w4.id);

	for (int x = 0; x < 4; x++)
		for (int y = x + 1; y < 5; y++)
			simplified[y][x] = simplified[x][y];

	cout << simplified[0][1].distance << endl;
	cout << simplified[1][0].distance << endl;

	// Give it a feasable but generic end value
	bestValue = GetGraph(h.id, w1.id) + GetGraph(w1.id, w2.id) + GetGraph(w2.id, w3.id) + GetGraph(w3.id, w4.id) + GetGraph(w4.id, h.id);
	stringstream st;
	st << h.id;
	DynamicPath(h, w1, w2, w3, w4, simplified, 0, 0, st.str());
}

void DynamicPath(Waypoint h, Waypoint w1, Waypoint w2, Waypoint w3, Waypoint w4, Node simplified[5][5],
	int currentWaypoint, int currentValue, string currentPath)
{
	cout << currentValue << " " << currentPath << endl;

	// If you've arrived at the home waypoint and completed the cycle, you're done
	if (currentWaypoint == h.id &&
		currentPath.find(w1.id) != string::npos &&
		currentPath.find(w2.id) != string::npos &&
		currentPath.find(w3.id) != string::npos &&
		currentPath.find(w4.id) != string::npos)
	{
		cout << "Path found: " << currentValue << "m, " << currentPath << endl;
		bestPath = currentPath;
		bestValue = currentValue;
		return;
	}

	for (int i = 0; i < 5; i++)
	{
		if (i == currentWaypoint)
			continue;

		int moveValue = simplified[currentWaypoint][i].distance;

		if (currentValue + moveValue > bestValue)
			continue;
		stringstream newPath;
		newPath << currentPath;
		if (i == 0)
			newPath << h.id;
		else if (i == 1)
			newPath << w1.id;
		else if (i == 2)
			newPath << w2.id;
		else if (i == 3)
			newPath << w3.id;
		else if (i == 4)
			newPath << w4.id;
		DynamicPath(h, w1, w2, w3, w4, simplified, i, currentValue + moveValue, newPath.str());
	}
}

Node DynamicDistance(int start, int end)
{
	map<string, int> distances;
	int best = INT_MAX;

	for (int pos2 = 1; pos2 <= 8; pos2++)
	{
		if (pos2 == start)
			continue;

		int total = GetGraph(start, pos2);

		if (total >= best)
			continue;

		if (pos2 == end)
		{
			stringstream key;
			key << start;
			key << pos2;
			distances[key.str()] = total;
			best = total;
			continue;
		}

		for (int pos3 = 1; pos3 <= 8; pos3++)
		{
			if (pos3 == start || pos3 == pos2)
				continue;

			total = GetGraph(start, pos2);
			total += GetGraph(pos2, pos3);

			if (total >= best)
				continue;

			if (pos3 == end)
			{
				stringstream key;
				key << start;
				key << pos2;
				key << pos3;
				distances[key.str()] = total;
				best = total;
				continue;
			}

			for (int pos4 = 1; pos4 <= 8; pos4++)
			{
				if (pos4 == start || pos4 == pos2 || pos4 == pos3)
					continue;

				total = GetGraph(start, pos2);
				total += GetGraph(pos2, pos3);
				total += GetGraph(pos3, pos4);

				if (total >= best)
					continue;

				if (pos4 == end)
				{
					stringstream key;
					key << start;
					key << pos2;
					key << pos3;
					key << pos4;
					distances[key.str()] = total;
					best = total;
					continue;
				}

				for (int pos5 = 1; pos5 <= 8; pos5++)
				{
					if (pos5 == start || pos5 == pos2 || pos5 == pos3 || pos5 == pos4)
						continue;

					total = GetGraph(start, pos2);
					total += GetGraph(pos2, pos3);
					total += GetGraph(pos3, pos4);
					total += GetGraph(pos4, pos5);

					if (total >= best)
						continue;

					if (pos5 == end)
					{
						stringstream key;
						key << start;
						key << pos2;
						key << pos3;
						key << pos4;
						key << pos5;
						distances[key.str()] = total;
						best = total;
						continue;
					}

					for (int pos6 = 1; pos6 <= 8; pos6++)
					{
						if (pos6 == start || pos6 == pos2 || pos6 == pos3 || pos6 == pos4 || pos6 == pos5)
							continue;

						total = GetGraph(start, pos2);
						total += GetGraph(pos2, pos3);
						total += GetGraph(pos3, pos4);
						total += GetGraph(pos4, pos5);
						total += GetGraph(pos5, pos6);

						if (total >= best)
							continue;

						if (pos6 == end)
						{
							stringstream key;
							key << start;
							key << pos2;
							key << pos3;
							key << pos4;
							key << pos5;
							key << pos6;
							distances[key.str()] = total;
							best = total;
							continue;
						}

						for (int pos7 = 1; pos7 <= 8; pos7++)
						{
							if (pos7 == start || pos7 == pos2 || pos7 == pos3 || pos7 == pos4 || pos7 == pos5 || pos7 == pos6)
								continue;

							total = GetGraph(start, pos2);
							total += GetGraph(pos2, pos3);
							total += GetGraph(pos3, pos4);
							total += GetGraph(pos4, pos5);
							total += GetGraph(pos5, pos6);
							total += GetGraph(pos6, pos7);

							if (total >= best)
								continue;

							if (pos7 == end)
							{
								stringstream key;
								key << start;
								key << pos2;
								key << pos3;
								key << pos4;
								key << pos5;
								key << pos6;
								key << pos7;
								distances[key.str()] = total;
								best = total;
								continue;
							}

							for (int pos8 = 1; pos8 <= 8; pos8++)
							{
								if (pos8 == start || pos8 == pos2 || pos8 == pos3 || pos8 == pos4 || pos8 == pos5 || pos8 == pos6 || pos8 == pos7)
									continue;

								total = GetGraph(start, pos2);
								total += GetGraph(pos2, pos3);
								total += GetGraph(pos3, pos4);
								total += GetGraph(pos4, pos5);
								total += GetGraph(pos5, pos6);
								total += GetGraph(pos6, pos7);
								total += GetGraph(pos7, pos8);

								if (total >= best)
									continue;

								if (pos8 == end)
								{
									stringstream key;
									key << start;
									key << pos2;
									key << pos3;
									key << pos4;
									key << pos5;
									key << pos6;
									key << pos7;
									key << pos8;
									distances[key.str()] = total;
									best = total;
									continue;
								}
							}
						}
					}
				}
			}
		}
	}

	Node node;
	for (pair<string, int> pair : distances)
	{
		if (pair.second < node.distance)
		{
			node.path = pair.first;
			node.distance = pair.second;
		}
	}

	cout << "Dynamic Shortening for " << start << " to " << end << " took " << distances.size() << " attempts" << endl;
	cout << "Optimal path " << node.path << " which is " << node.distance << "m" << endl;
	return node;
}

int BruteForceDistance(int start, int end)
{
	map<string, int> distances;

	for (int pos2 = 1; pos2 <= 8; pos2++)
	{
		if (pos2 == start)
			continue;
		if (pos2 == end)
		{
			stringstream key;
			key << start;
			key << pos2;
			int total = 0;
			total += GetGraph(start, pos2);
			distances[key.str()] = total;
			continue;
		}

		for (int pos3 = 1; pos3 <= 8; pos3++)
		{
			if (pos3 == start || pos3 == pos2)
				continue;
			if (pos3 == end)
			{
				stringstream key;
				key << start;
				key << pos2;
				key << pos3;
				int total = 0;
				total += GetGraph(start, pos2);
				total += GetGraph(pos2, pos3);
				distances[key.str()] = total;
				continue;
			}

			for (int pos4 = 1; pos4 <= 8; pos4++)
			{
				if (pos4 == start || pos4 == pos2 || pos4 == pos3)
					continue;
				if (pos4 == end)
				{
					stringstream key;
					key << start;
					key << pos2;
					key << pos3;
					key << pos4;
					int total = 0;
					total += GetGraph(start, pos2);
					total += GetGraph(pos2, pos3);
					total += GetGraph(pos3, pos4);
					distances[key.str()] = total;
					continue;
				}

				for (int pos5 = 1; pos5 <= 8; pos5++)
				{
					if (pos5 == start || pos5 == pos2 || pos5 == pos3 || pos5 == pos4)
						continue;
					if (pos5 == end)
					{
						stringstream key;
						key << start;
						key << pos2;
						key << pos3;
						key << pos4;
						key << pos5;
						int total = 0;
						total += GetGraph(start, pos2);
						total += GetGraph(pos2, pos3);
						total += GetGraph(pos3, pos4);
						total += GetGraph(pos4, pos5);
						distances[key.str()] = total;
						continue;
					}


					for (int pos6 = 1; pos6 <= 8; pos6++)
					{
						if (pos6 == start || pos6 == pos2 || pos6 == pos3 || pos6 == pos4 || pos6 == pos5)
							continue;
						if (pos6 == end)
						{
							stringstream key;
							key << start;
							key << pos2;
							key << pos3;
							key << pos4;
							key << pos5;
							key << pos6;
							int total = 0;
							total += GetGraph(start, pos2);
							total += GetGraph(pos2, pos3);
							total += GetGraph(pos3, pos4);
							total += GetGraph(pos4, pos5);
							total += GetGraph(pos5, pos6);
							distances[key.str()] = total;
							continue;
						}


						for (int pos7 = 1; pos7 <= 8; pos7++)
						{
							if (pos7 == start || pos7 == pos2 || pos7 == pos3 || pos7 == pos4 || pos7 == pos5 || pos7 == pos6)
								continue;
							if (pos7 == end)
							{
								stringstream key;
								key << start;
								key << pos2;
								key << pos3;
								key << pos4;
								key << pos5;
								key << pos6;
								key << pos7;
								int total = 0;
								total += GetGraph(start, pos2);
								total += GetGraph(pos2, pos3);
								total += GetGraph(pos3, pos4);
								total += GetGraph(pos4, pos5);
								total += GetGraph(pos5, pos6);
								total += GetGraph(pos6, pos7);
								distances[key.str()] = total;
								continue;
							}

							for (int pos8 = 1; pos8 <= 8; pos8++)
							{
								if (pos8 == start || pos8 == pos2 || pos8 == pos3 || pos8 == pos4 || pos8 == pos5 || pos8 == pos6 || pos8 == pos7)
									continue;
								if (pos8 == end)
								{
									stringstream key;
									key << start;
									key << pos2;
									key << pos3;
									key << pos4;
									key << pos5;
									key << pos6;
									key << pos7;
									key << pos8;
									int total = 0;
									total += GetGraph(start, pos2);
									total += GetGraph(pos2, pos3);
									total += GetGraph(pos3, pos4);
									total += GetGraph(pos4, pos5);
									total += GetGraph(pos5, pos6);
									total += GetGraph(pos6, pos7);
									total += GetGraph(pos7, pos8);
									distances[key.str()] = total;
									continue;
								}
							}
						}
					}
				}
			}
		}
	}

	string path;
	int distance = -1;
	for (pair<string, int> pair : distances)
	{
		if (pair.second < distance || distance == -1)
		{
			path = pair.first;
			distance = pair.second;
		}
	}

	cout << "Brute Forcing " << start << " to " << end << " took " << distances.size() << " attempts" << endl;
	cout << "Optimal path " << path << " which is " << distance << "m" << endl;
	return distance;
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
}*/