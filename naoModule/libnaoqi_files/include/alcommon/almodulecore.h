/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011, 2012 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALCOMMON_ALCOMMON_ALMODULECORE_H_
#define _LIBALCOMMON_ALCOMMON_ALMODULECORE_H_

# include <alcommon/api.h>
# include <boost/enable_shared_from_this.hpp>
# include <boost/shared_ptr.hpp>
# include <boost/noncopyable.hpp>

# include <alcommon/almoduleinfo.h>
# include <alcommon/almethodinfo.h>
# include <alcommon/alfunctor.h>

# include <alerror/alerror.h>
# include <qi/log.hpp>
# include <map>

#include <qitype/dynamicobject.hpp>
#include <qitype/signature.hpp>
#include <qitype/anyfunction.hpp>
#include <qitype/dynamicobjectbuilder.hpp>
#include <qitype/dynamicobject.hpp>

//legacy hell, LEGACY HELL
#define BIND_OBJ_METHOD(objptr, meth) _builder.advertiseMethod(_mBuilder, objptr, &meth)
#define BIND_METHOD(meth) _builder.advertiseMethod(_mBuilder, this, &meth)

#define BIND_OBJ_METHOD_PTR(objptr, methptr) _builder.advertiseMethod(_mBuilder, objptr, methptr)
#define BIND_METHOD_PTR(methptr) _builder.advertiseMethod(_mBuilder, this, methptr)

namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALValue;
  class ALModuleCorePrivate;

  /**
   * \class ALModuleCore almodulecore.h "alcommon/almodulecore.h"
   * \brief ALModuleCore is the superclass of user modules.
   *
   * It implements basic functions that enables communication with naoqi
   * brokers, so that the distributed approach is painless for users
   * who just want to come up with a simple module quickly,
   * compile it and have it work, without having to deal with
   * interprocess communication.
   * \ingroup Module
   */
  class ALModuleCore: public ::boost::enable_shared_from_this<ALModuleCore>, public ::boost::noncopyable, public qi::DynamicObject
  {
  public:
    /**
     * \typedef Ptr
     * \brief Shared pointer to ALModuleCore
     * \deprecated Use boost::shared_ptr<ALModuleCore> instead
     */
    typedef boost::shared_ptr<ALModuleCore>       Ptr;
    /**
     * \typedef WeakPtr
     * \brief Weak pointer to ALModuleCore
     * \deprecated Use boost::weak_ptr<ALModuleCore> instead
     */
    typedef boost::weak_ptr<ALModuleCore>         WeakPtr;

    /**
     * \enum ModuleType
     * \brief Module type (Ruby, lua, and matlab are not currently used)
     * \deprecated not used anywhere
     */
    enum ModuleType
      {
        CPP    = 0, /**< C++ type */
        PYTHON = 1, /**< python type */
        RUBY   = 2, /**< ruby type (unused) */
        LUA    = 3, /**< lua type (unused) */
        MATLAB = 4, /**< matlab type (unused) */
        URBI        /**< urbi type */
      };

    /**
     * \brief Constructor.
     *
     *        An ALModule has a name, and is registered in a broker,
     *        so that its methods can be called by other modules,
     *        via a proxy constructed with module's name
     * \param pBroker a pointer to the broker
     * \param pName name of the module
     */
    ALModuleCore(boost::shared_ptr<ALBroker> pBroker,
                 const std::string &pName);

    /** \brief Destructor. */
    virtual ~ALModuleCore();

    /**
     * \brief Get a reference to a temporary object used to construct
     *        method help
     * \return a reference to a temporary ALMethodInfo
     */
    ALMethodInfo& getCurrentMethodDescription();

    /**
     * \brief Getter to the class.
     * \return a pointer to this
     */
    boost::shared_ptr<ALModuleCore> getThis();
    /**
     * \brief Getter to class.
     * \return a const pointer to this
     */
    boost::shared_ptr<const ALModuleCore> getThis() const;

    /**
     * \brief Check if someone want to exit the module.
     * \return true if someone ask to exit the module, false othewise
     */
    bool isClosing();

    /**
     * \brief Register a module to a broker.
     *
     *        Automatically called when loading a module from autoload.ini
     */
    void initModule(void);

    /**
     * \brief Get access to a module.
     *
     *        ex: getProxy("ALMotion")
     * \param pModuleName module name
     * \return a pointer to ALProxy
     */
    boost::shared_ptr<AL::ALProxy> getProxy(const std::string &pModuleName);

    /**
     * \brief Get the name of the registered broker.
     * \return name of the broker
     */
    std::string getBrokerName();

    /**
     * \brief Get the type of the module.
     * \return type of the module
     */
    ModuleType getModuleType(void);

    /**
     * \brief Set the type of the module.
     * \param pType type of the module
     */
    void setModuleType(ModuleType pType);

    /**
     * \brief Execute a method with some arguments and store the result.
     * \param pMethod method to execute
     * \param pParams set of arguments for the method
     * \param pResult result of the method execution
     * \return a pointer to the method executed,
     *         so it can be used to get information about the method
     */
    virtual ALMethodInfo* execute(const std::string &pMethod,
                                  const AL::ALValue &pParams,
                                  AL::ALValue &pResult);

    /**
     * \brief Get the module method list.
     * \return vector of string module name
     */
    std::vector<std::string> getMethodList();

    /**
     * \brief Get a method's description string.
     * \param pMethodName method's name.
     * \return a structured method's description following the format :
     * [
     *   std::string methodName,
     *   std::string methodDescription,
     *   [parameter, ...],
     *   std::string returnName,
     *   std::string returnDescription
     * ]
     * Where parameter is :
     * [
     *   std::string parameterName,
     *   std::string parameterDescription
     * ]
     * \warning Will return only one version of a method, therefore the method
     * doesn't handle overloading.
     */
    AL::ALValue getMethodHelp(const std::string &pMethodName);

    /**
     * \brief Get a method's description string.
     * \param pMethodName method's name.
     * \return a structured method's description
     */
    ALMethodInfo getMethodHelpObject(const std::string &pMethodName);

    /**
     * \brief Get the module's description.
     * \return a string describing the module
     */
    AL::ALValue moduleHelp();

    /**
     * \brief Just a ping. Used to test connectivity to a module.
     * \return always returns true
     */
    bool ping(void);

    /**
     * \brief Get module's version
     * \return The version as a string
     */
    virtual std::string version();

    /**
     * \brief Exit the module and unregister it.
     */
    virtual void exit();

    /**
     * \brief Get the name of the module given when constructing
     * \return The name of the module
     */
    const std::string& getName() const;

    /**
     * \brief Get information about the module.
     * \return a pointer to ALModuleInfo
     */
    boost::shared_ptr<ALModuleInfo> getModuleInfo();

    /**
     * \brief Called by the broker webpage to detail the module.
     * \return an optional extra description of the module
     */
    virtual std::string httpGet();

    /**
     * \brief Find method information by name and argument type
     *        not only by map key.
     * \param pName method name
     * \param paramType list of parameters
     * \param softCompare true mean ALValue can be anyType
     *                    (use it for all type compare except local call)
     * \return a poitner to methodInfo
     */
    ALMethodInfo* getMethodInfoByNameMember(const std::string &pName,
                                            const std::vector<std::string> &paramType,
                                            bool softCompare = true);

    /**
     * \brief Call by a proxy to check function's parameter.
     * \param pName function Name
     * \return a poitner to methodInfo
     */
    ALMethodInfo* getMethodInfo(const std::string &pName);

    /**
     * \brief Call by a proxy to check function's parameter.
     * \param pName function Name
     * \param pParamsType parameters type
     * \return a poitner to methodInfo
     */
    ALMethodInfo* getMethodInfo(const std::string &pName,
                                std::vector<std::string> pParamsType);

    /**
     * \brief Call by a proxy to check function's parameter.
     * \param pName function Name
     * \param pParams method parameters
     * \return a poitner to methodInfo
     */
    ALMethodInfo* getMethodInfo(const std::string &pName,
                                const AL::ALValue &pParams);

    /**
     * \brief deprecated
     * \deprecated
     */
    ALMethodInfo* getFunctionDesc(const std::string &pName);

    /**
     * \brief deprecated
     * \deprecated
     */
    ALMethodInfo* getFunctionDesc(const std::string &pName,
                                  std::vector<std::string> pParamsType);

    /**
     * \brief deprecated
     * \deprecated
     */
    ALMethodInfo* getFunctionDesc(const std::string &pName,
                                  const AL::ALValue &pParams);

    /**
     * \brief deprecated
     * \deprecated
     */
    ALMethodInfo* getFunctionDescByNameMember(const std::string &pName,
                                              const std::vector<std::string> &paramType,
                                              bool softCompare = true);

    /**
     * \brief Get a pointer to the broker context.
     * \return a shared pointer to the broker context
     */
    boost::shared_ptr<ALBroker> getParentBroker() const;

    /**
     * \brief Local stop. Use stop(id) for remote/local compatibility
     * \param pTaskID the ID of the task you want to stop
     */
    void functionStop(int pTaskID);


    /**
     * \brief Set the description of the module.
     * \param pDesc a description of the module
     */
    void setModuleDescription(const std::string &pDesc);

    /**
     * \brief Get the usage of a method as a string.
     * \param methodName the name of the method
     * \return the usage as a string
     */
    std::string getUsage(const std::string &methodName);

    /**
     * \brief Create a module core link to a broker.
     * \param pBroker to pointer the a broker
     * \return a pointer to the module
     * \throw ALError
     */
    template <class T>
    static boost::shared_ptr<T> createModuleCore(boost::shared_ptr<ALBroker> pBroker)
    {
      boost::shared_ptr<T> module = boost::shared_ptr<T>(new T(pBroker));
      module->initModule();  // register module in broker
      try
      {
        // we call init on a ALModule::Ptr as init may be protected
        // init is a virtual method that can be reimplemented
        (boost::static_pointer_cast<ALModuleCore>(module))->init();
      }
      catch(const ALError& e)
      {
        module->exit();
        throw(e);
      }
      return module;
    }

    /**
     * \brief Create a module core, do not register on the broker
     * \param pBroker to pointer the a broker
     * @param[in] name Name of the module core.
     * \return a pointer to the module
     * \throw ALError
     */
    template <class T>
    static boost::shared_ptr<T> createModuleCoreNoRegister(boost::shared_ptr<ALBroker> pBroker, const std::string &name)
    {
      boost::shared_ptr<T> module = boost::shared_ptr<T>(new T(pBroker, name));
      //module->initModule();  // register module in broker
      try
      {
        // we call init on a ALModule::Ptr as init may be protected
        // init is a virtual method that can be reimplemented
        (boost::static_pointer_cast<ALModuleCore>(module))->init();
      }
      catch(const ALError& e)
      {
        module->exit();
        throw(e);
      }
      return module;
    }

    /**
     * \brief Create a module core link to a broker.
     * \param pBroker pointer to the a broker
     * \param name module's name
     * \return a pointer to the module
     * \throw ALError
     */
    template <class T>
    static boost::shared_ptr<T> createModuleCore(boost::shared_ptr<ALBroker> pBroker,
                                                 const std::string &name)
    {
      boost::shared_ptr<T> module = boost::shared_ptr<T>(new T(pBroker, name));
      module->initModule();
      try
      {
        // init if you redefined it
        (boost::static_pointer_cast<ALModuleCore>(module))->init();
      }
      catch(const ALError& e)
      {
        module->exit();
        throw(e);
      }
      return module;
    }

    /**
     * \brief Create a URBI module core link to a broker.
     * \param pBroker pointer to the a broker
     * \param name module's name
     * \return a pointer to the module
     */
    template <class T>
    static boost::shared_ptr<T> createUrbiModule(boost::shared_ptr<ALBroker> pBroker,
                                                 const std::string &name)
    {
      boost::shared_ptr<T> module = createModuleCore<T>(pBroker, name);
      module->setModuleType(AL::ALModuleCore::URBI);
      return module;
    }

    /**
     * \brief Know if program or module termination is asked.
     * \return true if module termination is asked, false otherwise
     */
    bool isModuleStopped();

    /**
     * \brief Set the id of the module used to determine the shutdown order.
     * \param id the id given to it by the broker
     */
    void setModuleID(int id);

    /**
     * \brief Get the module id given to it be the broker.
     * \return an int module id
     */
    int getModuleID();

    /**
     * \brief Bind a method.
     * \param pFunctor pointer to a generic functor
     */
    void bindMethod(boost::shared_ptr<ALFunctorBase> pFunctor);

    /**
     * \brief Bind a method.
     * \param pFunctor pointer to a generic functor
     * \param pName the name of the method
     * \param pClass the name of your class
     * \param pFunctionDescription the description of the method
     * \param pMethodDescription the description method.
     */
    void bindMethod(boost::shared_ptr<ALFunctorBase> pFunctor,
                    const std::string &pName,
                    const std::string &pClass,
                    const std::string &pFunctionDescription,
                    const ALMethodInfo &pMethodDescription);

    /**
     * \brief Use to define a bound method.
     * \param pFunctor pointer to a generic functor
     */
    void bindMethodOverload(boost::shared_ptr<ALFunctorBase> pFunctor);

    /**
     * \brief Define the name of a bound method.
     * \param pName the name of the method
     * \param pClass the name of your class
     * \param pFunctionDescription the description of the method
     * \param pMask optional Mask, default 0.
     *              see almethodinfo.h for more information
     */
    void functionName(const std::string &pName,
                      const std::string &pClass,
                      const std::string &pFunctionDescription,
                      int pMask = 0);

    /**
     * \brief Add a documented parameter to a method.
     *
     * \param pName the name of the parameter
     * \param pDesc the description of the parmeter
     */
    void addParam(const std::string &pName,
                  const std::string &pDesc);

    /**
     * \brief Add a module example.
     * \param pLanguage the language of the example (c++, python, .net, etc)
     * \param pExample the example
     */
    void addModuleExample(const std::string &pLanguage,
                          const std::string &pExample);

    /**
     * \brief Add a method example.
     * \param pLanguage the language of the example (c++, python, .net, etc)
     * \param pExample the example
     */
    void addMethodExample(const std::string &pLanguage,
                          const std::string &pExample);

    /**
     * \brief Sets the description of the return value.
     * \param pName the name of the return item (used in autogeneration)
     * \param pDesc the description of the return item
     */
    void setReturn(const std::string &pName, const std::string &pDesc);

    virtual qi::Future<qi::AnyReference> metaCall(qi::AnyObject context, unsigned int method, const qi::GenericFunctionParameters &in, qi::MetaCallType callType, qi::Signature returnSignature);


    qi::AnyObject asObject();

    /**
     * Used only for naoqi1/naoqi2 compatibility layers. Do not use unless you
     * know what you are doing
     */
    qi::DynamicObjectBuilder& getBuilder() {return _builder;};


    /**
     * Used for simulating old naoqi1 post behavior that return an id
     */
    int pCall(const qi::AnyArguments& args);

  protected:
    /**
     * \brief Call at every module creation.
     *
     *        User can overload it
     */
    virtual void init(void) {}

  private:
    int _pCall(const unsigned int &methodId, const std::vector<qi::AnyValue> &args);

  protected:
    qi::DynamicObjectBuilder _builder;
    friend class baseModule; // for inaoqi that needs to advertise methods
  public:
    qi::GenericObject _go;
    ALModuleCorePrivate *_p;
    qi::MetaMethodBuilder _mBuilder;

  };  // !ALModuleCore
}

#endif  // _LIBALCOMMON_ALCOMMON_ALMODULECORE_H_
