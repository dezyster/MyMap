#include <cstdlib>
#include <ctime>

#include "Map.h"
#include "RBTree.h"
#include "TreeInfoViewer.h"

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void checkTree()
{
    RBTree<int> tst;

    for(int i = 1; i <= 20; i++)
    {
        tst.addKey(getRandomNumber(1,50000));
        //tst.addKey(i);
    }

    //auto ptr = tst.begin();

    //tst.erase();

    std::cout << TreeInfoViewer::getBlackHeight(tst) << std::endl;

    TreeInfoViewer::printTreeInfo(tst);
    TreeInfoViewer::printBlackHeight(tst);

    //tst.printTreeInfo();
    //tst.checkTree();

    //std::cout << tst.empty();
}

void checkConstMap()
{
    const Map<int, int> testMap { {1,11}, {2,22}, {3,33}, {4,44}, {5,55}};

    auto a = testMap.begin();
    ++a;

    auto b { a };
    std::cout << b->second << std::endl << std::endl;


    for(auto it: testMap)
    {
        //it.second = 2;
        std::cout << it.second << std::endl;
    }

    std::cout << testMap.contains(6) << std::endl;
    std::cout << testMap[5] << std::endl;
    std::cout << testMap.empty() << std::endl;
    std::cout << testMap.size() << std::endl;
}

void checkMap()
{
    Map<int, int> testMap;

    testMap[1] = 11;
    testMap[2] = 22;
    testMap[3] = 33;
    testMap[4] = 44;
    testMap[5] = 55;

    testMap.insert(std::make_pair(6,9));

    TreeInfoViewer::printTreeInfo(testMap);
    TreeInfoViewer::printBlackHeight(testMap);


    std::cout << std::boolalpha << TreeInfoViewer::checkBlackHeight(testMap) << std::endl;
    std::cout << TreeInfoViewer::getBlackHeight(testMap) << std::endl;

    std::cout << testMap.contains(6) << std::endl;
    std::cout << testMap[6] << std::endl;
    std::cout << std::boolalpha << testMap.empty() << std::endl;
    std::cout << testMap.size() << std::endl;

    for(auto it: testMap)
    {
        std::cout << std::endl << it.first << " "<< it.second;
    }

    for(const auto &it: testMap)
    {
        std::cout << std::endl << it.first << " "<< it.second;
    }

    auto a = testMap.begin();

    ++a;

    //std::cout << (*a).getValueByKey(1) << std::endl;
    //(*a).second = 55;
    //std::cout << (*a).second << std::endl;*/
}

void checkEqualityOperatorRBTree()
{

    RBTree<int> tst;
    for(int i = 1; i <= 10; i++)
    {
        tst.addKey(i);
    }

    RBTree<int> tst2(tst);

    /*for(int i = 1; i <= 5; i++)
    {
        tst2.addKey(i);
    }*/

    TreeInfoViewer::printTreeInfo(tst); std::cout << std::endl;
    TreeInfoViewer::printTreeInfo(tst2); std::cout << std::endl;

    //tst2 = std::move(tst);

    Map<int, int> testMap;

    testMap[1] = 11;
    testMap[2] = 22;
    testMap[3] = 33;
    testMap[4] = 44;
    testMap[5] = 55;

    tst2 = testMap;



    TreeInfoViewer::printTreeInfo(tst2); std::cout << std::endl;
    TreeInfoViewer::printTreeInfo(tst); std::cout << std::endl;
}

void checkEqualityOperatorMap()
{
    Map<int, int> testMap;

    testMap[1] = 11;
    testMap[2] = 22;
    testMap[3] = 33;
    testMap[4] = 44;
    testMap[5] = 55;

    Map<int, int> testMap2;

    testMap2 = std::move(testMap);

    /*for(int i = 1; i <= 5; i++)
    {
        tst2.addKey(i);
    }*/

    TreeInfoViewer::printTreeInfo(testMap); std::cout << std::endl;
    TreeInfoViewer::printTreeInfo(testMap2); std::cout << std::endl;

    /*tst2 = std::move(tst);

    TreeInfoViewer::printTreeInfo(tst2);
    TreeInfoViewer::printTreeInfo(tst);*/
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand();

    checkTree();

    checkMap();

    checkConstMap();

    checkEqualityOperatorRBTree();
    checkEqualityOperatorMap();

    return 0;
}
