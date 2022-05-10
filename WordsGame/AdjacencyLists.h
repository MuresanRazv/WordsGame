#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
using std::map;
using std::vector;
using std::string;

template <typename dataType>
struct Node {
	vector<Node<dataType>*> adjList;
	dataType element;
};

template <typename dataType>
class Graph {
private:
	// Adjacency list: Array of pointers to the heads of the graph
	map<dataType, vector<dataType>> vertices;
	friend class Game;

public:
	// Implicit Constructor
	Graph();

	// Destructor
	~Graph();

	// Get vertices
	map<dataType, vector<dataType>>& getVertices();

	// Insert new node in adjacency list
	void addNode(dataType element);

	// Connect two nodes
	bool connect(dataType node1, dataType node2);
	
};

template<typename dataType>
inline Graph<dataType>::Graph()
{
}

template<typename dataType>
inline Graph<dataType>::~Graph()
{
	vertices.clear();
}

template<typename dataType>
inline map<dataType, vector<dataType>>& Graph<dataType>::getVertices()
{
	return vertices;
}

template<typename dataType>
inline void Graph<dataType>::addNode(dataType element) {
	if (vertices.find(element) == vertices.end()) {
		vertices.insert(std::pair<dataType, vector<dataType>>(element, vector<dataType>()));
	}
}

template<typename dataType>
inline bool Graph<dataType>::connect(dataType node1, dataType node2)
{
	if (vertices.find(node1) != vertices.end() && vertices.find(node2) != vertices.end()) {
		vertices[node1].push_back(node2);
		vertices[node2].push_back(node1);
	}
	return true;
}


