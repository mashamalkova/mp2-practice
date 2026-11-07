#include "postfix_form.h"
#include <iostream>
#include <vector>

bool ArithmeticExpression::isOperation(char c) {
	return OPERATIONS.find(c) != string::npos;
}

int ArithmeticExpression::getPriority(char c) {
	if (c == '(') return 1;
	if (c == '-' || c == '+') return 2;
	if (c == '*' || c == '/') return 3;
	return 0;
}

string ArithmeticExpression::GetPostfix() {
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
			double op1 = val_operands.top();
			val_operands.pop();
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
	return val_operands.top();
}
vector<char> ArithmeticExpression::GetUnique() {
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

vector <pair<char, double>> ArithmeticExpression::MakeVectorPair() {
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