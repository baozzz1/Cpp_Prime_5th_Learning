#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<deque>
#include<forward_list>
using namespace std;

bool funcE9_4(vector<int>::iterator begin, vector<int>::iterator end, int target) {
	while (begin != end) {
		if (*begin == target)return true;
		++begin;
	}
	return false;
}

bool funcE9_15(vector<int> vec1, vector<int> vec2) {
	if (vec1.size() != vec2.size()) { cout << "size is not correct!" << endl; return false; }
	auto beg1 = vec1.begin(); auto end1 = vec1.end();
	auto beg2 = vec2.begin(); auto end2 = vec2.end();
	int i = 0;
	while (beg1 != end1) {
		if (*beg1 != *beg2) {
			cout << "Index at " << i << " is not correct, the first is " << *beg1 << ", the second is "
				<< *beg2 << "." << endl; return false;
		}
		++beg1; ++beg2; ++i;
	}
	cout << "RIGHT" << endl;
	return true;
}

bool funcE9_16(list<int> lst1, vector<int> vec1, list<int>::iterator iter1, vector<int>::iterator iter2) {
	if (*iter1 == *iter2)return true;
	else return false;
}


#if 0
int main() {
#if 0
	list<deque<int>> E9_2;
	vector<int> vecE9_4 = { 0,1,2,3,4,5,6,7,8,9,10 };
	auto iter1 = vecE9_4.begin(); auto iter2 = vecE9_4.end();
	int tarE9_4 = 11;
	cout << funcE9_4(iter1, iter2, tarE9_4);

	while (iter1 < iter2) { cout << "rua" << endl; ++iter1; }

	vector<int>::difference_type typeE9_7 = 0; ++typeE9_7;
	cout << vecE9_4[typeE9_7] << endl;
	list<string>::value_type typeE9_7_2;
	list<string> lst1 = { "0,1,2,3,4,5,6,7,8,9,10" };
	list<string>::iterator iter3 = (lst1.begin());
	lst1.push_back("x");

	vector<int> v1;
	const vector<int> v2 = { 0,1,2,3,4 };
	auto it1 = v1.begin(); auto  it2 = v2.begin();
	auto it3 = v1.cbegin(); auto  it4 = v2.cbegin();

	vector<double> vec1E9_13 = { 0.0,1.2,3.4 }; vector<int> vec2E9_13 = { 1,2,3 };
	list<int> target1(vec1E9_13.begin(), vec1E9_13.end());
	vector<int> target2(vec2E9_13.begin(), vec2E9_13.end());
	auto itit = target1.begin();
	while (itit != target1.end()) {
		cout << *itit << endl; ++itit;
		cout << *target2.begin() << endl;
	}

	char x1[10] = "acaavav";
	list<char*> lst1E9_14 = { x1,x1,x1,x1 };
	vector<string> vec1E9_14;
	vec1E9_14.assign(lst1E9_14.begin(), lst1E9_14.end());
	auto itit22 = vec1E9_14.begin();
	while (itit22 != vec1E9_14.end()) {
		cout << *itit22 << endl; ++itit22;
	}

	vector<int> vec1E9_15 = { 0,1,2,3,4,5,6,7,8,9,10 };
	vector<int> vec2E9_15 = { 0,1,2,3,4,5,6,7,8,9,10 };
	funcE9_15(vec1E9_15, vec2E9_15);

	list<int> lst1E9_16 = { 0,1,2 };
	vector<int> vec1E9_16 = { 3,4,1 };
	list<int>::iterator iter1E9_16 = lst1E9_16.begin();
	++iter1E9_16;
	vector<int>::iterator iter2E9_16 = vec1E9_16.begin();
	++iter2E9_16; ++iter2E9_16;
	cout << funcE9_16(lst1E9_16, vec1E9_16, iter1E9_16, iter2E9_16);

	list<int> lst222 = { 0,1,2,3,4,5,6,7,8,9,10 };
	deque<int> deq1;
	deque<int> deq2;
	for (auto beg = lst222.begin(); beg != lst222.end(); ++beg) {
		if ((*beg % 2) == 0) deq2.push_back(*beg);
		else deq1.push_back(*beg);
	}
	cout << "ÆæÊý£º" << endl;
	for (auto beg = deq1.begin(); beg != deq1.end(); ++beg) {
		cout << *beg << endl;
	}
	cout << "Å¼Êý£º" << endl;
	for (auto beg = deq2.begin(); beg != deq2.end(); ++beg) {
		cout << *beg << endl;
	}
	list<int> iv = { 0,1,2,3,4,5,6,7,8,9,10 };
	list<int>::iterator iterE9_22 = iv.begin(), mid = iv.begin();
	for (size_t i = 0; i != iv.size() / 2; ++i) {
		++mid;
	}
	int some_val = 8;
	while (iterE9_22 != iv.end()) {
		if (*iterE9_22 == some_val)
			iv.insert(iterE9_22, 2 * some_val);
		++iterE9_22;
		cout << "rua" << endl;
	}
	for (auto beg = iv.begin(); beg != iv.end(); ++beg) {
		cout << *beg << endl;
	}
	cout << iv.size();
#endif // 0


	//vector<int> vecE9_24;
	//cout << vecE9_24.at(0);
	//cout << vecE9_24.front();
	//cout <<*vecE9_24.begin();
#if 0

	list<int> lstE9_25 = { 0,1,2,3,4,5,6,7,8,9,10 };
	auto elem1 = lstE9_25.end();
	auto elem2 = lstE9_25.end();
	elem1 = lstE9_25.erase(elem1, elem2);
	for (auto beg = lstE9_25.begin(); beg != lstE9_25.end(); ++beg) {
		cout << *beg << endl;
	}

	int ia[] = { 0,1,1,2,3,5,8,13,21,55,89 };
	vector<int> iavec;
	list<int> ialst;
	for (int i = 0; i < size(ia); ++i) {
		iavec.push_back(ia[i]);
		ialst.push_back(ia[i]);
	}

	for (auto beg = ialst.begin(); beg != ialst.end();) {
		if (*beg % 2)
			beg = ialst.erase(beg);
		else
			++beg;
	}
	for (auto beg = iavec.begin(); beg != iavec.end();) {
		if (*beg % 2 == 0)
			beg = iavec.erase(beg);
		else
			++beg;
	}
	cout << "É¾³ýÅ¼ÔªËØµÄvector:" << endl;
	for (auto beg = iavec.begin(); beg != iavec.end(); ++beg) {
		cout << *beg << endl;
	}
	cout << "É¾³ýÆæÔªËØµÄlist:" << endl;
	for (auto beg = ialst.begin(); beg != ialst.end(); ++beg) {
		cout << *beg << endl;
	}
#endif // 0

#if 0
	//E9.3.6
	forward_list<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
	auto iter_pre = vi.before_begin();
	auto iter = vi.begin();
	while (iter != vi.end()) {
		if (*iter % 2) {//¸´ÖÆÆæÊý
			iter = vi.insert_after(iter, *iter);
			iter_pre = iter;
			++iter;
		}
		else //É¾³ýÅ¼Êý
			iter = vi.erase_after(iter_pre);
	}
	//cout << endl;
	for (auto beg = vi.begin(); beg != vi.end(); ++beg) {
		cout << *beg << " ";
	}
	cout << endl;

	vector<int> vii = { 0,1,2,3,4,5,6,7,8,9 };

	auto iter2 = vii.begin();
	while (iter2 != vii.end()) {
		if (*iter2 % 2)
			iter2 = vii.insert(iter2, *iter2);
		iter2++;
	}
	for (auto beg = vii.begin(); beg != vii.end(); ++beg) {
		cout << *beg << " ";
	}
	cout << endl;
#endif // 0


#if 0
	vector<int> rua1, rua2 = { 0 }, rua3(1024, 1);
	cout << rua1.capacity() << endl;
	cout << rua2.capacity() << endl;
	cout << rua3.capacity() << endl;
	rua3.resize(100);
	cout << rua3.capacity() << endl;
	typedef vector<int>::size_type size_type;
	rua1.reserve(34);
	for (size_type ix = 0; ix != 36; ++ix) {
		rua1.push_back(ix);
		cout << "vector's size is " << rua1.size() << ", and its capacity is " << rua1.capacity() << "." << endl;
	}
#endif // 0



}
#endif // 0
