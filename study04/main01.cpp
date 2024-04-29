#include <chrono>
#include <iostream>
#include <list>
#include <vector>


int main(){
    const long MAX_CNT = 100000;

    long lSum = 0;
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    //秒単位で計測
    std::chrono::duration<double> elapsed_sec;
    //ミリ秒単位で計測
    std::chrono::duration<double, std::milli> elapsed_msec;

#if 0  //std::list
    start = std::chrono::system_clock::now();
    //要素登録
    std::list<long> oList;
    for(long l = 0; l < MAX_CNT; l++){
        oList.push_back(l);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "要素登録処理時間,std::list," << elapsed_msec.count() << ",ミリ秒" << std::endl;

    //順次検索:iterator(1)登録
    lSum = 0;
    start = std::chrono::system_clock::now();
    for(std::list<long>::iterator it = oList.begin(); it!=oList.end(); it++){
        lSum += (*it);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,iterator(1),std::list," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;

    //順次検索:iterator(2)登録
    lSum = 0;
    start = std::chrono::system_clock::now();
    std::list<long>::iterator itE = oList.end();
    for(std::list<long>::iterator it = oList.begin(); it!=itE; it++){
        lSum += (*it);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,iterator(2),std::list," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;
#endif
#if 1  //std::vector
    start = std::chrono::system_clock::now();
    //要素登録
    std::vector<long> oVec;
    for(long l = 0; l < MAX_CNT; l++){
        oVec.push_back(l);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "要素登録処理時間,std::vector," << elapsed_msec.count() << ",ミリ秒" << std::endl;

    //順次検索:iterator(1)
    lSum = 0;
    start = std::chrono::system_clock::now();
    for(std::vector<long>::iterator it = oVec.begin(); it!=oVec.end(); it++){
        lSum += (*it);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,iterator(1),std::vector," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;

    //順次検索:iterator(2)
    lSum = 0;
    start = std::chrono::system_clock::now();
    std::vector<long>::iterator itE = oVec.end();
    for(std::vector<long>::iterator it = oVec.begin(); it!=itE; it++){
        lSum += (*it);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,iterator(2),std::vector," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;

    //順次検索:[]オペレータ
    lSum = 0;
    start = std::chrono::system_clock::now();
    for(long l = 0; l < MAX_CNT; l++){
        lSum += oVec[l];
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,[]オペレータ,std::vector," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;

    //順次検索:atメソッド登録
    lSum = 0;
    start = std::chrono::system_clock::now();
    for(long l = 0; l < MAX_CNT; l++){
        lSum += oVec.at(l);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,atメソッド,std::vector," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;
#endif
}