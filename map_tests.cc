#include <gtest/gtest.h>

#include "Map.h"

class MapTest: public ::testing::Test {
public:
    MapTest():
        emptyMap{}, bigSizedMap{}, constMap{ {1,11}, {2,22}, {3,33}, {4,44}, {5,55}, {6,66} } // initialize maps
    {

    }
    ~MapTest() = default;

    void SetUp()
    {
        for(int i = 0; i < 10000; ++i)
        {
            bigSizedMap[i] = i * 11; // adds 10000 elements to bigSizedMap
        }
    }
    void TearDown()
    {
        emptyMap = Map<int, int>{}; // make emptyMap a blank map
        bigSizedMap = Map<int, int>{}; // make bigSizedMap a blank map
    }

protected:
    Map<int, int> emptyMap;  // blank map
    Map<int, int> bigSizedMap;  // big-sized map
    const Map<int, int> constMap;  // const map
};

TEST_F(MapTest, sizeTest)
{
    EXPECT_EQ(emptyMap.size(), 0); // expects emptyMap size to be 0

    EXPECT_EQ(bigSizedMap.size(), 10000); // expects bigSizedMap size to be 10000

    EXPECT_EQ(constMap.size(), 6); // expects constMap size to be 6
}

TEST_F(MapTest, emptyTest)
{
    EXPECT_TRUE(emptyMap.empty()); // expects emptyMap to be empty

    EXPECT_FALSE(bigSizedMap.empty()); // expects bigSizedMap not to be empty

    EXPECT_FALSE(constMap.empty()); // expects constMap not to be empty
}

TEST_F(MapTest, containsTest)
{
    EXPECT_FALSE(emptyMap.contains(5)); // expects emptyMap not to contain element 5

    EXPECT_TRUE(bigSizedMap.contains(555)); // expects bigSizedMap to contain element 555
    EXPECT_FALSE(bigSizedMap.contains(-10)); // expects bigSizedMap not to contain element -10

    EXPECT_TRUE(constMap.contains(5)); // expects constMap size to contain element 5
    EXPECT_FALSE(constMap.contains(7)); // expects constMap size not to contain element 7
}

TEST_F(MapTest, eraseTest)
{
    bigSizedMap.erase();

    EXPECT_TRUE(bigSizedMap.empty()); // expects bigSizedMap to be empty after erase
    EXPECT_EQ(bigSizedMap.size(), 0); // expects bigSizedMap's size to be 0 after erase
}

TEST_F(MapTest, ValueTest)
{
    EXPECT_EQ(bigSizedMap[5], 55); // expects bigSizedMap's element with key 5 to have value 55
    EXPECT_EQ(constMap[5], 55); // expects constMap's element with key 5 to have value 55
}

TEST_F(MapTest, insertWithKeyValueTest)
{
    emptyMap.insert(9,99); // inserts element with key 9 and value 99

    EXPECT_TRUE(emptyMap.contains(9)); // expects emptyMap to contain element 9
    EXPECT_EQ(emptyMap[9], 99); // expects emptyMap's element with key 9 to have value 99

    emptyMap.insert(9,88); // tries to insert element with key 9 and value 88 ( needs to be ignored )

    EXPECT_EQ(emptyMap[9], 99); // expects emptyMap's element with key 9 to have value 99
    EXPECT_EQ(emptyMap.size(), 1); // expects emptyMap size to be 1
}

TEST_F(MapTest, insertWithPairTest)
{
    emptyMap.insert(std::pair<int,int>(9,99)); // inserts element with key 9 and value 99

    EXPECT_TRUE(emptyMap.contains(9)); // expects emptyMap not to contain element 5
    EXPECT_EQ(emptyMap[9], 99); // expects emptyMap's element with key 9 to have value 99

    emptyMap.insert(std::pair<int,int>(9,99)); // tries to insert element with key 9 and value 88

    EXPECT_EQ(emptyMap[9], 99); // expects emptyMap's element with key 9 to have value 99
    EXPECT_EQ(emptyMap.size(), 1); // expects emptyMap size to be 1
}

TEST_F(MapTest, insertOrAssignWithKeyValueTest)
{
    emptyMap.insert_or_assign(9,99); // inserts element with key 9 and value 99

    EXPECT_TRUE(emptyMap.contains(9)); // expects emptyMap to contain element 9
    EXPECT_EQ(emptyMap[9], 99); // expects emptyMap's element with key 9 to have value 99

    emptyMap.insert_or_assign(9,88); // tries to insert element with key 9 and value 88

    EXPECT_EQ(emptyMap[9], 88); // expects emptyMap's element with key 9 to have value 88
}

TEST_F(MapTest, insertOrAssignWithPairTest)
{
    emptyMap.insert_or_assign(std::pair<int,int>(9,99)); // inserts element with key 9 and value 99

    EXPECT_TRUE(emptyMap.contains(9)); // expects emptyMap to contain element 9
    EXPECT_EQ(emptyMap[9], 99); // expects emptyMap's element with key 9 to have value 99

    emptyMap.insert_or_assign(std::pair<int,int>(9,88)); // tries to insert element with key 9 and value 88

    EXPECT_EQ(emptyMap[9], 88); // expects emptyMap's element with key 9 to have value 88
}

TEST_F(MapTest, CopyCopyConstructorTests)
{
    Map<int, int> tempemptyMap(emptyMap);  // creates temp blank red-black map and calls copy copy constructor

    EXPECT_TRUE(tempemptyMap.empty()); // expects tempEmptyMap to be empty
    EXPECT_TRUE(emptyMap.empty()); // expects emptyMap to be empty

    Map<int, int> tempbigSizedMap(bigSizedMap);  // creates temp big-sized red-black map calls copy copy constructor

    EXPECT_EQ(tempbigSizedMap.size(), 10000); // expects tempBigSizedMap size to be 10000
    EXPECT_TRUE(tempbigSizedMap.contains(6)); // expects tempBigSizedMap to contain element 555

    const Map<int, int> tempconstMap(constMap);  // creates temp const map calls copy copy constructor

    EXPECT_EQ(tempconstMap.size(), 6); // expects tempConstMap size to be 6
    EXPECT_TRUE(tempconstMap.contains(6)); // expects tempConstMap to contain element 6
}

TEST_F(MapTest, MoveCopyConstructorTests)
{
    Map<int, int> tempemptyMap(std::move(emptyMap));  // creates temp blank red-black map calls move copy constructor

    EXPECT_TRUE(tempemptyMap.empty()); // expects tempEmptyMap to be empty
    EXPECT_TRUE(emptyMap.empty()); // expects emptyMap to be empty

    Map<int, int> tempbigSizedMap(std::move(bigSizedMap));  // creates temp big-sized red-black map move copy constructor

    EXPECT_EQ(tempbigSizedMap.size(), 10000); // expects tempBigSizedMap size to be 10000
    EXPECT_TRUE(bigSizedMap.empty()); // expects bigSizedMap to be empty
}

TEST_F(MapTest, CopyEqualityOperatorTests)
{
    Map<int, int> tempemptyMap;  // creates temp blank red-black map
    tempemptyMap = emptyMap; // calls copy equality operator

    EXPECT_TRUE(tempemptyMap.empty()); // expects tempEmptyMap to be empty
    EXPECT_TRUE(emptyMap.empty()); // expects emptyMap to be empty

    Map<int, int> tempbigSizedMap;  // creates temp big-sized red-black map
    tempbigSizedMap = bigSizedMap; // calls copy equality operator

    EXPECT_EQ(tempbigSizedMap.size(), 10000); // expects tempBigSizedMap size to be 10000
    EXPECT_TRUE(tempbigSizedMap.contains(6)); // expects tempBigSizedMap to contain element 555
}

TEST_F(MapTest, MoveEqualityOperatorTests)
{
    Map<int, int> tempemptyMap;  // creates temp blank red-black map
    tempemptyMap = std::move(emptyMap); // calls move equality operator

    EXPECT_TRUE(tempemptyMap.empty()); // expects tempEmptyMap to be empty
    EXPECT_TRUE(emptyMap.empty()); // expects emptyMap to be empty

    Map<int, int> tempbigSizedMap;  // creates temp big-sized red-black map
    tempbigSizedMap = std::move(bigSizedMap); // calls move equality operator

    EXPECT_EQ(tempbigSizedMap.size(), 10000); // expects tempBigSizedMap size to be 10000
    EXPECT_TRUE(bigSizedMap.empty()); // expects bigSizedMap to be empty
}
