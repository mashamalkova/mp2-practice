#include <iostream>
#include <BaseTsd.h>

const int MAX_STACK_SIZE = 1000000;

template <typename T>
class TStack {
	SSIZE_T size, top_idx;
	T* st;

public:
	TStack(SSIZE_T sz){
		if (sz < 1)
			throw std::exception("Stack size should be greater than zero");
		if (sz > MAX_STACK_SIZE)
			throw std::length_error("Stack size too large");
		size = sz;
		top_idx = -1;
		st = new T[sz];
	}
	TStack(const TStack<T>& s): size(s.size), top_idx(s.top_idx) {
		st = new T[size];
		for (SSIZE_T i = 0; i <= s.top_idx; i++) {
			st[i] = s.st[i];
		}
	}
	TStack(TStack<T>&& s) : size(s.size), top_idx(s.top_idx) {
		st = s.st;
		s.st = nullptr;
		s.size = 0;
		s.top_idx = -1;
	}
	~TStack() {
		delete[] st;
	}

	void push(const T& x) {
		if (isFull())
			throw std::exception("Stack overflow");
		st[++top_idx] = x;
	}
	void pop() {
		if (isEmpty())
			throw std::exception("Stack is empty");
		top_idx--;
	}
	T top()const {
		if (isEmpty())
			throw std::exception("Stack is empty");
		return st[top_idx];
	}
	bool isFull() const {
		return top_idx == size-1;
	}
	bool isEmpty() const {
		return top_idx == -1;
	}
	const TStack<T>& operator = (const TStack<T>& s) {
		if (this == &s)
			return *this;
		if (size != s.size) {
			T* tmp = new T[s.size];
			delete[] st;
			st = tmp;
			size = s.size;
		}
		top_idx = s.top_idx;
		for (SSIZE_T i = 0; i <= top_idx; i++) {
			st[i] = s.st[i];
		}
		return *this;
	}
	TStack<T>& operator = (const TStack<T>&& s) {
		delete st[];
		st = s.st;
		s.st = nullptr;
		size = s.size;
		s.size = 0;
		top_idx = s.top_idx;
		s.top_idx = -1;
		return *this;
	}
	bool operator ==(const TStack<T>& s) const{
		if (this == &s)
			return true;
		if (top_idx != s.top_idx) {
			return false;
		}
		for (SSIZE_T i = 0; i <= top_idx; i++) {
			if (st[i] != s.st[i])
				return false;
		}
		return true;
	}
	bool operator != (const TStack<T>& s) const{
		return !(*this == s);
	}
};