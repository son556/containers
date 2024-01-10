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

int main()
{
	ft::vector<int> test;
	for (int i = 1; i <= 5; i++) test.push_back(i);
	ft::list<int> lstt(test.begin(), test.end());
	ft::list<int>::reverse_iterator it2 = lstt.rbegin();
	for (; it2 != lstt.rend(); ++it2) {
		std::cout << *it2 << std::endl;
	}
	std::cout << std::endl;

	// std::vector<int> test2; // rbegin ?? rend??
	// for (int i = 1; i <= 5; i++) test2.push_back(i);
	// std::list<int> lstt2(test2.begin(), test2.end());
	// std::list<int>::reverse_iterator it3 = lstt2.rbegin();
	// for (; it3 != lstt2.rend(); ++it3) {
	// 	std::cout << *it2 << std::endl;
	// }

	// std::list<int> test3(test2.begin(), test2.end());
	// std::list<int>::iterator it = test3.end();
	// std::cout << "test---------------------\n";
	// for (int i = 0; i < 20; i++) {
	// 	std::cout << *it << ' ';
	// 	if (i && i % 10 == 0) std::cout << std::endl;
	// 	it--;
	// }
	// std::cout << std::endl;

	// std::vector<int> test;
	// for (int i = 1; i <= 5; i++) test.push_back(i);
	// std::list<int> lstt(test.begin(), test.end());
	// std::list<int>::reverse_iterator it2 = lstt.rbegin();
	// for (; it2 != lstt.rend(); ++it2) {
	// 	std::cout << *it2 << std::endl;
	// }
	// std::cout << std::endl;

}