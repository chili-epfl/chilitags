/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/

// clang and GCC
#if defined(__GNUC__)
# if defined(__clang__) || (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#  pragma GCC diagnostic pop
# endif
#elif defined(_MSC_VER)
# pragma warning(pop)
#endif
