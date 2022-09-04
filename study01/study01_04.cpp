#include <map>
#include <iostream>

class Test{
    public:
        //int sub01(std::map< int, int >*& pTestMap){
        //    for(int i = 0; i<4; ++i){
        //        m_oTestMap01.insert(std::make_pair(i,1));
        //    }
        //    pTestMap = &m_oTestMap01;
        //    return 0;
        //}
        int sub0201(const std::map< int, int >*& pTestMap){
            m_oTestMap02.clear();
            for(int i = 0; i<4; ++i){
                m_oTestMap02.insert(std::make_pair(i,2));
            }
            pTestMap = &m_oTestMap02;
            std::cout << "Test::m_oTestMap02のアドレス : " << &m_oTestMap02 << "\n";
            return 0;
        }
        int clear0201(){
            m_oTestMap02.clear();
            m_pTestMap02 = NULL;
            return 0;
        }
        //int sub0202(const std::map< int, int >* pTestMap){
        //    for(int i = 0; i<4; ++i){
        //        m_oTestMap02.insert(std::make_pair(i,2));
        //    }
        //    pTestMap = &m_oTestMap02;
        //    return 0;
        //}
        int sub0203(const std::map< int, int >**& ppTestMap){
            (*ppTestMap) = new (const std::map< int, int >*);
            sub0201(*ppTestMap);
            m_pTestMap02 = *ppTestMap;
            return 0;
        }
    private:
        //std::map< int, int > m_oTestMap01;
        std::map< int, int > m_oTestMap02;
        const std::map< int, int >* m_pTestMap02;
};

int main(){
    Test oTest01;
    const std::map< int, int >* pTestMap0201 = NULL;
    const std::map< int, int >* pTestMap0202 = NULL;

    const std::map< int, int >** ppTestMap = NULL;


    oTest01.sub0201(pTestMap0201);
    //oTest01.sub0202(pTestMap0202);

    if(pTestMap0201 != NULL){
        std::cout << "pTestMap0201 is not NULL : " << pTestMap0201 << "\n";
    }
    else{
        std::cout << "pTestMap0201 is NULL\n";
    }
    //if(pTestMap0202 != NULL){
    //    std::cout << "pTestMap0202 is not NULL : " << pTestMap0202 << "\n";
    //}
    //else{
    //    std::cout << "pTestMap0202 is NULL\n";
    //}
    std::map< int, int >::const_iterator itTest01 = pTestMap0201->begin();
    if(itTest01 == pTestMap0201->end()){
        std::cout << "pTestMap0201の要素数:0\n";    
    }
    for(; itTest01 != pTestMap0201->end(); ++itTest01){
        std::cout << itTest01->first << ":" << itTest01->second << "\n";    
    }

    oTest01.clear0201();
    std::map< int, int >::const_iterator itTest02 = pTestMap0201->begin();
    if(itTest02 == pTestMap0201->end()){
        std::cout << "pTestMap0201の要素数:0\n";    
    }
    for(; itTest02 != pTestMap0201->end(); ++itTest02){
        std::cout << itTest02->first << ":" << itTest02->second << "\n";    
    }

    oTest01.sub0203(ppTestMap);
    if(ppTestMap != NULL){
        std::cout << "ppTestMap is not NULL : " << ppTestMap << "\n";
    }
    else{
        std::cout << "ppTestMap is NULL\n";
    }
    oTest01.clear0201();
    std::map< int, int >::const_iterator itTest03 = (*ppTestMap)->begin();
    if(itTest03 == (*ppTestMap)->end()){
        std::cout << "*ppTestMapの要素数:0\n";    
    }
    for(; itTest03 != (*ppTestMap)->end(); ++itTest03){
        std::cout << itTest03->first << ":" << itTest03->second << "\n";    
    }


    return 0;
}
