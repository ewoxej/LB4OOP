#include<iostream>
#include"BSTRee.h"
#include<string>
//#include<algorithm>
template<typename AT,typename cmp>
void func(typename BSTree<AT,cmp>::Iterator a) {
	std::cout << *a;
}

bool predic(std::string a, std::string b) {
	return (a < b);
}
//std::less 
int main() {
	BSTree<int> a;
	a.insertKey(2);
	a.insertKey(1);
	a.insertKey(3);
	a.insertKey(23);
	a.insertKey(4);
	a.insertKey(8);
	BSTree<int> b;
	b.insertKey(5);
	b = a;
	a.directWalkDemo();
	b.directWalkDemo();
	//a.symmetricWalk(b.copyToThis);
	// TODO : тесты и isEmpty
	system("pause");
}