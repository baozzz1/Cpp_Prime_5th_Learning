#pragma once
#ifndef  _LESSON16_
#define _LESSON16_

#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<algorithm>

template <typename T, typename F = std::less<T>>
int compare(const T &v1, const T &v2, F f = F()) {
	if (f(v1, v2)) return -1;
	if (f(v2, v1)) return 1;
	return 0;
}

template<typename T, typename U>
T func16_4(T beg, T end, const U &target) {
	while (beg != end) {
		if (*beg == target)
			return beg;
		else
			++beg;
	}
	return end;
}

template <typename> class BlobPtr;
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob {
	friend class BlobPtr<T>;
	friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
	//构造函数
	Blob();
	Blob(std::initializer_list<T> il);
	//Blob中的元素数目
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	//添加和删除元素
	void push_back(const T &t) { data->push_back(t); }
	//移动版本
	void push_back(T &&t) { data->push_back(std::move(t)); }
	void pop_back();
	//元素访问
	T& back();
	const T& back() const;
	T& operator[](size_type i);
	const T& operator[](size_type i) const;

private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type i, const std::string &msg) const;
};

template <typename T> class BlobPtr {
public:
	BlobPtr() :curr(0) {}
	BlobPtr(Blob<T> &a, size_t sz = 0) :
		wptr(a.data), curr(sz) {}
	T& operator*() const {
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	BlobPtr& operator++();
	BlobPtr& operator--();

private:
	std::shared_prt<std::vector<T>>
		check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr;
};

#endif // ! _LESSON16_
