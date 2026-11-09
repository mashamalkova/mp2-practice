#include <gtest/gtest.h>
#include "postfix_form.h"
#include <vector>

TEST(PostfixForm, can_getpostfix_simple_expression) {
    ArithmeticExpression ae("A+B");
    EXPECT_EQ(ae.GetPostfix(), "AB+");
}

TEST(PostfixForm, can_getpostfix_complex_expression) {
    ArithmeticExpression ae("A+(B-C)*D");
    EXPECT_EQ(ae.GetPostfix(), "ABC-D*+");
}

TEST(PostfixForm, can_find_unique_in_simple_expression) {
    ArithmeticExpression ae("A+B-A");
    vector<char> expected = { 'A', 'B' };
    EXPECT_EQ(ae.GetUnique(), expected);
}

TEST(PostfixForm, can_find_unique_in_complex_expression) {
    ArithmeticExpression ae("(A+B)*C-D/E");
    vector<char> expected = { 'A', 'B', 'C', 'D', 'E' };
    EXPECT_EQ(ae.GetUnique(), expected);
}

TEST(PostfixForm, can_compute_simple_expression) {
    ArithmeticExpression ae("A+B");
    vector <pair<char, double>> vars = { {'A', 2.0}, {'B', 3.0} };
    EXPECT_DOUBLE_EQ(ae.Compute(vars), 5.0);
}

TEST(PostfixForm, can_compute_complex_expression) {
    ArithmeticExpression ae("A+(B-C)*D-F/(G-H)");
    vector <pair<char, double>> vars = {
        {'A', 1.0}, {'B', 2.0}, {'C', 3.0},
        {'D', 2.0}, {'F', 1.0}, {'G', 2.0}, {'H', 1.0}
        };
    EXPECT_DOUBLE_EQ(ae.Compute(vars), -2.0);
}

TEST(PostfixForm, cant_divide_by_zero) {
    ArithmeticExpression ae("A/B");
    vector <pair<char, double>> vars = { {'A', 5.0}, {'B', 0.0} };
    EXPECT_THROW(ae.Compute(vars), std::exception);
}

// todo: errors
// A++B
// -A
// A+++B
// ((A+B)
// ...