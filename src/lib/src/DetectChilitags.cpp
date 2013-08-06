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
#include "DetectEdges.hpp"
#include "FindQuads.hpp"
#include "Map.hpp"
#include "Undistort.hpp"
#include "ReadBits.hpp"
#include "Decode.hpp"
#include "Register.hpp"
#include "Refine.hpp"

chilitags::DetectChilitags::DetectChilitags(
        const cv::Mat *pInputImage,
        Registrar &pRegistrar) :
	mPipeline(0),
	mPipeables(),
	mRegistrar(pRegistrar)
{
	EnsureGreyscale *tEnsureGreyscale = new EnsureGreyscale(pInputImage);
	mPipeables.push_back(tEnsureGreyscale);
	DetectEdges *tDetectEdges = new DetectEdges(100, 200, 3, tEnsureGreyscale->GetOutputImage());
	mPipeables.push_back(tDetectEdges);
	FindQuads *tFindQuads = new FindQuads(tDetectEdges->GetOutputImage());
	mPipeables.push_back(tFindQuads);
	Map<Quad> *tMap = new Map<Quad>(
	        tFindQuads->QuadCorners(),
	        tFindQuads->NumQuads());
	mPipeables.push_back(tMap);
	*tEnsureGreyscale | *tDetectEdges | *tFindQuads | *tMap;

	Undistort *tUndistort = new Undistort(tEnsureGreyscale->GetOutputImage(), tMap->Variable());
	mPipeables.push_back(tUndistort);
	ReadBits *tReadBits = new ReadBits(tUndistort->GetOutputImage());
	mPipeables.push_back(tReadBits);
	Decode *tDecode = new Decode(tReadBits->GetBits(), pRegistrar.GetTranscoder());
	mPipeables.push_back(tDecode);
	Register *tRegister = new Register(tDecode->GetDecodedTag(), tMap->Variable(), tDecode->GetOrientation(), pRegistrar);
	mPipeables.push_back(tRegister);
	Refine *tRefine = new Refine(tEnsureGreyscale->GetOutputImage(), tDecode->GetDecodedTag(), pRegistrar);
	mPipeables.push_back(tRefine);
	*tUndistort | *tReadBits | *tDecode | *tRegister | *tRefine;
	tMap->Function(tUndistort);

	mPipeline = tEnsureGreyscale;
}

chilitags::DetectChilitags::~DetectChilitags()
{
	for(std::vector<Pipeable *>::iterator it = mPipeables.begin(); it != mPipeables.end(); ++it)
	{
		delete *it;
	}
}

void chilitags::DetectChilitags::update() {
	mRegistrar.reset();
	mPipeline->start();
}
