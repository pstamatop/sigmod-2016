#include <pthread.h>

#include "Graph.h"
#include "sizes.h"

class Job {
public:
     Job(int);
     virtual ~Job() {};
     virtual void run() = 0;
     int getId();
     void setIndex(int);
protected:
    int id_;
    int index_;
};

class DQuery : public Job {
public:
    DQuery(DGraph*, int, int, int, int, Queue**, Queue**, Visited**, Visited**, int**, int**, int);
    ~DQuery(){};
    void run();
private:
    DGraph* graph_;
    int currentVersion_;
    int node1_;
    int node2_;
    Queue** qs_;
    Queue** qe_;
    Visited** vs_;
    Visited** ve_;
    int** ls_;
    int** le_;
    int version_;
};

class SQuery : public Job {
public:
    SQuery(SGraph*, int, int, int, Queue**, Queue**, Visited**, Visited**, int**, int**, int);
    ~SQuery(){};
    void run();
private:
    SGraph* graph_;
    int node1_;
    int node2_;
    Queue** qs_;
    Queue** qe_;
    Visited** vs_;
    Visited** ve_;
    int** ls_;
    int** le_;
    int version_;
};

class JobsQ {
public:
    JobsQ();
    ~JobsQ();
    void enqueue(Job *);
    Job* dequeue(int &);
    void erase(int);
    int getCount();
    bool isEmpty();
private:
    Job** queue_;
    int size_;
    int cursize_;
    int count_;
    int front_;
    int rear_;
};

class JobScheduler {
public:
    JobScheduler(int);
    ~JobScheduler();
    void submitJob(Job *);
    void executeAllJobs();
    void waitAllTasksFinish();
    JobsQ jobs_;
private:
    int jobCount_;
    int executionThreads_;
    pthread_t* tids_;
    int* results_;
};

void *threadFunction(void *);