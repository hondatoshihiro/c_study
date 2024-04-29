#include <chrono>
#include <iostream>
#include <list>
#include <vector>
#include <set>

//ビルド:>g++ main01.cpp
//ビルド(最適化):>g++ -O2 main01.cpp
//実行:>./a.out
int main(){
    const long MAX_CNT = 100000;
    //const long MAX_CNT = 1000000;
    //const long MAX_CNT = 10000000;

    long lSum = 0;
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    //秒単位で計測
    std::chrono::duration<double> elapsed_sec;
    //ミリ秒単位で計測
    std::chrono::duration<double, std::milli> elapsed_msec;

#if 1  //std::list
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
    std::list<long>::iterator itListE = oList.end();
    for(std::list<long>::iterator it = oList.begin(); it!=itListE; it++){
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
    std::vector<long>::iterator itVecE = oVec.end();
    for(std::vector<long>::iterator it = oVec.begin(); it!=itVecE; it++){
        lSum += (*it);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,iterator(2),std::vector," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;

    //順次検索:[]オペレータ(1)
    lSum = 0;
    start = std::chrono::system_clock::now();
    for(long l = 0; l < oVec.size(); l++){
        lSum += oVec[l];
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,[]オペレータ(1),std::vector," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;

    //順次検索:[]オペレータ(2)
    lSum = 0;
    start = std::chrono::system_clock::now();
    long opMaxSize = oVec.size();
    for(long l = 0; l < opMaxSize; l++){
        lSum += oVec[l];
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,[]オペレータ(2),std::vector," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;

    //順次検索:atメソッド(1)
    lSum = 0;
    start = std::chrono::system_clock::now();
    for(long l = 0; l < oVec.size(); l++){
        lSum += oVec.at(l);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,atメソッド(1),std::vector," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;

    //順次検索:atメソッド(2)
    lSum = 0;
    start = std::chrono::system_clock::now();
    long atMaxSize = oVec.size();
    for(long l = 0; l < atMaxSize; l++){
        lSum += oVec.at(l);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,atメソッド(2),std::vector," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;
#endif
#if 1  //std::set
    start = std::chrono::system_clock::now();
    //要素登録
    std::set<long> oSet;
    for(long l = 0; l < MAX_CNT; l++){
        oSet.insert(l);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "要素登録処理時間,std::set," << elapsed_msec.count() << ",ミリ秒" << std::endl;

    //順次検索:iterator(1)
    lSum = 0;
    start = std::chrono::system_clock::now();
    for(std::set<long>::iterator it = oSet.begin(); it!=oSet.end(); it++){
        lSum += (*it);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,iterator(1),std::set," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;

    //順次検索:iterator(2)
    lSum = 0;
    start = std::chrono::system_clock::now();
    std::set<long>::iterator itSetE = oSet.end();
    for(std::set<long>::iterator it = oSet.begin(); it!=itSetE; it++){
        lSum += (*it);
    }
    end = std::chrono::system_clock::now();
    elapsed_msec =  end - start;
    //結果出力
    std::cout << "順次検索,iterator(2),std::set," << elapsed_msec.count() << ",ミリ秒,lSum," << lSum << std::endl;
#endif
}