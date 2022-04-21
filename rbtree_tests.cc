#include <gtest/gtest.h>

#include "TreeInfoViewer.h"

class RBtreeTest: public ::testing::Test {
public:
    RBtreeTest():
        emptyTree{}, bigSizedTree{}, constTree{10,6,9,13,17,15} // initialize trees
    {

    }
    ~RBtreeTest() = default;

    void SetUp()
    {
        for(int i = 0; i < 10000; ++i)
        {
            bigSizedTree.addKey(i); // adds 10000 elements to bigSizedTree
        }
    }
    void TearDown()
    {
        emptyTree = RBTree<int>{}; // make emptyTree a blank tree
        bigSizedTree = RBTree<int>{}; // make bigSizedTree a blank tree
    }

protected:
    RBTree<int> emptyTree;  // blank red-black tree
    RBTree<int> bigSizedTree;  // big-sized red-black tree
    const RBTree<int> constTree;  // const tree
};

TEST_F(RBtreeTest, sizeTest)
{
    EXPECT_EQ(emptyTree.size(), 0); // expects emptyTree size to be 0

    EXPECT_EQ(bigSizedTree.size(), 10000); // expects bigSizedTree's size to be 10000

    EXPECT_EQ(constTree.size(), 6); // expects constTree's size to be 6
}

TEST_F(RBtreeTest, emptyTest)
{
    EXPECT_TRUE(emptyTree.empty()); // expects emptyTree to be empty

    EXPECT_FALSE(bigSizedTree.empty()); // expects bigSizedTree not to be empty

    EXPECT_FALSE(constTree.empty()); // expects constTree not to be empty
}

TEST_F(RBtreeTest, containsTest)
{
    EXPECT_FALSE(emptyTree.contains(5)); // expects emptyTree not to contain element 5

    EXPECT_TRUE(bigSizedTree.contains(555)); // expects bigSizedTree to contain element 555
    EXPECT_FALSE(bigSizedTree.contains(-10)); // expects bigSizedTree not to contain element -10

    EXPECT_TRUE(constTree.contains(6)); // expects constTree size to contain element 6
    EXPECT_FALSE(constTree.contains(7)); // expects constTree size not to contain element 7
}

TEST_F(RBtreeTest, eraseTest)
{
    bigSizedTree.erase();

    EXPECT_TRUE(bigSizedTree.empty()); // expects bigSizedTree to be empty after erase
    EXPECT_EQ(bigSizedTree.size(), 0); // expects bigSizedTree's size to be 0 after erase
}

TEST_F(RBtreeTest, blackHeightTest)
{
    EXPECT_EQ(TreeInfoViewer::getBlackHeight(emptyTree), 0); // expects emptyTree's black height to be 0

    EXPECT_EQ(TreeInfoViewer::getBlackHeight(constTree), 2); // expects constTree's black height to be 2

    EXPECT_EQ(TreeInfoViewer::getBlackHeight(bigSizedTree), 12); // expects bigSizedTree's black height to be 12
}

TEST_F(RBtreeTest, blackHeightEqualityTest)
{
    EXPECT_TRUE(TreeInfoViewer::checkBlackHeight(constTree)); // expects constTree's leaf's black height to be equal

    EXPECT_TRUE(TreeInfoViewer::checkBlackHeight(bigSizedTree)); // expects bigSizedTree's leaf's black height to be equal
}

TEST_F(RBtreeTest, CopyConstructorTests)
{
    RBTree<int> tempEmptyTree(emptyTree);  // creates temp blank red-black tree and calls copy copy constructor

    EXPECT_TRUE(tempEmptyTree.empty()); // expects tempEmptyTree to be empty
    EXPECT_TRUE(emptyTree.empty()); // expects emptyTree to be empty

    RBTree<int> tempBigSizedTree(bigSizedTree);  // creates temp big-sized red-black tree calls copy copy constructor

    EXPECT_EQ(tempBigSizedTree.size(), 10000); // expects tempBigSizedTree size to be 10000
    EXPECT_TRUE(tempBigSizedTree.contains(6)); // expects tempBigSizedTree size to contain element 555

    const RBTree<int> tempConstTree(constTree);  // creates temp const tree calls copy copy constructor

    EXPECT_EQ(tempConstTree.size(), 6); // expects tempConstTree size to be 6
    EXPECT_TRUE(tempConstTree.contains(6)); // expects tempConstTree size to contain element 6
}

TEST_F(RBtreeTest, MoveConstructorTests)
{
    RBTree<int> tempEmptyTree(std::move(emptyTree));  // creates temp blank red-black tree calls move copy constructor

    EXPECT_TRUE(tempEmptyTree.empty()); // expects tempEmptyTree to be empty
    EXPECT_TRUE(emptyTree.empty()); // expects emptyTree to be empty

    RBTree<int> tempBigSizedTree(std::move(bigSizedTree));  // creates temp big-sized red-black tree move copy constructor

    EXPECT_EQ(tempBigSizedTree.size(), 10000); // expects tempBigSizedTree size to be 10000
    EXPECT_TRUE(bigSizedTree.empty()); // expects bigSizedTree to be empty
}

TEST_F(RBtreeTest, CopyEqualityOperatorTests)
{
    RBTree<int> tempEmptyTree;  // creates temp blank red-black tree
    tempEmptyTree = emptyTree; // calls copy equality operator

    EXPECT_TRUE(tempEmptyTree.empty()); // expects tempEmptyTree to be empty
    EXPECT_TRUE(emptyTree.empty()); // expects emptyTree to be empty

    RBTree<int> tempBigSizedTree;  // creates temp big-sized red-black tree
    tempBigSizedTree = bigSizedTree; // calls copy equality operator

    EXPECT_EQ(tempBigSizedTree.size(), 10000); // expects tempBigSizedTree size to be 10000
    EXPECT_TRUE(tempBigSizedTree.contains(6)); // expects tempBigSizedTree size to contain element 555
}

TEST_F(RBtreeTest, MoveEqualityOperatorTests)
{
    RBTree<int> tempEmptyTree;  // creates temp blank red-black tree
    tempEmptyTree = std::move(emptyTree); // calls move equality operator

    EXPECT_TRUE(tempEmptyTree.empty()); // expects tempEmptyTree to be empty
    EXPECT_TRUE(emptyTree.empty()); // expects emptyTree to be empty

    RBTree<int> tempBigSizedTree;  // creates temp big-sized red-black tree
    tempBigSizedTree = std::move(bigSizedTree); // calls move equality operator

    EXPECT_EQ(tempBigSizedTree.size(), 10000); // expects tempBigSizedTree size to be 10000
    EXPECT_TRUE(bigSizedTree.empty()); // expects bigSizedTree to be empty
}
