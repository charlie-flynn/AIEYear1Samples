#pragma once
#include "Node.h"

template<typename T>
class Iterator
{
private:
	Node<T>* m_current;
public:
	Iterator<T>();
	Iterator<T>(Node<T>* current);

	T operator*() const;
	Iterator<T> operator++();
	Iterator<T> operator++(int);	
	Iterator<T> operator--();
	Iterator<T> operator--(int);
	const bool operator==(const Iterator<T>& other) const;
	const bool operator!=(const Iterator<T>& other) const;

};

template<typename T>
inline Iterator<T>::Iterator() : m_current(nullptr)
{
}

template<typename T>
inline Iterator<T>::Iterator(Node<T>* current) : m_current(current)
{
}

template<typename T>
inline T Iterator<T>::operator*() const
{
	return m_current->value;
}

template<typename T>
inline Iterator<T> Iterator<T>::operator++()
{
	if (m_current)
	{
		m_current = m_current->next;
		return Iterator<T>(m_current);
	}

	return Iterator<T>(nullptr);
}

template<typename T>
inline Iterator<T> Iterator<T>::operator++(int)
{
	if (m_current)
	{
		m_current = m_current->next;
		return Iterator<T>(m_current);
	}

	return Iterator<T>(nullptr);
}

template<typename T>
inline Iterator<T> Iterator<T>::operator--()
{
	if (m_current)
	{
		m_current = m_current->previous;
		return Iterator<T>(m_current);
	}

	return Iterator<T>(nullptr);
}

template<typename T>
inline Iterator<T> Iterator<T>::operator--(int)
{
	if (m_current)
	{
		m_current = m_current->previous;
		return Iterator<T>(m_current);
	}

	return Iterator<T>(nullptr);
}

template<typename T>
inline const bool Iterator<T>::operator==(const Iterator<T>& other) const
{
	return m_current == other.m_current;
}

template<typename T>
inline const bool Iterator<T>::operator!=(const Iterator<T>& other) const
{
	return m_current != other.m_current;
}
