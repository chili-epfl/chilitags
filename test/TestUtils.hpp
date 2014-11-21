/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
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

#ifndef TestUtils_HPP
#define TestUtils_HPP

#include <opencv2/core/core.hpp>

namespace TestUtils {

float mean(const std::vector<float>& vals)
{
    float sum = 0.0f;
    for(auto v : vals) sum += v;
    return sum/vals.size();
}

float variance(const std::vector<float>& vals)
{
    float current_mean = mean(vals);
    float temp = 0;
    for(auto v : vals)
        temp += (current_mean-v)*(current_mean-v);
    return temp/vals.size();
}

float sigma(const std::vector<float>& vals)
{
    return std::sqrt(variance(vals));
}

}

#endif
