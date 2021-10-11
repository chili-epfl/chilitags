/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

/*
 * Workaround a swig problem regarding std::vector __getitem__
 * Without this macro, constructs like x = myVectorPosition2D[i] return
 * elements by reference and not by value, which causes problems
 * when myVectorPosition2D gets garbage-collected: the C++ vector is freed
 * and x holds a dandling pointer.
 * With this macro, myVectorPosition2D[i] return a copy of the element.
 *
 * See bug 3497770
 * https://sourceforge.net/tracker/?func=browse&group_id=1645&atid=101645
 */
%define RETURN_COPY_FROM_VECTOR(TYPE)
%typemap(out) TYPE & front {
        $result = SWIG_NewPointerObj(%new_copy(*$1, $*ltype), $descriptor,
        SWIG_POINTER_OWN | %newpointer_flags);
  }
%typemap(out) TYPE & back {
        $result = SWIG_NewPointerObj(%new_copy(*$1, $*ltype), $descriptor,
        SWIG_POINTER_OWN | %newpointer_flags);
  }
%typemap(out) TYPE & __getitem__ {
        $result = SWIG_NewPointerObj(%new_copy(*$1, $*ltype), $descriptor,
        SWIG_POINTER_OWN | %newpointer_flags);
  }
%enddef
%module almathswig

%feature("autodoc", "1");

%{
#include <sstream>
#include "almath/dsp/digitalfilter.h"
#include "almath/dsp/pidcontroller.h"

#include "almath/types/alaxismask.h"

#include "almath/types/alpose2d.h"
#include "almath/types/alposition2d.h"
#include "almath/types/alposition3d.h"
#include "almath/types/alposition6d.h"
#include "almath/types/alpositionandvelocity.h"
#include "almath/types/alquaternion.h"
#include "almath/types/aldisplacement.h"

#include "almath/types/alrotation.h"
#include "almath/types/alrotation3d.h"

#include "almath/types/altransform.h"

#include "almath/types/alvelocity3d.h"
#include "almath/types/alvelocity6d.h"

#include "almath/types/altransformandvelocity6d.h"

#include "almath/tools/aldubinscurve.h"
#include "almath/tools/altrigonometry.h"
#include "almath/tools/avoidfootcollision.h"
#include "almath/tools/altransformhelpers.h"
#include "almath/tools/almath.h"

// forward-declare function that swig will create (thanks to the %extend
// below) and that we use to print some std::vector
static char * AL_Math_Position2D___repr__(AL::Math::Position2D *);
static char * AL_Math_Pose2D___repr__(AL::Math::Pose2D *);
static char * AL_Math_Position6D___repr__(AL::Math::Position6D *);
%}

RETURN_COPY_FROM_VECTOR(AL::Math::Position2D)
RETURN_COPY_FROM_VECTOR(AL::Math::Pose2D)
RETURN_COPY_FROM_VECTOR(AL::Math::Position6D)

%include "std_vector.i"
%include "std_string.i"

namespace std {
  %template(vectorFloat) vector<float>;
  %template(vectorPosition2D) vector<AL::Math::Position2D>;
  %template(vectorPose2D) vector<AL::Math::Pose2D>;
  %template(vectorPosition6D) vector<AL::Math::Position6D>;


  %extend vector<float> {
    std::string __repr__() {
      std::ostringstream out;
      out << "vectorFloat([";
      if ($self->size() > 0) {
        std::vector<float>::iterator it = $self->begin();
        // print all but the last element
        for ( ; it<$self->end()-1; ++it)
          out << *it << ", ";
        // print the last element, without the trailing ", "
        out << *it;
      }
      out << "])" << std::endl;
      return out.str();
    }
  }

  %extend vector<AL::Math::Position2D> {
    std::string __repr__() {
      std::ostringstream out;
      out << "vectorPosition2D([";
      if ($self->size() > 0) {
        std::vector<AL::Math::Position2D>::iterator it = $self->begin();
        // print all but the last element
        for ( ; it<$self->end()-1; ++it)
          out << AL_Math_Position2D___repr__(&(*it)) << ", ";
        // print the last element, without the trailing ", "
        out << AL_Math_Position2D___repr__(&(*it));
      }
      out << "])" << std::endl;
      return out.str();
    }
  }

  %extend vector<AL::Math::Pose2D> {
    std::string __repr__() {
      std::ostringstream out;
      out << "vectorPose2D([";
      if ($self->size() > 0) {
        std::vector<AL::Math::Pose2D>::iterator it = $self->begin();
        // print all but the last element
        for ( ; it<$self->end()-1; ++it)
          out << AL_Math_Pose2D___repr__(&(*it)) << ", ";
        // print the last element, without the trailing ", "
        out << AL_Math_Pose2D___repr__(&(*it));
      }
      out << "])" << std::endl;
      return out.str();
    }
  }

  %extend vector<AL::Math::Position6D> {
    std::string __repr__() {
      std::ostringstream out;
      out << "vectorPosition6D([";
      if ($self->size() > 0) {
        std::vector<AL::Math::Position6D>::iterator it = $self->begin();
        // print all but the last element
        for ( ; it<$self->end()-1; ++it)
          out << AL_Math_Position6D___repr__(&(*it)) << ", ";
        // print the last element, without the trailing ", "
        out << AL_Math_Position6D___repr__(&(*it));
      }
      out << "])" << std::endl;
      return out.str();
    }
  }
}

%include "almath/dsp/digitalfilter.h"
%include "almath/dsp/pidcontroller.h"

%include "almath/types/alaxismask.h"

%include "almath/types/alpose2d.h"
%include "almath/types/alposition2d.h"
%include "almath/types/alposition3d.h"
%include "almath/types/alposition6d.h"
%include "almath/types/alpositionandvelocity.h"
%include "almath/types/alquaternion.h"
%include "almath/types/aldisplacement.h"

%include "almath/types/alrotation.h"
%include "almath/types/alrotation3d.h"

%include "almath/types/altransform.h"

%include "almath/types/alvelocity3d.h"
%include "almath/types/alvelocity6d.h"

%include "almath/types/altransformandvelocity6d.h"

%include "almath/tools/aldubinscurve.h"
%include "almath/tools/altrigonometry.h"
%include "almath/tools/avoidfootcollision.h"
%include "almath/tools/altransformhelpers.h"
%include "almath/tools/almath.h"


%extend AL::Math::Pose2D {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Pose2D(x=%g, y=%g, theta=%g)",
               $self->x, $self->y, $self->theta);
       return tmp;
   }

   AL::Math::Pose2D __rmul__(const float lhs) {
       return (*$self) * lhs;
   }
};

%extend AL::Math::Position2D {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Position2D(x=%g, y=%g)",
               $self->x, $self->y);
       return tmp;
   }

   AL::Math::Position2D __rmul__(const float lhs) {
       return (*$self) * lhs;
   }
};


%extend AL::Math::Position3D {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Position3D(x=%g, y=%g, z=%g)",
               $self->x, $self->y, $self->z);
       return tmp;
   }

   AL::Math::Position3D __rmul__(const float lhs) {
       return (*$self) * lhs;
   }
};


%extend AL::Math::Quaternion {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Quaternion(w=%g, x=%g, y=%g, z=%g)",
               $self->w, $self->x, $self->y, $self->z);
       return tmp;
   }
};

%extend AL::Math::Position6D {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Position6D(x=%g, y=%g, z=%g, wx=%g, wy=%g, wz=%g)",
               $self->x, $self->y, $self->z,
               $self->wx, $self->wy, $self->wz);
       return tmp;
   }

   AL::Math::Position6D __rmul__(const float lhs) {
       return (*$self) * lhs;
   }
};

%extend AL::Math::PositionAndVelocity {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "PositionAndVelocity(q=%g, dq=%g)",
               $self->q, $self->dq);
       return tmp;
   }
};


%extend AL::Math::Rotation {
   char *__str__() {
       static char tmp[1024];
       sprintf(tmp, "[[%g, %g, %g]\n"
                    " [%g, %g, %g]\n"
                    " [%g, %g, %g]]",
               $self->r1_c1, $self->r1_c2, $self->r1_c3,
               $self->r2_c1, $self->r2_c2, $self->r2_c3,
               $self->r3_c1, $self->r3_c2, $self->r3_c3);
       return tmp;
   }

   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Rotation([%g, %g, %g\n"
                    "          %g, %g, %g\n"
                    "          %g, %g, %g])",
               $self->r1_c1, $self->r1_c2, $self->r1_c3,
               $self->r2_c1, $self->r2_c2, $self->r2_c3,
               $self->r3_c1, $self->r3_c2, $self->r3_c3);
       return tmp;
   }

   AL::Math::Position3D __mul__(AL::Math::Position3D rhs) const {
       return (*$self) * rhs;
   }
};


%extend AL::Math::Rotation3D {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Rotation3D(wx=%g, wy=%g, wz=%g)",
               $self->wx, $self->wy, $self->wz);
       return tmp;
   }
};


%extend AL::Math::Transform {
   char *__str__() {
       static char tmp[1024];
       sprintf(tmp, "[[%g, %g, %g, %g]\n"
                    " [%g, %g, %g, %g]\n"
                    " [%g, %g, %g, %g]]",
               $self->r1_c1, $self->r1_c2, $self->r1_c3, $self->r1_c4,
               $self->r2_c1, $self->r2_c2, $self->r2_c3, $self->r2_c4,
               $self->r3_c1, $self->r3_c2, $self->r3_c3, $self->r3_c4);
       return tmp;
   }

   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Transform([%g, %g, %g, %g\n"
                    "           %g, %g, %g, %g\n"
                    "           %g, %g, %g, %g])",
               $self->r1_c1, $self->r1_c2, $self->r1_c3, $self->r1_c4,
               $self->r2_c1, $self->r2_c2, $self->r2_c3, $self->r2_c4,
               $self->r3_c1, $self->r3_c2, $self->r3_c3, $self->r3_c4);
   return tmp;
   }

   AL::Math::Position3D __mul__(AL::Math::Position3D rhs) const {
       return (*$self) * rhs;
   }
};


%extend AL::Math::TransformAndVelocity6D {
   // TODO: fix these 2 methods
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "TransformAndVelocity6D(T=Transform([%g, %g, %g, %g\n"
                    "                                    %g, %g, %g, %g\n"
                    "                                    %g, %g, %g, %g]),\n"
                    "                       V=Velocity6D(xd=%g, yd=%g, zd=%g, wxd=%g, wyd=%g, wzd=%g))",
               $self->T.r1_c1, $self->T.r1_c2, $self->T.r1_c3, $self->T.r1_c4,
               $self->T.r2_c1, $self->T.r2_c2, $self->T.r2_c3, $self->T.r2_c4,
               $self->T.r3_c1, $self->T.r3_c2, $self->T.r3_c3, $self->T.r3_c4,
               $self->V.xd,  $self->V.yd,  $self->V.zd,
               $self->V.wxd, $self->V.wyd, $self->V.wzd);
       return tmp;
   }
};

%extend AL::Math::Displacement {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Displacement(P=Position3D(x=%g, y=%g, z=%g)\n"
                    "             Q=Quaternion(w=%g, x=%g, y=%g, z=%g))\n",
               $self->P.x, $self->P.y, $self->P.z,
               $self->Q.w, $self->Q.x, $self->Q.y, $self->Q.z);
       return tmp;
   }
};

%extend AL::Math::Velocity3D {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Velocity3D(xd=%g, yd=%g, zd=%g)",
               $self->xd, $self->yd, $self->zd);
       return tmp;
   }

   AL::Math::Velocity3D __rmul__(const float lhs) {
       return (*$self) * lhs;
   }
};

%extend AL::Math::Velocity6D {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp, "Velocity6D(xd=%g, yd=%g, zd=%g, wxd=%g, wyd=%g, wzd=%g",
               $self->xd,  $self->yd,  $self->zd,
               $self->wxd, $self->wyd, $self->wzd);
       return tmp;
   }

   AL::Math::Velocity6D __rmul__(const float lhs) const {
       return lhs * (*$self);
   }
};
