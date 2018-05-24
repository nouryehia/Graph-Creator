/* Graph Creator
 * Author: Nour Yehia
 * Date: 5-24-18
 * This program creates a graph by allowing the user to add and remove edges and vertices. It also allows the user to find the shortest path between two vertices and to print out the graph in the form of an adjacency table. */

//Include.
#include "graph.h"

int main(){

	//Declare variables.
	graph graph;
	char answer;
	bool running = true;

	cout << "\nThis program creates a graph made of vertices and edges.\n";

	while (running) {

		//Prompt user.
		cout << "\nCommands:\n" 
			 << "(1) Add a vertex\n"
			 << "(2) Add an edge\n"
			 << "(3) Remove a vertex\n"
			 << "(4) Remove an edge\n"
			 << "(P) Print graph\n"
			 << "(Q) Quit\n\n";

		cin >> answer;

		//Make sure answer is valid.
		while (answer != '1' && answer != '2' && answer != '3' && 
			   answer != '4' && answer != 'P' && answer != 'p' && answer != 'Q' && answer != 'q') {
			cout << "\nChoose one of the options above.\n\n";
			cin >> answer;
		}

		//Call function based on answer.
		if (answer == '1') graph.addVertex();
		if (answer == '2') graph.addEdge();
		if (answer == '3') graph.removeVertex();
		if (answer == '4') graph.removeEdge();
		if (answer == 'P' || answer == 'p') graph.print();
		if (answer == 'Q' || answer == 'q') running = false;
	}

}