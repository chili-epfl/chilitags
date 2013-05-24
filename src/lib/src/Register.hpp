/*******************************************************************************
*   Copyright 2013 EPFL                                                        *
*                                                                              *
*   This file is part of chilitags.                                            *
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
*   You should have received a copy of the GNU Lesser General Public License   *
*   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         *
*******************************************************************************/

#ifndef Register_HPP
#define Register_HPP

#include "Pipeable.hpp"
#include <Registrar.hpp>
#include <Quad.hpp>

namespace chilitags {

class Register : public Pipeable
{
public:
Register(
        const int *pDecodedTag,
        const Quad *pCorners,
        const int *pRotation,
        Registrar &pRegistrar);

virtual ~Register();

protected:
void run();

const int *mDecodedTag;
const Quad *mCorners;
const int *mRotation;
Registrar &mRegistrar;

private:
Register(const Register&);
Register& operator=(const Register&);
};


}

#endif
