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

#ifndef Pipeable_HPP
#define Pipeable_HPP

// Chilitags is structured into "Pipeables".
// For short, Pipeables are classes with a run() method that does not take
// any parameters. They are also linked list nodes, with a public start()
// method that iteratively call the instance's run() and the following's.
// The Pipeables typically get their input in the form of a reference
// passed to their constructor, and manage their own output.
class Pipeable
{
public:
Pipeable() : mNext(0){
}

virtual ~Pipeable(){
}

Pipeable(const Pipeable& pPipeable) : mNext(pPipeable.mNext){
}

Pipeable &operator=(const Pipeable& pPipeable) {
	mNext = pPipeable.mNext; return *this;
}

Pipeable &operator|(Pipeable &pNext){
	mNext = &pNext; return *mNext;
}

void start() {
	for (
	        Pipeable *tCurrent = this;
	        tCurrent != 0;
	        tCurrent = tCurrent->mNext)
	{
		tCurrent->run();
	}
};
void stop() {
	mNext = 0;
}

protected:
virtual void run() = 0;
Pipeable *mNext;
};


#endif
