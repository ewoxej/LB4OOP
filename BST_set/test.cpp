#include<iostream>
#include"BSTRee.h"
#include"Date.h"
#include<string>
#include<cassert>
#include<algorithm>

template<typename T>
struct pr
{
template<typename T>
bool operator()(const T a, const T b)const {
	return (a < b);
}
};

void INTEGER_TEST() {
	BSTree<int> a;
	a.insertKey(2);
	a.insertKey(1);
	a.insertKey(3);
	a.insertKey(23);
	a.insertKey(4);
	a.insertKey(8);
	BSTree<int> b;
	b.insertKey(5);
	assert(b.hasKey(5));
	b = a;
	assert(!b.hasKey(5));
	assert(b.hasKey(23));
	assert(b.minimum() == 1);
	assert(b.maximum() == 23);
	b.deleteKey(23);
	assert(b.maximum() == 8);
	std::cout << "\nA tree:";
	a.directWalkDemo();
	std::cout << "\nB tree:";
	b.directWalkDemo();
	std::cout << "\n";
	for (auto i : b) {
		std::cout << i << " ";
	}
	assert(std::find(a.begin(), a.end(), 164) == a.end());
	BSTree<int>::Iterator itet = a.begin();
	++itet;
	assert((*itet) == 2);
}

void STRING_TEST() {
	BSTree<std::string,std::greater<std::string>> a;
	a.insertKey("br");
	a.insertKey("add");
	a.insertKey("cccc");
	a.insertKey("key");
	a.insertKey("feature");
	a.insertKey("open");
	BSTree<std::string,std::greater<std::string>> b;
	b.insertKey("lemon");
	assert(b.hasKey("lemon"));
	b = a;
	assert(!b.hasKey("lemon"));
	assert(b.hasKey("key"));
	assert(b.minimum() == "open");
	assert(b.maximum() == "add");
	b.deleteKey("add");
	assert(b.maximum() == "br");
	std::cout << "\nA tree:";
	a.directWalkDemo();
	std::cout << "\nB tree:";
	b.directWalkDemo();
	std::cout << "\n";
	for (auto i : b) {
		std::cout << i << " ";
	}
	assert(std::find(a.begin(), a.end(), "abrahjl4lk") == a.end());
	BSTree<std::string,std::greater<std::string>>::Iterator itet = a.begin();
	++itet;
	assert((*itet) == "key");
}

void DATE_TEST() {
	BSTree<Date, pr<Date>> a;
	Date d1(2017, 05, 02);
	Date d2(2016, 04, 03);
	Date d3(1974, 11, 12);
	Date d4(2020, 06, 02);
	a.insertKey(d1);
	a.insertKey(d2);
	a.insertKey(d3);
	a.insertKey(d4);
	assert(a.minimum() == d3);
	assert(a.maximum() == d4);
	a.deleteKey(d4);
	assert(a.maximum() == d1);
	for (auto i : a) {
		std::cout << i.GetYear() << " ";
	}
	assert(std::find(a.begin(), a.end(),Date(2010,12,12)) == a.end());
	BSTree<Date,pr<Date>>::Iterator itet = a.begin();
	++itet;
	assert((*itet) == d2);
}


//std::less 
int main() {
	INTEGER_TEST();
	STRING_TEST();
	DATE_TEST();
	system("pause");
}