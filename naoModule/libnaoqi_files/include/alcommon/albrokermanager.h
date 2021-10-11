/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011, 2012 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALCOMMON_ALCOMMON_ALBROKERMANAGER_H_
#define _LIBALCOMMON_ALCOMMON_ALBROKERMANAGER_H_

# include <alcommon/api.h>
# include <vector>
# include <boost/shared_ptr.hpp>

# define MAXBROKER 10   /**< Broker's max number */

namespace AL
{
  class ALBroker;
  class ALBrokerManagerPrivate;

  /**
   * \class ALBrokerManager albrokermanager.h "alcommon/albrokermanager.h"
   * \brief ALBrokerManager is a class to manage brokers.
   *
   *        It should be only singleton with various main pointer.
   * \ingroup Broker
   */
  class ALBrokerManager
  {
  protected:
    /** \brief Constructor. */
    ALBrokerManager();
    ALBrokerManager(const ALBrokerManager &);
    ALBrokerManager &operator=(const ALBrokerManager &);
  public:
    /** \brief Destructor. */
    virtual ~ALBrokerManager();

    /**
     * \brief Add a Broker in the map of broker.
     *
     *        Add a broker to the map if it do not already exist.
     * \param pBroker pointer to a broker
     */
    void addBroker(boost::shared_ptr<ALBroker> pBroker);

    /**
     * \brief Remove a broker from the map of broker.
     * \warning It will also shutdown the broker.
     * \param pBroker pointer to a broker
     */
    void removeBroker(boost::shared_ptr<ALBroker> pBroker);

    /**
     * \brief Remove a broker from the map of broker.
     *
     *        It won't shutdown of the broker
     * \param pBroker pointer to a broker
     */
    void removeFromList(boost::shared_ptr<ALBroker> pBroker);

    /**
     * \brief Get the suitable broker.
     *
     * \param brokerName name of wanted broker
     */
    boost::shared_ptr<ALBroker> getBrokerByName(const std::string &brokerName);

    /**
     * \brief Get the first broker in the list.
     * \return A pointer to a broker, throw if broker's list is empty
     * \throw ALERROR
     */
    boost::shared_ptr<ALBroker> getRandomBroker(void);

    /**
     * \brief Get a broker from index.
     * \param i index to the broker
     * \return A pointer to the broker.
     */
    boost::shared_ptr<ALBroker> getBroker(int i);

    /**
     * \brief Get a broker from IP and port address.
     * \param strEndPoint broker's address, format "127.0.0.1:5559/"
     * \return A pointer to the broker if we find it,
     *         a pointer to the first borker in the list otherwise.
     */
    boost::shared_ptr<ALBroker> getBrokerByIPPort(const std::string &strEndPoint);


    /**
     * \brief Get a broker by port address.
     * \param strIP broker's IP (unused)
     * \param pPort broker's port
     * \return A pointer to the broker if we find it,
     *         a pointer to the first borker in the list otherwise.
     */
    boost::shared_ptr<ALBroker> getBrokerByIPPort(const std::string &strIP,
                                                  int pPort);

    /**
     * \brief Get a broker by parent's broker port.
     * \param strIP broker's IP (unused)
     * \param pPort parent's port the broker
     * \return A pointer to the broker, boost::shared_ptr<ALBroker>() otherwise
     */
    boost::shared_ptr<ALBroker> getBrokerByParentIPPort(const std::string &strIP, int pPort);

    /**
     * \brief Remove and shutdown all brokers.
     * \warning Program should not work any more after that.
     */
    void killAllBroker(void);

    /**
     * \brief Create a empty broker.
     * \return A pointer to a Broker
     */
    boost::shared_ptr<ALBroker> getReservedBroker(void);

    /**
     * \brief Get the ALBrokerManager singleton.
     * \return A poitner to the instance of the ALBrokerManager
     */
    static boost::shared_ptr<ALBrokerManager> getInstance();

    /**
     * \brief Set the ALBrokerManager singleton.
     * \warning It will kill the old singleton to replace it by the new one
     * \param pSingleton A pointer to a new ALBrokerManager
     * \return A poitner to the new instance of the ALBrokerManager
     */
    static boost::shared_ptr<ALBrokerManager> setInstance(boost::shared_ptr<ALBrokerManager> pSingleton);

    /**
     * \brief Reset the ALBrokerManager singleton
     */
    static void kill();

  private:
    /** ALBrokerManager singleton. */
    static boost::shared_ptr<ALBrokerManager> *_singleton;

  public:
    /** A pointer to the private implementation of ALBrokerManager. */
    ALBrokerManagerPrivate                   *_p;
  };
}  // !namespace AL
#endif  // _LIBALCOMMON_ALCOMMON_ALBROKERMANAGER_H_
