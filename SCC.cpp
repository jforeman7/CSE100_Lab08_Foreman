// Jeff Foreman
// CSE 100
// Lab 08: Strongly Connected Components
// 15 November 2017

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Array to mark if visited or not.
bool visit[101] = { 0 };

// SCC structures.
vector<int> adjacent[101], rev[101], order;
vector< vector<int> > SCC;

// Depth-First Search of the graph.
void DFS(vector<int> graph[], vector<int> &res, int i) 
{
	visit[i] = true;
	for (int j = 0; j < graph[i].size(); j++) 
	{
		if (!visit[graph[i][j]])
			DFS(graph, res, graph[i][j]);
	}
	res.push_back(i);
}

// Initialize and create an SCC graph.
void createSCC(int vertices)
{
	for (int i = 0; i < vertices; i++) 
		visit[i] = false;

	reverse(order.begin(), order.end());
	for (int i = 0; i < order.size(); i++) 
	{
		if (!visit[order[i]]) 
		{
			vector<int> component;
			DFS(rev, component, order[i]);
			SCC.push_back(component);
		}
	}
}

// Create the graph structure.
void createGraph(int vertices, int edges)
{
	int u, v;

	for (int i = 0; i < edges; i++) 
	{
		cin >> u >> v;
		adjacent[u].push_back(v);
	}

	for (int i = 0; i < vertices; i++) 
		visit[i] = false;

	for (int i = 0; i < vertices; i++) 
	{
		if (!visit[i])
			DFS(adjacent, order, i);
	}

	for (int i = 0; i < vertices; i++) 
	{
		for (int j = 0; j < adjacent[i].size(); j++)
			rev[adjacent[i][j]].push_back(i);
	}

}
int main() 
{
	int vertices = 0, edges = 0, comp;

	cin >> vertices >> edges;

	int * arr = new int[vertices];

	for (int i = 0; i < vertices; i++) 
	{
		arr[i] = i;
	}
	createGraph(vertices, edges);

	createSCC(vertices);

	for (int i = 0; i < SCC.size(); i++) 
	{
		for (int j = 0; j < SCC[i].size(); j++) 
		{
			comp = SCC[i][j];

			for (int k = 0; k < vertices; k++) 
			{
				if (arr[k] == comp) 
					arr[k] = *min_element(SCC[i].begin(), SCC[i].end());
			}
		}
	}
	for (int i = 0; i < vertices; i++) {
		cout << arr[i] << endl;
	}
	return 0;
}
