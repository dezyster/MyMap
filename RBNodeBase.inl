template <typename Key>
RBNodeBase<Key>::RBNodeBase(Key key)
    :m_key{ key }, m_color{ Colors::black }, m_parent{}, m_left { nullptr }, m_right { nullptr }
{

}

template <typename Key>
RBNodeBase<Key>::RBNodeBase(Key key, RBNode_ptr parent)
    :m_key{ key }, m_color{ Colors::red }, m_parent{ parent }, m_left { nullptr }, m_right { nullptr }
{

}

template <typename Key>
void RBNodeBase<Key>::swapParents(RBNode_ptr &root, RBNode_ptr shared_this, RBNode_ptr &nodeToRoll)
{
    if(m_parent.lock())
    {
        if(m_parent.lock()->m_right == shared_this)
        {
           m_parent.lock()->m_right = nodeToRoll;
        }
        else
        {
            m_parent.lock()->m_left = nodeToRoll;
        }
    }

    if(!m_parent.lock())
    {
        root = nodeToRoll;
    }

    auto tempParent = m_parent;
    m_parent = nodeToRoll;

    nodeToRoll->m_parent = tempParent;
}

template <typename Key>
void RBNodeBase<Key>::moveOtherNode(RBNode_ptr shared_this, RBNode_ptr &nodeToRoll, RBNode_ptr &otherNode)
{
    auto tempNode = otherNode;
    otherNode = shared_this;

    nodeToRoll = tempNode;
    if(nodeToRoll)
    {
        nodeToRoll->m_parent = shared_this;
    }
}

template <typename Key>
void RBNodeBase<Key>::makeRoll(RBNode_ptr &root, RBNode_ptr shared_this, RBNode_ptr &nodeToRoll, RBNode_ptr &otherNode)
{
    swapParents(root, shared_this, nodeToRoll);

    std::swap(m_color, nodeToRoll->m_color);

    moveOtherNode(shared_this, nodeToRoll, otherNode);
}

template <typename Key>
void RBNodeBase<Key>::rollRight(RBNode_ptr &root, RBNode_ptr shared_this)
{
    makeRoll(root, shared_this, m_left, m_left->m_right);
}

template <typename Key>
void RBNodeBase<Key>::rollLeft(RBNode_ptr &root, RBNode_ptr shared_this)
{
    makeRoll(root, shared_this, m_right, m_right->m_left);
}

template <typename Key>
bool RBNodeBase<Key>::isNodeRed(RBNode_ptr node)
{
    if(node)
    {
        return node->m_color == Colors::red;
    }
    return false;
}

template <typename Key>
void RBNodeBase<Key>::rollTree(RBNode_ptr &root, RBNode_ptr shared_this, RBNode_ptr &node)
{
    if(node == m_left)
    {
        if(isNodeRed(node->m_right))
        {
            node->rollLeft(root, node);
        }
        rollRight(root, shared_this);
    }
    else
    {
        if(isNodeRed(node->m_left))
        {
            node->rollRight(root, node);
        }
        rollLeft(root, shared_this);
    }
}

template <typename Key>
bool RBNodeBase<Key>::tryRecolor()
{
    if(m_left && m_right)
    {
        if(m_left->m_color == Colors::red && m_right->m_color == Colors::red)
        {
            m_left-> m_color = Colors::black;
            m_right->m_color = Colors::black;
            m_color = Colors::red;

            return 1; //success
        }
    }
    return 0; //fail
}

template <typename Key>
bool RBNodeBase<Key>::hasRedChilds()
{
    return isNodeRed(m_right) || isNodeRed(m_left);
}

template <typename Key>
void RBNodeBase<Key>::checkRBRules(RBNode_ptr &root, RBNode_ptr shared_this, RBNode_ptr &node)
{
    if(node)
    {
        if(node->m_color == Colors::red && node->hasRedChilds())
        {
            if(!tryRecolor())
            {
                rollTree(root, shared_this, node);
            }
        }
    }
}

template <typename Key>
void RBNodeBase<Key>::startBalancing(RBNode_ptr &root, RBNode_ptr shared_this)
{
    checkRBRules(root, shared_this, m_left);
    checkRBRules(root, shared_this, m_right);
    if(m_parent.lock())
    {
        m_parent.lock()->startBalancing(root, m_parent.lock());
    }
    else
    {
        m_color = Colors::black;
    }
}

template <typename Key>
void RBNodeBase<Key>::addToNode(RBNode_ptr &root, RBNode_ptr shared_this, Key key, RBNode_ptr &node)
{
    if(node)
    {
        node->addNode(root, node, key);
    }
    else
    {
        createNewNode(shared_this, key, node);
        if(m_parent.lock())
        {
            m_parent.lock()->startBalancing(root, m_parent.lock());
        }
    }
}

template <typename Key>
void RBNodeBase<Key>::addNode(RBNode_ptr &root, RBNode_ptr shared_this, Key key)
{
    if(key > m_key)
    {
        addToNode(root, shared_this, key, m_right);
    }
    else
    {
        addToNode(root, shared_this, key, m_left);
    }
}

template <typename Key>
bool RBNodeBase<Key>::isKeyExist(const Key &key) const
{
    if(m_key == key)
    {
        return true;
    }
    else if(m_right && key > m_key)
    {
        return m_right->isKeyExist(key);
    }
    else if(m_left && key < m_key)
    {
        return m_left->isKeyExist(key);
    }
    return false;
}

template <typename Key>
void RBNodeBase<Key>::getSize(size_t &size) const
{
    if(m_left)
    {
        m_left->getSize(++size);
    }
    if(m_right)
    {
        m_right->getSize(++size);
    }
}

template <typename Key>
void RBNodeBase<Key>::copyNode(RBNode_ptr &othersPrev, RBNode_ptr nodeToCopyFrom, RBNode_ptr &othersNode)
{
    othersPrev->createNewNode(othersPrev, nodeToCopyFrom->getKey(), othersNode);
    nodeToCopyFrom->copyElements(othersNode);
}

template <typename Key>
void RBNodeBase<Key>::copyElements(RBNode_ptr &othersPrev)
{
    if(m_left)
    {
        copyNode(othersPrev, m_left, othersPrev->m_left);
    }
    if(m_right)
    {
        copyNode(othersPrev, m_right, othersPrev->m_right);
    }
}
