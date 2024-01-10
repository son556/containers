#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../deque/deque.hpp"

namespace ft {
    template <class T, class Container = deque<T> >
    class queue {
        public:
            typedef T           value_type;
            typedef Container   container_type;
			typedef size_t		size_type;
		
		private:
			container_type	_cntr;
		
		public:
			explicit queue (const container_type& ctnr = container_type()) : _cntr(ctnr) {}

			queue(const queue& ref) { *this = ref; }

			queue& operator=(const queue& ref) {
				_cntr = ref._cntr;
				return *this;
			}

			~queue() {}

			bool empty() const {
				if (this->_cntr.size() == 0) return true;
				return false;
			}


			size_type size() const { return this->_cntr.size(); }

			
			value_type& front() { return this->_cntr.front(); }
			
			const value_type& front() const { return this->_cntr.front(); }

			value_type& back() {return this->_cntr.back(); }
			
			const value_type& back() const { return this->_cntr.back(); }

			void push (const value_type& val) { this->_cntr.push_back(val); }

			void pop() { this->_cntr.pop_front(); }
    };

	template <class T, class Container>  
	bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		queue<T, Container> ltmp = lhs, rtmp = rhs;
		while (ltmp.size() && rtmp.size()) {
			if (ltmp.front() != rtmp.front()) return false;
			ltmp.pop();
			rtmp.pop();
		}
		return true;
	}

	template <class T, class Container>  
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Container>  
	bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		queue<T, Container> ltmp = lhs, rtmp = rhs;
		while (ltmp.size() && rtmp.size()) {
			if (ltmp.front() > rtmp.front()) return false;
			if (ltmp.front() < rtmp.front()) return true;
			ltmp.pop();
			rtmp.pop();
		}
		if (ltmp.size()) return false;
		if (ltmp.size() == rtmp.size()) return false;
		return true;
	}

	template <class T, class Container>  
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		queue<T, Container> ltmp = lhs, rtmp = rhs;
		while (ltmp.size() && rtmp.size()) {
			if (ltmp.front() > rtmp.front()) return false;
			if (ltmp.front() < rtmp.front()) return true;
			ltmp.pop();
			rtmp.pop();
		}
		if (ltmp.size()) return false;
		return true;
	}

	template <class T, class Container>  
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		queue<T, Container> ltmp = lhs, rtmp = rhs;
		while (ltmp.size() && rtmp.size()) {
			if (ltmp.front() < rtmp.front()) return false;
			if (ltmp.front() > rtmp.front()) return true;
			ltmp.pop();
			rtmp.pop();
		}
		if (rtmp.size()) return false;
		if (ltmp.size() == rtmp.size()) return false;
		return true;
	}

	template <class T, class Container>  
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		queue<T, Container> ltmp = lhs, rtmp = rhs;
		while (ltmp.size() && rtmp.size()) {
			if (ltmp.front() < rtmp.front()) return false;
			if (ltmp.front() > rtmp.front()) return true;
			ltmp.pop();
			rtmp.pop();
		}
		if (rtmp.size()) return false;
		return true;
	}
}
#endif