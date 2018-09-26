#include "Lesson15.h"
#include<iostream>
using namespace std;

class base {
public:
	string name() { return basename; }
	virtual void print(ostream &os) { os << basename; }
private:
	string basename;
};
class derived :public base {
public:
	void print(ostream &os) { base::print(os); os << " " << i; }
private:
	int i;
};

double pirce_total(ostream &os, const Quote &item, size_t n) {
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

double Bulk_quote::net_price(size_t cnt) const
{
	if (cnt >= min_qty)
		return cnt * (1 - discount)*price;
	else
		return cnt * price;
}

int main() {
	Quote q1("Quote",100.0);
	Bulk_quote q2("Bulk_Quote", 100.0, 1, 0.7);
	pirce_total(cout, q1, 10);
	pirce_total(cout, q2, 10);
	q1.debug(cout);
	q2.debug(cout);

	base bobj;
	derived dobj;
	base *bp1 = &bobj;
	base *bp2 = &dobj;
	base &br1 = bobj;
	base &br2 = dobj;

	bobj.print(cout);
	dobj.print(cout);
	bp1->name();
	bp2->name();
	br1.print(cout);
	br2.print(cout);



}