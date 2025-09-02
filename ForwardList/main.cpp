#include <iostream>
using namespace std;

#define delimetr "\n--------------------------------------------------------\n"
#define tab "\t"

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Значение следующего элемента
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;	//приватные поля этого класса доступны другу "ForwardList"
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		//Конструктор по умолчанию - создаёт пустой список
		Head = nullptr;	//Если список пуст, то его голова указывает на 0
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor:\t" << this << endl;
	}

	//			Adding element:
	void push_front(int Data)
	{
		//1) Создаём элемент и сохраняем в него добавляемое значение
		Element* New = new Element(Data);

		//2) Привязываем новый созданный элемент к началу списка
		New->pNext = Head;

		//3) Переносим голову на новый элемент (Отправляем новый элемент в голову):
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			Head = new Element(Data);
			return;
		}
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
	}
	void pop_front()
	{
		if (Head == nullptr) return;
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
	}
	void pop_back()
	{
		Element* Temp = Head;
		if (Head == nullptr) return;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	//				Methods
	void print()const
	{
		Element* Temp = Head;	//Temp - итератор
		//Итератор - это указатель, при помощи которого можно перебирать элементы структуры данных

		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Element element = 5;
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
}