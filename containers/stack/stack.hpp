#ifndef STACK_HPP
#define STACK_HPP

#include "../deque/deque.hpp"

namespace ft {
    template<class T, class Container = ft::deque<T> >
    class stack {
        public:
            typedef T           value_type;
            typedef size_t      size_type;
            typedef Container   container_type;
		private:
			container_type _cntr;
		public:
			explicit stack (const container_type& ctnr = container_type()) : _cntr(ctnr) {}

			stack(const stack& other) { *this = other; }

			~stack() {}
			
			stack& operator=(const stack& other) { 
				this->_cntr = other._cntr;
				return *this; 
			}

			bool empty() const {
				if (this->_cntr.size() == 0) return true;
				return false;
			}

			size_type size() const {return this->_cntr.size(); }

			value_type& top() { return this->_cntr.back(); }
			
			const value_type& top() const { return this->_cntr.back(); }

			void push (const value_type& val) { this->_cntr.push_back(val); }

			void pop() { this->_cntr.pop_back(); }
    };

	template <class T, class Container>  
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		stack<T, Container> ltmp = lhs;
		stack<T, Container> rtmp = rhs;

		while (ltmp.size()) {
			if (ltmp.top() != rtmp.top()) return false;
			ltmp.pop();
			rtmp.pop();
		}
		return true;
	}	

	template <class T, class Container>  
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs == rhs);
	}
	
	template <class T, class Container>  
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		stack<T, Container> ltmp = lhs;
		stack<T, Container> rtmp = rhs;
		while (ltmp.size() && rtmp.size()) {
			if (ltmp.top() < rtmp.top()) return true;
			if (ltmp.top() > rtmp.top()) return false;
			ltmp.pop();
			rtmp.pop();
		}
		if (ltmp.size()) return false;
		if (ltmp.size() == 0 && rtmp.size() == 0) return false;
		return true;
	}
	
	template <class T, class Container>  
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		stack<T, Container> ltmp = lhs;
		stack<T, Container> rtmp = rhs;
		while (ltmp.size() && rtmp.size()) {
			if (ltmp.top() < rtmp.top()) return true;
			if (ltmp.top() > rtmp.top()) return false;
			ltmp.pop();
			rtmp.pop();
		}
		if (ltmp.size()) return false;
		return true;
	}

	template <class T, class Container>  
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		stack<T, Container> ltmp = lhs;
		stack<T, Container> rtmp = rhs;
		while (ltmp.size() && rtmp.size()) {
			if (ltmp.top() > rtmp.top()) return true;
			if (ltmp.top() < rtmp.top()) return false;
			ltmp.pop();
			rtmp.pop();
		}
		if (rtmp.size()) return false;
		if (ltmp.size() == 0 && rtmp.size() == 0) return false;
		return true;
	}

	template <class T, class Container>  
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		stack<T, Container> ltmp = lhs;
		stack<T, Container> rtmp = rhs;
		while (ltmp.size() && rtmp.size()) {
			if (ltmp.top() > rtmp.top()) return true;
			if (ltmp.top() < rtmp.top()) return false;
			ltmp.pop();
			rtmp.pop();
		}
		if (rtmp.size()) return false;
		return true;
	}
}
#endif