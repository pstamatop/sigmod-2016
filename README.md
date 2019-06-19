## ACM SIGMOD 2016 Programming Contest

Project for the Software Development for Information Systems course

Specifications: https://dsg.uwaterloo.ca/sigmod16contest/task.html

## Description

Given both dynamic and static graphs of millions of nodes and edges, the task was to answer to queries for shortest paths. The unweighted directed graphs were represented by adjacency lists. The initial calculation was completed using bidirectional-BFS but in order to speed up the process we also calculated the graph's connected components, its strong connected components using Tarjan's (iterative) algorithm and a Grail index (probabilistic data structure for reachability queries). The program is also multithreaded using POSIX threads.

Tarjan's algorithm: https://en.wikipedia.org/wiki/Tarjan's_strongly_connected_components_algorithm

Grail Index: http://www.vldb.org/pvldb/vldb2010/pvldb_vol3/R24.pdf



## Team

https://github.com/pstamatop

https://github.com/isabellems
