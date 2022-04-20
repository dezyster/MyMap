#include <memory>

template<typename MapPair, typename MapNode>
MapIterator<MapPair, MapNode>::MapIterator(std::weak_ptr<MapNode> mapNode)
    :m_mapNode{ mapNode }, m_pair{ std::make_unique<MapPair>(m_mapNode.lock()->getKey(), m_mapNode.lock()->getValue()) }
{

}

template<typename MapPair, typename MapNode>
MapIterator<MapPair, MapNode>::MapIterator(const MapIterator &other)
    :m_mapNode(other.m_mapNode), m_pair{ std::make_unique<MapPair>(m_mapNode.lock()->getKey(), m_mapNode.lock()->getValue()) }
{

}

template<typename MapPair, typename MapNode>
bool MapIterator<MapPair, MapNode>::operator!=(MapIterator const& other) const
{
    return m_mapNode.lock() != other.m_mapNode.lock();
}

template<typename MapPair, typename MapNode>
bool MapIterator<MapPair, MapNode>::operator==(MapIterator const& other) const
{
    return m_mapNode.lock() == other.m_mapNode.lock();
}

template<typename MapPair, typename MapNode>
typename MapIterator<MapPair, MapNode>::reference MapIterator<MapPair, MapNode>::operator*() const
{
    return *m_pair;
}

template<typename MapPair, typename MapNode>
typename MapIterator<MapPair, MapNode>::pointer MapIterator<MapPair, MapNode>::operator->() const
{
    return m_pair.get();
}

template<typename MapPair, typename MapNode>
MapIterator<MapPair, MapNode>& MapIterator<MapPair, MapNode>::operator++()
{
    m_mapNode = m_mapNode.lock()->getNextNode(m_mapNode.lock());

    m_pair.reset(new MapPair(m_mapNode.lock()->getKey(), m_mapNode.lock()->getValue()));

    return *this;
}
