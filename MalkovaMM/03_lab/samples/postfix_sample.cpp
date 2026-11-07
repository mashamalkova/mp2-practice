#include "postfix_form.h"
#include <iostream>
#include <vector>
#include <clocale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    string expression;
    cout << "Введите выражение: ";
    cin >> expression;
    ArithmeticExpression ae(expression);
    cout << "\nПостфиксная форма: " << ae.GetPostfix() << endl;
    vector <pair<char, double>> vars = ae.MakeVectorPair();
    double result = ae.Compute(vars);
    cout << "\nРезультат: " << result << endl;
    return 0;
}
