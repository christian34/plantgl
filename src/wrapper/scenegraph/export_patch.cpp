/* -*-c++-*-
 *  ----------------------------------------------------------------------------
 *
 *       GeomPy: Python wrapper for the Plant Graphic Library
 *
 *       Copyright 1995-2003 UMR AMAP 
 *
 *       File author(s): C. Pradal (christophe.pradal@cirad.fr)
 *
 *       $Source$
 *       $Id$
 *
 *       Forum for AMAPmod developers    : amldevlp@cirad.fr
 *
 *  ----------------------------------------------------------------------------
 *
 *                      GNU General Public Licence
 *
 *       This program is free software; you can redistribute it and/or
 *       modify it under the terms of the GNU General Public License as
 *       published by the Free Software Foundation; either version 2 of
 *       the License, or (at your option) any later version.
 *
 *       This program is distributed in the hope that it will be useful,
 *       but WITHOUT ANY WARRANTY; without even the implied warranty of
 *       MERCHANTABILITY or FITNESS For A PARTICULAR PURPOSE. See the
 *       GNU General Public License for more details.
 *
 *       You should have received a copy of the GNU General Public
 *       License along with this program; see the file COPYING. If not,
 *       write to the Free Software Foundation, Inc., 59
 *       Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *  ----------------------------------------------------------------------------
 */

#include <boost/python.hpp>

#include <plantgl/tool/util_array.h>
#include <plantgl/tool/util_array2.h>

#include <plantgl/scenegraph/geometry/parametricmodel.h>
#include <plantgl/scenegraph/container/pointmatrix.h>
#include <plantgl/scenegraph/geometry/patch.h>
#include <plantgl/scenegraph/geometry/bezierpatch.h>
#include <plantgl/scenegraph/geometry/nurbspatch.h>

#include "../util/export_refcountptr.h"
#include "../util/export_property.h"

PGL_USING_NAMESPACE
TOOLS_USING_NAMESPACE
using namespace boost::python;
using namespace std;

DEF_POINTEE(Patch)
DEF_POINTEE(BezierPatch)
DEF_POINTEE(NurbsPatch)

SETGET(Patch,CCW,bool);

void export_Patch()
{
  class_< Patch, PatchPtr, bases< ParametricModel >,boost::noncopyable >
    ("Patch",no_init)
    .DEC_SETGET_WD(ccw,Patch,CCW,bool)
    ;

  implicitly_convertible< PatchPtr,ParametricModelPtr >();
}

SETGET(BezierPatch,UStride,uint32_t);
SETGET(BezierPatch,VStride,uint32_t);
SETGET(BezierPatch,CtrlPointMatrix,Point4MatrixPtr);

void export_BezierPatch()
{
  class_< BezierPatch, BezierPatchPtr, bases< Patch >,boost::noncopyable >
    ("BezierPatch",init<Point4MatrixPtr, optional<uint32_t,uint32_t,bool> >
     ("BezierPatch(Point4Matrix ctrlPoints [,ustride,vstride,ccw])"))
    .DEC_SETGET_WD(ustride,BezierPatch,UStride,uint32_t)
    .DEC_SETGET_WD(vstride,BezierPatch,VStride,uint32_t)
    .DEC_SETGET(ctrlPointMatrix,BezierPatch,CtrlPointMatrix,Point4MatrixPtr)
    ;

  implicitly_convertible< BezierPatchPtr,PatchPtr >();
}

SETGET(NurbsPatch,UDegree,uint32_t);
SETGET(NurbsPatch,VDegree,uint32_t);
SETGET(NurbsPatch,UKnotList,RealArrayPtr);
SETGET(NurbsPatch,VKnotList,RealArrayPtr);

void export_NurbsPatch()
{
  class_< NurbsPatch, NurbsPatchPtr, bases< BezierPatch >,boost::noncopyable >
    ("NurbsPatch",init<Point4MatrixPtr, optional< RealArrayPtr, RealArrayPtr, 
     uint32_t,uint32_t,uint32_t,uint32_t,bool> >
     ("NurbsPatch(Point4Matrix ctrlPoints, RealArray uKnotList,RealArray vKnotList [,uDeg, vDeg,ustride,vstride,ccw])"))
    .DEC_SETGET_WD(udegree,NurbsPatch,UDegree,uint32_t)
    .DEC_SETGET_WD(vdegree,NurbsPatch,VDegree,uint32_t)
    .DEC_SETGET_WD(uknotList,NurbsPatch,UKnotList,RealArrayPtr)
    .DEC_SETGET_WD(vknotList,NurbsPatch,VKnotList,RealArrayPtr)
    .def("setVKnotListToDefault",&NurbsPatch::setVKnotListToDefault)
    .def("setUKnotListToDefault",&NurbsPatch::setUKnotListToDefault)
    ;

  implicitly_convertible< NurbsPatchPtr,BezierPatchPtr >();

}


