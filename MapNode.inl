template <typename Key, typename Value>
void MapNode<Key, Value>::createNewNode(typename RBNodeBase<Key>::RBNode_ptr shared_this, Key key,
                                        typename RBNodeBase<Key>::RBNode_ptr &node)
{
    node = std::make_shared<MapNode<Key, Value>>(key, shared_this);
}

template <typename Key, typename Value>
typename MapNode<Key, Value>::MapNode_ptr MapNode<Key, Value>::convertToMapNode(typename RBNodeBase<Key>::RBNode_ptr rbNode)
{
    return std::dynamic_pointer_cast<MapNode<Key, Value>>(rbNode);
}

template <typename Key, typename Value>
Value& MapNode<Key, Value>::getValueByKey(Key key)
{
    if(this->m_key == key)
    {
        return m_value;
    }
    else if(key > this->m_key)
    {
        return convertToMapNode(this->m_right)->getValueByKey(key);
    }
    else
    {
        return convertToMapNode(this->m_left)->getValueByKey(key);
    }
}

template <typename Key, typename Value>
const Key& MapNode<Key, Value>::getKey() const
{
    return this->m_key;
}

template <typename Key, typename Value>
Value& MapNode<Key, Value>::getValue()
{
    return this->m_value;
}

/****************  Iterators zone   *****************/
template <typename Key, typename Value>
typename MapNode<Key, Value>::MapNode_ptr MapNode<Key, Value>::getMostLeft(MapNode_ptr shared_this)
{
    if(this->m_left)
    {
        const auto &convertedLeft{ convertToMapNode(this->m_left) };
        return convertedLeft->getMostLeft(convertedLeft);
    }
    else
    {
        return shared_this;
    }
}

template <typename Key, typename Value>
typename MapNode<Key, Value>::MapNode_ptr MapNode<Key, Value>::findSuitableParent(MapNode_ptr shared_this)
{
    if(this->m_parent.lock())
    {
        const auto &convertedParent{ convertToMapNode(this->m_parent.lock()) };
        if(convertedParent->m_right == shared_this)
        {
            return convertedParent->findSuitableParent(convertedParent);
        }
        else
        {
            return convertedParent;
        }
    }
    else
    {
        return nullptr;
    }
}

template <typename Key, typename Value>
typename MapNode<Key, Value>::MapNode_ptr MapNode<Key, Value>::getNextNode(MapNode_ptr shared_this)
{
    if(this->m_right)
    {
        const auto &convertedRight{ convertToMapNode(this->m_right) };
        return convertedRight->getMostLeft(convertedRight);
    }
    else if(this->m_parent.lock())
    {
        return findSuitableParent(shared_this);
    }
    else
    {
        return nullptr;
    }
}
/****************************************************/
