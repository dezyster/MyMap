#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "Map.h"
#include "RBTree.h"

class TreeInfoViewer
{
    TreeInfoViewer() = delete;

    template <typename Key>
    static void printRBNodeKeyAndColor(typename RBNodeBase<Key>::RBNode_ptr);

    template <typename Key>
    static void printNeighborsInfo(typename RBNodeBase<Key>::RBNode_ptr);

    template <typename Key>
    static void printRBNodeInfo(typename RBNodeBase<Key>::RBNode_ptr);

    template <typename Key, typename Value>
    static void printMapNodeInfo(typename MapNode<Key, Value>::MapNode_ptr);

    template <typename Key>
    static void printBlackHeight(typename RBNodeBase<Key>::RBNode_ptr, int&);

    template <typename Key>
    static int getBlackHeight(typename RBNodeBase<Key>::RBNode_ptr, int&);

    template <typename Key>
    static void checkBlackHeight(typename RBNodeBase<Key>::RBNode_ptr, int&, std::vector<int>&);

public:
    template <typename Key>
    static void printTreeInfo(const RBTreeBase<Key>&);

    template <typename Key, typename Value>
    static void printTreeInfo(const Map<Key, Value>&);

    template <typename Key>
    static void printBlackHeight(const RBTreeBase<Key>&);

    template <typename Key>
    static int getBlackHeight(const RBTreeBase<Key>&);

    template <typename Key>
    static bool checkBlackHeight(const RBTreeBase<Key>&);
};

#include "TreeInfoViewer.inl"
