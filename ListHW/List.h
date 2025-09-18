#pragma once
#include "stdafx.h"
#include "constants.h"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;
	//ќбъекты классов и структур и указатели на эти объекты можно об€ъвл€ть непосредственно после описани€ классов и структур
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();

		//			Comparison operators:
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		T operator*()const;
	};
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();

		ConstIterator operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator& operator--(int);

	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);

	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp);
		~Iterator();
		T& operator* ();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp);
		~ReverseIterator();
		T& operator*();
	};

	ConstIterator begin()const;
	ConstIterator end()const;
	ConstReverseIterator rbegin() const;
	ConstReverseIterator rend() const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//					Operators:
	List<T>& operator=(const List<T>& other);

	//					Adding Elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//Removing elements:
	void pop_front();
	void pop_back();

	//					Methods:
	void print() const;
	void reverse_print() const;
};