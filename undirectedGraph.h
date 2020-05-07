//#pragma once
//Qinying Wu
//20783213
//q227wu
//ECE250
//Project 5: Single Source Shortest Path - Dijsktra's Algorithm
//this is the class declaration header for the undirectedGraph object
#include <vector>
#include "City.h"
using std::vector;

//constant variables for indicating invalid operations
const string FAILURESTR = "failure";
const string SUCCESS = "success";
const int FAILUREINT = -1;


//binary sort function for sorting the PQ
//parameter Q is the priority queue
//parameter obj is the city to be inserted to the PQ
//parameter index is the index of the city in Q for comparison
//parameter lowerBound is the lower bound of the current checking range
//parameter upperBound is the upper bound of the current checking range
//returns the sorted PQ after inserting the cityPQ obj
//vector<CityPQ*> BinarySort(vector<CityPQ*> Q, CityPQ* obj, int index, int lowerBound, int upperBound);

//function that performs minimum binary heap sort
//returns the sorted PQ with the first element as the minimum element in the vector so far
//parameter Q is the priority queue
//parameter root is the root assumed having two children nodes with greater values
vector<CityPQ*> BinaryHeapSort(vector<CityPQ*> Q, int root);

//class declaration
class undirectedGraph {
public:
	//inserts a city (node) into the graph
	//returns true if the city is inserted successfully
	//returns false if the city already exists in the graph
	bool i(string name);

	//assigns or updates a distance d to the edge (road) between two nodes (cities) name1 and name2
	//returns true if assigned or updated successfully
	//returns false if one or both cities do not exist, or invalid d (<=0)
	bool setd(string name1, string name2,double d);

	//search for a city with the specified name
	//parameter name is the name of the city
	//returns the index of the city stored in the cities vector if found, -1 if not found
	int s(string name);

	//returns the degree of the given city
	//parameter name is the name of the city
	int degree(string name);

	//returns the number of cities (nodes) in the graph
	int graph_nodes();
	//returns the number of roads (edges) in the graph
	int graph_edges();

	//returns the weight of the edge between the two nodes name1 and name2 if both cities are found
	//returns -1 if there exist no edge between the two cities or either name1 and/or name2 is/are non-existing cities in the graph
	//name1 is the name of the first city
	//name2 is the name of the second city that makes up the edge
	double d(string name1, string name2);

	//returns the vector of CityPQ objects after performing the Dijkstra's algorithm containing the shortest path from city1 indicated by index1 to city2 indicated by city2
//parameters index1 is the corresponding index of the city in the cities vector of the undirectedGraph object
	vector<CityPQ*> Dijkstra(int index1);

	//deletes all the nodes (cities) and edges (roads) from the graph
	void clear();

	//determines the minimum path weight from a city to its adjacent city
	//parameter u is the originating city, v is u's adjacent city (there exist a path between city u and v)
	void Relax(CityPQ* u, CityPQ* v);
	undirectedGraph();//constructor
	~undirectedGraph();//destructor
private:
	vector<City*> cities; //storing the list of cities in the graph (nodes)
	vector<vector<double>> roads; //storing the rad connection between cities (edges)
	int road_count; //store the number of roads (edges) in the graph
};
