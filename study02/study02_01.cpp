#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

const int ThreadNum=2;

struct TestStr {
    int j;
    pthread_mutex_t* pmutex;
};

void* thread_main(void* ptr){
    int i=0;
    TestStr* pStr = (TestStr*)ptr;
    for(int i=0; i<10; ++i){
        std::cout << "thread_main No:" << pStr->j << ",pthread_mutex_lock" << "\n";
        int ret = pthread_mutex_lock(pStr->pmutex);
        std::cout << "thread_main No:" << pStr->j << ",pthread_mutex_lock ret:" << ret << "\n";
        std::cout << "thread_main No:" << pStr->j << ",loop cnt:" << i << "\n";
        ret = pthread_mutex_unlock(pStr->pmutex);
        sleep(10);
    }
    return NULL;
}

int main(){

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_t threadArray[ThreadNum];
    struct TestStr testStrArray[ThreadNum];

    for(int j=0; j<ThreadNum; ++j){
        testStrArray[j].j=j;
        testStrArray[j].pmutex = &mutex;
        std::cout << "pthread_create No:" << j << "\n";
        pthread_create(&threadArray[j], NULL, thread_main, (void*)&(testStrArray[j]));
    }
    for(int k=0; k<ThreadNum; ++k){
        std::cout << "pthread_join No:" << k << "\n";
        pthread_join(threadArray[k], NULL);
    }
    return 0;
}