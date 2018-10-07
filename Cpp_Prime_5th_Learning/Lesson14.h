#pragma once
#ifndef _LESSON_14_
#define _LESSON_14_

#include"header.h"

class Sales_data {
	friend std::ostream &operator<<(std::ostream&, const Sales_data&);
	friend std::istream &operator>>(std::istream&, Sales_data&);
	friend bool operator==(const Sales_data&, const Sales_data&);
	friend bool operator!=(const Sales_data&, const Sales_data&);
	friend Sales_data operator+(const Sales_data&, const Sales_data&);
public:
	Sales_data() = default; 
	Sales_data(const Sales_data &orig) :bookNo(orig.bookNo), units_sold(orig.units_sold), revenue(orig.revenue) {}
	Sales_data(const std::string &s) :bookNo(s) {}
	Sales_data(const std::string s, unsigned cnt, double rev) :bookNo(s), units_sold(cnt), revenue(rev*cnt) {}
	Sales_data(std::istream &is) :Sales_data("") { is >> bookNo; }	//委托构造函数
	std::string isbn() const { return bookNo; }
	~Sales_data() {}

	Sales_data &operator=(const Sales_data&);
	Sales_data &operator=(const std::string&);
	Sales_data &operator+=(const Sales_data&);
private:
	double avg_price() const { return units_sold ? revenue / units_sold : 0; }
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data& Sales_data::operator=(const Sales_data &rhs) {
	bookNo = rhs.bookNo;
	units_sold = rhs.units_sold;
	revenue = rhs.revenue;
	return *this;
}
Sales_data& Sales_data::operator=(const std::string &s) {
	bookNo = s;
	units_sold = 0;
	revenue = 0.0;
	return *this;
}
Sales_data& Sales_data::operator+=(const Sales_data &rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.isbn() == rhs.isbn() &&
		lhs.units_sold == rhs.units_sold &&
		lhs.revenue == rhs.revenue;
}
bool operator!=(const Sales_data &lhs, const Sales_data &rhs) {
	return !(lhs == rhs);
}
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs;
	sum += rhs;
	return sum;
}
std::ostream& operator<<(std::ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
	return os;
}
std::istream& operator>>(std::istream &is, Sales_data &item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	if (is)
		item.revenue = item.units_sold*price;
	else
		item = Sales_data();
	return is;
}

#endif // !_LESSON_14_
