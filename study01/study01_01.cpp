#include <map>
#include <iostream>

void sub1(std::map<int, int>& oTestMap){
    std::map<int, int>::iterator itTest = oTestMap.begin();
    for(;itTest != oTestMap.end(); ++itTest){
        std::cout << itTest->first << ":" << itTest->second << "\n";
    }
    oTestMap.insert(std::make_pair(5,50));
}

void sub2(const std::map<int, int>& oTestMap){
    //constのmapは、const_itratorで扱う
    //itratorで扱うとエラーが発生する
    std::map<int, int>::const_iterator itTest = oTestMap.begin();
    for(;itTest != oTestMap.end(); ++itTest){
        std::cout << itTest->first << ":" << itTest->second << "\n";
    }
    //constなので、要素の追加はできない。
    //oTestMap.insert(std::make_pair(6,60));
}

void sub3(std::map<int, int>* pTestMap){
    std::map<int, int>::iterator itTest = pTestMap->begin();
    for(;itTest != pTestMap->end(); ++itTest){
        std::cout << itTest->first << ":" << itTest->second << "\n";
    }
    pTestMap->insert(std::make_pair(7,70));
}

//pointerがconstになるだけと思ったけど、pointの指す先の変更もできない。
void sub4(const std::map<int, int>* pTestMap){
    std::map<int, int>::iterator itTest = pTestMap->begin();
    for(;itTest != pTestMap->end(); ++itTest){
        std::cout << itTest->first << ":" << itTest->second << "\n";
    }
    pTestMap->insert(std::make_pair(8,80));
}

int main(){
    std::map<int, int> oTestMap;

    oTestMap.insert(std::make_pair(1,10));
    oTestMap.insert(std::make_pair(2,20));
    oTestMap.insert(std::make_pair(3,30));
    oTestMap.insert(std::make_pair(4,40));
    sub1(oTestMap);
    sub2(oTestMap);
    sub3(&oTestMap);
    sub4(&oTestMap);
}

