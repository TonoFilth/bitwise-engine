#ifndef BW_BASE_POINTER_HASH_TABLE_H
#define BW_BASE_POINTER_HASH_TABLE_H

#include "Bw/Base/Common.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  PointerHashTable
////////////////////////////////////////////////////////////////////////////////
template <class V, unsigned N>
class PointerHashTable
{
public:
	typedef uintptr_t K;
	typedef size_t (*H) (K);

public:
	PointerHashTable(V defaultValue);

	V    get(K key) const;
	void put(K key, V value);
	void clear();

	void setHashFunction(H function);

private:
	static const K INVALID_KEY = 0x0;

	struct Pair
	{
		K key;
		V value;

		Pair() {}

		Pair(K k, V v) :
			key(k),
			value(v)
		{
		}
	};

	bool tryGet(K key, size_t initialIndex, size_t& index) const;

private:
	Pair m_table[N];
	H    m_hash;
	V    m_defaultValue;
};

// -----------------------------------------------------------------------------

BW_INLINE size_t IdentityHashFunction(uintptr_t key)
{
	return static_cast<size_t>(key);
}

// -----------------------------------------------------------------------------

template <class V, unsigned N>
PointerHashTable<V, N>::PointerHashTable(V defaultValue) :
	m_hash(IdentityHashFunction),
	m_defaultValue(defaultValue)
{
	clear();
}

// -----------------------------------------------------------------------------

template <class V, unsigned N>
V PointerHashTable<V, N>::get(K key) const
{
	size_t index = m_hash(key) % N;

	if (m_table[index].key == key)
	{
		return m_table[index].value;
	}
	else
	{
		size_t realIndex;

		if (tryGet(key, index, realIndex))
		{
			return m_table[realIndex].value;
		}
		else
		{
			BW_ASSERT(false);
		}
	}

	return m_defaultValue;
}

// -----------------------------------------------------------------------------

template <class V, unsigned N>
bool PointerHashTable<V, N>::tryGet(K key, size_t initialIndex, size_t& result) const
{
	bool stopLeft  = false;
	bool stopRight = false;
	int64_t index  = static_cast<size_t>(initialIndex);
	int64_t i      = 1;

	while (!(stopLeft && stopRight))
	{
		if (!stopLeft)
		{
			int64_t leftIndex = index - i * i;

			if (leftIndex >= 0)
			{
				if (m_table[leftIndex].key == key)
				{
					result = static_cast<size_t>(leftIndex);
					return true;
				}
			}
			else
			{
				stopLeft = true;
			}
		}

		if (!stopRight)
		{
			int64_t rightIndex = index + i * i;

			if (rightIndex < N)
			{
				if (m_table[rightIndex].key == key)
				{
					result = static_cast<size_t>(rightIndex);
					return true;
				}
			}
			else
			{
				stopRight = true;
			}
		}

		++i;
	}

	return false;
}

// -----------------------------------------------------------------------------

template <class V, unsigned N>
void PointerHashTable<V, N>::put(K key, V value)
{
	size_t index = m_hash(key) % N;

	if (m_table[index].key == INVALID_KEY || m_table[index].key == key)
	{
		m_table[index] = Pair(key, value);
	}
	else
	{
		size_t realIndex;

		if (tryGet(INVALID_KEY, index, realIndex))
		{
			Pair& pair = m_table[realIndex];

			pair.key   = key;
			pair.value = value;
		}
		else
		{
			BW_ASSERT(false);
		}
	}
}

// -----------------------------------------------------------------------------

template <class V, unsigned N>
void PointerHashTable<V, N>::clear()
{
	for (int i = 0; i < N; ++i)
	{
		m_table[i] = Pair(K(0), m_defaultValue);
	}
}

// -----------------------------------------------------------------------------

template <class V, unsigned N>
void PointerHashTable<V, N>::setHashFunction(H function)
{
	BW_ASSERT(function);
	m_hash = function;
}

}	// namespace bw

#endif	// BW_BASE_POINTER_HASH_TABLE_H