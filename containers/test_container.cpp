#include "test/test.hpp"
#include <fstream>


int main(void)
{
	test_Vector<ft::vector<int> >();
	test_Deque<ft::deque<int> >();
	test_Queue<ft::queue<int>, ft::deque<int> >();
	test_Stack<ft::stack<int>, ft::deque<int>>();
	test_List<ft::list<int>, int>();

	return (0);
}
