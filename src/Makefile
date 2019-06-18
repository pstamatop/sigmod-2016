all: graph queue hash nodeIndexTest listNodeTest BFStest Stacktest CCtest conComponentsTest SCCtest Hypergraphtest Grailtest Hypergconstruction staticInitTest

graph: SGraph.o DGraph.o NodeIndex.o SBuffer.o DBuffer.o SListNode.o DListNode.o Queue.o Hashtable.o CC.o Stack.o SCC.o Grail.o Hypergraph.o Tarjantable.o Visited.o Jobs.o main.o
	g++ -O3 SGraph.o DGraph.o NodeIndex.o SBuffer.o DBuffer.o SListNode.o DListNode.o Queue.o Hashtable.o CC.o Stack.o SCC.o Grail.o Hypergraph.o Tarjantable.o Visited.o Jobs.o main.o -o graph -pthread

staticInitTest:SGraph.o DGraph.o NodeIndex.o SBuffer.o DBuffer.o SListNode.o DListNode.o Queue.o Hashtable.o CC.o Stack.o SCC.o Grail.o Hypergraph.o Tarjantable.o Visited.o staticInitTest.o
	g++ -O3 SGraph.o DGraph.o NodeIndex.o SBuffer.o DBuffer.o SListNode.o DListNode.o Queue.o Hashtable.o CC.o Stack.o  SCC.o Grail.o Hypergraph.o Tarjantable.o Visited.o staticInitTest.o -o staticInitTest

queue: Queue.o queueTest.o
	g++ -O3 Queue.o queueTest.o -o queue 

hash: Hashtable.o hashTest.o
	g++ -O3 Hashtable.o hashTest.o -o hash

nodeIndexTest: NodeIndex.o nodeIndexTest.o
	g++ -O3 NodeIndex.o nodeIndexTest.o -o nodeIndexTest

listNodeTest: SListNode.o Listnodetest.o
	g++ -O3 SListNode.o Listnodetest.o -o listNodeTest

BFStest: SGraph.o DGraph.o Visited.o NodeIndex.o SBuffer.o DBuffer.o SListNode.o DListNode.o Queue.o Hashtable.o CC.o Stack.o SCC.o Grail.o Hypergraph.o Tarjantable.o BFStest.o
	g++ -O3 SGraph.o DGraph.o Visited.o NodeIndex.o SBuffer.o DBuffer.o SListNode.o DListNode.o Queue.o Hashtable.o CC.o Stack.o SCC.o Grail.o Hypergraph.o BFStest.o Tarjantable.o -o BFStest

Stacktest: Stacktest.o Stack.o
	g++ -O3 Stacktest.o Stack.o -o Stacktest

CCtest: CC.o CCtest.o
	g++ -O3 CC.o CCtest.o -o CCtest

SCCtest: SCC.o NodeIndex.o SCCtest.o
	g++ -O3 SCC.o NodeIndex.o SCCtest.o -o SCCtest

conComponentsTest: Visited.o SGraph.o DGraph.o NodeIndex.o SBuffer.o DBuffer.o SListNode.o DListNode.o Queue.o Hashtable.o CC.o Stack.o SCC.o Grail.o Tarjantable.o Hypergraph.o conComponentsTest.o
	g++ -O3 Visited.o SGraph.o DGraph.o NodeIndex.o SBuffer.o DBuffer.o SListNode.o DListNode.o Queue.o Hashtable.o CC.o Stack.o SCC.o Grail.o Tarjantable.o Hypergraph.o conComponentsTest.o -o conComponentsTest

Hypergraphtest: Hypergraph.o NodeIndex.o SBuffer.o SListNode.o Stack.o Hashtable.o Hypergraphtest.o
	g++ -O3 Hypergraph.o NodeIndex.o SBuffer.o SListNode.o Stack.o Hashtable.o Hypergraphtest.o -o Hypergraphtest

Grailtest: Visited.o Grail.o Grailtest.o Stack.o Hashtable.o Hypergraph.o NodeIndex.o SBuffer.o SListNode.o
	g++ -O3 Visited.o Grail.o Grailtest.o Stack.o Hashtable.o Hypergraph.o NodeIndex.o SBuffer.o SListNode.o -o Grailtest

Hypergconstruction: SGraph.o Visited.o NodeIndex.o SBuffer.o SListNode.o Queue.o Hashtable.o CC.o Stack.o SCC.o Grail.o Hypergraph.o Tarjantable.o Hypergconstruction.o
	g++ -O3 SGraph.o Visited.o NodeIndex.o SBuffer.o SListNode.o Queue.o Hashtable.o CC.o Stack.o SCC.o Grail.o Hypergraph.o Tarjantable.o Hypergconstruction.o -o Hypergconstruction

SGraph.o: SGraph.cpp
	g++ -O3 -c SGraph.cpp

DGraph.o: DGraph.cpp
	g++ -O3 -c DGraph.cpp

NodeIndex.o: NodeIndex.cpp
	g++ -O3 -c NodeIndex.cpp

SBuffer.o: SBuffer.cpp
	g++ -O3 -c SBuffer.cpp

DBuffer.o: DBuffer.cpp
	g++ -O3 -c DBuffer.cpp

SListNode.o: SListNode.cpp
	g++ -O3 -c SListNode.cpp

DListNode.o: DListNode.cpp
	g++ -O3 -c DListNode.cpp

Queue.o : Queue.cpp
	g++ -O3 -c Queue.cpp

Hashtable.o: Hashtable.cpp
	g++ -O3 -c Hashtable.cpp

Stack.o: Stack.cpp
	g++ -O3 -c Stack.cpp

CC.o: CC.cpp
	g++ -O3 -c CC.cpp

SCC.o: SCC.cpp
	g++ -O3 -c SCC.cpp

Grail.o: Grail.cpp
	g++ -O3 -c Grail.cpp

Tarjantable.o: Tarjantable.cpp
	g++ -O3 -c Tarjantable.cpp

Hypergraph.o: Hypergraph.cpp
	g++ -O3 -c Hypergraph.cpp

conComponentsTest.o: conComponentsTest.cpp
	g++ -O3 -c conComponentsTest.cpp

main.o: main.cpp
	g++ -O3 -c main.cpp

queueTest.o: queueTest.cpp
	g++ -O3 -c queueTest.cpp

hashTest.o: hashTest.cpp
	g++ -O3 -c hashTest.cpp

nodeIndexTest.o: nodeIndexTest.cpp
	g++ -O3 -c nodeIndexTest.cpp

Listnodetest.o: Listnodetest.cpp
	g++ -O3 -c Listnodetest.cpp

BFStest.o: BFStest.cpp
	g++ -O3 -c BFStest.cpp

Stacktest.o: Stacktest.cpp
	g++ -O3 -c Stacktest.cpp

CCtest.o: CCtest.cpp
	g++ -O3 -c CCtest.cpp

SCCtest.o: SCCtest.cpp
	g++ -O3 -c SCCtest.cpp

Hypergraphtest.o: Hypergraphtest.cpp
	g++ -O3 -c Hypergraphtest.cpp

Grailtest.o: Grailtest.cpp
	g++ -O3 -c Grailtest.cpp

Hypergconstruction.o: Hypergconstruction.cpp
	g++ -O3 -c Hypergconstruction.cpp

Visited.o: Visited.cpp
	g++ -O3 -c Visited.cpp

staticInitTest.o: staticInitTest.cpp
	g++ -O3 -c staticInitTest.cpp

Jobs.o: Jobs.cpp
	g++ -O3 -c Jobs.cpp -pthread

clean:
	rm *o graph queue hash nodeIndexTest listNodeTest BFStest Stacktest CCtest SCCtest conComponentsTest Hypergraphtest Grailtest Hypergconstruction staticInitTest
