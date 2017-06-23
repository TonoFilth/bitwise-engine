template <typename T>
bw::List<T>::List() :
    m_first(nullptr),
    m_last(nullptr),
    m_itemCount(0),
    m_allocator(bw::memory::generic_allocator())
{
}

// -----------------------------------------------------------------------------

template <typename T>
bw::List<T>::List(Allocator& allocator) :
    m_first(nullptr),
    m_last(nullptr),
    m_itemCount(0),
    m_allocator(allocator)
{
}

// -----------------------------------------------------------------------------

template <typename T>
bw::List<T>::~List()
{
    Node* node = m_first;

    while (node != nullptr)
    {
        Node* next = node->next;

        node->item.~T();
        m_allocator.deallocate(node);
        node = next;
    }
}

// -----------------------------------------------------------------------------

template <typename T>
void bw::List<T>::add(const T& item)
{
    Node* node = m_allocator.allocateObject<Node>(item);

    node->next = nullptr;
    node->prev = nullptr;

    if (m_first == nullptr)
    {
        m_first = node;
        m_last  = node;
    }
    else
    {
        m_last->next = node;
        node->prev   = m_last;
        m_last       = node;
    }

    ++m_itemCount;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::List<T>::iterator bw::List<T>::insert(const_iterator it, const T& item)
{
    Node* itNode = it.node();
    Node* node   = m_allocator.allocateObject<Node>(item);

    node->prev   = itNode->prev;
    node->next   = itNode;
    itNode->prev = node;

    if (m_first == itNode)
    {
        m_first = node;
    }
    
    ++m_itemCount;

    return iterator(node);
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::List<T>::iterator bw::List<T>::remove(const_iterator it)
{
    Node* node = it.node();

    if (node->prev != nullptr) node->prev->next = node->next;
    if (node->next != nullptr) node->next->prev = node->prev;

    if (m_first == node)
    {
        m_first = node->next;
    }

    iterator nextIt;

    if (m_last == node)
    {
        m_last = node->prev;
        nextIt = iterator(nullptr);
    }
    else
    {
        nextIt = iterator(node->next);
    }

    m_allocator.deallocateObject(node);
    --m_itemCount;

    return nextIt;
}

// -----------------------------------------------------------------------------

template <typename T>
T& bw::List<T>::first()
{
    return m_first->item;
}

// -----------------------------------------------------------------------------

template <typename T>
const T& bw::List<T>::first() const
{
    return m_first->item;
}

// -----------------------------------------------------------------------------

template <typename T>
T& bw::List<T>::last()
{
    return m_last->item;
}

// -----------------------------------------------------------------------------

template <typename T>
const T& bw::List<T>::last() const
{
    return m_last->item;
}

// -----------------------------------------------------------------------------

template <typename T>
size_t bw::List<T>::count() const
{
    return m_itemCount;
}

// -----------------------------------------------------------------------------

template <typename T>
bool bw::List<T>::empty() const
{
    return m_itemCount == 0;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::List<T>::iterator bw::List<T>::begin()
{
    return iterator(m_first);
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::List<T>::const_iterator bw::List<T>::begin() const
{
    return const_iterator(m_first);
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::List<T>::const_iterator bw::List<T>::cbegin() const
{
    return const_iterator(m_first);
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::List<T>::iterator bw::List<T>::end()
{
    return iterator(nullptr);
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::List<T>::const_iterator bw::List<T>::end() const
{
    return const_iterator(nullptr);
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::List<T>::const_iterator bw::List<T>::cend() const
{
    return const_iterator(nullptr);
}