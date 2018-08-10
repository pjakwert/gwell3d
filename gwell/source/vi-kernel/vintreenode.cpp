#ifdef __GNUG__
#pragma implementation
#endif

/*-------------------------------------------------------------------------
 * \file vipolyhhierlist.cpp
 *  Plik zawiera implementacjê metod klasy 
 *  \link ViNTreeNode ViNTreeNode\endlink,
 *  która jest sercem struktury drzewiastej pozwlaj±cej modelowaæ otwarte
 *  ³añcuchy kinematyczne.
 *
 *  \author  Bogdan Kreczmer
 *  \date    2003.11
 */



#include <cstring>
#include "streamutils.hh"
#include "matrixh3f.hh"
#include "vintreenode.hh"
#include "vinodeaddress.hh"
#include "vielemepolyh.hh"
#include "vi-keywords.hh"
#include "vinodedescr.hh"
#include "viexception.hh"
#include "sxinterp.hh"
#include "vi-sxutils.hh"
#include "visynxinterp.hh"
#include "vielemepolyh.hh"
#include "vimultipolyh.hh"


using namespace std;
using namespace Vi;

ViNTreeNode::ParamDescrBuff ViNTreeNode::_TmpBuff;



//==========================================================================
//...................... ViNTreeNode ...............................

/*! \fn bool ViNTreeNode::ShouldCallForClassDescr(const char *ClassName) const
 * \if brief_public_methods
 *  \brief Decyduje czy ma byæ szukana sekcja opisu klasy
 * \endif
 *
 *
 * Decyduje czy przy odczycie opisu bryly w opisie obiektu modeluj±cego
 * dan± bry³ê ma byæ szukana sekcja opisu dla tej klasy.
 * W przypadku klasy \b ViNTreeNode zawsze jest zwracana warto¶æ \p true.
 * Programista w swojej klasie mo¿e nadpisywaæ tê metodê i zwracaæ warto¶æ
 * \p false. Mo¿e to mieæ zastosowanie w przypadku, gdy wczytywane s±
 * pliki z opisem bry³ elementarnych, których klasy maj± ubo¿sz± strukturê 
 * dziedziczenia.\n
 * W takim przypadku definiowana metoda powinna mieæ postaæ:
 * \code
      bool MojaBryla::ShouldCallForClassDescr(const char *ClassName) const
      {
        return strcmp(ClassName,"MojaBryla");
      }
   \endcode
 * \param ClassName - (\b in) nazwa klasy.
 *  \retval true - dla klasy \b ViNTreeNode zwraca zawsze \p true.
 */







/*!
 *  Metoda ³±czy dany element definiuj±cy pozycjê interfejsu 
 *  (obiekt klasy ViNTreeNode) z danym obiektem klasy
 *  ViNTreeNode, do którego maj± siê odnosiæ zmiany wspó³rzêdnych 
 *  jednego z parametrów macierzy. 
 *
 *  Wspomniane wy¿ej po³±czenie realizowane jest poprzez dodanie do
 *  listy dwukierunkowej. Dodany element jest automatycznie usuwany
 *  stamt±d poprzez usuniêcie interfejsu.
 *  \param pCItem - dodwany element interfejsu sterowania.
 */
void ViNTreeNode::BindWithCtrlInterfaceItem(ViKinemCtrlItem *pCItem)
{
  List<ViKinemCtrlItem,ID_KINEMCTRL_NTREENODE>::AddToTail(pCItem);
}






void ViNTreeNode::InitWithDescr( const ExtString &Descr )
{
  SxInterp  Interp(Descr);
  ViNodeAddress   Address;
  SXCMD_DEFINE_VAR;

  try {
    SXCMD_START_LOOP2END(Interp,
               (KW_INDIVNAME,'n')(KW_NODEADDRESS,'a')(KW_TRANSF2PARENT,'t'))
      case 'n':  // NodeName:
        Interp.LookForChar(':');
        Interp.GetWord(_IndivName);
        continue;
      case 'a':
        Interp.LookForChar(':');
        Interp.GetWord(Address,".");
        continue;
      case 't':
        InitMtxFrom(Interp,UseMtx2ParentCoord());
        continue;
   SXCMD_END_LOOP(Interp);
   ViSynxInterp::GetPolyhList().AddUsingAddress(this,Address);
  }
  catch (Sx::Exception &Except) {
     throw ViException_Syntax(Except.GetErrID(),Except.GetErrMsg());
  }
}



void ViNTreeNode::InterpretParamDescr( const ViNodeDescr &      Descr, 
                                           const ViNTreeNode *  pNode
                                         )
{
  ExtString  ClassDescr;
  if (!Descr.GetClassDescr(GetClassName(),ClassDescr)) {
    throw ViException_Syntax(ERRNUM_SYNTAX__NO_CLASS_DESCR,
                    (MSG(ERRMSG_SYNTAX__NO_CLASS_DESCR),GetClassName()));
  }
  InitWithDescr(ClassDescr);
}


void ViNTreeNode::InterpretParamDescr(const ViNodeDescr &  Descr)
{
  InterpretParamDescr(Descr,(const ViNTreeNode *) 0L);
}


ViNTreeNode::ViNTreeNode(char const *Name)
  : _Transf2ParentCoord(MTXID_NODE2PARENT)
{
  SetName(Name);
  ValidFlag_ResetAll();
}


void ViNTreeNode::AddDescripToBuff( unsigned int       Margin,
                                        ExtString const   &ParamDescr, 
                                        const std::string &TypeName,
                                        void const        *ObjPtr
                                      ) const
{
  ExtString  Line;

  UseBuff().AddSpace(Margin);  WriteToBuff(KW_BEGIN_DERIVSEC);
  WriteToBuff(": ");  WriteToBuff(TypeName.c_str());
  WriteToBuff("\n");

  for (unsigned int i = 0; !ParamDescr.ExtractLineFor(i,Line,true); i++) {
    UseBuff().AddSpace(Margin+1);
    WriteToBuff(Line);
  }
  UseBuff().AddSpace(Margin);  WriteToBuff(KW_END_DERIVSEC);
  WriteToBuff("\n");
}


void ViNTreeNode::WriteDescripToBuff( unsigned int Margin,
                                          const ViNTreeNode *
                                        ) const
{
  UseBuff().clear();
  if (Margin > 2)  UseBuff().AddSpace(Margin-2);
  UseBuff() << KW_NODE << ":\n";
  ExtString  Descr;
  WriteDescriptionTo(Descr);
  AddDescripToBuff(Margin,Descr,GetClassName(),this);
}



void ViNTreeNode::WriteDescriptionTo(ExtString &Descr) const
{
  Descr.clear();
  Descr << KW_INDIVNAME << ": " << IndivName() << "\n";
  Descr << KW_NODEADDRESS << ": " << GetNodeAddress() << "\n";
  Descr << KW_TRANSF2PARENT << "\n";
  Mtx2ParentCoord().WriteParamTo(Descr,Mtx2ParentCoord().GetAngInterp(),
                                       _TmpBuff.GetAngUnit(),2);
}


bool ViNTreeNode::WriteNodeDescriptionTo( 
                                ostream                 &ostrm,
                                MatrixH3f::AnglesType    AType,
                                AngleUnit                AUnit,
                                unsigned int             Margin
                              ) const
{
  UseBuff().clear();
  WriteAllParamToBuff(Margin);
  if (Margin > 2) UseBuff().AddSpace(Margin-2);
  UseBuff() << KW_ENDNODE << "\n";
  ostrm << GetBuff();
  return !ostrm.fail();
}



ViNodeAddress ViNTreeNode::GetNodeAddress() const
 {
    ViNodeAddress NodeAddr;  
    GetNodeAddress(NodeAddr);  
    return NodeAddr;
 }



     //----------------------------------------------------------------------
     // Uniewa¿nia flagê dla wspó³rzêdnych dla danego widoku i struktur od
     //  nich zale¿nych. Akcja ta jest realizowana
     // dla danego wêz³a i wszystkich jego potomków.
     //
void ViNTreeNode::ValidFlag_Reset4All_ViewVtx( int  NView, 
                                                   bool ForAllObjectFamily
                                                 )
{
  WalkAlongPattePolyhTree_IB(&ViNTreeNode::ValidFlag_ResetViewVtx,
                       NView,
                       ForAllObjectFamily);
} 



/*!
 *  Uniewa¿nia flagê dla wspó³rzêdnych wierzho³ków globalnych. Prowadzi to
 *  do uniewa¿nienia równie¿ flag zwi±zanych ze struktrami pochodnymi,
 *  np. wspó³rzêdne wierzcho³ków dla widoków, obrys bry³y.
 *
 *  \param  ForAllObjectFamily - Je¶li true (domy¶lnie), to ustawian jest
 *                     flaga  VFLAG_TEST_DESCENDANTS dla wszystkich kolejnych
 *                     przodków danego wêz³a.
 *                     Je¶li false, to flagi resetowane s± tylko dla
 *                     danego obiektu elementarnego.
 *
 *  \post Uniewa¿nione zostaj± flagi:
 *       GLB_VTX, VIEW_VTX,  RECT_OUT, FACE_POLY, FACE_RGN, FACE_VIEW_RGN
 */
void ViNTreeNode::ValidFlag_ResetGlbVtx(bool ForAllObjectFamily)
{
  VF_ResetGlbVtx();
  VF_ResetDependedOnGlbVtx();
  ValidFlag_ResetAuxDependedOnGlbVtx();
  if (!ForAllObjectFamily) return;
  ValidFlag_SetTestDescants4Acestor();
} 



/*============================================================================
 *  Uniewa¿nia flagê dla wspó³rzêdnych wierzho³ków dla widoku. Prowadzi to
 *  do uniewa¿nienia równie¿ flag zwi±zanych ze struktrami pochodnymi,
 *  np. wspó³rzêdne wierzcho³ków dla widoków, obrys bry³y. Akcja ta jest 
 *  realizowana dla danego wêz³a i wszystkich jego potomków.
 *
 *  PRE:  ForAllObjectFamily - Je¶li true (domy¶lnie), to ustawian jest flaga 
 *                             VFLAG_TEST_DESCENDANTS dla wszystkich kolejnych
 *                             przodków danego wêz³a.
 *                             Je¶li false, to flagi resetowane s± tylko dla
 *                             danego obiektu elementarnego.
 *
 *  POST: Uniewa¿nione zostaj± flagi:
 *            VIEW_VTX,  RECT_OUT, FACE_POLY, FACE_RGN, FACE_VIEW_RGN
 */
void ValidFlag_ResetViewVtx(bool ForAllObjectFamily)
{

}




    /*========================================================================
     * Uniewa¿nia flagê wa¿no¶ci obliczeñ wspó³rzêdnych globalnych 
     * wierzcho³ków i struktur od nich
     * zale¿nych. Akcja ta jest realizowana
     * dla danego wêz³a i wszystkich jego potomków.
     * \param ForAllObjectFamily - jego warto¶æ decyduje o tym czy 
     *          uniewa¿nienie ma byæ zrealizowane równie¿ dla wszystkich
     *          potomków (gdy warto¶æ \p true) danego wêz³a. Je¶li warto¶æ
     *          parametru jest \p false, to uniewa¿nianie jest realizowane
     *          tylko dla danego wêz³a. Warto¶ci± domy¶ln± tego parametru jest
     *          \p true.
     */
void ViNTreeNode::ValidFlag_Reset4All_GlbVtx(bool ForAllObjectFamily)
{
 WalkAlongPattePolyhTree(&ViNTreeNode::ValidFlag_ResetGlbVtx,
                     ForAllObjectFamily);
} 



    /*========================================================================
     * Ustawia wa¿no¶æ flagi dla wspó³rzêdnych globalnych i uniewa¿nia
     * flagi dla struktur od nich zale¿nych. Akcja ta jest realizowana
     * dla danego wêz³a i wszystkich jego potomków.
     */
void ViNTreeNode::ValidFlag_SetGlbVtx(bool ForAllObjectFamily)
{
  VF_SetGlbVtx();
  ValidFlag_ResetAuxDependedOnGlbVtx();
  if (!ForAllObjectFamily) return;
  ValidFlag_SetTestDescants4Acestor();
} 




void ViNTreeNode::ValidFlag_Set4All_GlbVtx(bool ForAllObjectFamily)
{
 WalkAlongPattePolyhTree(&ViNTreeNode::ValidFlag_SetGlbVtx,
                                                     ForAllObjectFamily);
}



/*!
 *  Metoda zwraca najbli¿szego przodka danego wêz³a, który jest klasy
 *  ViElemePolyh lub klasy pochodnej wzglêdem ViElemePolyh. W przypadku
 *  gdy taki wêze³ nie zostanie znaleziony, to zwracany jest 
 *  adres \p NULL.\n
 *  Wska¼nik na wêze³ udostêpniany jest w trybie sta³ym.
 */
const ViElemePolyh *ViNTreeNode::GetAncestor_ElemePolyh() const
{
  const ViNTreeNode *pNode = GetParentNode();

  while (pNode) {
    if (pNode->GetInheritorType() == IT_ELEMEPOLYH) 
                      return (const ViElemePolyh*) pNode;
    pNode = pNode->GetParentNode();
  }
  return 0L;
}


/*!
 *  \fn ViElemePolyh *ViNTreeNode::UseAncestor_ElemePolyh()
 *
 *  Metoda zwraca najbli¿szego przodka danego wêz³a, który jest klasy
 *  ViElemePolyh lub klasy pochodnej wzglêdem ViElemePolyh. W przypadku
 *  gdy taki wêze³ nie zostanie znaleziony, to zwracany jest 
 *  adres \p NULL.\n
 *  Wska¼nik na wêze³ udostêpniany jest w trybie modyfikacji.
 */


/*!
 *  Metoda zwraca najbli¿szego przodka danego wêz³a, który jest klasy
 *  ViMultiPolyh lub klasy pochodnej wzglêdem ViMultiPolyh. W przypadku
 *  gdy taki wêze³ nie zostanie znaleziony, to zwracany jest 
 *  adres \p NULL.\n
 *  Wska¼nik na wêze³ udostêpniany jest w trybie sta³ym.
 */
const ViMultiPolyh *ViNTreeNode::GetAncestor_MultiPolyh() const
{
  const ViNTreeNode *pNode = GetParentNode();

  while (pNode) {
    if (pNode->GetInheritorType() == IT_MULTIPOLYH) 
                      return (const ViMultiPolyh*) pNode;
    pNode = pNode->GetParentNode();
  }
  return 0L;
}


/*!
 *  \fn ViElemePolyh *ViNTreeNode::UseAncestor_MultiPolyh()
 *
 *  Metoda zwraca najbli¿szego przodka danego wêz³a, który jest klasy
 *  ViMultiPolyh lub klasy pochodnej wzglêdem ViMultiPolyh. W przypadku
 *  gdy taki wêze³ nie zostanie znaleziony, to zwracany jest 
 *  adres \p NULL.\n
 *  Wska¼nik na wêze³ udostêpniany jest w trybie modyfikacji.
 */



/*=======================================================================
 * Resetuje flagê swojego przodka (lub wszystkich przodków. Flaga ta
 * która informuje
 * ¿e dane przynajmniej jednego z potomków musz± byæ zaaktualizowane.
 */
void ViNTreeNode::ValidFlag_SetTestDescants4Acestor(bool SetForAllAncestor)
{
  for (ViNTreeNode *pHFig = GetParentNode();
       pHFig;  pHFig = pHFig->GetParentNode()) 
                             pHFig->ValidFlag_SetTestDescants();
}


ViNTreeNode const *ViNTreeNode::SeekNodeInLayer( 
                                                         char const *Name
	                                               ) const
{
  for (ViNTreeNode const *pNode = FirstDesc();
       pNode;  pNode = pNode->NextNode()) {
    if (pNode->IndivName() == Name) return pNode;
  }
  return NULL;
}





void ViNTreeNode::SetMtx2ParentCoord(MatrixH3f const &Mtx)
{
  _Transf2ParentCoord = Mtx;
}




ViNTreeNode const *ViNTreeNode::GetRoot_Scene() const
{
  if (GetInheritorType() == IT_SCENEPOLYHLIST) return this;

  ViNTreeNode const *pNode = this;
  while ((pNode = (ViNTreeNode const*) pNode->Root())) {
    if (pNode->GetInheritorType() == IT_SCENEPOLYHLIST) return pNode;
  }
  return 0L;
}



ViNTreeNode const *ViNTreeNode::SeekNodeAlongPath( 
                                                           char const *NodeAddr
                                                         )  const
{
  ViNTreeNode const *pNode = this;

  if (*NodeAddr == NA_SEPARATOR) {
      if (GetInheritorType() != IT_SCENEPOLYHLIST)
          if (!(pNode = GetRoot_Scene())) return 0L;
    return pNode->SeekNodeAlongPath(NodeAddr);
  }

  ExtString      NodeLabel(NodeAddr);
  NodeLabel.insert(0,NA_SEPARATOR,1);
  ViNodeAddress  Addr(NodeLabel);

  
  if (Addr.GetFirstLabel(NodeLabel)) return 0L;
  do {
    if (!(pNode = pNode->SeekNodeInLayer(NodeLabel))) return 0L;
  } while (Addr.GetNextLabel(NodeLabel));
  return pNode;
}



char const *ViNTreeNode::GetNodeAddress( ViNodeAddress &Address ) const
{
  if (GetInheritorType() == IT_SCENEPOLYHLIST) {
    Address = NA_SEPARATOR;
    return Address();
  }

  GetNodePath(Address);
  return Address << IndivName();
}


//--------------------------------------
// Path: 
//   zwracana sciezka, ktora jako ostatni znak separatro adresu.
//
char const *ViNTreeNode::GetNodePath( ViNodeAddress &Address ) const
{
  Address = NA_SEPARATOR;


  if (GetInheritorType() == IT_SCENEPOLYHLIST) return Address = NA_SEPARATOR;


  ViNodeAddress  LocAddr;

  ViNTreeNode const *pNode = this->GetParentNode();
  if (!pNode) { Address = NA_ERROR; return NULL; }
  if (pNode->GetInheritorType() == IT_SCENEPOLYHLIST) return Address;
  do {
     (LocAddr = NA_SEPARATOR) << pNode->NodeName() << Address;
     Address = LocAddr;
     if (!(pNode = pNode->GetParentNode())) {
                (Address = NA_ERROR) << LocAddr;  return NULL;
     }
  } while (pNode->GetInheritorType() != IT_SCENEPOLYHLIST);

  return Address();
}





/*!
 * Metoda pozwala na otrzymanie macierzy transformacji do uk³adu wspó³rzêdnych
 * finalnej bry³y z³o¿onej (tzn. takiej bry³y z³o¿onej, której bezpo¶rednim
 * rodzicem jest obiekt klasy ViScene).
 * \param Mtx - (\b in/\b out) macierz wynikowa.
 * \retval 1  - je¶li dany obiekt jest zwi±zany ze scen±.
 * \retval 0 - je¶li zachodzi sytuacja przeciwna.
 * \post Do parametru \e Mtx wpisana zostaje macierz transformacji do 
 *       uk³adu wspó³rzêdnych finalnej bry³y z³o¿onej
 *       (je¶li jest zwi±zany z jak±¶ scen±).
 */
int ViNTreeNode::GetMtx2RootCoord(MatrixH3f &Mtx) const
{
  if (GetInheritorType() == IT_SCENEPOLYHLIST) { return 1; }
  Mtx = Mtx2ParentCoord();

  ViNTreeNode const *pNode = this;
  if (!pNode->GetParentNode()) return 0;

  MatrixH3f Mtx_o, &Mtx_n = Mtx;

  while (pNode->GetParentNode()->GetInheritorType() != IT_SCENEPOLYHLIST) {
    Mtx_o = pNode->Mtx2ParentCoord();
    Mtx_o *= Mtx_n;
    Mtx_n = Mtx_o;
    pNode = pNode->GetParentNode();
    if (!pNode->GetParentNode()) return 0;
  }
  return 1;
}



/*!
 * Metoda pozwala na otrzymanie macierzy transformacji do uk³adu wspó³rzêdnych
 * bry³y z³o¿onej, której sk³adnikiem jest dany element. (tzn. element ten
 *  mo¿e byæ bry³± elementarn± lub bry³± z³o¿on±).
 * \param Mtx - macierz wynikowa.
 * \retval 1  - je¶li dany obiekt jest zwi±zany ze obiektem klasy ViMultiPolyh.
 * \retval 0 - je¶li zachodzi sytuacja przeciwna.
 * \post Do parametru \e Mtx wpisana zostaje macierz transformacji do 
 *       uk³adu wspó³rzêdnych bry³y z³o¿onej.
 */
int ViNTreeNode::GetMtx2LocalRootCoord(MatrixH3f &Mtx) const
{
  if (GetInheritorType() == IT_MULTIPOLYH) { Mtx.SetUnitMtx(); return 1; }
  Mtx = Mtx2ParentCoord();

  ViNTreeNode const *pNode = this->GetParentNode();
  MatrixH3f Mtx_o, &Mtx_n = Mtx;

  while (pNode) {
    if (pNode->GetInheritorType() == IT_MULTIPOLYH) return 1;
    Mtx_o = pNode->Mtx2ParentCoord();
    Mtx_o *= Mtx_n;
    Mtx_n = Mtx_o;
    pNode = pNode->GetParentNode();
  }
  return 0;
}





/*!
 * Metoda pozwala na otrzymanie macierzy transformacji do uk³adu wspó³rzêdnych
 * globalnych danej sceny.
 * \param Mtx - macierz wynikowa.
 * \retval 0  - je¶li dany obiekt jest zwi±zany ze scen±.
 * \retval -1 - je¶li zachodzi sytuacja przeciwna.
 * \post Do parametru \e Mtx wpisana zostaje macierz transformacji do 
 *       uk³adu globalnego sceny (je¶li jest zwi±zany z jak±¶ scen±)
 *       lub uk³adu wspó³rzêdnych elementu, który jest korzeniem dla
 *       ca³ej struktury.
 */
int ViNTreeNode::GetMtx2GlbCoord(MatrixH3f &Mtx) const
{
  MatrixH3f Mtx_i;

  if (GetMtx2RootCoord(Mtx_i)) return 0;
  ViNTreeNode const *pRootNode = GetTreeRoot();
  if (!pRootNode) return -1;
  (Mtx = pRootNode->Mtx2ParentCoord()) *= Mtx_i;
  return 0;
}

/*!
 * Metoda pozwala na otrzymanie macierzy transformacji z uk³adu wspó³rzêdnych
 * obiektu, który jest korzeniem ca³ego drzewa (obiekt klasy
 * \link ViMultiPolyh ViMultiPolyh\endlink) do uk³adu wspó³rzêdnych
 * globalnych danej sceny.
 * \param Mtx - macierz wynikowa.
 * \retval 0  - je¶li dany obiekt jest zwi±zany ze scen±.
 * \retval -1 - je¶li zachodzi sytuacja przeciwna.
 * \post Do parametru \e Mtx wpisana zostaje macierz transformacji do 
 *       uk³adu globalnego sceny (je¶li jest zwi±zany z jak±¶ scen±)
 *       lub uk³adu wspó³rzêdnych elementu, który jest korzeniem dla
 *       ca³ej struktury.
 */
int ViNTreeNode::GetMtxRoot2GlbCoord(MatrixH3f &Mtx) const
{
  ViNTreeNode const *pRootNode = GetTreeRoot();
  if (!pRootNode) return -1;
  Mtx = pRootNode->Mtx2ParentCoord();
  return 0;
}


ViNTreeNode *ViNTreeNode::GetTreeRoot()
{
  return (ViNTreeNode*)(*(ViNTreeNode const*)this).GetTreeRoot();
}



ViNTreeNode const *ViNTreeNode::GetTreeRoot() const
{
  ViNTreeNode const *pNode = this;

  for (; pNode->GetParentNode() &&
         pNode->GetParentNode()->GetInheritorType() != IT_SCENEPOLYHLIST;
         pNode = pNode->GetParentNode());
  return pNode;
}



/*!
 * Przesuwa dany wêze³ wraz z ca³ym jego podrzewem do 
 * listy sceny, czyniac go niezale¿nym nowy obiektem tej sceny.
 * \pre Operacja mo¿e zostaæ wykonana pod warunkiem, ¿e klas± pochodn±
 *      dla tego obiektu jest ViMultiPolyh. Oprócz tego obiekt macierzysty
 *      musi nale¿eæ do sceny.
 * \retval 0 - je¶li operacja zosta³a wykonana.
 * \retval 1 - je¶li operacja nie mog³a zostaæ wykonana, gdy¿ obiekt
 *             jest ju¿ w li¶cie bry³ sceny.
 * \retval -1 - je¶li operacja nie mog³a zostaæ wykonana, gdy¿
 *              bry³a nie wchodzi w sk³ad listy bry³ sceny.
 * \retval -2 - je¶li operacja nie mog³a zostaæ wykonana, gdy¿ klas±
 *              pochodn± obiektu nie jest klasa ViMultiPolyh.
 */
int ViNTreeNode::MoveBranchFromParentToRoot()
{
  if (GetInheritorType() != IT_MULTIPOLYH) return -2;
  if (GetParentNode()) return -1;
  if (GetParentNode()->GetInheritorType() == IT_SCENEPOLYHLIST) return 1;
  
  ViNTreeNode *pNode =  GetRoot_Scene();
  
  if (!pNode) return -1;
  MoveBranchTo(pNode);
  return 0;
}



/*!
 * Przesuwa dany wêze³ wraz z ca³ym jego podrzewem do 
 * drzewa, którego elementem jest wêzel \e pNode. Od tego momentu
 * staje siê on rodzicem dla wêz³a reprezentowanego przez obiekt,
 * dla którego wyw³ana zostaje ta metoda.
 * \param pNode - wska¼nik na wêze³, do którego ma zostaæ przesuniête
 *                dane podrzewo.
 * \retval 0 - je¶li operacja zosta³a wykonana.
 * \retval -1 - je¶li operacja nie mog³a zostaæ wykonana, gdy¿
 *              \e pNode == \p NULL.
 */
int ViNTreeNode::MoveBranchTo(ViNTreeNode *pNode)
{
  if (!pNode) return -1;
  RemoveFromList();
  pNode->AddNode(this);
  return 0;
}





/*!
 *  Metoda przechodzi po ca³ej strukturze drzewiastej poczynaj±c od wêz³a,
 *  dla którego zosta³a wywo³ana. Chodz±c po tej strukurze wywo³uje dla niej
 *  funkcjê, która przekazywana jest jako parametr wywo³ania tej metody.
 *  Przechodzenie nastêpuje w porz±dku preorder.
 *
 *  \param  Fun - funkcja, która jest wywo³ywana dla ka¿dego wêz³a. Parametrami
 *          tej funkcji jest wska¼nik na dany obiekt modeluj±cy bry³ê 
 *          elementarn± (obiekt klasy \link ViElemePolyh ViElemePolyh\endlink.
 *          Drugim parametrem jest jest wska¼nik \b void.
 *          Trzecim parametrem jest warto¶æ okre¶laj±ca poziom zag³êbienia
 *          w strukturze drzewa. Pocz±tkowa warto¶æ tego parametru jest
 *          brana z warto¶ci parametru \e Level.
 *  \param  pData  - wska¼nik na dowoln± strukturê danych, która jest
 *                 obs³ugiwana przez funkcjê \e Fun.
 *  \param  Level - poziom zag³êbienia w strukturze drzewiastej. Warto¶æ
 *                 parametru pokazuje na jakiej g³êboko¶ci jest dany wêze³.
 *
 *  \pre
 *    Dla wêz³a, dla którego wywo³ana jest bezpo¶rednio ta metoda, warto¶æ 
 *    parametru \e Level musi byæ równa 0.
 *  \post
 *    Metoda przechodzi po wszystkich obiektach klasy 
 *    \link ViElemePolyh ViElemePolyh\endlink i wywo³uje dla nich funkcjê
 *     \e Fun. 
 */
int ViNTreeNode::WalkAlongTree_PreOrder(
		 int (*Fun)(ViElemePolyh const *, void *, int Level),
                 void *pData,
                 int   Level 
              ) const
{
  int err;
  
  for ( ViNTreeNode const *pNode = FirstDesc();
        pNode;  pNode = pNode->NextNode()) {
    if ((err = (*Fun)((ViElemePolyh const *)pNode,pData,Level+1))) return err;
    if ((err = pNode->WalkAlongTree_PreOrder(Fun,pData,Level+1))) return err;
  }
  return 0;
}




int ViNTreeNode::WalkAlongPattePolyhTree(
                               int (*Fun)(ViElemePolyh const *pNode_i, 
                                          MatrixH3f    const *pMtx_i, 
                                          int Level_i
                                         ),
                               MatrixH3f const *pMtx,
                               int Level 
                             ) const
{
 MatrixH3f Mtx_new = pMtx ? *pMtx : Mtx2ParentCoord();
 int err;

 if (pMtx) { Mtx_new *= Mtx2ParentCoord(); }

 for ( ViNTreeNode const *pNode = FirstDesc();
        pNode;  pNode = pNode->NextNode()) {
  if ((err = (*Fun)((ViElemePolyh const *)pNode,&Mtx_new,Level+1))) {
      return err;
  }
  if ((err = pNode->WalkAlongPattePolyhTree(Fun,&Mtx_new,Level+1))) {
      return err;
  }
 }

 if (!Level) return 0;
 Mtx_new *= ((ViElemePolyh*)this)->Mtx2SolidFigCoord();

 return 0;
}






int ViNTreeNode::WalkAlongPattePolyhTree(
              int (*Fun)(ViElemePolyh *, MatrixH3f const *pMtx, int Level),
              MatrixH3f const *pMtx,
              int Level 
           )
{
 MatrixH3f Mtx_new = pMtx ? *pMtx : Mtx2ParentCoord();
 int err;

 if (pMtx) Mtx_new *= Mtx2ParentCoord();
 if (GetInheritorType() == IT_ELEMEPOLYH) {
   if ((err = (*Fun)((ViElemePolyh *)this,&Mtx_new,Level))) return err;
 }
 for ( ViNTreeNode *pRFig = FirstDesc();
        pRFig;  pRFig = pRFig->NextNode()) {
  if ((err = pRFig->WalkAlongPattePolyhTree(Fun,&Mtx_new,Level+1))) return err;
 }
 return 0;
}





/*!
 *  Metoda przechodzi po ca³ej strukturze drzewiastej poczynaj±c od wêz³a,
 *  dla którego zosta³a wywo³ana. Chodz±c po tej strukurze wywo³uje dla niej
 *  funkcjê, która przekazywana jest jako parametr wywo³ania tej metody.
 *
 *  \param  Fun - funkcja, która jest wywo³ywana dla ka¿dego wêz³a. Parametrami
 *          tej funkcji jest wska¼nik na dany obiekt modeluj±cy bry³ê 
 *          elementarn± (obiekt klasy \link ViElemePolyh ViElemePolyh\endlink.
 *          Drugim parametrem jest referencja do prostopad³o¶ciennego
 *          obrysu danej bry³y (klasa \link OutlineBox3f OutlineBox3f\endlink),
 *          Nastêpnym jest wska¼nik na macierz transformacji oraz numer 
 *          zag³êbienia (parametr \e Level).
 *  \param  Oln  - macierz transformacji, która jest przekazywana jako 
 *                 parametr przy kolejnych wywo³aniach funkcji \e Fun.
 *  \param  pMtx - wska¼nik na macierz, który dalej jest przekazywany
 *                 jako parametr dla kolejnych wywo³añ funkcji \e Fun.
 *  \param  Level - poziom zag³êbienia w strukturze drzewiastej. Warto¶æ
 *                 parametru pokazuje na jakiej g³êboko¶ci jest dany wêze³.
 *
 *  \pre
 *    Dla wêz³a, dla którego wywo³ana jest bezpo¶rednio ta metoda, warto¶æ 
 *    parametru \e Level musi byæ równa 0.
 *  \post
 *    Metoda przechodzi po wszystkich obiektach klasy 
 *    \link ViElemePolyh ViElemePolyh\endlink i wywo³uje dla nich funkcjê
 *     \e Fun. 
 *
 *    Metoda ta wykorzysta jest miêdzy innymi do wyliczania wspó³rzêdnych
 *    globalnych wierzcho³ków bry³ elementarnych wchodz±cych w sk³ad danej
 *    bry³y z³o¿onej.
 */
int ViNTreeNode::WalkAlongPattePolyhTree(
       int (*Fun)(ViElemePolyh *,OutlineBox3f &, MatrixH3f const *, int Level),
       OutlineBox3f        &Oln,
       MatrixH3f const *pMtx,
       int Level 
      )
{
  MatrixH3f Mtx_new = pMtx ? *pMtx : Mtx2ParentCoord();
  int err;

  if (pMtx) Mtx_new *= Mtx2ParentCoord();
  if (GetInheritorType() == IT_ELEMEPOLYH) {
    if ((err = (*Fun)((ViElemePolyh *)this,Oln,&Mtx_new,Level))) return err;
  }
  for ( ViNTreeNode *pRFig = FirstDesc();
        pRFig;  pRFig = pRFig->NextNode()) {
     if ((err = pRFig->WalkAlongPattePolyhTree(Fun,Oln,&Mtx_new,Level+1))) 
        return err;
  }
  return 0;
}





/*!
 * Metoda ma charakter pomocniczy i przeznaczona jest do wykonywania
 * z wykorzystaniem metod z rodziny ValidFlag_... .
 * \param Method - metoda, która wywo³ywana jest dla ka¿dego wêz³a.
 *          Parametrem jest warto¶æ logiczna.
 * \param ForAllObjectFamily - warto¶æ logiczna z jak± wywo³ywana
 *        jest metoda \e Method tylko dla wêz³a, dla którego wywo³ana zostaje
 *        ta metoda. Dla pozosta³ych warto¶æ ta jest zawsze false.
 *        Jest to spowodowane tym ¿e warto¶æ tego parametru decyduje
 *        o tym czy dana flaga bêdzie ustawiana równie¿ dla przodków
 *        danego wêz³a (np. patrz opis metody 
 *        \link  ViNTreeNode::ValidFlag_ResetGlbVtx 
 *               ValidFlag_ResetGlbVtx \endlink).
 * \param  Level - poziom zag³êbienia w strukturze drzewiastej. Warto¶æ
 *                 parametru pokazuje na jakiej g³êboko¶ci jest dany wêze³.
 * \retval 0 - po wywo³aniu dla ka¿dego z wêz³ów metoda \e Method zwróci³a
 *             warto¶æ 0.
 * \retval !=0 - je¶li po wywo³aniu metody dla jednego z wêz³ów zwróci³a
 *               ona warto¶æ ró¿n± od zera. Przegl±danie pozosta³ych
 *               wierzcho³ków zostaje wówczas przerwane i otrzymana
 *               warto¶æ jest zwracana jako wynik dzia³ania.
 */
int ViNTreeNode::WalkAlongPattePolyhTree( 
            void (ViNTreeNode::*Method)(bool val),
            bool ForAllObjectFamily,
            int  Level
          )
{
  int err;

  if (Level) (this->*Method)(false);
  for ( ViNTreeNode *pRFig = FirstDesc();
        pRFig;  pRFig = pRFig->NextNode()) {
    if ((err = 
          pRFig->WalkAlongPattePolyhTree(Method,ForAllObjectFamily,Level+1))) 
                                                                    return err;
  }
  if (!Level) (this->*Method)(ForAllObjectFamily);
  return 0;
}





/*!
 * Metoda ma charakter pomocniczy i przeznaczona jest do wykonywania
 * z wykorzystaniem metod z rodziny ValidFlag_... .
 * Jej zastosowanie przewidziane jest w klasach pochodnych zawieraj±cych
 * dane zale¿ne od grafiki i wyró¿niaj±ce poszczególne widoki.
 * \param Method - metoda, która wywo³ywana jest dla ka¿dego wêz³a.
 *          Parametrami s± numer widoku (\e NView) i warto¶æ logiczna
 *          (\e ForAllObjectFamily).
 * \param NView - numer widoku.
 * \param ForAllObjectFamily - warto¶æ logiczna z jak± wywo³ywana
 *        jest metoda \e Method tylko dla wêz³a, dla którego wywo³ana zostaje
 *        ta metoda. Dla pozosta³ych warto¶æ ta jest zawsze false.
 *        Jest to spowodowane tym ¿e warto¶æ tego parametru decyduje
 *        o tym czy dana flaga bêdzie ustawiana równie¿ dla przodków
 *        danego wêz³a (np. patrz opis metody 
 *        \link  ViNTreeNode::ValidFlag_ResetGlbVtx 
 *               ValidFlag_ResetGlbVtx \endlink).
 * \param  Level - poziom zag³êbienia w strukturze drzewiastej. Warto¶æ
 *                 parametru pokazuje na jakiej g³êboko¶ci jest dany wêze³.
 * \retval 0 - po wywo³aniu dla ka¿dego z wêz³ów metoda \e Method zwróci³a
 *             warto¶æ 0.
 * \retval !=0 - je¶li po wywo³aniu metody dla jednego z wêz³ów zwróci³a
 *               ona warto¶æ ró¿n± od zera. Przegl±danie pozosta³ych
 *               wierzcho³ków zostaje wówczas przerwane i otrzymana
 *               warto¶æ jest zwracana jako wynik dzia³ania.
 */
int ViNTreeNode::WalkAlongPattePolyhTree_IB( 
            void (ViNTreeNode::*Method)(int, bool val),
            int  NView,
            bool ForAllObjectFamily,
            int  Level
          )
{
  int err;

  if (Level) (this->*Method)(NView,false);
  for ( ViNTreeNode *pRFig = FirstDesc();
        pRFig;  pRFig = pRFig->NextNode()) {

   if ((err = pRFig->
       WalkAlongPattePolyhTree_IB(Method,NView,ForAllObjectFamily,Level+1))) 
                                                                    return err;
  }
  if (!Level) (this->*Method)(NView,ForAllObjectFamily);
  return 0;
}

//...................... ViNTreeNode ...............................
//==========================================================================
