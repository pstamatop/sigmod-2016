#include "Graph.h"
#include "Queue.h"
#include "Hashtable.h"
#include "Stack.h"

#include <cstdlib>
#include <cstring>
#include <fstream>

void DGraph::insertNodes(int id1, int id2, int version) {
    int index;
    if(!nodeIndexOut_.searchNode(id1)){  //if it does not exist in the Index
        index = bufferOut_.allocNewNode(); //allocate node in buffer
        bufferOut_.setLastUsed(index); //update node's last used listnode
        nodeIndexOut_.insertNode(id1,index);
        versionOut_.insertNode(id1, version); // -1 because of insert's code
    }
    if(!nodeIndexIn_.searchNode(id2)){ //reverse DGraph
        index = bufferIn_.allocNewNode();
        bufferIn_.setLastUsed(index);
        nodeIndexIn_.insertNode(id2,index);
        versionIn_.insertNode(id2, version);
    }
}


void DGraph::insertEdge(int id1, int id2, int version) {
    this->insertNodes(id1,id2, version); //insert nodes in the Indices
    int index1 = nodeIndexOut_.getListHead(id1);
    int index2 = nodeIndexIn_.getListHead(id2);
    if(bufferOut_.getTotalNodeCount(index1) <= bufferIn_.getTotalNodeCount(index2)) { //search in the smallest list of neighbors
        if(!bufferOut_.searchNeighbor(index1,id2)){     
            bufferOut_.addEdge(index1, id2, version);
            bufferIn_.addEdge(index2, id1, version);
        }
    }
    else{
        if(!bufferIn_.searchNeighbor(index2,id1)){
            bufferOut_.addEdge(index1, id2, version);
            bufferIn_.addEdge(index2, id1, version);
        }
    }
}

int DGraph::BFS(Queue &queue, Visited &visit1, Visited &visit2, int *level1, int *level2, int &length, bool out, int comp, int end, int bfsVersion, int graphVersion, int& grandc){ //type = 0 for dynamic, 1 for static
    int id = -1, index = -1, count = -1, neighbor = -1, path, ncomp, cindex, property, prop;
    int dummy = -1 , len = -1 , minLen = -1, last = -1, temp = -1 , node = -1, lnCount = 0, insertVersion;
    bool flag = false, deadend = true;
    grandc = 0;
    while(queue.getCount() > 0 && queue.peekFrontLength() == length){
        id = queue.peekFrontId();
        if(out == true){
            index = nodeIndexOut_.getListHead(id);
            insertVersion = versionOut_.getListHead(id);
        }
        else{
            index = nodeIndexIn_.getListHead(id);
            insertVersion = versionIn_.getListHead(id);
        }
        if(index < 0 || insertVersion > graphVersion)
            count = 0; //No neighbors to check in the loop
        else{
            deadend = false; //there is no deadend
            do{
                if(out == true)
                    lnCount = bufferOut_.buffer_[index].count_;
                else
                    lnCount = bufferIn_.buffer_[index].count_;;
                for(int i = 0 ; i < lnCount ; i++){
                    if(out == true){
                        property = bufferOut_.buffer_[index].edgeProperty_[i];
                        neighbor = bufferOut_.buffer_[index].neighbor_[i];
                    }
                    else{
                        property = bufferIn_.buffer_[index].edgeProperty_[i];
                        neighbor = bufferIn_.buffer_[index].neighbor_[i];
                    }
                    if(property > graphVersion)
                        continue;
                    if(wcomponents_.areConnected(graphVersion, neighbor, end)){
                         if(visit1.array_[neighbor] != bfsVersion){ //check all neighbors of current level and keep the minimum length to the other side
                            if(visit2.array_[neighbor] == bfsVersion){
                                len = level2[neighbor];
                                if(flag == false || len < minLen)
                                    minLen = len;
                                flag = true;
                            }
                            queue.enqueue(neighbor, length + 1);
                            visit1.array_[neighbor] = bfsVersion;
                            level1[neighbor] = length + 1;
                            if(out == true){
                                cindex = nodeIndexOut_.getListHead(neighbor);
                                if(cindex >= 0){
                                    count = bufferOut_.buffer_[cindex].totalNodeCount_;
                                    grandc += count;
                                }
                            }
                            else{
                                cindex = nodeIndexIn_.getListHead(neighbor);
                                if(cindex >= 0){
                                    count = bufferIn_.buffer_[cindex].totalNodeCount_;
                                    grandc += count;
                                }
                            }
                        }
                    }
                }
                if(out == true)
                    index = bufferOut_.buffer_[index].nextListNode_;
                else
                    index = bufferIn_.buffer_[index].nextListNode_;
            }
            while(index >= 0);
        }
        queue.dequeue();
    }
    length++;
    if(deadend == true)
        minLen = -2;
    return minLen;
}
 
int DGraph::bidirectionalBFS(int start, int end, Queue &queueStart, Queue &queueEnd, Visited &visitedFromStart, Visited &visitedFromEnd, int *levelStart, int *levelEnd, int bfsVersion, int graphVersion){
    int comp1, comp2;
    int exists;
    int grandcOut = 0, grandcIn = 0;
    if(start == end)
        return 0;
    if(!nodeIndexOut_.searchNode(start) || !nodeIndexIn_.searchNode(end) || versionOut_.getListHead(start) > graphVersion || versionIn_.getListHead(end) > graphVersion)
        return -1;
    int max = getMaxIndexSize();
    //Check if array of visited nodes and array of levels need to be reallocated
    if(max > visitedFromStart.size_){
        visitedFromStart.expand(max);
        visitedFromEnd.expand(max);
        //Expand level-arrays as well
        int temp = visitedFromStart.size_;
        while(temp < max)
            temp *= 2;
        levelStart = (int*) realloc(levelStart, sizeof(int) * temp);
        levelEnd = (int*) realloc(levelEnd, sizeof(int) * temp);
    }
    if(!wcomponents_.areConnected(graphVersion, start, end)){ //maybe their weakly connencted components were connected after an addition
        return -1;
    }
    else{
        comp1 = wcomponents_.getComponent(start); 
        comp2 = wcomponents_.getComponent(end);
    }
    int lengthStart = 0 ,lengthEnd = 0;
    int queueStartL = 0, queueEndL = 0;
    int minLen = -1, shortest = -1;
    queueStart.enqueue(start, lengthStart);
    visitedFromStart.array_[start] = bfsVersion;
    levelStart[start] = lengthStart;
    queueEnd.enqueue(end, lengthEnd);
    visitedFromEnd.array_[end] = bfsVersion;
    levelEnd[end] = lengthEnd;
    while((queueStartL = queueStart.getCount()) > 0 && (queueEndL = queueEnd.getCount()) > 0){
        if((queueStartL + grandcOut) < (queueEndL + grandcIn)){ //run BFS in the smallest queue
            if((minLen = BFS(queueStart, visitedFromStart, visitedFromEnd, levelStart, levelEnd, lengthStart, true, comp2, end, bfsVersion, graphVersion, grandcOut)) >= 0){ //minLen = -1 shortest path not found yet
                shortest = lengthStart + minLen;                                                     
                break;
            }
        }
        else{
            if((minLen = BFS(queueEnd, visitedFromEnd, visitedFromStart, levelEnd, levelStart, lengthEnd, false, comp1, start, bfsVersion, graphVersion, grandcIn)) >= 0){//Send the component of the other end as an argument for checking grail index (if you are searching within a specific component comp1 equals to comp2) 
                shortest = lengthEnd + minLen;
                break;
            }
        }
        if(minLen == -2)   //minLen == -2 there is no path
            break;
    }
    queueStart.reset();
    queueEnd.reset();
    return shortest;
}


void DGraph::estimateConnectedComponents(Stack &stack, int conCompVersion){
    int dummy = -1, dummy2 = -1;
    int last = -1, node = -1; // for getNeighbor
    int count = 0, countIn, countOut, lnCount;
    int i, j, neighbor, indexIn, indexOut, n, maxsize;
    int nodes = nodeIndexOut_.getSize();
    if(nodeIndexOut_.size_ > nodeIndexIn_.size_)
        maxsize = nodeIndexOut_.size_;
    else
        maxsize = nodeIndexIn_.size_;
    wcomponents_.init(maxsize);
    if(visited.size_ < maxsize)
        visited.expand(maxsize);
    for(i = 0; i < nodes; i++){
        if(nodeIndexOut_.getListHead(i) < 0) //no neighbors
            continue;
        if(visited.array_[i] != conCompVersion){
            count++; // Start constructing new cc
            // Start DFS from i
            stack.push(i);
            while(stack.getCount() > 0){
                n = stack.pop();
                if(visited.array_[n] != conCompVersion){
                    visited.array_[n] = conCompVersion;
                    wcomponents_.insertCC(n, count, true);
                    // Push to stack all in and out vertices
                    indexOut = nodeIndexOut_.getListHead(n);
                    indexIn = nodeIndexIn_.getListHead(n);
                    if(indexOut < 0)
                        countOut = 0;
                    else{
                        do{
                            lnCount = bufferOut_.buffer_[indexOut].count_;
                            for(int i = 0 ; i < lnCount ; i++){
                                neighbor = bufferOut_.buffer_[indexOut].neighbor_[i];
                                if(visited.array_[neighbor] != conCompVersion)
                                    stack.push(neighbor);
                            }
                            indexOut = bufferOut_.buffer_[indexOut].nextListNode_;
                        }
                        while(indexOut >= 0);
                    }
                    if(indexIn < 0)
                        countIn = 0;
                    else{
                        do{
                            lnCount = bufferIn_.buffer_[indexIn].count_;
                            for(int i = 0 ; i < lnCount ; i++){
                                neighbor = bufferIn_.buffer_[indexIn].neighbor_[i];
                                if(visited.array_[neighbor] != conCompVersion)
                                    stack.push(neighbor);
                            }
                            indexIn = bufferIn_.buffer_[indexIn].nextListNode_;
                        }
                        while(indexIn >= 0);
                    }
                }
            }
        }
    }
    wcomponents_.setLastComponent(count);
    wcomponents_.initUpdate();
    stack.reset();
    visited.reset();
}

void DGraph::dynamicInit(int version) {
    Stack stack;
    int maxsize;
    if(visited.array_ == NULL){
        if(nodeIndexOut_.size_ > nodeIndexIn_.size_)
            maxsize = nodeIndexOut_.size_;
        else
            maxsize = nodeIndexIn_.size_;
        visited.init(maxsize);
    }
    this->estimateConnectedComponents(stack, version); //first call of estimateConnectedComponents
}

void DGraph::CCaddition(int version, int id1, int id2) {
    wcomponents_.insertNewEdge(version, id1, id2);
}

void DGraph::resetUpdate(int version, int pastVersions) {
    if(wcomponents_.rebuildIndexes(pastVersions))
        this->dynamicInit(version);
}

int DGraph::getMaxIndexSize() {
    if(nodeIndexOut_.size_ > nodeIndexIn_.size_)
        return nodeIndexOut_.size_;
    else
        return nodeIndexIn_.size_;
}


void DGraph::newVersion(int version) {
    wcomponents_.newVersion(version);
}
