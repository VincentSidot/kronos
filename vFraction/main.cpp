#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include "vFraction.h"
//#include "vFunc.h"
#include "vDefinition.h"


int main(int argc, char **argv)
{
	vIntervalle test("[5/9;9/3[");
	std::cout << test << std::endl;
	"[5,10]" >> test;
	std::cout << test << std::endl;
	test << "[32/10,89/100]";
	std::cout << test << std::endl;

	getchar();
	return 0;
}