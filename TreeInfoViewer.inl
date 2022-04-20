
template <typename Key>
void TreeInfoViewer::printRBNodeKeyAndColor(typename RBNodeBase<Key>::RBNode_ptr rbNode)
{
    std::cout << "I'm " << rbNode->m_key <<
    ", my color is " << (rbNode->m_color == RBNodeBase<Key>::Colors::red ? "Red" : "Black");
}

template <typename Key>
void TreeInfoViewer::printNeighborsInfo(typename RBNodeBase<Key>::RBNode_ptr rbNode)
{
    if(rbNode->m_parent.lock())
    {
        std::cout << ", my parent is " << rbNode->m_parent.lock()->m_key;
    }
    if(rbNode->m_left)
    {
        std::cout << ", my left child is " << rbNode->m_left->m_key;
    }
    if(rbNode->m_right)
    {
        std::cout << ", my right child is " << rbNode->m_right->m_key;
    }
    std::cout << std::endl;
}

template <typename Key>
void TreeInfoViewer::printRBNodeInfo(typename RBNodeBase<Key>::RBNode_ptr rbNode)
{
    printRBNodeKeyAndColor<Key>(rbNode);
    printNeighborsInfo<Key>(rbNode);
    if(rbNode->m_left)
    {
        printRBNodeInfo<Key>(rbNode->m_left);
    }
    if(rbNode->m_right)
    {
        printRBNodeInfo<Key>(rbNode->m_right);
    }
}

template <typename Key, typename Value>
void TreeInfoViewer::printMapNodeInfo(typename MapNode<Key, Value>::MapNode_ptr mapNode)
{
    printRBNodeKeyAndColor<Key>(mapNode);
    std::cout << ", my value is " << mapNode->m_value;
    printNeighborsInfo<Key>(mapNode);
    if(mapNode->m_left)
    {
        printMapNodeInfo<Key, Value>(MapNode<Key,Value>::convertToMapNode(mapNode->m_left));
    }
    if(mapNode->m_right)
    {
        printMapNodeInfo<Key, Value>(MapNode<Key,Value>::convertToMapNode(mapNode->m_right));
    }
}

template <typename Key>
void TreeInfoViewer::printBlackHeight(typename RBNodeBase<Key>::RBNode_ptr rbNode, int &height)
{
    if(rbNode->m_color == RBNodeBase<Key>::Colors::black)
    {
        ++height;
    }

    if(!rbNode->m_left && !rbNode->m_right)
    {
        std::cout << "I'm " << rbNode->m_key << " my black height = " << height << "\n";
    }
    else
    {
        if(rbNode->m_left)
        {
            printBlackHeight<Key>(rbNode->m_left, height);
        }
        if(rbNode->m_right)
        {
            printBlackHeight<Key>(rbNode->m_right, height);
        }
    }

    if(rbNode->m_color == RBNodeBase<Key>::Colors::black)
    {
        --height;
    }
}

template <typename Key>
int TreeInfoViewer::getBlackHeight(typename RBNodeBase<Key>::RBNode_ptr rbNode, int &height)
{
    if(rbNode->m_color == RBNodeBase<Key>::Colors::black)
    {
        ++height;
    }

    if(!rbNode->m_left && !rbNode->m_right)
    {
        return height;
    }
    else
    {
        if(rbNode->m_left)
        {
            return getBlackHeight<Key>(rbNode->m_left, height);
        }
        else
        {
            return getBlackHeight<Key>(rbNode->m_right, height);
        }
    }

    if(rbNode->m_color == RBNodeBase<Key>::Colors::black)
    {
        --height;
    }
}

template <typename Key>
void TreeInfoViewer::checkBlackHeight(typename RBNodeBase<Key>::RBNode_ptr rbNode, int &height, std::vector<int> &heightsVec)
{
    if(rbNode->m_color == RBNodeBase<Key>::Colors::black)
    {
        ++height;
    }

    if(!rbNode->m_left && !rbNode->m_right)
    {
        heightsVec.push_back(height);
    }
    else
    {
        if(rbNode->m_left)
        {
            checkBlackHeight<Key>(rbNode->m_left, height, heightsVec);
        }
        if(rbNode->m_right)
        {
            checkBlackHeight<Key>(rbNode->m_right, height, heightsVec);
        }
    }

    if(rbNode->m_color == RBNodeBase<Key>::Colors::black)
    {
        --height;
    }
}

template <typename Key>
void TreeInfoViewer::printTreeInfo(const RBTreeBase<Key> &rbTree)
{
    if(rbTree.m_root)
    {
        printRBNodeInfo<Key>(rbTree.m_root);
    }
    else
    {
        std::cout << "Tree is empty!\n";
    }
}

template <typename Key, typename Value>
void TreeInfoViewer::printTreeInfo(const Map<Key, Value> &myMap)
{
    if(myMap.m_root)
    {
        printMapNodeInfo<Key, Value>(MapNode<Key,Value>::convertToMapNode(myMap.m_root));
    }
    else
    {
        std::cout << "Map is empty!\n";
    }
}

template <typename Key>
void TreeInfoViewer::printBlackHeight(const RBTreeBase<Key> &rbTree)
{
    int height = 0;
    if(rbTree.m_root)
    {
        printBlackHeight<Key>(rbTree.m_root, height);
    }
    else
    {
        std::cout << "Tree is empty!\n";
    }
}

template <typename Key>
int TreeInfoViewer::getBlackHeight(const RBTreeBase<Key> &rbTree)
{
    int height = 0;

    if(rbTree.m_root)
    {
        return getBlackHeight<Key>(rbTree.m_root, height);
    }

    return height;
}

template<typename T>
bool allEqual(std::vector<T> const &vec)
{
    if (vec.size() == 0)
    {
        return false;
    }

    return std::equal(vec.begin() + 1, vec.end(), vec.begin());
}

template <typename Key>
bool TreeInfoViewer::checkBlackHeight(const RBTreeBase<Key> &rbTree)
{
    int height = 0;
    std::vector<int> heightsVec;

    checkBlackHeight<Key>(rbTree.m_root, height, heightsVec);

    return allEqual(heightsVec);
}
