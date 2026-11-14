#include "postfix_form.h"
#include <iostream>
#include <vector>

bool ArithmeticExpression::isOperation(char c) const {
	return OPERATIONS.find(c) != string::npos;
}

int ArithmeticExpression::getPriority(char c) const {
	if (c == '(') return 1;
	if (c == '-' || c == '+') return 2;
	if (c == '*' || c == '/') return 3;
	return 0;
}

bool ArithmeticExpression::isValidExp(string exp) const {
	if (exp.empty())
		return false;
	if (isOperation(exp[0]) && exp[0] != '-' && exp[0] != '(')
		return false;
	char last = exp.back();
	if (isOperation(last) && last != ')')
		return false;
	char prev = ' ';
	int ck = 0;
	for (char c : exp) {
		if (c == '(')
			ck++;
		if (c == ')')
			ck--;
		if (ck < 0)
			return false;
		if (prev =='(' && c == ')')
			return false;
		if (isOperation(prev) && isOperation(c) && prev != '(' && prev != ')' && c != '(' && c != ')') {
			return false;
		}
		prev = c;
	}
	return ck == 0;
}

string ArithmeticExpression::GetPostfix() const {
	TStack<char> operands(STACK_SIZE);
	TStack<char> operations(STACK_SIZE);
	string result = "";

	for (char c : expression) {
		if (c == ' ') continue;
		if (!isOperation(c)) {
			operands.push(c);
		}
		else if (c == '(') {
			operations.push(c);
		}
		else if (c == ')') {
			while (!operations.isEmpty() && operations.top() != '(') {
				operands.push(operations.top());
				operations.pop();
			}
			if (!operations.isEmpty()) {
				operations.pop();
			}
		}
		else {
			while (!operations.isEmpty() && operations.top() != '('
				&& getPriority(operations.top()) >= getPriority(c)) {
				operands.push(operations.top());
				operations.pop();
			}
			operations.push(c);
		}
	}
	while (!operations.isEmpty()) {
		operands.push(operations.top());
		operations.pop();
	}
	while (!operands.isEmpty()) {
		result = operands.top() + result;
		operands.pop();
	}
	return result;
}

double ArithmeticExpression::Compute(const vector <pair<char, double>>& vars) {
	string postfix = GetPostfix();
	TStack<double> val_operands(STACK_SIZE);
	for (char c : postfix) {
		if (!isOperation(c)) {
			double x = 0.0;
			for (const auto& p : vars) {
				if (p.first == c) {
					x = p.second;
					break;
				}
			}
			val_operands.push(x);
		}
		else {
			double op2 = val_operands.top();
			val_operands.pop();
			double op1 = 0.0;
			if (!val_operands.isEmpty()) {
				op1 = val_operands.top();
				val_operands.pop();
			}
			double res = 0.0;
			switch (c) {
			case('+'): res = op1 + op2; break;
			case('-'): res = op1 - op2; break;
			case('*'): res = op1 * op2; break;
			case('/'):
				if (op2 == 0)
					throw invalid_argument("division by zero");
				res = op1 / op2;
				break;
			}
			val_operands.push(res);
		}
	}
	double result = val_operands.top();
	val_operands.pop();
	if (!val_operands.isEmpty())
		throw std::runtime_error("incorrect expression");
	return result; 
}
vector<char> ArithmeticExpression::GetUnique() const {
	vector<char> uniqVars;
	for (char c : expression) {
		if (c == ' ' || isOperation(c)) continue;
		bool found = false;
		for (char v : uniqVars) {
			if (v == c) {
				found = true;
				break;
			}
		}
		if (!found) {
			uniqVars.push_back(c);
		}
	}
	return uniqVars;
}

vector <pair<char, double>> ArithmeticExpression::MakeVectorPair() const {
	vector <pair<char, double>> result;
	vector<char> uniqVars = GetUnique();
	if (uniqVars.empty()) {
		cout << "нет переменных";
		return result;
	}
	cout << "введите значени€ переменных:" << endl;
	for (char c : uniqVars) {
		double val;
		cout << " " << c << " = ";
		cin >> val;
		result.push_back(make_pair(c, val));
	}
	return result;
}