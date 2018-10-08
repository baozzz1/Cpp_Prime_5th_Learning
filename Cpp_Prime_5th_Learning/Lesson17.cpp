#include"Lesson17.h"
#include"Lesson14.h"	//提供Sales_data类

using namespace std;

void Lesson17_1_1() {
	//初始化tuple
	tuple<size_t, size_t, size_t> threeD;
	tuple<string, vector<double>, int, list<int>> someVal("constants", { 3.14,2.718 }, 42, { 0,1,2,3,4,5 });
	auto item = make_tuple("0-999-78345-X", 3, 20.00);

	//索引的使用，左值右值
	auto book = get<0>(item);
	auto cnt = get<1>(item);
	auto price = get<2>(item) / cnt;
	get<2>(item) *= 0.8;

	// value 和 type 的使用
	typedef decltype(item) trans;
	size_t sz = tuple_size<trans>::value;
	tuple_element<1, trans>::type cntNew = get<1>(item);

}

void Exercise17_1() {
	tuple<int, int, int> E17_1(10, 20, 30);
	tuple<string, vector<string>, pair<string, int>> E17_2((string)"1", { "2","2" }, { "3",3 });

}

/*-------------------------------------------------------------------------------
------------------------------	Exercise 17.3	---------------------------------
---------------------------------------------------------------------------------
*/
TextQuery_Exercise17_3::TextQuery_Exercise17_3(ifstream &is) :file(new vector<string>) {
	string text;
	while (getline(is, text)) {
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word) {
			auto iter = word.begin();
			while (iter != word.end()) {
				if ((*iter >= 'a' && *iter <= 'z') || ((*iter >= '0' && *iter <= '9'))) { ++iter; }
				else if (*iter >= 'A' && *iter <= 'Z') { *iter = tolower(*iter); ++iter; }
				else { iter = word.erase(iter); }
			}
			auto &lines = wm[word];
			if (!lines)
				lines.reset(new set<line_no>);
			lines->insert(n);
		}
	}
}
tuple<string, shared_ptr<set<line_no>>, shared_ptr<vector<string>>> TextQuery_Exercise17_3::query_rewrite(const string &sought)const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.cend())
		return tuple<string, shared_ptr<set<line_no>>, shared_ptr<vector<string>>>(sought, nodata, file);
	else
		return tuple<string, shared_ptr<set<line_no>>, shared_ptr<vector<string>>>(sought, loc->second, file);
}
extern string make_plural_rewrite(size_t ctr, const string &word, const string &ending) { return (ctr > 1) ? word + ending : word; }
ostream &print(ostream &os, const tuple<string, shared_ptr<set<line_no>>, shared_ptr<vector<string>>> &qr) {
	os << get<0>(qr) << " occurs " << get<1>(qr)->size() << " " << make_plural_rewrite(get<1>(qr)->size(), "time", "s") << endl;
	for (auto num : *(get<1>(qr)))
		os << "\t(line " << num + 1 << ") " << *(get<2>(qr)->begin() + num) << endl;
	return os;
}
void runQueries_rewrite(ifstream &infile) {
	TextQuery_Exercise17_3 tq(infile);
	while (true) {
		cout << "enter word to look for, or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q")break;
		print(cout, tq.query_rewrite(s)) << endl;
	}
}

/*-------------------------------------------------------------------------------
------------------------------	Lesson 17.1.2	---------------------------------
---------------------------------------------------------------------------------
*/
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs);
//matches有三个成员：一家店的索引和两个指向书店vector中元素的迭代器
typedef tuple<vector<Sales_data>::size_type,
	vector<Sales_data>::const_iterator,
	vector<Sales_data>::const_iterator> matches;
vector<matches> findBook(const vector<vector<Sales_data>> &files, const string &book) {
	vector<matches> ret;
	for (auto it = files.cbegin(); it != files.cend(); ++it) {
		auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);
		if (found.first != found.second)
			ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second));
	}
	return ret;
}
void reportResults(istream &in, ostream &os, const vector<vector<Sales_data>> &files) {
	string s;//要查找的书
	while (in >> s) {
		auto trans = findBook(files, s);
		if (trans.empty()) {
			cout << s << " not found in any stores" << endl;
			continue;
		}
		for (const auto &store : trans)
			os << "store " << get<0>(store) << " sales: " << accumulate(get<1>(store), get<2>(store), Sales_data(s)) << endl;
	}
}
/*-------------------------------------------------------------------------------
------------------------------	Exercise 17.5	---------------------------------
---------------------------------------------------------------------------------
*/
typedef pair<vector<Sales_data>::size_type, pair<vector<Sales_data>::const_iterator, vector<Sales_data>::const_iterator>> matches_exercise17_5;
vector<matches_exercise17_5> findBook_exercise17_5(const vector<vector<Sales_data>> &files, const string &book) {
	vector<matches_exercise17_5> ret;
	for (auto it = files.cbegin(); it != files.cend(); ++it) {
		auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);
		if (found.first != found.second)
			ret.push_back(make_pair(it - files.cbegin(), found));
	}
	return ret;
}
void reportResults_exercise17_5(istream &in, ostream &os, const vector<vector<Sales_data>> &files) {
	string s;//要查找的书
	while (in >> s) {
		auto trans = findBook_exercise17_5(files, s);
		if (trans.empty()) {
			cout << s << " not found in any stores" << endl;
			continue;
		}
		for (const auto &store : trans)
			os << "store " << store.first << " sales: " << accumulate(store.second.first, store.second.second, Sales_data(s)) << endl;
	}
}

/*-------------------------------------------------------------------------------
------------------------------	Exercise 17.6	---------------------------------
---------------------------------------------------------------------------------
*/
template <typename T>
class match_exercise17_6 {
public:
	match_exercise17_6(typename vector<T>::size_type i, typename vector<T>::const_iterator it1, typename  vector<T>::const_iterator it2) :index(i), first(it1), second(it2) {}
	typename vector<T>::size_type index;
	typename vector<T>::const_iterator first, second;
};
vector<match_exercise17_6<Sales_data>> findBook_exercise17_6(const vector<vector<Sales_data>> &files, const string &book) {
	vector< match_exercise17_6<Sales_data>> ret;
	for (auto it = files.cbegin(); it != files.cend(); ++it) {
		auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);
		if (found.first != found.second)
			ret.push_back(match_exercise17_6<Sales_data>(it - files.cbegin(), found.first,found.second));
	}
	return ret;
}
void reportResults_exercise17_6(istream &in, ostream &os, const vector<vector<Sales_data>> &files) {
	string s;//要查找的书
	while (in >> s) {
		auto trans = findBook_exercise17_6(files, s);
		if (trans.empty()) {
			cout << s << " not found in any stores" << endl;
			continue;
		}
		for (const auto &store : trans)
			os << "store " << store.index << " sales: " << accumulate(store.first, store.second, Sales_data(s)) << endl;
	}
}

/*-------------------------------------------------------------------------------
------------------------------	Lesson 17.2		---------------------------------
---------------------------------------------------------------------------------
*/
void funcLesson17_2() {
	bitset<64> bitvec1(32);
	bitset<32> bitvec2(1010101);
	string bstr;
	cin >> bstr;
	bitset<8> bitvec3(bstr);

	cout << "bitset<64> bitvec1(32):" << bitvec1 << endl;
	cout << "bitset<32> bitvec2(1010101):" << bitvec2 << endl;
	cout << "bitset<8> bitvec3(bstr):" << bitvec3 << endl;
}

/*-------------------------------------------------------------------------------
------------------------------	Lesson 17.3		---------------------------------
---------------------------------------------------------------------------------
*/


void runLesson17() {
	//Lesson17_1_1();
	//Exercise17_1();

	//Exercise 17.3
	//ifstream ifile("Lesson11_in.txt");
	//runQueries_rewrite(ifile);

	//funcLesson17_2();



}