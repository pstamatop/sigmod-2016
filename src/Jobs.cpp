#include <pthread.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "Jobs.h"
#include "sizes.h"

using namespace std;

pthread_cond_t batch; 
pthread_cond_t execute;
pthread_mutex_t qmtx;
pthread_mutex_t exmtx;
pthread_mutex_t tmtx;
pthread_mutex_t endmtx;
pthread_mutex_t thrmtx;

bool beginExecution_;
bool endExecution_;
int totalJobs;
int* results;
int resSize;
int position;

Job::Job(int id) {
    id_ = id;
    index_ = 0;
}

int Job::getId() {
    return id_;
}

void Job::setIndex(int index) {
    index_ = index;
}

DQuery::DQuery(DGraph *graph, int current_version, int id, int node1, int node2, Queue** qs, Queue** qe, Visited** vs, Visited** ve, int** ls, int** le, int version) : Job(id) {
    currentVersion_ = current_version;
    node1_ = node1;
    node2_ = node2;
    qs_ = qs;
    qe_ = qe;
    vs_ = vs;
    ve_ = ve;
    ls_ = ls;
    le_ = le;
    version_ = version;
    graph_ = graph;
}

void DQuery::run() {
    int res;
    res = graph_->bidirectionalBFS(node1_, node2_, *qs_[index_] , *qe_[index_], *vs_[index_], *ve_[index_], ls_[index_], le_[index_], version_, currentVersion_);
    results[id_] = res;
}

SQuery::SQuery(SGraph *graph, int id, int node1, int node2, Queue** qs, Queue** qe, Visited** vs, Visited** ve, int** ls, int** le, int version) : Job(id) {
    node1_ = node1;
    node2_ = node2;
    qs_ = qs;
    qe_ = qe;
    vs_ = vs;
    ve_ = ve;
    ls_ = ls;
    le_ = le;
    version_ = version;
    graph_ = graph;
}

void SQuery::run() {
    int res;
    res = graph_->bidirectionalBFS(node1_, node2_, *qs_[index_], *qe_[index_], *vs_[index_], *ve_[index_], ls_[index_], le_[index_], version_);
    results[id_] = res;
}

JobsQ::JobsQ(){
    count_ = 0;
    cursize_ = 0;
    size_ = JQUEUE;
    front_ = 0;
    rear_ = 0;
    queue_ = NULL;
    queue_ = (Job**) malloc(sizeof(Job*) * size_);
}

JobsQ::~JobsQ() {
    free(queue_);
}

void JobsQ::enqueue(Job *j) {
    if(cursize_ + 1 <= size_){
        queue_[rear_] = j;
        rear_ = rear_ + 1;
    }
    else{
        int initSize = size_;
        size_ = size_ * 2;
        queue_ = (Job**) realloc(queue_, sizeof(Job*) * size_);
        queue_[rear_] = j;
        rear_ = rear_ + 1;
    }
    cursize_++;
    count_++;
}

Job* JobsQ::dequeue(int &temp) {
    if(count_ == 0) return NULL;
    temp = front_;
    front_ = front_ + 1;
    count_--;
    if(count_ == 0){
        front_ = 0;
        rear_ = 0;
    }
    return queue_[temp];
}

void JobsQ::erase(int pos) {
    delete queue_[pos];
}

int JobsQ::getCount() {
    return count_;
}

bool JobsQ::isEmpty() {
    return count_ == 0;
}

JobScheduler::JobScheduler(int thread_num) {
    jobCount_ = 0;
    executionThreads_ = thread_num;
    beginExecution_ = false;
    endExecution_ = false;
    totalJobs = 1;
    position = 0;
    pthread_mutex_init(&qmtx, 0); 
    pthread_cond_init(&batch, 0);
    pthread_mutex_init(&exmtx, 0); 
    pthread_cond_init(&execute, 0); 
    pthread_mutex_init(&tmtx, 0);  
    pthread_mutex_init(&thrmtx, 0);
    tids_ = (pthread_t*) malloc(sizeof(pthread_t) * thread_num);
    resSize = RESSIZE;
    results = (int*) malloc(sizeof(int) * resSize);
    for(int i = 0 ; i < thread_num ; i++){
        if(pthread_create(&tids_[i], NULL, threadFunction, &jobs_) < 0)
            perror("Thread cannot be created.");
    }
}

JobScheduler::~JobScheduler() {
    pthread_mutex_destroy(&qmtx); 
    pthread_cond_destroy(&batch);
    pthread_mutex_destroy(&exmtx); 
    pthread_cond_destroy(&execute); 
    pthread_mutex_destroy(&tmtx); 
    pthread_mutex_destroy(&thrmtx);
    for(int i = 0 ; i < executionThreads_ ; i++){
        pthread_mutex_lock(&endmtx);
        endExecution_ = true;
        pthread_mutex_unlock(&endmtx);
        pthread_mutex_lock(&exmtx);
        beginExecution_ = true;
        pthread_mutex_unlock(&exmtx);
        pthread_cond_broadcast(&execute); 
    }
    free(tids_);
    free(results);
}

void JobScheduler::submitJob(Job *j) {
    jobs_.enqueue(j);
    jobCount_++;
    if(j->getId() >= resSize){
        resSize *= 2;
        results = (int*) realloc(results, sizeof(int) * resSize);
    }
}

void JobScheduler::executeAllJobs() {
    pthread_mutex_lock(&tmtx); 
    totalJobs = jobs_.getCount();
    pthread_mutex_unlock(&tmtx); 
    pthread_mutex_lock(&exmtx);
    beginExecution_ = true;
    pthread_mutex_unlock(&exmtx);
    pthread_cond_broadcast(&execute); 
}

void JobScheduler::waitAllTasksFinish() {
    pthread_mutex_lock(&tmtx); 
    while(totalJobs > 0){
        pthread_cond_wait(&batch, &tmtx);
    }
    pthread_mutex_unlock(&tmtx); 
    for(int i = 0 ; i < jobCount_ ; i++)
        cout << results[i] << endl;
    totalJobs = 1;
    jobCount_ = 0;
}

void *threadFunction(void *args) {
    JobsQ *queue = (JobsQ*) args;
    Job* j;
    int pos;
    int index;
    bool empty = false;
    pthread_mutex_lock(&thrmtx);
    index = position;
    position++;
    pthread_mutex_unlock(&thrmtx);
    while(1){
        pthread_mutex_lock(&exmtx);
        while(beginExecution_ == false)
            pthread_cond_wait(&execute,&exmtx); //wait for the condition
        pthread_mutex_unlock(&exmtx);
        pthread_mutex_lock(&endmtx);
        if(endExecution_ == true){
            pthread_mutex_unlock(&endmtx);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&endmtx);

        pthread_mutex_lock(&qmtx); 
        if(!queue->isEmpty()){
            j = queue->dequeue(pos);
            empty = false;          
        }
        else{
            if(queue->isEmpty()){ //if it is empty
                pthread_mutex_lock(&exmtx);
                beginExecution_ = false;
                pthread_mutex_unlock(&exmtx);
                empty = true;
            }
        }
        pthread_mutex_unlock(&qmtx); 
        if(empty == false){
            j->setIndex(index);
            j->run();
            pthread_mutex_lock(&qmtx); 
            queue->erase(pos);
            pthread_mutex_unlock(&qmtx); 
            pthread_mutex_lock(&tmtx); 
            totalJobs--;
            if(totalJobs == 0)
                pthread_cond_signal(&batch);
            pthread_mutex_unlock(&tmtx); 
        }
    }
}       
