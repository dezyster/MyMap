template <typename Key, typename Value>
Map<Key, Value>::Map(const std::initializer_list<std::pair<Key, Value>> &list)
    :RBTreeBase<Key>()
{
    for(auto &pair : list)
    {
        if(!(this->contains(pair.first)))
        {
            this->addNode(pair.first);
        }
        MapNode<Key,Value>::convertToMapNode(this->m_root)->getValueByKey(pair.first) = pair.second;
    }
}

template <typename Key, typename Value>
void Map<Key, Value>::copyMap(const Map<Key, Value> &other)
{
    this->copyTree(other);
    if(this->m_root)
    {
        MapNode<Key,Value>::convertToMapNode(this->m_root)->getValue() = MapNode<Key,Value>::convertToMapNode(other.m_root)->getValue();
    }
}

template <typename Key, typename Value>
Map<Key, Value>::Map(const Map<Key, Value> &other)
    :RBTreeBase<Key>()
{
    copyMap(other);
}

template <typename Key, typename Value>
Map<Key, Value>::Map(const RBTreeBase<Key> &other)
    :RBTreeBase<Key>()
{
    this->copyTree(other);
}

template <typename Key, typename Value>
Map<Key, Value>::Map(Map<Key, Value> &&other)
    :RBTreeBase<Key>()
{
    this->moveTree(dynamic_cast<RBTreeBase<Key>&&>(other));
}

template <typename Key, typename Value>
Map<Key, Value>& Map<Key, Value>::operator=(const Map<Key, Value> &other)
{
    copyMap(other);

    return *this;
}

template <typename Key, typename Value>
Map<Key, Value>& Map<Key, Value>::operator=(const RBTreeBase<Key> &other)
{
    this->copyTree(other);

    return *this;
}

template <typename Key, typename Value>
Map<Key, Value>& Map<Key, Value>::operator=(Map<Key, Value> &&other)
{
    this->moveTree(dynamic_cast<RBTreeBase<Key>&&>(other));

    return *this;
}

template <typename Key, typename Value>
void Map<Key, Value>::createRoot(Key key)
{
    this->m_root = std::make_shared<MapNode<Key, Value>>(key);
}

template <typename Key, typename Value>
Value& Map<Key, Value>::operator[](Key key)
{
    if(!(this->contains(key)))
    {
        this->addNode(key);
    }
    return MapNode<Key,Value>::convertToMapNode(this->m_root)->getValueByKey(key);
}

template <typename Key, typename Value>
const Value& Map<Key, Value>::operator[](Key key) const
{
    return MapNode<Key,Value>::convertToMapNode(this->m_root)->getValueByKey(key);
}

template <typename Key, typename Value>
void Map<Key, Value>::insert(Key key, Value value)
{
    if(!(this->contains(key)))
    {
        this->addNode(key);
        MapNode<Key,Value>::convertToMapNode(this->m_root)->getValueByKey(key) = value;
    }
}

template <typename Key, typename Value>
void Map<Key, Value>::insert(const std::pair<Key, Value> &pair)
{
    insert(pair.first, pair.second);
}

template <typename Key, typename Value>
void Map<Key, Value>::insert_or_assign(Key key, Value value)
{
    if(!(this->contains(key)))
    {
        this->addNode(key);
    }
    MapNode<Key,Value>::convertToMapNode(this->m_root)->getValueByKey(key) = value;
}

template <typename Key, typename Value>
void Map<Key, Value>::insert_or_assign(const std::pair<Key, Value> &pair)
{
    insert_or_assign(pair.first, pair.second);
}

template <typename Key, typename Value>
typename Map<Key, Value>::iterator Map<Key, Value>::begin()
{
    if(this->m_root)
    {
        return iterator(MapNode<Key,Value>::convertToMapNode(this->m_root)->
                        getMostLeft(MapNode<Key,Value>::convertToMapNode(this->m_root)));
    }
    else
    {
        return iterator(std::weak_ptr<MapNode<Key, Value>>{});
    }
}

template <typename Key, typename Value>
typename Map<Key, Value>::iterator Map<Key, Value>::end()
{
    return iterator(std::weak_ptr<MapNode<Key, Value>>{});
}

template <typename Key, typename Value>
typename Map<Key, Value>::const_iterator Map<Key, Value>::begin() const
{
    if(this->m_root)
    {
        return const_iterator(MapNode<Key,Value>::convertToMapNode(this->m_root)->
                              getMostLeft(MapNode<Key,Value>::convertToMapNode(this->m_root)));
    }
    else
    {
        return const_iterator(std::weak_ptr<MapNode<Key, Value>>{});
    }
}

template <typename Key, typename Value>
typename Map<Key, Value>::const_iterator Map<Key, Value>::end() const
{
    return const_iterator(std::weak_ptr<MapNode<Key, Value>>{});
}
