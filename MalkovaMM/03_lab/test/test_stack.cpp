#include <gtest/gtest.h>
#include "stack.h"

TEST(TStack, can_create_stack_with_positive_length) {
	ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, cant_create_too_large_vector) {
	ASSERT_ANY_THROW(TStack<int> s(1000005));
}

TEST(TStack, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> s(10);
	ASSERT_NO_THROW(TStack<int> s1(s));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
	TStack<int> s(5);
	for (size_t i = 0; i < 5; i++) s.push(i);
	TStack<int> s1(s);
	for (int i = 0; i < 5; i++) {
		ASSERT_TRUE(s.top() == s1.top());
		s.pop();
		s1.pop();
	}
}
TEST(TStack, copied_stack_has_its_own_memory)
{
	TStack<int> s(5);
	s.push(10);
	TStack<int> s1(s);
	s1.push(20);
	EXPECT_NE(s.top(), s1.top());
}

TEST(TStack, can_assign_stack_to_itself)
{
	TStack<int> s(5);
	s.push(10);
	ASSERT_NO_THROW(s = s);
}

TEST(TStack, can_push_element) {
	TStack<int> s(5);
	ASSERT_NO_THROW(s.push(10));
}

TEST(TStack, cant_push_element_when_stack_is_full) {
	TStack<int> s(5);
	for (int i = 0; i < 5; i++) s.push(i);
	ASSERT_ANY_THROW(s.push(10));
}

TEST(TStack, can_pop_element) {
	TStack<int> s(5);
	for (int i = 0; i < 5; i++) s.push(i);
	ASSERT_NO_THROW(s.pop());
}

TEST(TStack, cant_pop_element_when_stack_is_empty) {
	TStack<int> s(5);
	ASSERT_ANY_THROW(s.pop());
}

TEST(TStack, can_get_top_element) {
	TStack<int> s(5);
	for (int i = 0; i < 5; i++) s.push(i);
	ASSERT_NO_THROW(s.top());
}

TEST(TStack, cant_get_top_element_when_stack_is_empty) {
	TStack<int> s(5);
	ASSERT_ANY_THROW(s.top());
}

