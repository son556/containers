#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"
// #include "type_traits.hpp"

namespace ft
{
	
	// random access iterator
	template<typename Iterator>
	class randomaccess_iterator {
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator*>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator*>::value_type			value_type;
			typedef typename iterator_traits<Iterator*>::difference_type	difference_type;
			typedef typename iterator_traits<Iterator*>::pointer			pointer;
			typedef typename iterator_traits<Iterator*>::reference			reference;
		protected:
			pointer ptr;
		public:
			randomaccess_iterator() {}
			randomaccess_iterator(const randomaccess_iterator<value_type>& ref) : ptr(ref.base()) {}
			randomaccess_iterator(pointer _ptr) : ptr(_ptr) {}
			virtual ~randomaccess_iterator() {}

			randomaccess_iterator& operator=(const randomaccess_iterator& it) {
				this->ptr = it.ptr;
				return *this;
			}
			
			randomaccess_iterator& operator=(randomaccess_iterator* it) { 
				ptr = it->ptr;
				return *this; 
			}
			
			reference operator*() const { return *ptr; }
			
			pointer operator->() const { return ptr; }
			
			pointer get_ptr() const { return ptr; }
			
			randomaccess_iterator& operator++() {
				ptr++;
				return *this;
			}
			
			randomaccess_iterator operator++(int) {
				randomaccess_iterator tmp(*this);
				ptr++;
				return tmp;
			}
			
			randomaccess_iterator& operator--() {
				ptr--;
				return *this;
			}
			
			randomaccess_iterator operator--(int) {
				randomaccess_iterator tmp(*this);
				ptr--;
				return tmp;
			}

			randomaccess_iterator operator-(difference_type n) {
				randomaccess_iterator tmp(*this);
				tmp.ptr -= n;
				return tmp;
			}
			
			randomaccess_iterator operator+(difference_type n) {
				randomaccess_iterator tmp(*this);
				tmp.ptr += n;
				return tmp;
			}


			pointer base() const { return ptr; }


			randomaccess_iterator& operator+=(difference_type n) {
				this->ptr += n;
				return *this;
			}
			randomaccess_iterator& operator-=(difference_type n) {
				this->ptr -= n;
				return *this;
			}
			reference operator[] (difference_type n) const { return *(ptr + n); }
	};
	template<typename T>
	randomaccess_iterator<T> operator+(typename randomaccess_iterator<T>::difference_type n, randomaccess_iterator<T> a) {
		randomaccess_iterator<T> tmp(a);
		tmp += n;
		return tmp;
	}

	template<typename T1, typename T2>
	bool operator<(const randomaccess_iterator<T1>& a, const randomaccess_iterator<T2>& b) {
		return a.get_ptr() < b.get_ptr();
	}

	template<typename T1, typename T2>
	bool operator>(const randomaccess_iterator<T1>& a, const randomaccess_iterator<T2>& b) {
		return a.get_ptr() > b.get_ptr();
	}

	template<typename T1, typename T2>
	bool operator>=(const randomaccess_iterator<T1>& a, const randomaccess_iterator<T2>& b) {
		return a.get_ptr() >= b.get_ptr();
	}

	template<typename T1, typename T2>
	bool operator<=(const randomaccess_iterator<T1>& a, const randomaccess_iterator<T2>& b) {
		return a.get_ptr() <= b.get_ptr();
	}

	template<typename T1, typename T2>
	bool operator== (const randomaccess_iterator<T1>& a, const randomaccess_iterator<T2>& b) {
		return a.get_ptr() == b.get_ptr();
	}

	template<typename T1, typename T2>
	bool operator!= (const randomaccess_iterator<T1>& a, const randomaccess_iterator<T2>& b) {
		return a.get_ptr() != b.get_ptr();
	}
}
#endif