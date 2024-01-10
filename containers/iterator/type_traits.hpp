#ifndef ABLE_STRUCT_HPP
#define ABLE_STRUCT_HPP

#include <cstdint>

namespace ft
{
    template<typename T>
    struct Node {
        T       val;
        Node    *next;
        Node    *before;
        Node() : val(0), next(NULL), before(NULL) {}
        Node(const Node<T>& ref) : val(ref.val), next(ref.next), before(ref.before) {}
        Node(T value) : val(value), next(NULL), before(NULL) {}
    };
    
    template<class T>
    struct remove_const { typedef T type; };

    template<class T>
    struct remove_const<const T> { typedef T type; };

    template<class T>
    struct create_const { typedef const T type; };

    template<class T>
    struct create_const<const T> {typedef T type;};
    
    
    template<bool Cond, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template <class T, T v>
    struct integral_constant {
        const static T value = v;
        typedef T value_type;
        typedef integral_constant<T,v> type;
        operator T() { return v; }
    };

    template <typename T>
    struct is_const : public integral_constant<bool, false> {};

    template <typename T>
    struct is_const<const T> : public integral_constant<bool, true> {};

    template <typename T>
    struct is_integral : public integral_constant<bool, false> {};

    template<>
    struct is_integral<bool> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<char> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<char16_t> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<wchar_t> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<signed char> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<short int> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<int> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<long int> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<long long int> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<unsigned char> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<unsigned short int> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<unsigned int> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<unsigned long int> : public integral_constant<bool, true> {};

    template<>
    struct is_integral<unsigned long long int> : public integral_constant<bool, true> {};

}
#endif