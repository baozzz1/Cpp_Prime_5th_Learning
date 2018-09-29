#pragma once
#ifndef  _LESSON16_
#define _LESSON16_

#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<algorithm>

template <typename T>
int compare(const T &v1, const T &v2) {
	if (v1 < v2) return -1;
	if (v2 < v1) return 1;
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
#endif // ! _LESSON16_
