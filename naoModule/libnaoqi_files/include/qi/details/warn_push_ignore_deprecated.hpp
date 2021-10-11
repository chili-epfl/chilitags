/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/

/*
 * this allow removing spurious warning when a deprecated declaration use another deprecated declaration.
 *
 * QI_API_DEPRECATED class Foo;
 *
 * #include <qi/details/diagnostic_push_ignore_deprecated.hpp>
 * //Would emit a spurious deprecated warning about Foo otherwise
 * QI_API_DEPRECATED void bar(Foo foo);
 * #include <qi/details/diagnostic_pop.hpp>
 */


// clang and GCC
#if defined(__GNUC__)
# if defined(__clang__) || (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#  pragma GCC diagnostic push
# endif
# pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif
