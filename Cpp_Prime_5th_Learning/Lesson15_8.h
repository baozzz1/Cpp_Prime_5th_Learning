#pragma once
#ifndef _LESSON15_8_
#define _LESSON15_8_

#include<memory>
#include<string>
#include<iostream>
#include<set>
#include<vector>

class Quote {
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price) :bookNo(book), price(sales_price) {}
	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return n * price; }
	virtual ~Quote() = default;	//�������������ж�̬��
	virtual void debug(std::ostream &os) {
		os << "ISBN: " << bookNo << " # price: " << price << std::endl;
	}
private:
	std::string bookNo;
protected:
	double price = 0.0;
};

class Basket {
public:
	void add_item(const std::shared_ptr<Quote> &sale) { items.insert(sale); }
	double total_receipt(std::ostream&) const;
private:
	//���ڱȽ�shared_ptr��multiset��Ա���õ���
	static bool compare(const std::shared_ptr<Quote> &lhs,
						const std::shared_ptr<Quote> &rhs)
	{ return lhs->isbn() < rhs->isbn(); }
	//multiset���������ۣ�����compare��Ա����
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{ compare };
};
#endif // !_LESSON15_8_
