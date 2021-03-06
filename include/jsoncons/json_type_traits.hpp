// Copyright 2013 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_JSON_TYPE_TRAITS_HPP
#define JSONCONS_JSON_TYPE_TRAITS_HPP

#include <array>
#include <string>
#include <vector>
#include <valarray>
#include <exception>
#include <cstring>
#include <utility>
#include <algorithm> // std::swap
#include <limits> // std::numeric_limits
#include <type_traits> // std::enable_if
#include <iterator> // std::iterator_traits, std::input_iterator_tag
#include <jsoncons/json_type.hpp>
#include <jsoncons/bignum.hpp>
#include <jsoncons/json_content_handler.hpp>
#include <jsoncons/detail/more_type_traits.hpp>
#include <string>
#include <tuple>
#include <map>
#include <functional>
#include <memory>
#include <jsoncons/conversion_error.hpp>

namespace jsoncons {

    template <class T,class Enable=void>
    struct is_basic_json_class : std::false_type
    {};

    #if defined(_MSC_VER) && _MSC_VER < 1916  
    template <class T>
    struct is_basic_json_class<T, typename std::enable_if<!std::is_void<typename T::char_type>::value && 
                                                          !std::is_void<typename T::implementation_policy>::value && 
                                                          !std::is_void<typename T::allocator_type>::value>::type> : std::true_type
    {};
    #else
    template <class T>
    struct is_basic_json_class<T, decltype(std::declval<jsoncons::basic_json<typename T::char_type,typename T::implementation_policy,typename T::allocator_type>>(),void())> : std::true_type
    {};
    #endif

    template <class T>
    struct is_json_type_traits_declared : public std::false_type
    {};

    #if !defined(JSONCONS_NO_DEPRECATED)
    template <class T>
    using is_json_type_traits_impl = is_json_type_traits_declared<T>;
    #endif

    // json_type_traits

    template<typename T>
    struct unimplemented : std::false_type
    {};

    template <class Json, class T, class Enable=void>
    struct json_type_traits
    {
        typedef typename Json::allocator_type allocator_type;

        static constexpr bool is_compatible = false;

        static constexpr bool is(const Json&)
        {
            return false;
        }

        static T as(const Json&)
        {
            static_assert(unimplemented<T>::value, "as not implemented");
        }

        static Json to_json(const T&, const allocator_type& = allocator_type())
        {
            static_assert(unimplemented<T>::value, "to_json not implemented");
        }
    };

namespace detail {

    // is_json_type_traits_unspecialized
    template<class Json, class T, class Enable = void>
    struct is_json_type_traits_unspecialized : std::false_type {};

    // is_json_type_traits_unspecialized
    template<class Json, class T>
    struct is_json_type_traits_unspecialized<Json,T,
        typename std::enable_if<!std::integral_constant<bool, json_type_traits<Json, T>::is_compatible>::value>::type
    > : std::true_type {};

    // is_json_type_traits_specialized
    template<class Json, class T, class Enable=void>
    struct is_json_type_traits_specialized : std::false_type {};

    template<class Json, class T>
    struct is_json_type_traits_specialized<Json,T, 
        typename std::enable_if<!is_json_type_traits_unspecialized<Json,T>::value
    >::type> : std::true_type {};

    // is_compatible_string_type
    template<class Json, class T, class Enable=void>
    struct is_compatible_string_type : std::false_type {};

    template<class Json, class T>
    struct is_compatible_string_type<Json,T, 
        typename std::enable_if<!std::is_same<T,typename Json::array>::value &&
        jsoncons::detail::is_string_like<T>::value && 
        !is_json_type_traits_unspecialized<Json,typename std::iterator_traits<typename T::iterator>::value_type>::value
    >::type> : std::true_type {};

    // is_compatible_string_view_type
    template<class Json, class T, class Enable=void>
    struct is_compatible_string_view_type : std::false_type {};

    template<class Json, class T>
    struct is_compatible_string_view_type<Json,T, 
        typename std::enable_if<!std::is_same<T,typename Json::array>::value &&
        jsoncons::detail::is_string_view_like<T>::value && 
        !is_json_type_traits_unspecialized<Json,typename std::iterator_traits<typename T::iterator>::value_type>::value
    >::type> : std::true_type {};

    // is_compatible_array_type
    template<class Json, class T, class Enable=void>
    struct is_compatible_array_type : std::false_type {};

    template<class Json, class T>
    struct is_compatible_array_type<Json,T, 
        typename std::enable_if<!std::is_same<T,typename Json::array>::value &&
        jsoncons::detail::is_vector_like<T>::value && 
        !is_json_type_traits_unspecialized<Json,typename std::iterator_traits<typename T::iterator>::value_type>::value
    >::type> : std::true_type {};

    // is_compatible_object_type
    template<class Json, class T, class Enable=void>
    struct is_compatible_object_type : std::false_type {};

    template<class Json, class T>
    struct is_compatible_object_type<Json,T, 
                           typename std::enable_if<
        !is_json_type_traits_unspecialized<Json,typename T::mapped_type>::value
    >::type> : std::true_type {};

} // namespace detail

    template<class Json>
    struct json_type_traits<Json, const typename std::decay<typename Json::char_type>::type*>
    {
        typedef typename Json::char_type char_type;
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_string();
        }
        static const char_type* as(const Json& j)
        {
            return j.as_cstring();
        }
        template <class ... Args>
        static Json to_json(const char_type* s, Args&&... args)
        {
            return Json(s, semantic_tag::none, std::forward<Args>(args)...);
        }
    };

    template<class Json>
    struct json_type_traits<Json, typename std::decay<typename Json::char_type>::type*>
    {
        typedef typename Json::char_type char_type;
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_string();
        }
        template <class ... Args>
        static Json to_json(const char_type* s, Args&&... args)
        {
            return Json(s, semantic_tag::none, std::forward<Args>(args)...);
        }
    };

    // integral

    template<class Json, class T>
    struct json_type_traits<Json, T,
                            typename std::enable_if<jsoncons::detail::is_integer_like<T>::value
    >::type>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            if (j.is_int64())
            {
                return (j.template as_integer<int64_t>() >= (std::numeric_limits<T>::lowest)()) && (j.template as_integer<int64_t>() <= (std::numeric_limits<T>::max)());
            }
            else if (j.is_uint64())
            {
                return j.template as_integer<uint64_t>() <= static_cast<uint64_t>((std::numeric_limits<T>::max)());
            }
            else
            {
                return false;
            }
        }
        static T as(const Json& j)
        {
            return j.template as_integer<T>();
        }
        static Json to_json(T val, allocator_type = allocator_type())
        {
            return Json(val, semantic_tag::none);
        }
    };

    template<class Json, class T>
    struct json_type_traits<Json, T,
                            typename std::enable_if<jsoncons::detail::is_uinteger_like<T>::value>::type>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            if (j.is_int64())
            {
                return j.template as_integer<int64_t>() >= 0 && static_cast<uint64_t>(j.template as_integer<int64_t>()) <= (std::numeric_limits<T>::max)();
            }
            else if (j.is_uint64())
            {
                return j.template as_integer<uint64_t>() <= (std::numeric_limits<T>::max)();
            }
            else
            {
                return false;
            }
        }

        static T as(const Json& j)
        {
            return j.template as_integer<T>();
        }

        static Json to_json(T val, allocator_type = allocator_type())
        {
            return Json(val, semantic_tag::none);
        }
    };

    template<class Json, class T>
    struct json_type_traits<Json, T,
                            typename std::enable_if<std::is_floating_point<T>::value
    >::type>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_double();
        }
        static T as(const Json& j)
        {
            return static_cast<T>(j.as_double());
        }
        static Json to_json(T val, allocator_type = allocator_type())
        {
            return Json(val, semantic_tag::none);
        }
    };

    template<class Json>
    struct json_type_traits<Json, typename Json::object>
    {
        typedef typename Json::object json_object;
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_object();
        }
        static Json to_json(const json_object& o, const allocator_type& = allocator_type())
        {
            return Json(o,semantic_tag::none);
        }
    };

    template<class Json>
    struct json_type_traits<Json, typename Json::array>
    {
        typedef typename Json::array json_array;
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_array();
        }
        static Json to_json(const json_array& a, const allocator_type& = allocator_type())
        {
            return Json(a, semantic_tag::none);
        }
    };

    template<class Json>
    struct json_type_traits<Json, Json>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json&) noexcept
        {
            return true;
        }
        static Json as(Json j)
        {
            return j;
        }
        static Json to_json(const Json& val, allocator_type = allocator_type())
        {
            return val;
        }
    };

    template<class Json>
    struct json_type_traits<Json, jsoncons::null_type>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_null();
        }
        static typename jsoncons::null_type as(const Json& j)
        {
            JSONCONS_ASSERT(j.is_null());
            return jsoncons::null_type();
        }
        static Json to_json(jsoncons::null_type, allocator_type = allocator_type())
        {
            return Json::null();
        }
    };

    template<class Json>
    struct json_type_traits<Json, bool>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_bool();
        }
        static bool as(const Json& j)
        {
            return j.as_bool();
        }
        static Json to_json(bool val, allocator_type = allocator_type())
        {
            return Json(val, semantic_tag::none);
        }
    };

    template<class Json, class T>
    struct json_type_traits<Json, T, typename std::enable_if<std::is_same<T, 
        std::conditional<!std::is_same<bool,std::vector<bool>::const_reference>::value,
                         std::vector<bool>::const_reference,
                         void>::type>::value>::type>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_bool();
        }
        static bool as(const Json& j)
        {
            return j.as_bool();
        }
        static Json to_json(bool val, allocator_type = allocator_type())
        {
            return Json(val, semantic_tag::none);
        }
    };

    template<class Json>
    struct json_type_traits<Json, std::vector<bool>::reference>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_bool();
        }
        static bool as(const Json& j)
        {
            return j.as_bool();
        }
        static Json to_json(bool val, allocator_type = allocator_type())
        {
            return Json(val, semantic_tag::none);
        }
    };

    template<class Json, typename T>
    struct json_type_traits<Json, T, 
                            typename std::enable_if<!is_json_type_traits_declared<T>::value && jsoncons::detail::is_compatible_array_type<Json,T>::value>::type>
    {
        typedef typename std::iterator_traits<typename T::iterator>::value_type value_type;
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            bool result = j.is_array();
            if (result)
            {
                for (auto e : j.array_range())
                {
                    if (!e.template is<value_type>())
                    {
                        result = false;
                        break;
                    }
                }
            }
            return result;
        }

        template <class Ty = value_type>
        static typename std::enable_if<!std::is_same<Ty,uint8_t>::value,T>::type
        as(const Json& j)
        {
            if (j.is_array())
            {
                T result;
                do_reserve_(typename std::integral_constant<bool, jsoncons::detail::has_reserve<T>::value>::type(),result,j.size());
                for (const auto& item : j.array_range())
                {
                    result.push_back(item.template as<value_type>());
                }

                return result;
            }
            else 
            {
                JSONCONS_THROW(ser_error(conversion_errc::json_not_vector));
            }
        }

        template <class Ty = value_type>
        static typename std::enable_if<std::is_same<Ty,uint8_t>::value,T>::type
        as(const Json& j)
        {
            if (j.is_array())
            {
                T result;
                do_reserve_(typename std::integral_constant<bool, jsoncons::detail::has_reserve<T>::value>::type(),result,j.size());
                for (const auto& item : j.array_range())
                {
                    result.push_back(item.template as<value_type>());
                }

                return result;
            }
            else if (j.is_byte_string_view())
            {
                T v(j.as_byte_string_view().begin(),j.as_byte_string_view().end());
                return v;
            }
            else
            {
                JSONCONS_THROW(ser_error(conversion_errc::json_not_vector));
            }
        }

        static Json to_json(const T& val)
        {
            Json j(json_array_arg);
            auto first = std::begin(val);
            auto last = std::end(val);
            size_t size = std::distance(first,last);
            j.reserve(size);
            for (auto it = first; it != last; ++it)
            {
                j.push_back(*it);
            }
            return j;
        }

        static Json to_json(const T& val, const allocator_type& alloc)
        {
            Json j(json_array_arg, alloc);
            auto first = std::begin(val);
            auto last = std::end(val);
            size_t size = std::distance(first, last);
            j.reserve(size);
            for (auto it = first; it != last; ++it)
            {
                j.push_back(*it);
            }
            return j;
        }

        static void do_reserve_(std::true_type, T& v, size_t size)
        {
            v.reserve(size);
        }

        static void do_reserve_(std::false_type, T&, size_t)
        {
        }
    };

    template<class Json, typename T>
    struct json_type_traits<Json, T, 
                            typename std::enable_if<!is_json_type_traits_declared<T>::value && jsoncons::detail::is_compatible_string_type<Json,T>::value>::type>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_string();
        }

        static T as(const Json& j)
        {
       	    return T(j.as_string());
        }

        static Json to_json(const T& val)
        {
            return Json(val, semantic_tag::none);
        }

        static Json to_json(const T& val, const allocator_type& alloc)
        {
            return Json(val, semantic_tag::none, alloc);
        }
    };

    template<class Json, typename T>
    struct json_type_traits<Json, T, 
                            typename std::enable_if<!is_json_type_traits_declared<T>::value && jsoncons::detail::is_compatible_string_view_type<Json,T>::value>::type>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_string_view();
        }

        static T as(const Json& j)
        {
       	    return T(j.as_string_view().data(),j.as_string_view().size());
        }

        static Json to_json(const T& val)
        {
            return Json(val, semantic_tag::none);
        }

        static Json to_json(const T& val, const allocator_type& alloc)
        {
            return Json(val, semantic_tag::none, alloc);
        }
    };

    template<class Json, typename T>
    struct json_type_traits<Json, T, 
                            typename std::enable_if<!is_json_type_traits_declared<T>::value && 
                                                    jsoncons::detail::is_constructible_from_const_pointer_and_size<typename T::key_type>::value &&
                                                    jsoncons::detail::is_json_type_traits_specialized<Json,typename T::mapped_type>::value>::type
    >
    {
        typedef typename T::mapped_type mapped_type;
        typedef typename T::value_type value_type;
        typedef typename T::key_type key_type;
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            bool result = j.is_object();
            for (auto member : j.object_range())
            {
                if (!member.value().template is<mapped_type>())
                {
                    result = false;
                }
            }
            return result;
        }

        static T as(const Json& j)
        {
            if (!j.is_object())
            {
                JSONCONS_THROW(ser_error(conversion_errc::json_not_map));
            }
            T result;
            for (const auto& item : j.object_range())
            {
                result.emplace(key_type(item.key().data(),item.key().size()), item.value().template as<mapped_type>());
            }

            return result;
        }

        static Json to_json(const T& val)
        {
            Json j(json_object_arg, val.begin(), val.end());
            return j;
        }

        static Json to_json(const T& val, const allocator_type& alloc)
        {
            Json j(json_object_arg, val.begin(), val.end(), alloc);
            return j;
        }
    };

    template <class Json, typename T>
    struct json_type_traits<Json, T, 
                            typename std::enable_if<!is_json_type_traits_declared<T>::value && 
                                                    std::is_integral<typename T::key_type>::value &&
                                                    jsoncons::detail::is_json_type_traits_specialized<Json,typename T::mapped_type>::value>::type
    >
    {
        typedef typename T::mapped_type mapped_type;
        typedef typename T::value_type value_type;
        typedef typename T::key_type key_type;
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& val) noexcept {
            if (!val.is_object())
                return false;
            for (const auto& item : val.object_range())
            {
                if (!jsoncons::detail::to_integer<key_type>(item.key().data(),item.key().size()))
                {
                    return false;
                }
            }
            return true;
        }

        static T as(const Json& val) {
            T result;
            for (const auto& item : val.object_range())
            {
                auto r = jsoncons::detail::to_integer<key_type>(item.key().data(),item.key().size());
                result.emplace(r.value(), item.value().template as<mapped_type>());
            }

            return result;
        }

        static Json to_json(const T& val) {
            Json j;
            j.reserve(val.size());
            for (const auto& item : val)
            {
                typename Json::key_type key;
                jsoncons::detail::print_integer(item.first,key);
                j.try_emplace(key, item.second);
            }
            return j;
        }

        static Json to_json(const T& val, const allocator_type& alloc)
        {
            Json j;
            j.reserve(val.size());
            for (const auto& item : val)
            {
                typename Json::key_type key{alloc};
                jsoncons::detail::print_integer(item.first,key);
                j.try_emplace(key, item.second, alloc);
            }
            return j;
        }
    };

    template<class Json, class E, size_t N>
    struct json_type_traits<Json, std::array<E, N>>
    {
        typedef typename Json::allocator_type allocator_type;

        typedef E value_type;

        static bool is(const Json& j) noexcept
        {
            bool result = j.is_array() && j.size() == N;
            if (result)
            {
                for (auto e : j.array_range())
                {
                    if (!e.template is<value_type>())
                    {
                        result = false;
                        break;
                    }
                }
            }
            return result;
        }

        static std::array<E, N> as(const Json& j)
        {
            std::array<E, N> buff;
            JSONCONS_ASSERT(j.size() == N);
            for (size_t i = 0; i < N; i++)
            {
                buff[i] = j[i].template as<E>();
            }
            return buff;
        }

        static Json to_json(const std::array<E, N>& val)
        {
            Json j(json_array_arg);
            j.reserve(N);
            for (auto it = val.begin(); it != val.end(); ++it)
            {
                j.push_back(*it);
            }
            return j;
        }

        static Json to_json(const std::array<E, N>& val, 
                            const allocator_type& alloc)
        {
            Json j(json_array_arg, alloc);
            j.reserve(N);
            for (auto it = val.begin(); it != val.end(); ++it)
            {
                j.push_back(*it);
            }
            return j;
        }
    };

namespace detail
{
    template<size_t Pos, class Json, class Tuple>
    struct json_tuple_helper
    {
        using element_type = typename std::tuple_element<Pos - 1, Tuple>::type;
        using next = json_tuple_helper<Pos - 1, Json, Tuple>;
        
        static bool is(const Json& j) noexcept
        {
            if(j[Pos - 1].template is<element_type>())
            {
                return next::is(j);
            }
            else
            {
                return false;
            }
        }

        static void as(Tuple& tuple, const Json& j)
        {
            std::get<Pos - 1>(tuple) = j[Pos - 1].template as<element_type>();
            next::as(tuple, j);
        }

        static void to_json(const Tuple& tuple, std::array<Json, std::tuple_size<Tuple>::value>& jsons)
        {
            jsons[Pos - 1] = json_type_traits<Json, element_type>::to_json(std::get<Pos-1>(tuple));
            next::to_json(tuple, jsons);
        }
    };

    template<class Json, class Tuple>
    struct json_tuple_helper<0, Json, Tuple>
    {
        static bool is(const Json&) noexcept
        {
            return true;
        }

        static void as(Tuple&, const Json&)
        {
        }

        static void to_json(const Tuple&, std::array<Json, std::tuple_size<Tuple>::value>&)
        {
        }
    };
} // namespace detail

    template<class Json, typename... E>
    struct json_type_traits<Json, std::tuple<E...>>
    {
    private:
        using helper = jsoncons::detail::json_tuple_helper<sizeof...(E), Json, std::tuple<E...>>;

    public:
        static bool is(const Json& j) noexcept
        {
            return helper::is(j);
        }
        
        static std::tuple<E...> as(const Json& j)
        {
            std::tuple<E...> buff;
            helper::as(buff, j);
            return buff;
        }
         
        static Json to_json(const std::tuple<E...>& val)
        {
            std::array<Json, sizeof...(E)> buf;
            helper::to_json(val, buf);
            return Json(typename Json::array(buf.begin(), buf.end()));
        }
    };

    template<class Json, class T1, class T2>
    struct json_type_traits<Json, std::pair<T1,T2>>
    {
    public:
        static bool is(const Json& j) noexcept
        {
            return j.is_array() && j.size() == 2;
        }
        
        static std::pair<T1,T2> as(const Json& j)
        {
            return std::make_pair<T1,T2>(j[0].template as<T1>(),j[1].template as<T2>());
        }
        
        static Json to_json(const std::pair<T1,T2>& val)
        {
            return Json(json_array_arg, { val.first, val.second });
        }
    };

    template<class Json, class Allocator>
    struct json_type_traits<Json, basic_byte_string<Allocator>>
    {
    public:
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            return j.is_byte_string();
        }
        
        static basic_byte_string<Allocator> as(const Json& j)
        { 
            return j.template as_byte_string<Allocator>();
        }
        
        static Json to_json(const basic_byte_string<Allocator>& val, 
                            const allocator_type& alloc = allocator_type())
        {
            return Json(val, semantic_tag::none, alloc);
        }
    };

    template<class Json, class ValueType>
    struct json_type_traits<Json, std::shared_ptr<ValueType>,
                            typename std::enable_if<!is_json_type_traits_declared<std::shared_ptr<ValueType>>::value &&
                                                    !std::is_polymorphic<ValueType>::value
    >::type>
    {
        static bool is(const Json& j) noexcept 
        {
            return j.is_null() || j.template is<ValueType>();
        }

        static std::shared_ptr<ValueType> as(const Json& j) 
        {
            return std::make_shared<ValueType>(j.template as<ValueType>());
        }

        static Json to_json(const std::shared_ptr<ValueType>& ptr) 
        {
            if (ptr.get() != nullptr) 
            {
                Json j(*ptr);
                return j;
            }
            else 
            {
                return Json::null();
            }
        }
    };

    template<class Json, class ValueType>
    struct json_type_traits<Json, std::unique_ptr<ValueType>,
                            typename std::enable_if<!is_json_type_traits_declared<std::unique_ptr<ValueType>>::value &&
                                                    !std::is_polymorphic<ValueType>::value
    >::type>
    {
        static bool is(const Json& j) noexcept 
        {
            return j.is_null() || j.template is<ValueType>();
        }

        static std::unique_ptr<ValueType> as(const Json& j) 
        {
            return jsoncons::make_unique<ValueType>(j.template as<ValueType>());
        }

        static Json to_json(const std::unique_ptr<ValueType>& ptr) 
        {
            if (ptr.get() != nullptr) 
            {
                Json j(*ptr);
                return j;
            }
            else 
            {
                return Json::null();
            }
        }
    };

    template<class Json, class T>
    struct json_type_traits<Json, jsoncons::optional<T>,
                            typename std::enable_if<!is_json_type_traits_declared<jsoncons::optional<T>>::value>::type>
    {
    public:
        static bool is(const Json& j) noexcept
        {
            return j.is_null() || j.template is<T>();
        }
        
        static jsoncons::optional<T> as(const Json& j)
        { 
            return j.is_null() ? jsoncons::optional<T>() : jsoncons::optional<T>(j.template as<T>());
        }
        
        static Json to_json(const jsoncons::optional<T>& val)
        {
            return val.has_value() ? Json(val.value()) : Json::null();
        }
    };

    template<class Json>
    struct json_type_traits<Json, byte_string_view>
    {
        typedef typename Json::allocator_type allocator_type;

    public:
        static bool is(const Json& j) noexcept
        {
            return j.is_byte_string_view();
        }
        
        static byte_string_view as(const Json& j)
        {
            return j.as_byte_string_view();
        }
        
        static Json to_json(const byte_string_view& val, const allocator_type& alloc = allocator_type())
        {
            return Json(val, semantic_tag::none, alloc);
        }
    };

    // basic_bignum

    template<class Json, class Allocator>
    struct json_type_traits<Json, basic_bignum<Allocator>>
    {
    public:
        static bool is(const Json& j) noexcept
        {
            switch (j.type())
            {
                case json_type::string_value:
                    return jsoncons::detail::is_base10(j.as_string_view().data(), j.as_string_view().length());
                case json_type::int64_value:
                case json_type::uint64_value:
                    return true;
                default:
                    return false;
            }
        }
        
        static basic_bignum<Allocator> as(const Json& j)
        {
            switch (j.type())
            {
                case json_type::string_value:
                    if (!jsoncons::detail::is_base10(j.as_string_view().data(), j.as_string_view().length()))
                    {
                        JSONCONS_THROW(json_runtime_error<std::domain_error>("Not a bignum"));
                    }
                    return basic_bignum<Allocator>(j.as_string_view().data(), j.as_string_view().length());
                case json_type::half_value:
                case json_type::double_value:
                    return basic_bignum<Allocator>(j.template as<double>());
                case json_type::int64_value:
                    return basic_bignum<Allocator>(j.template as<int64_t>());
                case json_type::uint64_value:
                    return basic_bignum<Allocator>(j.template as<uint64_t>());
                default:
                    JSONCONS_THROW(json_runtime_error<std::domain_error>("Not a bignum"));
            }
        }
        
        static Json to_json(const basic_bignum<Allocator>& val)
        {
            std::basic_string<typename Json::char_type> s;
            val.dump(s);
            return Json(s,semantic_tag::bigint);
        }
    };

    // std::valarray

    template<class Json, class T>
    struct json_type_traits<Json, std::valarray<T>>
    {
        typedef typename Json::allocator_type allocator_type;

        static bool is(const Json& j) noexcept
        {
            bool result = j.is_array();
            if (result)
            {
                for (auto e : j.array_range())
                {
                    if (!e.template is<T>())
                    {
                        result = false;
                        break;
                    }
                }
            }
            return result;
        }
        
        static std::valarray<T> as(const Json& j)
        {
            if (j.is_array())
            {
                std::valarray<T> v(j.size());
                for (size_t i = 0; i < j.size(); ++i)
                {
                    v[i] = j[i].template as<T>();
                }
                return v;
            }
            else
            {
                JSONCONS_THROW(ser_error(conversion_errc::json_not_array));
            }
        }
        
        static Json to_json(const std::valarray<T>& val)
        {
            Json j(json_array_arg);
            auto first = std::begin(val);
            auto last = std::end(val);
            size_t size = std::distance(first,last);
            j.reserve(size);
            for (auto it = first; it != last; ++it)
            {
                j.push_back(*it);
            }
            return j;
        } 

        static Json to_json(const std::valarray<T>& val, const allocator_type& alloc)
        {
            Json j(json_array_arg, alloc);
            auto first = std::begin(val);
            auto last = std::end(val);
            size_t size = std::distance(first,last);
            j.reserve(size);
            for (auto it = first; it != last; ++it)
            {
                j.push_back(*it);
            }
            return j;
        }
    };

} // jsoncons

#endif
