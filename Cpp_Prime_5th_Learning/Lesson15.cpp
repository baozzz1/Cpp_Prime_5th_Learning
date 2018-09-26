#include "Lesson15.h"
#include<iostream>
using namespace std;

class base {
	friend class Pal;
public:
	string name() { return basename; }
	virtual void print(ostream &os) { os << basename; }
private:
	string basename;

protected:
	int prot_mem;
};
class derived :public base {
public:
	void print(ostream &os) { base::print(os); os << " " << i; }
private:
	int i;
};

class Sneaky :public base {
	friend void clobber(Sneaky&);
	friend void clobber(base&);
	int j;
};
void clobber(Sneaky &s) { s.j = s.prot_mem = 0; }
void clobber(base &b) { /*b.prot_mem =0 ;*/ }

//友元关系不能继承
class Pal {
public:	
	int f(base b) { return b.prot_mem; }	//Right
	int f2(Sneaky s) { /*return s.j;*/ }	//Wrong
	int f3(Sneaky s) { return s.prot_mem; }	//Right
};
class D2 :public Pal {
public:
	int mem(base b) { /*return b.prot_mem;*/ }	//Wrong
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

#if Lesson15_7
int main() {
	Quote q1("Quote", 100.0);
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
#endif // Lesson15_7
