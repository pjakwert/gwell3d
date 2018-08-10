#ifdef __GNUG__
#pragma implementation
#endif

#include "vector3f.hh"
#include "halfline3f.hh"
#include "vielemepolyhface.hh"
#include "vielemepolyh.hh"
#include "vimultipolyh.hh"
#include "viscene.hh"

/*===========================================================================
 * Szuka punktu przeci�cia p�prostej z dan� �ciank� przy za�o�eniu, �e 
 * dany wielobok jest wypuk�y.
 *
 */
bool ComputeCrossPnt4HalfLineAndPolyhedralFace( HalfLine3f       const &Ln, 
                                                ViElemePolyhFace const &Fc, 
                                                Vector3f               &CrossPnt,
                                                float                  &t
                                              )
{
  if (!Fc.GetPlain().CrossPoint4HalfLine(Ln,CrossPnt,t)) return false;

  Vector3f V_border, V_point;
    //.................................................................
    // Idea zastosowanej metod:
    //   Idzie wzd�u� brzegu i sprawdza czy wzgl�dem danego punktu jest
    //   on wypuk�y.
    //   Porz�dek wierzcho�k�w jest odwrotny do wskaz�wek zegara.
    //

  int Idx_prev = 0;
  for (int Idx = Fc.GetVtxNo()-1; Idx >= 0; Idx_prev = Idx--) {
    V_border = Fc.GlbVtx(Idx) - Fc.GlbVtx(Idx_prev);
    V_point  = Fc.GlbVtx(Idx_prev) - CrossPnt;
    if (sgn(V_border & V_point) != -1) {
        return false;
    }
  }
  return true;
}

//=============================================================================
// Metoda przygotowana dostosowana jest tylko dla bry� wypuk�ych.
//
bool FindCrossPnt4HalfLineAndPolyhedralFace( HalfLine3f  const &Ln,  
                                             ViElemePolyh const &RF,
                                             Vector3f          &CrossPnt,
                                             float             &t
                                           ) 
{
  /*__TMP__ Zakomentowane, aby odrzucic grafike ______________________  
  for (ViElemePolyh::ConFaceIter FcIter = RF.GetFacesIter_Const();
       FcIter;  ++FcIter) {
   if (sgn(FcIter->GetPlain().GetNVct() & Ln.cA()) != -1) continue;
   if (ComputeCrossPnt4HalfLineAndPolyhedralFace(Ln,*FcIter,CrossPnt,t)) {
                                                          return true;
   }
  }
  __TMP_*/
  return false;
}


//==============================================================================
// Metoda szuka tych punkt�w, kt�re s� bli�sze ni� warto�� parametru t.
//
bool FindCrossPnt4HalfLineAndPolyhedralFace( HalfLine3f   const &Ln,  
                                             ViMultiPolyh const &BObj,
                                             float              &t,
                                             Vector3f           &CrossPnt
                                           )
{
  bool        found = false;
  /*__TMP__ Zakomentowane, aby odrzucic grafike ______________________
  float       t_j;
  Vector3f  Pnt;

  CRealFigureIterator RFIter = BObj.GetCRealFigIterator();

  while (RFIter) {
    if (RFIter->GlbOlnBox().IsCommonPart(Ln)) {
      if (FindCrossPnt4HalfLineAndPolyhedralFace(Ln,*RFIter,Pnt,t_j)) {
	if (t_j < t) { 
          found = true;
          CrossPnt = Pnt;
          t = t_j;
	}
      }
    }
    ++RFIter;
  }
  __TMP_*/
  return found;
}


//=============================================================================
// Funkcja szuka najbli�ego punktu przeci�cia danej p�prostej z widzialnymi
// �ciankami wielo�cian�w znajduj�cymi si� na danej scenie.
//
// PRE:   Ln   - zawiera opis p�prostej,
//        Cell - udost�pnia opis sceny.
//        t    - warto�� parametru okre�laj�ca dopuszczalne maksymalne 
//               oddalenie punkt�w przeci�cia od pocz�tku prostej.
//               W przypadku gdy wsp�czynnik kierunkowy p�prostej jest
//               znormalizowany warto�� ta ma interpretacj� odleg�o�ci.
//    Obj2Omit - obiekt, ktory b�dzie pomijany przy szukaniu przeci��.
//               Zwykle jest to nadajnik emituj�cy promie�.
//
// POST (zwraca warto��):
//  true  - gdy punkt przeci�cia zosta� znaleziony,
//      CorossPnt  - wsp�rz�dne punktu przeci�cia
//
//  false - gdy punkt przeci�cia nie zosta� znaleziony.
//
bool FindCrossPnt4HalfLineAndPolyhedralFace( HalfLine3f   const &Ln,  
                                             ViScene      const &Scn,
                                             float              &t,
                                             Vector3f           &CrossPnt,
                                             ViMultiPolyh const *Obj2Omit
                                           )
{
  /*__TMP__ Zakomentowane, aby odrzucic grafike ______________________
 for (List<BaseObject,IDOBJECT>::ConstIterator BOIter 
                                                  = Scn.GetIter4BaseObject();
         BOIter;  ++BOIter) {
    if ((BaseObject const *)BOIter == Obj2Omit) continue;
    if (BOIter->_GlbOutlineBox.IsCommonPart(Ln)) {
      if (FindCrossPnt4HalfLineAndPolyhedralFace(Ln,*BOIter,t,CrossPnt))
                                                                  return true;
    }
 }
  __TMP_*/
 return false;
}
