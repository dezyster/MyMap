#pragma once

#include "RBNodeBase.h"

template <class Key>
class RBNode: public RBNodeBase<Key>
{
protected:
    virtual typename RBNodeBase<Key>::RBNode_ptr getNewNode(typename RBNodeBase<Key>::RBNode_ptr, Key) override;

public:
    RBNode(Key key): RBNodeBase<Key>(key){};
    RBNode(Key key, typename RBNodeBase<Key>::RBNode_ptr node): RBNodeBase<Key>(key, node){};

    virtual ~RBNode() = default;
};

#include "RBNode.inl"
