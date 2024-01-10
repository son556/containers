#ifndef DEQUE_ITERATOR_HPP
#define DEQUE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
    template<typename Iterator>
	class deque_iterator {
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator*>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator*>::value_type			value_type;
			typedef typename iterator_traits<Iterator*>::difference_type	difference_type;
			typedef typename iterator_traits<Iterator*>::pointer			pointer;
			typedef typename iterator_traits<Iterator*>::reference			reference;
			typedef difference_type											size_type;
		
		protected:
			pointer const*				_current;
			pointer						_ptr;
		
		public:
			deque_iterator() : _current(0), _ptr(0) {}


			deque_iterator(const deque_iterator &ref) 
			: _current(ref.const_current()), _ptr(ref.const_ptr()) {}

			deque_iterator(pointer const* current, pointer ptr) : _current(current), _ptr(ptr) {}

			virtual ~deque_iterator() {}

			deque_iterator& operator=(const deque_iterator& it) {
				this->_current = it.const_current();
				this->_ptr = it.const_ptr();
				return *this;
			}
			
			deque_iterator& operator=(deque_iterator* it) { 
                this->_current = it->const_current();
				this->_ptr = it->const_ptr();
				return *this; 
			}
			
			reference operator*() const { return *_ptr; }
			
			pointer operator->() const { return _ptr; }

			pointer* &get_current() {return _current;}

			pointer &get_ptr() { return _ptr; }
			
			deque_iterator& operator++() {
				if (_ptr == *_current + 4) {
					this->_current++;
					_ptr = *(this->_current);
				}
				else _ptr++;
				return *this;
			}
			
			deque_iterator operator++(int) {
				deque_iterator tmp(*this);
				if (_ptr == *_current + 4) {
					this->_current++;
					_ptr = *(this->_current);
				}
				else _ptr++;
				return tmp;
			}
			
			deque_iterator& operator--() {
				if (this->_ptr == *(this->_current)) {
					this->_current--;
					this->_ptr = *(this->_current) + 4;
				}
				else this->_ptr--;
				return *this;
			}
			
			deque_iterator operator--(int) {
				deque_iterator tmp(*this);
				if (this->_ptr == *(this->_current)) {
					this->_current--;
					this->_ptr = *(this->_current) + 4;
				}
				else this->_ptr--;
				return tmp;
			}

			deque_iterator operator-(difference_type n) const {
				deque_iterator tmp(*this);
				size_type row = n / 5;
				size_type col = n % 5;
				size_type interval = tmp._ptr - *(tmp._current);
				tmp._current -= row;
				if (col  > interval) {
					col -= interval;
					tmp._current--;
					tmp._ptr = *(tmp._current) + 4;
					tmp._ptr -= col - 1;
				}
				else {
					tmp._ptr = *(tmp._current) + interval;
					tmp._ptr -= col;
				}
				return tmp;
			}
			
			deque_iterator operator+(difference_type n) const {
				deque_iterator tmp(*this);
				size_type row = n / 5;
				size_type col = n % 5;

				size_type interval = *(tmp._current) + 4 - tmp._ptr;
				tmp._current += row;
				if (col > interval) {
					tmp._current++;
					col -= interval + 1;
					tmp._ptr = *(tmp._current) + col;
				}
				else {
					tmp._ptr = *(tmp._current) + 4 - interval;
					tmp._ptr += col;
				}
				return tmp;
			}

			pointer const* const_current() const {return _current;}

			pointer const_ptr() const { return _ptr; }

			deque_iterator& operator+=(difference_type n) {
				size_type row = n / 5;
				size_type col = n % 5;
				size_type interval = *(this->_current) + 4 - this->_ptr;
				this->_current += row;
				if (col > interval) {
					this->_current++;
					col -= interval + 1;
					this->_ptr = *(this->_current) + col;
				}
				else {
					this->_ptr = *(this->_current) + 4 - interval;
					this->_ptr += col;
				}
				return *this;
			}

			deque_iterator& operator-=(difference_type n) {
				size_type row = n / 5;
				size_type col = n % 5;
				size_type interval = this->_ptr - *(this->_current);
				this->_current -= row;
				if (col  > interval) {
					col -= interval;
					this->_current--;
					this->_ptr = *(this->_current) + 4;
					this->_ptr -= col - 1;
				}
				else {
					this->_ptr = *(this->_current) + interval;
					this->_ptr -= col;
				}
				return *this;
			}

			reference operator[] (difference_type n) const {
				deque_iterator tmp(*this);
				tmp += n;
				return (*(tmp._ptr));
			}
	};
	template<typename T>
	deque_iterator<T> operator+(typename deque_iterator<T>::difference_type n, deque_iterator<T> a) {
		deque_iterator<T> tmp(a);
		tmp += n;
		return tmp;
	}

	template<typename T1, typename T2>
	bool operator<(const deque_iterator<T1>& a, const deque_iterator<T2>& b) {
		return a.const_ptr() < b.const_ptr();
	}

	template<typename T1, typename T2>
	bool operator>(const deque_iterator<T1>& a, const deque_iterator<T2>& b) {
		return a.const_ptr() > b.const_ptr();
	}

	template<typename T1, typename T2>
	bool operator>=(const deque_iterator<T1>& a, const deque_iterator<T2>& b) {
		return a.const_ptr() >= b.const_ptr();
	}

	template<typename T1, typename T2>
	bool operator<=(const deque_iterator<T1>& a, const deque_iterator<T2>& b) {
		return a.const_ptr() <= b.const_ptr();
	}

	template<typename T1, typename T2>
	bool operator== (const deque_iterator<T1>& a, const deque_iterator<T2>& b) {
		return a.const_ptr() == b.const_ptr();
	}

	template<typename T1, typename T2>
	bool operator!= (const deque_iterator<T1>& a, const deque_iterator<T2>& b) {
		return a.const_ptr() != b.const_ptr();
	}
}

#endif