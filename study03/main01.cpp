//zlibのインストール
//>sudo wget -P /usr/local/src http://www.zlib.net/zlib-1.2.13.tar.gz
//>cd /usr/local/src
//>sudo tar xzf zlib-1.2.13.tar.gz
//>cd zlib-1.2.13
//>sudo .configure --prefix=/usr/local
//makeがインストールされていなかった
//>sudo apt install make
//>sudo apt install make-guile
//>sudo make
//>sudo make install
//ソースのコンパイル
//g++ main01.cpp -lz -g3
//g++ main01.cpp -lz -g0
#include <cstdio>
#include <zlib.h>
#include <stdio.h>
#include <cstring>
#include <time.h>

//#define FILENAME "test.txt"
//#define GZFILENAME "test.txt.gz"
//#define FILENAME "test_0010M.txt"
//#define GZFILENAME "test_0010M.txt.gz"
//#define FILENAME "test_0100M.txt"
//#define GZFILENAME "test_0100M.txt.gz"
//#define FILENAME "test_0200M.txt"
//#define GZFILENAME "test_0200M.txt.gz"
#define FILENAME "test_0500M.txt"
#define GZFILENAME "test_0500M.txt.gz"
//#define FILENAME "test_1000M.txt"
//#define GZFILENAME "test_1000M.txt.gz"
int main(void){

    clock_t startTime;
    clock_t endTime;

    startTime = clock();
    FILE* pFile;
    //ファイルオープン
    pFile = fopen(FILENAME, "rb");
    if(pFile==NULL){
        printf("fopen error!!\n");
        return -1;
    }
    char buff[256];
    int readCnt=0;
    while(1){
        readCnt++;
        memset(buff, 0x00, sizeof(buff));
        //gzファイルリード
        int readByte = fread(buff, 1, sizeof(buff), pFile);
        if(readByte <= 0){ 
            break;
        }
        //printf("fread readCnt:%d, readByte:%d\n", readCnt, readByte);
    }
    //ファイルクローズ
    fclose(pFile);
    endTime = clock();
    printf("fread time:%f(s)\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);

    startTime = clock();
    gzFile pGzFile;
    //gzファイルオープン
    pGzFile = gzopen(GZFILENAME, "rb");
    if(pGzFile==NULL){
        printf("gzopen error!!\n");
        return -1;
    }
    readCnt=0;
    while(1){
        readCnt++;
        memset(buff, 0x00, sizeof(buff));
        //gzファイルリード
        int readByte = gzread(pGzFile, buff, sizeof(buff));
        if(readByte <= 0){ 
            break;
        }
        //printf("gzread readCnt:%d, readByte:%d\n", readCnt, readByte);
    }
    //gzファイルクローズ
    gzclose(pGzFile);
    endTime = clock();
    printf("gzread time:%f(s)\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);
    return 0;
}
