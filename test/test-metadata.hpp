#ifndef TestMetadata_HPP
#define TestMetadata_HPP

namespace TestMetadata {

struct TestCase {
    std::string filename;
    std::vector<int> expectedTagIds;
    std::vector<int> knownMissedTagIds;
    bool isExpected   (int id) const {
        return contains(expectedTagIds,    id);
    }
    bool isKnownToMiss(int id) const {
        return contains(knownMissedTagIds, id);
    }
    static bool contains(const std::vector<int> &v, int x) {
        return std::find(v.begin(), v.end(), x) != v.end();
    }
};

// The string is the filename of an image,
// the first list correspond to the ids of tags shown on the image,
// and the second list to the ids of the tags that are undetected.
std::vector< TestCase > all = {
    {"stills/4360x2448/smartphone01.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34},
#ifdef EXPERIMENTAL_LSD
        {9,17,29}},
#else
     {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34}},
#endif
    {"stills/4360x2448/smartphone02.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34},
#ifdef EXPERIMENTAL_LSD
        {6,11,20,21,27,28,33,34}},
#else
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34}},
#endif
    {"stills/4360x2448/smartphone04.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34},
#ifdef EXPERIMENTAL_LSD
        {1,2,3,4,5,6,7,12,13,14,15,16,19,20,21,22,27,31,34}},
#else
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34}},
#endif
    {"stills/4360x2448/smartphone03.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34},
#ifdef EXPERIMENTAL_LSD
        {0,1,2,3,4,5,6,7,8,12,13,14,15,19,20,21,22,25,27,28,29,31,33,34}},
#else
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34}},
#endif
    {"stills/1600x1200/thesis01.jpg",
        {369,370,371,372,373,374,375,377,378,379,380,381,382,383,384,385,386,394,395,396,397,398,399,400,401,402,405,406,407,408,409},
#ifdef EXPERIMENTAL_LSD
        {369}},
#else
        {}},
#endif
    {"stills/1600x1200/thesis02.jpg",
        {588,589,590,591,592,593,594,595,596,597,598,599,1000},
#ifdef EXPERIMENTAL_LSD
        {}},
#else
        {597,}},
#endif
    {"stills/1600x1200/thesis03.jpg",
        {576,577,588,589,590,591,593,594,595,1023},
        {}},
    {"stills/1600x1200/thesis04.jpg",
        {573,574,575,582,583,584,585,586,587,588,589,590,591,592,593,594,595,596,597,598,599,1022},
        {}},
    {"stills/640x480/severin01.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
#ifdef EXPERIMENTAL_LSD
        {}},
#else
        {1,13,}},
#endif
    {"stills/640x480/severin02.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
        {}},
    {"stills/640x480/severin03.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
        {}},
    {"stills/640x480/severin04.jpg",
        {      3,        8,9,10,         14               },
        {14,}},
    {"stills/640x480/severin05.jpg",
        {0,1,    4,5,6,7,          12,13,14,      17,18   },
#ifdef EXPERIMENTAL_LSD
        {5,6,7,12,13,14,18,}},
#else
        {5,7,12,13,18,}},
#endif
    {"stills/640x480/severin06.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
        {}},
    {"stills/640x480/nasty01.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
#ifdef EXPERIMENTAL_LSD
        {1,8,16,}},
#else
        {1,13,}},
#endif
    {"stills/640x480/nao01.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
        {}},
    {"stills/640x480/nao02.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
        {}},
    {"stills/640x480/nao03.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
        {}},
    {"stills/640x480/nao04.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
        {}},
    {"stills/640x480/nao05.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
#ifdef EXPERIMENTAL_LSD
        {}},
#else
        {1,}},
#endif
    {"stills/640x480/nao06.jpg",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
#ifdef EXPERIMENTAL_LSD
        {0,4,}},
#else
        {0,1,4,6,8,15,}},
#endif
    {"stills/640x480/occlusion01.jpg",
        {  1,17      },
        {1,17,}},
    {"stills/640x480/occlusion02.jpg",
        {  1,17      },
        {1,17,}},
    {"stills/320x240/nao01.png",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
#ifdef EXPERIMENTAL_LSD
        {1,2,5,6,8,9,10,11,12,13,15,16,17,19,}},
#else
        {1,2,5,6,8,9,10,11,12,13,14,15,16,17,19,}},
#endif
    {"stills/320x240/nao02.png",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
#ifdef EXPERIMENTAL_LSD
        {1,2,4,5,6,7,9,11,12,13,14,15,16,17,19,}},
#else
        {1,2,4,5,6,7,8,9,11,13,14,15,16,17,18,19,}},
#endif
    {"stills/320x240/nao03.png",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
#ifdef EXPERIMENTAL_LSD
        {2,7,}},
#else
        {2,5,7,10,14,16,18,}},
#endif
    {"stills/320x240/nao04.png",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
#ifdef EXPERIMENTAL_LSD
        {0}},
#else
        {3,6,14,}},
#endif
    {"stills/320x240/nao05.png",
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,15,16,17,18,19,}},
    {"stills/320x240/nao06.png",
        {46, 50, 51, 55, 59, 62},
#ifdef EXPERIMENTAL_LSD
        {46,50,51,55,59,62,}},
#else
        {46,50,51,59,62,}},
#endif
    {"stills/320x240/nao07.png",
        {46, 50, 51, 55, 59, 62},
#ifdef EXPERIMENTAL_LSD
        {46,50,51,55,59,62,}},
#else
        {46,50,55,59,62,}},
#endif
    {"stills/320x240/nao08.png",
        {50, 51, 55, 62},
#ifdef EXPERIMENTAL_LSD
        {50,51,55,62,}},
#else
        {50,51,62,}},
#endif
};
}

#endif
