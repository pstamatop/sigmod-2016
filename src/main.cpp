#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Jobs.h"

#define MAX 100

using namespace std;

int main(int argc, char *argv[]) {
    int id1, id2, path;
    int type;
    int queryId = 0;
    char line[MAX],command, strtype[20];

    ifstream input(argv[1]);
    ifstream workload(argv[2]);

    if(!input || !workload){
        cout << "Failed to open files" << endl;
        return -1;
    }

    workload >> strtype;
    if(!strcmp(strtype, "STATIC"))
        type = 1;
    else if(!strcmp(strtype, "DYNAMIC"))
        type = 0;
    else{
        cout << "Unkown type of graph: \"" << command <<"\"." << endl;
        return -1;
    }

    JobScheduler* scheduler = new JobScheduler(THREADS);
    Visited* visitedStart[THREADS];
    Visited* visitedEnd[THREADS];
    Queue* queueStart[THREADS];
    Queue* queueEnd[THREADS];
    int* levelStart[THREADS];
    int* levelEnd[THREADS];
    int bfsVersion = 0;

    if(type == 1){
        SGraph graph;
        SQuery *q;
        while(input.getline(line, MAX)){
            if(strcmp(line, "S") && strcmp(line, "\n")){
                sscanf(line, "%d %d", &id1, &id2);
                graph.insertEdge(id1, id2);   
            }
        }
        graph.staticInit();
        int maxSize = graph.getMaxIndexSize();
        for(int i = 0 ; i < THREADS ; i++){
            queueStart[i] = new Queue();
            queueEnd[i] = new Queue();
            visitedStart[i] = new Visited();
            visitedStart[i]->init(maxSize);
            visitedEnd[i] = new Visited();
            visitedEnd[i]->init(maxSize);
            levelStart[i] = (int *) malloc(maxSize * sizeof(int));
            levelEnd[i] = (int *) malloc(maxSize * sizeof(int));
        }
        while(workload.getline(line,MAX)){
            sscanf(line,"%c %d %d", &command, &id1, &id2);
            if(command == 'F'){
                scheduler->executeAllJobs();
                scheduler->waitAllTasksFinish();
                queryId = 0;
            }
            else if(command == 'Q'){
                bfsVersion++;
                q = new SQuery(&graph, queryId, id1, id2, queueStart, queueEnd, visitedStart, visitedEnd, levelStart, levelEnd, bfsVersion);
                scheduler->submitJob(q);
                queryId++;
            }
        }
    }
    else{
        DGraph graph;
        DQuery *q;
        int version = 1;
        int current_version = 0;
        int previous_command = 2;
        while(input.getline(line, MAX)){
            if(strcmp(line, "S") && strcmp(line, "\n")){
                sscanf(line, "%d %d", &id1, &id2);
                graph.insertEdge(id1, id2, current_version);   
            }
        }
        graph.dynamicInit(version);
        int maxSize = graph.getMaxIndexSize();
        for(int i = 0 ; i < THREADS ; i++){
            queueStart[i] = new Queue();
            queueEnd[i] = new Queue();
            visitedStart[i] = new Visited();
            visitedStart[i]->init(maxSize);
            visitedEnd[i] = new Visited();
            visitedEnd[i]->init(maxSize);
            levelStart[i] = (int *) malloc(maxSize * sizeof(int));
            levelEnd[i] = (int *) malloc(maxSize * sizeof(int));
        }
        while(workload.getline(line,MAX)){
            sscanf(line,"%c %d %d", &command, &id1, &id2);
            if(command == 'F'){
                scheduler->executeAllJobs();
                scheduler->waitAllTasksFinish();
                queryId = 0;
                version++;
                graph.resetUpdate(version, current_version);
            }
            else if(command == 'A'){
                if(previous_command == 1){
                    current_version++;
                    graph.newVersion(current_version);
                }
                previous_command = 0;
                graph.insertEdge(id1, id2, current_version);
                graph.CCaddition(current_version, id1, id2);
            }
            if(command == 'Q'){
                if(previous_command == 0)
                    previous_command = 1;
                bfsVersion++;
                q = new DQuery(&graph, current_version, queryId, id1, id2, queueStart, queueEnd, visitedStart, visitedEnd, levelStart, levelEnd, bfsVersion);
                scheduler->submitJob(q);
                queryId++; 
            }
        }
    }

    delete scheduler;
    for(int i = 0 ; i < THREADS ; i++){
        delete queueStart[i];
        delete queueEnd[i];
        delete visitedStart[i];
        delete visitedEnd[i];
        free(levelStart[i]);
        free(levelEnd[i]);
    }
}