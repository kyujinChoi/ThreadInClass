#include "thread_class.h"

void initThreadClass(int num)
{
    std::cout << "allocThreadClass..\n";
    for (int i = 0; i < num; i++)
    {
        ThreadClass *tc = new ThreadClass;
        threadList.push_back(*tc);
    }
    std::cout << "done!\n";
    std::cout << "initThreadClass..\n";

    std::list<ThreadClass>::iterator iter;
    int id = 0;

    for(iter = threadList.begin(); iter != threadList.end(); iter++)
    {
        iter->initialize(id++);
    }
    std::cout << "done!\n";
}

void chooseFunction(int _my_func, bool _use_thread)
{
    std::cout << "chooseFunction..\n";
    std::list<ThreadClass>::iterator iter;

    for(iter = threadList.begin(); iter != threadList.end(); iter++)
    {
        iter->reinitialize(_my_func, _use_thread);
    }
    std::cout << "done!\n";
}
void deleteThreadClass()
{
    std::cout << "deleteThreadClass..\n";

    threadList.clear();

    std::cout << "done!\n";
}
int main()
{
    int num = 2;
    bool use_thread = true;

    initThreadClass(num);

    while(1)
    {
        num--;
        chooseFunction(POS, use_thread);
        sleep(2);
        chooseFunction(NEG, use_thread);
        sleep(2);
        use_thread = !use_thread;
        if(num < 0)
        {
            deleteThreadClass();
            break;
        }
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//      ThreadClass Class Functions
//
/////////////////////////////////////////////////////////////////////////////////////////
// ThreadClass::~ThreadClass()

void *ThreadClass::handler(void *_pthis)
{
    ThreadClass *pthis = (ThreadClass *)_pthis;
    pthis->run();
}
void ThreadClass::initialize(int _id)
{
    id = _id;
    use_thread = false;
}
void ThreadClass::reinitialize(int _my_func, bool _use_thread)
{
    bool prev_use_thread = use_thread;
    
    my_func = _my_func;
    use_thread = _use_thread;
    

    if (use_thread)
    {
        if(!prev_use_thread)
        {
            pthread_create(&tcThread, NULL, ThreadClass::handler, (void *)this);
            pthread_detach(tcThread);
        }
    }
    else
    {
        if (prev_use_thread)
        {
            pthread_cancel(tcThread);
        }
        run();
    }
   
    return;
}

void ThreadClass::run()
{
    if(use_thread)
    {
        while(1)
        {
            std::cout << "\tmy_func : " << my_func << std::endl;
            if (my_func == POS)
                printPos();
            else
                printNeg();
            sleep(1);
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            std::cout << "\tmy_func : " << my_func << std::endl;
            if (my_func == POS)
                printPos();
            else
                printNeg();
        }
    }
}
void ThreadClass::printPos()
{
    std::cout << "\tid : " << id << ", func : POS" << ", is_multi : " << use_thread << std::endl;
}
void ThreadClass::printNeg()
{
    std::cout << "\tid : " << id << ", func : NEG" << ", is_multi : " << use_thread << std::endl;
}