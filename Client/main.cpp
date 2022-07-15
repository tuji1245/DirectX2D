
#include <iostream>
#include "math_test.h"
#include "class_test.h"


void main()
{
	using namespace std;
	math_test::fibonacci_init(1,1);
	{
		const int max = 9;
		for (int i = 0; i < max; i++)
		{
			math_test::fibonacci_next();
			cout << math_test::fibonacci_current() << endl;
		}
	}


	math_test::test<int> _Test;

	_Test.a = 10;

	cout << _Test.add(100,100) << endl;

	std::system("pause");
	return;
}