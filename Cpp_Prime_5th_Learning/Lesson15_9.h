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

//������࣬����Ĳ�ѯ���ʹ������������г�Ա����private��
class Query_base {
	friend class Query;
protected:
	using line_no = TextQuery::line_no;		//����eval����
	virtual ~Query_base() = default;
private:
	//eval�����뵱ǰQueryƥ���QueryResult,��Ϊ���麯��
	virtual QueryResult eval(const TextQuery&) const = 0;
	//rep�Ǳ�ʾ��ѯ��һ��string
	virtual std::string rep() const = 0;
};

//����һ������Query_base�̳���ϵ�Ľӿ���
class Query {
	//��Щ�������Ҫ���ʽ���shared_ptr�Ĺ��캯�������ú�����˽�е�
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const std::string&);		//����һ���µ�WordQuery
	//�ӿں��������ö�Ӧ��Query_base����
	QueryResult eval(const TextQuery &t) const { return q->eval(t); }
	std::string rep() const { return q->rep(); }
private:
	Query(std::shared_ptr<Query_base> query) :q(query) {}
	std::shared_ptr<Query_base> q;
};

//Query����������
std::ostream &
operator<<(std::ostream &os, const Query &query) {
	return os << query.rep();
}

//--------------------------------------------------------------------------------------------
//-----------------------------------------������----------------------------------------------
//ʵ�������ǵ������ಢ���洢Query_base��ָ�룬����ֱ��ʹ��Query���󡣣��ýӿ�����������Լ���Ƶ��ࣩ
//--------------------------------------------------------------------------------------------

//---------WordQuery�� ������string��Query���캯������-----------
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

//-----------------NotQuery�� �� ~�����-------------------
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

//-----------------BinaryQuery��---------------------------
class BinaryQuery :public Query_base {
protected:
	BinaryQuery(const Query &l, const Query &r, std::string s) :
		lhs(l), rhs(r), opSym(s) {}
	//�����ࣺBinaryQuery������eval
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;
	std::string opSym;
};

//-------------------AndQuery�༰OrQuery��-------------------
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
