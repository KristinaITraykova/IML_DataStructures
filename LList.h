#pragma once
#include <iostream>

template <class T>
class LList
{
	struct Node {
		T data;
		Node* next;

		Node(const T& data = 0, Node* next = nullptr) : data(data), next(next) {}
		
		bool operator==(const T& other) {
			return data == other;
		}
	};

	Node* first, *last;
	size_t size;

	void copy(const LList&);
	void del();
	Node* findByIndex(size_t index){
		if (index == 0)
			return first;
		if (index == size - 1)
			return last;

		Node* current = first->next;
		size_t currentIndex = 1;
		while (currentIndex < index) {
			current = current->next;
			++currentIndex;
		}
		return current;
	}

public:
	LList();
	LList(const LList<T>&);
	LList& operator=(const LList<T>&);
	~LList();

	void push_back2(Node*&, T);
	void push_back(const T&);
	void push_front(const T&);
	void removeFirst();
	T removeFirstT();
	void removeAt(size_t);
	void removeLast();
	T removeNode(Node*&);
	bool isEmpty() const;
	size_t getSize() const;
	bool onlyOneData() const;
	const T& getAt(size_t index);    // instead of operator[]
	T& getNextNode(size_t pos);      // like operator++
	void reverse();                  // reverse the list
	void slc(size_t);                // return new list from the proper index
	//void removeDuplicates();         // remove duplicates numbers
	//void removeDuplicates2();         // remove duplicates numbers
	//void removeDuplicates3();
	void changeElementAt(size_t, const T&);
	void split(Node*& head, Node*& first, Node*& second);
	void mergeSort(Node*& head);
	LList<T>& sortASC();
	LList<T>& sortDSC();

	friend std::ostream& operator<<(std::ostream& out, const LList<T>& list)
	{
		Node* current = list.first;
		while (current) {
			out << current->data << " ";
			current = current->next;
		}
		return out;
	}

	Node* merge(Node* first, Node* second) {
		Node* result = nullptr;

		if (first == nullptr)
			return second;
		if (second == nullptr)
			return first;

		if (first->data <= second->data) {
			result = first;
			result->next = merge(first->next, second);
		}
		else {
			result = second;
			result->next = merge(first, second->next);
		}

		return result;
	}
};

template <class T>
void LList<T>::copy(const LList<T>& other)
{
	Node* current = other.first;
	Node* copy = nullptr;

	while (current) {
		Node* newNode = new Node(current->data, nullptr);

		if (first == nullptr)
			first = newNode;
		else if (current == other.last)
			last = newNode;
		else if (copy)
			copy->next = newNode;

		copy = newNode;
		current = current->next;
	}
	size = other.size;
}

template <class T>
void LList<T>::del()
{
	Node* temp = nullptr;

	while (this->first != nullptr) {
		temp = first->next;
		delete this->first;
		this->first = temp;
	}
	this->last = nullptr;
}

template <class T>
LList<T>::LList()
{
	this->first = nullptr;
	this->last = nullptr;
	this->size = 0;
}

template <class T>
LList<T>::LList(const LList<T>& other)
{
	this->copy(other);
}

template <class T>
LList<T>& LList<T>::operator=(const LList<T>& other)
{
	if (this != &other) {
		del();
		copy(other);
	}
	return *this;
}

template <class T>
LList<T>::~LList()
{
	del();
}

template <class T>
void  LList<T>::push_back2(Node*& first, T element)
{
	Node* newNode = new Node(element);

	if (first == nullptr)
	{
		first = newNode;
		return;
	}

	Node* current = first;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = newNode;
}

template <class T>
void LList<T>::push_back(const T& element)
{
	Node* newNode = new Node(element, nullptr);

	if (isEmpty()) {
		last = newNode;
		first = newNode;
	}
	else {
		last->next = newNode;
		last = newNode;
	}
	++size;
}

template <class T>
void LList<T>::push_front(const T& element)
{
	Node* newNode = new Node;
	newNode->data = element;
	newNode->next = first;

	if (isEmpty()) {
		last = newNode;
	}
	first = newNode;
	++size;
}

template <class T>
void LList<T>::removeFirst()
{
	if (isEmpty()) {
		return;
	}

	Node* newNode = first;
	first = first->next;
	delete newNode;

	if (size == 1) {
		last = nullptr;
	}
	--size;
}

template <class T>
T LList<T>::removeFirstT()
{
	Node* first_ = first;
	T d = first_->data;

	first = first->next;

	if (size == 1) {
		delete[] last;
	}
	else {
		delete[] first;
	}

	--size;
	return d;
}

template <class T>
void LList<T>::removeAt(size_t index)
{
	if (index >= size)
		return;
	if (index == 0)
		return removeFirst();

	Node* prev = findByIndex(index - 1);
	Node* n = prev->next;
	prev->next = n->next;

	if (n == last)
		last = prev;

	delete n;
	--size;
}

template <class T>
void LList<T>::removeLast() {
	Node* curr = first;
	while (curr->next->next != nullptr) {
		curr = curr->next;
	}
	last = curr;

	size--;
}

template <class T>
T LList<T>::removeNode(Node*& node)
{
	if (first == node) {
		return removeFirstT();
	}

	Node* current = first;
	while (current->next != node) {
		current = current->next;
	}

	current->next = node->next;

	T d = node->data;

	delete node;
	node = nullptr;
	--size;

	return d;
}

template <class T>
bool LList<T>::isEmpty() const
{
	return size == 0;
}

template <class T>
size_t LList<T>::getSize() const
{
	return this->size;   // +1
}

template <class T>
bool LList<T>::onlyOneData() const
{
	Node* current = this->first;
	if (current != nullptr && current->next == nullptr) {
		return true;
	}
	return false;
}

template <class T>
const T& LList<T>::getAt(size_t index)
{
	if (index >= 0 && index < size) {
		Node* holder = findByIndex(index);
		return holder->data;
	}
	else return first->data;
}

template <class T>
T& LList<T>::getNextNode(size_t pos)
{
	Node* current = this->first;
	while (pos > 0 && current != nullptr)
	{
		--pos;
		current = current->next;
	}
	return current->next;
}

template <class T>
void LList<T>::reverse()
{
	if (size <= 1) {
		return;
	}

	Node* current = first;
	Node* prev = nullptr;
	Node* next = nullptr;

	last = current;
	while (current != nullptr)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	first = prev;
}

template <class T>
void LList<T>::slc(size_t index) 
{
	if (index < 0 || index >= size)
		return;

	while (index) {
		removeFirst();
		--index;
	}
}
/*
template <class T>
void LList<T>::removeDuplicates()
{
	for (Node* node = first; node != nullptr; node = node->next)
	{
		for (Node* j_node = node->next; j_node != nullptr; ) 
		{
			if (j_node->data == node->data) {
				removeNode(j_node);
				j_node = node->next;
			}
			else {
				j_node = j_node->next;
			}
		}
	}
}

template <class T>
void LList<T>::removeDuplicates2()
{
	Node* current = first;
	Node* ptr, * dup;

	while (current != nullptr && current->next != nullptr) {
		ptr = current;

		while (ptr->next != nullptr) {
			if (current->data == ptr->next->data) {
				dup = ptr->next;
				ptr->next = ptr->next->next;
				removeNode(dup);//delete(dup);
			}
			else
				ptr = ptr->next;
		}
		current = current->next;
	}
}

template <class T>
void LList<T>::removeDuplicates3()
{
	Node* others = current->next;
	Node* prev = first;

	size_t i = 0, j = 1;
	while (current->next != nullptr) {
		while (others != nullptr) {

			if (current->data == others->data) {
				if (others->next != nullptr) {
					others = others->next;
					//removeAt(j);
				}
				if (others->next == nullptr) {
					//prev->next = others->next;
					//others = prev;
					removeLast();

					break;  // ??
				}
				else if (others->next != nullptr) {
					prev->next = others->next;
					others = others->next;
					//removeAt(j);
				}
				removeAt(j);
			}
			if (others->next != nullptr) {
				others = others->next;
				prev = prev->next;
			}
			j++;
		}

		if (current->next->next != nullptr)
		{
			current = current->next;
			others = current->next;
			prev = current;
		}
		else
			break;

		i++;
		j = i + 1;
	}
}
*/
template <class T>
void LList<T>::changeElementAt(size_t index, const T& element)
{
	Node* current = findByIndex(index);
	current->data = element;
}

template <class T>
void LList<T>::split(Node*& head, Node*& first, Node*& second) {
	Node* slow = head;
	Node* fast = head;

	while (fast->next != nullptr && fast->next->next != nullptr) {
		fast = fast->next;
		if (fast != nullptr) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	first = head;
	second = slow->next;
	slow->next = nullptr;
}

template <class T>
void LList<T>::mergeSort(Node*& head) {

	Node* current = head;
	Node* first = nullptr;
	Node* second = nullptr;

	if (current == nullptr || current->next == nullptr) {
		return;
	}
	split(head, first, second);

	mergeSort(first);
	mergeSort(second);

	head = merge(first, second);
}

template <class T>
LList<T>& LList<T>::sortASC()
{
	Node* first = nullptr;
	size_t s = this->getSize();
	for (size_t i = 0; i < s; i++)
	{
		push_back2(first, this->getAt(i));
	}

	mergeSort(first);
	for (size_t i = 0; i < s; i++) {
		this->changeElementAt(i, first->data);
		first = first->next;
	}
	return *this;
}

template <class T>
LList<T>& LList<T>::sortDSC()
{
	Node* first = nullptr;
	size_t s = this->getSize();
	for (size_t i = 0; i < s; i++)
	{
		push_back2(first, this->getAt(i));
	}

	mergeSort(first);
	for (size_t i = 0; i < s; i++) {
		this->changeElementAt(i, first->data);
		first = first->next;
	}
	this->reverse();
	return *this;
}