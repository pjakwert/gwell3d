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
 * Szuka punktu przeciêcia pó³prostej z dan± ¶ciank± przy za³o¿eniu, ¿e 
 * dany wielobok jest wypuk³y.
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
    //   Idzie wzd³u¿ brzegu i sprawdza czy wzglêdem danego punktu jest
    //   on wypuk³y.
    //   Porz±dek wierzcho³ków jest odwrotny do wskazówek zegara.
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
// Metoda przygotowana dostosowana jest tylko dla bry³ wypuk³ych.
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
// Metoda szuka tych punktów, które s± bli¿sze ni¿ warto¶æ parametru t.
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
// Funkcja szuka najbli¿ego punktu przeciêcia danej pó³prostej z widzialnymi
// ¶ciankami wielo¶cianów znajduj±cymi siê na danej scenie.
//
// PRE:   Ln   - zawiera opis pó³prostej,
//        Cell - udostêpnia opis sceny.
//        t    - warto¶æ parametru okre¶laj±ca dopuszczalne maksymalne 
//               oddalenie punktów przeciêcia od pocz±tku prostej.
//               W przypadku gdy wspó³czynnik kierunkowy pó³prostej jest
//               znormalizowany warto¶æ ta ma interpretacjê odleg³o¶ci.
//    Obj2Omit - obiekt, ktory bêdzie pomijany przy szukaniu przeciêæ.
//               Zwykle jest to nadajnik emituj±cy promieñ.
//
// POST (zwraca warto¶æ):
//  true  - gdy punkt przeciêcia zosta³ znaleziony,
//      CorossPnt  - wspó³rzêdne punktu przeciêcia
//
//  false - gdy punkt przeciêcia nie zosta³ znaleziony.
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
