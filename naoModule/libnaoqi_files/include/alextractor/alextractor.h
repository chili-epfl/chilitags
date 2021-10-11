/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALEXTRACTOR_ALEXTRACTOR_ALEXTRACTOR_H_
#define _LIBALEXTRACTOR_ALEXTRACTOR_ALEXTRACTOR_H_

#include <alcommon/almodule.h>
#include <alextractor/config.h>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>

namespace AL
{
  class ALBroker;
  class ALExtractorPrivate;

  /**
   * \class ALExtractor alextractor.h "alextractor/alextractor.h"
   * \brief ALExtractor class implements an extractor.
   *
   * An extractor is a module which extracts some information
   * about the world. It can be activated to produce information.
   * \ingroup libalextractor
   */
  class ALEXTRACTOR_API ALExtractor: public ALModule
  {
  public:
    /**
     * \brief Constructor.
     *
     *        Create a extractor link to a broker.
     * \param pBroker pointer to the broker
     * \param pName name of the extractor
     */
    ALExtractor(boost::shared_ptr<ALBroker> pBroker,
                const std::string& pName);

    /** \brief Destructor. */
    virtual ~ALExtractor();

    /**
     * \brief Called by the "client" to tell that
     *        it is interested in the output values.
     * \param pSubscribedName Name of the client module
     * \param pPeriod period of the extractor
     * \param pPrecision precision of the extractor
     */
    virtual void subscribe(const std::string &pSubscribedName,
                           const int &pPeriod,
                           const float &pPrecision);

    /**
     * \brief Called by the "client" to tell that
     *        it is interested in the output values.
     *        Period and Precision specified by getDefaultPrecision()
     *        and getDefaultPeriod() will be used by default.
     * \param pSubscribedName Name of the client module
     */
    virtual void subscribe(const std::string &pSubscribedName);


    /**
     * \brief Called by the "client" to update the periode.
     * \param pSubscribedName Name of the client module
     * \param pPeriod period of the extractor
     */
    virtual void updatePeriod(const std::string &pSubscribedName,
                              const int &pPeriod);

    /**
     * \brief Called by the "client" to update the precision.
     * \param pSubscribedName Name of the client module
     * \param pPrecision precision of the extractor
     */
    virtual void updatePrecision(const std::string &pSubscribedName,
                                 const float &pPrecision);

    /**
     * \brief Called by the "client" to tell that
     *        it is not interested anymore in the output values.
     * \param pSubscribedName Name of the client module
     */
    virtual void unsubscribe(const std::string &pSubscribedName);

    /**
     * \brief Called by the "client" to get the
     *        current period chosen by the Extractor.
     * \return current period
     */
    virtual int getCurrentPeriod();

    /**
     * \brief Called by the "client" to get the
     *        current precision chosen by the Extractor.
     * \return current precision
     */
    virtual float getCurrentPrecision();

    /**
     * \brief Called by the "client" to get the period.
     * \param pSubscribedName Name of the client module
     * \return period I required
     */
    virtual int getMyPeriod(const std::string &pSubscribedName);

    /**
     * \brief Called by the "client" to get the precision.
     * \param pSubscribedName Name of the client module
     * \return precision I required
     */
    virtual float getMyPrecision(const std::string &pSubscribedName);

    /**
     * \brief Called by the "client" to get the
     *        information of all the current subscribers.
     * \return info, names and parameters of all subscribers
     */
    ALValue getSubscribersInfo();

    /**
     * \brief Called by the broker webpage to detail the module.
     * \return an optional extra description of the module
     */
    virtual std::string httpGet();

  protected:

    /**
     * \brief What the extractor shall do to start detection.
     *
     *
     * This method is called only once: when the first module subscribes.
     * \param pPeriod period of the extractor
     * \param pPrecision precision of the extractor
     */
    virtual void xStartDetection(const int pPeriod,
                                 const float pPrecision) = 0;

    /**
     * \brief Enables to do some custom updates when the period and/or
     * the precision have been updated
     *
     * This empty method can be overrided to do some custom updates
     * when the period and/or the precision have been updated.
     * \param pPeriod period of the extractor
     * \param pPrecision precision of the extractor
     */
    virtual void xUpdateParameters(const int pPeriod, const float pPrecision) {}

    /**
     * \brief What the extractor shall do to stop detection.
     *
     * this method is called only once: when the last module unsubscribes.
     */
    virtual void xStopDetection() = 0;


    /**
     * \brief Specifies the advertised period that should be chosen
     * by default when subscribe(std::string name) is used
     *
     * Implementing this method is optional. If not implemented, 30 ms will
     * be chosen.
     */
    virtual int getDefaultPeriod();

    /**
     * \brief Specifies the advertised precision that should be chosen
     * by default when subscribe(std::string name) is used
     *
     * Implementing this method is optional. If not implemented, 0 will
     * be chosen.
     */
    virtual float getDefaultPrecision();


    /**
     * \brief Specifies the minimum period (in ms) that can be set
     * for the extractor.
     *
     * Implementing this method is optional. If not implemented, 1 ms
     * will be chosen.
     */
    virtual int getMinimumPeriod();

    /**
     * \brief Specifies the maximum period (in ms) that can be set
     * for the extractor.
     *
     * Implementing this method is optional. If not implemented, no
     * maximum period will be set and the function will return -1.
     */
    virtual int getMaximumPeriod();

    /**
     * \brief Which values this extractor updates in ALMemory.
     * \return vector of modified value
     */
    virtual std::vector<std::string> getOutputNames(void);

    /**
     * \brief Retrieves the list of events updated by the extractor.
     * \return vector of events
     */
    std::vector<std::string> getEventList(void);

    /**
     * \brief Retrieves the list of memory keys updated by the extractor.
     * \return vector of memory keys
     */
    std::vector<std::string> getMemoryKeyList(void);

    /**
     * \brief Declares an event in ALMemory.
     */
    void declareEvent(const std::string& event);

    /**
     * \brief Initializes a memory key in ALMemory (with an empty ALValue).
     */
    void declareMemoryKey(const std::string& key);

  private:
    /** Pointer to ALExtractor private implementation */
    boost::scoped_ptr<ALExtractorPrivate> _private;
    /**
     * \brief updates fCurrentParameters from fSubscribedList.
     */
    void xUpdateParameters();


    boost::mutex fSubscriptionMutex;
  };
} // namespace AL

#endif  // _LIBALEXTRACTOR_ALEXTRACTOR_ALEXTRACTOR_H_

