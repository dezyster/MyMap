#pragma once

#include "RBNodeBase.h"

template <class Key>
class RBTreeBase
{
    friend class TreeInfoViewer; // Needed to gain access to Info Viewer

protected:
    typename RBNodeBase<Key>::RBNode_ptr m_root;

    virtual void createRoot(Key) = 0;

    void copyTree(const RBTreeBase<Key>&);
    void moveTree(RBTreeBase<Key>&&);

public:
    RBTreeBase(): m_root{ nullptr }{};

    void addKey(Key);
    bool contains(const Key&) const;
    void erase();
    size_t size() const;
    bool empty() const;

    virtual ~RBTreeBase() = default;
};

#include "RBTreeBase.inl"
