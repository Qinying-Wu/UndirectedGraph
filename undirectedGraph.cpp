//Qinying Wu
//20783213
//q227wu
//ECE250
//Project 5: Single Source Shortest Path - Dijsktra's Algorithm
//this is the class definition for the undirectedGraph object
//#pragma once
#include "undirectedGraph.h"

//constructor
undirectedGraph::undirectedGraph() {
	road_count = 0;
}
//destructor
undirectedGraph::~undirectedGraph() {
	roads.clear();
	cities.clear();
}

//inserts a city (node) into the graph
//returns true if the city is inserted successfully
//returns false if the city already exists in the graph
bool undirectedGraph::i(string name){
	if (s(name) == -1) {//only add when the city is not found
		cities.push_back(new City(name,cities.size()));
		roads.resize(roads.size() + 1);
		//resize the adjacency matrix to fit more roads
		for (unsigned int i = 0; i < roads.size(); i++) {
			roads.at(i).resize(roads.size());
		}
		return true;
	}
	return false;
}

//assigns or updates a distance d to the edge (road) between two nodes (cities) name1 and name2
//returns true if assigned or updated successfully
//returns false if one or both cities do not exist, or invalid d (<=0)
bool undirectedGraph::setd(string name1, string name2,double d) {
	int index1 = s(name1);
	int index2 = s(name2);
	if (index1 == -1 || index2 == -1 || d <= 0||index1==index2) {
		return false;
	}
	else {
		if (roads.at(index1).at(index2) == 0 && roads.at(index2).at(index1) == 0) { //first time adding a road between these two cities
			++road_count;
			cities.at(index1)->adjacent.push_back(cities.at(index2));
			cities.at(index2)->adjacent.push_back(cities.at(index1));
		}
		roads.at(index1).at(index2) = d;
		roads.at(index2).at(index1) = d; //assign the weight of the edge in the corresponding entry of the adjacency matrix
		return true;
	}
}


//search for a city with the specified name
//parameter name is the name of the city
//returns the index of the city stored in the cities vector if found, -1 if not found
int undirectedGraph::s(string name) {
	for (unsigned int i = 0; i < cities.size(); i++) {
		if (cities.at(i)->name == name) {
			return i; //name found
		}
	}
	return FAILUREINT; //name not found
}

//returns the degree of the given city
//parameter name is the name of the city
int undirectedGraph::degree(string name) {
	int index = s(name);
	if (index != -1) {
		return cities.at(index)->adjacent.size(); //size pf the adjacent edges set is the degree
	}
	else {
		return FAILUREINT;
	}
}

//returns the number of cities (nodes) in the graph
int undirectedGraph::graph_nodes() {
	return cities.size();
}
//returns the number of roads (edges) in the graph
int undirectedGraph::graph_edges() {
	return road_count;
}

//returns the weight of the edge between the two nodes name1 and name2 if both cities are found
//returns -1 if there exist no edge between the two cities or either name1 and/or name2 is/are non-existing cities in the graph
//name1 is the name of the first city
//name2 is the name of the second city that makes up the edge
double undirectedGraph::d(string name1, string name2) {
	int index1 = s(name1);
	int index2 = s(name2);
	if (index1 == -1 || index2 == -1 || roads.at(index1).at(index2) == 0||index1==index2) {
		return FAILUREINT;
	}
	else {
		return roads.at(index1).at(index2);
	}
}

//returns the vector of CityPQ objects after performing the Dijkstra's algorithm containing the shortest path from city1 indicated by index1 to city2 indicated by city2
//parameters index1 is the corresponding index of the city in the cities vector of the undirectedGraph object
vector<CityPQ*> undirectedGraph::Dijkstra(int index1) {
	vector<CityPQ*> All; //the vector containing all the City PQ objects for comparison
	vector<CityPQ*>Sorted; //for storing the vities already visited
	Sorted.resize(cities.size());
	for (unsigned int i = 0; i < cities.size(); i++) {
		All.push_back(new CityPQ(cities.at(i)));
	}
	All.at(index1)->d = 0;//s.setd(0)
	All.at(index1)->inQ = true;
	vector<CityPQ*> Q = { All.at(index1) }; //storing the cities to be visited (PQ)
	while (Q.size() != 0) {
		CityPQ* u = Q.at(0);
		Q.erase(Q.begin()); //remove the first city in PQ since it is being processed right now
		//sort the adjacent edges in ascending weight order to form a valid PQ
		for (unsigned int i = 0; i < u->cityObj->adjacent.size(); i++) {
			int vIndex = u->cityObj->adjacent.at(i)->index;
			CityPQ* v = All.at(vIndex);
			if (Sorted.at(vIndex) != All.at(vIndex)) {//only relax cities that are not already sorted
				Relax(u, v);
				if (v->inQ == false) {
					v->inQ = true;
					//reorganize PQ in ascending weight order
					if (Q.size() == 0) {
						Q.push_back(v);
					}
					else {
						Q.insert(Q.begin(), v);
					}
					//	//Q=BinarySort(Q, v, Q.size() / 2,0,Q.size()-1);
					//	/*for (unsigned int i = 0; i <= Q.size(); i++) {
					//		if (i == Q.size()) {
					//			Q.push_back(v);
					//			break;
					//		}
					//		else if (Q.at(i)->d >= v->d) {
					//			Q.insert(Q.begin() + i, v);
					//			break;
					//		}
					//	}*/
					//}
				}
			}
			Q = BinaryHeapSort(Q, 0);
		}
		Sorted.at(u->cityObj->index) = u;
	}
	return All;
}


//deletes all the nodes (cities) and edges (roads) from the graph
void undirectedGraph::clear() {
	cities.clear();
	roads.clear();
	road_count = 0;
}

//determines the minimum path weight from a city to its adjacent city
//parameter u is the originating city, v is u's adjacent city (there exist a path between city u and v)
void undirectedGraph::Relax(CityPQ* u, CityPQ* v) {
	//establish the min weight
	if (v->d > u->d + roads.at(u->cityObj->index).at(v->cityObj->index)) {
		v->d = u->d + roads.at(u->cityObj->index).at(v->cityObj->index);
		v->parent = u;
	}
}

//binary sort function for sorting the PQ
//parameter Q is the priority queue
//parameter obj is the city to be inserted to the PQ
//parameter index is the index of the city in Q for comparison
//parameter lowerBound is the lower bound of the current checking range
//parameter upperBound is the upper bound of the current checking range
//returns the sorted PQ after inserting the cityPQ obj
//vector<CityPQ*> BinarySort(vector<CityPQ*> Q,CityPQ* obj,int index,int lowerBound, int upperBound) {
//	if (Q.at(index)->d <= obj->d) {//go to the right half of the sorted list
//		lowerBound = index+1;
//		if (lowerBound > upperBound) {
//			if (upperBound == Q.size() - 1) {
//				Q.push_back(obj);
//			}
//			else {
//				Q.insert(Q.begin() + lowerBound, obj);
//			}
//			return Q;
//		}
//		else {
//			return BinarySort(Q, obj, (upperBound + lowerBound) / 2, lowerBound, upperBound);
//		}
//
//	}
//	else if (Q.at(index)->d > obj->d) {//go to the left half of the sorted list
//		upperBound = index-1;
//		if (lowerBound > upperBound) {
//			if (lowerBound ==0) {
//				Q.insert(Q.begin(), obj);
//			}
//			else {
//				Q.insert(Q.begin() + upperBound, obj);
//			}
//			return Q;
//		}
//		else {
//			return BinarySort(Q, obj, (lowerBound+upperBound)/2, lowerBound, upperBound);
//		}
//		
//	}
//
//}

//function that performs minimum binary heap sort
//returns the sorted PQ with the first element as the minimum element in the vector so far
//parameter Q is the priority queue
//parameter root is the root assumed having two children nodes with greater values
vector<CityPQ*> BinaryHeapSort(vector<CityPQ*> Q,int root) {
	int leftIndex = root * 2+1;
	int rightIndex = (root+1) * 2;
	int newRoot = root;
	//case 1: left subtree value smaller than the current root
	if (leftIndex<Q.size() &&Q.at(leftIndex)->d < Q.at(newRoot)->d) {
		newRoot = leftIndex;
	}
	//case 2: right subtree value smaller than the current root
	if (rightIndex<Q.size() &&Q.at(rightIndex)->d < Q.at(newRoot)->d) {
		newRoot = rightIndex;
	}
	//when the greatest value is not the current root
	if (newRoot != root) {
		CityPQ* temp = Q.at(root);
		Q.at(root) = Q.at(newRoot);
		Q.at(newRoot) = temp;
		temp = nullptr;
		Q = BinaryHeapSort(Q, newRoot);
	}
	return Q;
}