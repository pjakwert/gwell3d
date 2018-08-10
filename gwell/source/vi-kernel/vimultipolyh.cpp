/*--------------------------------------------------------------------------
 * \file vimultipolyh.cpp
 * Plik zawiera implementacjê metod klasy
 *     \link ViMultiPolyh ViMultiPolyh\endlink
 * \author  Bogdan Kreczmer
 * \date    2004.03
 */



#ifdef __GNUG__
#pragma implementation
#endif

#include <iostream>
#include <fstream>
#include "vielemepolyh.hh"
#include "vimultipolyh.hh"
#include "vi-keywords.hh"
#include "streamutils.hh"

using namespace std;





void ViMultiPolyh::InitWithDescr( const ExtString &Descr )
{}






/*!
 *  Dodaje now± pozycjê, daj±c± dostêp do zadanej macierzy 
 *  transformacji i definiuj±c± interfejs do danej wspó³rzêdnej.
 * \param pPolyh - wska¼nik na obiekt modeluj±cy bry³ê, dla której 
 *                 bêdzie modyfikowany dany parametr transformacji.
 * \param Mtx - macierz transformacji, z któr± skojarzony
 *              zostaje dany obiekt.
 * \param TransfType - typ transformacji, której parametr bêdzie podlega³
 *                     zmianie,
 * \param Coord - okre¶la, która ze wspó³rzêdnych danego wektora parametrów
 *                ma podlegaæ zmianom.
 * \param TOrder - okre¶la porz±dek translacji wzglêdem rotacji,
 * \param Unit - okre¶la jednostkê, w których podawana jest warto¶æ
 *               danego parametru.
 */
ViKinemCtrlItem * ViMultiPolyh::
              AddCtrlInterface( ViNTreeNode   *pPolyh,
                                ViMatrix3f        &Mtx,
                                Vi::TransformType  TransfType,
                                Vi::Coord3DType    Coord,
                                TransOrder         TOrder,
                                Vi::MetricUnit     Unit
                              )
{
  return _CtrlInterface.Add(pPolyh,Mtx,TransfType,Coord,TOrder,Unit);
}







int ComputeElemePolyhGlbVtx( ViElemePolyh     *pEPolyh,
                             OutlineBox3f     &ObjOln,
                             MatrixH3f  const *pMtx, 
                             int               Level
                           )
{
  if (!pMtx) return 0;
  pEPolyh->ComputeGlbVtx(*pMtx);
  ObjOln.Join(pEPolyh->GlbOlnBox());
  return 0;
}




int ViMultiPolyh::WriteMultiPolyhToFile(
                     const char *             FileName, 
                     MatrixH3f::AnglesType    AType,
                     AngleUnit                AUnit,
                     unsigned int             Margin
                   ) const
{
  ofstream  fstrm(FileName);
  if (!fstrm.is_open()) return -1;
  if (!WriteMultiPolyhTo(fstrm,AType,AUnit,Margin)) return -2;
  return 0;
}


bool ViMultiPolyh::WriteMultiPolyhTo(
                     ostream                 &ostrm, 
                     MatrixH3f::AnglesType    AType,
                     AngleUnit                AUnit,
                     unsigned int             Margin
                   ) const
{
  Space(ostrm,Margin) << KW_MULTIPOLYH_BEGIN << endl;
  for (ViNTreeNode::ConPolyhIter Iter = ConBegin_PolyhHierList(); 
       Iter; ++Iter) {
       Iter->WriteNodeDescriptionTo(ostrm,AType,AUnit,Margin+4);
  }
  Space(ostrm,Margin) << KW_MULTIPOLYH_END << endl; 
  return WriteCtrlInterfaceTo(ostrm,Margin);
}


void ViMultiPolyh::WriteDescriptionTo(ExtString &Descr) const
{
  Descr.clear();
}

/*!
 *  \if brief_public_methods
 *   \brief  Metoda zapisuje sekcjê interfejsu.
 *  \endif
 *
 *  Metoda zapisuje sekcjê interfejsu dla danej bry³y z³o¿onej.
 *  W przypadku, gdy dla danej bry³y nie zosta³ zdefiniowany interfejs
 *  sterowania, to nie s± dokonywany ¿aden wpis do strumienia wyj¶ciowego.
 *  \param ostrm - (\b in/\b out) strumieñ wyj¶ciowy.
 *  \param Margin - (\b in) okre¶la ilo¶æ spacji jakie poprzedzaj± 
 *                   s³owo kluczowe otwieraj±ce sekcjê interfejsu sterownia.
 *  \retval true - je¶li operacja zapisu powiod³a siê.
 *  \retval false - w przypadku przeciwnym.
 */
bool ViMultiPolyh::WriteCtrlInterfaceTo(  ostream      &ostrm,
                                          unsigned int  Margin
                                       ) const
{
  if (!IsCtrlInterface()) return true;
  return GetCtrlInterface().WriteTo(ostrm,Margin);
}



#define  AXIS_SIZE            100

void ViMultiPolyh::ComputeCoordGlbVtx(MatrixH3f const &M)
{
 // To nalezy zoptymalizowac
  Vector3f Pnt(0,0,0);
  Vector3f Scale;

  _IndividualCoord[0] = M*Pnt; 
  Scale = M.GetScale();
  _IndividualCoord[1] = M*Pnt.Set(AXIS_SIZE/Scale.x,0,0); 
  _IndividualCoord[2] = M*Pnt.Set(0,AXIS_SIZE/Scale.y,0); 
  _IndividualCoord[3] = M*Pnt.Set(0,0,AXIS_SIZE/Scale.z); 
}



void ViMultiPolyh::InitIndivCoord(float Axis_Length)
{
  // 0 -> 0, 0, 0
  _IndividualCoord[0].Set(0,0,0);   // 0
  _IndividualCoord[1].Set(Axis_Length,0,0);  // x
  _IndividualCoord[2].Set(0,Axis_Length,0);  // y
  _IndividualCoord[2].Set(0,0,Axis_Length);  // z
}



   /*==========================================================================
    *  Wylicza wspó³rzêdne globalne wierzcho³ków wszystkich bry³ sk³adaj±cych
    *  siê na dany zbiór bry³ oraz wyznacza dla nich wspólny prostopad³o¶cienny
    *  obrys.
    */
int ViMultiPolyh::ComputeHierAllGlbVtx()
{
  _GlbOutlineBox.Reset();
#ifdef TEST
  cerr << " ----------- Start obliczen ---------" << endl; 
#endif
  return WalkAlongPattePolyhTree(ComputeElemePolyhGlbVtx,_GlbOutlineBox);
}
