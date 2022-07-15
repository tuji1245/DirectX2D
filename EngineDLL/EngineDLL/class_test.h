#include "pch.h"


#ifdef ENGINEDLL_EXPORTS
#define CLASSTEST_API __declspec(dllexport)
#else
#define CLASSTEST_API __declspec(dllimport)
#endif


#define DllExport   __declspec( dllexport )

namespace math_test {

	template<typename T>
	class DllExport test
	{
	public:
		test();
		virtual ~test();
		T a, b;

		int add(int a, int b);
	};
}