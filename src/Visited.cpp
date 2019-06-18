#include <cstdlib>
#include <cstring>

#include "Visited.h"

Visited::Visited() {
    size_ = 0;
    array_ = NULL;
}

Visited::~Visited() {
    if(array_ != NULL)
        free(array_);
}

void Visited::init(int size) {
    array_ = (int*) malloc(sizeof(int) * size);
    size_ = size;
    memset(array_ , 0, size_ * sizeof(int));
}
  
void Visited::expand(int newsize) {
    int temp = size_;
    while(temp < newsize)
        temp *= 2;
    array_ = (int*) realloc(array_, sizeof(int) * temp);
    memset(array_ + size_, 0, (temp-size_) * sizeof(int));
    size_ = temp;
}

void Visited::reset() {
    memset(array_ , 0, size_ * sizeof(int));
}
