#pragma once
/*
 * Copyright (C) 2009-2012, Aldebaran Robotics.
 * Imported from urbi-sdk's libport.
 *
 */

#ifndef _QI_PREPROC_HPP_
#define _QI_PREPROC_HPP_

# include <boost/preprocessor/seq/for_each.hpp>
# include <boost/preprocessor/seq/remove.hpp>
# include <boost/preprocessor/seq/transform.hpp>

# define QI_MAP_HELPER(R, Macro, Elt) (Macro(Elt))
/// Return \a Seq, with \a Macro applied on every element.
# define QI_MAP(Macro, Seq)                                 \
  BOOST_PP_SEQ_FOR_EACH(QI_MAP_HELPER, Macro, Seq)

# define QI_APPLY_HELPER(R, Macro, Elt) Macro(Elt)
/// Apply \a Macro applied on every element of \a Seq.
# define QI_APPLY(Macro, Seq)                               \
  BOOST_PP_SEQ_FOR_EACH(QI_APPLY_HELPER, Macro, Seq)


# define QI_SEPARATE_HELPER(Elt) , Elt
/// Separate \a Seq with commas
# define QI_SEPARATE(Seq)                                          \
  BOOST_PP_SEQ_HEAD(Seq)                                                     \
  QI_APPLY(QI_SEPARATE_HELPER, BOOST_PP_SEQ_TAIL(Seq))

/// Separate \a Seq with \a Sep
# define QI_ENUM(Seq, Sep)                                         \
  BOOST_PP_SEQ_HEAD(Seq)                                                     \
  BOOST_PP_SEQ_FOR_EACH(QI_ENUM_HELPER, Sep, BOOST_PP_SEQ_TAIL(Seq))
# define QI_ENUM_HELPER(Data, Sep, Elt) Sep Elt

/// Separate \a Seq with \a LSep for the last separator and \a Sep everywhere else.
/// Typically: "a, b, c, d and e".
# define QI_ENUM_PRETTY(Seq, Sep, LSep)                            \
  BOOST_PP_CAT(                                                         \
    QI_ENUM_PRETTY_,                                               \
    BOOST_PP_IF(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(Seq)), SEVERAL, ONE))    \
  (Seq, Sep, LSep)
# define QI_ENUM_PRETTY_ONE(Seq, Sep, LSep)        \
  BOOST_PP_SEQ_HEAD(Seq)
# define QI_ENUM_PRETTY_SEVERAL(Seq, Sep, LSep)    \
  QI_ENUM(QI_RTAIL(Seq), Sep) LSep QI_RHEAD(Seq)

/// The last element element of the sequence (reverse head)
# define QI_RHEAD(Seq) BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(Seq)), Seq)
/// The sequence minus the last element (reverse tail)
# define QI_RTAIL(Seq) BOOST_PP_SEQ_REMOVE(Seq, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(Seq)))

/// Concatenate the two arguments.
# ifdef _MSC_VER

#  define QI_CAT(A, B) QI_CAT_0(A, B)
/*
#!/usr/bin/python

for i in range(0, 32):
  print '#  define QI_CAT_%s(A, B) QI_CAT_%s(A, B)' % (i, i + 1)
*/
#  define QI_CAT_0(A, B) QI_CAT_1(A, B)
#  define QI_CAT_1(A, B) QI_CAT_2(A, B)
#  define QI_CAT_2(A, B) QI_CAT_3(A, B)
#  define QI_CAT_3(A, B) QI_CAT_4(A, B)
#  define QI_CAT_4(A, B) QI_CAT_5(A, B)
#  define QI_CAT_5(A, B) QI_CAT_6(A, B)
#  define QI_CAT_6(A, B) QI_CAT_7(A, B)
#  define QI_CAT_7(A, B) QI_CAT_8(A, B)
#  define QI_CAT_8(A, B) QI_CAT_9(A, B)
#  define QI_CAT_9(A, B) QI_CAT_10(A, B)
#  define QI_CAT_10(A, B) QI_CAT_11(A, B)
#  define QI_CAT_11(A, B) QI_CAT_12(A, B)
#  define QI_CAT_12(A, B) QI_CAT_13(A, B)
#  define QI_CAT_13(A, B) QI_CAT_14(A, B)
#  define QI_CAT_14(A, B) QI_CAT_15(A, B)
#  define QI_CAT_15(A, B) QI_CAT_16(A, B)
#  define QI_CAT_16(A, B) QI_CAT_17(A, B)
#  define QI_CAT_17(A, B) QI_CAT_18(A, B)
#  define QI_CAT_18(A, B) QI_CAT_19(A, B)
#  define QI_CAT_19(A, B) QI_CAT_20(A, B)
#  define QI_CAT_20(A, B) QI_CAT_21(A, B)
#  define QI_CAT_21(A, B) QI_CAT_22(A, B)
#  define QI_CAT_22(A, B) QI_CAT_23(A, B)
#  define QI_CAT_23(A, B) QI_CAT_24(A, B)
#  define QI_CAT_24(A, B) QI_CAT_25(A, B)
#  define QI_CAT_25(A, B) QI_CAT_26(A, B)
#  define QI_CAT_26(A, B) QI_CAT_27(A, B)
#  define QI_CAT_27(A, B) QI_CAT_28(A, B)
#  define QI_CAT_28(A, B) QI_CAT_29(A, B)
#  define QI_CAT_29(A, B) QI_CAT_30(A, B)
#  define QI_CAT_30(A, B) QI_CAT_31(A, B)
#  define QI_CAT_31(A, B) A ## B
# else
#  define QI_CAT(A, B) QI_CAT_(A, B)
#  define QI_CAT_(A, B) A ## B
# endif

/// __FILE__:__LINE__ as a string.
# define __HERE                             \
  __FILE__ ":" BOOST_PP_STRINGIZE(__LINE__)

# define QI_ID(...) __VA_ARGS__

# define QI_DELAY(X) X

# define QI_COMMA ,

# define QI_WRAP(...) (__VA_ARGS__)

# define QI_UNWRAP(...) QI_ID __VA_ARGS__


/*
#!/usr/bin/python

def gen(n):
  print '#define QI_LIST_BUILD_%(max)s(%(formals)s IGNORED) %(list)s' % {
    'formals' : ''.join(map(lambda i: 'A%s,' % i, range(n))),
    'list'    : ''.join(map(lambda i: '(A%s)' % i, range(n))),
    'max'     : n,
    }

for i in range(10):
  gen(i)
*/

#define QI_LIST_BUILD_0( IGNORED)
#define QI_LIST_BUILD_1(A0, IGNORED)       \
  (A0)
#define QI_LIST_BUILD_2(A0,A1, IGNORED)    \
  (A0)(A1)
#define QI_LIST_BUILD_3(A0,A1,A2, IGNORED) \
  (A0)(A1)(A2)
#define QI_LIST_BUILD_4(A0,A1,A2,A3, IGNORED)      \
  (A0)(A1)(A2)(A3)
#define QI_LIST_BUILD_5(A0,A1,A2,A3,A4, IGNORED)   \
  (A0)(A1)(A2)(A3)(A4)
#define QI_LIST_BUILD_6(A0,A1,A2,A3,A4,A5, IGNORED)        \
  (A0)(A1)(A2)(A3)(A4)(A5)
#define QI_LIST_BUILD_7(A0,A1,A2,A3,A4,A5,A6, IGNORED)     \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)
#define QI_LIST_BUILD_8(A0,A1,A2,A3,A4,A5,A6,A7, IGNORED)  \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)
#define QI_LIST_BUILD_9(A0,A1,A2,A3,A4,A5,A6,A7,A8, IGNORED)       \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)
#define QI_LIST_BUILD_10(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9, IGNORED)   \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)
#define QI_LIST_BUILD_11(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)
#define QI_LIST_BUILD_12(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)
#define QI_LIST_BUILD_13(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)
#define QI_LIST_BUILD_14(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)
#define QI_LIST_BUILD_15(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)
#define QI_LIST_BUILD_16(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)
#define QI_LIST_BUILD_17(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)
#define QI_LIST_BUILD_18(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)
#define QI_LIST_BUILD_19(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)
#define QI_LIST_BUILD_20(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)
#define QI_LIST_BUILD_21(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)
#define QI_LIST_BUILD_22(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)(A21)
#define QI_LIST_BUILD_23(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)(A21)(A22)
#define QI_LIST_BUILD_24(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22,A23, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)(A21)(A22)(A23)
#define QI_LIST_BUILD_25(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22,A23,A24, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)(A21)(A22)(A23)(A24)
#define QI_LIST_BUILD_26(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)(A21)(A22)(A23)(A24)(A25)
#define QI_LIST_BUILD_27(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,A26, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)(A21)(A22)(A23)(A24)(A25)(A26)
#define QI_LIST_BUILD_28(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,A26,A27, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)(A21)(A22)(A23)(A24)(A25)(A26)(A27)
#define QI_LIST_BUILD_29(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,A26,A27,A28, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)(A21)(A22)(A23)(A24)(A25)(A26)(A27)(A28)
#define QI_LIST_BUILD_30(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,A26,A27,A28,A29, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)(A21)(A22)(A23)(A24)(A25)(A26)(A27)(A28)(A29)
#define QI_LIST_BUILD_31(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,A26,A27,A28,A29,A30, IGNORED) \
  (A0)(A1)(A2)(A3)(A4)(A5)(A6)(A7)(A8)(A9)(A10)(A11)(A12)(A13)(A14)(A15)(A16)(A17)(A18)(A19)(A20)(A21)(A22)(A23)(A24)(A25)(A26)(A27)(A28)(A29)(A30)

# ifdef _MSC_VER
#  define QI_LIST_VASIZE_HELPER1(...)                                \
  QI_DELAY(QI_LIST_VASIZE_HELPER)##2(__VA_ARGS__, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
# else
#  define QI_LIST_VASIZE_HELPER1(...)                                \
  QI_LIST_VASIZE_HELPER2(__VA_ARGS__, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
# endif
# define QI_LIST_VASIZE_HELPER2(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, ...) \
  A32

# define QI_LIST_VASIZE(List)                                    \
  QI_LIST_VASIZE_HELPER1 List

#define QI_LIST_HELPER(M, A) M A

#define QI_LIST(...)                                               \
  QI_LIST_HELPER(                                                  \
  QI_CAT(QI_LIST_BUILD_, QI_LIST_VASIZE((__VA_ARGS__))), \
  (__VA_ARGS__))

# define QI_LIST_SIZE(List) BOOST_PP_SEQ_SIZE(List)

# define QI_LIST_EMPTY_0 QI_TRUE
# define QI_LIST_EMPTY_1 QI_FALSE
# define QI_LIST_EMPTY_2 QI_FALSE
# define QI_LIST_EMPTY_3 QI_FALSE
# define QI_LIST_EMPTY_4 QI_FALSE
# define QI_LIST_EMPTY_5 QI_FALSE
# define QI_LIST_EMPTY_6 QI_FALSE
# define QI_LIST_EMPTY_7 QI_FALSE
# define QI_LIST_EMPTY_8 QI_FALSE
# define QI_LIST_EMPTY_9 QI_FALSE
# define QI_LIST_EMPTY_10 QI_FALSE
# define QI_LIST_EMPTY_11 QI_FALSE
# define QI_LIST_EMPTY_12 QI_FALSE
# define QI_LIST_EMPTY_13 QI_FALSE
# define QI_LIST_EMPTY_14 QI_FALSE
# define QI_LIST_EMPTY_15 QI_FALSE
# define QI_LIST_EMPTY_16 QI_FALSE
# define QI_LIST_EMPTY_17 QI_FALSE
# define QI_LIST_EMPTY_18 QI_FALSE
# define QI_LIST_EMPTY_19 QI_FALSE
# define QI_LIST_EMPTY_20 QI_FALSE
# define QI_LIST_EMPTY_21 QI_FALSE
# define QI_LIST_EMPTY_22 QI_FALSE
# define QI_LIST_EMPTY_23 QI_FALSE
# define QI_LIST_EMPTY_24 QI_FALSE
# define QI_LIST_EMPTY_25 QI_FALSE
# define QI_LIST_EMPTY_26 QI_FALSE
# define QI_LIST_EMPTY_27 QI_FALSE
# define QI_LIST_EMPTY_28 QI_FALSE
# define QI_LIST_EMPTY_29 QI_FALSE
# define QI_LIST_EMPTY_30 QI_FALSE
# define QI_LIST_EMPTY_31 QI_FALSE
# define QI_LIST_EMPTY(List) QI_CAT(QI_LIST_EMPTY_, QI_LIST_SIZE(List))

# define QI_LIST_HEAD(List) BOOST_PP_SEQ_HEAD(List)

# define QI_LIST_TAIL(List) BOOST_PP_SEQ_TAIL(List)

# define QI_LIST_MAP_HELPER(Unused, Macro, Elt)    \
  Macro(Elt)
# define QI_LIST_MAP(Macro, List)                          \
  BOOST_PP_SEQ_TRANSFORM(QI_LIST_MAP_HELPER, Macro, List)

# define QI_LIST_MAP_AUX_HELPER(Unused, Aux, Elt)                  \
  BOOST_PP_TUPLE_ELEM(2, 0, Aux)(Elt, BOOST_PP_TUPLE_ELEM(2, 1, Aux))
# define QI_LIST_MAP_AUX(Macro, List, Aux)                         \
  BOOST_PP_SEQ_TRANSFORM(QI_LIST_MAP_AUX_HELPER, (Macro, Aux), List)

# define QI_LIST_APPLY_HELPER(Unused, Macro, Elt)  \
  Macro(Elt)
# define QI_LIST_APPLY(Macro, List)                        \
  BOOST_PP_SEQ_FOR_EACH(QI_LIST_APPLY_HELPER, Macro, List)

# define QI_LIST_APPLY_ARGS_HELPER(Unused, Macro, Elt)     \
  Macro Elt
# define QI_LIST_APPLY_ARGS(Macro, List)                           \
  BOOST_PP_SEQ_FOR_EACH(QI_LIST_APPLY_ARGS_HELPER, Macro, List)

# define QI_LIST_APPLY_AUX_HELPER(Unused, Aux, Elt)                \
  BOOST_PP_TUPLE_ELEM(2, 0, Aux)(Elt, BOOST_PP_TUPLE_ELEM(2, 1, Aux))
# define QI_LIST_APPLY_AUX(Macro, List, Aux)                       \
  BOOST_PP_SEQ_FOR_EACH(QI_LIST_APPLY_AUX_HELPER, (Macro, Aux), List)

/*
#!/usr/bin/python

def gen(n):
  args = {'n': n, 'n_1': n - 1,}
  print '# define QI_LIST_NTH_%(n)s(List) BOOST_PP_CAT(QI_LIST_NTH_%(n)s_, QI_LIST_EMPTY(List))(List)' % args
  print '# define QI_LIST_NTH_%(n)s_QI_TRUE(List)' % args
  if n != 0:
    print '# define QI_LIST_NTH_%(n)s_QI_FALSE(List) QI_LIST_NTH_%(n_1)s(QI_LIST_TAIL(List))' %args

for i in range(0, 10):
  gen(i)
*/

# define QI_LIST_NTH_0(List) BOOST_PP_CAT(QI_LIST_NTH_0_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_0_QI_TRUE(List)
# define QI_LIST_NTH_1(List) BOOST_PP_CAT(QI_LIST_NTH_1_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_1_QI_TRUE(List)
# define QI_LIST_NTH_1_QI_FALSE(List) QI_LIST_NTH_0(QI_LIST_TAIL(List))
# define QI_LIST_NTH_2(List) BOOST_PP_CAT(QI_LIST_NTH_2_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_2_QI_TRUE(List)
# define QI_LIST_NTH_2_QI_FALSE(List) QI_LIST_NTH_1(QI_LIST_TAIL(List))
# define QI_LIST_NTH_3(List) BOOST_PP_CAT(QI_LIST_NTH_3_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_3_QI_TRUE(List)
# define QI_LIST_NTH_3_QI_FALSE(List) QI_LIST_NTH_2(QI_LIST_TAIL(List))
# define QI_LIST_NTH_4(List) BOOST_PP_CAT(QI_LIST_NTH_4_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_4_QI_TRUE(List)
# define QI_LIST_NTH_4_QI_FALSE(List) QI_LIST_NTH_3(QI_LIST_TAIL(List))
# define QI_LIST_NTH_5(List) BOOST_PP_CAT(QI_LIST_NTH_5_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_5_QI_TRUE(List)
# define QI_LIST_NTH_5_QI_FALSE(List) QI_LIST_NTH_4(QI_LIST_TAIL(List))
# define QI_LIST_NTH_6(List) BOOST_PP_CAT(QI_LIST_NTH_6_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_6_QI_TRUE(List)
# define QI_LIST_NTH_6_QI_FALSE(List) QI_LIST_NTH_5(QI_LIST_TAIL(List))
# define QI_LIST_NTH_7(List) BOOST_PP_CAT(QI_LIST_NTH_7_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_7_QI_TRUE(List)
# define QI_LIST_NTH_7_QI_FALSE(List) QI_LIST_NTH_6(QI_LIST_TAIL(List))
# define QI_LIST_NTH_8(List) BOOST_PP_CAT(QI_LIST_NTH_8_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_8_QI_TRUE(List)
# define QI_LIST_NTH_8_QI_FALSE(List) QI_LIST_NTH_7(QI_LIST_TAIL(List))
# define QI_LIST_NTH_9(List) BOOST_PP_CAT(QI_LIST_NTH_9_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_9_QI_TRUE(List)
# define QI_LIST_NTH_9_QI_FALSE(List) QI_LIST_NTH_8(QI_LIST_TAIL(List))
# define QI_LIST_NTH_10(List) BOOST_PP_CAT(QI_LIST_NTH_10_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_10_QI_TRUE(List)
# define QI_LIST_NTH_10_QI_FALSE(List) QI_LIST_NTH_9(QI_LIST_TAIL(List))
# define QI_LIST_NTH_11(List) BOOST_PP_CAT(QI_LIST_NTH_11_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_11_QI_TRUE(List)
# define QI_LIST_NTH_11_QI_FALSE(List) QI_LIST_NTH_10(QI_LIST_TAIL(List))
# define QI_LIST_NTH_12(List) BOOST_PP_CAT(QI_LIST_NTH_12_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_12_QI_TRUE(List)
# define QI_LIST_NTH_12_QI_FALSE(List) QI_LIST_NTH_11(QI_LIST_TAIL(List))
# define QI_LIST_NTH_13(List) BOOST_PP_CAT(QI_LIST_NTH_13_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_13_QI_TRUE(List)
# define QI_LIST_NTH_13_QI_FALSE(List) QI_LIST_NTH_12(QI_LIST_TAIL(List))
# define QI_LIST_NTH_14(List) BOOST_PP_CAT(QI_LIST_NTH_14_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_14_QI_TRUE(List)
# define QI_LIST_NTH_14_QI_FALSE(List) QI_LIST_NTH_13(QI_LIST_TAIL(List))
# define QI_LIST_NTH_15(List) BOOST_PP_CAT(QI_LIST_NTH_15_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_15_QI_TRUE(List)
# define QI_LIST_NTH_15_QI_FALSE(List) QI_LIST_NTH_14(QI_LIST_TAIL(List))
# define QI_LIST_NTH_16(List) BOOST_PP_CAT(QI_LIST_NTH_16_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_16_QI_TRUE(List)
# define QI_LIST_NTH_16_QI_FALSE(List) QI_LIST_NTH_15(QI_LIST_TAIL(List))
# define QI_LIST_NTH_17(List) BOOST_PP_CAT(QI_LIST_NTH_17_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_17_QI_TRUE(List)
# define QI_LIST_NTH_17_QI_FALSE(List) QI_LIST_NTH_16(QI_LIST_TAIL(List))
# define QI_LIST_NTH_18(List) BOOST_PP_CAT(QI_LIST_NTH_18_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_18_QI_TRUE(List)
# define QI_LIST_NTH_18_QI_FALSE(List) QI_LIST_NTH_17(QI_LIST_TAIL(List))
# define QI_LIST_NTH_19(List) BOOST_PP_CAT(QI_LIST_NTH_19_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_19_QI_TRUE(List)
# define QI_LIST_NTH_19_QI_FALSE(List) QI_LIST_NTH_18(QI_LIST_TAIL(List))
# define QI_LIST_NTH_20(List) BOOST_PP_CAT(QI_LIST_NTH_20_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_20_QI_TRUE(List)
# define QI_LIST_NTH_20_QI_FALSE(List) QI_LIST_NTH_19(QI_LIST_TAIL(List))
# define QI_LIST_NTH_21(List) BOOST_PP_CAT(QI_LIST_NTH_21_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_21_QI_TRUE(List)
# define QI_LIST_NTH_21_QI_FALSE(List) QI_LIST_NTH_20(QI_LIST_TAIL(List))
# define QI_LIST_NTH_22(List) BOOST_PP_CAT(QI_LIST_NTH_22_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_22_QI_TRUE(List)
# define QI_LIST_NTH_22_QI_FALSE(List) QI_LIST_NTH_21(QI_LIST_TAIL(List))
# define QI_LIST_NTH_23(List) BOOST_PP_CAT(QI_LIST_NTH_23_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_23_QI_TRUE(List)
# define QI_LIST_NTH_23_QI_FALSE(List) QI_LIST_NTH_22(QI_LIST_TAIL(List))
# define QI_LIST_NTH_24(List) BOOST_PP_CAT(QI_LIST_NTH_24_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_24_QI_TRUE(List)
# define QI_LIST_NTH_24_QI_FALSE(List) QI_LIST_NTH_23(QI_LIST_TAIL(List))
# define QI_LIST_NTH_25(List) BOOST_PP_CAT(QI_LIST_NTH_25_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_25_QI_TRUE(List)
# define QI_LIST_NTH_25_QI_FALSE(List) QI_LIST_NTH_24(QI_LIST_TAIL(List))
# define QI_LIST_NTH_26(List) BOOST_PP_CAT(QI_LIST_NTH_26_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_26_QI_TRUE(List)
# define QI_LIST_NTH_26_QI_FALSE(List) QI_LIST_NTH_25(QI_LIST_TAIL(List))
# define QI_LIST_NTH_27(List) BOOST_PP_CAT(QI_LIST_NTH_27_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_27_QI_TRUE(List)
# define QI_LIST_NTH_27_QI_FALSE(List) QI_LIST_NTH_26(QI_LIST_TAIL(List))
# define QI_LIST_NTH_28(List) BOOST_PP_CAT(QI_LIST_NTH_28_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_28_QI_TRUE(List)
# define QI_LIST_NTH_28_QI_FALSE(List) QI_LIST_NTH_27(QI_LIST_TAIL(List))
# define QI_LIST_NTH_29(List) BOOST_PP_CAT(QI_LIST_NTH_29_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_29_QI_TRUE(List)
# define QI_LIST_NTH_29_QI_FALSE(List) QI_LIST_NTH_28(QI_LIST_TAIL(List))
# define QI_LIST_NTH_30(List) BOOST_PP_CAT(QI_LIST_NTH_30_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_30_QI_TRUE(List)
# define QI_LIST_NTH_30_QI_FALSE(List) QI_LIST_NTH_29(QI_LIST_TAIL(List))
# define QI_LIST_NTH_31(List) BOOST_PP_CAT(QI_LIST_NTH_31_, QI_LIST_EMPTY(List))(List)
# define QI_LIST_NTH_31_QI_TRUE(List)
# define QI_LIST_NTH_31_QI_FALSE(List) QI_LIST_NTH_30(QI_LIST_TAIL(List))

# define QI_LIST_NTH_0_QI_FALSE(List) QI_LIST_HEAD(List)
# define QI_LIST_NTH(Nth, List) BOOST_PP_CAT(QI_LIST_NTH_, Nth)(List)

# define QI_LIST_FLATTEN(List) QI_LIST_SEP(List, )

# define QI_LIST_SEP_HELPER(Elt, Sep)      \
  QI_UNWRAP(Sep) Elt
# define QI_LIST_SEP_QI_FALSE(List, Sep)                      \
  QI_LIST_HEAD(List)                                               \
  QI_LIST_APPLY_AUX(QI_LIST_SEP_HELPER, QI_LIST_TAIL(List), Sep)
# define QI_LIST_SEP_QI_TRUE(List, Sep)
# define QI_LIST_SEP(List, Sep)                                    \
  QI_CAT(QI_LIST_SEP_,                                        \
              QI_LIST_EMPTY(List))(List, QI_WRAP(Sep))

# define QI_LIST_ARG_HELPER(Macro, Args)   \
  Macro Args
# define QI_LIST_ARG(Macro, List)                                  \
  QI_LIST_ARG_HELPER(Macro, (QI_LIST_SEP(List, QI_COMMA)))

/// Call Macro(useless, Arg, elem) for each elem (extra argument).
#define QI_VAARGS_APPLY(Macro, Arg, ...)           \
  BOOST_PP_SEQ_FOR_EACH(Macro, Arg,                     \
                        QI_LIST(__VA_ARGS__,))

#define _QI_OR_00 0
#define _QI_OR_01 1
#define _QI_OR_10 1
#define _QI_OR_11 1
#define _QI_OR_I1(a, b) BOOST_PP_CAT(BOOST_PP_CAT(_QI_OR_, a), b)
#define _QI_OR_I2(a, b) _QI_OR_I1(a, b)
#define _QI_OR_I3(a, b) _QI_OR_I2(a, b)
#define _QI_OR_I4(a, b) _QI_OR_I3(a, b)
#define QI_OR(a, b) _QI_OR_I4(a, b)

#define _QI_IS_EMPTY_HELPER__ a,b
#define _QI_IS_ONE_HELPER__1 a,b

// To suppress a VCXX warning, the two macro below must be called with CAT(_, arg)
// otherwise due to evaluation ordering, code ends up calling QI_IS_ONE() which
// triggers a warning

//@return 1 if a is defined to 1, 0 otherwise. Must be called with CAT(_, a)
#define _QI_IS_ONE(a) QI_LIST_VASIZE((BOOST_PP_CAT(_QI_IS_ONE_HELPER_, a)))
//@return 1 if a is defined to empty, 0 otherwise. Must be called with CAT(_, a)
#define _QI_IS_EMPTY(a) QI_LIST_VASIZE((BOOST_PP_CAT(_QI_IS_EMPTY_HELPER, BOOST_PP_CAT(_, a))))


//@return 1 if a is defined to empty or 1. Return 0 otherwise. Must be called with CAT(_, a)
#define _QI_IS_ONE_OR_EMPTY(a) \
  QI_OR(_QI_IS_EMPTY(a), _QI_IS_ONE(a))


#define _QI_GEN_ARGTYPE(z,n,_) BOOST_PP_COMMA_IF(n) P ## n
#define _QI_GEN_ARGDECL(z,n,_) BOOST_PP_COMMA_IF(n) P ## n p##n
#define _QI_GEN_ARGDECLSAMETYPE(z,n,t) BOOST_PP_COMMA_IF(n) t p##n
#define _QI_GEN_ARGUSE(z,n,_) BOOST_PP_COMMA_IF(n) p##n
#define _QI_GEN_ARGTYPEDECL(z, n, _) BOOST_PP_COMMA_IF(n) typename P##n

#define _QI_GEN_PREPOST(z, n, prepost) BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, prepost), n) BOOST_PP_SEQ_ELEM(1, prepost)
#define _QI_GEN_PREPOST2(z, n, prepost) BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, prepost), n) BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1, prepost), n) BOOST_PP_SEQ_ELEM(2, prepost)

// pre 0 post pre 1 post pre 2 post...
#define QI_GEN_PREPOST(n, pre, post)  BOOST_PP_REPEAT(n, _QI_GEN_PREPOST, (pre)(post))
// pre 0 mid 0 post pre 1 mid 1 post ...
#define QI_GEN_PREPOST2(n, pre, mid, post)  BOOST_PP_REPEAT(n, _QI_GEN_PREPOST2, (pre)(mid)(post))
// P0, P1, ...
#define QI_GEN_ARGSTYPE(n) BOOST_PP_REPEAT(n, _QI_GEN_ARGTYPE, _)
// P0 p0, P1 p1, ...
#define QI_GEN_ARGSDECL(n) BOOST_PP_REPEAT(n, _QI_GEN_ARGDECL, _)
// p0, p1, p2 ...
#define QI_GEN_ARGSUSE(n) BOOST_PP_REPEAT(n, _QI_GEN_ARGUSE, _)
// typename P0, typename P1...
#define QI_GEN_ARGSTYPEDECL(n) BOOST_PP_REPEAT(n, _QI_GEN_ARGTYPEDECL, _)
// t p0, t p1...
#define QI_GEN_ARGSDECLSAMETYPE(n, t) BOOST_PP_REPEAT(n, _QI_GEN_ARGDECLSAMETYPE, t)


#define _QI_GEN(z, n, f) f(n, QI_GEN_ARGSTYPEDECL(n), QI_GEN_ARGSTYPE(n), QI_GEN_ARGSDECL(n), QI_GEN_ARGSUSE(n), BOOST_PP_COMMA_IF(n))

// invoke f(n, argtypedecl, argstype, argsdecl, argsuses, comma_or_empty) for n in [0, 10]
#define QI_GEN(f) BOOST_PP_REPEAT(10, _QI_GEN, f)
#define QI_GEN_RANGE(f, max) BOOST_PP_REPEAT(max, _QI_GEN, f)

// Evaluate to empty or 'template<' depending on wheter args is empty or a comma.
#define QI_GEN_MAYBE_TEMPLATE_OPEN(...) \
  QI_CAT(_QI_GEN_MAYBE_TEMPLATE_OPEN_, QI_LIST_VASIZE((__VA_ARGS__)))
#define QI_GEN_MAYBE_TEMPLATE_CLOSE(...) \
  QI_CAT(_QI_GEN_MAYBE_TEMPLATE_CLOSE_, QI_LIST_VASIZE((__VA_ARGS__)))

#define QI_PAIR_FIRST(x) QI_DELAY(_QI_PAIR_FIRST)x
#define QI_PAIR_SECOND(x) QI_DELAY(_QI_PAIR_SECOND)x
#define _QI_PAIR_FIRST(x, ...) x
#define _QI_PAIR_SECOND(x, y) y
#define _QI_GEN_MAYBE_TEMPLATE_OPEN_1 template<
#define _QI_GEN_MAYBE_TEMPLATE_OPEN_0
#define _QI_GEN_MAYBE_TEMPLATE_CLOSE_1 >
#define _QI_GEN_MAYBE_TEMPLATE_CLOSE_0
// Return i+1 as a symbol
#define QI_GEN_SYMINC(i) BOOST_PP_CAT(_QI_GEN_SYMINC_, i)
#define _QI_GEN_SYMINC_9 10
#define _QI_GEN_SYMINC_8 9
#define _QI_GEN_SYMINC_7 8
#define _QI_GEN_SYMINC_6 7
#define _QI_GEN_SYMINC_5 6
#define _QI_GEN_SYMINC_4 5
#define _QI_GEN_SYMINC_3 4
#define _QI_GEN_SYMINC_2 3
#define _QI_GEN_SYMINC_1 2
#define _QI_GEN_SYMINC_0 1

#define _QI_IF_QI_TRUE(a) a
#define _QI_IF_QI_FALSE(a)
#define _QI_NIF_QI_TRUE(a)
#define _QI_NIF_QI_FALSE(a) a



#define QI_01_TO_TRUEFALSE(v) BOOST_PP_CAT(_QI_01_TO_TRUEFALSE_,v)
#define _QI_01_TO_TRUEFALSE_0 QI_FALSE
#define _QI_01_TO_TRUEFALSE_1 QI_TRUE

# ifdef _MSC_VER
/* Sometimes when bouncing __VA_ARGS__ around you end up with all args in the same, so use a delay-trick
*/
#define __QI_VAARGS_MAP_0(Macro, Arg, elem, ...)   Macro(0, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##1(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_1(Macro, Arg, elem, ...) , Macro(1, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##2(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_2(Macro, Arg, elem, ...) , Macro(2, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##3(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_3(Macro, Arg, elem, ...) , Macro(3, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##4(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_4(Macro, Arg, elem, ...) , Macro(4, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##5(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_5(Macro, Arg, elem, ...) , Macro(5, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##6(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_6(Macro, Arg, elem, ...) , Macro(6, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##7(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_7(Macro, Arg, elem, ...) , Macro(7, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##8(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_8(Macro, Arg, elem, ...) , Macro(8, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##9(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_9(Macro, Arg, elem, ...) , Macro(9, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##10(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_10(Macro, Arg, elem, ...) , Macro(10, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##11(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_11(Macro, Arg, elem, ...) , Macro(11, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##12(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_12(Macro, Arg, elem, ...) , Macro(12, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##13(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_13(Macro, Arg, elem, ...) , Macro(13, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##14(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_14(Macro, Arg, elem, ...) , Macro(14, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##15(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_15(Macro, Arg, elem, ...) , Macro(15, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##16(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_16(Macro, Arg, elem, ...) , Macro(16, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##17(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_17(Macro, Arg, elem, ...) , Macro(17, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##18(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_18(Macro, Arg, elem, ...) , Macro(18, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##19(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_19(Macro, Arg, elem, ...) , Macro(19, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##20(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_20(Macro, Arg, elem, ...) , Macro(20, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##21(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_21(Macro, Arg, elem, ...) , Macro(21, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##22(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_22(Macro, Arg, elem, ...) , Macro(22, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##23(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_23(Macro, Arg, elem, ...) , Macro(23, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##24(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_24(Macro, Arg, elem, ...) , Macro(24, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##25(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_25(Macro, Arg, elem, ...) , Macro(25, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##26(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_26(Macro, Arg, elem, ...) , Macro(26, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##27(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_27(Macro, Arg, elem, ...) , Macro(27, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##28(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_28(Macro, Arg, elem, ...) , Macro(28, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##29(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_29(Macro, Arg, elem, ...) , Macro(29, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##30(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_30(Macro, Arg, elem, ...) , Macro(30, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##31(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_31(Macro, Arg, elem, ...) , Macro(31, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##32(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_32(Macro, Arg, elem, ...) , Macro(32, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(QI_DELAY(__QI_VAARGS_MAP_)##33(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_33(Macro, Arg, elem, ...) , Macro(33, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(TOO_MANY_ARGUMENTS)

#define __QI_VAARGS_EMPTY(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, ...) QI_01_TO_TRUEFALSE(p20)

// QI_TRUE if __VA_ARGS__ has *no comma*, QI_FALSE else
#define QI_VAARGS_EMPTY(...) QI_DELAY(__QI_VAARGS_)##EMPTY(__VA_ARGS__, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0,1,1)
// expand to Macro(0, Arg, p0), Macro(1, Arg, p1), ... , Macro(N, Arg, pN)
#define QI_VAARGS_MAP(Macro, Arg, ...) \
   QI_DELAY(__QI_VAARGS_MAP_)##0(Macro, Arg,  __VA_ARGS__,)

#else

#define __QI_VAARGS_MAP_0(Macro, Arg, elem, ...)   Macro(0, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_1(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_1(Macro, Arg, elem, ...) , Macro(1, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_2(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_2(Macro, Arg, elem, ...) , Macro(2, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_3(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_3(Macro, Arg, elem, ...) , Macro(3, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_4(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_4(Macro, Arg, elem, ...) , Macro(4, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_5(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_5(Macro, Arg, elem, ...) , Macro(5, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_6(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_6(Macro, Arg, elem, ...) , Macro(6, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_7(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_7(Macro, Arg, elem, ...) , Macro(7, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_8(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_8(Macro, Arg, elem, ...) , Macro(8, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_9(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_9(Macro, Arg, elem, ...) , Macro(9, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_10(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_10(Macro, Arg, elem, ...) , Macro(10, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_11(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_11(Macro, Arg, elem, ...) , Macro(11, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_12(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_12(Macro, Arg, elem, ...) , Macro(12, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_13(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_13(Macro, Arg, elem, ...) , Macro(13, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_14(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_14(Macro, Arg, elem, ...) , Macro(14, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_15(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_15(Macro, Arg, elem, ...) , Macro(15, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_16(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_16(Macro, Arg, elem, ...) , Macro(16, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_17(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_17(Macro, Arg, elem, ...) , Macro(17, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_18(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_18(Macro, Arg, elem, ...) , Macro(18, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_19(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_19(Macro, Arg, elem, ...) , Macro(19, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_20(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_20(Macro, Arg, elem, ...) , Macro(20, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_21(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_21(Macro, Arg, elem, ...) , Macro(21, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_22(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_22(Macro, Arg, elem, ...) , Macro(22, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_23(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_23(Macro, Arg, elem, ...) , Macro(23, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_24(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_24(Macro, Arg, elem, ...) , Macro(24, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_25(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_25(Macro, Arg, elem, ...) , Macro(25, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_26(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_26(Macro, Arg, elem, ...) , Macro(26, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_27(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_27(Macro, Arg, elem, ...) , Macro(27, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_28(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_28(Macro, Arg, elem, ...) , Macro(28, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_29(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_29(Macro, Arg, elem, ...) , Macro(29, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_30(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_30(Macro, Arg, elem, ...) , Macro(30, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_31(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_31(Macro, Arg, elem, ...) , Macro(31, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_32(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_32(Macro, Arg, elem, ...) , Macro(32, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(__QI_VAARGS_MAP_33(Macro, Arg, __VA_ARGS__))
#define __QI_VAARGS_MAP_33(Macro, Arg, elem, ...) , Macro(33, Arg, elem) QI_CAT(_QI_NIF_,QI_VAARGS_EMPTY(__VA_ARGS__))(TOO_MANY_ARGUMENTS)

#define __QI_VAARGS_EMPTY(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, ...) QI_01_TO_TRUEFALSE(p20)

/// QI_TRUE if __VA_ARGS__ has *no comma*, QI_FALSE else
#define QI_VAARGS_EMPTY(...) __QI_VAARGS_EMPTY(__VA_ARGS__, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0,1,1)
/// expand to Macro(0, Arg, p0), Macro(1, Arg, p1), ... , Macro(N, Arg, pN)
#define QI_VAARGS_MAP(Macro, Arg, ...) \
   __QI_VAARGS_MAP_0(Macro, Arg,  __VA_ARGS__,)

#endif



#endif  // _QI_PREPROC_HPP_
