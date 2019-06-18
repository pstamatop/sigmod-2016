#include <cstdlib>
#include <cstring>
#include <ctime>

#include "Grail.h"

GrailNode::GrailNode() {
    min_rank = -1;
    rank = -1;
    parent = -1;
    iterator = 0;
    last = -1;
    getN = -1;
}   

bool GrailNode::visited() {
    if(min_rank < 0 && rank < 0)
        return false;
    else 
        return true;
}

Grail::Grail() {
    for(int i = 0 ; i < GRAIL ; i++){
        grailIndex_[i] = NULL;
        count_ = 0;
    }
}   

Grail::~Grail() {
    for(int i = 0 ; i < GRAIL ; i++)
        free(grailIndex_[i]);
    free(shuffledComps_);
} 

void Grail::init(int count) {
    count_ = count + 1; 
    for(int j = 0 ; j < GRAIL ; j++){
        grailIndex_[j] = (GrailNode*) malloc(sizeof(GrailNode) * (count + 1));
        for(int i = 0 ; i < count_ ; i++) {
            GrailNode* node = new GrailNode();
            memcpy(&grailIndex_[j][i], node, sizeof(GrailNode));
            delete node;
        }
    }
    shuffledComps_ = (int *) malloc((count) * sizeof(int));
}

void Grail::constrIndex(Hypergraph &hyperg, Stack &successors) {
    int dummy = -1, ncount, neighbor, last, index = 0, bufferIndex, parent, pminRank, cminRank, comp, scc;
    int min, total, iterator, backtrack, lastMin, n, version = 1;
    int *status = (int *) malloc(count_ * sizeof(int));
    
    memset(status , 0, count_ * sizeof(int));
    for(int i = 0 ; i < GRAIL ; i++){
        shuffleArray(shuffledComps_, count_ - 1);
        for(comp = 0 ; comp < count_ - 1 ; comp++){
            scc = shuffledComps_[comp];
            if(status[scc] == 0){ //if this node is unvisited
                successors.push(scc);
                status[scc] = version; //pushed in stack
                last = scc;
                while(1){
                    bufferIndex = hyperg.getListHead(last);
                    if(bufferIndex < 0)
                        ncount = 0;
                    else
                        ncount = hyperg.getTotalNodeCount(bufferIndex);
                    iterator = getIterator(i, last);
                    if(iterator < ncount){
                        neighbor = hyperg.getNeighbor(bufferIndex, iterator, getLast(i, last), getN(i, last));
                        incrIterator(i, last);
                        if(status[neighbor] != version){
                            setNode(i, neighbor, -1, last);
                            successors.push(neighbor);
                            status[neighbor] = version; //pushed in stack
                            last = neighbor;
                        }
                        else if(status[neighbor] == version){ //if neighbor is on stack
                            cminRank = getMinRank(i, neighbor);
                            if(cminRank < getMinRank(i, last) || getMinRank(i, last) < 0){
                                setMinRank(i, last, cminRank);
                            }
                        }
                    }
                    else{
                        if(successors.getCount() > 0){
                            n = successors.pop();
                            index++;
                            setRank(i, n, index);
                            if((getMinRank(i, n) > 0 && getMinRank(i, n) > index) || getMinRank(i, n) < 0)
                                setMinRank(i, n, index);    
                            parent = getParent(i, n);
                        }
                        backtrack = getParent(i, last);
                        if(backtrack != -1){
                            lastMin = getMinRank(i, last);
                            if(lastMin < getMinRank(i, backtrack) || getMinRank(i, backtrack) < 0)
                                setMinRank(i, backtrack, lastMin);
                                last = backtrack;
                        }
                        else{
                            break;
                        }
                    }
                }
            }
        }
    }
    free(status);
}

int Grail::pathExists(int id1, int id2) {
    bool flag = false;
    if(id1 > count_ || id2 > count_)
        return NO;
    for(int i = 0 ; i < GRAIL ; i++){
        int min_rank1 = grailIndex_[i][id1].min_rank;
        int min_rank2 = grailIndex_[i][id2].min_rank;
        int rank1 = grailIndex_[i][id1].rank;
        int rank2 = grailIndex_[i][id2].rank;
        if(!(min_rank2 >= min_rank1 && min_rank2 <= rank1 && rank2 >= min_rank1 && rank2 <= rank1))
            return NO;
    }
    return MAYBE;
}

void Grail::setNode(int i, int id, int index, int parent) {
    grailIndex_[i][id].rank = index;
    grailIndex_[i][id].min_rank = index;
    grailIndex_[i][id].parent = parent;
    grailIndex_[i][id].iterator = 0;
    grailIndex_[i][id].last = -1;
    grailIndex_[i][id].getN = -1;
}

int Grail::getRank(int i, int id) {
    return grailIndex_[i][id].rank;
}

int Grail::getMinRank(int i, int id) {
    return grailIndex_[i][id].min_rank;
}

void Grail::setRank(int i, int id, int rank) {
    grailIndex_[i][id].rank = rank;
}

void Grail::setMinRank(int i, int id, int minRank) {
    grailIndex_[i][id].min_rank = minRank;
}

void Grail::incrIterator(int i, int id) {
    grailIndex_[i][id].iterator++;
}

int Grail::getIterator(int i, int id) {
    return grailIndex_[i][id].iterator;
}

int Grail::getParent(int i, int id) {
    return grailIndex_[i][id].parent;
}

int& Grail::getLast(int i, int id) {
    return grailIndex_[i][id].last;
}

int& Grail::getN(int i, int id) {
    return grailIndex_[i][id].getN;
}


bool Grail::visited(int i, int id) {
    return grailIndex_[i][id].visited();
}

void Grail::setShuffledComps(int index, int value){
    shuffledComps_[index] = value;
}

void Grail::shuffleArray(int *array, int size){
    srand(time(NULL));
    int j, temp, i;
    for(i = size - 1; i > 0; i--){
        j = rand() % (i + 1);
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}