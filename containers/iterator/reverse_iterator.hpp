#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "type_traits.hpp"
namespace ft
{
    template<typename Iterator>
	class reverse_iterator {
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
			reverse_iterator() {}
			reverse_iterator(const reverse_iterator<typename remove_const<iterator_type>::type> &ref_it) : current(ref_it.current) {}
			explicit reverse_iterator(const typename remove_const<iterator_type>::type &ref_it) : current(ref_it) {}
			reverse_iterator& operator=(const reverse_iterator& it) {
				this->current = it.current;
				return *this;
			}

			iterator_type base() const { return current; }

			/**
			 * @brief iterator 의 참조 값을 반환
			 *
			 * @return reference 
			 */
			reference operator*() {
				iterator_type tmp;
				tmp = current - 1;
				return *tmp;
			}

			/**
			 * @brief 현재 iterator + n 반환 
			 * 
			 * @param n 현재 iterator에서 떨어진 위치. 
			 * @return reverse_iterator 
			 */
			reverse_iterator operator+(difference_type n) const { 
				return reverse_iterator(current - n); 
			}

			/**
			 * @brief reverse_iterator의 전위 연산++
			 * 
			 * @return reverse_iterator& 
			 */
			reverse_iterator& operator++() {
				current--;
				return *this;
			}

			/**
			 * @brief 현재 iterator 를 n만큼 + 한 후 반환
			 * 
			 * @param n 
			 * @return reverse_iterator& 
			 */
			reverse_iterator& operator+=(difference_type n) {
				current -= n;
				return *this;
			}

			/**
			 * @brief  reverse_iterator의 후위연산++
			 * 
			 * @return reverse_iterator 
			 */
			reverse_iterator operator++(int) {
				reverse_iterator tmp(current);
				current--;
				return tmp;
			}

			/**
			 * @brief 현재 iterator - n 반환 
			 * 
			 * @param n 현재 iterator에서 떨어진 위치
			 * @return reverse_iterator 
			 */
			reverse_iterator operator-(difference_type n) const {
				return reverse_iterator(current + n);
			}

			/**
			 * @brief reverse_iterator 전위연산--
			 * 
			 * @return reverse_iterator& 
			 */
			reverse_iterator& operator--() {
				current++;
				return *this;
			}

			/**
			 * @brief reverse_iterator 후위연산--
			 * 
			 * @return reverse_iterator 
			 */
			reverse_iterator operator--(int) {
				reverse_iterator tmp(current);
				current++;
				return tmp;
			}

			/**
			 * @brief 현재 iterator 를 n만큼 - 한 후 반환
			 * 
			 * @param n 
			 * @return reverse_iterator& 
			 */
			reverse_iterator& operator-=(difference_type n) {
				current += n;
				return *this;
			}

			pointer operator->() const {
				return &(operator*());
			}

			reference operator[] (difference_type n) const {
				return *(this->operator+(n));
			}
	};
	template <class Iterator>  
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() == rhs.base(); }

	template <class Iterator>  
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() != rhs.base(); }

	template <class Iterator>  
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() < rhs.base(); }

	template <class Iterator>  
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() <= rhs.base(); }

	template <class Iterator>  
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() > rhs.base(); }

	template <class Iterator>  
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() >= rhs.base(); }

	template <class Iterator>  
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator- (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return reverse_iterator<Iterator>(rev_it.base() + n);
	}
}

#endif