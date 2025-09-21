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
	cout << "������� ����� �����: "; cin >> n;
	elevator(n);
	//cout << "Recusion";
	//main();  
#endif // elevator

	int a, b;
	cout << "\t\t\t\t���������: \n"; cin >> a;
	cout << "Factorial(" << a << ") = " << Factorial(5) << endl;
	cout << "\n\n\t\t\t\t���������� � ������� " << endl;
	cout << "������� ���������: "; cin >> a;
	cout << "������� �������: "; cin >> b;
	cout << a << " � ������� " << b << " = " << Power(a, b);
	cout << "\n\n\t\t\t\t����� ���������:" << endl;
	cout << "������� ������ �����: "; cin >> a;
	Fibonachi(a);


}
void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "�� � �������" << endl;
		return;
	}
	cout << "�� �� " << floor << " �����" << endl;
	elevator(floor - 1);
	cout << "�� �� " << floor << " �����" << endl;
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