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

#include "FindQuads.hpp"

//#define DEBUG_FindQuads
#ifdef DEBUG_FindQuads
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core_c.h> // CV_AA
#endif

#include <iostream>
#include <cmath> //abs
#include <set>
#include <map>
#include <algorithm>

#define MIN_QUAD_SIZE 10

using namespace std;
using namespace cv;

bool intersection(const Point2f& o1, const Point2f& p1, const Point2f& o2, const Point2f& p2, Point2f &r)
{
    Point2f x = o2 - o1;
    Point2f d1 = p1 - o1;
    Point2f d2 = p2 - o2;

    float cross = d1.x*d2.y - d1.y*d2.x;
    if (abs(cross) < /*EPS*/1e-8)
        return false;

    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
    r = o1 + d1 * t1;
    return true;
}

void mergePoints(vector<Vec4f>& lines, vector<Vec2f>& points, vector<Vec2i>& segs_idx) {

    for (auto& seg : lines) {

        Point2f seg00 = {seg[0], seg[1]};
        Point2f seg01 = {seg[2], seg[3]};

        auto len = norm(seg00 - seg01);
        // discard too small segments
        if (len < MIN_QUAD_SIZE) {continue;}
        //auto min_dist = max(1., min(0.1*len, 10.));

        for (auto& seg2 : lines) {

            Point2f seg10 = {seg2[0], seg2[1]};
            Point2f seg11 = {seg2[2], seg2[3]};

            if (seg00 == seg10 && seg01 == seg11) {continue;}

            auto len2 = norm(seg10 - seg11);
            auto min_dist = 0.2*min(len,len2);

            Point2f corner;
            if (!intersection(seg00, seg01, seg10, seg11, corner)) {continue;}

            if (    norm(seg00 - corner) < min_dist
                &&  norm(seg10 - corner) < min_dist) {
                seg[0] = corner.x;
                seg[1] = corner.y;
                seg2[0] = corner.x;
                seg2[1] = corner.y;
                continue;
            }
            if (    norm(seg01 - corner) < min_dist
                &&  norm(seg10 - corner) < min_dist) {
                seg[2] = corner.x;
                seg[3] = corner.y;
                seg2[0] = corner.x;
                seg2[1] = corner.y;
                continue;
            }

            if (    norm(seg00 - corner) < min_dist
                &&  norm(seg11 - corner) < min_dist) {
                seg[0] = corner.x;
                seg[1] = corner.y;
                seg2[2] = corner.x;
                seg2[3] = corner.y;
                continue;
            }

            if (    norm(seg01 - corner) < min_dist
                &&  norm(seg11 - corner) < min_dist) {
                seg[2] = corner.x;
                seg[3] = corner.y;
                seg2[2] = corner.x;
                seg2[3] = corner.y;
                continue;
            }
        }
    }

    for (auto& seg : lines) {

        Vec2f p0 = {seg[0], seg[1]};
        Vec2f p1 = {seg[2], seg[3]};

        int i = -1;
        int j = -1;

        auto it = find(points.begin(), points.end(), p0);
        if (it == points.end()) {
            points.push_back(p0);
            i = points.size()-1;
        }
        else {i = it - points.begin();}

        it = find(points.begin(), points.end(), p1);
        if (it == points.end()) {
            points.push_back(p1);
            j = points.size()-1;
        }
        else {j = it - points.begin();}

        segs_idx.push_back({i,j});
    }
}


chilitags::FindQuads::FindQuads(
        const cv::Mat *pBinaryImage) :
    mBinaryImage(pBinaryImage),
    mQuads(),
    lsd(createLineSegmentDetector(LSD_REFINE_NONE))
    //lsd(createLineSegmentDetector(LSD_REFINE_ADV))
{
#ifdef DEBUG_FindQuads
    cv::namedWindow("FindQuads");
#endif
}

chilitags::FindQuads::~FindQuads()
{
}

void chilitags::FindQuads::run()
{
    //TODO function too long, split it

    mQuads.clear();
    const cv::Mat tBinaryImage = *mBinaryImage;

    vector<Vec4f> lines;
    lsd->detect(tBinaryImage, lines);

#ifdef DEBUG_FindQuads
    // These constants will be given to OpenCv for drawing with
    // sub-pixel accuracy with fixed point precision coordinates
    static const int scShift = 16;
    static const float scPrecision = 1<<scShift;
    const static cv::Scalar scColor(255, 0, 255);

    Mat tDebugImage(tBinaryImage);

    cout << "Found " << lines.size() << " lines (" << 2*lines.size() << " points)" << endl;
#endif

    // merge close segments end
    vector<Vec2f> points;
    vector<Vec2i> segs_idx;
    mergePoints(lines, points, segs_idx);

    map<int, vector<int>> adjacency_list;

    for (auto& p : segs_idx) {
        adjacency_list[p[0]].push_back(p[1]);
        adjacency_list[p[1]].push_back(p[0]);
    }

    // remove all points that do not have connections to 2 other points
    for (auto it = adjacency_list.cbegin(); it != adjacency_list.cend() /* not hoisted */; /* no increment */)
    {
        if (it->second.size() != 2)
        {
            adjacency_list.erase(it++);
        }
        else
        {
            ++it;
        }
    }

    set<int> unexplored;
    // store the list of vertices
    for (auto& kv : adjacency_list) {unexplored.insert(kv.first);}
    
    vector<vector<int>> connected_components;

    for (auto it = unexplored.cbegin(); it != unexplored.cend() /* not hoisted */; /* no increment */)
    {
        vector<int> component;
        vector<int> queue;
        component.push_back(*it);
        queue.push_back(*it);
        unexplored.erase(it++); // mark the node as explored
        while(!queue.empty()) {
            auto n = queue.back();
            queue.pop_back();
            for (auto i : adjacency_list[n]) {
                if (unexplored.count(i) == 1) {
                    if (*it == i) {it++;}
                    unexplored.erase(i);
                    component.push_back(i);
                    queue.push_back(i);
                }
            }
        }
        if (component.size() == 4) {
            connected_components.push_back(component);
        }
    }

    for (auto& quad : connected_components) {
        vector<Point2f> hull;
        vector<Point2f> rawquad = {points[quad[0]],
                                points[quad[1]],
                                points[quad[3]],
                                points[quad[2]]};
        convexHull(rawquad,
                    hull, false);
        mQuads.push_back(Quad(hull));

    }

#ifdef DEBUG_FindQuads
    cout << "After merging, " << segs_idx.size() << " lines (" << points.size() << " points)" << endl;

    cout << connected_components.size() << " connected components" << endl;
    for (auto line : lines) {
            cv::line(
                tDebugImage,
                scPrecision*Point2f(line[0],line[1]),
                scPrecision*Point2f(line[2],line[3]),
                CV_RGB(0,0,0), 1, CV_AA, scShift);
 
    }

    for (auto& quad : connected_components) {

            cv::line(
                tDebugImage,
                scPrecision*Point2f(points[quad[0]]),
                scPrecision*Point2f(points[quad[1]]),
                scColor, 1, CV_AA, scShift);
            cv::line(
                tDebugImage,
                scPrecision*Point2f(points[quad[1]]),
                scPrecision*Point2f(points[quad[3]]),
                scColor, 1, CV_AA, scShift);
            cv::line(
                tDebugImage,
                scPrecision*Point2f(points[quad[3]]),
                scPrecision*Point2f(points[quad[2]]),
                scColor, 1, CV_AA, scShift);
            cv::line(
                tDebugImage,
                scPrecision*Point2f(points[quad[2]]),
                scPrecision*Point2f(points[quad[0]]),
                scColor, 1, CV_AA, scShift);
    }

    cv::imshow("FindQuads", tDebugImage);
    //cv::waitKey(0);
#endif



/*
        if (points.empty()) {
            points.push_back({p[0], p[1]});
            points.push_back({p[2], p[3]});
            segs_idx.push_back({0,1});
            continue;
        }
        int j = -1;
        int k = -1;
        for (size_t i=0; i < points.size();i++) {
            if (j == -1
                && abs(points[i][0] - p[0]) < MIN_DIST
                && abs(points[i][1] - p[1]) < MIN_DIST) 
            {
                j = i;
                continue;
            }
            if (k == -1
                && abs(points[i][0] - p[2]) < MIN_DIST
                && abs(points[i][1] - p[3]) < MIN_DIST) 
            {
                k = i;
                continue;
            }
        }

        if (j == -1) {// no merging occured for first seg end
            points.push_back({p[0], p[1]});
            j = points.size() - 1;
        }

        if (k == -1) {// no merging occured for second seg end
            points.push_back({p[2], p[3]});
            k = points.size() - 1;
        }
        segs_idx.push_back({j,k});
    }
*/
}

