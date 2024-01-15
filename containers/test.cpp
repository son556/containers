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


int main()
{
	ft::list<int> lst;
	for (int i = 1; i <= 10; i++) lst.push_back(i);

	lst.resize(5);
	ft::list<int> lstt;
	for (int i = 1; i < 6; i++) lstt.push_back(-i);
	ft::list<int>::iterator it = lst.begin();
	it++;
	lst.splice(it, lstt);
	lstt.splice (lstt.begin(), lst, it);
	display(lst.begin(), lst.size());
	display(lstt.begin(), 3);
	std::cout << *it << std::endl;

	std::cout << "\n\nreal-----------------------------\n\n";

	std::list<int> mylist;

	// set some initial content:
	for (int i=1; i<10; ++i) mylist.push_back(i);

	mylist.resize(5);
	std::list<int> mylist2;
	for (int i = 1; i < 6; i++) mylist2.push_back(-i);
	std::list<int>::iterator itest = mylist.begin();
	itest++;
	mylist.splice(itest, mylist);
	mylist2.splice(mylist2.begin(), mylist, itest);
	display(mylist.begin(), mylist.size());
	display(mylist2.begin(), 3);
	std::cout << *(++itest) << std::endl;

	return 0;
}