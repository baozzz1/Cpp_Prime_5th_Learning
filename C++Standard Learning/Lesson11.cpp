#include<map>
#include<set>
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>
#include<list>
#include<iterator>
#include<chrono>

using namespace std;

int funcE4(const string &filename) {
	//从文件读入数据
	ifstream is(filename);
	if (!is)	return 0;
	map<string, size_t>word_count;
	set<string> exclude = { "the","but","and","or","an","a","" };
	string word;
	while (is >> word) {
		//忽略标点，转换成小写
		auto iter = word.begin();
		while (iter != word.end()) {
			if ((*iter >= 'a' && *iter <= 'z') || ((*iter >= '0' && *iter <= '9'))) { ++iter; }
			else if (*iter >= 'A' && *iter <= 'Z') { *iter = tolower(*iter); ++iter; }
			else { iter = word.erase(iter); }
		}
		if (exclude.find(word) == exclude.end())
			++word_count[word];
	}
	for (const auto &w : word_count)
		cout << w.first << " occurs " << w.second << ((w.second > 1) ? " times" : " time") << endl;

	is.close();
	return 0;
}

void funcE7E8() {
	vector<string> vec1 = { "rua1","rua2" }, vec2 = { "fatAss1","fatAss2" };
	map<string, vector<string>> family = { {"Jack",vec1},
											{"Ben",vec2} };
	vector<string> multiword(10, string("fatAss"));
	set<string> word_set(multiword.cbegin(), multiword.cend());
	vector<string> word;
	for (auto iter = multiword.begin(); iter != multiword.end(); ++iter) {
		if (find(word.cbegin(), word.cend(), *iter) == word.cend())
			word.push_back(*iter++);
		else
			iter++;
	}
	cout << multiword.size() << endl;
	cout << word_set.size() << endl;
	cout << word.size() << endl;
}

class Sales_data {
public:
	Sales_data() {}
	Sales_data(const string& s) :bookNo(s) {}
	string isbn() const { return bookNo; }
private:
	string bookNo;
};

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.isbn() < rhs.isbn();
}
using compareType = bool(*)(const Sales_data &lhs, const Sales_data &rhs);
void funcE11E17E18E19() {
	multiset<Sales_data, decltype(compareIsbn)* > bookStore1(compareIsbn);
	multiset<Sales_data, compareType > bookStore2(&compareIsbn);
	auto iter_auto = bookStore1.begin();
	multiset < Sales_data, bool(*)(const Sales_data &lhs, const Sales_data &rhs)>::const_iterator iter = bookStore2.begin();

	multiset<string> c;
	vector<string> v;
	//multiset没有push_back的成员函数
	//copy(v.begin(), v.end(), inserter(c, c.end()));
	//copy(v.begin(), v.end(), back_inserter(c));
	copy(c.begin(), c.end(), inserter(v, v.end()));
	copy(c.begin(), c.end(), back_inserter(v));

	map<string, size_t>word_count;
	auto map_it_auto = word_count.cbegin();
	map<string, size_t>::const_iterator map_it = word_count.cbegin();
}

/*	Exercise11_12
	新建两个保存相同大小的string和int文件，将其读入，并成pair地保存在vector中
	*/
string random_string(const vector<char> &lib, const int &length) {
	string result = "";
	for (int i = 0; i < length; ++i) {
		int seed = rand() % 52;
		result.push_back(lib[seed]);
	}
	return result;
}
void funcE12_assist(const string &filename1, const string &filename2, const size_t &size) {
	ofstream ofs1(filename1, ostream::out);
	ofstream ofs2(filename2, ostream::out);
	ostream_iterator<string> os_it1(ofs1, " ");
	ostream_iterator<int> os_it2(ofs2, " ");

	vector<char> lib;
	for (int i = 0; i < 26; ++i) {
		lib.push_back('a' + i);
		lib.push_back('A' + i);
	}

	for (size_t i = 0; i < size; ++i) {
		*os_it1++ = random_string(lib, 5);
		*os_it2++ = rand() % 100;
	}

	ofs1.close();
	ofs2.close();
}

void funcE12(const string &input_filname1, const string &input_filname2, const size_t &size) {
	funcE12_assist(input_filname1, input_filname2, size);
	vector<pair<string, int>> result;

	ifstream ifs1(input_filname1);
	ifstream ifs2(input_filname2);
	istream_iterator<string> ifs_it1(ifs1), eof1;
	istream_iterator<int> ifs_it2(ifs2), eof2;
	//三种创建pair的方法.1
	auto started1 = chrono::high_resolution_clock::now();
	while (ifs_it1 != eof1 && ifs_it2 != eof2)
		result.push_back({ *ifs_it1++ ,*ifs_it2++ });
	auto down1 = chrono::high_resolution_clock::now();
	ifs1.close(); ifs2.close();

	ifstream ifs3(input_filname1);
	ifstream ifs4(input_filname2);
	istream_iterator<string> ifs_it3(ifs3);
	istream_iterator<int> ifs_it4(ifs4);
	//三种创建pair的方法.2
	auto started2 = chrono::high_resolution_clock::now();
	while (ifs_it3 != eof1 && ifs_it4 != eof2)
		result.push_back(pair<string, int>(*ifs_it3++, *ifs_it4++));
	auto down2 = chrono::high_resolution_clock::now();
	ifs3.close(); ifs4.close();

	ifstream ifs5(input_filname1);
	ifstream ifs6(input_filname2);
	istream_iterator<string> ifs_it5(ifs5);
	istream_iterator<int> ifs_it6(ifs6);
	//三种创建pair的方法.3
	auto started3 = chrono::high_resolution_clock::now();
	while (ifs_it5 != eof1 && ifs_it6 != eof2)
		result.push_back(make_pair(*ifs_it5++, *ifs_it6++));
	auto down3 = chrono::high_resolution_clock::now();
	ifs5.close(); ifs6.close();

	cout << "结果vector的大小为" << result.size() << ",连续创建 " << size << " 个pair，不同方法用时如下。" << endl;
	cout << "第一种：对返回值进行列表初始化的方法创建pair，用时：	";
	cout << chrono::duration_cast<chrono::milliseconds>(down1 - started1).count() << " ms." << endl;
	cout << "第二种：显式构造返回值的方法创建pair，用时：	";
	cout << chrono::duration_cast<chrono::milliseconds>(down2 - started2).count() << " ms." << endl;
	cout << "第三种：make_pair的方法创建pair，用时：	";
	cout << chrono::duration_cast<chrono::milliseconds>(down3 - started3).count() << " ms." << endl;
#if 0
	for (auto iter = result.cbegin(); iter != result.cend(); ++iter) {
		cout << "Line " << iter - result.cbegin() << "	:";
		cout << iter->first << " " << iter->second << endl;
	}
#endif // 0
}

void funcE21E22() {
	map<string, size_t> word_count;
	string word;
	while (cin >> word)
		++word_count.insert({ word,0 }).first->second;

	map<string, vector<int>> word_write;
	auto pairreturn = word_write.insert({ "newString",{1,2,3} });
	auto ff = pairreturn.first->first;	//string
	auto fs = pairreturn.first->second[2];	//vector<int>
	auto s = pairreturn.second;			//bool
	cout << ff << " " << fs << " " << s << endl;
}

map<string, string> buildMap(ifstream &map_file) {
	map<string, string> trans_map;
	string key;
	string value;
	while (map_file >> key && getline(map_file, value))
		if (value.size() > 1)
			trans_map[key] = value.substr()[1];
		else
			throw runtime_error("No rule for " + key);
	return trans_map;
}

const string &transform(const string &s, const map<string, string> &m) {
	auto map_it = m.find(s);
	if (map_it != m.cend())
		return map_it->second;
	else
		return s;
}

void word_transform(ifstream &map_file, ifstream &input) {
	auto trans_map = buildMap(map_file);
	string text;
	while (getline(input, text)) {
		istringstream stream(text);
		string word;
		bool firstword = true;
		while (stream >> word) {
			if (firstword)
				firstword = false;
			else
				cout << " ";
			cout << transform(word, trans_map);
		}
		cout << endl;
	}
}

#if Lesson11
int main() {
#if Lesson11_1
	funcE4("Lesson11_in.txt");
#endif // Lesson11_1

#if Lesson11_2
	//结果证明,make_pair的方法速度最快，相比列表初始化和显式初始化
	funcE12("Exercise11_12_string.txt", "Exercise11_12_int.txt", 2e2);
#endif // Lesson11_2


}
#endif // Lesson11
