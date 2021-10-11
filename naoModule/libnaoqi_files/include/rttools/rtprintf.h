/**
 * @author Cedric GESTES
 * Copyright (c) Aldebaran Robotics 2008 All Rights Reserved
 *
 */


/**
 * This file implement a real-time thread safe printf
 */
#pragma once

#ifndef _LIB_RTTOOLS_RTTOOLS_RTPRINTF_H_
#define _LIB_RTTOOLS_RTTOOLS_RTPRINTF_H_

typedef int (*RtPrintfCallback)(const char *);

/*
 * set the rtprintf callback to do the effective print
 */
void rtPrintfSetCallback(RtPrintfCallback cb);

void rtprintf(const char *fmt, ...);

#endif  // _LIB_RTTOOLS_RTTOOLS_RTPRINTF_H_
