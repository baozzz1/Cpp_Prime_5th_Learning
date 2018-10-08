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

#endif // !_LESSON_14_
