#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../iterator/iterator_traits.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../iterator/random_access_iterator.hpp"
#include "../iterator/type_traits.hpp"
#include "../iterator/algorithm.hpp"
#include <memory>

namespace ft {

    template < typename T, typename Alloc = std::allocator<T> >
    class vector {
        public:
            typedef T   										    	value_type;
            typedef Alloc										    	allocator_type;
			typedef typename allocator_type::reference			        reference;
			typedef typename allocator_type::const_reference	        const_reference;
			typedef typename allocator_type::pointer			        pointer;
			typedef typename allocator_type::const_pointer		        const_pointer;
            typedef randomaccess_iterator<value_type>                   iterator;
            typedef randomaccess_iterator<const value_type>             const_iterator;
            typedef reverse_iterator<iterator>                          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
            typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef difference_type										size_type;
		
		protected:
			allocator_type												_alloc;
			pointer														_start;
			pointer														_end;
			pointer														_end_capacity;
        
		public:
            explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _start(0), \
            _end(0), _end_capacity(0) {}
            
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
				this->_alloc = alloc;
				this->_start = _alloc.allocate(n);
				this->_end = this->_start;
				this->_end_capacity = this->_start + n;
				while (n--) {
					this->_alloc.construct(this->_end, val);
					this->_end++;
				}
			}
			
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				size_type n = last.get_ptr() - first.get_ptr();
				this->_alloc = alloc;
				this->_start = _alloc.allocate(n);
				this->_end = this->_start;
				this->_end_capacity = this->_start + n;
				while (n--) {
					this->_alloc.construct(this->_end, *first);
					this->_end++;
					first++;
				}
			}
            
			vector (const vector& ref) {
				this->_start = 0;
				this->_end = 0;
				this->_end_capacity = 0;
				*this = ref;
			}

			vector& operator=(const vector& ref) {
				this->_alloc = ref._alloc;
				reserve(ref._end_capacity - ref._start);
				size_type n = ref._end - ref._start;
				for (size_type i = 0; i < n; i++) this->_alloc.construct(this->_start + i, *(ref._start + i));
				this->_end = this->_start + n;
				return *this;
			}

			~vector() {
				clear();
				this->_alloc.deallocate(this->_start, capacity());
			}

			template <class InputIterator> 
			void assign (InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				size_type n = this->_end - this->_start;
				for (size_type i = 0; i < n; i++) this->_alloc.destroy(_start + i);
				reserve(last.get_ptr() - first.get_ptr());
				clear();
				while (first != last)
				{
					this->_alloc.construct(this->_end, *first);
					this->_end++;
					first++;
				}	
			}

			void assign (size_type n, const value_type& val) {
				size_type tmp = this->_end - this->_start;
				for (size_type i = 0; i < tmp; i++) this->_alloc.destroy(_start + i);
				reserve(n);
				clear();
				while (n--)
				{
					this->_alloc.construct(this->_end, val);
					this->_end++;
				}
			}

			void reserve(size_type new_cap) {
				size_type n = this->_end_capacity - this->_start;
				if (n >= new_cap) return;
				pointer tmp_start, tmp_end, tmp_end_capacity;
				tmp_start = this->_alloc.allocate(new_cap);
				tmp_end = tmp_start;
				tmp_end_capacity = tmp_start + new_cap;
				n = this->_end - this->_start;
				for (size_type i = 0; i < n; i++) {
					this->_alloc.construct(tmp_end, *(_start + i));
					this->_alloc.destroy(_start + i);
					tmp_end++;
				}
				if (size() > 0)
					this->_alloc.deallocate(this->_start, this->_end_capacity - this->_start);
				this->_start = tmp_start;
				this->_end = tmp_end;
				this->_end_capacity = tmp_end_capacity;
			}

			void clear() {
				while (this->_start != this->_end)
					this->_alloc.destroy(--this->_end);
			}

			size_type capacity() { return this->_end_capacity - this->_start; }

			allocator_type get_allocator() const { return this->_alloc; }

			reference at(size_type n) {
				if (n >= size()) {
					throw std::out_of_range("ft::vector");
				}
				return (*(this->_start + n));
			}
			
			const_reference at(size_type n) const {
				if (n >= size()) throw std::out_of_range("ft::vector");
				return *(this->_start + n);
			}

			reference operator[] (size_type n) { return *(this->_start + n); }

			const_reference operator[] (size_type n) const { return *(this->_start + n); }

			size_type size() const { return this->_end - this->_start; }

			reference front() { return *(this->_start); }

			const_reference front() const { return *(this->_start); }

			reference back() { return *(this->_end - 1); }

			const_reference back() const { return *(this->_end - 1); }

			value_type* data() { return this->_start; }
			 
			const value_type* data() const { return this->_start; }

			void push_back (const value_type& val) {
				if (this->_end + 1 > this->_end_capacity) this->reserve(_end_capacity - _start + 1);
				this->_alloc.construct(this->_end, val);
				this->_end += 1;
			}

			void pop_back() { this->_alloc.destroy(--this->_end); }

			iterator insert (iterator position, const value_type& val) {
				size_type n = position.get_ptr() - this->_start;
				push_back(val);
				for (pointer i = this->_end - 1; i > this->_start + n; i--)
					this->_alloc.construct(i, *(i - 1));
				this->_alloc.construct(this->_start + n, val);
				return this->begin() + n;
			}

			void insert (iterator position, size_type n, const value_type& val) {
				size_type diff = position.get_ptr() - this->_start;
				reserve(this->_end - this->_start + n);
				for (pointer i = _end - 1; i >= this->_start + diff; i--)
					this->_alloc.construct(i + n, *i);
				for (pointer i = this->_start + diff; i < this->_start + diff + n; i++)
					this->_alloc.construct(i, val);
				this->_end += n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				size_type n = position.get_ptr() - this->_start;
				last--;
				first--;
				while (first != last) {
					insert(this->_start + n, *last);
					last--;
				}
			}

			iterator erase (iterator position) {
				size_type n = position.get_ptr() - this->_start;
				for (pointer i = this->_start + n; i < this->_end - 1; i++)
					*(i) = *(i + 1);
				pop_back();
				return this->begin() + n;
			}
			
			iterator erase (iterator first, iterator last) {
				iterator tmp = first;
				size_type n = last.get_ptr() - first.get_ptr(), cnt = 0;
				if (first == last) return tmp;
				while (cnt < n)
				{
					erase(first);
					cnt++;
				}
				if (n == this->_end - this->_start) tmp = 0;
				return tmp;
			}

			void swap (vector& x) {
				vector tmp = *this;
				*this = x;
				x = tmp;
			}

			void resize (size_type n, value_type val = value_type()) {
				if (n < this->size())
					this->erase(this->begin() + n, this->end());
				else
					this->insert(this->end(), n - this->size(), val);
			}

			bool empty() { return (this->_end - this->_start == 0); }

			const_iterator begin() const { return const_iterator(_start); }
			iterator begin()  { return iterator(this->_start); }
			const_iterator end() const { return const_iterator(this->_end); }
			iterator end() { return iterator(this->_end); }
			reverse_iterator rbegin() { return reverse_iterator(this->end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
			reverse_iterator rend() { return reverse_iterator(this->begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }
    };

	template <class T, class Alloc>  
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		for (size_t i = 0; i < lhs.size(); i++) {
			if (lhs[i] != rhs[i]) return false;
		}
		return true;
	}

	template <class T, class Alloc>  
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs == rhs) return false;
		return true;
	}

	template <class T, class Alloc>  
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>  
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return rhs < lhs; }

	template <class T, class Alloc>  
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs < rhs); }

	template <class T, class Alloc>  
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs > rhs); }
}

#endif