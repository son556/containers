#include <iostream>
#include <ctime>
#include <fstream>

#include "./vector/vector.hpp"
#include "./deque/deque.hpp"
#include "./priority_queue/priority_queue.hpp"
#include "./stack/stack.hpp"
#include "./list/list.hpp"

#include <queue>
#include <deque>
#include <algorithm>
#include <stack>
#include <list>

template<typename Iterator>
void display(Iterator iter, int n) {
	for (int i = 0; i < n; i++) {
		std::cout << *iter << ' ';
		iter++;
	}
	std::cout << std::endl;
}

template<typename Iterator>
void reverseDisplay(Iterator iter, int n) {
	for (int i = 0; i < n; i++) {
		std::cout << *iter << ' ';
		iter--;
	}
	std::cout << std::endl;
}


using namespace std;

bool helloTest(int a, int b) {
	if (a > b) return false;
	return true;
}

template<typename T>
bool ttest(T f, int n) {
	return f(n);
}

int main()
{
	ft::list<int> lst;
	for (int i = 0; i < 5; i++) {
		lst.push_back(i + 1);
		lst.push_back(i + 1);
	}
	lst.push_back(1);
	lst.unique(helloTest);
	cout << lst.size() << endl;
	display(lst.begin(), lst.size());

	cout << "\n\n--------------real-----------------\n\n";

	list<int> tlst;
	for (int i = 0; i < 5; i++) {
		tlst.push_back(i + 1);
		tlst.push_back(i + 1);
	}
	tlst.push_back(1);
	tlst.unique(helloTest);
	cout << tlst.size() << endl;
	display(tlst.begin(), tlst.size());

	return 0;
}