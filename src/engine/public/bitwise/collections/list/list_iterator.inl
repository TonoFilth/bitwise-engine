template <class I, class U>
bw::ListIterator<I,U>::ListIterator() :
    m_node(nullptr) 
{
}

// -----------------------------------------------------------------------------

template <class I, class U>
bw::ListIterator<I,U>::ListIterator(const ListIterator& other) :
    m_node(other.m_node)
{
}

// -----------------------------------------------------------------------------

template <class I, class U>
bw::ListIterator<I,U>::ListIterator(Node* node) :
    m_node(node)
{
}

// -----------------------------------------------------------------------------

template <class I, class U>
bw::ListIterator<I,U>::~ListIterator()
{
}

// -----------------------------------------------------------------------------

template <class I, class U>
bw::ListIterator<I,U>& bw::ListIterator<I,U>::operator=(const ListIterator& other)
{
    if (this != &other)
    {
        m_node = other.m_node;
    }

    return *this;
};

// -----------------------------------------------------------------------------

template <class I, class U>
template <class OtherType>
bool bw::ListIterator<I,U>::operator==(const ListIterator<OtherType>& other) const
{
    return m_node == other.cnode();
}

// -----------------------------------------------------------------------------

template <class I, class U>
template <class OtherType>
bool bw::ListIterator<I,U>::operator!=(const ListIterator<OtherType>& other) const
{
    return m_node != other.cnode();
}

// -----------------------------------------------------------------------------

template <class I, class U>
I& bw::ListIterator<I,U>::operator*() const
{
    return m_node->item;
}

// -----------------------------------------------------------------------------

template <class I, class U>
I* bw::ListIterator<I,U>::operator->() const
{
    return &m_node->item;
}

// -----------------------------------------------------------------------------

template <class I, class U>
bw::ListIterator<I,U>& bw::ListIterator<I,U>::operator++()
{
    m_node = m_node->next;
    return *this;
}

// -----------------------------------------------------------------------------

template <class I, class U>
bw::ListIterator<I,U> bw::ListIterator<I,U>::operator++(int)
{
    ListIterator tmp(*this);
    operator++();
    return tmp;
}

// -----------------------------------------------------------------------------

template <class I, class U>
bw::ListIterator<I,U>& bw::ListIterator<I,U>::operator--()
{
    m_node = m_node->prev;
    return *this;
}

// -----------------------------------------------------------------------------

template <class I, class U>
bw::ListIterator<I,U> bw::ListIterator<I,U>::operator--(int)
{
    ListIterator tmp(*this);
    operator--();
    return tmp;
}

// -----------------------------------------------------------------------------

template <class I, class U>
bw::ListIterator<I,U>::operator bool() const
{
    return m_node != nullptr;
}

// -----------------------------------------------------------------------------

template <class I, class U>
bw::ListIterator<I,U>::operator ListIterator<const I>() const
{
    return ListIterator<const I>(m_node);
}

// -----------------------------------------------------------------------------

template <class I, class U>
typename bw::ListIterator<I,U>::Node* bw::ListIterator<I,U>::node() const
{
    return m_node;
}

// -----------------------------------------------------------------------------

template <class I, class U>
typename const bw::ListIterator<I,U>::Node* bw::ListIterator<I,U>::cnode() const
{
    return m_node;
}

// -----------------------------------------------------------------------------

template <class I, class U>
void bw::ListIterator<I,U>::swap(ListIterator& other) noexcept
{
    std::swap(m_node, other.m_node);
}