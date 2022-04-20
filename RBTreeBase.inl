template <typename Key>
void RBTreeBase<Key>::copyTree(const RBTreeBase<Key> &other)
{
    if(other.m_root)
    {
        createRoot(other.m_root->getKey());
        other.m_root->copyElements(m_root);
    }
    else
    {
        m_root = nullptr;
    }
}

template <typename Key>
void RBTreeBase<Key>::moveTree(RBTreeBase<Key> &&other)
{
    m_root = std::move(other.m_root);
}

template <typename Key>
void RBTreeBase<Key>::addNode(Key key)
{
    if(m_root)
    {
        m_root->addNode(m_root, m_root, key);
    }
    else
    {
        createRoot(key);
    }
}

template <typename Key>
bool RBTreeBase<Key>::contains(const Key &key) const
{
    if(m_root)
    {
        return m_root->isKeyExist(key);
    }
    else
    {
        return false;
    }
}

template <typename Key>
void RBTreeBase<Key>::erase()
{
    m_root = nullptr;
}

template <typename Key>
int RBTreeBase<Key>::size() const
{
    if(m_root)
    {
        int treeSize{ 1 };

        m_root->getSize(treeSize);

        return treeSize;
    }

    return 0;
}

template <typename Key>
bool RBTreeBase<Key>::empty() const
{
    return !m_root;
}
