
#ifndef LIST_HPP
#define LIST_HPP

#include "../iterator/list_iterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "../iterator/type_traits.hpp"

namespace ft {

    template <typename T, class Alloc = std::allocator<T> >
    class list {
        public:
            typedef T														value_type;
            typedef Alloc													allocator_type;
            typedef typename allocator_type::reference          			reference;
            typedef typename allocator_type::const_reference    			const_reference;
            typedef typename allocator_type::pointer            			pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef list_iterator<value_type>								iterator;
			typedef const_list_iterator<value_type>							const_iterator;
			typedef reverse_list_iterator<iterator>							reverse_iterator;
			typedef reverse_list_iterator<const_iterator>					const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
			typedef difference_type											size_type;
		private:
			typedef typename allocator_type::template rebind<Node<T> >::other node_allocator;
			allocator_type				_alloc;
			node_allocator				_allocNode;
			Node<value_type>*			_head;
			Node<value_type>*			_tail;
			size_type					_size;
			const size_type				_max_size = 768614336404564650;

			void startNode() {
				this->_head = this->_allocNode.allocate(1);
				this->_allocNode.construct(this->_head, Node<value_type>());
				this->_head->before = this->_head;
				this->_head->next = this->_head;
				this->_tail = this->_head;
				this->_size = 0;
			}

			void newNode(value_type val) {
				if (this->_size + 1 > this->_max_size)
					throw std::out_of_range("ft::list");
				this->_tail->next = this->_allocNode.allocate(1);
				this->_allocNode.construct(this->_tail->next, Node<value_type>(val));
				if (this->_size == 0)
					this->_tail->before = this->_tail->next;
				this->_tail->val = val;
				this->_tail->next->before = this->_tail;
				this->_tail = this->_tail->next;
				this->_tail->val = val;
				this->_tail->next = this->_head;
				this->_head->before = this->_tail;
				this->_size++;
			}

		public:
			explicit list(const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
				startNode();
			}
			
			explicit list (size_type n, const value_type& val = value_type(), \
				const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
				startNode();
				while (n--)
					newNode(val);
			}

			template <class InputIterator>
			list (InputIterator first, InputIterator last, \
					const allocator_type& alloc = allocator_type(), \
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				startNode();
				while (first != last) {
					newNode(*first);
					first++;
				}
			}

			list (const list& x) {
				const_iterator it = x.begin();
				startNode();
				for (size_t i = 0; i < x.size(); i++) {
					newNode(*it);
					it++;
				}
			}

			~list() {
				Node<value_type>* tmp = this->_head;
				Node<value_type>* ntmp;
				for (size_type i = 0; i <= this->_size; i++) {
					ntmp = tmp->next;
					this->_allocNode.destroy(tmp);
					this->_allocNode.deallocate(tmp, 1);
					tmp = ntmp;
				}
				this->_size = 0;
			}

			list& operator= (const list& x) {
				const_iterator it = x.begin();
				startNode();
				for (size_t i = 0; i < x.size(); i++) {
					newNode(*it);
					it++;
				}
			}

			iterator begin() { return iterator(this->_head); }
			
			const_iterator begin() const { return const_iterator(this->_head); }

			iterator end() { return iterator(this->_tail); }
			
			const_iterator end() const { return const_iterator(this->_tail); }

			reverse_iterator rbegin() { return reverse_iterator(this->end()); }
			
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

			reverse_iterator rend() { return reverse_iterator(this->begin()); }
			 
			const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

			bool empty() const {
				if (this->_size == 0) return true;
				return false;
			}

			size_type size() const { return this->_size; }

			size_type max_size() const { return this->_max_size; }

			reference front() { return this->_head->val; }
			
			const_reference front() const { return this->_head->val; }

			reference back() { return this->_tail->before->val; }
			
			const_reference back() const { return this->_tail->before->val; }

			template <class InputIterator>  
			void assign (InputIterator first, InputIterator last, \
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				this->~list();
				startNode();
				while (first != last) {
					newNode(*first);
					first++;
				}
			}

			void assign (size_type n, const value_type& val) {
				this->~list();
				startNode();
				while (n--)
					newNode(val);
			}

			void push_front (const value_type& val) {
				if (this->_size + 1 > this->_max_size)
					throw std::out_of_range("ft::list");
				Node<value_type>* tmp = this->_allocNode.allocate(1);
				this->_allocNode.construct(tmp, Node<value_type>(val));
				tmp->next = this->_head;
				tmp->before = this->_tail;
				this->_head->before = tmp;
				this->_head = tmp;
				this->_tail->next = this->_head;
				if (this->_size == 0)
					this->_tail->val = this->_head->val;
				this->_size++;
			}

			void pop_front() {
				Node<value_type>* tmp = this->_head;
				this->_head = this->_head->next;
				this->_head->before = this->_tail;
				this->_tail->next = this->_head;
				this->_allocNode.destroy(tmp);
				this->_allocNode.deallocate(tmp, 1);
				this->_size--;
				if (this->_size == 0) 
					this->_tail->val = 0;
			}

			void push_back (const value_type& val) {
				if (this->_size + 1 > this->_max_size)
					throw std::out_of_range("ft::list");
				this->_tail->val = val;
				this->_tail->next = this->_allocNode.allocate(1);
				this->_allocNode.construct(this->_tail->next, Node<value_type>(val));
				this->_tail->next->before = this->_tail;
				this->_tail = this->_tail->next;
				this->_tail->next = this->_head;
				this->_head->before = this->_tail;
				this->_size++;
			}

			void pop_back() {
				Node<value_type>* tmp = this->_tail;
				this->_tail = this->_tail->before;
				this->_tail->val = this->_tail->before->val;
				this->_tail->next = this->_head;
				this->_head->before = this->_tail;
				this->_allocNode.destroy(tmp);
				this->_allocNode.deallocate(tmp, 1);
				this->_size--;
			}

			iterator insert (iterator position, const value_type& val) {
				if (this->_size + 1 > this->_max_size)
					throw std::out_of_range("ft::list");
				Node<value_type> *tmp;
				tmp = this->_allocNode.allocate(1);
				this->_allocNode.construct(tmp, Node<value_type>(val));
				tmp->next = position.get_ptr();
				tmp->before = position.get_ptr()->before;
				position.get_ptr()->before->next = tmp;
				position.get_ptr()->before = tmp;
				if (position.get_ptr() == this->_head) 
					this->_head = tmp;
				this->_size++;
				return iterator(tmp);
			}

			void insert (iterator position, size_type n, const value_type& val) {
				while (n--)
				{
					insert(position, val);
					position--;
				}
			}

			template <class InputIterator> 
			void insert (iterator position, InputIterator first, InputIterator last, \
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				while (first != last) {
					insert(position, *first);
					first++;
				}
			}

			iterator erase (iterator position) {
				if (position == this->end())
					throw std::out_of_range("ft::list segfault");
				Node<value_type> *tmp = position.get_ptr();
				Node<value_type> *ntmp = tmp->next;
				tmp->next->before = tmp->before;
				tmp->before->next = ntmp;
				if (tmp == this->begin().get_ptr())
					this->_head = ntmp;
				else if (tmp == this->end().get_ptr() - 1)
					this->_tail->val = tmp->before->val;
				this->_allocNode.destroy(tmp);
				this->_allocNode.deallocate(tmp, 1);
				this->_size--;
				return iterator(ntmp);
			}
			
			iterator erase (iterator first, iterator last) {
				iterator it, res;
				while (first != last) {
					it = iterator(first.get_ptr()->next);
					res = erase(first);
					first = it;
				}
				return res;
			}

			void swap (list& x) {
				Node<value_type>* tmp_head = this->_head;
				Node<value_type>* tmp_tail = this->_tail;
				size_type tmp_size = this->_size;
				this->_size = x._size;
				this->_head = x._head;
				this->_tail = x._tail;
				x._head = tmp_head;
				x._tail = tmp_tail;
				x._size = tmp_size;
			}

			void resize (size_type n, value_type val = value_type()) {
				if (n > this->_size) {
					while (n != this->_size)
						push_back(val);
				}
				else if (n < this->_size) {
					iterator it;
					while (n != this->_size) {
						it = this->end();
						it--;
						erase(it);
					}
				}
			}

			void clear() {
				iterator it(this->_head);
				iterator nit;
				for (size_type i = 0; i < this->_size; i++) {
					nit = iterator(it.get_ptr()->next);
					this->_allocNode.destroy(it.get_ptr());
					this->_allocNode.deallocate(it.get_ptr(), 1);
					it = nit;
				}
				this->_head = this->_tail;
				this->_head->before = this->_head;
				this->_head->next = this->_head;
				this->_head->val = 0;
				this->_size = 0;
			}

			void splice (iterator position, list& x) {
				iterator it = position;
				iterator itt = x.end();
				itt--;
				for (size_type i = 0; i < x.size(); i++) {
					it = this->insert(it, *itt);
					itt--;
				}
				x.clear();
			}
	
			void splice (iterator position, list& x, iterator i) {
				this->insert(position, *i);
				x.erase(i);
			}
	
			void splice (iterator position, list& x, iterator first, iterator last);
    };
}

#endif


/**
 * @brief 내가 만난 문제점들...
 * 1. 리스트 템플릿의 allocator가 allocator<T>를 받는데 리스트의 멤버변수가 node*인 경우 어떻게 allocator를 사용해서
 * 할당하는지?? -> typedef typename allocator<T>::rebind<node>::other nodeAllocator로 새로 지정하여 사용.
 * 이렇게 하면 기존의 allocator의 타입선언을 바꾼 allocator를 사용하여 할당이 가능해짐.
 * 
 * const int ** -> const int ** 로 형변환이 불가능함, const int* const * 는 가능 -> 정확히 설명 가능할 때 까지 공부
 */