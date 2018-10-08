#pragma once
#ifndef _LESSON17_
#define _LESSON17_

#include"header.h"
#include<bitset>
#include<regex>

/*
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
*/
using line_no = std::vector<std::string>::size_type;
using line_it = std::set<line_no>::const_iterator;

class TextQuery_Exercise17_3 {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery_Exercise17_3() :file(), wm() {}
	TextQuery_Exercise17_3(std::ifstream&);
	std::tuple<std::string, std::shared_ptr<std::set<line_no>>, std::shared_ptr<std::vector<std::string>>> query_rewrite(const std::string&)const;
private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

#endif