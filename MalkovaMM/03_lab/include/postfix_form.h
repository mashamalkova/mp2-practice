#include <iostream>
#include "stack.h"
#include <vector>
#include <BaseTsd.h>

using namespace std;

const SSIZE_T STACK_SIZE = 10000;

class ArithmeticExpression{
	string expression;
	const string OPERATIONS = "+-*/()";
	bool isOperation(char) const;
	int getPriority(char) const;
	bool isValidExp(string) const;

public:
	ArithmeticExpression(const string& exp): expression(exp){
		if (!isValidExp(exp))
			throw std::exception("incorrect expression");
	}
	string GetPostfix() const;
	double Compute(const vector <pair<char, double>>&);
	vector<char> GetUnique() const;
	vector<pair<char, double>> MakeVectorPair() const;
};