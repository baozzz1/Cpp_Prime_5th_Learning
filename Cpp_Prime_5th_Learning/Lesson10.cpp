#include <iostream>
#include<algorithm>
#include<vector>
#include<list>
#include<string>
#include<numeric>
#include<functional>
#include<iterator>
#include<fstream>

using namespace std;
using namespace std::placeholders;

vector<int> VEC = { 1,2,3,4,5,6,7,8,9,10 };

class Sales_data {
public:
	Sales_data() {}
	Sales_data(const string& s) :bookNo(s) {}
	string isbn() const { return bookNo; }
private:
	string bookNo;
};

void func10_1(const vector<int>& vec, int target) {
	int result = count(vec.begin(), vec.end(), target);
	cout << "result is " << result << endl;
}
void func10_2(const list<string>& vec, string target) {
	int result = count(vec.begin(), vec.end(), target);
	cout << "result is " << result << endl;
}

void print(vector<string> vec) {
	for (auto iter = vec.begin(); iter != vec.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
}
void print(vector<const char*> vec) {
	for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
		cout << *iter << " ";
	}
}
void print(vector<int> vec) {
	for (auto iter = vec.begin(); iter != vec.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
}
void print(list<int> lst) {
	for (auto iter = lst.begin(); iter != lst.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
}
void print(list<string> lst) {
	for (auto iter = lst.begin(); iter != lst.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
}

//消除重复单词
void elimDups(vector<string> &words) {
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
}

bool compareISBN(const Sales_data& item1, const Sales_data& item2) {
	return item1.isbn() < item2.isbn();
}

bool func13(const string &str) { return str.size() >= 5; }

//E10_16
extern string make_plural(size_t ctr, const string &word, const string &ending) { return (ctr > 1) ? word + ending : word; }
void biggies(vector<string> &words, vector<string>::size_type sz) {
	elimDups(words);
	stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {return a.size() < b.size(); });
	auto wc = find_if(words.begin(), words.end(), [sz](const string &a) {return a.size() >= sz; });
	auto count = words.end() - wc;
	cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer " << endl;
	for_each(wc, words.end(), [](const string &s) {cout << s << " "; }); cout << endl;
}

//E10_18
void biggiesE18(vector<string> &words, vector<string>::size_type sz) {
	elimDups(words);
	stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {return a.size() < b.size(); });
	auto wc = partition(words.begin(), words.end(), [sz](const string &a) {return a.size() >= sz; });
	for_each(words.begin(), wc, [](const string &s) {cout << s << " "; }); cout << endl;
}
//E10_19
void biggiesE19(vector<string> &words, vector<string>::size_type sz) {
	elimDups(words);
	stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {return a.size() < b.size(); });
	auto wc = stable_partition(words.begin(), words.end(), [sz](const string &a) {return a.size() >= sz; });
	for_each(words.begin(), wc, [](const string &s) {cout << s << " "; }); cout << endl;
}
//E10_20
void biggiesE20(vector<string> &words, vector<string>::size_type sz) {
	elimDups(words);
	stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {return a.size() < b.size(); });
	auto count = count_if(words.begin(), words.end(), [sz](const string &s) {return s.size() >= sz; });
	cout << count << endl;
}
//E10_22
bool check_size(const string &s, string::size_type sz) {
	return s.size() >= sz;
}
void biggiesE22(vector<string> &words, vector<string>::size_type sz) {
	elimDups(words);
	stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {return a.size() < b.size(); });
	auto count = count_if(words.begin(), words.end(),bind(check_size,_1,sz));
	cout << count << endl;
}

//E10_24
bool isShorter(int &a,int &b) {
	return a < b;
}
void biggiesE24(vector<int> vec, const string &str) {
	sort(vec.begin(), vec.end(), bind(isShorter,_2,_1));
	auto find = find_if(vec.begin(), vec.end(), bind(check_size, str, _1));
	cout << *find << endl;
}

//E10_25
ostream &printE25(ostream &os, const string &s, char c) { return os << s << c; }
bool compare(const string &s1, const string &s2) { return s1.size() < s2.size(); }
void biggiesE25(vector<string> &words, vector<string>::size_type sz) {
	elimDups(words);
	stable_sort(words.begin(), words.end(), bind(compare,_1,_2));
	auto wc = partition(words.begin(), words.end(), bind(check_size,_1,sz));
	for_each(words.begin(), wc, bind(printE25, ref(cout), _1, ' '));
}

//E10_27
list<string> elimDupsE27(vector<string> &words) {
	list<string> tarLst;
	sort(words.begin(), words.end());
	auto end_unique = unique_copy(words.begin(), words.end(), inserter(tarLst,tarLst.begin()));
	return tarLst;
}

//E10_33 在文件中生成随机整数0~100
void int2file(const string &filename, const int &size) {
	ofstream ofs(filename, ostream::out);
	ostream_iterator<int> os_it(ofs, " ");
	for (int i = 0; i < size; ++i) {
		*os_it++ = rand() % 100;
	}
	ofs.close();
}
//目的函数
void funcE33(const string &input_filname, const string &output_filname1, const string &output_filname2) {
	ifstream ifs(input_filname);
	istream_iterator<int> ifs_it(ifs), eof;
	ofstream ofs1(output_filname1, ostream::out);
	ofstream ofs2(output_filname2, ostream::out);
	ostream_iterator<int> os_it1(ofs1, " "), os_it2(ofs2, "\n");
	while (ifs_it != eof)
		if (*ifs_it % 2)	*os_it1++ = *ifs_it++;
		else				*os_it2++ = *ifs_it++;
	ofs1.close();
	ofs2.close();
}



#if Lesson10
int main() {
#if E10_1
	vector<int> vec;
	vec = VEC;
	func10_1(vec, 10);
#endif // E10_1

#if E10_2
	list<string> lst; string str;
	while (cin >> str) { lst.push_back(str); }
	func10_2(lst, "abcd");
#endif // E10_2

#if E10_3
	vector<int> vec10_3 = { 1,2,3,4,5,6,7,8,9,0,11,12,13 };
	int sum = accumulate(vec10_3.cbegin(), vec10_3.cend(), 0);
	cout << sum << endl;
#endif // E10_3

#if E10_4
	vector<double> vec10_3 = { 1.1,2.2,3.3,4.4,5.5,6.7,7,8,9,0,11,12,13 };
	double sum1 = accumulate(vec10_3.cbegin(), vec10_3.cend(), 0);
	double sum2 = accumulate(vec10_3.cbegin(), vec10_3.cend(), 0.0);
	cout << sum1 << endl << sum2 << endl;
#endif // E10_4


#if E10_5
	vector<const char*> rua1 = { "12141425" ,"2","3" };
	vector<const char*> rua2;
	rua2 = { "12141425" ,"2","3" };
	print(rua2);
	if ("1" == "1")
		//if (equal(rua1.cbegin(), rua1.cend(), rua2.cbegin()))
		cout << endl << "?????" << endl;
#endif // E10_5

#if E10_6
	vector<int> ivec(10, 1);
	print(ivec); cout << endl;
	fill_n(ivec.begin(), ivec.size(), 0);
	print(ivec); cout << endl;
#endif // E10_6

#if E10_9
	vector<string> vec = { "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	elimDups(vec);
	print(vec);
#endif // E10_9


#if E10_13
	vector<string> vec = { "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	auto end_part = partition(vec.begin(), vec.end(), func13);
	for (auto iter = vec.begin(); iter != end_part; ++iter)
		cout << *iter << endl;
#endif // E10_13

#if Lesson10_3
	vector<string> vec = { "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	[](int a, int b) {return a + b; };
	int a; [a](int b) {return a + b; };
	biggies(vec, 4);

	biggiesE18(vec, 4);
	biggiesE19(vec, 4);
	biggiesE20(vec, 6);

#if E10_21
	//E21
	int x;
	[x]()mutable->bool {if (x = 0)return true; while (x != 0) { --x; }return false; };
#endif // E10_21

	biggiesE22(vec, 5);

	vector<int> vecInt = { 0,1,2,3,4,5,6,7,8,9,10 };
	biggiesE24(vecInt, "string");

	//E10_25
	biggiesE25(vec, 5);
#endif // Lesson10_3

#if Lesson10_4_1
	list<int> lst = { 1,2,3,4 }, lst2, lst3;
	copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
	print(lst2);
	copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));
	print(lst3);
#endif // Lesson10_4_1

#if E10_27
	vector<string> vec = { "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	list<string> tarLst = elimDupsE27(vec);
	print(tarLst);
#endif // E10_27

#if E10_28
	vector<int> vec = { 1,2,3,4,5,6,7,8,9 };
	vector<int> vec1, vec3;
	list<int> lst2;
	copy(vec.begin(), vec.end(), inserter(vec1, vec1.begin()));
	copy(vec.begin(), vec.end(), front_inserter(lst2));
	copy(vec.begin(), vec.end(), back_inserter(vec3));
	print(vec1);
	print(lst2);
	print(vec3);
#endif // E10_28

#if E10_29
	ifstream ifile("1");
	istream_iterator<string> int_it(ifile);
	istream_iterator<string> eof;
	vector<string> vec;
	while (int_it != eof)
		vec.push_back(*int_it++);
	print(vec);
#endif // E10_29


#if E10_30
	vector<int> vecInt, tarVec;
	istream_iterator<int> ini_it(cin), eof;
	ostream_iterator<int> os_it(cout, " ");
	while (ini_it != eof)
		vecInt.push_back(*ini_it++);
	sort(vecInt.begin(), vecInt.end());
	auto end_unique = unique_copy(vecInt.begin(), vecInt.end(), inserter(tarVec, tarVec.begin()));
	copy(tarVec.begin(), tarVec.end(), os_it);
	cout << endl;
#endif // E10_30

#if E10_33
	int2file("in.txt", 50);
	funcE33("in.txt", "out1.txt", "out2.txt");
#endif // E10_33

	//10.34
	vector<int> vec = { 1,2,3,4,5,6,7,8,9 };
	for (reverse_iterator<vector<int>::const_iterator> r_iter = vec.crbegin(); r_iter != vec.crend(); ++r_iter)
		cout << *r_iter << " ";
	cout << endl;
	//10.35
	auto r_iter = vec.cend();
	for (--r_iter; r_iter != vec.cbegin(); --r_iter) {
		cout << *r_iter << " ";
	}
	cout << *r_iter << endl;
	//10.36
	list<int> lst;
	for (int i = 0; i < 50; i++) {
		lst.push_back(rand() % 10);
		cout << *lst.crbegin() << " ";
	}
	cout << endl;
	auto rzero = find(lst.crbegin(), lst.crend(), 0);
	for (auto iter = rzero.base(); iter != lst.cend(); ++iter)
		cout << *iter << " ";
	cout << endl;
}
#endif // Lesson10
