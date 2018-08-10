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

#ifndef QGLVIEWER_FRAME_H
#define QGLVIEWER_FRAME_H

#include <qobject.h>
#include <qstring.h>

#include "constraint.h"
// #include "GL/gl.h" is now included in config.h for ease of configuration

namespace qglviewer {
  /*! \brief A frame in 3D space (position and orientation), with possible displacement constraints.
    
  A Frame is a 3D coordinate system, represented by a position() and an orientation(). The order of
  these transformations is important : in libQGLViewer, the Frame is \e firstly translated \e and \e
  then rotated around the new translated origin. A Frame is useful to define the position and
  orientation of a 3D rigid object :

  \code
  Frame fr;
  fr.setPosition(1,0,3);
  fr.setOrientationAxisAngle(0,1,0, M_PI/2); // Rotation around the Y axis.
  glPushMatrix();
  glMultMatrixd(fr.matrix());
  // Draw your object here
  glPopMatrix();
  \endcode
  
  Many functions are provided to transform a 3D point from one coordinate system to an other : see
  coordinatesOf(), inverseCoordinatesOf(), coordinatesOfIn(), coordinatesOfFrom()...

  You may also want to transform a 3D \e vector from one frame to an other, which corresponds to
  applying only the rotational part of the frame transformation : see transformOf() and
  inverseTransformOf().

  See the <a href="../examples/frameTransform.html">frameTransform</a> example for an illustration.
  
  The translation() and the rotation() that are encapsulated in a Frame can also be used to represent a
  \e solid \e transformation of space. Such a solid transformation can also be interpreted as a change
  of coordinate system, and the coordinate system conversion functions actually allow you to use a
  Frame as a solid transformation. Use inverseCoordinatesOf() (resp. coordinatesOf()) to apply the
  transformation (resp. its inverse). Note the inversion.
  
  <h3>Hierarchy of frames</h3>

  The position and the rotation of a Frame are actually defined with respect to a referenceFrame().
  The default referenceFrame() is the world coordinate system, but this value can be set to any
  other frame using setReferenceFrame(). When a referenceFrame() is specified, one must
  differentiate :
  
  \arg the \e local translation() and rotation(), defined with respect to the referenceFrame()
  and
  
  \arg the \e global position() and orientation(), defined with respect to the world
  coordinate system.

  This terminology for \e local (translation() and rotation()) and \e global (position() and
  orientation()) definition is used in all the functions' names and should be sufficient to prevent
  ambiguities. These notions are identical when there is no referenceFrame() (i.e. a \c NULL value,
  corresponding to the world coordinate system).
  
  A Frame is actually defined by its translation() with respect to its referenceFrame(), and \e then
  by a rotation() of the coordinate system around the new translated origin.

  Setting a \c NULL reference frame resets the world coordinate system as the referenceFrame()
  (default value). The world coordinate system is the one you are in at the beginning of the
  QGLViewer::draw() function (see the <a href="../intro.html">introduction page></a>).

  Frames can hence easily be organized in a tree hierarchy, which root is the world
  coordinate system. A loop in the hierarchy would result in an inconsistent (multiple) frame
  definition. settingAsReferenceFrameWillCreateALoop() checks this and prevents setReferenceFrame()
  from creating such a loop.

  This frame hierarchy is used in methods like coordinatesOfIn(), coordinatesOfFrom()... which allow
  coordinates (or vector) conversion from a frame to any other one (including the world coordinate system).

  \attention However, one must note that this hierarchical representation is internal to the Frame
  classes. When the frames represent openGL coordinates system, one should map this hierarchical
  representation to the openGL GL_MODELVIEW matrix stack. If we define this Frame hierarchy:
  \code
  Frame* body     = new Frame();
  Frame* leftArm  = new Frame();
  Frame* rightArm = new Frame();
  leftArm->setReferenceFrame(body);
  rightArm->setReferenceFrame(body);
  \endcode
  Then the openGL drawing code associated with this Frame representation should look like:
  \code
  draw()
  {
    glPushMatrix();
    glMultMatrixd(body->matrix());
    drawBody();

    glPushMatrix();
    glMultMatrixd(leftArm->matrix());
    drawArm();
    glPopMatrix();

    glPushMatrix();
    glMultMatrixd(rightArm->matrix());
    drawArm();
    glPopMatrix();
    
    glPopMatrix();
  }
  \endcode
  Note how we use imbricated glPushMatrix() and glPopMatrix() to represent our frame hierarchy.
  leftArm and rightArm are hence both defined with respect to the body coordinate system, as in the
  Frame hierarchy.
  
  <h3>Constraints</h3>

  An interesting feature of Frames is that their displacement can be \e constrained. When a
  Constraint is attached to a Frame, it \e filters the input of translate() and rotate(), and only
  the resulting filtered motion is applied to the frame. The default constraint() is \c NULL and no
  filter is applied. Use setConstraint() to attach a constraint to a frame.

  Constraints are especially usefull for the ManipulatedFrame instances, in order to forbid some
  mouse motions. See the <a href="../examples/constrainedFrame.html">constrainedFrame</a>,
  <a href="../examples/constrainedCamera.html">constrainedCamera</a> and
  <a href="../examples/luxo.html">luxo</a> examples for an illustration.
  
  New constraints can very easily be implemented by deriving a class from the Constraint
  class or any of its derived classes. All you need is to provide your own implementation of the
  Constraint::constrainTranslation(qglviewer::Vec&, Frame* const) and
  Constraint::constrainRotation(qglviewer::Quaternion& , Frame* const) functions.

  Classical constraints are provided for convenience : see the LocalConstraint, WorldConstraint and
  CameraConstraint classes for axial and plane constraints. The TriangleSetConstraint is very
  useful for walk through applications, in order to force the camera to remain on a given path.

  <h3>Derived classes</h3>

  The ManipulatedFrame class inherits Frame and implements a mouse motion convertion, so that a
  frame can be manipulated with the mouse. SpinningFrame are animated Frames with a rotational
  motion.

  \nosubgrouping */
  class QGLVIEWER_EXPORT Frame : public QObject
  {
    Q_OBJECT

  public:
    Frame();
    
    /*! Virtual destructor. Empty. */
    virtual ~Frame() {};

    Frame& operator=(const Frame& f);

    Frame(const Frame& f);

  signals:
    /*! This signal is emitted whenever the position or the orientation of the Frame is modified. Connect this
    signal to any object that must be notified.
    \code
    QObject::connect(myFrame, SIGNAL(modified()), myObject, SLOT(update()));
    \endcode

    This signal can also be connected to \e all the viewers using QGLViewer::connectSignalToAllViewers().

    \note If your Frame is part of a Frame hierarchy (see referenceFrame()), a modification of one
    of the parents of this Frame will \e not emit this Frame modified() signal. Use code like this
    to change this behavior (you can do this recursively for all the referenceFrame() until the \c
    NULL world root frame is encountered):
    \code
    // Emits the frame modified() signal when its referenceFrame() is modified().
    connect(myFrame->referenceFrame(), SIGNAL(modified()), myFrame, SIGNAL(modified()));
    \endcode
    
    \attention Connecting this signal to a QGLWidget::updateGL() function (or a function that calls
    it) will prevent you from modifying the frame \e inside your QGLViewer::draw() function as it would
    result in an infinite loop. */
    void modified();

  public:
    /*! @name World Coordinate position and orientation
    Methods to set and restore the frame position and orientation (with respect to the \e world coordinate system).
  
    \p position is the absolute position of the origin of the frame, and
    \p orientation \e then defines its orientation (as a rotation around the new translated frame origin).
  
    Use translation() and rotation() to get the \e local (defined with respect to the
    referenceFrame()) frame characteristics. */
    //@{
    explicit Frame(const Vec& pos, const Quaternion& orien);

    void setPosition(const Vec& t);
    void setPosition(const float x, const float y, const float z);
    void setPositionWithConstraint(Vec& t);
    
    void setOrientation(const float x, const float y, const float z, const float a);
    void setOrientation(const Quaternion& q);
    void setOrientationWithConstraint(Quaternion& q);
    void setOrientationAxisAngle(const float x, const float y, const float z, const float a);

    void setPositionAndOrientation(const Vec& t, const Quaternion& q);
    void setPositionAndOrientationWithConstraint(Vec& t, Quaternion& q);
    
    /*! Returns the current frame origin position (defined in the world coordinate system). See setPosition(). */
    Vec position() const { return inverseCoordinatesOf(Vec(0.0,0.0,0.0)); };
    void getPosition(float& x, float& y, float& z) const;

    Quaternion orientation() const;
    void getOrientation(float& q0, float& q1, float& q2, float& q3) const;
  //@}

    
  public:
    /*! @name Composition of frames
    A frame is defined with respect to a given coordinate system. Default is the
    world coordinate system, corresponding to a \c NULL referenceFrame().
  
    Setting the reference frame to non \c NULL will define the frame with respect to this reference
    frame. Hierarchical frame structures can then be represented in a tree, whose root would be
    the world coordinate system (\c NULL). */
    //@{
    /*! Returns the current reference frame, defined with setReferenceFrame().

    The frame is "child" of the referenceFrame(), meaning that its position and orientation are
    defined with respect to the referenceFrame(). A \c NULL referenceFrame() (default value) means
    that the frame is defined is the world coordinate system. Chaining frames like this allows you
    to easily create a hierarchy of frames.

    Convenient functions allow you to convert 3D coordinates from one frame to an other :
    coordinatesOf(), localCoordinatesOf(), coordinatesOfIn() and their inverse functions.

    Vectors can also be converted from one frame to an other using transformOf(), transformOfIn,
    localTransformOf() and the inverse functions.

    A warning is printed if setting \p fr as a reference frame would create a loop in the frame
    hierarchy (see settingAsReferenceFrameWillCreateALoop()), as this hierarchy needs to be a
    tree. */
    Frame* referenceFrame() const { return referenceFrame_; };
    void setReferenceFrame(Frame* const fr);

    bool settingAsReferenceFrameWillCreateALoop(Frame* const fr);
    //@}

    /*! @name Local frame translation and rotation
    Methods to set and get the frame translation and rotation (defined with respect to the \e reference frame).
  
    A frame is defined by its translation with respect to its reference frame, and \e then by a
    rotation of the coordinate system around the new translated origin.
    These values (translation and then rotation) are hence defined with respect to the local
    reference frame. Use position() and orientation() to get the \e world coordinates of the frame. */
    //@{
    void setTranslation(const float x, const float y, const float z);
    /*! Set the current local translation of the frame. Use translation() to get the current frame
    position. See setPosition() and position() to get the \e world position of the frame. Emits
    the modified() signal. See also setRotation() and setTranslationWithConstraint(). */
    void setTranslation(const Vec& t) { t_ = t; emit modified(); };
    void setTranslationWithConstraint(Vec& t);

    void setRotation(const float x, const float y, const float z, const float a);
    /*! Set the current rotation Quaternion. See rotation() and the different Quaternion
    constructors. Emits the modified() signal. See also setTranslation() and
    setRotationWithConstraint(). */
    void setRotation(const Quaternion& q) { q_ = q; emit modified(); };
    void setRotationWithConstraint(Quaternion& q);
    void setRotationAxisAngle(const float x, const float y, const float z, const float a);

    void setTranslationAndRotation(const Vec& t, const Quaternion& q);
    void setTranslationAndRotationWithConstraint(Vec& t, Quaternion& q);

    void getTranslation(float& x, float& y, float& z) const;
    /*! Returns the current frame position. See setTranslation(). */
    Vec translation() const { return t_; };

    void getRotation(float& x, float& y, float& z, float& a) const;
    /*! Returns the current Quaternion orientation. See setRotation(). */
    Quaternion rotation() const { return q_; };
    //@}

    /*! @name Displacement of frames
    These methods translate/rotate the Frame. The associated constraint (if defined) is satisfied. The modified() signal is emitted. */
    //@{
    void translate(Vec& t);
    void translate(const Vec& t);
    void translate(float t[3]);
    void translate(float& x, float& y, float& z);
    void translate(const float x, const float y, const float z);
    
    void rotate(Quaternion& q);
    void rotate(const Quaternion& q);
    void rotate(float q[4]);
    void rotate(float& x, float& y, float& z, float& a);
    void rotate(const float x, const float y, const float z, const float a);

    void rotateAroundPoint(Quaternion& q, const Vec& p);
    void rotateAroundPoint(const Quaternion& q, const Vec& p);
    //@}


    /*! @name Coordinate system transformation of 3D points
  
    A frame is as a new coordinate system, defined with respect to a reference frame
    (the world coordinate system by default, see the "Composition of frame" section).
  
    The coordinatesOf() (resp. inverseCoordinatesOf()) functions transform a 3D point from (resp.
    to) the world coordinates system. This section defines the 3D \e point transformation functions.
    See the Coordinate system transformation of vectors below for the transformation of 3D
    \e vectors. The difference between the two sets of functions is simple : for vectors,
    only the rotational part of the transformations is taken into account, while translation is
    also considered for 3D points.
  
    When \e local is prepended to the names of the functions, the functions simply transform from
    (and to) the reference frame.
  
    When \e In (resp. From) is appended to the names, the functions transform from (resp. To) the
    frame that is given as an argument. The frame does not need to be in the same branch or the
    hierarchical tree, and can be \c NULL (the world coordinates system).
  
    Combining any of these functions with its inverse (in any order) leads to the identity.

    See the <a href="../examples/frameTransform.html">frameTransform</a> example for an illustration
    of some these functions. */
    //@{
    Vec coordinatesOf(const Vec& src) const;
    Vec inverseCoordinatesOf(const Vec& src) const;
    Vec localCoordinatesOf(const Vec& src) const;
    Vec localInverseCoordinatesOf(const Vec& src) const;
    Vec coordinatesOfIn(const Vec& src, const Frame* in) const;
    Vec coordinatesOfFrom(const Vec& src, const Frame* from) const;
    
    void getCoordinatesOf(const float src[3], float res[3]) const;
    void getInverseCoordinatesOf(const float src[3], float res[3]) const;
    void getLocalCoordinatesOf(const float src[3], float res[3]) const;
    void getLocalInverseCoordinatesOf(const float src[3], float res[3]) const;
    void getCoordinatesOfIn(const float src[3], float res[3], const Frame* in) const;
    void getCoordinatesOfFrom(const float src[3], float res[3], const Frame* from) const;
    //@}

    /*! @name Coordinate system transformation of vectors
  
    A frame is as a new coordinate system, defined with respect to a reference frame (the world
    coordinate system by default, see the "Composition of frame" section).
  
    The transformOf() (resp. inverseTransformOf()) functions transform a 3D \e vector from (resp.
    to) the world coordinates system. This section defines the 3D \e vector transformation
    functions. See the Coordinate system transformation of 3D points above for the transformation of
    3D \e points. The difference between the two sets of functions is simple : for vectors, only the
    rotational part of the transformations is taken into account, while translation is also
    considered for 3D points.
  
    The length of the resulting transformed vector is identical to the one of the source vector
    for all the described functions.
  
    When \e local is prepended to the names of the functions, the functions
    simply transform from (and to) the reference frame.
  
    When \e In (resp. From) is appended to the names, the functions transform
    from (resp. To) the frame that is given as an argument. The frame does not need to be in the
    same branch or the hierarchical tree, and can be \c NULL (the world coordinates system).
  
    Combining any of these functions with its inverse (in any order) leads to the identity. */
    //@{
    Vec transformOf(const Vec& src) const;
    Vec inverseTransformOf(const Vec& src) const;
    Vec localTransformOf(const Vec& src) const;
    Vec localInverseTransformOf(const Vec& src) const;
    Vec transformOfIn(const Vec& src, const Frame* in) const;
    Vec transformOfFrom(const Vec& src, const Frame* from) const;
    
    void getTransformOf(const float src[3], float res[3]) const;
    void getInverseTransformOf(const float src[3], float res[3]) const;
    void getLocalTransformOf(const float src[3], float res[3]) const;
    void getLocalInverseTransformOf(const float src[3], float res[3]) const;
    void getTransformOfIn(const float src[3], float res[3], const Frame* in) const;
    void getTransformOfFrom(const float src[3], float res[3], const Frame* from) const;
    //@}

    /*! @name Constraints on the displacement
  
    A constraint can be attached to the frame to limit its displacement. The translate() and rotate() function will satisfy this constraint.
    Default value is a non-constraint constraint. See the Constraint and derived class documentation. */
    //@{
    /*! Returns the current constraint. Result is of type Constraint and \c dynamic_cast should be used to convert it to a derived class.

    A \c NULL value means that no Constraint is applied to filter translate() and rotate() (default value). */
    Constraint* constraint() const { return constraint_; }
    /*! Set the constraint attached with the frame. A \p NULL value means no constraint, i.e. a
    Constraint instance. The previous constraint pointer should be deleted by the calling function if
    needed. Use constraint() to get this value. */
    void setConstraint(Constraint* c) { constraint_ = c; }
    //@}

    /*! @name Frame associated matrices */
    //@{
  public:
    const GLdouble* matrix() const;
    void getMatrix(GLdouble m[4][4]) const;
    void getMatrix(GLdouble m[16]) const;
    
    const GLdouble* worldMatrix() const;
    void getWorldMatrix(GLdouble m[4][4]) const;
    void getWorldMatrix(GLdouble m[16]) const;

    void setFromMatrix(const float m[4][4]);
    void alignWithFrame(const Frame* const fr, bool move=false, float threshold=0.85f);
    void projectOnLine(const Vec& origin, const Vec& dir);

    const GLdouble* inverseMatrix() const;
    void getInverseMatrix(GLdouble m[4][4]) const;
    void getInverseMatrix(GLdouble m[16]) const;
    
    const GLdouble* worldInverseMatrix() const;
    void getWorldInverseMatrix(GLdouble m[4][4]) const;
    void getWorldInverseMatrix(GLdouble m[16]) const;
    //@}

    /*! @name Inversion of the transformation */
    //@{
    /*! Returns the inverse of the Frame space transformation. The original Frame is \e not
      modified. Use invert() to actually modify the Frame.

    The rotation() of the new Frame is the Quaternion::inverse() of the original rotation().
    Its translation() is the negated and inverse rotated image of the original translation().

    The new Frame has the same referenceFrame() as the original. Hence only the \e local Frame
    transformation is inverted (see the "Hierarchy of frames" section in the Frame Detailed
    documentation for details on this notion). Use worldInverse() for a \e global inverse. */
    Frame inverse() const;
    
    /*! Invert the Frame (same as inverse(), but the Frame is actually inverted). The new rotation
      is the inverse of the previous one. The translation is the negated inverse rotation of the
      original translation().

      This method only inverts the \e local Frame transformation (see inverse() for details). Use
      worldInvert() for a full transformation inversion. The modified() signal is emitted. */
    void invert() { t_=q_.inverseRotate(t_); q_.invert(); emit modified(); }

    /*! Returns the world inverse of the Frame transformation. The original Frame is \e not
      modified. Use worldInvert() to actually modify the Frame.

    The orientation() of the new Frame is the Quaternion::inverse() of the original orientation().
    Its position() is the negated and inverse rotated image of the original position().

    The new Frame has no (i.e. \c NULL) referenceFrame(). Hence the complete Frame transformation
    (including its referenceFrame() transformations) is inverted (see the "Hierarchy of
    frames" section in the Frame Detailed documentation for details on this notion). Use
    inverse() for a \e local inverse. */
    Frame worldInverse() const { return Frame(-(orientation().inverseRotate(position())), orientation().inverse()); }
    
    /*! Invert the Frame world transformations (same as worldInverse(), but the Frame is actually
      inverted). The new orientation is the inverse of the previous one. The position() is the
      negated inverse rotation of the original position().

      This method only inverts the \e local Frame transformation (see inverse() for details). Use
      invert() for a local transformation inversion. The modified() signal is emitted. */
    void worldInvert();
    //@}
  
  public:
    /*! @name XML representation */
    //@{
    virtual QDomElement domElement(const QString& name, QDomDocument& doc) const;
    virtual void initFromDOMElement(const QDomElement& de);
    //@}

  private:
    // P o s i t i o n   a n d   o r i e n t a t i o n
    Vec t_;
    Quaternion q_;

    // C o n s t r a i n t s
    Constraint* constraint_;
    
    // F r a m e   c o m p o s i t i o n
    Frame* referenceFrame_;    
  };
  
} // namespace qglviewer

#endif // QGLVIEWER_FRAME_H
