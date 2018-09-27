#include "Lesson15_9.h"

using namespace std;

//------------------- OrQuery::eval -------------------
QueryResult
OrQuery::eval(const TextQuery &text) const {
	auto right = rhs.eval(text), left = lhs.eval(text);
	auto ret_lines = make_shared<set<line_no>>(left.cbegin(), left.cend());
	ret_lines->insert(right.cbegin(), right.cend());
	return QueryResult(rep(), ret_lines, left.get_file());
}

//------------------- AndQuery::eval -------------------
QueryResult
AndQuery::eval(const TextQuery &text) const {
	auto right = rhs.eval(text), left = lhs.eval(text);
	auto ret_lines = make_shared<set<line_no>>();
	set_intersection(left.cbegin(), left.cend(),
		right.cbegin(), right.cend(),
		inserter(*ret_lines, ret_lines->begin()));
	ret_lines->insert(right.cbegin(), right.cend());
	return QueryResult(rep(), ret_lines, left.get_file());
}

//------------------- NotQuery::eval -------------------
QueryResult
NotQuery::eval(const TextQuery &text) const {
	//通过Query运算对象对eval进行虚调用
	auto result = query.eval(text);
	//开始时结果set为空
	auto ret_lines = make_shared<set<line_no>>();
	auto beg = result.cbegin(), end = result.cend();
	//对于输入文件的每一行，如果该行不在result内，则将其添加到ret_lines
	auto sz = result.get_file()->size();
	for (size_t n = 0; n != sz; ++n) {
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}

int main() {
	ifstream ifile("Lesson15_9_input.txt");
	TextQuery textquery(ifile);
	//print(cout, Query("fiery").eval(textquery));
	Query q = Query("fiery") & Query("bird") | Query("wind");
	//Query q = Query("magical") | Query("him");
	print(cout, q.eval(textquery));

}

