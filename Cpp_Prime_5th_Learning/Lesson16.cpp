#include "Lesson16.h"
#include"Lesson14.h"
using namespace std;

class Sales_data;

template <typename T> 
Blob<T>::Blob() : data(make_shared<vector<T>>()) {}

template <typename T> 
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)) {}

template <typename T>
void Blob<T>::check(size_type i, const string &msg) const {
	if (i >= data->size())
		throw out_of_range(msg);
}

template <typename T>
T& Blob<T>::back() {
	check(0, "back on empty Blob");
	return data->back();
}
template <typename T>
const T& Blob<T>::back() const {
	check(0, "back on empty Blob");
	return data->back();
}
template <typename T>
T& Blob<T>::operator[](size_type i) {
	check(i, "subscript out of range");
	return (*data)[i];
}
template <typename T>
const T& Blob<T>::operator[](size_type i) const {
	check(i, "subscript out of range");
	return (*data)[i];
}
template <typename T>
void Blob<T>::pop_back() {
	check(0, "pop_back on empty Blob");
	data->pop_back();
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
	BlobPtr ret = *this;
	++*this;
	return ret;
}

void runLesson16() {
	vector<int> vec = { 0,1,2,3,4,5,6,7,8,9 };
	list<string> lst = { "ling","yi","er","san","si","wu","liu","qi","ba","jiu" };
	func16_4(vec.cbegin(), vec.cend(), 9);
	func16_4(lst.cbegin(), lst.cend(), "shiyi");

}