#ifndef OBJECTCONFIG_HPP
#define OBJECTCONFIG_HPP

#include <vector>
#include <array>
#include <unordered_map>
#include <memory> // for shared_ptr
#include <opencv2/core/core.hpp> // for Point3f (and FileStorage)

namespace chilitags {

struct MarkerConfig {
	MarkerConfig(int id):id(id),corners(),localcorners(){}
    int id;
    float size = 0.;
    std::array<float, 3> translation = {{0., 0., 0.}};
    // the rotation is specified as a XYZ Euler rotation,
    // ie, first a rotation around X, then around Y, then around Z
    std::array<float, 3> rotation = {{0., 0., 0.}};
    bool keep = false;

    // this array stores the 3D location of the 
    // 4 corners of the marker *in the parent 
    // object frame*. It is automatically computed.
    std::array<cv::Point3f, 4> corners;

    // this array stores the 3D location of the 
    // 4 corners of the marker *in the marker 
    // own frame*. It is automatically computed.
    std::array<cv::Point3f, 4> localcorners;
};

struct Object {
	Object():name(),markers(){}
    std::string name;
    std::vector<MarkerConfig> markers;
};

/**
 * ObjectConfig reads and stores markers configurations.
 *
 * A marker configuration allows to associate a marker to
 * an object name (ie, alias) with possibly a 6D transformation.
 * It also allows to associate several markers to the same object,
 * for robust detection.
 */
class ObjectConfig {

public:
    ObjectConfig(const std::string& configuration);

    std::vector<Object> objects() const;

    const Object* usedBy(int markerId) const;
    const MarkerConfig* marker(int markerId) const;
    const int nbMarkers() const {return _markers.size();}

private:
    void computeCorners(MarkerConfig& marker) const;
    std::vector<Object> _objects;
    std::unordered_map<int, const MarkerConfig*> _markers;

};

}

#endif
