#include "Lesson15_8.h"

using namespace std;

double print_total(ostream &os, const Quote &item, size_t n);
double Basket::total_receipt(ostream &os) const
{
	double sum = 0.0;
	//因为items是容器multiset，存在多个相同的iter关键字，所以“递增”迭代器操作使用upper_bound函数，
	//它能返回指向所有与iter关键字相等的元素中最后一个元素的下一位置
	for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
		sum += print_total(os, **iter, items.count(*iter));
	}
	os << "Total Sale: " << sum << endl;
	return sum;
}
