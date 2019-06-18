#include "Graph.h"
#include "Queue.h"
#include "Hashtable.h"
#include "Stack.h"

#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

void SGraph::insertNodes(int id1,int id2) {
    int index;
    if(!nodeIndexOut_.searchNode(id1)){  //if it does not exist in the Index
        index = bufferOut_.allocNewNode(); //allocate node in buffer
        bufferOut_.setLastUsed(index); //update node's last used listnode
        nodeIndexOut_.insertNode(id1,index);
    }
    if(!nodeIndexIn_.searchNode(id2)){ //reverse DGraph
        index = bufferIn_.allocNewNode();
        bufferIn_.setLastUsed(index);
        nodeIndexIn_.insertNode(id2,index);
    }
}


void SGraph::insertEdge(int id1, int id2) {
    this->insertNodes(id1,id2); //insert nodes in the Indices
    int index1 = nodeIndexOut_.getListHead(id1);
    int index2 = nodeIndexIn_.getListHead(id2);
    int dummy = 0;
    if(bufferOut_.getTotalNodeCount(index1) <= bufferIn_.getTotalNodeCount(index2)) { //search in the smallest list of neighbors
        if(!bufferOut_.searchNeighbor(index1,id2)){
            bufferOut_.addEdge(index1, id2);
            bufferIn_.addEdge(index2, id1);
        }
    }
    else{
        if(!bufferIn_.searchNeighbor(index2,id1)){
            bufferOut_.addEdge(index1, id2);
            bufferIn_.addEdge(index2, id1);
        }
    }
}

int SGraph::BFS(Queue &queue, Visited &visit1, Visited &visit2, int *level1, int *level2, int &length, bool out, int mode, int comp, int bfsVersion, int& grandc){ //type = 0 for dynamic, 1 for static
    int id = -1, index = -1, count = -1, neighbor = -1, path, ncomp, cindex;
    int dummy = -1 , len = -1 , minLen = -1, last = -1, temp = -1 , node = -1, lnCount = 0;;
    bool flag = false, deadend = true;
    grandc = 0;
    while(queue.getCount() > 0 && queue.peekFrontLength() == length){
        id = queue.peekFrontId();
        if(out == true)
            index = nodeIndexOut_.getListHead(id);
        else
            index = nodeIndexIn_.getListHead(id);
        if(index < 0)
            count = 0; //No neighbors to check in the loop
        else{
            deadend = false; //there is no deadend
            do{
                if(out == true)
                        lnCount = bufferOut_.buffer_[index].count_;
                else
                    lnCount = bufferIn_.buffer_[index].count_;;
                for(int i = 0 ; i < lnCount ; i++){
                    if(out == true)
                        neighbor = bufferOut_.buffer_[index].neighbor_[i];
                    else
                        neighbor = bufferIn_.buffer_[index].neighbor_[i];
                    if(mode == 1 && scomponents_.belongsToComponent(neighbor) == comp){
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
                    else if(mode == 0){
                        ncomp = scomponents_.belongsToComponent(neighbor);
                        if(out == true)
                            path = grailIndexOut_.pathExists(ncomp, comp);
                        else
                            path = grailIndexIn_.pathExists(ncomp, comp);
                        if(path == MAYBE){
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
 
int SGraph::bidirectionalBFS(int start, int end, Queue &queueStart, Queue &queueEnd, Visited &visitedFromStart, Visited &visitedFromEnd, int *levelStart, int *levelEnd, int bfsVersion){//type = 0 for dynamic, 1 for static
    int mode;
    int comp1, comp2;
    int exists;
    int grandcOut = 0, grandcIn = 0;
    //Check if array of visited nodes and array of levels need to be reallocated
    if(start == end)
        return 0;
    int max = getMaxIndexSize();
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
    if((comp1 = scomponents_.belongsToComponent(start)) == (comp2 = scomponents_.belongsToComponent(end)))
        mode = 1;
    else{
        if(grailIndexOut_.pathExists(comp1, comp2) == MAYBE || grailIndexIn_.pathExists(comp2, comp1) == MAYBE)
            mode = 0; //search whole graph
        else{
            return -1;
        }
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
            if((minLen = BFS(queueStart, visitedFromStart, visitedFromEnd, levelStart, levelEnd, lengthStart, true, mode, comp2, bfsVersion, grandcOut)) >= 0){ //minLen = -1 shortest path not found yet
                shortest = lengthStart + minLen;                                                     
                break;
            }
        }
        else{
            if((minLen = BFS(queueEnd, visitedFromEnd, visitedFromStart, levelEnd, levelStart, lengthEnd, false, mode, comp1, bfsVersion, grandcIn)) >= 0){//Send the component of the other end as an argument for checking grail index (if you are searching within a specific component comp1 equals to comp2) 
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


void SGraph::createHypergraph() {
    int index, last, cur;
    int nindex, nlast, ncur;
    int dummy = -1, node = 0, neighbor, comp;
    int total, ntotal, lnCount, version1 = 1, version2 = 1;
    int count = scomponents_.getCompCount();
    ofstream grailtest;
    int *vis = (int*) malloc((count + 1) * sizeof(int));
    memset(vis , 0, (count + 1) * sizeof(int));
    // if(count == getMaxIndexCount()){
    //     for(int k = 1 ; k <= count ; k++){
    //         hypergOut_.insertSCC(k);
    //         hypergIn_.insertSCC(k);
    //     }
    //     return;
    // }
    for(int i = 1; i <= count ; i++){
        index = scomponents_.searchComponent(i);
        total = scomponents_.getTotalIncludedNodes(index);
        for(int j = 0 ; j < total ; j++){
            node = scomponents_.getNode(index, j, last, cur);
            nindex = nodeIndexOut_.getListHead(node);
            if(nindex < 0)
                ntotal = 0;
            else{
                ntotal = bufferOut_.getTotalNodeCount(nindex);
               for(int k = 0 ; k < ntotal ; k++){
                    neighbor = bufferOut_.getNeighbor(nindex, k, nlast, ncur);
                    comp = scomponents_.belongsToComponent(neighbor);
                    if(comp!=i && visited.array_[comp] != version1){
                        hypergOut_.insertEdge(i, comp);
                        visited.array_[comp] = version1;
                    }
                }
            }
            nindex = nodeIndexIn_.getListHead(node);
            if(nindex < 0)
                ntotal = 0;
            else{
               ntotal = bufferIn_.getTotalNodeCount(nindex);
               for(int k = 0 ; k < ntotal ; k++){
                    neighbor = bufferIn_.getNeighbor(nindex, k, nlast, ncur);
                    comp = scomponents_.belongsToComponent(neighbor);
                    if(comp!=i && vis[comp] != version2){
                        hypergIn_.insertEdge(i, comp);
                        vis[comp] = version2;
                    }
                }
            }
        }
        version1++;
        version2++;
    }
    free(vis);
}


 void SGraph::createSCC(int size) {
    scomponents_.init(size);
 }

 void SGraph::addSCC(int id) {
    scomponents_.addComponent(id, true);
 }

void SGraph::addNodeSCC(int id, int comp) {
    scomponents_.addNode(id, comp);
}

void SGraph::estimateStronglyConnectedComponents(Stack &successors){
    int index = 0, i, indexOut, countScc = 0;
    int n, last, iterator, neighbIndex, lastLow, countOut, neighbor, backtrack, node;
    int nodes;
    successors.reset();
    if(nodeIndexOut_.getSize() <= nodeIndexIn_.getSize())
        nodes = nodeIndexOut_.getSize();
    else
        nodes = nodeIndexIn_.getSize();
    int* status = (int*) malloc(sizeof(int) * nodes); // 0: unvisited, 1: visited, 2: stacked
    memset(status , 0, nodes * sizeof(int));
    tarjanTable_.tarjanTableInit(nodes);
    for(node = 0; node < nodes; node++){
        if(nodeIndexOut_.getListHead(node) < 0) //no neighbors
            continue;
        if(status[node] == 0){ //if node is unvisited
            tarjanTable_.setNode(node, index, -1); // -1: parent
            successors.push(node);
            status[node] = 2;
            last = node;
            index++;
            
            while(true){
                indexOut = nodeIndexOut_.getListHead(last);
                if(indexOut < 0){
                    countOut = 0;
                }
                else{
                    countOut = bufferOut_.getTotalNodeCount(indexOut);
                }
                iterator = tarjanTable_.getIterator(last);
                if(iterator < countOut){
                    neighbor = bufferOut_.getNeighbor(indexOut, iterator, tarjanTable_.getLast(last), tarjanTable_.getN(last));
                    tarjanTable_.incrIterator(last);
                    if(status[neighbor] == 0){ //if neighbor is unvisited
                        tarjanTable_.setNode(neighbor, index, last);
                        successors.push(neighbor);
                        status[neighbor] = 2;
                        index++;
                        last = neighbor;
                    }
                    else if(status[neighbor] == 2){ //if neighbor is on stack
                        neighbIndex = tarjanTable_.getIndex(neighbor);
                        if(neighbIndex < tarjanTable_.getLowlink(last))
                            tarjanTable_.setLowlink(last, neighbIndex);
                    }
                }
                else{
                    if(tarjanTable_.getLowlink(last) == tarjanTable_.getIndex(last)){
                        countScc++;
                        addSCC(countScc);
                        do{
                            n = successors.pop();
                            status[n] = 1;
                            addNodeSCC(n, countScc);
                        } while(n != last);
                    }
                    backtrack = tarjanTable_.getParent(last);
                    if(backtrack != -1){
                        lastLow = tarjanTable_.getLowlink(last);
                        if(lastLow < tarjanTable_.getLowlink(backtrack))
                            tarjanTable_.setLowlink(backtrack, lastLow);
                            last = backtrack;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
    free(status);
}

void SGraph::staticInit() {
    int scccount;
    Stack successors, recStack;
    Visited vis;
    int max = getMaxIndexSize();
    scomponents_.init(max);
    this->estimateStronglyConnectedComponents(successors);
    scccount = scomponents_.getCompCount();
    vis.init(scccount+1);
    visited.init(scccount+1);
    this->createHypergraph();
    grailIndexOut_.init(scccount);
    grailIndexIn_.init(scccount);
    copySccs();
    grailIndexOut_.constrIndex(hypergOut_, successors);
    grailIndexIn_.constrIndex(hypergIn_, successors);
}

int SGraph::getMaxIndexSize() {
    if(nodeIndexOut_.size_ > nodeIndexIn_.size_)
        return nodeIndexOut_.size_;
    else
        return nodeIndexIn_.size_;
}

int SGraph::getMaxIndexCount() {
    if(nodeIndexOut_.count_ > nodeIndexIn_.count_)
        return nodeIndexOut_.count_;
    else
        return nodeIndexIn_.count_;
}

int SGraph::getCompCount() {
    return scomponents_.getCompCount();
}

void SGraph::visitedInit(int size) {
    visited.init(size);
}

void SGraph::copySccs(){
    int sccs = getCompCount();
    for(int i = 0; i < sccs; i++){
        grailIndexIn_.setShuffledComps(i, i + 1);
        grailIndexOut_.setShuffledComps(i, i + 1);
    }
}
