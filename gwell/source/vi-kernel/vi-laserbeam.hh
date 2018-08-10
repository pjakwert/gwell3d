#ifndef VI_LASERBEAM_H
#define VI_LASERBEAM_H


#ifdef __GNUG__
#pragma interface
#endif

class HalfLine3f;
class ViScene;
class Vector3f;
class ViMultiPolyh;

  //----------------------------------------------------------------------------
  // Funkcja szuka najbli�ego punktu przeci�cia danej p�prostej z widzialnymi
  // �ciankami wielo�cian�w.
  //
bool FindCrossPnt4HalfLineAndPolyhedralFace( HalfLine3f   const &Ln,
                                             ViScene      const &Scn,
                                             float              &t,
                                             Vector3f           &CrossPnt,
                                             ViMultiPolyh const *Obj2Omit = 0L
                                           );


#endif
