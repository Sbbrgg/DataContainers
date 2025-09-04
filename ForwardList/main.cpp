#include <iostream>
using namespace std;

#define delimetr "\n--------------------------------------------------------\n"
#define tab "\t"

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Значение следующего элемента
	//static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		//count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		//count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;	//приватные поля этого класса доступны другу "ForwardList"
};
//int Element::count = 0;
class ForwardList
{
	Element* Head;
	int size;
public:
	ForwardList()
	{
		//Конструктор по умолчанию - создаёт пустой список
		Head = nullptr;	//Если список пуст, то его голова указывает на 0
		size = 0;
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor:\t" << this << endl;
		while (Head)pop_front();
		size = 0;
		/*while (Head)
		{
			Element* Temp = Head;
			Head = Head->pNext;
			delete Temp;
		}*/
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
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = New;
		size++;
		/*if (Head == nullptr)
		{
			Head = new Element(Data);
			return;
		}
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);*/
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index >= size)return push_back(Data);
		//1) Доходим до нужного элемента (элемент перед добавляемым)
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//2) Создаём добавляемый элемент:
		Element* New = new Element(Data);

		//3) Пристыковываем новый элемент к его следующему элементу:
		New->pNext = Temp->pNext;

		//4) Пристыковываем предыдущий элемент к новому:
		Temp->pNext = New;
		size++;
	}

	//					Removing elements
	void pop_front()
	{
		if (Head == nullptr)return;
		//1) Запоминаем адрес удаляемого элемента:
		Element* Erased = Head;
		//2) Исключаем удаляемый элемент из списка:
		Head = Head->pNext;
		//3) Удаляем удаляемый элемент из памяти:
		delete Erased;
		size--;
		/*if (Head == nullptr) return;
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;*/
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)
		{
			delete Head;
			Head = nullptr;
			size--;
			return;
		}
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
		/*Element* Temp = Head;
		if (Head == nullptr) return;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;*/
	}
	void erase(int Index)
	{
		if (Head == nullptr)return;
		if (Index == 0)return pop_front();
		if (Index >= size || Index < 0)return;

		Element* Temp = Head;
		for (int i = 0; Temp->pNext && i < (Index - 1); i++)
			Temp = Temp->pNext;
		if (Temp->pNext == nullptr)return;

		Element* Erased = Temp->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;
		size--;
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
		cout << "Количество элементов: " << size << endl;
	}

	ForwardList operator+(const ForwardList& other) const
	{
		ForwardList result;
		Element* Temp = Head;

		while (Temp)
		{
			result.push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		Temp = other.Head;
		while (Temp)
		{
			result.push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		return result;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	//Element element = 5;
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	//list.push_back(123);
	list.print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
#endif // BASE_CHECK

	ForwardList list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	list1.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	//int index;
	//int value;
	//cout << "Введите индекс добавляемого элемента: "; cin >> index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list1.insert(value, index);
	//list1.print();

	ForwardList fusion = list1 + list2;
	fusion.print();
	//ForwardList(list1 + list2).print();
	//(list1+list2).print();
}