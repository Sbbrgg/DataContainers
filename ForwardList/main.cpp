#include <iostream>
using namespace std;
#include <ctime>

#define delimiter "\n--------------------------------------------------------\n"
#define tab "\t"
//#define DEBUG

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Значение следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;	//приватные поля этого класса доступны другу "ForwardList"
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
int Element::count = 0;
class ForwardList
{
	Element* Head;
	size_t size;
public:
	Element* get_Head()const
	{
		return Head;
	}
	size_t get_size()const
	{
		return size;
	}
	ForwardList()
	{
		//Конструктор по умолчанию - создаёт пустой список
		Head = nullptr;	//Если список пуст, то его голова указывает на 0
		size = 0;
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(size_t size) :ForwardList()
	{
		clock_t t_start = clock();
		for (int i = 0; i < size; i++)
		{
			push_front(rand() % 10);
		}
		clock_t t_end = clock();
		cout << "FLConstructor(n):\t" << this << "\tcomplete for " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		//Deep copy (Побитовое копирование)
		*this = other;
		cout << "FLCopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other)
	{
		//Shallow Copy
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "FLMoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		clock_t t_start = clock();
		while (Head)pop_front();
		clock_t t_end = clock();
		cout << "FLDestructor:\t" << this << "\tcomplete for " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
		size = 0;
		/*while (Head)
		{
			Element* Temp = Head;
			Head = Head->pNext;
			delete Temp;
		}*/
	}

	//			Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;	//0) Проверяем, не является ли 'this' и 'other' одним объектом.
		while (Head)pop_front();			//1) Старое значение объекта удаляется из памяти
		//2)Deep copy (Побитовое копирование)
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();

		this->Head = other.Head;
		this->size = other.size;

		other.Head = nullptr;
		other.size = 0;
		cout << "FLMoveAssignment:\t" << this << endl;
		return *this;
	}
	int& operator[](size_t index)
	{
		if (index >= size)throw std::out_of_range("Index out of range!");
		Element* Temp = Head;
		for (size_t i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}

	//			Adding element:
	void push_front(int Data)
	{
		////1) Создаём элемент и сохраняем в него добавляемое значение
		//Element* New = new Element(Data);

		////2) Привязываем новый созданный элемент к началу списка
		//New->pNext = Head;

		////3) Переносим голову на новый элемент (Отправляем новый элемент в голову):
		//Head = New;
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
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

		////2) Создаём добавляемый элемент:
		//Element* New = new Element(Data);

		////3) Пристыковываем новый элемент к его следующему элементу:
		//New->pNext = Temp->pNext;

		////4) Пристыковываем предыдущий элемент к новому:
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
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
		/*if (Head == nullptr)return;
		if (Head->pNext == nullptr)
		{
			delete Head;
			Head = nullptr;
			size--;
			return;
		}*/
		if (!Head || Head->pNext == nullptr)return pop_front();
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
		//Element* Temp = Head;	//Temp - итератор
		////Итератор - это указатель, при помощи которого можно перебирать элементы структуры данных

		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList fusion;

	for (Element* Temp = left.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_back(Temp->Data);
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		fusion.push_back(Temp->Data);

	return fusion;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define HOMEWORK_FIRST_CHECK
#define HOMEWORK_SECOND_CHECK

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
	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();*/
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
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

	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list1.insert(value, index);
	list1.print();*/

	ForwardList fusion;
	cout << delimiter << endl;
	fusion = list1 + list2;		//
	cout << delimiter << endl;
	fusion.print();
	//ForwardList(list1 + list2).print();
	//(list1+list2).print();
#endif // COUNT_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "ForwardList filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("pause");
#endif // PERFORMANCE_CHECK

#ifdef HOMEWORK_FIRST_CHECK
	ForwardList list(100000);
	clock_t t_start = clock();
	for (size_t i = 0; i < list.get_size(); i++)
		list[i] = rand() % 100;
	clock_t t_end = clock();
	cout << "Operator [] perfomance: " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec\n" << endl;
#endif // HOMEWORK_FIRST_CHECK

#ifdef HOMEWORK_SECOND_CHECK
	ForwardList list1(100000);
	clock_t t_start = clock();
	ForwardList list2 = list1;
	clock_t t_end = clock();
	cout << "Copy constructor time: " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec" << endl;

	ForwardList list3;
	t_start = clock();
	list3 = list1; // copy assignment
	t_end = clock();
	cout << "Copy assignment time: " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec" << endl;

#endif // HOMEWORK_SECOND_CHECK

}