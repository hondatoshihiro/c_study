#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>


const int ThreadNum=2;

struct TestStr {
    int j;
    pthread_mutex_t* pmutex;
};

void* thread_main1(void* ptr){
    int i=0;
    TestStr* pStr = (TestStr*)ptr;
    for(int i=0; i<10; ++i){
        //std::cout << "thread_main No:" << pStr->j << ",pthread_mutex_lock" << "\n";
        //int ret = pthread_mutex_lock(pStr->pmutex);
        //std::cout << "thread_main No:" << pStr->j << ",pthread_mutex_lock ret:" << ret << "\n";
        std::cout << "thread_main1 No:" << pStr->j << ",loop cnt:" << i << "\n";
        //ret = pthread_mutex_unlock(pStr->pmutex);
        sleep(10);
    }
    return NULL;
}

void* thread_main2(void* ptr){
    int i=0;
    TestStr* pStr = (TestStr*)ptr;
    for(int i=0; i<10; ++i){
        //std::cout << "thread_main No:" << pStr->j << ",pthread_mutex_lock" << "\n";
        //int ret = pthread_mutex_lock(pStr->pmutex);
        //std::cout << "thread_main No:" << pStr->j << ",pthread_mutex_lock ret:" << ret << "\n";
        std::cout << "thread_main2 No:" << pStr->j << ",loop cnt:" << i << "\n";
        //ret = pthread_mutex_unlock(pStr->pmutex);
        sleep(10);
    }
    return NULL;
}

int main(){

    pthread_mutex_t mutex;

    pthread_t threadArray[ThreadNum];
    struct TestStr testStrArray[ThreadNum];

    testStrArray[0].j=0;
    testStrArray[0].pmutex = &mutex;
    std::cout << "pthread_create No:0\n";
    pthread_create(&threadArray[0], NULL, thread_main1, (void*)&(testStrArray[0]));

    testStrArray[1].j=1;
    testStrArray[1].pmutex = &mutex;
    std::cout << "pthread_create No:1\n";
    pthread_create(&threadArray[1], NULL, thread_main2, (void*)&(testStrArray[1]));

    for(int k=0; k<ThreadNum; ++k){
        std::cout << "pthread_join No:" << k << "\n";
        pthread_join(threadArray[k], NULL);
    }
    return 0;
}