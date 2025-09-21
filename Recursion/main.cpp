#include <iostream>
using namespace std;

void elevator(int floor);
int Factorial(int n);
double Power(double a, int n);
void Fibonachi(int limit, int a = 0, int b = 1);

//#define ELEVATOR
#define HOMEWORK

void main()
{
	setlocale(LC_ALL, "");
#ifdef ELEVATOR
	int n;
	cout << "Введите номер этажа: "; cin >> n;
	elevator(n);
	//cout << "Recusion";
	//main();  
#endif // elevator

	int a, b;
	cout << "\t\t\t\tФакториал: \n"; cin >> a;
	cout << "Factorial(" << a << ") = " << Factorial(5) << endl;
	cout << "\n\n\t\t\t\tВозведение в степень " << endl;
	cout << "Введите основание: "; cin >> a;
	cout << "Введите степень: "; cin >> b;
	cout << a << " в степени " << b << " = " << Power(a, b);
	cout << "\n\n\t\t\t\tЧисла фибоначчи:" << endl;
	cout << "Введите предел чисел: "; cin >> a;
	Fibonachi(a);


}
void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	elevator(floor - 1);
	cout << "Вы на " << floor << " этаже" << endl;
}

int Factorial(int n)
{
	if (n <= 1)return 1;
	return n * Factorial(n - 1);
}
double Power(double a, int n)
{
	if (n == 0) return 1;
	if (n > 0) return a * Power(a, n - 1);
	return 1 / Power(a, -n);
}
void Fibonachi(int limit, int a, int b)
{
	if (a > limit)return;
	cout << a << " ";
	Fibonachi(limit, b, a + b);
}