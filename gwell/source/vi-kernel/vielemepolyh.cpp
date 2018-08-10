#ifdef __GNUG__
#pragma implementation
#endif

#include "selectionflags.h"
#include "vielemepolyh.hh"
#include "vector3f.hh"
#include "viface.hh"
#include "vi-keywords.hh"
#include "vipattepolyh.hh"
#include "visynxinterp.hh"
#include "vi-sxutils.hh"
#include "vipatteaddress.hh"
#include "vipattepolyhlib.hh"


unsigned int ViElemePolyh::_FacesCount = 0;



void ViElemePolyh::InitWithDescr( const ExtString &Descr )
{
  ViSynxInterp   Interp(Descr);
  SXCMD_DEFINE_VAR;
  ExtString       PattName;
  ViPatteAddress  PattAddr;
  const ViPattePolyh *pPatte;

  SXCMD_START_LOOP2END(Interp,(KW_PATTNAME,'P')(KW_PATTE2ELEME,'E')
                              (KW_ELEME2INDIV,'I'))
    case 'P': 
      Interp.LookForChar(':');
      Interp.GetWord(PattAddr,":");
      //=== if (!(pPatte = Interp.GetScene()->FindPattePolyh(PattAddr))) {
      if (!(pPatte = Interp.GetPatteLibList()->FindPattePolyh(PattAddr))) {
        throw ViException_Patte(ERRNUM_PATTE__NO_PATTE_POLYH,
               (MSG(ERRMSG_PATTE__NO_PATTE_POLYH),
                   PattAddr.GetLibraryNameStr().c_str(),
                   PattAddr.GetPatteNameStr().c_str(),
                   PattAddr.GetPatteTypeStr().c_str()));
      }
      //== Realizacja polaczenia bryly elementarnej z bryla wzorcowa.
      SetPattePolyh(pPatte);
      continue;
    case 'E':
      Interp.LookForChar(':');
      Vi::InitMtxFrom(Interp,Mtx2ElemeCoord()); 
      continue;
    case 'I':
      Interp.LookForChar(':');
      Vi::InitMtxFrom(Interp,Mtx2IndivCoord());
      continue;
  SXCMD_END_LOOP(Interp);
}




void ViElemePolyh::WriteDescriptionTo(ExtString &Descr) const
{
  Descr << KW_PATTNAME << ": " << PattPolyh().GetLibName() 
        << "::" << PattPolyh().GetListName() 
        << "::" << PattPolyh().GetName() << "\n";
  Descr << KW_PATTE2ELEME << ":\n";
  Mtx2SolidFigCoord().WriteParamTo(Descr,Mtx2SolidFigCoord().GetAngInterp(),
                                                             GetAngUnit(),2);
  Descr << KW_ELEME2INDIV << ":\n";
  Mtx2IndivCoord().WriteParamTo(Descr,Mtx2IndivCoord().GetAngInterp(),
                                                             GetAngUnit(),2);
}


void ViElemePolyh::SetPattePolyh(const ViPattePolyh *pPatt)
{
  _pPattePolyh = pPatt;
  if (!pPatt) return;
  if (_GlbVtx) delete [] _GlbVtx;
  _GlbVtx   = new Vector3f[pPatt->GetVtxNo()];
  if (_GlbVtx == NULL) return;
  for (unsigned int ix=0; ix < pPatt->GetVtxNo(); ix++)
                   _GlbVtx[ix] = pPatt->Vertex(ix);
  if (_PolyhFaces) delete [] _PolyhFaces;
  ResetFacesCount();
  _PolyhFaces = new ViElemePolyhFace[pPatt->GetFacesNo()](*this);  

  //----------------------------------------------------------------------
  // Petla inicjalizacji idneksow sasiednich wierzcholkow 
  //

  for (int idx_f = 0;  idx_f < pPatt->GetFacesNo();  idx_f++) {
    ViElemePolyhFace  &EFace = _PolyhFaces[idx_f];
    for (int idx_e = 0; idx_e < EFace.GetEdgesNo(); idx_e++) {
      EFace.UseGlbEdge(idx_e).PostInit();
    }
  }
}


ViElemePolyh::ViElemePolyh( ViPattePolyh const *pPolyh,
                             const char        *IndivName
			    ):
  _Mtx_Patte2Eleme(MTXID_PATTE2ELEME),  _Mtx_Eleme2Indiv(MTXID_ELEME2INDIV)
{
  _GlbVtx = 0L;  _PolyhFaces = 0L;
  SetPattePolyh(pPolyh);
  SetName(IndivName);
  SetUnselected();
}



ViElemePolyh::ViElemePolyh( ViPattePolyh const &PPolyh,
                             const char        *IndivName
                          ):
  _Mtx_Patte2Eleme(MTXID_PATTE2ELEME),  _Mtx_Eleme2Indiv(MTXID_ELEME2INDIV)
{ 
  _GlbVtx = 0L;  _PolyhFaces = 0L;
  SetPattePolyh(PPolyh);
  SetName(IndivName);
  SetUnselected();
}



ViElemePolyh::~ViElemePolyh()
{
  if (_GlbVtx) delete [] _GlbVtx;
}



void ViElemePolyh::SetMtx2SolidFigCoord(MatrixH3f::Parameters const &FP)
{
  Mtx2SolidFigCoord() <<= FP;
}


void ViElemePolyh::SetMtx2SolidFigCoord(MatrixH3f const &Mtx)
{
  Mtx2SolidFigCoord() = Mtx;
}



void ViElemePolyh::SetMtx2IndivCoord(MatrixH3f::Parameters const &FP)
{
  Mtx2IndivCoord() <<= FP;
}


void ViElemePolyh::SetMtx2IndivCoord(MatrixH3f const &Mtx)
{
  Mtx2IndivCoord() = Mtx;
}




bool ViElemePolyh::SetSelection(unsigned int SelOpt)
{
  bool OldSelection = _Selected;

  switch(SelOpt) {
   case NOSELECT : return false;
   case SELECT   : _Selected=true;  break;
   case UNSELECT : _Selected=false;  break;
   case XORSELECT: _Selected = !_Selected; return true;
  }
  return _Selected != OldSelection;
}


ViFace const *ViElemePolyh::GetPattFace(int FNo) const 
{ 
  return PattPolyh().GetFacesTab()+FNo; 
}

/*
unsigned int ViElemePolyh::GetVtxNo() const
{
  return PattPolyh().GetVtxNo();
}
*/

unsigned int  ViElemePolyh::GetFacesNo() const 
{ 
  return PattPolyh().GetFacesNo(); 
}



/*===========================================================================
 * Dokonuje zmiany rozmiaru. Jednocze¶nie resetuje flagi wa¿no¶ci
 * danych obliczeniowych dla danego obiektu elementarnego.
 *
 * POST:  Je¶li  ValidFlagsForAllParents == true, to dla wszystkich przodków
 *        w strukturze drzewiastej danego obiektu ustawiana jest flaga
 *    VFLAG_TEST_DESCENDANTS  sygnalizuj±ca niewa¿no¶æ danych obliczeniowych
 *    jednego z potomków.
 *    W przypadku przeciwnym flagi dla przodków nie s± ustawiane.
 */
void ViElemePolyh::Resize( float ScaX, float ScaY, float ScaZ,
                           bool ValidFlagsForAllParents
                         )
{
  Resize(Vector3f(ScaX,ScaY,ScaZ));
}


/*===========================================================================
 * Dokonuje zmiany rozmiaru. Jednocze¶nie resetuje flagi wa¿no¶ci
 * danych obliczeniowych dla danego obiektu elementarnego.
 *
 * POST:  Je¶li  ValidFlagsForAllParents == true, to dla wszystkich przodków
 *        w strukturze drzewiastej danego obiektu ustawiana jest flaga
 *    VFLAG_TEST_DESCENDANTS  sygnalizuj±ca niewa¿no¶æ danych obliczeniowych
 *    jednego z potomków.
 *    W przypadku przeciwnym flagi dla przodków nie s± ustawiane.
 */
void ViElemePolyh::Resize( Vector3f const &Sca, 
                                bool            ValidFlagsForAllParents
                              )
{
  MatrixH3f::Parameters FPar;

  FPar<<=Mtx2IndivCoord();
  FPar.SetScale(Sca);
  SetMtx2IndivCoord(FPar);

  ValidFlag_ResetGlbVtx(ValidFlagsForAllParents);
}





void ViElemePolyh::TranslateIndivCoord(Vector3f const &Step)
{
  Vector3f  Scale;
  Vector3f &NewStep = Scale;
  // To trzeba jeszcze sprawdz. 
  Scale = Mtx2SolidFigCoord().GetScale();
  NewStep.Set(Step.x/Scale.x,Step.y/Scale.y,Step.z/Scale.z);
  //ZMIEN na Before
  Mtx2IndivCoord().AddTrans_TAfterR(NewStep);
}



#define  AXIS_SIZE            100

void ViElemePolyh::ComputeCoordGlbVtx(MatrixH3f const &M)
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



void ViElemePolyh::InitIndivCoord(float Axis_Length)
{
  // 0 -> 0, 0, 0
  _IndividualCoord[0].Set(0,0,0);   // 0
  _IndividualCoord[1].Set(Axis_Length,0,0);  // x
  _IndividualCoord[2].Set(0,Axis_Length,0);  // y
  _IndividualCoord[2].Set(0,0,Axis_Length);  // z
}



ViElemePolyh::ConFaceIter ViElemePolyh::GetFacesIter_Const() const
{
  return ViElemePolyh::ConFaceIter(GetFacesNo(),GetGlbFacesTab());
}


ViElemePolyh::VarFaceIter ViElemePolyh::GetFacesIter()
{
  return ViElemePolyh::VarFaceIter(GetFacesNo(),GetGlbFacesTab());
}



ViElemePolyh::ConFaceIter ViElemePolyh::ConBegin_GlbFace() const
{
  return ViElemePolyh::ConFaceIter(GetFacesNo(),GetGlbFacesTab());
}


ViElemePolyh::VarFaceIter ViElemePolyh::VarBegin_GlbFace()
{
  return ViElemePolyh::VarFaceIter(GetFacesNo(),GetGlbFacesTab());
}




void ViElemePolyh::ComputeGlbVtx(MatrixH3f const &ObjPos)
{ 
  MatrixH3f TF = ObjPos * Mtx2SolidFigCoord();
  TF *= Mtx2IndivCoord();  // Przesuniecie lokalnego ukladu bryly
                           // w stosunku do ukladu wspolrzednych wzorca.
  ComputeCoordGlbVtx(TF);  //2004.05.30 Zmiana, wyliczanie przesuniete
                           // za instrukcje, ktora jest powyzej.

  if (!PattPolyh().GetVtxNo()) return;
  GlbOlnBox().Init(GlbVtx(0) = TF * PattPolyh().Vertex(0));

  unsigned int i;
    //--------------------------------------------------------------------
    // Obliczanie globalnych wspó³rzêdnych wierzcho³ków.
  for (i = 1;  i < PattPolyh().GetVtxNo();  i++) { 
         GlbVtx(i) = TF * PattPolyh().Vertex(i);
         GlbOlnBox().Join(GlbVtx(i));
  }
    //---------------------------------------------------------------------
    // Obliczanie równañ p³aszczyzny ¶cianek i wektorów normalnych ¶cianek.
  for (ViElemePolyh::VarFaceIter FIter = GetFacesIter(); FIter; FIter++){
    if (!FIter->ComputePlain3f()) {
      //      cerr << "!!!   Obliczenia zaniechane dla scianki bryly elementarnej"
      //           << endl;
    }
  }

  ValidFlag_SetGlbVtx();
  return;
}

