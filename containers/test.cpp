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
	if (a > b) return true;
	return false;
}

template<typename T>
bool ttest(T f, int n) {
	return f(n);
}

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

int main()
{
	ft::list<double> lst;
	ft::list<double> lst2;

	for (int i = 0; i < 3; i++) {
		lst.push_back(i);
		lst2.push_back(i);
	}
	lst.push_back(200);
	lst2.push_back(1);
	lst2.push_back(13);
	cout << (lst < lst2) << endl; 

	cout << "\n\n--------------real-----------------\n\n";

	list<int> tmp;
	list<int> tmp2;

	for (int i = 0; i < 5; i++) {
		tmp.push_back(i);
		tmp2.push_back(i);
	}
	tmp.push_back(200);
	tmp2.push_back(1);
	tmp2.push_back(12);
	cout << (tmp < tmp2) << endl;
	return 0;
}