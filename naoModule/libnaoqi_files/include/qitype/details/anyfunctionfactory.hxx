#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_ANYFUNCTIONFACTORY_HXX_
#define _QITYPE_DETAILS_ANYFUNCTIONFACTORY_HXX_

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/bind.hpp>
#include <boost/any.hpp>
#include <boost/thread/mutex.hpp>
#include <qi/atomic.hpp>
#include <qitype/anyreference.hpp>

namespace qi
{
  namespace detail
  {
    /* General idea: code generated to make a function call taking a
     * void*, long, or long& is the same.
     * So we reduce the function types for which we effectively implement
     * call, and bounce the equivalent functions to it.
     */

    /* ASSERTS
     * We make some asumptions for this code to work. Failure on any of
     * those asumptions will *not* be detected and will cause undefined behavior.
     * - typesystem Storage for pointer types is by-value, and by-pointer for everything else
     * - compiler-generated code is the same when calling a function:
     *     - with argument T and EqType<T>::type
     *     - with return type T and EqType<T>::rType
     *     - with all pointer types and all reference types for argument/return type
     */

    class Class{}; // dummy class placeholder

    /* For each type, get equivalent type, and if it is a reference
     * Equivalent type is a type for which when types are substituted in a
     * function call, compiler-generated code is the same.
     * *WARNING* some magic occurs for return type, so have a separate rule
     * which matches less stuffs for it.
     */
    template <typename T, bool isWordSize>
    struct EqTypeBase
    {
      typedef T type;
      typedef T rType;
      typedef typename boost::is_reference<T>::type isReference;
      static const int dbgTag = 0;
    };

    template<typename T>
    struct EqTypeBase<T, true>
    {
      typedef typename boost::mpl::if_<typename boost::is_fundamental<T>::type, void*, T>::type type;
      typedef typename boost::mpl::if_<typename boost::is_fundamental<T>::type, void*, T>::type rType;
      typedef typename boost::is_reference<T>::type isReference;
      static const int dbgTag = 1;
    };

    template <typename T>
    struct EqType: public EqTypeBase<T, sizeof(T) == sizeof(void*)>
    {
    };

    template <> struct EqType<void>
    {
      typedef void type;
      typedef void* rType;
      typedef boost::false_type isReference;
    };

    template<> struct EqType<double>
    {
      typedef double type;
      typedef double rType;
      typedef boost::false_type isReference;
    };

    template<> struct EqType<float>
    {
      typedef float type;
      typedef float rType;
      typedef boost::false_type isReference;
    };

    template<> struct EqType<bool>
    {
      typedef void* type;
      typedef void* rType;
      typedef boost::false_type isReference;
    };

    template <typename T> struct EqType<T&>
    {
      typedef void* type;
      typedef void* rType;
      typedef boost::true_type isReference;
      static const int dbgTag = 2;
    };

    template <typename T> struct EqType<T const &>
    {
      typedef void* type;
      typedef void* rType;
      typedef boost::true_type isReference;
      static const int dbgTag = 3;
    };

    // HACK: mark pointer as references, because typesystem transmit them
    // by-value
    template <typename T>
    struct EqType<T *>
    {
      typedef void* type;
      typedef void* rType;
      typedef boost::true_type isReference;
      static const int dbgTag = 4;
    };

    // helper to compute a reference mask iterating through a mpl sequence
    template<typename S, typename I, int p>
    struct RefMasqBuilderHelper
    {
      typedef typename boost::mpl::deref<I>::type type;
      static const unsigned int isRef = EqType<type>::isReference::value;
      static const unsigned long vSelf = isRef << p;
      static const unsigned long val = vSelf + RefMasqBuilderHelper<S,
      typename boost::mpl::next<I>::type, p+1>::val;
    };

    template<typename S, int p>
    struct RefMasqBuilderHelper<S, typename boost::mpl::end<S>::type, p>
    {
      static const unsigned long val = 0;
    };

    /* Equivalent function info for function type F
   *
   */
    template<typename F> struct EqFunctionBare
    {
      typedef typename boost::function_types::components<F>::type Components;

      typedef typename boost::function_types::parameter_types<F>::type Arguments;
      typedef typename boost::function_types::result_type<F>::type Result;

      // need to handle result type separately
      typedef typename boost::mpl::transform<Arguments,
      EqType<boost::mpl::_1> >::type EqArguments;
      typedef typename EqType<Result>::rType EqResult;
      typedef typename boost::mpl::push_front<EqArguments, EqResult>::type EqComponents;

      // Bit b is set if argument index b+1 (0=return type) is a reference.
      static const unsigned long refMask = RefMasqBuilderHelper<Components,
      typename boost::mpl::begin<Components>::type, 0>::val;
      typedef typename boost::function_types::function_type<EqComponents>::type type;
    };

    template<typename F> struct EqMemberFunction
    {
      typedef typename boost::function_types::components<F>::type Components;
      // we need to handle object type and return type separately
      // arguments with object
      typedef typename boost::function_types::parameter_types<F>::type MethodArguments;
      // arguments without object
      typedef typename boost::mpl::pop_front<MethodArguments>::type Arguments;
      // return type
      typedef typename boost::function_types::result_type<F>::type Result;
      typedef typename boost::mpl::transform<Arguments,
      EqType<boost::mpl::_1> >::type EqArguments;
      typedef typename EqType<Result>::rType EqResult;
      // push equivalent object type
      typedef typename boost::mpl::push_front<EqArguments, detail::Class&>::type EqComponentsInt;
      typedef typename boost::mpl::push_front<EqComponentsInt, EqResult>::type EqComponents;
      typedef typename boost::function_types::member_function_pointer<EqComponents>::type type;
      static const unsigned long refMask = RefMasqBuilderHelper<Components,
      typename boost::mpl::begin<Components>::type, 0>::val;
    };

    template<typename F>
    struct EqFunction:
        public boost::mpl::if_<typename boost::is_member_function_pointer<F>::type,
                               EqMemberFunction<F>,
                               EqFunctionBare<F> >::type
    {};
    /* args[i] is a pointer to an element of expected type DROPPING ref
     * we will make the call by dereferencing all args, so we must add
     * one layer of pointer to effective refs
     *
     */
    inline void transformRef(void** args, void** out, unsigned int sz, unsigned long refMask)
    {
      for (unsigned i=0; i<sz; ++i)
      {
        if (refMask & (1 << (i+1))) // bit 0 is for return type
          out[i] = &args[i];
        else
          out[i] = args[i];
      }
    }
    // makeCall function family
    // accepts a bare function, boost function, member function
    // we handled byval/byref in refMask/transformRef, so bypass
    // entirely ptrFromStorage.

#define callArg(z, n, _) \
  BOOST_PP_COMMA_IF(n) *(typename boost::remove_reference<P ## n>::type  *)args[n]
#define makeCall(n, argstypedecl, argstype, argsdecl, argsues, comma)     \
  template<typename R comma argstypedecl> \
  void* makeCall(R(*f)(argstype), void** args)  \
    { \
  detail::AnyReferenceCopy val; \
  val(), f( \
  BOOST_PP_REPEAT(n, callArg, _) \
  ); \
  return val.rawValue(); \
  }
    QI_GEN(makeCall)
#undef makeCall

#ifdef _WIN32
#define STATIC_IF_SAFE
#else
#define STATIC_IF_SAFE static
#endif

    // hacks are disabled for boost::function (refMask forced to 0)
    // so use ptrFromStorage.
#define declType(z, n, _) \
  STATIC_IF_SAFE TypeInterface* type_ ## n  = typeOf<typename boost::remove_reference<P ## n>::type>();
#define callArgBF(z, n, _) \
  BOOST_PP_COMMA_IF(n) *(typename boost::remove_reference<P ## n>::type  *)type_##n -> ptrFromStorage(&args[n])

#define makeCall(n, argstypedecl, argstype, argsdecl, argsues, comma)     \
  template<typename R comma argstypedecl> \
  void* makeCall(boost::function<R(argstype)> f, void** args)  \
    { \
  BOOST_PP_REPEAT(n, declType, _) \
  detail::AnyReferenceCopy val; \
  val(), f( \
  BOOST_PP_REPEAT(n, callArgBF, _) \
  ); \
  return val.rawValue(); \
  }
    QI_GEN(makeCall)
#undef makeCall

#define makeCall(n, argstypedecl, argstype, argsdecl, argsues, comma)     \
  template<typename R comma argstypedecl> \
  void* makeCall(R(Class::*f)(argstype), void* instance, void** args)  \
    { \
  detail::AnyReferenceCopy val; \
  Class* cptr = *(Class**)instance; \
  val(), ((*cptr).*f)( \
  BOOST_PP_REPEAT(n, callArg, _) \
  ); \
  return val.rawValue(); \
  }
    QI_GEN(makeCall)
#undef makeCall

#define makeCall_(n, argstypedecl, argstype, argsdecl, argsues, comma)     \
  template<typename R comma argstypedecl> \
  void* makeCall(R(Class::*f)(argstype), void** args)  \
    { \
  return makeCall(f, args[0], args + 1); \
  }

    QI_GEN(makeCall_)
#undef callArg
#undef makeCall_

#ifdef QITYPE_TRACK_FUNCTIONTYPE_INSTANCES
    // debug-tool to monitor function type usage
    void QITYPE_API functionTypeTrack(const std::string& functionName);
    void QITYPE_API functionTypeDump();
#endif
  }

  struct InfosKeyMask: public std::vector<TypeInterface*>
  {
  public:
    InfosKeyMask(const std::vector<TypeInterface*>& b, unsigned long mask)
      : std::vector<TypeInterface*>(b), _mask(mask) {}
    bool operator < (const InfosKeyMask& b) const
    {
      if (size() != b.size())
        return size() < b.size();
      for (unsigned i=0; i<size(); ++i)
      {
        if ( (*this)[i]->info() != b[i]->info())
          return (*this)[i]->info() < b[i]->info();
      }
      return _mask < b._mask;
    }
    unsigned long _mask;
  };

  /* T is the *reducted* function type
  *  S is the storage type of the function
  * So each instance must know the refMask, and the real return type
  *
  * categories of S in use:
  *  boost::function: no reduction performed
  *  bare function pointer
  *  member function pointer: T is the linearized signature
  */
  template<typename T, typename S>
  class FunctionTypeInterfaceEq: public FunctionTypeInterface
  {
  public:
    typedef typename boost::function_types::result_type<T>::type ReturnType;
    FunctionTypeInterfaceEq(unsigned long refMask)
      : refMask(refMask)
    {
#ifdef QITYPE_TRACK_FUNCTIONTYPE_INSTANCES
      detail::functionTypeTrack(typeid(S).name());
#endif
    }
    virtual void* call(void* storage, void** args, unsigned int argc)
    {
#if QI_HAS_VARIABLE_LENGTH_ARRAY
      void* out[argc];
#else
      void* outStatic[8];
      void** out;
      if (argc <= 8)
        out = outStatic;
      else
        out = new void*[argc];
#endif
      detail::transformRef(args, out, argc, refMask);
      void* v = detail::makeCall(*(S*)ptrFromStorage(&storage), (void**)out);
      // v is storage for type ReturnType we claimed we were
      // adapt return value if needed
      if (boost::is_pointer<ReturnType>::value
          &&  _resultType->kind() != TypeKind_Pointer)
      {
        // if refMask&1, real return type is some Foo& and v is Foo*
        // else, return type is Foo with sizeof(Foo) == sizeof(void*) and v is a Foo
        void* vstorage = _resultType->initializeStorage(
              (refMask&1)? v: &v);
        vstorage = _resultType->clone(vstorage);
        //qiLogWarning("ft") << "Ret deref " << (unsigned long)v <<' ' << vstorage
        // << ' ' << *(unsigned long*)vstorage;
        v = vstorage;
      }
#if ! QI_HAS_VARIABLE_LENGTH_ARRAY
      if (argc > 8)
        delete[] out;
#endif
      return v;
    }
    unsigned long refMask;
    static FunctionTypeInterfaceEq<T, S>* make(unsigned long refMask, std::vector<TypeInterface*> argsType,
                                               TypeInterface* returnType)
    { // we need to hash/compare on all the arguments
      std::vector<TypeInterface*> key(argsType);
      key.push_back(returnType);
      typedef std::map<InfosKeyMask,  FunctionTypeInterfaceEq<T, S>* > FTMap;
      static FTMap* ftMap = 0;
      static boost::mutex* mutex = 0;
      QI_THREADSAFE_NEW(ftMap, mutex);
      boost::mutex::scoped_lock lock(*mutex);
      FunctionTypeInterfaceEq<T, S>* & fptr = (*ftMap)[InfosKeyMask(key, refMask)];
      if (!fptr)
      {
        fptr = new FunctionTypeInterfaceEq<T, S>(refMask);
        fptr->_resultType = returnType;
        fptr->_argumentsType = argsType;
      }
      return fptr;
    }
    _QI_BOUNCE_TYPE_METHODS(DefaultTypeImplMethods<S>);
  };

  namespace detail
  {

    // Trick used to avoid instanciating a T
    template<typename T> struct Ident
    {
    };

    struct checkForNonConstRef
    {
      template<typename T> void operator()(Ident<T>)
      {
        qiLogCategory("qitype.functiontypefactory");
        if (boost::is_reference<T>::value && !boost::is_const<
            typename boost::remove_reference<T>::type>::value)
          qiLogWarning() << "Function argument is a non-const reference: " << typeid(T).name();
      }
    };
    template<typename T> struct remove_constptr
    {
      typedef T type;
    };
    template<typename T> struct remove_constptr<const T*>
    {
      typedef T* type;
    };
    // Fill a vector<TypeInterface*> from a T*
    struct fill_arguments
    {
      inline fill_arguments(std::vector<TypeInterface*>* target)
        : target(target) {}

      template<typename T> void operator()(T*) const
      {
        TypeInterface* result = typeOf<
            typename remove_constptr<
            typename boost::remove_const<
            typename boost::remove_reference<T>::type
            >::type>::type>();
        target->push_back(result);
      }
      std::vector<TypeInterface*>* target;
    };

    // build a function pointer or member function pointer type
    template<typename F, bool Member> struct FunctionPointerSynthetizer
    {
      typedef typename  boost::function_types::member_function_pointer<F>::type type;
    };
    template<typename F> struct FunctionPointerSynthetizer<F, false>
    {
      typedef typename boost::function_types::function_pointer<F>::type type;
    };
    // Accept a function pointer or member function pointer
    template<typename F>
    AnyFunction makeAnyFunctionBare(F func)
    {
      typedef typename boost::function_types::parameter_types<F>::type ArgsType;
      typedef typename boost::function_types::result_type<F>::type ResType;
      TypeInterface* resultType = typeOf<ResType>();
      std::vector<TypeInterface*> argumentsType;
      // Generate and store a TypeInterface* for each argument
      boost::mpl::for_each<
          boost::mpl::transform_view<ArgsType,
          boost::add_pointer<
          boost::remove_const<
          boost::remove_reference<boost::mpl::_1> > > > >(detail::fill_arguments(&argumentsType));
      typedef typename EqFunction<F>::type MapedF;
      // regenerate eq function pointer type
      typedef typename boost::function_types::components<MapedF>::type EqComponents;
      // would have used mpl::if_ but it has laziness issues it seems
      typedef typename FunctionPointerSynthetizer<EqComponents,
          boost::is_member_function_pointer<F>::value>::type EqFunPtr;
      unsigned long mask = EqFunction<F>::refMask;
      FunctionTypeInterface* ftype = FunctionTypeInterfaceEq<MapedF, EqFunPtr>::make(mask, argumentsType, resultType);

      qiLogDebug("qitype.makeAnyFunction") << "bare mask " << (unsigned long)EqFunction<F>::refMask;
      return AnyFunction(ftype, ftype->clone(ftype->initializeStorage(&func)));
    }

    template<typename C, typename R>
    AnyReference bouncer(const AnyReferenceVector& vargs,
                         R (C::*fun)(const AnyArguments&)
                         )
    {
      // Pack arguments, call, wrap return value in AnyValue
      AnyArguments nargs;
      nargs.args().resize(vargs.size()-1);
      for (unsigned i=0; i<vargs.size()-1; ++i)
        nargs.args()[i] = vargs[i+1];
      C* inst = (C*)vargs.front().rawValue();
      if (!inst)
        qiLogWarning("qitype.AnyArgumentsBouncer") << "Null instance";
      detail::AnyReferenceCopy output;
      output(), (*inst.*fun)(nargs); // output clones
      AnyValue* v = new AnyValue(output, false, true); // steal output
      return AnyReference::fromPtr(v);
    }

    template<typename R>
    AnyReference bouncerBF(const AnyReferenceVector& vargs,
                           boost::function<R (const AnyArguments&)> f
                           )
    {
      AnyArguments nargs;
      if(!vargs.empty())
      {
        nargs.args().resize(vargs.size());
        for (unsigned i=0; i<vargs.size(); ++i)
          nargs.args()[i] = vargs[i];
      }
      detail::AnyReferenceCopy output;
      output(), f(nargs);
      AnyValue* v = new AnyValue(output, false, true); // steal output
      return AnyReference::fromPtr(v);
    }

    template<typename C, typename R>
    AnyFunction makeAnyFunctionBare(R (C::*fun)(const AnyArguments&))
    {
      AnyFunction res = AnyFunction::fromDynamicFunction(boost::bind(&bouncer<C, R>, _1, fun));
      // The signature storage in GO will drop first argument, and bug if none is present
      const_cast<std::vector<TypeInterface*> &>(res.functionType()->argumentsType()).push_back(typeOf<AnyValue>());
      return res;
    }

    template<typename R>
    AnyFunction makeAnyFunctionBare(R (*fun)(const AnyArguments&))
    {
      boost::function<R (const AnyArguments&)> fu = fun;
      AnyFunction res = AnyFunction::fromDynamicFunction(boost::bind(&bouncerBF<R>, _1, fun));
      // The signature storage in GO will drop first argument, and bug if none is present
      const_cast<std::vector<TypeInterface*> &>(res.functionType()->argumentsType()).push_back(typeOf<AnyValue>());
      return res;
    }

    template<typename R> AnyFunction makeAnyFunctionBare(boost::function<R (const AnyArguments&)> fun)
    {
      AnyFunction res = AnyFunction::fromDynamicFunction(boost::bind(&bouncerBF<R>, _1, fun));
      // The signature storage in GO will drop first argument, and bug if none is present
      const_cast<std::vector<TypeInterface*> &>(res.functionType()->argumentsType()).push_back(typeOf<AnyValue>());
      return res;
    }

    template<typename F> AnyFunction makeAnyFunctionBare(boost::function<F> func)
    {
      /* Do not try to reduce anything on a boost::function.
      * It will bounce to an internal template backend anyway
      */
      typedef typename boost::function_types::parameter_types<F>::type ArgsType;
      typedef typename boost::function_types::result_type<F>::type ResType;
      TypeInterface* resultType = typeOf<ResType>();
      std::vector<TypeInterface*> argumentsType;
      boost::mpl::for_each<
          boost::mpl::transform_view<ArgsType,
          boost::add_pointer<
          boost::remove_const<
          boost::remove_reference<boost::mpl::_1> > > > >(detail::fill_arguments(&argumentsType));
      FunctionTypeInterface* ftype = FunctionTypeInterfaceEq<F, boost::function<F> >::make(0, argumentsType, resultType);
      return AnyFunction(ftype, new boost::function<F>(func));
    }

    // Use helper structures for which template partial specialisation is possible
    template<typename T> struct AnyFunctionMaker
    {
      static AnyFunction make(T func)
      {
        return makeAnyFunctionBare(func);
      }
    };
    template<typename T> struct AnyFunctionMaker<T*>
    {
      static AnyFunction make(T* func)
      {
        return makeAnyFunctionBare(func);
      }
    };
    template<typename R, typename F, typename B>
    struct AnyFunctionMaker<boost::_bi::bind_t<R, F, B> >
    {
      static AnyFunction make(boost::_bi::bind_t<R, F, B> v)
      {
        typedef typename boost::function<typename boost_bind_function_type<
            boost::_bi::bind_t<R, F, B> >::type> CompatType;
        CompatType f = v;
        return AnyFunction::from(f);
      }
    };
    template<typename T> struct AnyFunctionMaker<boost::function<T> >
    {
      static AnyFunction make(boost::function<T> func)
      {
        assert(sizeof(boost::function<T>) == sizeof(boost::function<void ()>));
        AnyFunction res = detail::makeAnyFunctionBare(func);
        return res;
      }
    };
    template<typename T> struct AnyFunctionMaker<const T&>
        : public AnyFunctionMaker<T> {};
    template<> struct AnyFunctionMaker<AnyFunction>
    {
      static AnyFunction make(AnyFunction func)
      {
        return func;
      }
    };
  }

  template<typename T>
  AnyFunction AnyFunction::from(T f)
  {
    return detail::AnyFunctionMaker<T>::make(f);
  }

  namespace detail
  {
    template<typename T> struct Pointer
    {
      static T* pointer(T& t)
      {
        return &t;
      }
    };
    template<typename T> struct Pointer<T*>
    {
      static T* pointer(T* & t)
      {
        return t;
      }
    };
  }

  template<typename F, typename C>
  AnyFunction AnyFunction::from(F func, C instance)
  {
    /* Taking a AnyFunction of F will likely imply a typeOf<C> which is
    * unnecessary. So use a fake class in signature.
    */
    typedef typename boost::function_types::result_type<F>::type Result;
    typedef typename boost::function_types::parameter_types<F, boost::mpl::identity<boost::mpl::_1> >::type Args;
    typedef typename boost::mpl::pop_front<Args>::type ArgsNoClass;
    typedef typename boost::mpl::push_front<ArgsNoClass, detail::Class&>::type ArgsFakeClass;
    typedef typename boost::mpl::push_front<ArgsFakeClass, Result>::type ComponentsFaked;
    typedef typename boost::function_types::member_function_pointer<ComponentsFaked>::type MethodTypeFaked;
    MethodTypeFaked newFunk = *(MethodTypeFaked*)(void*)&func;
    AnyFunction res = AnyFunction::from(newFunk);

    // Dynamic-cast instance to expected pointer type.
    typedef typename boost::mpl::at_c<Args, 0>::type FirstArg;
    // Get expected
    FirstArg* ptr = dynamic_cast<FirstArg*>(detail::Pointer<C>::pointer(instance));
    if (!ptr && instance)
      throw std::runtime_error("makeAnyFunction: failed to dynamic_cast bound value to expected type");
    res.prependArgument((void*)(const void*)ptr);
    return res;
  }

}
#endif  // _QITYPE_DETAILS_ANYFUNCTIONFACTORY_HXX_
