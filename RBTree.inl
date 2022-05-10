template <typename Key>
typename RBNodeBase<Key>::RBNode_ptr RBTree<Key>::getRoot(Key key)
{
    return std::make_shared<RBNode<Key>>(key);
}

template <typename Key>
RBTree<Key>::RBTree(const std::initializer_list<Key> &list)
    :RBTreeBase<Key>()
{
    for(auto &key: list)
    {
        this->addKey(key);
    }
}

template <typename Key>
RBTree<Key>::RBTree(const RBTree<Key> &other)
    :RBTreeBase<Key>()
{
    this->copyTree(other);
}

template <typename Key>
RBTree<Key>::RBTree(const RBTreeBase<Key> &other)
    :RBTreeBase<Key>()
{
    this->copyTree(other);
}

template <typename Key>
RBTree<Key>::RBTree(RBTree<Key> &&other)
    :RBTreeBase<Key>()
{
    this->moveTree(dynamic_cast<RBTreeBase<Key>&&>(other));
}

template <typename Key>
RBTree<Key>& RBTree<Key>::operator=(const RBTree<Key> &other)
{
    this->copyTree(other);

    return *this;
}

template <typename Key>
RBTree<Key>& RBTree<Key>::operator=(const RBTreeBase<Key> &other)
{
    this->copyTree(other);

    return *this;
}

template <typename Key>
RBTree<Key>& RBTree<Key>::operator=(RBTree<Key> &&other)
{
    this->moveTree(dynamic_cast<RBTreeBase<Key>&&>(other));

    return *this;
}
