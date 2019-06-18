#include <cstdlib>

#include "CC.h"

UpdateIndex::UpdateIndex() {
    updateTable_ = (int**) malloc(sizeof(int*) * (VERSIONS));
    for(int i = 0 ; i < VERSIONS ; i++)
        updateTable_[i] = NULL;
    count_ = (int*) malloc(sizeof(int) * (VERSIONS));
    size_ = (int*) malloc(sizeof(int) * (VERSIONS));
    currentNum_ = 1;
    lastComponent_ = 0;
    maxVersions_ = VERSIONS;
    versions_ = -1; //this will be 0 after the initial call, which is what we want
    versionsCreated_ = -1;
    pastVersions_ = 0;
}

UpdateIndex::~UpdateIndex() {
    for(int i = 0 ; i <= versionsCreated_ ; i++)
        free(updateTable_[i]);
    free(size_);
    free(count_);
    free(updateTable_);
}

void UpdateIndex::init(int i) { //initialises the specific version, at initial call from Graph it initialises the first one, see : CC::initUpdate()
    if(i!=0)
        i = i - pastVersions_;
    if(versionsCreated_ + 1 >= maxVersions_)
        expandWhole();
    versions_++;
    if(versionsCreated_ < i){
        size_[i] = lastComponent_+1;
        count_[i] = lastComponent_+1;
        updateTable_[i] = (int*) malloc(sizeof(int) * (size_[i]));
        versionsCreated_++;
    }
    else if(size_[i] < lastComponent_+1){
        size_[i] = lastComponent_+1;
        count_[i] = lastComponent_+1;
        updateTable_[i] = (int*) realloc(updateTable_[i], sizeof(int) * (size_[i]));
    }
    else
        count_[i] = lastComponent_+1;
    if(i == 0){
        initArray(0, 0, size_[i]);
    }
    else{
        for(int p = 0 ; p < size_[i] ; p++)
            updateTable_[i][p] = updateTable_[i-1][p];
    }
}

void UpdateIndex::expandVersion(int i) { //expands specific version
    if(i!=0)
        i = i - pastVersions_;
    int newCount = lastComponent_ + 1;
    count_[i] = lastComponent_+1;
    if(newCount > size_[i]){
        int temp = size_[i];
        while(temp <= newCount)
            temp *= 2;
        updateTable_[i] = (int *) realloc(updateTable_[i], sizeof(int) * temp);
        initArray(i, size_[i], temp);
        size_[i] = temp;
    }
}

void UpdateIndex::expandWhole() {
    maxVersions_ *= 2;
    updateTable_ = (int**) realloc(updateTable_, sizeof(int*) * maxVersions_);
    size_ = (int*) realloc(size_, sizeof(int) * maxVersions_);
    count_ = (int*) realloc(count_, sizeof(int) * maxVersions_);
}

void UpdateIndex::addPair(int version, int id1, int id2) {
    if(version !=0 )
        version = version - pastVersions_;
    if(updateTable_[version][id1] == -1 && updateTable_[version][id2] == -1) {
        updateTable_[version][id1] = updateTable_[version][id2] = currentNum_;
        currentNum_ = currentNum_ + 1;
    }
    else if(updateTable_[version][id1] == -1){
        updateTable_[version][id1] = updateTable_[version][id2];
    }
    else if(updateTable_[version][id2] == -1){
        updateTable_[version][id2] = updateTable_[version][id1];
    }
    else{
        int temp = updateTable_[version][id1];
        for(int i = 0 ; i < count_[version] ; i++){
            if(updateTable_[version][i] == temp){
                updateTable_[version][i] = updateTable_[version][id2];
            }
        }
    }
}

bool UpdateIndex::inPair(int version, int id1, int id2) {
    if(version !=0 )
        version = version - pastVersions_;
    if(id1 >= count_[version] || id2 >= count_[version])
        return false;
    if(updateTable_[version][id1] == -1 || updateTable_[version][id2] == -1)
        return false;
    return (updateTable_[version][id1] == updateTable_[version][id2]);
}

void UpdateIndex::reset() {
    initArray(0, 0, lastComponent_+1);
    currentNum_ = 0;
    lastComponent_ = 0;
    versions_ = -1;
}

void UpdateIndex::initArray(int version, int start, int end){
    for(int i = start; i < end; i++)
        updateTable_[version][i] = -1;
}

void UpdateIndex::setLastComponent(int last) {
    lastComponent_ = last;
}

void UpdateIndex::endBatch(int pastVersions) {
    if(versions_ > 0){
        expandVersion(0);
        for(int i = 0 ; i <= lastComponent_ ; i++)
            updateTable_[0][i] = updateTable_[versions_][i];
    }
    pastVersions_ = pastVersions;
    versions_ = 0;
}

CC::CC() {
    ccIndex_ = (int*) malloc(INDEX * sizeof(int));
    initArray(0, INDEX);
    size_ = INDEX;
    count_ = 0;
    metric_ = 0.0;
    succ_queries_ = 0;
    queries_ = 0;
}

CC::CC(int size) {
    ccIndex_ = (int*) malloc(size * sizeof(int));
    size_ = size;
    initArray(0, size_);
    count_ = 0;
    metric_ = 0.0 ;
    succ_queries_ = 0;
    queries_ = 0;
}

CC::~CC() {
    free(ccIndex_);
}

void CC::init(int size) {
    if(size > size_){
        ccIndex_ = (int*) realloc(ccIndex_, size * sizeof(int));
        initArray(0, size);
        size_ = size;
    }
}

int CC::getCount(){
    return count_;
}

int CC::getSize(){
    return size_;
}

void CC::insertCC(int id, int component, bool newcomp) {
     if (id + 1 > size_){
        int temp = size_;
        while(temp <= id)
            temp *= 2;
        ccIndex_ = (int *) realloc(ccIndex_, sizeof(int) * temp);
        initArray(size_, temp);
        size_ = temp;
    }
    ccIndex_[id] = component;
    if(newcomp){
        count_ ++;
        lastComponent_ = component;
    }
}

int CC::searchCC(int id) {
    if(id >= size_)
        return -1;
    else
        return ccIndex_[id];
}

void CC::insertNewEdge(int version, int id1, int id2) {
    int comp1, comp2;
    bool direct = false;
    comp1 = searchCC(id1);
    comp2 = searchCC(id2);
    if(comp1 < 0 && comp2 >= 0){
        insertCC(id1, comp2, false);
        comp1 = comp2;
    }
    else if(comp2 < 0 && comp1 >= 0){
        insertCC(id2, comp1, false);
        comp2 = comp1;
    }
    else if(comp1 < 0 && comp2 < 0){
        lastComponent_ = lastComponent_ + 1;
        insertCC(id1, lastComponent_, true);
        insertCC(id2, lastComponent_, true);
        comp1 = comp2;
        updateIndex_.setLastComponent(lastComponent_);
        updateIndex_.expandVersion(version);
    }
    if(comp1 != comp2 && !updateIndex_.inPair(version, comp1, comp2))
        updateIndex_.addPair(version, comp1, comp2);
}

bool CC::areConnected(int version, int id1, int id2) {
    int comp1, comp2;
    bool dummy, retvalue = false;
    queries_ ++;
    comp1 = searchCC(id1);
    comp2 = searchCC(id2);
    if(comp1 < 0 || comp2 < 0 ){
        return false;
    }
    else if(comp1 != comp2){
        retvalue = updateIndex_.inPair(version, comp1, comp2);
        if(retvalue == true)
            succ_queries_ ++;
        return retvalue;
    }
    else
        return true;
}

bool CC::rebuildIndexes(int pastVersions) { //when called, it checks if the structure must be rebuilt
    metric_ = (float) succ_queries_ / queries_; //if it must, it resets the UpdateTable and returns a value to the calling function
    if(metric_ >= BOTTOM ){ //indicating that the components must be reestimated (by dfs)
        updateIndex_.endBatch(pastVersions); 
        updateIndex_.reset();
        initArray(0, size_);
        succ_queries_ = 0;
        queries_ = 0;
        count_ = 0;
        metric_ = 0;
        return true;        
    }
    updateIndex_.endBatch(pastVersions); 
    return false;
}

int CC::getComponent(int index){
    return ccIndex_[index];
}

void CC::initArray(int start, int end){
    for(int i = start; i < end; i++)
        ccIndex_[i] = -1;
}

void CC::setLastComponent(int comp) {
    lastComponent_ = comp;
}

void CC::initUpdate() {
    updateIndex_.setLastComponent(lastComponent_);
    updateIndex_.init(0);
}

void CC::newVersion(int version) {
    updateIndex_.init(version);
}
