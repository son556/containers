#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "../vector/vector.hpp"
#include <queue>
namespace ft {

	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	template <class T> 
	struct less : binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const {return x < y;}
	};

	template <class T> 
	struct greater : binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const {return x > y;}
	};

    template <class T, class Container = ft::vector<T>,  class Compare = ft::less<typename Container::value_type> >
    class priority_queue {
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;
        
		protected:
            container_type  cntr;
            Compare         cmp;
        
		public:
            explicit priority_queue (const Compare& comp = Compare(), const Container& _ctnr = Container()) {
				this->cmp = comp;
				typename Container::const_iterator it = _ctnr.begin();
				for (; it != _ctnr.end(); it++) {
					this->cntr.push_back(*it);
					heapsortPush();
				}
			}

            template <class InputIterator>
            priority_queue (InputIterator first, InputIterator last, const Compare& comp = Compare(), const Container& ctnr = Container())
            {
                this->cmp = comp;
                for (typename container_type::iterator it = cntr.begin(); it != cntr.end(); it++) {
                    cntr.push_back(*it);
					heapsortPush();
                }
            }

			void heapsortPush() {
				int n = cntr.size() - 1;
				int next;
				value_type tmp;

				if (n - 1 < 0) return;
				next = (n - 1) / 2;
				while (1) {
					if (cmp(cntr[n], cntr[next]) == false) {
						tmp = cntr[n];
						cntr[n] = cntr[next];
						cntr[next] = tmp;
					}
					n = next;
					if (n - 1 < 0) break;
					next = (n - 1) / 2;
				}
			}

			void heapsortPop(size_type idx) {
				size_type n = cntr.size();
				if (idx >= n) return ;
				value_type tmp;
				size_type next;
				next = 2 * idx + 1;
				if (next < n && cmp(cntr[idx], cntr[next])) {
					tmp = cntr[idx];
					cntr[idx] = cntr[next];
					cntr[next] = tmp;
					heapsortPop(next);
				}
				next = 2 * idx + 2;
				if (next < n && cmp(cntr[idx], cntr[next])) {
					tmp = cntr[idx];
					cntr[idx] = cntr[next];
					cntr[next] = tmp;
					heapsortPop(next);
				}
			}

			bool empty() const { return cntr.empty(); }
			
			size_type size() const { return cntr.size(); }

			const value_type& top() const { return cntr.front(); }

			void push (const value_type& val) {
				cntr.push_back(val);
				heapsortPush();
			}

			void pop() {
				size_type n = cntr.size() - 1;
				cntr[0] = cntr[n];
				cntr.pop_back();
				heapsortPop(0);
			}

			void swap( priority_queue& other ) {
				container_type tmp = cntr;
				Compare tcmp = cmp;
				cntr = other.cntr;
				cmp = cntr.cmp;
				other.cntr = cntr;
				other.cmp = tcmp;
			}
    };
}
#endif