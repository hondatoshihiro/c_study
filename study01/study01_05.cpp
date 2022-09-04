#include <map>
#include <iostream>

class Test{
    public:
        int sub02(const std::map< int, int >**& ppTestMap){
            for(int i = 0; i<4; ++i){
                m_oTestMap02.insert(std::make_pair(i,2));
            }
            m_pTestMap02 = &m_oTestMap02;
            ppTestMap = &m_pTestMap02;
            return 0;
       }
       int clear02(){
            m_oTestMap02.clear();
            m_pTestMap02 = NULL;
            return 0;
       }
    private:
        std::map< int, int > m_oTestMap02;
        const std::map< int, int >* m_pTestMap02;
};

int main(){
    Test oTest;

    const std::map< int, int >** ppTestMap02;
    oTest.sub02(ppTestMap02);

    //const std::map< int, int >* pTestMap02;は、
    //指す先のポインタは変更できる
    //ポインタの先の実体は変更できない
    //下のコードはコンパイルエラーになる。
    //for(int i=4; i<7; ++i){
    //    (*ppTestMap02)->insert(std::make_pair(i,2));
    //}

    std::map< int, int >::const_iterator itTest02 = (*ppTestMap02)->begin();
    for(; itTest02 != (*ppTestMap02)->end(); ++itTest02){
        std::cout << itTest02->first << ":" << itTest02->second << "\n";    
    }

    std::cout << "before Test::clear02 *ppTestMap02 : " << *ppTestMap02 << "\n";

    oTest.clear02();
    if(*ppTestMap02==NULL){
        std::cout << "*ppTestMap02 NULLクリア済み *ppTestMap02 : " << *ppTestMap02 << "\n";
    }
    ppTestMap02 = NULL;

    return 0;
}

