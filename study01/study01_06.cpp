#include <map>
#include <iostream>

//2023/12/12 仕事の調査
void sub1(std::map<int, int>& oTestMap={}){
    std::map<int, int>::const_iterator itTest = oTestMap.begin();
    if(oTestMap.size()==0){
        std::cout << "oTestMap.size():0\n";
    }
    for(;itTest != oTestMap.end(); ++itTest){
        std::cout << itTest->first << ":" << itTest->second << "\n";
    }
    //oTestMap.insert(std::make_pair(5,50));
}


int main(){
    std::map<int, int> oTestMap;

    oTestMap.insert(std::make_pair(1,10));
    oTestMap.insert(std::make_pair(2,20));
    oTestMap.insert(std::make_pair(3,30));
    oTestMap.insert(std::make_pair(4,40));
    sub1(oTestMap);
}

