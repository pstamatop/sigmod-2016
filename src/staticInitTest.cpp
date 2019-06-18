#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Graph.h"
 
using namespace std;

int main() {
	SGraph graph;
	Queue queueStart, queueEnd;
	Visited visitedStart, visitedEnd;

	graph.insertEdge(1, 2);
	graph.insertEdge(2, 3);
	graph.insertEdge(3, 1);

	graph.insertEdge(2, 4);
	graph.insertEdge(4, 5);
	graph.insertEdge(5, 6);

	graph.insertEdge(6, 4);
	graph.insertEdge(5, 7);
	graph.insertEdge(7, 8);

	graph.insertEdge(8, 9);
	graph.insertEdge(9, 7);
	graph.insertEdge(6, 10);

	graph.insertEdge(10, 11);
	graph.insertEdge(11, 10);

	graph.insertEdge(9, 12);

	graph.staticInit();


	int bfsVersion = 0;
	int maxSize = graph.getMaxIndexSize();
	visitedStart.init(maxSize);
	visitedEnd.init(maxSize);
	int *levelStart = (int *) malloc(maxSize * sizeof(int));
	int *levelEnd = (int *) malloc(maxSize * sizeof(int));

	bfsVersion++;
	cout << "1 5 : " << graph.bidirectionalBFS(1, 5, queueStart, queueEnd, visitedStart, visitedEnd, levelStart, levelEnd, bfsVersion) << '\n'; 

	bfsVersion++;
	cout << "5 9 : " << graph.bidirectionalBFS(5, 9, queueStart, queueEnd, visitedStart, visitedEnd, levelStart, levelEnd, bfsVersion) << '\n'; 

	bfsVersion++;
	cout << "1 10 : " << graph.bidirectionalBFS(1, 10, queueStart, queueEnd, visitedStart, visitedEnd, levelStart, levelEnd, bfsVersion) << '\n'; 

	bfsVersion++;
	cout << "9 10 : " << graph.bidirectionalBFS(9, 10, queueStart, queueEnd, visitedStart, visitedEnd, levelStart, levelEnd, bfsVersion) << '\n'; 


	bfsVersion++;
	cout << "5 9 : " << graph.bidirectionalBFS(5, 9, queueStart, queueEnd, visitedStart, visitedEnd, levelStart, levelEnd, bfsVersion) << '\n'; 

	bfsVersion++;
	cout << "12 1 : " << graph.bidirectionalBFS(12, 1, queueStart, queueEnd, visitedStart, visitedEnd, levelStart, levelEnd, bfsVersion) << '\n'; 

	free(levelStart);
	free(levelEnd);
}