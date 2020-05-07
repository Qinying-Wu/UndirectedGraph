//Qinying Wu
//20783213
//q227wu
//ECE250
//Project 5: Single Source Shortest Path - Dijsktra's Algorithm
//this is the entry point of the undirectedGraphtest program

#include "undirectedGraph.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::stod;
int main()
{
	//initialize a MST object
	undirectedGraph ug;
	string input = "";
	while (std::getline(cin, input)) {
		int space = input.find(' ');
		string command = input;
		string parameter = "";
		if (space != FAILUREINT) {//some parameters are passed
			command = input.substr(0, space);
			parameter = input.substr(space + 1, input.length());
		}
		if (command == "i") {
			if (ug.i(parameter)) {
				cout << SUCCESS << endl;
			}
			else {
				cout << FAILURESTR << endl;
			}
			
		}
		else if (command == "setd") {
			int semi_colon = parameter.find_first_of(';');
			string name1 = parameter.substr(0, semi_colon);
			parameter = parameter.substr(semi_colon + 1, parameter.length());
			semi_colon = parameter.find_first_of(';');
			string name2 = parameter.substr(0, semi_colon);
			double d = stod(parameter.substr(semi_colon + 1, parameter.length()));
			if (ug.setd(name1, name2, d)) {
				cout << SUCCESS << endl;
			}
			else {
				cout << FAILURESTR << endl;
			}
		}
		else if (command == "s") {
			if (ug.s(parameter)!=FAILUREINT) {
				cout << "found " <<parameter<< endl;
			}
			else {
				cout << "not found" << endl;
			}
		}
		else if (command == "degree") {
			int result = ug.degree(parameter);
			if (result == FAILUREINT) {
				cout << FAILURESTR << endl;
			}
			else {
				cout << "degree of "<<parameter<< " " << result << endl;
			}
			
		}
		else if (command == "graph_nodes") {
			cout << "number of nodes " << ug.graph_nodes() << endl;
		}
		else if (command == "graph_edges") {
			cout << "number of edges " << ug.graph_edges() << endl;
		}
		else if (command == "d") {
			int semi_colon = parameter.find(';');
			string name1 = parameter.substr(0, semi_colon);
			string name2 = parameter.substr(semi_colon + 1, parameter.length());
			double result = ug.d(name1, name2);
			if (result == FAILUREINT) {
				cout << FAILURESTR << endl;
			}
			else {
				cout << "direct distance " << name1 << " to " << name2 << " " << result << endl;
			}
		}
		else if (command == "shortest_d"||command=="print_path") {
			int semi_colon = parameter.find(';');
			string name1 = parameter.substr(0, semi_colon);
			string name2 = parameter.substr(semi_colon + 1, parameter.length());
			int index1 =ug.s(name1);
			int index2 = ug.s(name2);
			//one or both cities DNE, or both cities refer to the same city
			if (index1 == FAILUREINT || index2 == FAILUREINT || index1 == index2) {
				cout << FAILURESTR << endl;
			}
			else {
				vector<CityPQ*> All = ug.Dijkstra(index1);
				if (All.at(index2)->d ==INFINITY) {//the city is not reachable
					cout << FAILURESTR << endl;
				}
				else {
					if (command == "shortest_d") {
						cout << "shortest distance " << name1 << " to " << name2 << " " << All.at(index2)->d << endl;
					}
					else if (command == "print_path") {
						string path = "";//construct the path string
						CityPQ* end = All.at(index2);
						while (end != All.at(index1)) {
							path = " " + end->cityObj->name + path;
							end = end->parent;
						}
						path = All.at(index1)->cityObj->name + path;
						cout << path<< endl;
					}
				}
			}
		}
		else if (command == "clear") {
			ug.clear();
			cout << SUCCESS << endl;
		}
	}
	return 0;
}






