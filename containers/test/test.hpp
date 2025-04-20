/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:27:56 by ncolomer          #+#    #+#             */
/*   Updated: 2023/12/14 20:26:46 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

# ifdef def_test_full
#  define FULL
# endif

# include <iostream>
# include "Number.hpp"
# include "../vector/vector.hpp"
# include "../stack/stack.hpp"
# include "../queue/queue.hpp"
# include "../deque/deque.hpp"
# include "../list/list.hpp"

# include <vector>
# include <list>
# include <stack>
# include <queue>
# include <map>
# include <set>
# include <deque>
# include <cassert>

template<typename Container>
void display_container(std::string const &header, Container const &ctn)
{
	typename Container::const_iterator it = ctn.begin();
	typename Container::const_iterator ite = ctn.end();
	std::cout << header;
	if (it == ite)
		std::cout << " empty !";
	std::cout << '\n';
	while (it != ite)
	{
		std::cout << *it;
		if (++it == ite)
			std::cout << '\n';
		else
			std::cout <<  ", ";
	}
}

# include "vector_test.hpp"
# include "list_test.hpp"
# include "stack_test.hpp"
# include "queue_test.hpp"
# include "deque_test.hpp"
// # include "map_test.hpp"
// # include "set_test.hpp"
// # include "multimap_test.hpp"
// # include "multiset_test.hpp"

#endif
