#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

#define NUM_OF_NODES 7		// total number of nodes
#define INF 9999			// unsearched node distance

// Convert the weighted graph matrix to upper triangle matrix
void pre_processing(int* graph) {
	for (int i = NUM_OF_NODES - 1; i > 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			if (graph[i * NUM_OF_NODES + j] != 0) {
				if (graph[j * NUM_OF_NODES + i] != 0) {
					cerr << "Weighted graph matrix value error" << endl;
					return;
				}
				graph[j * NUM_OF_NODES + i] = graph[i * NUM_OF_NODES + j];
				graph[i * NUM_OF_NODES + j] = 0;
			}
		}
	}
}

void breadth_first_search(int* graph, int src, int des) {
	int* dist = new int[NUM_OF_NODES];
	bool* visited = new bool[NUM_OF_NODES];
	bool finish_flag = false;
	int finish_iter = 0;

	for (int i = 0; i < NUM_OF_NODES; i++) {
		dist[i] = INF;
		visited[i] = false;
	}

	dist[src] = 0;
	visited[src] = true;

	vector<vector<int>> potential_path;
	potential_path.push_back(vector<int>());
	potential_path[0].push_back(src);
	for (int i = 0; i < NUM_OF_NODES; i++) {
		potential_path.push_back(vector<int>());
		int element_num_layer = potential_path[i].size();

		for (int j = 0; j < element_num_layer; j++) {
			for (int k = 0; k < NUM_OF_NODES; k++) {
				if (k == j) continue;	// don't need compare the vertex itself
				if (graph[j * NUM_OF_NODES + k] != 0) {
					if (!visited[k]) {
						dist[k] = graph[j * NUM_OF_NODES + k];
						visited[k] = true;
						potential_path[i + 1].push_back(k);

						if (k == des) finish_flag = true;
					}
					else {
						if (dist[j] + graph[j * NUM_OF_NODES + k] < dist[k]) {
							dist[k] = dist[j] + graph[j * NUM_OF_NODES + k];
						}
					}
				}
			}
		}

		if (finish_flag) {
			finish_iter = i + 1;
			break;
		}
	}

	for (const auto& vec : potential_path) {     // for every vector in v
		for (const auto& num : vec) // print the numbers
			cout << char(65 + num) << " ";
		cout << '\n';
	}
}

void update_Dij(int* graph, int src, int des) {
	int* dist = new int[NUM_OF_NODES];

	for (int i = 0; i < NUM_OF_NODES; i++) {
		dist[i] = INF;
	}

	dist[src] = 0;

	for (int i = 0; i < NUM_OF_NODES - 1; i++) {
		for (int j = i + 1; j < NUM_OF_NODES; j++) {
			if (graph[i * NUM_OF_NODES + j] != 0 && dist[i] != INF
				&& dist[i] + graph[i * NUM_OF_NODES + j] < dist[j]) {
				dist[j] = dist[i] + graph[i * NUM_OF_NODES + j];
			}
		}
	}

	for (int i = 0; i < NUM_OF_NODES; i++) {
		cout << dist[i] << " ";
	}
	cout << endl;

	cout << "Shortest path calculation using Dijkstra's algorithm. " << endl
		<< "From " << char(65 + src) << " to " << char(65 + des)
		<< " is: " << dist[des] << endl << endl;

	delete[] dist;
}


int main() {
	int* graph = new int[NUM_OF_NODES * NUM_OF_NODES];
	int graph_raw[NUM_OF_NODES * NUM_OF_NODES] = {
		0,5,3,0,0,0,0,
		0,0,2,0,3,0,1,
		0,0,0,7,7,0,0,
		2,0,0,0,0,6,0,
		0,0,0,2,0,1,0,
		0,0,0,0,0,0,0,
		0,0,0,0,1,0,0
	};

	for (int i = 0; i < NUM_OF_NODES * NUM_OF_NODES; i++) {
		graph[i] = graph_raw[i];
	}

	pre_processing(graph);
	update_Dij(graph, 0, 5);
	breadth_first_search(graph, 0, 6);

	delete[] graph;
	return 0;
}