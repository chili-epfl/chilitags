#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_BINDTYPE_HXX_
#define _QITYPE_DETAILS_BINDTYPE_HXX_

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/bind.hpp>
#include <boost/any.hpp>

namespace qi
{
    namespace detail
    {
      // Support stuff for boost_bind_function_type

      class ignore{};

      // Just store an int and a type
      template<int I, typename P> struct MappingItem {};

      // IntFromMappingItem: Extract int from MappingItem or something else

      template<typename T> struct IntFromMappingItem
      {
        static const long value = 0;
      };

      template<int I, typename P>
      struct IntFromMappingItem<MappingItem<I, P> >
      {
        static const long value = I;
      };


      // ArgResolver: Take a function, an index, and a boost::_bi::list element
      // return ignore, or a MappingItem

      template<typename F, int P, typename bilistarg>
      struct ArgResolver
      {
      };

      template<typename F, int P, typename V>
      struct ArgResolver<F, P, boost::_bi::value<V> >
      {
        typedef ignore type;
      };

      template<typename F, int P, int I>
      struct ArgResolver<F, P, boost::arg<I> >
      {
        typedef MappingItem<I,
          typename boost::mpl::at_c<
            typename boost::function_types::parameter_types<F>::type,
            P
          >::type
        > type;
      };


      // ArgLess: Index comparison between MappingItems

      template<typename A, typename B> struct ArgLess
      {
        typedef boost::true_type type;
      };

      template<typename A, int I, typename B>
      struct ArgLess<A, MappingItem<I, B> >
      {
        typedef boost::true_type type;
      };

      template<typename A, int I, typename B>
      struct ArgLess<MappingItem<I, B>, A>
      {
        typedef boost::false_type type;
      };

      template<int I1, typename V1, int I2, typename V2>
      struct ArgLess<MappingItem<I1, V1>, MappingItem<I2, V2> >
      {
        typedef typename boost::mpl::less<boost::mpl::long_<I1>, boost::mpl::long_<I2> >::type type;
      };


      // MapItemIndexIs: By-index MappingItem find helper

      template<typename A, typename B>
      struct MapItemIndexIs
      {
        typedef typename boost::false_type type;
      };

      template<typename T, int B>
      struct MapItemIndexIs<MappingItem<B, T>, boost::mpl::long_<B> >
      {
        typedef typename boost::true_type type;
      };


      // ReorderMapping: Reorder a sequence of MappingItems by their id

      template<int I, typename Map>
      struct ReorderMapping
      {
        typedef typename boost::mpl::push_back<
          typename ReorderMapping<I-1, Map>::type,
          typename boost::mpl::deref<typename boost::mpl::find_if<
             Map,
             MapItemIndexIs<boost::mpl::_1, boost::mpl::long_<I> >
           >::type
           >::type>::type type;
      };
      template<typename Map>
      struct ReorderMapping<1, Map>
      {
        typedef boost::mpl::vector<
          typename boost::mpl::deref<typename boost::mpl::find_if<
             Map,
             MapItemIndexIs<boost::mpl::_1, boost::mpl::long_<1> >
             >::type>::type> type;
      };
      template<typename Map>
      struct ReorderMapping<0, Map>
      {
        typedef boost::mpl::vector<> type;
      };


      // MappingToType: get type of MappingItem, or boost::any

      template<typename T>
      struct MappingToType
      {
        typedef boost::any type;
      };
      template<typename T, int I>
      struct MappingToType<MappingItem<I, T> >
      {
        typedef T type;
      };


      // MappingBuilder: Invoke ArgResolver on all elements of a sequence

      template<int idx, typename F, typename V>
      struct MappingBuilder
      {
        typedef typename boost::mpl::push_back<
          typename MappingBuilder<idx - 1, F, V>::type,
          typename ArgResolver<F, idx, typename boost::mpl::at_c<V, idx>::type>::type
          >::type type;
      };

      template<typename F, typename V>
      struct MappingBuilder<0, F, V>
      {
        typedef typename boost::mpl::vector<
          typename ArgResolver<F, 0, typename boost::mpl::at_c<V, 0>::type>::type
          > type;
      };

      template<typename F, typename S>
      struct parameter_types_from_bilist_seq
      {
        typedef typename MappingBuilder<boost::mpl::size<S>::type::value-1, F, S>::type
        type;
      };

      template<typename T> struct BilistToSeq
      {
        typedef boost::mpl::vector<> type;
      };
      template<typename P1>
      struct BilistToSeq<boost::_bi::list1<P1> >
      {
        typedef typename boost::mpl::vector<P1> type;
      };
      template<typename P1, typename P2>
      struct BilistToSeq<boost::_bi::list2<P1, P2> >
      {
        typedef typename boost::mpl::vector<P1, P2> type;
      };
      template<typename P1, typename P2, typename P3>
      struct BilistToSeq<boost::_bi::list3<P1, P2, P3> >
      {
        typedef typename boost::mpl::vector<P1, P2, P3> type;
      };
      template<typename P1, typename P2, typename P3, typename P4>
      struct BilistToSeq<boost::_bi::list4<P1, P2, P3, P4> >
      {
        typedef typename boost::mpl::vector<P1, P2, P3, P4> type;
      };
      template<typename P1, typename P2, typename P3, typename P4, typename P5>
      struct BilistToSeq<boost::_bi::list5<P1, P2, P3, P4, P5> >
      {
        typedef typename boost::mpl::vector<P1, P2, P3, P4, P5> type;
      };

      template<typename F, typename BL>
      struct parameter_types
      {
        typedef typename BilistToSeq<BL>::type BLSeq;
        typedef typename parameter_types_from_bilist_seq<F, BLSeq>::type Mapping;
        // Mapping is a vector of nothing or pair<index, type>
        // Get max value
        typedef typename boost::mpl::deref<typename boost::mpl::max_element<Mapping, ArgLess<boost::mpl::_1, boost::mpl::_2> >::type>::type MaxArg;
        // Reorder it
        typedef typename ReorderMapping<IntFromMappingItem<MaxArg>::value, Mapping>::type Reordered;
        //typedef typename Reorder<Mapping, MaxArg>::type Reordered;
        // Replace MappingItem with the type, and void with any
        typedef typename boost::mpl::transform<Reordered, MappingToType<boost::mpl::_1> >::type type;
      };
    }

    template<typename T> struct boost_bind_result_type {};
    template<typename R, typename A, typename B>
    struct boost_bind_result_type<boost::_bi::bind_t<R, A, B> >
    {
      typedef R type;
    };

    template<typename T> struct boost_bind_parameter_types {};
    template<typename R, typename F, typename B>
    struct boost_bind_parameter_types<boost::_bi::bind_t<R, F, B> >
    {
      typedef typename detail::parameter_types<F, B>::type type;
    };

    /** Take as argument the result of a boost::bind, and return
     * A compatible function type
     */
    template<typename T> struct boost_bind_function_type
    {
      typedef typename boost::function_types::function_type<
        typename boost::mpl::push_front<
          typename boost_bind_parameter_types<T>::type,
          typename boost_bind_result_type<T>::type
          >::type
        >::type type;
      typedef typename boost::function_types::function_pointer<
        typename boost::mpl::push_front<
          typename boost_bind_parameter_types<T>::type,
          typename boost_bind_result_type<T>::type
          >::type
        >::type pointer_type;
    };
}

#endif  // _QITYPE_DETAILS_BINDTYPE_HXX_
