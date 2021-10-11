/**
* @author Aldebaran Robotics
* Copyright (c) Aldebaran Robotics 2007 All Rights Reserved
*/

#pragma once

#ifndef _LIB_ALPYTHONTOOLS_ALPYTHONTOOLS_ALPYTHONTOOLS_H_
#define _LIB_ALPYTHONTOOLS_ALPYTHONTOOLS_ALPYTHONTOOLS_H_

#include "alpython.h"
#include <string>

/**
* All classes visible in python are here
*/


namespace AL
{
  class ALValue;

  class ALCriticalSectionGILPython
  {
  public:
    ALCriticalSectionGILPython() : fState(PyGILState_Ensure()){}
    ~ALCriticalSectionGILPython() {PyGILState_Release(fState);}

  private:
    PyGILState_STATE fState;
  };

  class ALCriticalSectionAllowThreadsPython
  {
  public:
    ALCriticalSectionAllowThreadsPython() : fSave(PyEval_SaveThread()) {}
    ~ALCriticalSectionAllowThreadsPython() {PyEval_RestoreThread(fSave);}

  private:
    PyThreadState* fSave;
  };

  /**
  * ALPythonTools
  */
  class ALPythonTools
  {
  public:

    /**
    * convert PyObject to AL::ALValue
    */
    static std::string eval(const std::string& pModuleName, const std::string& pMethod, const AL::ALValue& pParams, AL::ALValue& pResult);
    static std::string eval(const std::string& pToEval);
    static ::AL::ALValue evalReturn(const std::string& pToEval);
    static ::AL::ALValue evalFull(const std::string& pToEval);
    static ::AL::ALValue convertPyObjectToALValue(PyObject *param);
    static PyObject * convertALValueToPython(const ::AL::ALValue& value);
  };
}
#endif  // _LIB_ALPYTHONTOOLS_ALPYTHONTOOLS_ALPYTHONTOOLS_H_
