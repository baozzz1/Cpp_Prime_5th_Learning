#pragma once
#ifndef _LESSON15_
#define _LESSON15_

#include"header.h"

class Quote {
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price) :bookNo(book), price(sales_price) {}
	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return n * price; }
	virtual ~Quote() = default;	//对析构函数进行动态绑定
	virtual void debug(std::ostream &os) {
		os << "ISBN: " << bookNo << " # price: " << price << std::endl;
	}
private:
	std::string bookNo;
protected:
	double price = 0.0;
};

class Bulk_quote :public Quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) :
		Quote(book, p), min_qty(qty), discount(disc) {}
	double net_price(std::size_t) const override;
	void debug(std::ostream &os) override {
		Quote::debug(os);
		os << "# min_qty: " << min_qty << " # discount: " << discount << std::endl;
	}
private:
	std::size_t min_qty = 0;	//适用于折扣政策的最小购买量
	double discount = 0.0;		//以小数表示的折扣率
};

//用于表示折扣值和购买量的类，派生类使用这些数值实现不同的价格策略
class Disc_quote: public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string &book, double price, std::size_t qty, double disc) :
		Quote(book, price), quantity(qty), discount(disc) {}
	double net_price(std::size_t) const = 0;	//纯虚函数
protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};

class Bulk_quote_rewrite :public Disc_quote {
public:
	Bulk_quote_rewrite() = default;
	Bulk_quote_rewrite(const std::string &book, double price, std::size_t qty, double disc) :
		Disc_quote(book, price, qty, disc) {}
	double net_price(std::size_t) const override;
};
#endif // !_LESSON15_
