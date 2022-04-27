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

class MyClass // All examples are shown on class, that works as regular int
{
    int a;
public:
    MyClass():a{}{}
    MyClass(int b):a{b}{}
    operator>(const MyClass &other) const
    {
        return a > other.a;
    }

    operator<(const MyClass &other) const
    {
        return a > other.a;
    }

    operator==(const MyClass &other) const
    {
        return a == other.a;
    }

    friend std::ostream& operator<< (std::ostream &out, const MyClass &myClass);
};

std::ostream& operator<<(std::ostream &out, const MyClass &myClass)
{
    out << myClass.a;
    return out;
}

void checkTree()
{
    std::cout << "----- RBTree -----" << std::endl;

    RBTree<MyClass> testRBTree;

    for(int i = 1; i <= 10; i++)
    {
        testRBTree.addKey(getRandomNumber(1,10));
    }

    std::cout << "Tree height: " << TreeInfoViewer::getBlackHeight(testRBTree) << std::endl;

    std::cout << "Is tree empty: " << std::boolalpha << testRBTree.empty() << std::endl;

    TreeInfoViewer::printTreeInfo(testRBTree);

    std::cout << "----- ------ -----" << std::endl;
}

void checkConstMap()
{
    std::cout << "----- CONST MAP -----" << std::endl;

    const Map<MyClass, MyClass> testMap { {1,11}, {2,22}, {3,33}, {4,44}, {5,55}};

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

    Map<MyClass, MyClass> testMap;

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

    RBTree<MyClass> testRBTree;
    for(int i = 1; i <= 10; i++)
    {
        testRBTree.addKey(i);
    }

    RBTree<MyClass> testRBTree2(testRBTree);

    TreeInfoViewer::printTreeInfo(testRBTree); std::cout << std::endl;
    TreeInfoViewer::printTreeInfo(testRBTree2); std::cout << std::endl;

    Map<MyClass, MyClass> testMap;

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
    Map<MyClass, MyClass> testMap1;

    testMap1[1] = 11;
    testMap1[2] = 22;
    testMap1[3] = 33;
    testMap1[4] = 44;
    testMap1[5] = 55;

    std::cout << "----- Map copy -----" << std::endl;

    Map<MyClass, MyClass> testMap2(testMap1);

    TreeInfoViewer::printTreeInfo(testMap1); std::cout << std::endl;
    TreeInfoViewer::printTreeInfo(testMap2); std::cout << std::endl;

    RBTree<MyClass> testRBTree;
    for(int i = 50; i <= 60; i++)
    {
        testRBTree.addKey(i);
    }

    testMap2 = testRBTree;

    testMap2[55] = 65;

    TreeInfoViewer::printTreeInfo(testMap2); std::cout << std::endl;

    std::cout << "----- -------- -----" << std::endl;
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
