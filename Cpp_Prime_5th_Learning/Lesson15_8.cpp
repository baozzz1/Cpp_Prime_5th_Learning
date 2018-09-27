#include "Lesson15_8.h"

using namespace std;

double print_total(ostream &os, const Quote &item, size_t n);
double Basket::total_receipt(ostream &os) const
{
	double sum = 0.0;
	//��Ϊitems������multiset�����ڶ����ͬ��iter�ؼ��֣����ԡ�����������������ʹ��upper_bound������
	//���ܷ���ָ��������iter�ؼ�����ȵ�Ԫ�������һ��Ԫ�ص���һλ��
	for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
		sum += print_total(os, **iter, items.count(*iter));
	}
	os << "Total Sale: " << sum << endl;
	return sum;
}
