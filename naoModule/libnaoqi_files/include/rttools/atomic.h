/**
 * @author Cedric GESTES
 * Copyright (c) Aldebaran Robotics 2008 All Rights Reserved
 *
 */


/**
 * atomic operation on int
 */


#pragma once

#ifndef _LIB_RTTOOLS_RTTOOLS_ATOMIC_H_
#define _LIB_RTTOOLS_RTTOOLS_ATOMIC_H_

# if (TARGET_HOST == TARGET_HOST_WINDOWS) || !defined(i386)

static inline int
exchange_and_add(volatile signed long* mem, int val)
{
  *mem = val;
  return *mem;
}
static inline void
atomic_add(volatile signed long* mem, int val)
{
  *mem = val;
}
# else
static inline int //__attribute__ ((__unused__))
exchange_and_add(volatile signed long* mem, int val)
{
  register int result;
  asm volatile ("lock; \n"                      \
                "xaddl %0,%1"
                : "=r" (result),
                  "=m" (*mem)
                : "0" (val),
                  "m" (*mem)
                );
  return result;
}

static inline void //__attribute__ ((__unused__))
atomic_add(volatile signed long* mem, int val)
{
  asm volatile ("lock; \n"                      \
                "addl %1,%0 \n"
                : "=m" (*mem)
                : "ir" (val),
                  "m" (*mem));
}
#endif

#endif  // _LIB_RTTOOLS_RTTOOLS_ATOMIC_H_
