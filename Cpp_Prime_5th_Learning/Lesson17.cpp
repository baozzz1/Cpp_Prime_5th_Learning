#include"Lesson17.h"
#include"Lesson14.h"	//�ṩSales_data��

using namespace std;

void Lesson17_1_1() {
	//��ʼ��tuple
	tuple<size_t, size_t, size_t> threeD;
	tuple<string, vector<double>, int, list<int>> someVal("constants", { 3.14,2.718 }, 42, { 0,1,2,3,4,5 });
	auto item = make_tuple("0-999-78345-X", 3, 20.00);

	//������ʹ�ã���ֵ��ֵ
	auto book = get<0>(item);
	auto cnt = get<1>(item);
	auto price = get<2>(item) / cnt;
	get<2>(item) *= 0.8;

	// value �� type ��ʹ��
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

class Sales_data;
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs);
//matches��������Ա��һ�ҵ������������ָ�����vector��Ԫ�صĵ�����
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
	string s;//Ҫ���ҵ���
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

void runLesson17() {
	Lesson17_1_1();
	Exercise17_1();

	//Exercise 17.3
	ifstream ifile("Lesson11_in.txt");
	runQueries_rewrite(ifile);

}