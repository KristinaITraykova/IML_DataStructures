#pragma once

#include <iostream>

template <class T>
class Stack {
	T* data;
	size_t top;
	size_t capacity;

	void copy(const Stack<T>&);
	void del();
	void resize();

public:

	Stack();
	Stack(const Stack<T>&);
	Stack& operator=(const Stack&);
	~Stack();

	void push(T data);
	void pop();
	bool isEmpty() const;

	T& getTop() const;
	size_t getTopSize() const;
	bool isFull() const;
	T& operator[](size_t);
	const T& operator[](size_t) const;

	friend std::ostream& operator<<(std::ostream& out, const Stack<T>& stack) {
		size_t size = stack.getTop();
		for (size_t i = 0; i < size; i++)
		{
			out << stack[i] << " ";
		}
		return out;
	}

	
};

template <class T>
void Stack<T>::copy(const Stack<T>& other)
{
	this->top = other.top;
	this->capacity = other.capacity;

	this->data = new T[this->capacity];
	for (size_t i = 0; i < this->top; i++)
	{
		this->data[i] = other.data[i];
	}
}

template <class T>
void Stack<T>::del()
{
	delete[] this->data;
}

template <class T>
void Stack<T>::resize()
{
	this->capacity *= 2;
	T* temp = new T[this->capacity];
	for (size_t i = 0; i < this->top; i++)
	{
		temp[i] = this->data[i];
	}
	delete[] this->data;
	this->data = temp;
}

template <class T>
Stack<T>::Stack()
{
	this->top = 0;
	this->capacity = 8;
	this->data = new T[this->capacity];
}

template <class T>
Stack<T>::Stack(const Stack<T>& other)
{
	copy(other);
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	if (this != &other)
	{
		this->del();
		this->copy(other);
	}
	return *this;
}

template <class T>
Stack<T>::~Stack()
{
	this->del();
}

template <class T>
void Stack<T>::push(T data) 
{
	if (this->isFull())
	{
		this->resize();
	}
	this->data[top] = data;
	this->top++;
}

template <class T>
void Stack<T>::pop()
{
	--top;
}

template <class T>
T& Stack<T>::getTop() const
{
	if (this->isEmpty()) {
		throw std::out_of_range("Stack is empty!");
	}
	return this->data[this->top - 1];
}

template <class T>
size_t Stack<T>::getTopSize() const
{
	return this->top;
}

template <class T>
bool Stack<T>::isEmpty() const
{
	return this->top == 0;
}

template <class T>
bool Stack<T>::isFull() const
{
	return this->top == this->capacity;
}

template <class T>
T& Stack<T>::operator[](size_t pos)
{
	return this->data[pos];
}

template <class T>
const T& Stack<T>::operator[](size_t pos) const
{
	return this->data[pos];
}