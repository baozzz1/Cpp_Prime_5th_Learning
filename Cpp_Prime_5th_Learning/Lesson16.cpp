#include "Lesson16.h"
using namespace std;

#include"Lesson14.h"
class Sales_data;

void runLesson16() {
	vector<int> vec = { 0,1,2,3,4,5,6,7,8,9 };
	list<string> lst = { "ling","yi","er","san","si","wu","liu","qi","ba","jiu" };
	func16_4(vec.cbegin(), vec.cend(), 9);
	func16_4(lst.cbegin(), lst.cend(), "shiyi");


}