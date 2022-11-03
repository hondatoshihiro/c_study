#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

const int ThreadNum=2;
const int MsgSize=1024;

const long GetDataType1=1;
const long GetDataType2=2;
const long FinishProcType=3;
const long ErrDataType=4;

const int SendNum=10;

struct TestStr {
    int j;
    pthread_mutex_t* pmutex;
    int threadqid;
    int mainqid;
};

struct MsgStr {
    long msgType;
    char msgdata[MsgSize];
};

void* thread_main1(void* ptr){
    int i=0;
    TestStr* pStr = (TestStr*)ptr;
    MsgStr msgData;
    //MsgStr* pMsgData = &msgData;
    //for(int i=0; i<10; ++i){
    //    std::cout << "thread_main1 No:" << pStr->j << ",loop cnt:" << i << "\n";
    //    sleep(10);
    //}
    while(1){
        errno=0;
        msgrcv(pStr->threadqid, &msgData, MsgSize, 0, 0);
        if(msgData.msgType==GetDataType1){
            std::cout << "thread_main1 msgrcv from main dataget_msg\n";
            sleep(10);
            errno=0;
            msgsnd(pStr->mainqid, &msgData, MsgSize, 0);
            std::cout << "thread_main1 msgsnd to main dataget_msg errno:" << errno << "\n";
        }
        else if(msgData.msgType==FinishProcType){
            std::cout << "thread_main1 msgrcv from main finishproc_msg\n";
            errno=0;
            msgsnd(pStr->mainqid, &msgData, MsgSize, 0);
            std::cout << "thread_main1 msgsnd to main finishproc_msg errno:" << errno << "\n";;
            break;
        }
        else{
            std::cout << "thread_main1 msgrcv from main other!!\n";
            msgData.msgType=ErrDataType;
            errno=0;
            msgsnd(pStr->mainqid, &msgData, MsgSize, 0);
            std::cout << "thread_main1 msgsnd to main err_msg!! errno:" << errno << "\n";;
            break;
        }
    }
    return NULL;
}

void* thread_main2(void* ptr){
    int i=0;
    TestStr* pStr = (TestStr*)ptr;
    MsgStr msgData;
    //for(int i=0; i<10; ++i){
    //    std::cout << "thread_main2 No:" << pStr->j << ",loop cnt:" << i << "\n";
    //    sleep(10);
    //}
    while(1){
        errno=0;
        msgrcv(pStr->threadqid, &msgData, MsgSize, 0, 0);
        if(msgData.msgType==GetDataType2){
            std::cout << "thread_main2 msgrcv from main dataget_msg\n";
            sleep(10);
            errno=0;
            msgsnd(pStr->mainqid, &msgData, MsgSize, 0);
            std::cout << "thread_main2 msgsnd to main dataget_msg errno:" << errno << "\n";
        }
        else if(msgData.msgType==FinishProcType){
            std::cout << "thread_main2 msgrcv from main finishproc_msg\n";
            errno=0;
            msgsnd(pStr->mainqid, &msgData, MsgSize, 0);
            std::cout << "thread_main2 msgsnd to main finishproc_msg errno:" << errno << "\n";
            break;
        }
        else{
            std::cout << "thread_main2 msgrcv from main other!!\n";
            msgData.msgType=ErrDataType;
            errno=0;
            msgsnd(pStr->mainqid, &msgData, MsgSize, 0);
            std::cout << "thread_main2 msgsnd to main err_msg!! errno:" << errno << "\n";
            break;
        }
    }
    return NULL;
}

int main(){

    pthread_mutex_t mutex;

    pthread_t threadArray[ThreadNum];
    struct TestStr testStrArray[ThreadNum];
    int iRet;
    int mainqid,threadqid1,threadqid2;


    //メイン用キュー生成
    errno=0;
    mainqid = msgget(IPC_PRIVATE,0666);
    std::cout << "main用 mainqid:" << mainqid << ",errno:" << errno << "\n";

    //スレッド1用キュー生成
    errno=0;
    threadqid1 = msgget(IPC_PRIVATE,0666);
    std::cout << "thread_main1用 threadqid1:" << threadqid1 << ",errno:" << errno << "\n";
    //スレッド1生成
    testStrArray[0].j=0;
    testStrArray[0].pmutex = &mutex;
    testStrArray[0].threadqid = threadqid1;
    testStrArray[0].mainqid = mainqid;
    std::cout << "pthread_create No:0\n";
    pthread_create(&threadArray[0], NULL, thread_main1, (void*)&(testStrArray[0]));

    //スレッド2用キュー生成
    errno=0;
    threadqid2 = msgget(IPC_PRIVATE,0666);
    std::cout << "thread_main1用 threadqid2:" << threadqid2 << ",errno:" << errno << "\n";
    //スレッド2生成
    testStrArray[1].j=1;
    testStrArray[1].pmutex = &mutex;
    testStrArray[1].threadqid = threadqid2;
    testStrArray[1].mainqid = mainqid;
    std::cout << "pthread_create No:1\n";
    pthread_create(&threadArray[1], NULL, thread_main2, (void*)&(testStrArray[1]));


   MsgStr msgData1,msgData2,msgData;
   //メッセージ送信
    for(int sendCnt1=0; sendCnt1<SendNum; ++sendCnt1){
        msgData1.msgType=GetDataType1;
        memset(msgData1.msgdata,0x00,MsgSize);
        errno=0;
        iRet = msgsnd(threadqid1, &msgData1, MsgSize, 0);
        std::cout << "msgsnd to thread_main1 dataget_msg no." << sendCnt1 << ",errono:" << errno << "\n";
    }
    msgData1.msgType=FinishProcType;
    memset(msgData1.msgdata,0x00,MsgSize);
    errno=0;
    iRet = msgsnd(threadqid1, &msgData1, MsgSize, 0);
    std::cout << "msgsnd to thread_main1 finishproc_msg ,errno:" << errno << "\n";

    for(int sendCnt2=0; sendCnt2<SendNum; ++sendCnt2){
        msgData2.msgType=GetDataType2;
        memset(msgData2.msgdata,0x00,MsgSize);
        errno=0;
        iRet = msgsnd(threadqid2, &msgData2, MsgSize, 0);
        std::cout << "msgsnd to thread_main2 dataget_msg no." << sendCnt2 << ",errono:" << errno <<  "\n";
    }
    msgData2.msgType=FinishProcType;
    memset(msgData2.msgdata,0x00,MsgSize);
    errno=0;
    iRet = msgsnd(threadqid2, &msgData2, MsgSize, 0);
    std::cout << "msgsnd to thread_main2 finishproc_msg ,errono:" << errno << "\n";

    //メッセージ受信ループ
    int iGetDataCnt1=0;
    int iGetDataCnt2=0;
    int iFinishCnt=0;
    int iErrCnt=0;
    while(1){
        errno=0;
        msgrcv(mainqid, &msgData, MsgSize, 0, 0);
        if(msgData.msgType==GetDataType1){
            iGetDataCnt1++;
            std::cout << "msgrcv from thread_main1 dataget_msg no." << iGetDataCnt1 << ",errono;" << errno << "\n";
        }
        else if(msgData.msgType==GetDataType2){
            iGetDataCnt2++;
            std::cout << "msgrcv from thread_main2 dataget_msg no." << iGetDataCnt1 << ",errono;" << errno << "\n";
        }
        else if(msgData.msgType==FinishProcType){
            iFinishCnt++;
            std::cout << "msgrcv from thread_main? finishproc no." << iFinishCnt << ",errono;" << errno << "\n";
        }
        else{
            iErrCnt++;
            std::cout << "msgrcv from thread_main? err_msg no." << iErrCnt << ",errono;" << errno << "\n";
        }
        if(iFinishCnt==2
         || (iFinishCnt==1 && iErrCnt==1)
         || iErrCnt==2){
            break;
         }
        sleep(1);
    }


    for(int k=0; k<ThreadNum; ++k){
        //スレッドの終了待ち
        std::cout << "pthread_join No:" << k << "\n";
        pthread_join(threadArray[k], NULL);
    }
    std::cout << "finish main/n";
    return 0;
}