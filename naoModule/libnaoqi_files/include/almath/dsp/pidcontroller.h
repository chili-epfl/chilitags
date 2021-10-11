/*
 * Copyright (c) 2012-2014 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#ifndef _LIB_ALMATH_ALMATH_DSP_PIDCONTROLLER_H_
#define _LIB_ALMATH_ALMATH_DSP_PIDCONTROLLER_H_


namespace AL {
namespace Math {

namespace DSP {
class PIDController
{

public :
  PIDController(void);

  PIDController(float pKp,
                float pKv,
                float pKi,
                float pThreshold,
                float pStaticOffset,
                float pPeriod);

  ~PIDController();

  void initialize();

  void initialize(float pKp,
                  float pKv,
                  float pKi,
                  float pThreshold,
                  float pStaticOffset,
                  float pPeriod);

  float computeFeedback(float pCommand,
                        float pSensor,
                        float pPeriod = -1.0f);
  float computeFeedbackAbsolute(float pAbsoluteErr);


private:
  float fKp;
  float fKv;
  float fKi;

  float fPeriod;

  float fThreshold;
  float fStaticOffset;

  float fErr;
  float fPreviousErr;
  float fdErr;
  float fiErr;

  bool fFirstIteration;

  void xResetParameters(void);
  void xCheckData(void) const;
  void xCheckPositif(float pVal) const;
  void xCheckStriclyPositif(float pVal) const;
};
}
}
}
#endif // _LIB_ALMATH_ALMATH_DSP_PIDCONTROLLER_H_
