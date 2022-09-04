#include <map>
#include <iostream>

class TestSub{
    public:
        int sub(const std::map< int, int >*& pTestMap){
            m_oTestSubMap01.clear();
            for(int i = 0; i<4; ++i){
                m_oTestSubMap01.insert(std::make_pair(i,2));
            }
            pTestMap = &m_oTestSubMap01;
            std::cout << "TestSub::sub()\n";
            return 0;
        }

    private:
        std::map< int, int > m_oTestSubMap01;

};

class Test{
    public:
        Test(){
            m_pTestSub = new TestSub();
        }
        int GetTestSub01(TestSub* pTestSub){
            pTestSub = m_pTestSub;
            return 0;
        }
        int GetTestSub02(TestSub*& pTestSub){
            pTestSub = m_pTestSub;
            return 0;
        }
        int ClearTestSub(void){
            delete m_pTestSub;
            m_pTestSub = NULL;
            return 0;
        }
    private:
        TestSub* m_pTestSub;
};

int main(){
    Test oTest01;
    TestSub* pTestSub01;
    TestSub* pTestSub02;
    const std::map< int, int >* pTestMap02;

    oTest01.GetTestSub01(pTestSub01);
    if(pTestSub01 != NULL){
        std::cout << "before ClearTestSub : pTestSub01 is not NULL : " << *pTestSub01 << "\n";
        pTestSub01->sub(pTestMap02);
    }
    else{
        std::cout << "before ClearTestSub : pTestSub01 is NULL\n";
    }

    oTest01.GetTestSub02(pTestSub02);
    if(pTestSub02 != NULL){
        std::cout << "before ClearTestSub : pTestSub02 is not NULL : " << *pTestSub02 << "\n";
        pTestSub02->sub(pTestMap02);
    }
    else{
        std::cout << "before ClearTestSub : pTestSub02 is NULL\n";
    }

    oTest01.ClearTestSub();
    if(pTestSub01 != NULL){
        std::cout << "after ClearTestSub : pTestSub01 is not NULL : " << *pTestSub01 << "\n";
        pTestSub01->sub(pTestMap02);
    }
    else{
        std::cout << "after ClearTestSub : pTestSub01 is NULL\n";
    }
    if(pTestSub02 != NULL){
        std::cout << "after ClearTestSub : pTestSub02 is not NULL : " << *pTestSub02 << "\n";
        pTestSub02->sub(pTestMap02);
    }
    else{
        std::cout << "after ClearTestSub : pTestSub02 is NULL\n";
    }

    return 0;
}