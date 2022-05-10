#pragma once

#include <initializer_list>

#include "RBTreeBase.h"
#include "MapNode.h"
#include "MapIterator.h"

template <class Key, class Value>
class Map: public RBTreeBase<Key>
{
    virtual typename RBNodeBase<Key>::RBNode_ptr getRoot(Key) override;

    void copyMap(const Map<Key, Value>&);

public:
    Map() = default;
    Map(const std::initializer_list<std::pair<Key, Value>>&);

    Map(const Map<Key, Value>&);
    Map(const RBTreeBase<Key>&);
    Map(Map<Key, Value>&&);

    Map<Key, Value>& operator=(const Map<Key, Value>&);
    Map<Key, Value>& operator=(const RBTreeBase<Key>&);
    Map<Key, Value>& operator=(Map<Key, Value>&&);

    Value& operator[](Key);
    const Value& operator[](Key) const;

    void insert(Key, Value);
    void insert(const std::pair<Key, Value>&);

    void insert_or_assign(Key, Value);
    void insert_or_assign(const std::pair<Key, Value>&);

/****************  Iterators zone   *****************/
    using iterator = MapIterator<std::pair<const Key&, Value&>, MapNode<Key, Value>>;
    using const_iterator = MapIterator<std::pair<const Key&, const Value&>, MapNode<Key, Value>>;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
/****************************************************/

    virtual ~Map() override = default;
};

#include "Map.inl"
