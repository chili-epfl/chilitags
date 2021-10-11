/*******************************************************************************
*   Copyright (c) 2016-present, Bahar Irfan. All rights reserved.              *
*                                                                              *
*   This is the main file for ChilitagsModule (Chilitags for NAO Robot).       *
*                                                                              *
*   Please cite the following work if using this work:                         *
*                                                                              *
*      Chilitags for NAO Robot. B. Irfan and S. Lemaignan. University of       *
*     Plymouth, UK. https://github.com/birfan/chilitags. 2016.                 *
*                                                                              *
*      Chilitags 2: Robust Fiducial Markers for Augmented Reality. Q. Bonnard, *
*     S. Lemaignan, G.  Zufferey, A. Mazzei, S. Cuendet, N. Li, P. Dillenbourg.*
*     CHILI, EPFL, Switzerland. http://chili.epfl.ch/software. 2013.           *
*                                                                              *
*   Chilitags is free software: you can redistribute it and/or modify          *
*   it under the terms of the Lesser GNU General Public License as             *
*   published by the Free Software Foundation, either version 3 of the         *
*   License, or (at your option) any later version.                            *
*                                                                              *
*   Chilitags is distributed in the hope that it will be useful,               *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU Lesser General Public License for more details.                        *
*                                                                              *
*   ChilitagsModule is released under GNU Lesser General Public License v3.0   *
*   (LGPL3) in accordance with Chilitags (Bonnard et al., 2013). You should    *
*   have received a copy of the GNU Lesser General Public License along with   *
*   Chilitags.  If not, see <http://www.gnu.org/licenses/>.                    *
*******************************************************************************/

#ifndef _WIN32
# include <signal.h>
#endif

#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>
#include <alcommon/altoolsmain.h>
#include "chilitagsmodule.hpp"

#ifdef CHILITAGSMODULE_IS_REMOTE
# define ALCALL
#else
// when not remote, we're in a dll, so export the entry point
# ifdef _WIN32
#  define ALCALL __declspec(dllexport)
# else
#  define ALCALL
# endif
#endif

extern "C"
{
ALCALL int _createModule(boost::shared_ptr<AL::ALBroker> pBroker)
{
    // init broker with the main broker instance
    // from the parent executable
    AL::ALBrokerManager::setInstance(pBroker->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(pBroker);
    // create module instances
    AL::ALModule::createModule<ChilitagsModule>(pBroker, "ChilitagsModule");
    return 0;
}

ALCALL int _closeModule(  )
{
    return 0;
}
} // extern "C"


#ifdef CHILITAGSMODULE_IS_REMOTE
int main(int argc, char *argv[])
{
    // pointer to createModule
    TMainType sig;
    sig = &_createModule;
    // call main
    return ALTools::mainFunction("ChilitagsModule", argc, argv, sig);
}
#endif
