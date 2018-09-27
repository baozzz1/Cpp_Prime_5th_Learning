#pragma once
#ifndef _LESSON15_9_
#define _LESSON15_9_

#include<memory>
#include<string>
#include<iostream>
#include<set>
#include<vector>
#include<algorithm>

//include with "Lesson12.h"
#include"Lesson12.h"
class TextQuery;
class QueryResult;

//抽象基类，具体的查询类型从中派生，所有成员都是private的
class Query_base {
	friend class Query;
protected:
	using line_no = TextQuery::line_no;		//用于eval函数
	virtual ~Query_base() = default;
private:
	//eval返回与当前Query匹配的QueryResult,此为纯虚函数
	virtual QueryResult eval(const TextQuery&) const = 0;
	//rep是表示查询的一个string
	virtual std::string rep() const = 0;
};

//这是一个管理Query_base继承体系的接口类
class Query {
	//这些运算符需要访问接受shared_ptr的构造函数，而该函数是私有的
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const std::string&);		//构建一个新的WordQuery
	//接口函数：调用对应的Query_base操作
	QueryResult eval(const TextQuery &t) const { return q->eval(t); }
	std::string rep() const { return q->rep(); }
private:
	Query(std::shared_ptr<Query_base> query) :q(query) {}
	std::shared_ptr<Query_base> q;
};

//Query的输出运算符
std::ostream &
operator<<(std::ostream &os, const Query &query) {
	return os << query.rep();
}

//--------------------------------------------------------------------------------------------
//-----------------------------------------派生类----------------------------------------------
//实际上我们的派生类并不存储Query_base的指针，而是直接使用Query对象。（用接口类简化了我们自己设计的类）
//--------------------------------------------------------------------------------------------

//---------WordQuery类 及接受string的Query构造函数定义-----------
class WordQuery : public Query_base {
	friend class Query;
	WordQuery(const std::string &s) :query_word(s) {}

	QueryResult eval(const TextQuery &t) const override {
		return t.query(query_word);
	}
	std::string rep() const override { return query_word; }

	std::string query_word;
};
inline
Query::Query(const std::string &s) :q(new WordQuery(s)) {}

//-----------------NotQuery类 及 ~运算符-------------------
class NotQuery : public Query_base {
	friend Query operator~(const Query&);
	NotQuery(const Query &q) :query(q) {}

	QueryResult eval(const TextQuery&) const;
	std::string rep() const override { return "~(" + query.rep() + ")"; }

	Query query;
};
inline
Query operator~(const Query &operand) {
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}

//-----------------BinaryQuery类---------------------------
class BinaryQuery :public Query_base {
protected:
	BinaryQuery(const Query &l, const Query &r, std::string s) :
		lhs(l), rhs(r), opSym(s) {}
	//抽象类：BinaryQuery不定义eval
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;
	std::string opSym;
};

//-------------------AndQuery类及OrQuery类-------------------
class AndQuery :public BinaryQuery {
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "&") {}
	QueryResult eval(const TextQuery&) const;
};
inline
Query operator&(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery :public BinaryQuery {
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "|") {}
	QueryResult eval(const TextQuery&) const;
};
inline
Query operator|(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}



#endif
