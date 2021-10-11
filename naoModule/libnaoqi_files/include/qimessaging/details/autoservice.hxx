#include <stdexcept>

namespace qi
{
  template <typename T>
  AutoService<T>::AutoService(const std::string& name, SessionPtr session)
    : qi::Trackable<AutoService<T> > (this)
    , _session(session)
    , _name(name)
  {
    Future<qi::AnyObject> fut = session->service(name);
    fut.connect(&AutoService::onServiceModified, this, fut);

    _session->serviceRegistered.connect(&AutoService::onServiceAdded, this, _2);
    _session->serviceUnregistered.connect(&AutoService::onServiceRemoved, this, _2);
  }

  template <typename T>
  AutoService<T>::~AutoService()
  {
    this->destroy();
  }

  template <typename T>
  void AutoService<T>::onServiceRemoved(const std::string& name)
  {
    if (name == _name)
    {
      {
        boost::mutex::scoped_lock scoped_lock(_mutex);
        _object = qi::Object<T>();
        _promise.reset();
      }
      serviceRemoved();
    }
  }

  template <typename T>
  void AutoService<T>::onServiceModified(const qi::Future<qi::AnyObject>& future)
  {
    if (!future.hasError())
    {
      {
        boost::mutex::scoped_lock scoped_lock(_mutex);
        _object = qi::Object<T>(future.value());
        if (!_promise.future().isFinished())
          _promise.setValue(0);
      }
      serviceAdded();
    }
    else
    { // A Service has been added, but it has been impossible to get it; so we delete it.
      {
        boost::mutex::scoped_lock scoped_lock(_mutex);
        _object = qi::Object<T>();
        _promise.reset();
      }
      serviceRemoved();
    }
  }

  template <typename T>
  void AutoService<T>::onServiceAdded(const std::string& name)
  {
    if (name == _name)
    {
      boost::mutex::scoped_lock scoped_lock(_mutex);
      qi::Future<qi::AnyObject> future = _session->service(name);
      future.connect(&AutoService::onServiceModified, this, future);
    }
  }

  /**
   * The compiler will recursively call operator-> on each returned object until he get a pointer
   * We return an qi::details::Keeper<T> to keep T* alive during the call
   * (Object<T> will be temporary stored on stack while the call is pending)
   */
  template <typename T>
  qi::detail::Keeper<T> AutoService<T>::operator->()
  {
    boost::mutex::scoped_lock scoped_lock(_mutex);
    qi::detail::Keeper<T> keeper = qi::detail::Keeper<T>(_object);
    if (keeper._obj)
      return keeper;
    else
      throw std::runtime_error("Service " + _name + " unavailable");
  }

  template <typename T>
  qi::detail::Keeper<T> AutoService<T>::operator->() const
  {
    boost::mutex::scoped_lock scoped_lock(_mutex);
    qi::detail::Keeper<T> keeper = qi::detail::Keeper<T>(_object);
    if (keeper._obj)
      return keeper;
    else
      throw std::runtime_error("Service " + _name + " unavailable");
  }

  template <typename T>
  const T* AutoService<T>::get() const
  {
    boost::mutex::scoped_lock scoped_lock(_mutex);
    if (_object)
      return &(*_object);
    else
      throw std::runtime_error("Service " + _name + " unavailable");
  }

  template <typename T>
  T* AutoService<T>::get()
  {
    boost::mutex::scoped_lock scoped_lock(_mutex);
    if (_object)
      return &(*_object);
    else
      throw std::runtime_error("Service " + _name + " unavailable");
  }

  template <typename T>
  T& AutoService<T>::operator*()
  {
    return *get();
  }


  template <typename T>
  qi::FutureSync<void> AutoService<T>::waitForReady()
  {
    return _promise.future();
  }

  template <typename T>
  qi::GenericObject* AutoService<T>::asGenericObject() const
  {
    boost::mutex::scoped_lock scoped_lock(_mutex);
    if (_object)
      return _object.asGenericObject();
    else
      throw std::runtime_error("Service " + _name + " unavailable");
  }

  /**
   * Warning: AutoService<AnyObject> is invalid.
   *
   * Prefere use AnyAutoService instead.
   */
  template <>
  class AutoService<qi::AnyObject>
  {
  private:
    virtual void forbiden() = 0;
  };


  namespace detail
  {
    template <typename T>
    class Keeper
    {
    public:
      Keeper(qi::Object<T>& obj)
        : _obj(obj)
      {
      }

      T* operator->()
      {
        return &(*_obj);
      }

      qi::Object<T> _obj;
    };
  }
}
