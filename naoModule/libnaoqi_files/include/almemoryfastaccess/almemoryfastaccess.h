/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALMEMORYFASTACCESS_ALMEMORYFASTACCESS_ALMEMORYFASTACCESS_H_
#define _LIBALMEMORYFASTACCESS_ALMEMORYFASTACCESS_ALMEMORYFASTACCESS_H_

#include <alvalue/alvalue.h>
#include <alproxies/almemoryproxy.h>

#include <boost/shared_ptr.hpp>

namespace AL
{
  class ALProxy;
  class ALBroker;

  /**
   * \class ALMemoryFastAccess almemoryfastaccess/almemoryfastaccess.h
   * \brief ALMemoryFastAccess is a fast access in Read/Write to some variables of ALMemory.
   *
   * ALMemoryFastAccess is a fast access in Read/Write to some variables
   * of ALMemory regularily accessed, with a unified interface.
   *
   *   - if ALMemory is in same broker than the caller:
   *     store directly pointer to data (hack* method)
   *   - if ALMemory is remote with the caller:
   *     standard call (not so optimised, but the more optimal possible access)
   *
   *   - ASSUME: variables never disappear.
   *   - ASSUME: variables are all floats or ints.
   * \ingroup libalmemoryfastaccess
   */
  class ALMemoryFastAccess
  {
    /**
     * \typedef TVariablePtrArray
     * \brief Vector of float pointer
     */
    typedef std::vector<float *>              TVariablePtrArray;
    /**
     * \typedef TFloatPtrArray
     * \brief Vector of float pointer
     */
    typedef std::vector<float *>              TFloatPtrArray;
    /**
     * \typedef TIntPtrArray
     * \brief Vector of int pointer
     */
    typedef std::vector<int *>                TIntPtrArray;
    /**
     * \typedef ITVariablePtrArray
     * \brief Iterator on a vector of float pointer
     */
    typedef TVariablePtrArray::iterator       ITVariablePtrArray;
    /**
     * \typedef CITVariablePtrArray
     * \brief Iterator on a vector of float pointer
     */
    typedef TVariablePtrArray::const_iterator CITVariablePtrArray;

  public:
    /**
     * \brief Default constructor.
     */
    ALMemoryFastAccess();

    /**
     * \brief Default destructor.
     */
    ~ALMemoryFastAccess();


    /**
     * \brief Remove all pointer.
     */
    void StopAllAccess(void);

    /**
     * \brief Insert a binary ALValue in ALMemory.
     * \param pName value
     * \param pBuff ALValue
     */
    void insertBuffer(const std::string &pName,
                      const ALValue &pBuff);

    /**
     * \brief First time, you must "connect" to variables to access later,
     *        many times.
     * \param pBroker a pointer to the broker
     * \param pListVariables list of variable names,
     *                       eg: {"DCM/Sensor1", "DCM/Sensor2"} ...
     * \param bAllowNonExistantVariable unused parameter
     */
    void ConnectToVariables(const boost::shared_ptr<AL::ALBroker> pBroker,
                            const std::vector<std::string> &pListVariables,
                            bool bAllowNonExistantVariable = false);

    /**
     * \brief First time, you must "connect" to int variables to access later,
     *        many times.
     * \param pBroker a pointer to the broker
     * \param pListVariables list of variable names,
     *                       eg: {"DCM/Sensor1", "DCM/Sensor2"} ...
     */
    void ConnectToIntVariables(const boost::shared_ptr<AL::ALBroker> pBroker,
                               const std::vector<std::string> &pListVariables);

    /**
     * \brief Get pointer on 32bit data
     * \param pBroker a pointer to the broker
     * \param pStrValue value name
     * \param bAllowUnexistantVariable unused parameter
     */
    static void *getDataPtr(boost::shared_ptr<AL::ALBroker> pBroker,
                            const std::string &pStrValue,
                            bool bAllowUnexistantVariable);

    /**
     * \brief Get pointer on 32bit data
     * \param pMemoryProxy a pointer to the memory
     * \param pStrValue value name
     * \param pValue value to insert if pStrValue is non-existent
     */
    template<typename T>
    static T *getSafeDataPtr(boost::shared_ptr<ALMemoryProxy> pMemoryProxy,
                             const std::string &pStrValue,
                             T pValue)
    {
      bool insertData = false;

      try
      {
        insertData = !pMemoryProxy->getData(pStrValue).isValid();
      }
      catch(const std::exception &)
      {
        // If the data doesn't exist in memory getData return an invalid ALValue
        // or throw. So in this case we try to insert data before getting pointer.
        insertData = true;
      }

      if(insertData)
      {
        pMemoryProxy->insertData(pStrValue, pValue);
      }

      return static_cast<T*>(pMemoryProxy->getDataPtr(pStrValue));
    }

    /**
     * \brief FIXME: No implementation.
     * \param pBroker a pointer to the broker
     * \param pListVariables list of variable names,
     *                       eg: {"DCM/Sensor1", "DCM/Sensor2"} ...
     * \param bAllowUnexistantVariable unused parameter
     */
    void directConnectToVariables(const boost::shared_ptr<AL::ALBroker> pBroker,
                                  const std::vector<std::string> &pListVariables,
                                  bool bAllowUnexistantVariable = false);

    /**
     * \brief Get previous "connected" variables.
     * \param pListValue where to put the gathered value of variables
     */
    void GetValues(std::vector<float> &pListValue) const;

    /**
     * \brief Set previous "connected" variables.
     * \param pListValue Value of variables to put into memory.
     */
    void SetValues(const std::vector<float> &pListValue);

    /**
     * \brief Get previous "connected" variables.
     * \param pListValue where to put the gathered value of variables
     */
    void GetValues(std::vector<int> &pListValue) const;

    /**
     * \brief Set previous "connected" variables.
     * \param pListValue Value of variables to put into memory.
     */
    void SetValues(const std::vector<int> &pListValue);

#ifdef DEBUG
    /**
     * \brief Disable fatal error, if values connecting doesn't exists
     * \warning this is a debug functionnality only.
     */
    inline void DisableCheckOnNotExistingValueOrThings_Debug(void) { fbDisableCheking_Debug = true; };
#endif

    /**
     * \brief Test function.
     * \param pBroker a pointer to the broker
     * \return true if test ok, false otherwise
     */
    static bool InnerTest(const boost::shared_ptr<AL::ALBroker> pBroker);

  private:
    /**
     * \brief Get data from name's value.
     * \param pName name's value you want
     */
    static ALValue* getBuffer(const std::string &pName);

    /** A pointer to ALProxy (ALMemory) */
    boost::shared_ptr<AL::ALProxy> fMemoryProxy;

    /** true if ALMemory is local to us */
    bool              fbIsLocal;
    /** local case: direct memory pointer access where the data is stored */
    TVariablePtrArray fListVariablePtr;
    /** local case: direct memory pointer access where the data is stored */
    TFloatPtrArray    fListFloatPtr;
    /** local case: direct memory pointer access where the data is stored */
    TIntPtrArray      fListIntPtr;


    /** remote case: the format of the GetListData Command to send */
    ALValue           fCommandToGetData;
    /** remote case: the format of the GetListData Command to send */
    ALValue           fCommandToSetData;

    /** if true, stop all access (usually ALMemory has been destroyed) */
    bool       fStopAllAccess;

#ifdef DEBUG
    /** if true, doesn't complaign if value doesn't exists */
    bool              fbDisableCheking_Debug;
#endif
  };

} // !namespace AL
#endif  // _LIBALMEMORYFASTACCESS_ALMEMORYFASTACCESS_ALMEMORYFASTACCESS_H_
