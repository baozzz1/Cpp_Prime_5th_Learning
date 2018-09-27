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
	//���麯�����ص�ǰ�����һ�ݶ�̬����Ŀ���
	virtual Quote* clone() const& { return new Quote(*this); }			//�����������Ķ���
	virtual Quote* clone() && { return new Quote(std::move(*this)); }	//�ƶ�����
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
	std::size_t min_qty = 0;	//�������ۿ����ߵ���С������
	double discount = 0.0;		//��С����ʾ���ۿ���
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
	//���ڱȽ�shared_ptr��multiset��Ա���õ���
	static bool compare(const std::shared_ptr<Quote> &lhs,
		const std::shared_ptr<Quote> &rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}
	//multiset���������ۣ�����compare��Ա����
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{ compare };
};
#endif // !_LESSON15_8_
