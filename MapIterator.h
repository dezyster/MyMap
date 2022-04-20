#pragma once
#include <memory>

template<typename MapPair, typename MapNode>
class MapIterator: public std::iterator<std::input_iterator_tag, MapPair>
{
    std::weak_ptr<MapNode> m_mapNode;
    std::unique_ptr<MapPair> m_pair;

public:
    MapIterator(std::weak_ptr<MapNode>);
    MapIterator(const MapIterator&);

    bool operator!=(MapIterator const&) const;
    bool operator==(MapIterator const&) const;
    typename MapIterator::reference operator*() const;
    typename MapIterator::pointer operator->() const;
    MapIterator& operator++();

    ~MapIterator() = default;
};

#include "MapIterator.inl"
