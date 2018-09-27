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
	virtual ~Quote() = default;	//对析构函数进行动态绑定
	virtual void debug(std::ostream &os) {
		os << "ISBN: " << bookNo << " # price: " << price << std::endl;
	}
	//该虚函数返回当前对象的一份动态分配的拷贝
	virtual Quote* clone() const& { return new Quote(*this); }			//拷贝它给定的对象
	virtual Quote* clone() && { return new Quote(std::move(*this)); }	//移动操作
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
	Bulk_quote* clone() const & { return new Bulk_quote(*this); }
	Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); }
private:
	std::size_t min_qty = 0;	//适用于折扣政策的最小购买量
	double discount = 0.0;		//以小数表示的折扣率
};

class Basket {
public:
#if old_version_add_item
	void add_item(const std::shared_ptr<Quote> &sale) { items.insert(sale); }
#endif // old_version_add_item
	//new version of add_item
	void add_item(const Quote& sale) { items.insert(std::shared_ptr<Quote>(sale.clone())); }
	void add_item(Quote&& sale) { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }

	double total_receipt(std::ostream&) const;
private:
	//用于比较shared_ptr，multiset成员会用到它
	static bool compare(const std::shared_ptr<Quote> &lhs,
		const std::shared_ptr<Quote> &rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}
	//multiset保存多个报价，按照compare成员排序
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{ compare };
};
#endif // !_LESSON15_8_
