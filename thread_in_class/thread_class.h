#ifndef THREADCLASS_H_INCLUDED
#define THREADCLASS_H_INCLUDED

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>

enum
{
    POS,
    NEG
};

class ThreadClass
{
public:
    ThreadClass(){}
    ~ThreadClass()
    {
        std::cout << "~ThreadClass() called : " << id << "\n";
        if(use_thread)
            pthread_cancel(tcThread);
    }
    static void *handler (void *pthis);
    void initialize(int _id);
    void reinitialize(int _my_func, bool _use_thread);
    
private:
    int id;
    bool use_thread;
    int my_func;
    pthread_t tcThread;
    
    void run();
    void printPos();
    void printNeg();
    
};

static std::list<ThreadClass> threadList;
// static ThreadClass threadList[2];

#endif