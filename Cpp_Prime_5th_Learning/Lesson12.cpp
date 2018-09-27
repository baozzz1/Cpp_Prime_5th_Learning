#include"Lesson12.h"

using namespace std;

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

void StrBlob::check(size_type i, const string &msg) const {
	if (i >= data->size())
		throw out_of_range(msg);
}

string& StrBlob::front() {
	check(0, "front on empty StrBlob");
	return data->front();
}
const string& StrBlob::front() const {
	check(0, "front on empty StrBlob");
	return data->front();
}
string& StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}
const string& StrBlob::back() const {
	check(0, "front on empty StrBlob");
	return data->back();
}
void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

vector<int>* make_new_pvec_funcE6() {
	return  new vector<int>();
}
void read_funcE6(vector<int>* pvec) {
	int word;
	while (cin >> word)
		pvec->push_back(word);
}
void print_funcE6(const vector<int>* pvec) {
	for (auto iter = pvec->cbegin(); iter != pvec->cend(); ++iter)
		cout << *iter << " ";
	cout << endl;
}

shared_ptr<vector<int>> make_new_spvec_funcE7() {
	return make_shared<vector<int>>();
}
void read_funcE7(const shared_ptr<vector<int>> &spvec) {
	int word;
	while (cin >> word)
		spvec->push_back(word);
}
void print_funcE7(const shared_ptr<vector<int>> &spvec) {
	for (auto iter = spvec->cbegin(); iter != spvec->cend(); ++iter)
		cout << *iter << " ";
	cout << endl;
}

void process(shared_ptr<int> ptr) {
	cout << *ptr << endl;
}

TextQuery::TextQuery(ifstream &is) :file(new vector<string>) {
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
QueryResult TextQuery::query(const string &sought)const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.cend())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}
extern string make_plural(size_t ctr, const string &word, const string &ending) { return (ctr > 1) ? word + ending : word; }
ostream &print(ostream &os, const QueryResult &qr) {
	os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << endl;
	for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ") " << *(qr.files->begin() + num) << endl;
	return os;
}
void runQueries(ifstream &infile) {
	TextQuery tq(infile);
	while (true) {
		cout << "enter word to look for, or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q")break;
		print(cout, tq.query(s)) << endl;
	}
}

#if Lesson12
int main() {
#if Exercise12_6
	auto pvec = make_new_pvec_funcE6();
	read_funcE6(pvec);
	print_funcE6(pvec);
	delete(pvec);
#endif // Exercise12_6

#if Exericse12_7
	auto spvec = make_new_spvec_funcE7();
	read_funcE7(spvec);
	print_funcE7(spvec);
#endif // Exericse12_7

#if Lesson12_2
	typedef char arrChar[12];
	char *p = new arrChar;
	const char* s1 = "hello";
	const char* s2 = ", world";
	for (size_t i = 0; i != 12; ++i)
		*(p + i) = i >= 5 ? s2[i - 5] : s1[i];
	for (size_t i = 0; i != 12; ++i)
		cout << *(p + i);
	cout << endl;
#endif // Lesson12_2

	//Lesson 13
	//ifstream ifile("Lesson11_in.txt");
	//runQueries(ifile);


}
#endif // Lesson12

