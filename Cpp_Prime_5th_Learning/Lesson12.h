#pragma once
#ifndef LESSON12
#define LESSON12

#include<memory>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<deque>
#include<iterator>
#include<functional>
#include<new>
#include<iostream>
#include<sstream>
#include<fstream>

class StrBlob {
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string &t) { data->push_back(t); }
	void pop_back();
	std::string &front();
	const std::string &front() const;
	std::string &back();
	const std::string &back() const;
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string &msg) const;
};
class QueryResult;
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery() :file(), wm() {}
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&)const;
private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	using line_no = std::vector<std::string>::size_type;
	using line_it = std::set<line_no>::const_iterator;
	QueryResult(std::string s,
		std::shared_ptr<std::set<line_no>> p,
		std::shared_ptr<std::vector<std::string>> f) :
		sought(s), lines(p), files(f) {}
	line_it cbegin() const { return lines->cbegin(); }
	line_it cend() const { return lines->cend(); }
	std::shared_ptr<std::vector<std::string>> get_file() const { return files; }
	
private:
	std::string sought;//查询单词
	std::shared_ptr<std::set<line_no>> lines;//出现的行号
	std::shared_ptr<std::vector<std::string>> files;//输入文件
};
#endif // !LESSON12
