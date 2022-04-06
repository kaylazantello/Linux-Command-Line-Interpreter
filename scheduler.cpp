/*
Project 3: Short-Term Process Scheduler
CST-315: Operating Systems
March 29, 2022
Kayla Zantello, Ethan Macalaguim, Kara Sumpter

This program simulates a short-term scheduler using two data structures - a ready queue and a waiting queue.
Processes in the ready queue are in the READY state, while processes in the waiting queue are in the BLOCKED
state waiting for input. The scheduler must manage the two queues and choose which process to allocate the 
CPU to such that all 10 processes complete. There are five user processes and five I/O processes.
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unistd.h>
#include <pthread.h>
#include <algorithm>
#include "Process.h"

using namespace std;

// user processes 1-5
void *execUP1(void *);  
void *execUP2(void *);
void *execUP3(void *);
void *execUP4(void *);
void *execUP5(void *);

// i/o processes 1-5
void *execIO1(void *);
void *execIO2(void *);
void *execIO3(void *);
void *execIO4(void *);
void *execIO5(void *);

void updateState(Process, string);

int main() {

    vector<Process> ready;  // ready queue
    queue<Process> waiting;  // waiting queue

    pthread_t up1, up2, up3, up4, up5, io1, io2, io3, io4, io5;

    Process processA("User Process 1", 1, up1, execUP1);
    Process processB("User Process 2", 2, up2, execUP2);
    Process processC("User Process 3", 3, up3, execUP3);
    Process processD("User Process 4", 4, up4, execUP4);
    Process processE("User Process 5", 5, up5, execUP5);
    Process processF("I/O Process 1", 6, io1, execIO1, 4);
    Process processG("I/O Process 2", 7, io2, execIO2, 3);
    Process processH("I/O Process 3", 8, io3, execIO3, 2);
    Process processI("I/O Process 4", 9, io4, execIO4, 3);
    Process processJ("I/O Process 5", 10, io5, execIO5, 2);

                                // ready queue
                                // Process           ID   Type 
    ready.push_back(processA);  // User Process 1    1    user 
    ready.push_back(processF);  // I/O Process 2     6    I/O   
    ready.push_back(processB);  // User Process 2    2    user 
    ready.push_back(processG);  // I/O Process 2     7    I/O
    ready.push_back(processC);  // User Process 3    3    user
    ready.push_back(processH);  // I/O Process 3     8    I/O
    ready.push_back(processI);  // I/O Process 4     9    I/O
    ready.push_back(processJ);  // I/O Process 5     10   I/O
    ready.push_back(processD);  // User Process 4    4    user
    ready.push_back(processE);  // User Process 5    5    user

    // while there are Processes in the ready or waiting queues
    while(!ready.empty() || !waiting.empty()) {
        
        // if there is a Process in ready queue
        if(!ready.empty()) {
            cout << "\nSCHEDULER: allocating CPU to " << ready.front().name << endl;
            //updateState(ready.front(), "RUNNING");

            pthread_create(&ready.front().tid, NULL, ready.front().func, NULL);  // start running Process at front of ready queue

            pthread_join(ready.front().tid, NULL);  // wait for process to finish

            ready.front().cpuBursts[0]++;  // increment number of completed cpu bursts

            if(ready.front().cpuBursts[0] >= ready.front().cpuBursts[1]) {  // if all necessary cpu bursts have completed
                cout << "SCHEDULER: " << ready.front().name << " has completed" << endl;
            }
            else {  // else the process still has input to wait for
                cout << "SCHEDULER: " << ready.front().name << " has blocked for input" << endl;
                //updateState(ready.front(), "BLOCKED");

                waiting.push(ready.front());  // insert at tail of waiting queue
                waiting.front().blockedTime = clock();  // mark the time at which process blocked for input
            }
            ready.erase(ready.begin());  // pop process from head of ready queue
        }
        
        // if there are Processes in waiting queue
        if(!waiting.empty() && ((clock() - waiting.front().blockedTime)/CLOCKS_PER_SEC) > 2) {
            //updateState(waiting.front(), "READY");

            cout << "SCHEDULER: " << waiting.front().name << " has received input" << endl;

            ready.insert(ready.begin(), waiting.front());  // insert process at head of ready queue
            waiting.pop();  // pop process from head of waiting queue
        }

    }

    printf("\nSCHEDULER: all processes finished sucessfully!\n");

    return 0;
}

// user process 1
void *execUP1(void *) {
    system("./userProcess1");
    return NULL;
}

// user process 2
void *execUP2(void *) {
    system("./userProcess2");
    return NULL;
}

void *execUP3(void *) {
    system("./userProcess3");
    return NULL;
}

void *execUP4(void *) {
    system("./userProcess4");
    return NULL;
}

void *execUP5(void *) {
    system("./userProcess5");
    return NULL;
}

// I/O process 1
void *execIO1(void *) {
    system("./ioProcess1");
    return NULL; 
}

// I/O process 2
void *execIO2(void *) {
    system("./ioProcess2");
    return NULL;
}

void *execIO3(void *) {
    system("./ioProcess3");
    return NULL;
}

void *execIO4(void *) {
    system("./ioProcess4");
    return NULL;
}

void *execIO5(void *) {
    system("./ioProcess5");
    return NULL;
}

void updateState(Process p, string newState) {
    string prevState = p.state;
    p.state = newState;
    printf("SCHEDULER: %s has moved from %s state to %s state\n", p.name.c_str(), prevState.c_str(), p.state.c_str());
}
