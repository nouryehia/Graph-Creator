//Includes
#include <iostream> 
#include <cstring>

using namespace std;

//If undefined.
#ifndef GRAPH_H 
#define GRAPH_H

//Define class.
class graph {
protected:

	//Declare variables.
	char edges[21][21];
	int table[21][21];
	char vList[20]; //strcpy
	int vNum;
public:

	//Declare functions
	graph();
	void addVertex();
	void removeVertex();
	void addEdge();
	void removeEdge();
	void print();
};

//Constructor.
graph::graph(){

	//Initialize adjacency table.
	for (int i = 0; i < 21; i++){
		for (int j = 0; j < 21; j++){
			edges[i][j] = '\0';
			table[i][j] = -1 ;
		}
	}
	edges[0][0] = ' ';

	//Initialize list of vertices.
	for (int i; i < 20; i++) vList[i] = '\0';
	vNum = 0;
}

//Adds a vertex to the graph.
void graph::addVertex(){

	//Declare variables.
	char toAdd;
	bool inGraph = false;
	int nextOpen = 0;

	//Make sure graph is not full.
	if (vNum == 20) {
		cout << "\nYou cannot add more than 20 vertices to your tree.\n";
		return;
	}

	//Prompt user for vertex label.
	cout << "\nLabel the vertex you would like to add. Make sure it is a single character.\n\n";
	cin >> toAdd;
	vList[vNum] = toAdd;

	//Check that label is not already in use.
	for (int i = 0; i < vNum; i++)
		if (toAdd == vList[i]) inGraph = true;
	if (inGraph) {
		cout << "\nThere is already a vertex labeled '" << toAdd<< "' in your graph.\n";
		return;
	}

	//Add vertex.
	vNum++;
	edges[vNum][0] = toAdd;
	edges[0][vNum] = toAdd;

	//Create empty edges.
	for (int i = 1; i <= vNum; i++){
		table[i][vNum] = -1;
		table[vNum][i] = -1;
	}

	cout << "\nVertex '" << toAdd << "' has been added to your graph.\n";
}

//Removes a vertex from the graph.
void graph::removeVertex(){
	
	//Declare variables.
	char toRemove;
	bool inGraph = false;
	int pos;

	//Make sure graph is not empty.
	if (vNum == 0) {
		cout << "\nThere are no vertices in your graph at the moment.\n";
		return;
	}

	//Prompt user for vertex to be removed.
	cout << "\nWhich vertex would you like to remove?\n\n";
	cin >> toRemove;

	//Check if vertex is in graph.
	for (int i = 0; i < vNum; i++){
		if (toRemove == vList[i]) {
			inGraph = true;
			pos = i;
		}
	}
	if (!inGraph) {
		cout << "\nYour graph does not contain a vertex labeled '" << toRemove<< "'.\n";
		return;
	}

	//Remove vertex from list.
	for (int i = pos; i <= vNum; i++){
		if (i != vNum) vList[i] = vList[i+1];
		else vList[i] = '\0';
	}
	vNum--;

	//Remove vertex from adjacency table.
	for (int i = 0; i < 21; i++){
		for (int j = 0; j < 21; j++){
			if (i > pos && j > pos) {
				if (table[i+1][j+1]) table[i][j] = table[i+1][j+1];
				else table[i][j] = -1;
			}
			else if (i > pos){
				if (table[i+1][j]) table[i][j] = table[i+1][j];
				else table[i][j] = -1;
				if (edges[i+1][j]) edges[i][j] = edges[i+1][j];
				else edges[i][j] = '\0';
			}
			else if (j > pos){
				if (table[i][j+1]) table[i][j] = table[i][j+1];
				else table[i][j] = -1;
				if (edges[i][j+1]) edges[i][j] = edges[i][j+1];
				else edges[i][j] = '\0';
			}
			if (i > vNum || j > vNum){
				edges[i][j] = '\0';
				table[i][j] = -1;
			}
		}
	}

	cout << "\nVertex '" << toRemove << "' has been removed from your graph.\n";
}

//Adds an edge between two vertices of the graph.
void graph::addEdge(){

	//Declare variables.
	char start, end;
	bool inGraphS = false;
	bool inGraphE = false;
	int weight;

	//Make sure there are enough vertices to make an edge.
	if (vNum < 2) {
		cout << "\nYou need to have at least 2 vertices in your graph in order to add an edge.\n";
		return;
	}

	//Prompt user for edge to be added.
	cout << "\nEnter the start node followed by the end node of the edge you want to add.\n\n";
	cin >> start;
	cin >> end;

	//Check if the vertices are valid.
	for (int i = 0; i < vNum; i++){
		if (start == vList[i]) inGraphS = true;
		if (end == vList[i]) inGraphE = true;
	}
	if (!inGraphS && !inGraphE){
		cout << "\nNeither of these vertices exist in your graph.\n";
		return;		
	}
	if (!inGraphS){
		cout << "\nYour graph does not contain a vertex labeled '" << start << "'.\n";
		return;
	}
	if (!inGraphE){
		cout << "\nYour graph does not contain a vertex labeled '" << end << "'.\n";
		return;
	}
	if (start == end){
		cout << "\nEdges must connect two different vertices.\n";
		return;
	}

	//Prompt user for weight of edge.
	cout <<"\nEnter the weight of the edge you would like to add.\n\n";
	cin >> weight;

	//Add edge to adjacency table.
	for (int i = 0; i < 21; i++){
		for (int j = 0; j < 21; j++)
			if (edges[0][j] == start && edges[i][0] == end) table[i][j] = weight;
	}

	cout << "\nAn edge of weight " << weight << " has been added between the vertices '" << start << "' and '" << end << "'.\n";
}

//Removes an edge from the graph.
void graph::removeEdge(){

	//Declare variables.
	char start, end;
	bool inGraphS = false;
	bool inGraphE = false;

	//Check if there are enough vertices for an edge to exist.
	if (vNum < 2) {
		cout << "\nYou need to have at least 2 vertices in your graph in order to have an edge.\n";
		return;
	}

	//Prompt user for edge to be removed.
	cout << "\nEnter the start node followed by the end node of the edge you want to remove.\n\n";
	cin >> start;
	cin >> end;

	//Check validity of vertices.
	for (int i = 0; i < vNum; i++){
		if (start == vList[i]) inGraphS = true;
		if (end == vList[i]) inGraphE = true;
	}
	if (!inGraphS && !inGraphE){
		cout << "\nNeither of these vertices exist in your graph.\n";
		return;		
	}
	if (!inGraphS){
		cout << "\nYour graph does not contain a vertex labeled '" << start << "'.\n";
		return;
	}
	if (!inGraphE){
		cout << "\nYour graph does not contain a vertex labeled '" << end << "'.\n";
		return;
	}
	if (start == end){
		cout << "\nEdges must connect two different vertices.\n";
		return;
	}

	//Find vertices.
	for (int i = 0; i < 21; i++){
		for (int j = 0; j < 21; j++){
			if (edges[0][j] == start && edges[i][0] == end) {

				//Check if there is an edge between them.
				if (table[i][j] == -1) {
					cout << "\nNo edge exists between these two vertices.\n";
					return;
				}
				
				//Remove edge if it exists.
				table[i][j] = -1;
			}
		}
	}

	cout << "\nThe edge going from vertex '" << start << "' to vertex '" << end << "' has been removed from your graph.\n";
}

//Provides a visual representation of the graph in the form of an adjacency table.
void graph::print(){
	cout << "\n";
	if (vNum == 0){
		cout << "Your graph is empty. Add a vertex!\n";
		return;
	}
	for (int i = 0; i < 21; i++){
		for (int j = 0; j < 21; j++){
			if (i == 0 || j == 0){
				if (edges[i][j]) {
					if (j == 0) cout << " " << edges[i][j] << " ";
					else cout << " " << edges[i][j] << "  ";
				}
			}
			else {
				if (table[i][j] && i <= vNum && j <= vNum) {
					if (table[i][j] == -1) cout << "    ";
					else {
						if (table[i][j] < 10) cout << " " << table[i][j] << "  ";
						else if (table[i][j] >= 10 && table[i][j] < 100) cout << table[i][j] << "  ";
						else cout << table[i][j] << " ";
					}
				}
			}
		}
		if (edges[i][0]) cout << "\n";
	}
}
#endif