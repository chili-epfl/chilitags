/*
** Author(s):
**  - Cuche Herve <hcuche@aldebaran-robotics.com>
**
** Copyright (C) 2012 Cuche Herve
*/

#ifndef _ALPROXIES_NOTIFICATIONINFO_H_
# define _ALPROXIES_NOTIFICATIONINFO_H_

# include <string>
# include <iostream>
# include <alvalue/alvalue.h>
# include <alproxies/api.h>

namespace AL
{
  class NotificationInfoPrivate;
  class ALPROXIES_API NotificationInfo
  {
  public:
    NotificationInfo(const std::string &message,
                     const std::string &severity,
                     bool              removeOnRead = true);
    NotificationInfo(const AL::ALValue &notificationInfo);
    NotificationInfo(const NotificationInfo &rhs);
    NotificationInfo &operator=(const NotificationInfo &rhs);

    virtual ~NotificationInfo();

    int id() const;
    void setId(int id);

    std::string message() const;
    void setMessage(const std::string &message);

    std::string severity() const;
    void setSeverity(const std::string &severity);

    bool removeOnRead() const;
    void setRemoveOnRead(bool removeOnRead);

    AL::ALValue toALValue() const;

  public:
    NotificationInfoPrivate *_p;
  };
}

std::ostream &operator<<(std::ostream &stream,
                         const AL::NotificationInfo &notificationInfo);

#endif /* !_ALPROXIES_NOTIFICATIONINFO_H_ */
