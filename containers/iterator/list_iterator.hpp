#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "type_traits.hpp"

namespace ft {
	
    template<typename Iterator>
	class list_iterator {
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator*>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator*>::value_type			value_type;
			typedef typename iterator_traits<Iterator*>::difference_type	difference_type;
			typedef Node<iterator_type>*									pointer;
			typedef typename iterator_traits<Iterator*>::reference			reference;
		protected:
			pointer ptr;
		public:
			list_iterator() {}
			list_iterator(const list_iterator& ref) : ptr(ref.ptr) {}
			list_iterator(list_iterator* _ptr) : ptr(_ptr->ptr) {}
			list_iterator(pointer _ptr) : ptr(_ptr) {}
			virtual ~list_iterator() {}

			list_iterator& operator=(const list_iterator& it) {
				this->ptr = it.ptr;
				return *this;
			}
			
			list_iterator& operator=(list_iterator* it) { 
				ptr = it->ptr;
				return *this; 
			}
			
			reference operator*() { return ptr->val; }
			const reference operator*() const { return ptr->val; }
			
			pointer operator->() const { return ptr; }
			
			pointer get_ptr() const { return ptr; }
			
			list_iterator& operator++() {
				ptr = ptr->next;
				return *this;
			}
			
			list_iterator operator++(int) {
				list_iterator tmp(*this);
				ptr = ptr->next;
				return tmp;
			}
			
			list_iterator& operator--() {
				ptr = ptr->before;
				return *this;
			}
			
			list_iterator operator--(int) {
				list_iterator tmp(*this);
				ptr = ptr->before;
				return tmp;
			}

			pointer base() const { return ptr; }
	};

	template<typename T1, typename T2>
	bool operator== (const list_iterator<T1>& a, const list_iterator<T2>& b) {
		return a.get_ptr() == b.get_ptr();
	}

	template<typename T1, typename T2>
	bool operator!= (const list_iterator<T1>& a, const list_iterator<T2>& b) {
		return a.get_ptr() != b.get_ptr();
	}

	template<typename Iterator>
	class const_list_iterator {
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator*>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator*>::value_type			value_type;
			typedef typename iterator_traits<Iterator*>::difference_type	difference_type;
			typedef const Node<iterator_type>*								pointer;
			typedef typename iterator_traits<const Iterator*>::reference	reference;
		protected:
			pointer ptr;
		public:
			const_list_iterator() {}
			const_list_iterator(const const_list_iterator& ref) : ptr(ref.ptr) {}
			const_list_iterator(const_list_iterator* _ptr) : ptr(_ptr->ptr) {}
			const_list_iterator(pointer _ptr) : ptr(_ptr) {}
			virtual ~const_list_iterator() {}

			const_list_iterator& operator=(const const_list_iterator& it) {
				this->ptr = it.ptr;
				return *this;
			}
			
			const_list_iterator& operator=(const_list_iterator* it) { 
				ptr = it->ptr;
				return *this; 
			}
			
			reference operator*() const { return ptr->val; }
			
			pointer operator->() const { return ptr; }
			
			pointer get_ptr() const { return ptr; }
			
			const_list_iterator& operator++() {
				ptr = ptr->next;
				return *this;
			}
			
			const_list_iterator operator++(int) {
				const_list_iterator tmp(*this);
				ptr = ptr->next;
				return tmp;
			}
			
			const_list_iterator& operator--() {
				ptr = ptr->before;
				return *this;
			}
			
			const_list_iterator operator--(int) {
				const_list_iterator tmp(*this);
				ptr = ptr->before;
				return tmp;
			}

			pointer base() const { return ptr; }
	};

	template<typename T1, typename T2>
	bool operator== (const const_list_iterator<T1>& a, const const_list_iterator<T2>& b) {
		return a.get_ptr() == b.get_ptr();
	}

	template<typename T1, typename T2>
	bool operator!= (const const_list_iterator<T1>& a, const const_list_iterator<T2>& b) {
		return a.get_ptr() != b.get_ptr();
	}


	template<typename Iterator>
	class reverse_list_iterator {
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
		
		protected:
			iterator_type	current;
		
		public:
			reverse_list_iterator() {}
			reverse_list_iterator(const reverse_list_iterator<iterator_type> &ref_it) : current(ref_it.current) {}
			explicit reverse_list_iterator(const iterator_type &ref_it) : current(ref_it) {}
			reverse_list_iterator& operator=(const reverse_list_iterator& it) {
				this->current = it.current;
				return *this;
			}

			iterator_type base() const { return current; }

			reference operator*() {
				iterator_type tmp;
				iterator_type tmp2;
				tmp2 = current--;
				tmp = current;
				current = tmp2;
				return *tmp;
			}

			reverse_list_iterator& operator++() {
				current--;
				return *this;
			}

			reverse_list_iterator operator++(int) {
				reverse_list_iterator tmp(current);
				current--;
				return tmp;
			}

			reverse_list_iterator& operator--() {
				current++;
				return *this;
			}

			reverse_list_iterator operator--(int) {
				reverse_list_iterator tmp(current);
				current++;
				return tmp;
			}

			pointer operator->() const {
				return &(operator*());
			}

	};
	template <class Iterator>  
	bool operator== (const reverse_list_iterator<Iterator>& lhs, const reverse_list_iterator<Iterator>& rhs) { return lhs.base() == rhs.base(); }

	template <class Iterator>  
	bool operator!= (const reverse_list_iterator<Iterator>& lhs, const reverse_list_iterator<Iterator>& rhs) { return lhs.base() != rhs.base(); }
};

#endif