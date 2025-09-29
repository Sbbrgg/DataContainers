#include <iostream>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//#define MAX(a,b) a>b?a:b

//#define DEBUG

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
	int depth() const
	{
		return depth(Root);
	}
	void depth_print(int depth, int width=4)const
	{
		depth_print(depth, Root, width);
		cout << endl;
	}
	void tree_print()const
	{
		tree_print(depth(), 4*depth());
	}
	void erase(int Data)
	{
		return erase(Data, Root);
	}
	int sum()const
	{
		return Summ(Root);
	}
	double AVG()
	{
		return AVG(Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int count()const
	{
		return count(Root);
	}
	void clear()
	{
		clear(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
		cout << "ILConstructor:\t" << this << endl;
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}
	void balance()
	{
		balance(Root);
	}
	/*void Balance()
	{
		int n = count(Root);
		int* arr = new int[n];
		int index = 0;
		value_from_tree(Root, arr, index);
		clear(Root);
		Root = nullptr;
		Root = BuildBalancedTree(arr, 0, n - 1);
		delete[] arr;
	}*/
private:
	void balance(Element* Root)
	{
		if (Root == nullptr)return;
		if(abs(count(Root->pLeft) - count(Root->pRight)) < 2)return;
		if (count(Root->pLeft) < count(Root->pRight))
		{
			if (Root->pLeft)insert(Root->Data, Root->pLeft);
			else Root->pLeft = new Element(Root->Data);
			Root->Data = minValue(Root->pRight);
			erase(minValue(Root->pRight), Root->pRight);
		}
		if (count(Root->pLeft) > count(Root->pRight))
		{
			if (Root->pRight)insert(Root->Data, Root->pRight);
			else Root->pRight = new Element(Root->Data);
			Root->Data = maxValue(Root->pLeft);
			erase(maxValue(Root->pLeft), Root->pLeft);
		}
		balance(Root->pLeft);
		balance(Root->pRight);
		balance(Root);
	}
	virtual void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	int depth(Element* Root)const
	{
		return Root == nullptr ? 0 : std::max(depth(Root->pLeft) + 1, depth(Root->pRight) + 1);
		/*if (Root == nullptr)return 0;
		int l_depth = depth(Root->pLeft) + 1;
		int r_depth = depth(Root->pRight) + 1;
		return l_depth < r_depth ? r_depth : l_depth;*/
		/*return
			Root == nullptr ? 0 :
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1 :
			depth(Root->pRight) + 1;*/
		/*if (!Root)return 0;
			int left = depth(Root->pLeft);
			int right = depth(Root->pRight);
			return left >= right ? left + 1 : right + 1;*/
	}
	void depth_print(int depth, Element* Root, int width)const
	{
		if (Root == nullptr)
		{
			/*cout.width(width);
			cout << "";*/
			return;
		}
		if (depth == 0)
		{
			cout.width(width);
			cout << Root->Data;
		}
		depth_print(depth - 1, Root->pLeft, width);
		depth_print(depth - 1, Root->pRight, width);
	}
	void tree_print(int depth, int width)const
	{
		if (depth == -1)
		{
			cout.width(width);
			cout << " ";
			return;
		}
		tree_print(depth - 1, width * 1.5);
		depth_print(depth - 1, width);
		cout << endl;
		cout << endl;

	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int Summ(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return Summ(Root->pLeft) + Summ(Root->pRight) + Root->Data;*/
		return !Root ? 0 : Summ(Root->pLeft) + Summ(Root->pRight) + Root->Data;
	}
	double AVG(Element* Root)
	{
		int c = count(getRoot());
		return c == 0 ? 0 : (double)Summ(Root) / c;
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? INT_MIN : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
	}
	int maxValue(Element* Root)const
	{
		return !Root ? INT_MIN : Root->pRight ? maxValue(Root->pRight) : Root->Data;
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
	}
	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
	}
	void clear(Element*& Root)
	{
		if (!Root)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	/*void value_from_tree(Element* Root, int* arr, int& index)const
	{
		if (!Root)return;
		value_from_tree(Root->pLeft, arr, index);
		arr[index++] = Root->Data;
		value_from_tree(Root->pRight, arr, index);
	}
	Element* BuildBalancedTree(int* arr, int start, int end)
	{
		if (start > end)return nullptr;
		int mid = (start + end) / 2;
		Element* node = new Element(arr[mid]);
		node->pLeft = BuildBalancedTree(arr, start, mid - 1);
		node->pRight = BuildBalancedTree(arr, mid + 1, end);
		return node;
	}*/
	friend class UniqueTree;
};

class UniqueTree : public Tree
{

private:
	void insert(int Data, Element* Root) override
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}

	}
public:
	void insert(int Data)
	{
		return insert(Data, Root);
	}
};
void performance_test(Tree& tree)
{
	clock_t start, end;

	start = clock();
	cout << "Сумма элементов: " << tree.sum() << endl;
	end = clock();
	cout << "Время sum(): " << double(end - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

	start = clock();
	cout << "Среднее: " << tree.AVG() << endl;
	end = clock();
	cout << "Время AVG(): " << double(end - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

	start = clock();
	cout << "Min: " << tree.minValue() << " Max: " << tree.maxValue() << endl;
	end = clock();
	cout << "Время min/max(): " << double(end - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;

	start = clock();
	cout << "Depth: " << tree.depth() << endl;
	end = clock();
	cout << "Время depth(): " << double(end - start) / CLOCKS_PER_SEC * 1000 << " мс" << endl;
}

template<typename T>void measure_performance(const char massage[], T(Tree::* function)()const, const Tree& tree)
{
	//int (*function)() - указатель на функцию, которая ничего не принимает и возвращает значение типа инт
	clock_t start = clock();
	T result = (tree.*function)();
	clock_t end = clock();
	cout << massage << result << ", вычислено за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
}

//#define BASE_CHECK
//#define ERASE_CHECK
#define DEPTH_CHECK
//#define PERFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	cout << "Hello Tree" << endl;
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;

	cout << endl << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.AVG() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;

	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << u_tree.count() << endl;
	cout << "Сумма элементов дерева: " << u_tree.sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << u_tree.AVG() << endl;
#endif // BASE_CHECK

#ifdef ERASE_CHECK
	Tree tree =
	{
					50,

			25,				75,

		16,		32,		58,		85,91,98
	};
	tree.print();
	//int value;
	//cout << "Введите удаляемое значение: "; cin >> value;
	//tree.erase(25);
	//tree.erase(32);
	tree.erase(50);
	//tree.erase(75);
	tree.print();
	cout << "Глубина дерева: " << tree.depth() << endl;
#endif // ERASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree =
	{
					50,

			25,				75,

		16,		32,		58,		85//,91,98
	};
	tree.print();
	cout << "Глубина дерева: " << tree.depth() << endl;
	/*tree.Balance();
	tree.tree_print();*/
	cout << endl;

	Tree tree2 = { 55,34,21,13,8,5,3 };
	tree2.balance();
	tree2.tree_print();
	
#endif // DEPTH_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	/*tree.print();
	cout << endl << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.AVG() << endl;
	cout << "Глубина дерева: " << tree.depth() << endl;*/

	measure_performance("Минимальное значение в дереве: ", &Tree::minValue, tree);
	measure_performance("Максимальное значение в дереве: ", &Tree::maxValue, tree);
	measure_performance("Сумма элементов дерева: ", &Tree::sum, tree);
	measure_performance("Количество элементов дерева: ", &Tree::count, tree);
	//measure_performance("Среднее арифметическое жерева: ", &Tree::AVG, tree);
	measure_performance("Глубина дерева: ", &Tree::depth, tree);
#endif //PERFORMANCE_CHECK

}