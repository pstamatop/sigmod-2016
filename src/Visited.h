#ifndef VISITED_H
#define VISITED_H

class Visited{
public:
  Visited();
  ~Visited();
  void init(int);
  void expand(int);
  void reset();
  int* array_;
  int size_;
};

#endif
