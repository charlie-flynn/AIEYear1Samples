#pragma once

template<typename T>
struct Node
{
public:
	Node<T>();
	Node<T>(T value);
	~Node<T>() = default;
public:
	T value;
	Node<T>* previous;
	Node<T>* next;
};

template<typename T>
inline Node<T>::Node() : next(nullptr), previous(nullptr)
{
}

template<typename T>
inline Node<T>::Node(T value) : value(value), next(nullptr), previous(nullptr) 
{
}
