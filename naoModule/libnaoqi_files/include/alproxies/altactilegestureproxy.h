// Generated for ALTactileGesture version 0

#ifndef ALTACTILEGESTUREPROXY_H_
#define ALTACTILEGESTUREPROXY_H_

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <qi/types.hpp>
#include <qitype/anyobject.hpp>

#include <alvalue/alvalue.h>
#include <alproxies/api.h>

namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALTactileGestureProxy;

  namespace detail {
    class ALTactileGestureProxyPostHandler
    {
    protected:
      ALTactileGestureProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALTactileGestureProxy;

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALTactileGestureProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALTactileGestureProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALTactileGestureProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALTactileGestureProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALTactileGestureProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Define touch gesture.
    /// 
    ///         :param sensor_sequence: List of strings that represent the
    ///         sequence of the desired gesture. For example, SingleFront
    ///         would be the following: ['000', '100', '000']. NOTE: All
    ///         sequences must start with '000' and all non-hold sequences
    ///         must end with '000'. Hold gestures should end with the touch
    ///         sequence you will be holding. For example, a SingleFrontHold
    ///         would be the following: ['000', '100'].
    /// 
    ///         :returns: If sequence is valid, the name of gesture to listen
    ///         for, RuntimeError otherwise.
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::string createGesture(const std::vector<std::string>& arg1);

    /// <summary>
    /// Define touch gesture.
    /// 
    ///         :param sensor_sequence: Comma-separated string that represents
    ///         the sequence of the desired gesture. For example, SingleFront
    ///         would be the following: "000,100,000". NOTE: All sequences
    ///         must start with '000' and all non-hold sequences must end with
    ///         '000'. Hold gestures should end with the touch sequence you
    ///         will be holding. For example, a SingleFrontHold would be the
    ///         following: "000,100".
    /// 
    ///         :returns: If sequence is valid, the name of gesture to listen
    ///         for, RuntimeError otherwise.
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::string createGesture(const std::string& arg1);

    /// <summary>
    /// Get the sequence associated with a gesture name
    /// 
    ///         :param sequence: Sequence you want the gesture name of
    /// 
    ///         :returns: Sequence (as list of strings) if it exists, None otherwise
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue getGesture(const std::vector<std::string>& arg1);

    /// <summary>
    /// Get the sequence associated with a gesture name
    /// 
    ///         :param sequence: Sequence you want the gesture name of
    /// 
    ///         :returns: Sequence (as list of strings) if it exists, None otherwise
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue getGesture(const std::string& arg1);

    /// <summary>
    /// Get all gestures that have been defined in the system
    /// 
    ///         :returns: Dictionary (Map<String, List<String>>) of all gestures
    /// </summary>
    std::map<std::string,std::vector<std::string> > getGestures();

    /// <summary>
    /// Get the sequence associated with a gesture name
    /// 
    ///         :param gesture_name: Name of gesture you want the sequence of
    /// 
    ///         :returns: Sequence (as list of strings) if it exists, None otherwise
    ///         
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<std::string> getSequence(const std::string& arg1);

    /// <summary>
    /// Set length of hold time.
    /// 
    ///         :param hold_time: Desired hold time, in seconds (Default: 0.8s)
    /// 
    ///         :returns: True if hold time successfully updated, RuntimeError otherwise.
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool setHoldTime(const float& arg1);

    /// <summary>
    /// Set length of hold time.
    /// 
    ///         :param hold_time: Desired hold time, in seconds (Default: 0.8s)
    /// 
    ///         :returns: True if hold time successfully updated, RuntimeError otherwise.
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool setHoldTime(const std::string& arg1);

    /// <summary>
    /// Set length of sequence time.
    /// 
    ///         :param sequence_time: Desired sequence time, in seconds (Default: 0.2s)
    /// 
    ///         :returns: True if sequence time successfully updated, RuntimeError otherwise.
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool setSequenceTime(const std::string& arg1);

    /// <summary>
    /// Update length of sequence time.
    /// 
    ///         :param sequence_time: Desired sequence time, in seconds (Default: 0.2s)
    /// 
    ///         :returns: True if sequence time successfully updated, RuntimeError otherwise.
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool setSequenceTime(const float& arg1);

    /// <summary>
    /// Update length of settling time.
    /// 
    ///         :param settle_time: Desired settling time, in seconds (Default: 0.04s)
    /// 
    ///         :returns: True if settle time successfully updated, RuntimeError otherwise.
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool setSettleTime(const std::string& arg1);

    /// <summary>
    /// Update length of settling time.
    /// 
    ///         :param settle_time: Desired settling time, in seconds (Default: 0.04s)
    /// 
    ///         :returns: True if settle time successfully updated, RuntimeError otherwise.
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool setSettleTime(const float& arg1);


    detail::ALTactileGestureProxyPostHandler post;
  };

}
#endif // ALTACTILEGESTUREPROXY_H_
