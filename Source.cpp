#include<iostream>
#include<string>
#include"List.h"
//оголосити структуру Node потрібно перед ф-цією Show()
//struct Node;
//
//void Show(Node* head);
//
//struct Node {
//	int data;
//	Node* next;
//};

class Person
{
private:
	std::string name;
	int age;
public:
	Person(std::string name,int age)
		:name(name),age(age){ }

	std::string Name()const
	{
		return name;
	}
	int Age()const {
		return age;
	}
};

int main()
{
	/*Node* head=nullptr ;
	

	head = new Node{ 3, nullptr };

	head->next = new Node{ 5,nullptr };

	head->next->next = new Node{ 8,nullptr };
	
	Show(head);*/

	List<int> list1;

	list1.Show();

	for (size_t i = 0; i < 10; i++)
		list1.PushBack(i);
	
	list1.Show();

    list1.PopBack();
	std::cout << "\n";
	List<int> list2(list1);

	list2.Show();


	std::cout << "\n\nPopFront()\n";
	list1.Show();
	list1.PopFront();
	std::cout << "\n";
	list2 = list1;
	list2.Show();
	std::cout << '\n';

	list2.Remove(4);
	list2.Remove(100);
	list2.Show();

	std::cout <<"\n"<< std::boolalpha << list2.Find(3) << "\n";

	std::cout<<"size of list2 is: "<<list2.Size()<<'\n';
	try {
		std::cout << list2[10] << '\n';
	}
	catch (std::out_of_range&exc) {
		std::cout << exc.what() << std::endl;
	}

	std::cout << list2.Size() << '\n';

	//для того щоб звернутися до перших чотирьох елементів list через for ітератор робить 10 ітерацій (це можна вирішити за допомогою ітераторів

	List<int>::Iterator i =list2.Begin();

	for (List<int>::Iterator it = list2.Begin(); it != list2.End(); it++)
		std::cout << *it << " ";
	std::cout << '\n';


	List<Person>personList;

	personList.PushBack(Person("Danylo", 18));
	personList.PushBack(Person("Demien", 20));
	personList.PushBack(Person("Max", 15));
	personList.PushBack(Person("Oleg", 24));

	for (List<Person>::Iterator it = personList.Begin(); it != personList.End(); it++) {
		std::cout << "Person`s name is: " << it->Name();
		std::cout << "Person`s age is: " << it->Age() << '\n';
	}
}


//void Show(Node* head)
//{
//	if (head == nullptr)
//		std::cout << "list is empty\n";
//
//	//щоб саме використовувати struct тобі потрібно перше описати її
//	Node* current = head;
//
//	while (current != nullptr)
//	{
//		std::cout << current->data << " ";
//		current = current->next;
//	}
//
//}

