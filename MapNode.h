#pragma once

#include "RBNodeBase.h"

template <class Key, class Value>
class MapNode: public RBNodeBase<Key>
{
    friend class TreeInfoViewer; // Needed to gain access to Info Viewer

    Value m_value;

protected:

    virtual void createNewNode(typename RBNodeBase<Key>::RBNode_ptr, Key, typename RBNodeBase<Key>::RBNode_ptr&) override;

    virtual void copyNode(typename RBNodeBase<Key>::RBNode_ptr&, typename RBNodeBase<Key>::RBNode_ptr, typename RBNodeBase<Key>::RBNode_ptr&) override;

public:
    using MapNode_ptr = std::shared_ptr<MapNode<Key, Value>>;

    static MapNode_ptr convertToMapNode(typename RBNodeBase<Key>::RBNode_ptr);

    MapNode(Key key): RBNodeBase<Key>(key), m_value{} {}
    MapNode(Key key, typename RBNodeBase<Key>::RBNode_ptr node): RBNodeBase<Key>(key, node), m_value{} {}

    Value& getValueByKey(Key);
    const Key& getKey() const;
    Value& getValue();

/****************  Iterators zone   *****************/
    MapNode_ptr getMostLeft(MapNode_ptr);
    MapNode_ptr findSuitableParent(MapNode_ptr);
    MapNode_ptr getNextNode(MapNode_ptr);
/****************************************************/

    virtual ~MapNode() override = default;
};

#include "MapNode.inl"
