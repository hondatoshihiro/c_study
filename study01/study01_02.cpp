#include <map>
#include <iostream>

class Test{
    public:
        int sub01(std::map< int, int >*& pTestMap){
            for(int i = 0; i<4; ++i){
                m_oTestMap01.insert(std::make_pair(i,1));
            }
            pTestMap = &m_oTestMap01;
            return 0;
       }
        int sub02(const std::map< int, int >*& pTestMap){
            for(int i = 0; i<4; ++i){
                m_oTestMap02.insert(std::make_pair(i,2));
            }
            pTestMap = &m_oTestMap02;
            return 0;
       }
    private:
        std::map< int, int > m_oTestMap01;
        std::map< int, int > m_oTestMap02;
};

int main(){
    Test oTest;
    std::map< int, int >* pTestMap01;
    oTest.sub01(pTestMap01);

    for(int i=4; i<7; ++i){
        pTestMap01->insert(std::make_pair(i,1));
    }

    std::map< int, int >::iterator itTest01 = pTestMap01->begin();
    for(; itTest01 != pTestMap01->end(); ++itTest01){
        std::cout << itTest01->first << ":" << itTest01->second << "\n";    
    }
    pTestMap01 = NULL;
    if(pTestMap01==NULL){
        std::cout << "pTestMap01 NULLクリア済み\n";
    }

    const std::map< int, int >* pTestMap02;
    oTest.sub02(pTestMap02);

    //const std::map< int, int >* pTestMap02;は、
    //指す先のポインタは変更できる
    //ポインタの先の実体は変更できない
    //下のコードはコンパイルエラーになる。
    //for(int i=4; i<7; ++i){
    //    pTestMap02->insert(std::make_pair(i,2));
    //}

    std::map< int, int >::const_iterator itTest02 = pTestMap02->begin();
    for(; itTest02 != pTestMap02->end(); ++itTest02){
        std::cout << itTest02->first << ":" << itTest02->second << "\n";    
    }

    pTestMap02 = NULL;
    if(pTestMap02==NULL){
        std::cout << "pTestMap02 NULLクリア済み\n";
    }

    std::map< int, int >* const pTestMap03;


    return 0;
}

