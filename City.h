//Qinying Wu
//20783213
//q227wu
//ECE250
//Project 5: Single Source Shortest Path - Dijsktra's Algorithm
//this is the class declaration header for the city-related objects

//#pragma once

#include <string>
#include <vector>
#include <limits>
using std::string;
using std::vector;

const double INFINITY=std::numeric_limits<double>::infinity();
//the city object in the graph
class City {
public:
	int index; //the index of the city in the cities vector for accessing in Relax()
	string name; //name of the city
	friend class undirectedGraph;
	City(string name, int index); //cosntructor for the City object
	~City(); //destructor for the City object
private:
	vector<City*> adjacent; //the cities that has a road connected to the current city
	
};

//the city object in the priority queue
class CityPQ {
public:
	City* cityObj;//the graph city object
	double d; //the weight of the shortest path from the start city to the current city
	CityPQ* parent; //the predecessor of the current city in a path
	friend class undirectedGraph;
	CityPQ(City* obj); //constructor for the city object in the Priority Queue
	~CityPQ();
private:
	bool inQ; //flag to indicate the state whether the city is waiting to be visitied or not
	
};
