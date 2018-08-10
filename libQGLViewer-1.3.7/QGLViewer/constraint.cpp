/****************************************************************************

 This file is part of the QGLViewer library
 Copyright (C) 2002-2004  Gilles Debunne (Gilles.Debunne@imag.fr)
 Version 1.3.7 Release 1. Packaged on Friday April 30, 2004.

 http://artis.imag.fr/Members/Gilles.Debunne/QGLViewer

 libQGLViewer is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 libQGLViewer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with libQGLViewer; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/

#include "constraint.h"

#include "frame.h"
#include "camera.h"

using namespace qglviewer;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//                                  Constraint                                //
////////////////////////////////////////////////////////////////////////////////

/*! Translation and Rotation constraints are set to FREE. */
AxisPlaneConstraint::AxisPlaneConstraint()
  : translationConstraint_(AxisPlaneConstraint::FREE), rotationConstraint_(AxisPlaneConstraint::FREE)
{}

/*! Set possible constraints on the frame translation.
   By default, the frame has no translation constraint.
  
  Type() defines all the possible constraints. Depending on the value of \p c, the frame frame will
  be FREE, or will not be allowed to move out of a PLANE, or only along an AXIS, or not able to
  move at all (FORBIDDEN).
  
  The plane is defined by its normal vector and the axis is defined by its direction, both
  expressed in a coordinate system that depends on the derived class (see
  translationConstraintDir()).
  
  \p dir is not used if \p c is FREE or FORBIDDEN.
  
  Call Frame::setPosition() or Frame::setTranslation() before calling any of this method in order
  to define the relative constrained position of the frame.
  
  The current constraint is given by translationConstraintType() and translationConstraintDir(). */
void AxisPlaneConstraint::setTranslationConstraint(const Type t, const Vec& dir)
{
  setTranslationConstraintType(t);
  setTranslationConstraintDir(dir);
}

/*! Similar to setTranslationConstraint(), but only set the direction. */
void AxisPlaneConstraint::setTranslationConstraintDir(const Vec& dir)
{
  if ((translationConstraintType()!=AxisPlaneConstraint::FREE) && (translationConstraintType()!=AxisPlaneConstraint::FORBIDDEN))
    {
      const float norm = dir.norm();
      if (norm < 1E-8)
	{
	  qWarning("AxisPlaneConstraint::setTranslationConstraintDir : null vector for translation constraint");
	  translationConstraint_ = AxisPlaneConstraint::FREE;
	}
      else
	translationConstraintDir_ = dir/norm;
    }
}

/*! Same as setTranslationConstraint(), but with float parameters. */
void AxisPlaneConstraint::setTranslationConstraint(const Type t, const float x, const float y, const float z)
{
  setTranslationConstraint(t, Vec(x,y,z));
}

void AxisPlaneConstraint::getTranslationConstraintDir(float& x, float& y, float& z) const
{
  x = translationConstraintDir_.x;
  y = translationConstraintDir_.y;
  z = translationConstraintDir_.z;
}

/*! Set possible constraints on the frame rotation.
  By default, the frame has no rotation constraint.
  
  Type() defines all the possible constraints. 
  
  Depending on the value of \p c, the frame frame will be FREE, will only
  be able to move around an AXIS, in a PLANE, or will not able to move at all (FORBIDDEN).
  
  The axis and plane normal directions are expressed in different coordinates system, depending on
  the derived class (WorldConstraint, CameraConstraint...).
  \p dir is useless if \p c is FREE or FORBIDDEN.
  
  Call Frame::setOrientation() or Frame::setRotation() before calling this method in order to
  define the relative constrained orientation of the frame.
  
  The current constraint is given by rotationConstraintType() and rotationConstraintDir().
  The axis direction is undefined when the constraint is of type FREE or FORBIDDEN.
 
 \attention The PLANE rotational constraint cannot be used for rotational constraint. */
void AxisPlaneConstraint::setRotationConstraint(const Type t, const Vec& dir)
{
  setRotationConstraintType(t);
  setRotationConstraintDir(dir);
}

/*! Similar to setRotationConstraint(), but only set the direction. */
void AxisPlaneConstraint::setRotationConstraintDir(const Vec& dir)
{
  if ((rotationConstraintType()!=AxisPlaneConstraint::FREE) && (rotationConstraintType()!=AxisPlaneConstraint::FORBIDDEN))
    {
      float norm = dir.norm();
      if (norm < 1E-8)
	{
	  qWarning("AxisPlaneConstraint::setRotationConstraintDir : null vector for rotation constraint");
	  rotationConstraint_ = AxisPlaneConstraint::FREE;
	}
      else
	rotationConstraintDir_ = dir/norm;
    }
}

/*! Set the Type() of the rotation constraint. See setRotationConstraint().
  \attention The PLANE Type() cannot be used for rotational constraints. */
void AxisPlaneConstraint::setRotationConstraintType(const Type t)
{
  if (rotationConstraintType() == AxisPlaneConstraint::PLANE)
    {
      qWarning("AxisPlaneConstraint::setRotationConstraintType : the PLANE type cannot be used for a rotation constraints");
      return;
    }
  
  rotationConstraint_ = t;
}

/*! Same as setRotationConstraint(), but with float parameters. */
void AxisPlaneConstraint::setRotationConstraint(const Type t, const float x, const float y, const float z)
{
  setRotationConstraint(t, Vec(x,y,z));
}

void AxisPlaneConstraint::getRotationConstraintDir(float& x, float& y, float& z) const
{
  x = rotationConstraintDir_[0];
  y = rotationConstraintDir_[1];
  z = rotationConstraintDir_[2];
}



////////////////////////////////////////////////////////////////////////////////
//                               LocalConstraint                              //
////////////////////////////////////////////////////////////////////////////////

/*! Constrain the translation \p trans with a plane or an axis direction defined with respect to the current \e local coordinate system. */
void LocalConstraint::constrainTranslation(Vec& trans, Frame* const fr)
{
  Vec proj;
  switch (translationConstraintType())
    {
    case AxisPlaneConstraint::FREE:
      break;
    case AxisPlaneConstraint::PLANE:
      proj = fr->orientation().rotate(translationConstraintDir());
      trans.projectOnPlane(proj);
      break;
    case AxisPlaneConstraint::AXIS:
      proj = fr->orientation().rotate(translationConstraintDir());
      trans.projectOnAxis(proj);
      break;
    case AxisPlaneConstraint::FORBIDDEN:
      trans = Vec(0.0, 0.0, 0.0);
      break;     
    }
}

/*! Constrain the rotation \p trans with a plane or an axis direction defined with respect to the current \e local coordinate system. */
void LocalConstraint::constrainRotation(Quaternion& rot, Frame* const)
{
  switch (rotationConstraintType())
    {
    case AxisPlaneConstraint::FREE:
      break;
    case AxisPlaneConstraint::PLANE:
      break;
    case AxisPlaneConstraint::AXIS:
      {
	Vec axis = rotationConstraintDir();
	Vec quat = Vec(rot[0], rot[1], rot[2]);
	quat.projectOnAxis(axis);
	rot = Quaternion(quat, 2.0*acos(rot[3]));
      }
      break;
    case AxisPlaneConstraint::FORBIDDEN:
      rot = Quaternion(); // identity
      break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//                               WorldConstraint                              //
////////////////////////////////////////////////////////////////////////////////

/*! Constrain the translation \p trans with a plane or an axis direction defined with respect to the current \e world coordinate system. */
void WorldConstraint::constrainTranslation(Vec& trans, Frame* const fr)
{
  Vec proj;
  switch (translationConstraintType())
    {
    case AxisPlaneConstraint::FREE:
      break;
    case AxisPlaneConstraint::PLANE:
      if (fr->referenceFrame())
	{
	  proj = fr->referenceFrame()->transformOf(translationConstraintDir());
	  trans.projectOnPlane(proj);
	}
      else
	trans.projectOnPlane(translationConstraintDir());
      break;
    case AxisPlaneConstraint::AXIS:
      if (fr->referenceFrame())
	{
	  proj = fr->referenceFrame()->transformOf(translationConstraintDir());
	  trans.projectOnAxis(proj);
	}
      else
	trans.projectOnAxis(translationConstraintDir());
      break;
    case AxisPlaneConstraint::FORBIDDEN:
      trans = Vec(0.0, 0.0, 0.0);
      break;     
    }
}

/*! Constrain the rotation \p trans with a plane or an axis direction defined with respect to the current \e world coordinate system. */
void WorldConstraint::constrainRotation(Quaternion& rot, Frame* const fr)
{
  switch (rotationConstraintType())
    {
    case AxisPlaneConstraint::FREE:
      break;
    case AxisPlaneConstraint::PLANE:
      break;
    case AxisPlaneConstraint::AXIS:
      {
	Vec quat(rot[0], rot[1], rot[2]);
	Vec axis = fr->transformOf(rotationConstraintDir());
	quat.projectOnAxis(axis);
	rot = Quaternion(quat, 2.0*acos(rot[3]));
	break;
      }
    case AxisPlaneConstraint::FORBIDDEN:
      rot = Quaternion(); // identity
      break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//                               CameraConstraint                              //
////////////////////////////////////////////////////////////////////////////////

/*! Translation and Rotation constraints are set to FREE. */
CameraConstraint::CameraConstraint(const Camera* const cam)
  : AxisPlaneConstraint(), camera_(cam)
{}

/*! Constrain the translation \p trans with a plane or an axis direction defined with respect to the current \e camera coordinate system. */
void CameraConstraint::constrainTranslation(Vec& trans, Frame* const fr)
{
  Vec proj;
  switch (translationConstraintType())
    {
    case AxisPlaneConstraint::FREE:
      break;
    case AxisPlaneConstraint::PLANE:
      proj = camera()->frame()->inverseTransformOf(translationConstraintDir());
      if (fr->referenceFrame())
	proj = fr->referenceFrame()->transformOf(proj);
      trans.projectOnPlane(proj);
      break;
    case AxisPlaneConstraint::AXIS:
      proj = camera()->frame()->inverseTransformOf(translationConstraintDir());
      if (fr->referenceFrame())
	proj = fr->referenceFrame()->transformOf(proj);
      trans.projectOnAxis(proj);
      break;
    case AxisPlaneConstraint::FORBIDDEN:
      trans = Vec(0.0, 0.0, 0.0);
      break;     
    }
}

/*! Constrain the rotation \p trans with a plane or an axis direction defined with respect to the current \e camera coordinate system. */
void CameraConstraint::constrainRotation(Quaternion& rot, Frame* const fr)
{
  switch (rotationConstraintType())
    {
    case AxisPlaneConstraint::FREE:
      break;
    case AxisPlaneConstraint::PLANE:
      break;
    case AxisPlaneConstraint::AXIS:
      {
	Vec axis = fr->transformOf(camera()->frame()->inverseTransformOf(rotationConstraintDir()));
	Vec quat = Vec(rot[0], rot[1], rot[2]);
	quat.projectOnAxis(axis);
	rot = Quaternion(quat, 2.0*acos(rot[3]));
      }
      break;
    case AxisPlaneConstraint::FORBIDDEN:
      rot = Quaternion(); // identity
      break;
    }
}
