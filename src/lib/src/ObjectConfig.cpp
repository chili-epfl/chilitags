#include <fstream>
#include <cmath>  // for std::sin, std::cos

#include "ObjectConfig.hpp"

using namespace std;
using namespace cv;
#ifdef WITH_YAML
using namespace YAML;
#endif
using namespace chilitags;

ObjectConfig::ObjectConfig(const string& configuration) {

#ifdef WITH_YAML
    ifstream fin(configuration);
    Parser parser(fin);
    Node doc;
    parser.GetNextDocument(doc);
    parse(doc);
#endif

}

#ifdef WITH_YAML
ObjectConfig::ObjectConfig(const Node& configuration) {
    parse(configuration);
}

void operator >> (const YAML::Node& node, array<float,3>& array) {
    node[0] >> array[0];
    node[1] >> array[1];
    node[2] >> array[2];
}

void operator >> (const YAML::Node& node, MarkerConfig& conf) {

    node["marker"] >> conf.id;
    node["size"] >> conf.size;
    if(const YAML::Node *pVec = node.FindValue("translation")) *pVec >> conf.translation;
    if(const YAML::Node *pVec = node.FindValue("rotation")) *pVec >> conf.rotation;
    if(const YAML::Node *pBool = node.FindValue("keep")) *pBool >> conf.keep;

}
#endif

vector<Object> ObjectConfig::objects() const {
    return _objects;
}

const Object* ObjectConfig::usedBy(int markerId) const {

    for (auto& o : _objects) {
        for (auto& m : o.markers) {
            // here, we return a pointer to an element of
            // a vector<Object> which is dangerous: if 
            // elements are added to the vector, it may
            // resize and the pointer would become invalid.
            // In our case it's however ok since _objects
            // is only modified at construction.
            if (m.id == markerId) return &o;
        }
    }
    return nullptr;

}

const MarkerConfig* ObjectConfig::marker(int markerId) const {

    return _markers.at(markerId);

}

#ifdef WITH_YAML
void ObjectConfig::parse(const YAML::Node& configuration){

    for(auto it=configuration.begin();
             it!=configuration.end();
             ++it) {

        Object object;

        it.first() >> object.name;

        for(auto marker=it.second().begin();marker!=it.second().end();++marker) {
            MarkerConfig config;

            *marker >> config;

            computeCorners(config);

            object.markers.push_back(config);
        }

        _objects.push_back(object);

        // store the markers pointer only *after* the object is
        // stored in _objects, else we won't point to the correct
        // address.
        for (auto& m : _objects.back().markers) {
            _markers[m.id] = &m;
        }
    }

}
#endif // WITH_YAML

void ObjectConfig::computeCorners(MarkerConfig& marker) const {

    static const float RAD2DEG = 3.141593 / 180.;
    auto half = marker.size / 2;

    marker.localcorners[0] = Point3f(-half,-half,0.);
    marker.localcorners[1] = Point3f(half,-half,0.);
    marker.localcorners[2] = Point3f(half,half,0.);
    marker.localcorners[3] = Point3f(-half,half,0.);


    // Rotation matrix computation: cf The Matrix and Quaternions FAQ
    // http://www.cs.princeton.edu/~gewang/projects/darth/stuff/quat_faq.html#Q36
    
    auto A = cos(marker.rotation[0] * RAD2DEG);
    auto B = sin(marker.rotation[0] * RAD2DEG);
    auto C = cos(marker.rotation[1] * RAD2DEG);
    auto D = sin(marker.rotation[1] * RAD2DEG);
    auto E = cos(marker.rotation[2] * RAD2DEG);
    auto F = sin(marker.rotation[2] * RAD2DEG);

    Matx44f transformation(
            C*E,        -C*F,       D,    marker.translation[0],
            B*D*E+A*F,  -B*D*F+A*E, -B*C, marker.translation[1],
            -A*D*E+B*F, A*D*F+B*E,  A*C,  marker.translation[2],
            0.,         0.,         0.,   1.);

    for (auto i : {0, 1, 2, 3}) {
        Matx41f corner(marker.localcorners[i].x,
                       marker.localcorners[i].y,
                       marker.localcorners[i].z,
                       1.0);
        auto tCorner = transformation * corner;
        marker.corners[i] = Point3f(tCorner(0), tCorner(1), tCorner(2));
    }
}


/*
// Usage example
int main() {

    auto objects = ObjectConfig("markers.yml").objects();

    for (auto o : objects) {
        std::cout << "Found object: " << o.name << std::endl;

        for (auto marker:o.markers) {
            cout << "\tMarker " << marker.id << endl;
            cout << "\t\ttranslation: [";
            copy(marker.translation.begin(), marker.translation.end(), ostream_iterator<float>(cout, ", "));
            cout << "]" << endl;
            cout << "\t\trotation: [";
            copy(marker.rotation.begin(), marker.rotation.end(), ostream_iterator<float>(cout, ", "));
            cout << "]" << endl;
            cout << "\t\tkeep: " << marker.keep << endl;
        }
    }


    return 0;
}
*/
