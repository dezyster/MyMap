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
    std::cout << "----- RBTree -----" << std::endl;

    RBTree<int> testRBTree;

    for(int i = 1; i <= 20; i++)
    {
        testRBTree.addKey(getRandomNumber(1,100));
    }

    std::cout << TreeInfoViewer::getBlackHeight(testRBTree) << std::endl;

    TreeInfoViewer::printTreeInfo(testRBTree);
    TreeInfoViewer::printBlackHeight(testRBTree);

    std::cout << testRBTree.empty() << std::endl;

    std::cout << "----- ------ -----" << std::endl;
}

void checkConstMap()
{
    std::cout << "----- CONST MAP -----" << std::endl;

    const Map<int, int> testMap { {1,11}, {2,22}, {3,33}, {4,44}, {5,55}};

    auto a{ testMap.begin() };
    ++a;

    auto b { a };
    std::cout << b->second << std::endl << std::endl;

    std::cout << testMap.contains(6) << std::endl;
    std::cout << testMap[5] << std::endl;
    std::cout << testMap.empty() << std::endl;
    std::cout << testMap.size() << std::endl;

    TreeInfoViewer::printTreeInfo(testMap);
    TreeInfoViewer::printBlackHeight(testMap);

   std::cout << "----- --------- -----" << std::endl;
}

void checkMap()
{
    std::cout << "----- Map -----" << std::endl;

    Map<int, int> testMap;

    testMap[1] = 11;
    testMap[2] = 22;
    testMap[3] = 33;
    testMap[4] = 44;
    testMap[5] = 55;

    testMap.insert(std::make_pair(6,99));

    TreeInfoViewer::printTreeInfo(testMap);
    TreeInfoViewer::printBlackHeight(testMap);

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
    a->second = 55;
    std::cout << std::endl << a->second << std::endl;

    std::cout << "----- --- -----" << std::endl;
}

void checkEqualityOperatorRBTree()
{
    std::cout << "----- RBTree copy -----" << std::endl;

    RBTree<int> testRBTree;
    for(int i = 1; i <= 10; i++)
    {
        testRBTree.addKey(i);
    }

    RBTree<int> testRBTree2(testRBTree);

    TreeInfoViewer::printTreeInfo(testRBTree); std::cout << std::endl;
    TreeInfoViewer::printTreeInfo(testRBTree2); std::cout << std::endl;

    Map<int, int> testMap;

    testMap[1] = 11;
    testMap[2] = 22;
    testMap[3] = 33;
    testMap[4] = 44;
    testMap[5] = 55;

    testRBTree2 = testMap;

    TreeInfoViewer::printTreeInfo(testRBTree2); std::cout << std::endl;

    std::cout << "----- ----------- -----" << std::endl;
}

void checkEqualityOperatorMap()
{
    std::cout << "----- Map copy -----" << std::endl;

    Map<int, int> testMap;

    testMap[1] = 11;
    testMap[2] = 22;
    testMap[3] = 33;
    testMap[4] = 44;
    testMap[5] = 55;

    Map<int, int> testMap2;

    TreeInfoViewer::printTreeInfo(testMap); std::cout << std::endl;
    TreeInfoViewer::printTreeInfo(testMap2); std::cout << std::endl;

    RBTree<int> testRBTree;
    for(int i = 50; i <= 60; i++)
    {
        testRBTree.addKey(i);
    }

    testMap2 = testRBTree;
    TreeInfoViewer::printTreeInfo(testMap2); std::cout << std::endl;

    std::cout << "----- -------- -----" << std::endl;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand();

    //checkTree();

    //checkMap();

    //checkConstMap();

    checkEqualityOperatorRBTree();

    checkEqualityOperatorMap();

    return 0;
}
