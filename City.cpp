//Qinying Wu
//20783213
//q227wu
//ECE250
//Project 5: Single Source Shortest Path - Dijsktra's Algorithm
//this is the class definition for the city object

//#pragma once
#include "City.h"

//constructor for the City object
City::City(string name,int index) {
	this->name = name;
	this->index = index;

}

//destructor for the City object
City::~City() {
	adjacent.clear();
}

CityPQ::CityPQ(City* obj) {
	inQ = false;
	d = INFINITY; //initialize the distance to infinity
	cityObj = obj;
	parent = nullptr;
}
CityPQ::~CityPQ() {
	cityObj = nullptr;
	parent = nullptr;

}
