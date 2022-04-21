#pragma once

#include <memory>

class TreeInfoViewer;

template <class Key>
class RBNodeBase
{
    friend class TreeInfoViewer; // Needed to gain access to Info Viewer

public:
    enum class Colors
    {
        black,
        red
    };

    using RBNode_ptr = std::shared_ptr<RBNodeBase<Key>>;

protected:
    Key m_key;
    Colors m_color;
    std::weak_ptr<RBNodeBase<Key>> m_parent;
    RBNode_ptr m_left;
    RBNode_ptr m_right;

    virtual void createNewNode(RBNode_ptr, Key, RBNode_ptr&) = 0;
    virtual void copyNode(RBNode_ptr&, RBNode_ptr, RBNode_ptr&) = 0;

    void swapParents(RBNode_ptr&, RBNode_ptr, RBNode_ptr&);
    void moveOtherNode(RBNode_ptr, RBNode_ptr&, RBNode_ptr&);
    void makeRoll(RBNode_ptr&, RBNode_ptr, RBNode_ptr&, RBNode_ptr&);
    void rollRight(RBNode_ptr&, RBNode_ptr);
    void rollLeft(RBNode_ptr&, RBNode_ptr);
    bool tryRecolor();
    bool isNodeRed(RBNode_ptr);
    bool hasRedChilds();
    void rollTree(RBNode_ptr&, RBNode_ptr, RBNode_ptr&);
    void checkRBRules(RBNode_ptr&, RBNode_ptr, RBNode_ptr&);
    void startBalancing(RBNode_ptr&, RBNode_ptr);
    void addToNode(RBNode_ptr&, RBNode_ptr, Key, RBNode_ptr&);

public:
    RBNodeBase(Key);
    RBNodeBase(Key, RBNode_ptr);

    const Key& getKey() const { return m_key; };
    void addNode(RBNode_ptr&, RBNode_ptr, Key);
    bool isKeyExist(const Key&) const;
    void getSize(size_t&) const;

    void copyElements(RBNode_ptr&);

    virtual ~RBNodeBase() = default;
};

#include "RBNodeBase.inl"
