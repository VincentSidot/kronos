#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include "vFraction.h"
//#include "vFunc.h"
//#include "vDefinition.h"



int main(int argc, char **argv)
{

	vFraction test("5/2");
	std::cout << test << std::endl;
	test = -test;
	std::cout << test << std::endl;

	getchar();
	return 0;
}