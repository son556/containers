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

			void startNode() {
				this->_head = this->_allocNode.allocate(1);
				this->_allocNode.construct(this->_head, Node<value_type>());
				this->_head->before = this->_head;
				this->_head->next = this->_head;
				this->_tail = this->_head;
			}

			void newNode(value_type val) {
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
				this->_alloc = x._alloc;
				this->head = x.head;
			}

			list& operator= (const list& x) {
				this->_alloc = x._alloc;
				this->_allocNode = x._allocNode;
				this->_head = x._head;
				this->_tail = x._tail;
				this->_size = x._size;
			}

			iterator begin() { return iterator(this->_head); }
			
			const_iterator begin() const { return const_iterator(this->_head); }

			iterator end() { return iterator(this->_tail); }
			
			const_iterator end() const { return const_iterator(this->_tail); }

			reverse_iterator rbegin() { return reverse_iterator(this->end()); }
			
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

			reverse_iterator rend() { return reverse_iterator(this->begin()); }
			 
			const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }
    };
}

#endif


/**
 * @brief 내가 만난 문제점들...
 * 1. 리스트 템플릿의 allocator가 allocator<T>를 받는데 리스트의 멤버변수가 node*인 경우 어떻게 allocator를 사용해서
 * 할당하는지?? -> typedef typename allocator<T>::rebind<node>::other nodeAllocator로 새로 지정하여 사용.
 * 이렇게 하면 기존의 allocator의 타입선언을 바꾼 allocator를 사용하여 할당이 가능해짐.
 * 
 * const int ** -> const int ** 로 형변환이 불가능함, const int* const * 는 가능 
 */