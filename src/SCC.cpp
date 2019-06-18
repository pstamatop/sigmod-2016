#include <cstdlib>
#include <cstring>
#include <iostream>

#include "SCC.h"

using namespace std;

ComponentCursor::ComponentCursor() {
    index = 0;
}

void ComponentCursor::reset() {
    index = 0;
}

Component::Component(int id) {
    id_ = id;
    count_ = 0;
    size_ = COMPNODES;
    nextIndex_ = -1;
    lastUsed_ = -1;
    totalIncludedNodes_ = 0;
}

bool Component::addNode(int id) {
    if(count_ == COMPNODES) return false;
    includedNodes_[count_] = id;
    count_ ++;
    return true;
}

int Component::getId() {
    return id_;
}

int Component::getCount() {
    return count_;
}

int Component::getSize() {
    return size_;
}

void Component::print() {
    for(int i = 0 ; i < count_ ; i++){
        cout << includedNodes_[i] << " ";
    }
}

int Component::getLastUsed() {
    return lastUsed_;
}

void Component::setLastUsed(int lastused) {
    lastUsed_ = lastused;
}

int Component::getNextIndex() {
    return nextIndex_;
}

void Component::setNextIndex(int index) {
    nextIndex_ = index;
}

void Component::incrTotalIncludedNodes() {
    totalIncludedNodes_ = totalIncludedNodes_ + 1;
}

int Component::getTotalIncludedNodes() {
    return totalIncludedNodes_;
}

int Component::getNode(int i) {
    return includedNodes_[i];
}


SCC::SCC() {
    components_ = (Component*) malloc(sizeof(Component) * COMPONENTS);
    compCount_ = 0;
    count_ = 0;
    belongsToComponent_ = NULL;
    size_ = COMPONENTS;
}

SCC::~SCC() {
    free(components_);
    if(belongsToComponent_ != NULL)
        free(belongsToComponent_);
}

void SCC::init(int indexsize) {
    belongsToComponent_ = (int*) malloc(sizeof(int) * indexsize);
    memset(belongsToComponent_, 0 , indexsize * sizeof(int));
    arraySize_ = indexsize;
}

void SCC::addComponent(int id, bool flag) { // if flag==true we are adding a new component, if not we are adding an extension
    if(flag== true && sccIndex_.searchNode(id))
        return;
    if(count_ + 1 > size_){
        size_ *= 2;
        components_ = (Component*) realloc(components_, sizeof(Component) * size_);
;   } 
    Component *comp = new Component(id);
    count_ ++;
    memcpy(&components_[count_-1], comp, sizeof(Component));
    delete comp;
    if(flag){
        sccIndex_.insertNode(id, count_-1);
        compCount_ ++;
    }
}

int SCC::searchComponent(int id) {
    return sccIndex_.getListHead(id);
}

bool SCC::addNode(int id, int comp) {
    int component =  sccIndex_.getListHead(comp);
    int lastused = -1;
    if(component >= 0){
        if(components_[component].getCount() == 0)
            components_[component].setLastUsed(component);
        lastused = components_[component].getLastUsed();
        if(!components_[lastused].addNode(id)){
            this->addComponent(-1, false);
            components_[lastused].setNextIndex(count_-1);
            components_[component].setLastUsed(count_-1);
            components_[count_-1].addNode(id);
        }
        else
            components_[lastused].setLastUsed(component);
        components_[component].incrTotalIncludedNodes();
        if(id + 1 > arraySize_){
            int temp = arraySize_;
            while(temp <= id)
                temp *= 2;
            belongsToComponent_ = (int*) realloc(belongsToComponent_, sizeof(int) * temp);
        }
        belongsToComponent_[id] = comp;
        return true;
    }
    else
        return false;
}

void SCC::printCompNodes(int comp) {
    int component = searchComponent(comp);
    if(component >= 0){
        int next = component;
        do{
            components_[next].print();
            next = components_[next].getNextIndex();
        }
        while(next!=-1);
    }
    else
        cout << "Component doens't exist." << endl;
}

int SCC::getCount() {
    return count_;
}

void SCC::iterateSCC() {
    compCursor_.reset();
}

bool SCC::nextSSC() {
    if(compCursor_.index + 1 < count_) {
        compCursor_.index = compCursor_.index + 1;
        while(components_[compCursor_.index].getId() < 0){  //While this component is an extension 
            compCursor_.index = compCursor_.index + 1;      //of another
            if(compCursor_.index >= count_)
                return false;
        }
        return true;
    }
    else
        return false;
}

Component* SCC::getCurrentSCC() {
    if(compCursor_.index < count_)
        return &components_[compCursor_.index];
    return NULL;
}

int SCC::belongsToComponent(int id) {
    return belongsToComponent_[id];
}

int SCC::getNode(int index, int i, int& last , int& cur) {
    int tempnode = i / COMPNODES;
    int node = i % COMPNODES;
    if(i == 0){
       last = index;
       cur = tempnode;
    }
    index = last;
    if(tempnode != cur){
        index = components_[last].getNextIndex();
    }
    last = index;
    cur = tempnode;
    return components_[last].getNode(node);
}

int SCC::getTotalIncludedNodes(int comp) {
    return components_[comp].getTotalIncludedNodes();
}

int SCC::getCompCount() {
    return compCount_;
}
