/*   Copyright 2013 EPFL                                                        *
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

#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <chilitags/chilitags.hpp>

namespace chilitags {
    chilitags::Chilitags &Get(){
        static Chilitags instance;
        return instance;
    }

    Chilitags3D &Get3D(){
        static Chilitags3D instance;
        return instance;
    }
}

extern "C" {

    ////////////////////////////////////////////////////////////////// Chilitags

    //void setFilter(int persistence, double gain);
    void setFilter(int persistence, double gain)
    {
        chilitags::Get().setFilter(persistence, gain);
    }

    //std::map<int, Quad> find(const cv::Mat &inputImage);
    char* find(uchar* input, int width, int height)
    {
        cv::Mat inputImage(height, width, CV_8U, input);
        
        std::ostringstream str;
        str.setf(std::ios::fixed, std::ios::floatfield);
        str.precision(4);
        str << "{ ";
        for(auto tag: chilitags::Get().find(inputImage)){
            cv::Mat_<cv::Point2f> tCorners(tag.second);
            str << "\"" << tag.first << "\":["
                << *tCorners[0] << ","
                << *tCorners[1] << ","
                << *tCorners[2] << ","
                << *tCorners[3] << "],";
        }
        std::string ret = str.str();
        ret[ret.size()-1] = '}';
        //FIXME memory leak
        char* output = (char*)malloc(sizeof(char) * (ret.length()+1));
        strcpy(output, ret.c_str());
        return output;
    }

    //cv::Matx<unsigned char, 6, 6> encode(int id) const;
    //TODO
    //int decode(const cv::Matx<unsigned char, 6, 6> &bits) const;
    //TODO
    //cv::Mat draw(int id, int cellSize = 1, bool withMargin = false) const;
    //TODO

    //////////////////////////////////////////////////////////////// Chilitags3D

    //void setFilter(int persistence, double gain);
    void set3DFilter(int persistence, double gain)
    {
        chilitags::Get3D().setFilter(persistence, gain);
    }

    //getChilitags()
        //void setFilter(int persistence, double gain);
        void set2DFilter(int persistence, double gain)
        {
            chilitags::Get3D().getChilitags().setFilter(persistence, gain);
        }

        //std::map<int, Quad> find(const cv::Mat &inputImage);
        //TODO

    //std::map<std::string, cv::Matx44d> estimate(const std::map<int, Quad> & tags);
    //TODO

    //std::map<std::string, cv::Matx44d> estimate(const cv::Mat &inputImage);
    char* estimate(uchar* input, int width, int height, bool rectification)
    {
        cv::Mat inputImage = cv::Mat(height, width, CV_8U, input);
        
        std::ostringstream str;
        str.setf(std::ios::fixed, std::ios::floatfield);
        str.precision(4);
        str << "{ ";
        for(auto& kv : chilitags::Get3D().estimate(inputImage)){
            str << "\"" << kv.first << "\":[";
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    str << kv.second(i, j);
                    if(i != 3 || j != 3) str << ",";
                }
            }
            str << "],";
        }
        std::string ret = str.str();
        ret[ret.size()-1] = '}';
        char* output = (char*)malloc(sizeof(char) * (ret.length()+1));
        strcpy(output, ret.c_str());

        //undistortion of image
        if(rectification){
            cv::Mat originalImage = inputImage.clone();
            undistort(originalImage, inputImage, chilitags::Get3D().getCameraMatrix(), chilitags::Get3D().getDistortionCoeffs());
        }
        return output;
    }

    //void readTagConfiguration(
    //    const std::string &filename,
    //    bool omitOtherTags = false);
    void readTagConfiguration(const char* filename, bool omitOtherTags)
    {
        chilitags::Get3D().readTagConfiguration(filename, omitOtherTags);
    }

    //void setDefaultTagSize(float defaultSize);
    void setDefaultTagSize(float defaultSize) {
        chilitags::Get3D().setDefaultTagSize(defaultSize);
    }

    //void setCalibration(cv::InputArray newCameraMatrix,
    //                    cv::InputArray newDistCoeffs);
    //TODO

    //cv::Size readCalibration(const std::string &filename);
    void readCalibration(const char* filename)
    {
        chilitags::Get3D().readCalibration(filename);
    }

    //const cv::Mat &getCameraMatrix()     const;
    void getCameraMatrix(float *matrixData)
    {
        auto cameraMatrix = chilitags::Get3D().getCameraMatrix();
        for (int i = 0; i < 9; ++i) {
            matrixData[i] = cameraMatrix.at<double>(i);
        }
    }

    //const cv::Mat &getDistortionCoeffs() const;
    int getDistortionCoeffs(float *coeffsData)
    {
        auto coeffs = chilitags::Get3D().getCameraMatrix();
        for (int i = 0; i < 9; ++i) {
            coeffsData[i] = coeffs.at<double>(i);
        }
        return coeffs.size().area();
    }

}
