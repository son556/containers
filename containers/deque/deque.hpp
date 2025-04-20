#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "../iterator/reverse_iterator.hpp"
#include "../iterator/deque_iterator.hpp"
#include "../iterator/type_traits.hpp"
#include "../vector/vector.hpp"

namespace ft {
    template<class T, class Alloc = std::allocator<T*> > 
    class deque {
        public:
            typedef T           										value_type;
			typedef Alloc												allocator_type;
			typedef value_type&						        			reference;
			typedef const value_type&							        const_reference;
			typedef value_type*									        pointer;
			typedef const value_type*							        const_pointer;
			typedef deque_iterator<value_type>							iterator;
			typedef deque_iterator<const value_type>					const_iterator;
            typedef ft::reverse_iterator<iterator>                      reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
            typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef difference_type										size_type;
		private:
			vector<value_type*, allocator_type> 	_begin;
			pointer const* 							_start;
			pointer									_start_ptr;
			pointer const* 							_end;
			pointer									_end_ptr;
			size_type								_size;
			const size_type							_max_size = 4611686018427387903;
		public:
			explicit deque() {
				this->_begin = vector<value_type *, allocator_type>(3);
				for (int i = 0; i < 3; i++)
					(this->_begin)[i] = new value_type[5];
				this->_start = this->_begin.begin().get_ptr() + 1;
				this->_start_ptr = *(this->_start);
				this->_end = this->_start;
				this->_end_ptr = this->_start_ptr;
				this->_size = 0;
			}
			
			explicit deque (size_type n, const value_type& val = value_type()) {
				size_type cnt = n / 5 + 3;
				this->_begin = vector<value_type*, allocator_type>(cnt);
				for (int i = 0; i < cnt; i++) {
					(this->_begin)[i] = new value_type[5];
				}
				this->_size = n;
				this->_start = &((this->_begin)[cnt / 2]);
				this->_start_ptr = *(this->_start);
				this->_end = this->_start;
				this->_end_ptr = this->_start_ptr;
				while (n--) {
					*(this->_end_ptr) = val;
					this->_end_ptr++;
					if (this->_end_ptr == *(this->_end) + 5) {
						this->_end++;
						this->_end_ptr = *(this->_end);
					}
				}
			}
			
			template <class InputIterator>  
			deque (InputIterator first, InputIterator last, \
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				size_type n = last.get_ptr() - first.get_ptr();
				if (n == 0) return;
				this->_begin = vector<value_type *, allocator_type>(3 * n);
				for (int i = 0; i < 3 * n; i++) {
					(this->_begin)[i] = new value_type[5];
				}
				this->_size = n;
				this->_start = &((this->_begin)[n]);
				this->_start_ptr = *(this->_start);
				this->_end = this->_start;
				this->_end_ptr = this->_start_ptr;
				while (n--) {
					*(this->_end_ptr) = *first;
					this->_end_ptr++;
					first++;
					if (this->_end_ptr == *(this->_end) + 5) {
						this->_end++;
						this->_end_ptr = *(this->_end);
					}
				}
			}

			deque (const deque& x) {
				this->_size = 0;
				*this = x;
			}

			deque& operator= (const deque& ref) {
				if (this->_begin.size()) {
					for (size_type i = 0 ; i < _begin.size(); i++)
						delete this->_begin[i];
				}
				this->_size = ref._size;
				this->_begin = vector<value_type*, allocator_type>(ref._begin.size());
				for (size_type i = 0; i < _begin.size(); i++) {
					(this->_begin)[i] = new value_type[5];
				}
				this->_start = this->_begin.begin().get_ptr() + (ref._start - ref._begin.begin().get_ptr());
				this->_start_ptr = *(this->_start);
				this->_end = this->_start;
				this->_end_ptr = this->_start_ptr;
				for (const_iterator it = ref.begin(); it != ref.end(); it++) {
					*(this->_end_ptr) = *it;
					this->_end_ptr++;
					if (this->_end_ptr == *(this->_end) + 5) {
						this->_end++;
						this->_end_ptr = *(this->_end);
					}
				}
				return *this;
			}

			~deque() {
				for (size_type i = 0 ; i < _begin.size(); i++)
					delete this->_begin[i];
			}
			
			void display() const { // 시험용.
				iterator tmp(this->_start, this->_start_ptr);
				while(1) {
					if (tmp.const_ptr() == this->_end_ptr) break;
					if (tmp.const_ptr() == *(tmp.const_current()) + 4)
						std::cout << *tmp << std::endl;
					else
						std::cout << *tmp << ", ";
					tmp++;
				}
				std::cout << std::endl << std::endl;
			}

			iterator begin() {
				return iterator(this->_start, this->_start_ptr);
			}
			
			const_iterator begin() const {
				const value_type * const *a = this->_start;
				const value_type *b = this->_start_ptr;
				return const_iterator(this->_start, this->_start_ptr);
			}

			iterator end() {
				return iterator(this->_end, this->_end_ptr);
			}
			
			const_iterator end() const {
				return const_iterator(this->_end, this->_end_ptr);
			}

			reverse_iterator rbegin() { return reverse_iterator(this->end());}
			
			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(this->end());
			}

			reverse_iterator rend() {
				return reverse_iterator(this->begin());
			}
			
			const_reverse_iterator rend() const {
				return const_reverse_iterator(this->begin());
			}

			size_type size() const {return _size;}

			size_type max_size() const {return this->_max_size;} // macos에서 나온 값 기준

			void resize (size_type n, value_type val = value_type()) {
				if (this->_size <= n) {
					while (this->_size != n) {
						if (this->_size > this->_max_size)
							throw std::out_of_range("ft::deque");
						this->push_back(val);
					}
				}
				else {
					while (this->_size != n) {
						this->pop_back();
					}
				}
			}

			bool empty() const {
				if (_size == 0) return true;
				return false;
			}

			reference operator[] (size_type n) {
				iterator it = this->begin() + n;
				return *it;
			}
			
			const_reference operator[] (size_type n) const {
				const_iterator it = this->begin() + n;
				return *it;
			}

			reference at (size_type n) {
				if (n >= this->_size)
					throw std::out_of_range("ft::deque at(size_type n)");
				iterator it = this->begin() + n;
				return *it;
			}
			
			const_reference at (size_type n) const {
				if (n >= this->_size)
					throw std::out_of_range("ft::deque at(size_type n)");
				const_iterator it = this->begin() + n;
				return *it;
			}

			reference front() {return *(this->_start_ptr);}
			 
			const_reference front() const {return *(this->_start_ptr);}

			reference back() {
				if (this->_end_ptr == *(this->_end)) {
					return (*(this->_end - 1))[4];
				}
				return *(this->_end_ptr - 1);
			}
			
			const_reference back() const {
				if (this->_end_ptr == *(this->_end)) {
					return (*(this->_end - 1))[4];
				}
				return *(this->_end_ptr - 1);
			}

			template <class InputIterator>  
			void assign (InputIterator first, InputIterator last, 
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				this->_end = this->_start;
				this->_end_ptr = *(this->_end);
				this->_size = 0;
				while (first != last) {
					*(this->_end_ptr) = *first;
					this->_end_ptr++;
					first++;
					this->_size++;
					if (this->_size > this->_max_size)
						throw std::out_of_range("ft::deque assign(InputIterator first, InputIterator last)");
					if (this->_end_ptr == *(this->_end) + 5) {
						this->_end++;
						if (this->_end == _begin.end().get_ptr())
							_begin.push_back(new value_type[5]);
						this->_end_ptr = *(this->_end);
					}
				}
			}
			
			void assign (size_type n, const value_type& val) {
				this->_end = this->_start;
				this->_end_ptr = *(this->_end);
				this->_size = 0;
				while (n--) {
					*(this->_end_ptr) = val;
					this->_end_ptr++;
					this->_size++;
					if (this->_size > this->_max_size)
						throw std::out_of_range("ft::deque assign(size_type n, const value_type& val)");
					if (this->_end_ptr == *(this->_end) + 5) {
						this->_end++;
						if (this->_end == _begin.end().get_ptr())
							_begin.push_back(new value_type[5]);
						this->_end_ptr = *(this->_end);
					}
				}
			}

			void push_back (const value_type& val) {
				if (this->_size + 1 > this->_max_size)
					throw std::out_of_range("ft::deque push_back(const value_type& val)");
				*(this->_end_ptr) = val;
				this->_end_ptr++;
				this->_size++;
				if (this->_end_ptr == *(this->_end) + 5) {
					this->_end++;
					if (this->_end == this->_begin.end().get_ptr()) {
						size_type s_n = this->_start - (this->_begin).begin().get_ptr();
						size_type s_p = this->_start_ptr - *(this->_start);
						this->_begin.push_back(new value_type[5]);
						this->_end = (this->_begin).end().get_ptr() - 1;
						this->_start = (this->_begin).begin().get_ptr() + s_n;
						this->_start_ptr = *(this->_start) + s_p;
					}
					this->_end_ptr = *(this->_end);
				}
			}

			void push_front (const value_type& val) {
				if (this->_size + 1 > this->_max_size)
					throw std::out_of_range("ft::deque push_front(const value_type& val)");
				this->_size++;
				if (this->_start_ptr == this->_end_ptr) {
					*(this->_end_ptr) = val;
					this->_end_ptr++;
					return;
				} 
				if (this->_start_ptr == *(this->_start)) {
					this->_start--;
					if (this->_start == this->_begin.begin().get_ptr() - 1) {
						size_type space_end = this->_end - (this->_begin).begin().get_ptr() + 1;
						size_type space_end_ptr = this->_end_ptr - *(this->_end);
						this->_begin.insert(this->_begin.begin(), new value_type[5]);
						this->_start = this->_begin.begin().get_ptr();
						this->_end = this->_begin.begin().get_ptr() + space_end;
						this->_end_ptr = *(this->_end) + space_end_ptr;
					}
					this->_start_ptr = *(this->_start) + 4;
				}
				else this->_start_ptr--;
				*(this->_start_ptr) = val;
			}

			void pop_back() {
				if (this->_size == 0) return;
				this->_size--;
				if (this->_end_ptr == *(this->_end)) {
					this->_end--;
					this->_end_ptr = *(this->_end) + 4;
				}
				else this->_end_ptr--;
			}

			void pop_front() {
				if (this->_size == 0) return;
				this->_size--;
				this->_start_ptr++;
				if (this->_start_ptr == *(this->_start) + 5) {
					this->_start++;
					this->_start_ptr = *(this->_start);
				}
			}

			iterator insert (iterator position, const value_type& val) {
				std::cout << "here insert" << std::endl;
				if (this->_size + 1 > this->_max_size)
					throw std::out_of_range("ft::deque");
				push_back(val);
				value_type tmp_isnert = val;
				value_type tmp_out;
				iterator last(this->_end, this->_end_ptr);
				for (iterator it = last - 1; it != position; it--)
					*it = *(it - 1);
				*position = val;
				return position;
			}
    		
			void insert (iterator position, size_type n, const value_type& val) {
				if (_size + n > _max_size) 
					throw std::out_of_range("ft::deque insert(iterator position, size_type n, const value_type& val)");
				iterator last = this->end();
				iterator start = this->begin();
				size_type start_gap = position.const_current() - _begin.begin().get_ptr();
				size_type start_ptr_gap = position.const_ptr() - *(position.const_current());
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
				position = iterator(this->_begin.begin().get_ptr() + start_gap, *(this->_begin.begin().get_ptr() + start_gap) + start_ptr_gap);
				if (last == start) return;
				last = this->end();
				for (iterator it = last - 1; it != position + (n - 1); it--)
					*it = *(it - n);
				for (iterator it = position; it != position + n; it++)
					*it = val;
			}
			
			template <class InputIterator>    
			void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				while (last != first) {
					last--;
					insert(position, *last);
				}
			}
			
			iterator erase (iterator position) {
				value_type val = *position; // segfault 발생시키기 위해 사용
				iterator last(this->_end, this->_end_ptr);
				for (iterator it = position; it != last - 1; it++)
					*it = *(it + 1);
				if (this->_end_ptr == *(this->_end)) {
					this->_end--;
					this->_end_ptr = *(this->_end) + 4;
				}
				else this->_end_ptr--;
				this->_size--;
				return position;
			}

			iterator erase (iterator first, iterator last) {
				size_type cnt = (last.const_current() - first.const_current() - 1) * 5;
				if (cnt < 0) cnt = 0;
				if (first.const_current() != last.const_current()) {
					cnt += *(first.const_current()) + 5 - first.const_ptr();
					cnt += last.const_ptr() - *(last.const_current());
				}
				else cnt += last.const_ptr() - first.const_ptr();
				value_type val;
				if (cnt > this->_size)
					val = **(this->_begin.begin() - 1);// segfault 발생시키기 위해서 사용
				iterator tmp = iterator(this->_end, this->_end_ptr) - cnt;
				for(iterator it = first; it != tmp; it++)
					*it = *(it + cnt);
				this->_end = tmp.const_current();
				this->_end_ptr = tmp.const_ptr();
				this->_size -= cnt;
				return first;
			}

			void swap (deque& x) {
				deque<value_type> tmp = *this;
				*this = x;
				x = tmp;
			}

			void clear() {
				this->_size = 0;
				this->_end = this->_start;
				this->_end_ptr = this->_start_ptr;
			}
    };
	
	template< class T, class Alloc>
	bool operator==( const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs ) {
		if (lhs.size() != rhs.size()) return false;
		typename deque<T, Alloc>::const_iterator cmp_it = rhs.begin();
		for (typename deque<T, Alloc>::const_iterator it = lhs.begin(); it != lhs.end(); it++) {
			if (*it != *cmp_it) return false;
			cmp_it++;
		}
		return true;
	}

	template <class T, class Alloc>  
	bool operator!= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>  
	bool operator<  (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {
		typename deque<T, Alloc>::const_iterator l_it = lhs.begin();
		typename deque<T, Alloc>::const_iterator r_it = rhs.begin();
		
		if (lhs.size() <= rhs.size()) {
			for (; l_it != lhs.end(); l_it++) {
				if (*l_it < *r_it) return true;
				if (*l_it > *r_it) return false;
				r_it++;
			}
			if (lhs.size() == rhs.size()) return false;
			return true;
		}
		for (; r_it != rhs.end(); r_it++) {
			if (*l_it < *r_it) return true;
			if (*l_it > *r_it) return false;
			l_it++;
		}
		return false;
	}

	template <class T, class Alloc>  
	bool operator<= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {
		typename deque<T, Alloc>::const_iterator l_it = lhs.begin();
		typename deque<T, Alloc>::const_iterator r_it = rhs.begin();

		if (lhs.size() <= rhs.size()) {
			for (; l_it != lhs.end(); l_it++) {
				if (*l_it < *r_it) return true;
				if (*l_it > *r_it) return false;
				r_it++;
			}
			return true;
		}
		for (; r_it != rhs.end(); r_it++) {
			if (*l_it < *r_it) return true;
			if (*l_it > *r_it) return false;
			l_it++;
		}
		return false;
	}

	template <class T, class Alloc>  
	bool operator>  (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {
		typename deque<T, Alloc>::const_iterator l_it = lhs.begin();
		typename deque<T, Alloc>::const_iterator r_it = rhs.begin();

		if (lhs.size() >= rhs.size()) {
			for (; r_it != rhs.end(); r_it++) {
				if (*l_it > *r_it) return true;
				if (*l_it < *r_it) return false;
				l_it++;
			}
			if (lhs.size() == rhs.size()) return false;
			return true;
		}
		for (; l_it != lhs.end(); l_it++) {
			if (*l_it > *r_it) return true;
			if (*l_it < *r_it) return false;
			r_it++;
		}
		return false;
	}

	template <class T, class Alloc>  
	bool operator>= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {
		typename deque<T, Alloc>::const_iterator l_it = lhs.begin();
		typename deque<T, Alloc>::const_iterator r_it = rhs.begin();

		if (lhs.size() >= rhs.size()) {
			for (; r_it != rhs.end(); r_it++) {
				if (*l_it > *r_it) return true;
				if (*l_it < *r_it) return false;
				l_it++;
			}
			return true;
		}
		for (; l_it != lhs.end(); l_it++) {
			if (*l_it > *r_it) return true;
			if (*l_it < *r_it) return false;
			r_it++;
		}
		return false;
	}

}
#endif
