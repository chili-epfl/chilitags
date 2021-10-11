/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011, 2012 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALCOMMON_ALCOMMON_ALFUNCTOR_H_
#define _LIBALCOMMON_ALCOMMON_ALFUNCTOR_H_

# include <alcommon/api.h>
# include <alvalue/alvalue.h>
# include <boost/shared_ptr.hpp>
# include <qitype/anyobject.hpp>
# include <sstream>

/// \ingroup Functor
namespace AL
{
  /**
   * \typedef ALVoid
   * \brief Type def to void.
   * \ingroup Functor
   */
  typedef void ALVoid;

  /**
   * \class ALFunctorBase alfunctor.h "alcommon/alfunctor.h"
   * \brief ALFunctorBase is a generic functor class for pointer management.
   * \ingroup Functor
   */
  class ALFunctorBase
  {
  public:
    ALFunctorBase()
    {
    }

    ALFunctorBase(qi::AnyFunction metaFun)
      : _functor(metaFun)
    {
    }

    void reset(){
      _functor = qi::AnyFunction();
    }

    qi::AnyFunction genericFunction() {
      return _functor;
    }

    qi::Signature signature() const
    {
      //drop the first arg
      return _functor.parametersSignature(true);
    }

    qi::Signature sigreturn() const
    {
      return _functor.returnSignature();
    }

    /**
     * \brief Generic call to a bound module's method.
     * \param pParams input parameter
     * \param pResult output result
     */
    virtual void call(const ALValue& pParams, ALValue& pResult) {
      qiLogError("alcommon.ALFunctor") << "ALFunctor::call not implemented";
      //TODO: NOT IMPLEMENTED
    };

    /** \brief Destructor. */
    virtual ~ALFunctorBase() {
      //delete _functor;
    }

    qi::AnyFunction _functor;
  };

}

namespace AL {

  template<typename C, typename F>
  boost::shared_ptr<ALFunctorBase> createFunctor(C* obj, F fun)
  {
     return boost::shared_ptr<ALFunctorBase>(new ALFunctorBase(
       qi::AnyFunction::from(fun, obj).dropFirstArgument()));
  }
  template <typename C, typename R>
  boost::shared_ptr<ALFunctorBase> createFunctor(C *obj, R (C::*f) ()) {
    return boost::shared_ptr<ALFunctorBase>(new ALFunctorBase(qi::AnyFunction::from(f, obj).dropFirstArgument()));
   }

  template <typename C, typename P1, typename R>
  boost::shared_ptr<ALFunctorBase> createFunctor(C *obj, R (C::*f) (const P1 &)) {
    return boost::shared_ptr<ALFunctorBase>(new ALFunctorBase(qi::AnyFunction::from(f, obj).dropFirstArgument()));
  }

  template <typename C, typename P1, typename P2, typename R>
  boost::shared_ptr<ALFunctorBase> createFunctor(C *obj, R (C::*f) (const P1 &, const P2 &)) {
    return boost::shared_ptr<ALFunctorBase>(new ALFunctorBase(qi::AnyFunction::from(f, obj).dropFirstArgument()));
  }

  template <typename C, typename P1, typename P2, typename P3, typename R>
  boost::shared_ptr<ALFunctorBase> createFunctor(C *obj, R (C::*f) (const P1 &, const P2 &, const  P3 &)) {
    return boost::shared_ptr<ALFunctorBase>(new ALFunctorBase(qi::AnyFunction::from(f, obj).dropFirstArgument()));
  }

  template <typename C, typename P1, typename P2, typename P3, typename P4, typename R>
  boost::shared_ptr<ALFunctorBase> createFunctor(C *obj, R (C::*f) (const P1 &, const P2 &, const P3 &, const P4 &)) {
    return boost::shared_ptr<ALFunctorBase>(new ALFunctorBase(qi::AnyFunction::from(f, obj).dropFirstArgument()));
  }

  template <typename C, typename P1, typename P2, typename P3, typename P4, typename P5, typename R>
  boost::shared_ptr<ALFunctorBase> createFunctor(C *obj, R (C::*f) (const P1 &, const P2 &, const P3 &, const P4 &, const P5 &)) {
    return boost::shared_ptr<ALFunctorBase>(new ALFunctorBase(qi::AnyFunction::from(f, obj).dropFirstArgument()));
  }

  template <typename C, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename R>
  boost::shared_ptr<ALFunctorBase> createFunctor(C *obj, R (C::*f) (const P1 &, const P2 &, const P3  &, const P4 &, const P5 &, const P6 &)) {
    return boost::shared_ptr<ALFunctorBase>(new ALFunctorBase(qi::AnyFunction::from(f, obj).dropFirstArgument()));
  }

}

#endif  // _LIBALCOMMON_ALCOMMON_ALFUNCTOR_H_
