template <typename Key>
typename RBNodeBase<Key>::RBNode_ptr RBNode<Key>::getNewNode(typename RBNodeBase<Key>::RBNode_ptr shared_this, Key key)
{
    return std::make_shared<RBNode<Key>>(key, shared_this);
}
