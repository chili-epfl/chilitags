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

#ifndef Map_HPP
#define Map_HPP

#include "Pipeable.hpp"
#include <cstddef>

namespace chilitags {

template <class Iterable>
class Map : public Pipeable
{
public:

Map(const Iterable *pDomain) :
	mFunction(0),
	mVariable(),
	mDomain(pDomain){
}

const typename Iterable::value_type *Variable() const {
	return &mVariable;
}
void Function(Pipeable *pFunction){
	mFunction=pFunction;
}

protected:
void run()
{
	for (typename Iterable::const_iterator it = mDomain->begin();
		it != mDomain->end(); ++it)
	{
		mVariable = *it;
		mFunction->start();
	}
}

Pipeable *mFunction;
typename Iterable::value_type mVariable;
const Iterable *mDomain;

private:
Map(const Map&);
Map &operator=(const Map&);
};


}

#endif
