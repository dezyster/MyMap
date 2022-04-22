template <typename Key>
void RBNode<Key>::createNewNode(typename RBNodeBase<Key>::RBNode_ptr shared_this, Key key, typename RBNodeBase<Key>::RBNode_ptr &node)
{
    node = std::make_shared<RBNode<Key>>(key, shared_this);
}
