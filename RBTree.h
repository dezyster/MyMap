#pragma once

#include <initializer_list>

#include "RBNode.h"
#include "RBTreeBase.h"

template <class Key>
class RBTree: public RBTreeBase<Key>
{
protected:
    virtual void createRoot(Key) override;

public:
    RBTree() = default;
    RBTree(const std::initializer_list<Key>&);

    RBTree(const RBTree<Key>&);
    RBTree(const RBTreeBase<Key>&);
    RBTree(RBTree<Key>&&);

    RBTree<Key>& operator=(const RBTree<Key>&);
    RBTree<Key>& operator=(const RBTreeBase<Key>&);
    RBTree<Key>& operator=(RBTree<Key>&&);

    virtual ~RBTree() = default;
};

#include "RBTree.inl"
