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

#include <DetectChilitags.hpp>

#include "EnsureGreyscale.hpp"
#ifndef EXPERIMENTAL_LSD
#include "DetectEdges.hpp"
#endif
#include "FindQuads.hpp"
#include "ReadBits.hpp"
#include "Decode.hpp"
#include "Register.hpp"
#include "Refine.hpp"

// The class that takes care of all the detection of Chilitags.
namespace chilitags {

class DetectChilitags::Impl
{

public:

Impl(Registrar &pRegistrar = Registrar::GetDefault()):
	mRegistrar(pRegistrar),

	mEnsureGreyscale(),
#ifndef EXPERIMENTAL_LSD
	mDetectEdges(100, 200, 3),
#endif
	mFindQuads(),
	mRefine(),

	mReadBits(),
	mDecode(pRegistrar.GetTranscoder()),
	mRegister(pRegistrar)
{
}


void operator()(const cv::Mat pInputImage) {
	mEnsureGreyscale(pInputImage);
#ifndef EXPERIMENTAL_LSD
	mDetectEdges(mEnsureGreyscale.Image());
	mFindQuads(mDetectEdges.Image());
#else
	mFindQuads(mEnsureGreyscale.Image());
#endif
	mRefine(mEnsureGreyscale.Image(), mFindQuads.Quads());

	mRegistrar.reset();
	for (const auto & tQuad : mRefine.Quads()) {
		mReadBits(mEnsureGreyscale.Image(), tQuad);
		mDecode(mReadBits.Bits());
		mRegister(mDecode.TagId(), tQuad, mDecode.Orientation());
	}
}

protected:

Registrar &mRegistrar;

EnsureGreyscale mEnsureGreyscale;
#ifndef EXPERIMENTAL_LSD
DetectEdges mDetectEdges;
#endif
FindQuads mFindQuads;

ReadBits mReadBits;
Decode mDecode;
Register mRegister;
Refine mRefine;

};


DetectChilitags::DetectChilitags(Registrar &pRegistrar):
		mImpl(new Impl(pRegistrar))
{}

void DetectChilitags::operator()(const cv::Mat pInputImage) { mImpl->operator()(pInputImage); }

DetectChilitags::~DetectChilitags() = default;

}

