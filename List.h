#pragma once
#include<iostream>
template<typename T>
class List
{
private:
	void Copy(const List& other);

	struct Node {
		T data;
		Node* next;
	};

	Node* head;
	Node* tail;
	size_t size;

public:
	List();
	List(const List& other);
	List(List&& other);

	~List();

	void PushBack(const T& value);
	void PushFront(const T& value);

	
	void PopBack();
	void PopFront();
	void Remove(const T&value);
	void Clear();


	bool Find(const T& value)const;


	bool IsEmpty()const;
	size_t Size()const;

	List& operator=(const List& other);
	List& operator=( List&& other)noexcept;

	class Iterator {
	private:
		Node* node;
	public:
		Iterator(Node* node);
		bool operator!=(const Iterator& other)const;

		Iterator& operator++();
		Iterator operator++(int);
		T& operator*();
		T* operator->();
	};
	//оператор індексації перезавантажуємо двічі для const і не для const
	T& operator[](size_t index);
	const T& operator[](size_t index)const;

	//Iterator`s methods 
	Iterator Begin();
	Iterator End();
	

	void Show()const;
};

template<typename T>
List<T>::List()
	:head(nullptr), tail(nullptr), size(0)
{
}
template<typename T>
List<T>::List(const List& other)
	:List()//?
{
	Copy(other);
}
template<typename T>
List<T>::List(List&& other)
	:head(other.head), tail(other.tail), size(other.size)
{
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}
template<typename T>
List<T>::~List()
{
	Clear();
}
template<typename T>
void List<T>::PushBack(const T& value)
{
	if (head == nullptr) {
		head = new Node{ value,nullptr };
		tail = head;
	}
	else
	{
		/*Node* current = head;

		while (current->next != nullptr)
		{
			current = current->next;
		}

		current->next = new Node{ value,nullptr };*/

		tail->next = new Node{ value,nullptr };
		tail = tail->next;
	}
	size++;
}
template<typename T>
void List<T>::PushFront(const T& value)
{
	if (head == nullptr)
	{
		head = new Node{ value, nullptr };
		tail = head;
	}
	else if (head == tail)
	{
		Node* newNode = new Node{ value,head };
		head = newNode;
		tail = head->next;
	}
	else {
		Node* newNode = new Node{ value,head };
		head = newNode;
	}
	size++;
}
template<typename T>
void List<T>::PopBack()
{
	if (head == nullptr)
	{
		return;
	}

	else if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		Node* previous = head;
		Node* current = head->next;

		while (current->next != nullptr)
		{
			previous = previous->next;
			current = current->next;
		}

		delete current;
		current = nullptr;

		previous->next = nullptr;
		tail = previous;
	}
	size--;
}
template<typename T>
void List<T>::PopFront()
{

	if (head == nullptr)
		return;

	//тут в else if в мене замість порівняння був одне =
	else if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}

	else
	{
		Node* newHead = head->next;
		delete head;

		head = newHead;
	}
	size--;
}
template<typename T>
void List<T>::Remove(const T& value)
{
	Node* previous = nullptr;
	Node* current = head;

	while (current != nullptr) {
		if (current->data == value) {
			if (previous == nullptr)
				head = head->next;

			else {
				previous->next = current->next;
			}
			if (current == tail)
				tail = previous;
			delete current;
			return;
		}
		previous = current;
		//я тут не написав current = current->next
		current = current->next;
	}
	size--;
}
template<typename T>
void List<T>::Clear()
{
	while (head != nullptr)
	{
		Node* current = head;
		head = head->next;
		delete current;
	}
	tail = nullptr;
	size = 0;
}
template<typename T>
bool List<T>::Find(const T& value) const
{
	if (head == nullptr)
		return false;

	Node* current = head;

	while (current != nullptr) {
		if (current->data == value) {
			return true;
		}
		current = current->next;
	}
}
template<typename T>
bool List<T>::IsEmpty() const
{
	if (head == nullptr)
		return true;
	return false;
}
template<typename T>
size_t List<T>::Size() const
{
	return size;
}
template<typename T>
void List<T>::Show() const
{
	if (this->head == nullptr)
	{
		std::cout << "The list is empty\n";
	}
	Node* current = this->head;
	while (current != nullptr)
	{
		std::cout << current->data << " ";
		current = current->next;
	}
}
template<typename T>
void List<T>::Copy(const List& other)
{
	if (other.head == nullptr)
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
		return;
	}

	head = new Node{ other.head->data,nullptr };

	Node* current = head;
	Node* otherCurrent = other.head;
	//в show ми виводимо всі відповідно і перший також, а тут ми копіюємо - перший вже скопійований тому починаємо з next
	while (otherCurrent->next != nullptr)
	{
		//тут ми копіюємо для минулого next					//а тут задаємо nullptr для теперішнього(наступного)
		current->next = new Node{ otherCurrent->next->data,nullptr };

		current = current->next;
		otherCurrent = otherCurrent->next;
	}
	tail = current;
	size = other.size;

}
template<typename T>
List<T>& List<T>::operator=(const List& other)
{
	if (this != &other)
	{
		Clear();
		Copy(other);
		size = other.size;
	}
	return *this;
}
template<typename T>
List<T>& List<T>::operator=(List&& other) noexcept
{
	if (this != &other) {
		Clear();

		head = other.head;
		tail = other.tail;
		size = other.size;
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}
	return *this;
}
template<typename T>
T& List<T>::operator[](size_t index)
{
	if (index >= Size())
		throw std::out_of_range("Incorrect index List::operator[]");

	Node* current = head;
	for (size_t i = 0; i < index; i++)
		current = current->next;

	return current->data;
}
template<typename T>
const T& List<T>::operator[](size_t index) const
{
	if (index >= Size())
		throw std::out_of_range("Index is incorrect T operator[]");

	Node* current = head;
	for (size_t i = 0; i < index; i++)
		current = current->next;

	return current->data;
}
//коли реалізовуємо клас в класі то просто потрібно поставити typename перед List<T>::Iterator
//потрібно ставити typename перед функціями, що повертають тип Iterator, перед конструктор не треба ставити
template<typename T>
typename List<T>::Iterator List<T>::Begin()
{
	Iterator temp(head);
	return temp;
}
template<typename T>
typename List<T>::Iterator List<T>::End()
{
	Iterator temp(tail->next);
	return temp;
}
//але ось тут не потрібно дописувати typename, бо це конструктор
template<typename T>
List<T>::Iterator::Iterator(Node* node)
	:node(node)
{
}
template<typename T>
typename bool List<T>::Iterator::operator!=(const Iterator& other) const
{
	return this->node != other.node;
}
template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
	node = node->next;
	return *this;
}
template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
	Iterator temp(*this);
	++* this;
	return temp;
}
template<typename T>
T& List<T>::Iterator::operator*()
{
	return this->node->data;
}

template<typename T>
inline T* List<T>::Iterator::operator->()
{
	return &node->data;
}


