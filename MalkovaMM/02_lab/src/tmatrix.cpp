#include "tmatrix.h"
#include <iostream>

using namespace std;

template<typename T>
TDynamicVector<T>::TDynamicVector(const TDynamicVector& v) : sz(v.sz) {
	pMem = new T[sz];
	copy(v.pMem, v.pMem + sz, pMem);
}
template<typename T>
TDynamicVector<T>::TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem) {
	v.sz = 0;
	v.pMem = nullptr;
}
template<typename T>
TDynamicVector<T>::~TDynamicVector() {
	delete[] pMem;
}
template<typename T>
TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector& v) {
	if (this != &v) {
		TDynamicVector<T> tmp(v);
		swap(*this, tmp);
	}
	return *this;
}
// индексация
template<typename T>
T& TDynamicVector<T>::operator[](size_t ind) {
	return pMem[ind];
}
template<typename T>
const T& TDynamicVector<T>::operator[](size_t ind) const {
	return pMem[ind];
}
// индексация с контролем
template<typename T>
T& TDynamicVector<T>::at(size_t ind) {
	if (ind >= sz) {
		throw out_of_range("index out of range in at()");
	}
	return pMem[ind];
}

template<typename T>
const T& TDynamicVector<T>::at(size_t ind) const {
	if (ind >= sz) {
		throw out_of_range("index out of range in at()");
	}
	return pMem[ind];
}

// сравнение
template<typename T>
bool TDynamicVector<T>::operator==(const TDynamicVector& v) const noexcept {
	if (sz != v.sz) {
		return false;
	}
	for (size_t i = 0; i < sz; i++) {
		if (pMem[i] != v.pMem[i]) {
			return false;
		}
	}
	return true;
}

template<typename T>
bool TDynamicVector<T>::operator!=(const TDynamicVector& v) const noexcept {
	return !(*this == v);
}

// скалярные операции
template<typename T>
TDynamicVector<T> TDynamicVector<T>::operator+(T val) {
	TDynamicVector<T> res(sz);
	for (size_t i = 0; i < sz; i++) {
		res.pMem[i] += val;
	}
	return res;
}

template<typename T>
TDynamicVector<T> TDynamicVector<T>::operator-(T val) {
	TDynamicVector<T> res(sz);
	for (size_t i = 0; i < sz; i++) {
		res.pMem[i] -= val;
	}
	return res;
}

template<typename T>
TDynamicVector<T> TDynamicVector<T>::operator*(T val) {
	TDynamicVector<T> res(sz);
	for (size_t i = 0; i < sz; i++) {
		res.pMem[i] *= val;
	}
	return res;
}

// векторные операции
template<typename T>
TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector& v) const{
	if (sz != v.sz) {
		throw invalid_argument("vector sizes are different");
	}
	TDynamicVector<T> res(sz);
	for (size_t i = 0; i < sz; i++) {
		res.pMem[i] = pMem[i] + v.pMem[i];
	}
	return res;
}

template<typename T>
TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector& v) const{
	if (sz != v.sz) {
		throw invalid_argument("vector sizes are different");
	}
	TDynamicVector<T> res(sz);
	for (size_t i = 0; i < sz; i++) {
		res.pMem[i] = pMem[i] - v.pMem[i];
	}
	return res;
}

template<typename T>
T TDynamicVector<T>::operator*(const TDynamicVector& v) const noexcept(noexcept(T())) {
	if (sz != v.sz) {
		throw invalid_argument("vector sizes are different");
	}
	T sum = T();
	for (size_t i = 0; i < sz; i++) {
		sum = sum + (pMem[i] * v.pMem[i]);
	}
	return sum;
}

template class TDynamicVector<int>;
template class TDynamicVector<double>;



//матрица

// сравнение
template<typename T>
bool TDynamicMatrix<T>::operator==(const TDynamicMatrix<T>& m) const noexcept {
	if (sz != m.sz) return false;
	for (size_t i = 0; i < sz; i++) {
		if (m.pMem[i] != pMem[i])
			return false;
	}
	return true;
}

// матрично-скалярные операции
template<typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const T& val) {
	TDynamicMatrix<T> res(sz);
	for (size_t i = 0; i < sz; i++) {
		res.pMem[i] = pMem[i] * val;
	}
	return res;
}

// матрично-векторные операции
template<typename T>
TDynamicVector<T> TDynamicMatrix<T>::operator*(const TDynamicVector<T>& v) {
	if (sz != v.size()) {
		throw invalid_argument("different sizes");
	}
	TDynamicVector<T> res(sz);
	for (size_t i = 0; i < sz; i++) {
		res[i] = pMem[i] * v;
	}
	return res;
}

// матрично-матричные операции
template<typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& m) {
	if (sz != m.sz) {
		throw invalid_argument("different sizes");
	}
	TDynamicMatrix<T> res(sz);
	for (size_t i = 0; i < sz; i++) {
		res[i] = pMem[i] + m.pMem[i];
	}
	return res;
}

template<typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& m) {
	if (sz != m.sz) {
		throw invalid_argument("different sizes");
	}
	TDynamicMatrix<T> res(sz);
	for (size_t i = 0; i < sz; i++) {
		res[i] = pMem[i] - m.pMem[i];
	}
	return res;
}

template<typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& m) {
	if (sz != m.sz) {
		throw invalid_argument("different sizes");
	}
	TDynamicMatrix<T> res(sz);
	for (size_t i = 0; i < sz; i++) {
		for (size_t j = 0; j < sz; j++) {
			for (size_t k; k < sz; k++) {
				res[i][j] += pMem[i][k] * m.pMem[k][j];
			}
		}
	}
	return res;
}

// ввод/вывод
template<typename T>
istream& operator>>(istream& istr, TDynamicMatrix<T>& v) {
	for (size_t i = 0; i < v.size; i++) {
		istr >> v[i];
	}
	return istr;
}

template<typename T>
ostream& operator<<(ostream& ostr, const TDynamicMatrix<T>& v) {
	for (size_t i = 0; i < v.size; i++) {
		ostr << v[i] << "\n";
	}
	return ostr;
}

template class TDynamicMatrix<int>;
template class TDynamicMatrix<double>;
template class TDynamicVector<TDynamicVector<int>>;
template class TDynamicVector<TDynamicVector<double>>;