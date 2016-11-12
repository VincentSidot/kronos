#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include "vFraction.h"
#include "vFunc.h"


int main(int argc, char **argv)
{
	vFraction test("10/3+3");
	std::cout << test << " = " << vFraction::aproximateValue<double>(test) << std::endl;

	
	

	getchar();
	return 0;
}