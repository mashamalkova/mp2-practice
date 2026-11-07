#include <iostream>
#include "stack.h"
#include <vector>
#include <BaseTsd.h>

using namespace std;

const SSIZE_T STACK_SIZE = 10000;

class ArithmeticExpression{
	string expression;
	const string OPERATIONS = "+-*/()";
	bool isOperation(char);
	int getPriority(char);

public:
	ArithmeticExpression(const string& exp): expression(exp){}
	string GetPostfix();
	double Compute(const vector <pair<char, double>>&);
	vector<char> GetUnique();
	vector <pair<char, double>> MakeVectorPair();
};