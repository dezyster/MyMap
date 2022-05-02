#include <gtest/gtest.h>

#include "RBTree.h"
#include "Map.h"

class MapFromTreeTest: public ::testing::Test
{
protected:
    RBTree<int> emptyTree;  // blank red-black tree
    RBTree<int> bigSizedTree;  // big-sized red-black tree
    const RBTree<int> constTree;  // const tree

public:
    MapFromTreeTest(): emptyTree{}, bigSizedTree{}, constTree{10,6,9,13,17,15}{} // initialize trees
    ~MapFromTreeTest() = default;

    void SetUp()
    {
        for(int i{0}; i < 10000; ++i)
        {
            bigSizedTree.addKey(i); // adds 10000 elements to bigSizedTree
        }
    }
    void TearDown()
    {
        emptyTree = RBTree<int>{}; // make emptyTree a blank tree
        bigSizedTree = RBTree<int>{}; // make bigSizedTree a blank tree
    }
};

TEST_F(MapFromTreeTest, CopyConstructorFromDifferentTreeTests)
{
    Map<int, int> emptyMap(emptyTree); //creates map with copy constructor from empty RBTree

    EXPECT_TRUE(emptyMap.empty()); // expects emptyMap to be empty

    Map<int, int> bigSizedMap(bigSizedTree); //creates map with copy constructor from big sized RBTree

    EXPECT_EQ(bigSizedMap.size(), 10000); // expects bigSizedMap size to be 10000
    EXPECT_TRUE(bigSizedMap.contains(555)); // expects bigSizedMap to contain element 555

    const Map<int, int> constMap(constTree); //creates const map with copy constructor from const RBTree

    EXPECT_EQ(constMap.size(), 6); // expects constMap size to be 6
    EXPECT_TRUE(constMap.contains(17)); // expects constMap to contain element 17
}

TEST_F(MapFromTreeTest, CopyEqualityOperatorFromDifferentTreeTests)
{
    Map<int, int> emptyMap; // creates empty map
    emptyMap = emptyTree; // call copy equality operator with empty RBTree

    EXPECT_TRUE(emptyMap.empty()); // expects emptyMap to be empty

    Map<int, int> bigSizedMap; // creates empty map
    bigSizedMap = bigSizedTree; // call copy equality operator with big sized RBTree

    EXPECT_EQ(bigSizedMap.size(), 10000); // expects bigSizedMap size to be 10000
    EXPECT_TRUE(bigSizedMap.contains(555)); // expects bigSizedMap to contain element 555
}

class TreeFromMapTest: public ::testing::Test
{
protected:
    Map<int, int> emptyMap;  // blank map
    Map<int, int> bigSizedMap;  // big-sized map
    const Map<int, int> constMap;  // const map

public:
    TreeFromMapTest(): emptyMap{}, bigSizedMap{}, constMap{ {1,11}, {2,22}, {3,33}, {4,44}, {5,55}, {6,66} }{} // initialize maps
    ~TreeFromMapTest() = default;

    void SetUp()
    {
        for(int i{0}; i < 10000; ++i)
        {
            bigSizedMap[i] = i * 11; // adds 10000 elements to bigSizedMap
        }
    }
    void TearDown()
    {
        emptyMap = Map<int, int>{}; // make emptyMap a blank map
        bigSizedMap = Map<int, int>{}; // make bigSizedMap a blank map
    }
};

TEST_F(TreeFromMapTest, CopyConstructorFromDifferentTreeTests)
{
    RBTree<int> emptyTree(emptyMap);  // //creates RBTree with copy constructor from empty map

    EXPECT_TRUE(emptyTree.empty()); // expects emptyTree to be empty

    RBTree<int> bigSizedTree(bigSizedMap); //creates RBTree with copy constructor from big sized Map

    EXPECT_EQ(bigSizedTree.size(), 10000); // expects bigSizedTree size to be 10000
    EXPECT_TRUE(bigSizedTree.contains(555)); // expects bigSizedTree to contain element 555

    const RBTree<int> constTree(constMap); //creates const RBTree with copy constructor from const Map

    EXPECT_EQ(constTree.size(), 6); // expects constTree size to be 6
    EXPECT_TRUE(constTree.contains(6)); // expects constTree to contain element 17*/
}

TEST_F(TreeFromMapTest, CopyEqualityOperatorFromDifferentTreeTests)
{
    RBTree<int> emptyTree;  // creates blank RBTree
    emptyTree = emptyMap; // copies elements from emptyMap

    EXPECT_TRUE(emptyTree.empty()); // expects emptyTree to be empty

    RBTree<int> bigSizedTree; // creates blank RBTree
    bigSizedTree = bigSizedMap;// copies elements from empty bigSizedMap

    EXPECT_EQ(bigSizedTree.size(), 10000); // expects bigSizedTree size to be 10000
    EXPECT_TRUE(bigSizedTree.contains(555)); // expects bigSizedTree to contain element 555
}
