#pragma once
/*
**  Copyright (C) 2014 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _PYTHON_SRC_PYTRANSLATOR_HPP_
#define _PYTHON_SRC_PYTRANSLATOR_HPP_

#include <qi/translator.hpp>

namespace qi {
  namespace py {
    class PyTranslator: public qi::Translator {
      public:
        PyTranslator(const std::string &name);

        std::string translate1(const std::string &msg);
        std::string translate2(const std::string &msg, const std::string &domain);
    };

    void export_pytranslator();
  }
}

#endif
