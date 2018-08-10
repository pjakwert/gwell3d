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

#ifndef QGLVIEWER_CONSTRAINT_H
#define QGLVIEWER_CONSTRAINT_H

#include "vec.h"
#include "quaternion.h"

namespace qglviewer {
  class Frame;
  class Camera;

  /*!
  \brief A base class for Frame constraints.
  
  The different constraints that can be applied to a Frame to limit its motion must all derive
  from this class. A frame can have its constrain defined with Frame::setConstraint().
  
  constrainTranslation() and constrainRotation() can be overloaded to specify the constraint
  behavior. They take the desired displacement (translation or rotation) and the applied frame as
  parameters. The translation (resp. rotation) is then modified according to the constraint.

  The Frame::translate() and Frame::rotate() functions filter their input with the current Frame constraint (if any):
  \code
  Frame::translate(Vec& T)
  {
    if (constraint())
      constraint()->constrainTranslation(T, this);
    t += T;
  }

  Frame::rotate(Quaternion& Q)
  {
    if (constraint())
      constraint()->constrainRotation(Q, this);
    q *= Q;
  }
  \endcode
  
  Default behavior (Constraint base class) implements no constraint : constrainTranslation() and
  constrainRotation() are identity functions.
   
  Try the <a href="../examples/constrainedFrame.html">constrainedFrame</a> and
  <a href="../examples/constrainedCamera.html">constrainedCamera</a> examples for an illustration.

  <h3>Implemented constraints</h3>
  
  Classical constraints are provided for convenience : see the LocalConstraint, WorldConstraint and
  CameraConstraint classes for axial and plane constraints. The TriangleSetConstraint is very
  useful for walk through applications, in order to force the camera to remain on a given path.

  <h3>Definig new constraints</h3>

  The implementation of a new Constraint class simply consists in overloading the filtering
  functions:
  \code
  class myConstraint : public Constraint
  {
  public:
    virtual void constrainTranslation(Vec& t, Frame * const fr)
      {
        // The frame cannot have a negative z world coordinate.
	if (fr->position().z + t.z < 0.0) // new fr z coordinate
	  t.z = fr->position().z;         // t.z is clamped
      }
  };

  myFrame->setConstraint(new myConstraint());
  \endcode

  <h3>Combining constraints</h3>

  Combining constraints can easily be achieved by creating a new class that will apply the different
  constraint filters:
  \code
  myConstraint::constrainTranslation(Vec& v, Frame* const fr)
  {
    const1->constrainTranslation(v, fr);
    const2->constrainTranslation(v, fr);
    // and so on, with possible branches, tests, loops...
  }
  \endcode
  Much more complex constraint composition classes can be created in the same way.
  
  \attention Frame::setTranslation(), Frame::setRotation() and similar functions will actually \e
  set the frame position and orientation, without taking the constraint into consideration. Use the
  \e WithConstraint versions of these functions to enforce the constraint. */
  class QGLVIEWER_EXPORT Constraint
  {
  public:
    /*! Virtual empty destructor. */
    virtual ~Constraint() {};

    /*! Default un-constrained translation function. Desired translation is expressed in \e local frame
      coordinate system.

      Overload this function in your own Constraint class to define a new translation constraint.
      The frame which is applied a constrained translation is given as a parameter. It is not
      defined \c const, but you should refrain from directly changing its value in the
      constraint. */
    virtual void constrainTranslation(Vec&, Frame* const) {};

    /*! Default un-constrained rotation function. Desired rotation is expressed in \e local frame
      coordinate system.

      Overload this function in your own Constraint class to define a new rotational constraint.
      The frame which is applied a constrained rotation is given as a parameter. It is not defined
      \c const, but you should refrain from directly changing its value in the constraint. */
    virtual void constrainRotation(Quaternion& , Frame* const) {};
  };

  /*!
   \brief An abstract class for Frame constraints that use an axis or a plane.

   This class defines and implements a translation and a rotation constraint direction and type. The
   type is defined by the Type() enum which could be extended in derived classes to define new
   constraint types. The three implementations of this class: LocalConstraint, WorldConstraint and
   CameraConstraint each define the constraint axis/plane in a different coordinate system.

   Different implementations of this class are illustrated in the
   <a href="../examples/constrainedCamera.html">contrainedCamera</a> and
   <a href="../examples/constrainedFrame.html">constrainedFrame</a> examples.

   To completely forbid the displacement of a Frame, use a code like this:
   \code
   AxisPlaneConstraint* apc = new Any_Derived_Class();
   apc->setTranslationConstraintType(AxisPlaneConstraint::FORBIDDEN); // forbids translation
   // apc->setRotationConstraintType(AxisPlaneConstraint::FORBIDDEN); // or forbids rotation
   myFrame->setConstraint(apc);
   \endcode

   \attention The Axis rotational constraint is implemented by projecting the rotation axis
   direction of the constrained axis. The constrain is hence satisfied, but unpleasant behavior may
   appear when a mouse ManipulatedFrame is used to move the frame (try the above examples to see
   what I mean). A solution would be to directly measure the rotation angle in screen coordinates,
   but that would imply to know the Camera associated to the viewer, so that we can compute the
   projected coordinates of the rotation center. This is the way the Camera screen Z axis rotation
   is implemented (see the <a href="../mouse.html">mouse page</a> for details). However, we chose \e
   not to fix this problem, as it would imply an extra Camera pointer in all the AxisPlaneConstraint
   derived classes (which the user should have to update depending on the used viewer in a
   multi-viewer application). */
  class QGLVIEWER_EXPORT AxisPlaneConstraint : public Constraint
  {
  public:
    AxisPlaneConstraint();
    /*! Virtual empty destructor. */
    virtual ~AxisPlaneConstraint() {};

    /*! The different types of translation and rotation constraints that are available. New derived
    classes can introduce their own enum for specific constraints.
  
    Use setTranslationConstraint() and setRotationConstraint() to set constraints,
    translationConstraintType() and rotationConstraintType() to get the current constraint type.
     
    \note See the warning section of the Detailed Description section for limitations on the AXIS
    rotational constraint.

    \attention The PLANE constraint has no effect on a rotational constraint. */
    enum Type { FREE, PLANE, AXIS, FORBIDDEN };

    /*! @name Translation constraints */
    //@{   
    /*! Default un-constrained translation function. Desired translation is expressed in local frame
    coordinate system. Try the <a href="../examples/constrainedFrame.html">constrainedFrame</a>
    and <a href="../examples/constrainedCamera.html">constrainedCamera</a> examples for an
    illustration. */
    virtual void constrainTranslation(Vec&, Frame* const)=0;
    
    void setTranslationConstraint(const Type t, const Vec& dir);
    void setTranslationConstraint(const Type t, const float x, const float y, const float z);
    /*! Set the Type() of the translation constraint. See setTranslationConstraint(). */
    void setTranslationConstraintType(const Type t) { translationConstraint_ = t; };
    void setTranslationConstraintDir(const Vec& dir);
  
    /*! Returns the current translation constraint. Result is of type Type(). The
    translation constraint is set with setTranslationConstraint(). */
    Type translationConstraintType() const { return translationConstraint_; };
 
    /*! Same as getTranslationConstraintDir() but result is returned as floats. */
    void getTranslationConstraintDir(float& x, float& y, float& z) const;

    /*! Returns the current direction of the translation constraint. If translationConstraintType()
    is FREE or FORBIDDEN, this value is undefined. \p dir is the plane normal or the axis direction,
    depending on the constraint type. It is expressed in different coordinate system, depending on
    the actual constraint class (camera for CameraConstraint, local for LocalConstraint, world for
    WorldConstraint, etc.) This value can be modified with setTranslationConstraintDir(). */
    Vec translationConstraintDir() const { return translationConstraintDir_; };
    //@}
    
    /*! @name Rotation constraints */
    //@{   
    /*! Default un-constrained rotation function. Desired rotation is expressed in local frame
    coordinate system. Try the <a href="../examples/constrainedFrame.html">constrainedFrame</a>
    and <a href="../examples/constrainedCamera.html">constrainedCamera</a> examples for an
    illustration. */
    virtual void constrainRotation(Quaternion& , Frame* const)=0;
      
    void setRotationConstraint(const Type t, const Vec& dir);
    void setRotationConstraint(const Type t, const float x, const float y, const float z);
    void setRotationConstraintType(const Type t);
    void setRotationConstraintDir(const Vec& dir);

    /*! Returns the current rotation constraint. Result is of type Type(). The rotation
    constraint is set with setRotationConstraint(). */
    Type rotationConstraintType() const { return rotationConstraint_; };

    /*! Same as getRotationConstraintDir() but result is returned as floats. */
    void getRotationConstraintDir(float& x, float& y, float& z) const;
    /*! Returns the current direction of the rotation constraint. If rotationConstraintType() is
    FREE or FORBIDDEN, this value is undefined. \p dir is the plane normal or the axis direction,
    depending on the constraint. It is expressed in a different coordinate system depending on
    the derived class (WorldConstraint, CameraConstraint...). This value can be modified with
    setRotationConstraint(). */
    Vec rotationConstraintDir() const { return rotationConstraintDir_; };
    //@}
  
  private:
    /*! A constraint Type(), used for translation constraint specification. */
    Type translationConstraint_;
    /*! A constraint Type(), used for rotation constraint specification. */
    Type rotationConstraint_;

    /*! A vector, used for translation constraints (axis direction or plane normal). */
    Vec translationConstraintDir_;
    /*! A vector, used for rotation constraints (axis direction or plane normal). */
    Vec rotationConstraintDir_;
  };

  
  /*! \brief A translation/rotation Constraint defined with respect to the local frame coordinate system. */
  class QGLVIEWER_EXPORT LocalConstraint : public AxisPlaneConstraint
  {
  public:
    /*! Virtual empty destructor. */
    virtual ~LocalConstraint() {};

    virtual void constrainTranslation(Vec&        , Frame* const);
    virtual void constrainRotation   (Quaternion& , Frame* const);
  };


  
  /*! \brief A translation/rotation Constraint defined with respect to the world coordinate system. */
  class QGLVIEWER_EXPORT WorldConstraint : public AxisPlaneConstraint
  {
  public:
    /*! Virtual empty destructor. */
    virtual ~WorldConstraint() {};

    virtual void constrainTranslation(Vec&        , Frame* const);
    virtual void constrainRotation   (Quaternion& , Frame* const);
  };

  
  /*! \brief A translation/rotation Constraint defined with respect to the camera coordinate system. */
  class QGLVIEWER_EXPORT CameraConstraint : public AxisPlaneConstraint
  {
  public:
    explicit CameraConstraint(const Camera* const cam);
    /*! Virtual empty destructor. */
    virtual ~CameraConstraint() {};

    virtual void constrainTranslation(Vec&        , Frame* const);
    virtual void constrainRotation   (Quaternion& , Frame* const);

    /*! Returns the associated Camera, set using the CameraConstraint constructor. */
    const Camera* camera() const { return camera_; };
    
  private:
    /*! The camera which frame is used to define the constraints direction, set with the constructor. */
    const Camera* const camera_;
  };
 
} // namespace qglviewer

#endif // QGLVIEWER_CONSTRAINT_H
