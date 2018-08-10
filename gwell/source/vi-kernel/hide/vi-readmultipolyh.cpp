#include <fstream>
#include <iostream>
#include <cstdarg>
#include <cstring>
#include <set>
#include "vi-keywords.hh"
#include "vi-readmultipolyh.hh"
#include "viscene.hh"
#include "vintreenode.hh"
#include "vinodedescr.hh"
#include "vielemepolyh.hh"
#include "sxinterp.hh"
#include "visynxinterp.hh"
#include "vinodeaddress.hh"

using namespace std;

#define SEEKKEYWORDS( KeyWords ) \
   ({ const char KeyWordsTab = KeyWords;\
      int no = SeekLineKeyWord(istrm,KeyWordsTab); no; })




/*!
 *  Klasa umo¿liwia wczytywanie opisu bry³y z³o¿onej
 *  i wyeksrahowywanie z niego odpowiednich jednostek syntaktycznych
 *  przydzielonych odpowiadaj±cych poszczególnym klasom pochodnym
 *  wyprowadzonych z klasy bazowej ViNTreeNode.
 */
class ViPolyhDescr: public ExtString {
 public:
  /*!
   *  Zadaniem metody jest usuniêcie komentarza z linii.
   *  Metoda w tej chwili nie jest jeszcze zaimplementowana.
   */
  void RemoveComment(ExtString &Line) {} // Zaimplementowaæ
  //  bool ReadLine(istream &istrm);
  /*!
   *  Czyta strumieñ wej¶ciowy. Odrzuca z ka¿dej linii komentarz
   *  jednoliniowy (je¶li wystêpuje) i sprawdza, czy dana linia
   *  zawiera poszukiwne s³owo kluczowe.
   *  \param  istrm - strumieñ wej¶ciowy.
   *  \param  KeyWord - s³owo kluczowe.
   *  \retval true - je¶li s³owo zostanie znalezione,
   *  \retval false - w przypadku przeciwnym.
   *  \exception ViException_Syntax - zg³szany jest z kodem b³êdu
   *    \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_KEYWORD
   *                       ERRNUM_SYNTAX__UNEXPECTED_KEYWORD\endlink,
   *           gdy napotkane s³owo nie odpowiada oczekiwanemu s³owu kluczowemu.
   */
  bool SeekLineKeyWord(istream &istrm, const char *KeyWord);
    //    throw (ViException_Syntax);


  /*!
   *  Czyta strumieñ wej¶ciowy. Odrzuca z ka¿dej linii komentarz
   *  jednoliniowy (je¶li wystêpuje) i sprawdza, czy dana linia
   *  zawiera poszukiwne jedno ze s³ów kluczowych.
   *  \param  istrm - strumieñ wej¶ciowy.
   *  \param  KeyWord - s³owo kluczowe.
   *
   *  \pre
   *  Liczba prametrów mo¿e byæ dowolna. Warunkiem koniecznym jest, aby
   *  ostatnim argumentem by³ wska¼nik pusty (\p NULL).
   *
   *  \return numer znalezionego s³owa kluczowego na li¶cie argumentów
   *          wywo³ania danej funkcji. Numeracja rozpoczyna siê od 1.
   *          W przypadku, gdy napotkany zostanie koniec pliku i próba
   *          czytania nie powiedzie siê, zwracana jest warto¶æ 0.
   *  \exception ViException_Syntax - zg³szany jest z kodem b³êdu
   *    \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2
   *                       ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2\endlink,
   *           gdy napotkane s³owo nie odpowiada ¿adnemu ¿adnemu s³owu
   *           z zadanego zbioru oczekiwanych s³ów kluczowych.
   */
  int   SeekLineKeyWords(istream &istrm, const char *KeyWord, ... );
    //    throw (ViException_Syntax);
  /*!
   * Udostêpnia nastêpn± liniê, która jest niepusta i nie zwiera
   * prowadz±cych "bia³ych" znaków, ani te¿ nie zawiera takich znaków
   * na koñcu.
   * \retval true - je¶li nastêpn± liniê mo¿e zostaæ udostêpniona,
   * \retval false - w przypadku przeciwnym.
   */
  bool GetNextCleanedLine(istream   &istrm,  ExtString &Line);

  /*!
   *  Sk³aduje czytany tekst w obiekcie klasy ExtString, a¿ do momentu
   *  napotkania zadanego s³owa kluczowego.
   *  \param istrm - tekstowy strumieñ wej¶ciowy.
   *  \param KeyWord - wskazuje na s³owo kluczowe, którego napotkanie ma
   *             koñczyæ sk³adowanie napotkanego tekstu.
   *  \param StoredText - w obiekcie tym sk³adowny jest czytany tekst.
   *
   *  \pre Parametr \e KeyWord nie mo¿e mieæ warto¶ci \p NULL.
   *
   *  \exception ViException_Syntax - zg³aszany jest
   *        \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_END
   *                           ERRNUM_SYNTAX__UNEXPECTED_END\endlink
   *        w przypadku, gdy osi±gniêty zosta³ koniec strumienia,
   *        nie zosta³o napotkane natomiast oczekiwane s³owo kluczowe.
   */
  void  StoreUntilKeyWord( istream    &istrm, 
                           const char *KeyWord, 
                           ExtString  &StoredText

			   ); //  throw (ViException_Syntax);
  /*!
   *   Usuwa znaki bia³e z linii oraz komentarz.
   *   \retval  true - je¶li po oczyszczeniu linia nie jest pusta.
   *   \retval  false - w przypadku przeciwnym.
   */
  bool CleanLine(ExtString &Line);
};




bool ViPolyhDescr::CleanLine(ExtString &Line)
{
  RemoveComment(Line);
  Line.RemoveSpace();
  if (Line.IsEmpty()) return false;
  if (*Line.c_str() == '#') return false;
  string:size_type CommPos = Line.find_first_of("#");
  if (CommPos != string::npos) {
    Line.erase(CommPos);
    Line.RemoveSpace();
  }
  return !Line.IsEmpty();
}


bool ViPolyhDescr::GetNextCleanedLine(istream   &istrm,  ExtString &Line)
{
  while (istrm.good()) {
    getline(istrm,Line);
    if (CleanLine(Line)) return true;
  }
  return false;
}


bool ViPolyhDescr::SeekLineKeyWord(istream &istrm, const char *KeyWord)
  //  throw (ViException_Syntax)
{
  ExtString  Line;

  if (GetNextCleanedLine(istrm,Line)) return false;
  if (Line == KeyWord) return true;
  throw ViException_Syntax(ERRNUM_SYNTAX__UNEXPECTED_KEYWORD,
            (MSG(ERRMSG_SYNTAX__UNEXPECTED_KEYWORD),Line.c_str(),KeyWord));
  return false;
}


bool CompareString(const char *str1, const char *str2)
{
  return strcmp(str1,str2) == 1 ? true : false;
}


class IndexedKeyWord {
  public:
   const char *KeyWord;
   int         Index;
  
   bool operator < (const IndexedKeyWord& Key) const
            {
               return strcmp(KeyWord,Key.KeyWord) > 0; 
            }
   bool operator == (const IndexedKeyWord& Key) const
            {
              return strcmp(KeyWord,Key.KeyWord) == 0;
            }
  IndexedKeyWord(int Idx, const char *Key) { Index = Idx; Key = KeyWord; }
};


int ViPolyhDescr::SeekLineKeyWords(istream &istrm, const char *KeyWord, ... )
  //    throw (ViException_Syntax)
{
  if (!KeyWord) return -1;

  set<IndexedKeyWord>  KeyWordSet;  
  ExtString         Line;
  ExtString         AllKeyWords;
  const char *      Sep = "";
  IndexedKeyWord    IKey(1,0L);


  va_list  ParamList;

  va_start(ParamList,KeyWord);
  while (KeyWord) {
    AllKeyWords << Sep << KeyWord;
    Sep = ", ";
    IKey.KeyWord = KeyWord;
    KeyWordSet.insert(IKey);
    ++IKey.Index;
    KeyWord = va_arg(ParamList,const char*);
  }
  va_end(ParamList);
  
  set<IndexedKeyWord>::const_iterator  pos;

  if (!GetNextCleanedLine(istrm,Line)) return 0;
  IKey.KeyWord = Line.c_str();
  if ((pos = KeyWordSet.find(IKey)) != KeyWordSet.end()) {
    return pos->Index;
  }
  throw ViException_Syntax(ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2,
            (MSG(ERRMSG_SYNTAX__UNEXPECTED_KEYWORD2),Line.c_str(),
             AllKeyWords.c_str()));
  return -1;
}



void ViPolyhDescr::StoreUntilKeyWord( istream    &istrm, 
                                      const char *KeyWord, 
                                      ExtString  &StoredText
				      ) // throw (ViException_Syntax)
{
  ExtString  Line;

  StoredText.clear();
  while (GetNextCleanedLine(istrm,Line)) {
    if (Line == KeyWord)   return;
    StoredText << Line << "\n";
  }
  throw ViException_Syntax(ERRNUM_SYNTAX__UNEXPECTED_END,
			 (MSG(ERRMSG_SYNTAX__UNEXPECTED_END),KeyWord));
}





namespace Vi {

 /*!
  *  Funkcja tworzy obiekty klas 
  *  ViElemePolyh oraz ViMultiPolyh.
  *  Funkcja ta jest wykorzystywana do tworzenia obiektu tylko w tym
  *  przypadku,
  *  gdy programista w funkcji przekazywanej jako parametr wywo³ania
  *  ReadMultiPolyh nie obs³uguje takiego przypadku.
  *  \param ClassName - zawiera nazwê klasy.
  *  \pre Parametr \e ClassName musi zawieraæ jeden z napisów: \n
  *      \p "ViElemePolyh", \p "ViMultiPolyh".
  *  \return wska¼nik na utworzony obiekt. W przypadku gdy przekazany napis
  *          nie jednym z wcze¶niej wymienionych, zwracana jest warto¶æ \p 0L.
  */
 ViNTreeNode * CreatePolyhedronWithDescr(const char * ClassName)
 {
   if (!strcmp("ViElemePolyh",ClassName)) {
      return new ViElemePolyh();
   } if (!strcmp("ViMultiPolyh",ClassName)) {
      return new ViMultiPolyh();
   }
   return 0L;
 }






 static
 ViMultiPolyh *ReadOnlyMultiPolyh(  
                       std::istream      &istrm, 
                       const ViPatteLibList     &PatteLibList,
                       ViScenePolyhList  &ScnPolyhList,
                       ViNTreeNode * (*fun)(const char *ClassName)
                      ) // throw (ViException_Syntax)
 { 
  ViPolyhDescr  Descr;
  int           Idx;
  ExtString     StoredText;
  ViNodeDescr   NodeDesc;
  ExtString  DClass, ClassName; // Tylko dla testu.
  int               ClNum;
  ViNTreeNode  *pPolyh;
  ViMultiPolyh     *pMuPolyh;

  ViSynxInterp::SetPatteLibList(&PatteLibList); // Inicjalizacja aby pozniej moc 
                                                // dostac sie do sceny.

  try {
   
   while ((Idx = Descr.SeekLineKeyWords(istrm,KW_NODE":",
                                        KW_MULTIPOLYH_END,0L)) >= -1) {
     switch (Idx) {
      case 1: // KW_NODE
       Descr.StoreUntilKeyWord(istrm,KW_ENDNODE,StoredText);
       NodeDesc = StoredText.c_str();
       ClNum = NodeDesc.ClassesNum();

       if (NodeDesc.GetTopClassName(ClassName)) {
          pPolyh = 0L;

          if (fun) pPolyh = (*fun)(ClassName);
          if (!pPolyh) {
	    if (!(pPolyh = CreatePolyhedronWithDescr(ClassName)))
              throw ViException(ERRNUM_POLYH__CREATE_FAILED,
                                (MSG(ERRMSG_POLYH__CREATE_FAILED),ClassName));
          }
          pPolyh->InterpretParamDescr(NodeDesc);
       } else throw ViException(ERRNUM_SYNTAX__NO_TOP_CLASS_NAME,
                    (MSG(ERRMSG_SYNTAX__NO_TOP_CLASS_NAME),NodeDesc.c_str()));
       continue;
      case 2: // KW_MULTIPOLYH_END
       pMuPolyh = ViSynxInterp::GetPolyhList().GetFirstMultiPolyh(); 
       if (!ViSynxInterp::GetPolyhList().MoveFirstMultiPolyh(ScnPolyhList))
	 throw ViException_Syntax(ERRNUM_MULTI__MOVE2LIST_FAILED,
                                  ERRMSG_MULTI__MOVE2LIST_FAILED);
       return pMuPolyh;
     }
   }
  }
  catch (Ba::Exception const &Excep) {
    ViSynxInterp::GetPolyhList().DeletePolyhList();
    throw ViException_Syntax(Excep.GetErrID(),Excep.GetErrMsg());
  }
 }


 static
 inline 
 ViKinemCtrlItem *ReadMtxID_CreateCtrlInterface( 
                             SxInterp          &Interp,
                             ViKinemCtrlSet    &CtrlSet,
                             ViNTreeNode   *pPolyh,
                             int                KeyID
			   ) 
 {
  int              MtxID;
  ViMatrix3f      *pMtx;
  ViKinemCtrlItem *pCItem;

  Interp.LookForChar(':');
  Interp.GetNum(MtxID);
  if ((MtxID != MTXID_NODE2PARENT) && (MtxID != MTXID_PATTE2ELEME) &&
                                       (MtxID != MTXID_ELEME2INDIV)) {
         throw ViException(ERRNUM_POLYH__WRONG_MTXID,
                         (MSG( ERRMSG_POLYH__WRONG_MTXID),MtxID,
			  MTXID_NODE2PARENT,MTXID_PATTE2ELEME,
                          MTXID_ELEME2INDIV));
  }
  if (!pPolyh) throw ViException(ERRNUM_INTERF__NO_POLYH_FOUND,
                                      MSG(ERRMSG_INTERF__NO_POLYH_FOUND));
  if (pPolyh->GetInheritorType() != IT_ELEMEPOLYH &&
           (MtxID == MTXID_PATTE2ELEME || MtxID == MTXID_ELEME2INDIV)) {
         throw ViException(ERRNUM_INTERF__IMPROPER_MTX,
                           (MSG(ERRMSG_INTERF__IMPROPER_MTX),MtxID,
                           pPolyh->GetInheritorType()));
  }
  switch (MtxID) {
    case MTXID_NODE2PARENT: pMtx = &pPolyh->UseMtx2ParentCoord();  break;
    case MTXID_PATTE2ELEME: 
            pMtx = &((ViElemePolyh*)pPolyh)->Mtx2ElemeCoord();  
               break;
    case MTXID_ELEME2INDIV: 
            pMtx = &((ViElemePolyh*)pPolyh)->Mtx2IndivCoord();  
            break;
  }
  if ((pCItem = CtrlSet.Add(pPolyh,*pMtx))) pCItem->SetKeyID(KeyID);

  return pCItem;
 }




 static
 inline
 void ReadSingleInterfaceItem(
                               ExtString         &InterfDescr,
                               ViKinemCtrlSet    &CtrlSet,             
                               ViScenePolyhList  &ScnPolyhList
                             )
 {
  SxInterp          Interp(InterfDescr);
  ViNodeAddress     Address;
  ViKinemCtrlItem  *pCItem;
  SXCMD_DEFINE_VAR;
  int               KeyID=-1;
  ViNTreeNode  *pPolyh = 0L;
  ExtString         Name;
  float             Value;

  try {
    SXCMD_START_LOOP2END(Interp,(KW_NODEADDRESS,'a')(KW_MTXID,'i')
			 (KW_KEYID,'k')(KW_KEYNAME,'y')(KW_COMMENT,'c')
	 (KW_MIN,'m')(KW_MAX,'x')(KW_VALUE,'v')
	 (KW_TRANSFTYPE,'f')(KW_TRANSORDER,'o')(KW_UNIT,'u')
			 (KW_COORDTYPE,'r')
         (KW_INDIVNAME,'n')(KW_TRANSF2PARENT,'t')
         (KW_CTRLINTERFACE_END,'e'))
     case 'a':
       Interp.LookForChar(':');
       Interp.GetWord(Address,".");
       if (!(pPolyh = ScnPolyhList.GetNodeUsingAddress(Address))) {
         throw ViException(ERRNUM_HIER__WRONG_ADDR,
			   (MSG(ERRMSG_HIER__WRONG_ADDR),Address.c_str()));
       }
       continue;

      case 'i':
       pCItem = ReadMtxID_CreateCtrlInterface(Interp,CtrlSet,pPolyh,KeyID);
       continue;

      case 'c':
        Interp.LookForChar(':');
        Interp.GetLine(Name);  Name.RemoveSpace();
        pCItem->SetCommentName(Name);
        continue;

      case 'y':
        Interp.LookForChar(':');
        Interp.GetLine(Name);  Name.RemoveSpace();
        pCItem->SetKeyName(Name);
        continue;

      case 'k':
       Interp.LookForChar(':');  Interp.GetNum(KeyID);
       pCItem->SetKeyID(KeyID);
       continue;

      case 'v':
       Interp.LookForChar(':');  Interp.GetNum(Value);
       pCItem->SetVal(Value);
       CtrlSet.AddToTail(pCItem); 
       SXCMD_BREAK_THIS_LOOP;

      case 'f':
       Interp.LookForChar(':');  Interp.GetWord(Name);
       pCItem->SetTransfType(Vi::String2TransformType(Name));
       continue;
       
      case 'o':
       Interp.LookForChar(':');  Interp.GetWord(Name);
       pCItem->SetTransOrder(Vi::String2TransOrder(Name));
       continue;

      case 'u':
       Interp.LookForChar(':');  Interp.GetWord(Name);
       pCItem->SetUnit(Vi::String2MetricUnit(Name));
       continue;

      case 'r':
       Interp.LookForChar(':');  Interp.GetLine(Name);
       Name.RemoveSpace();
       pCItem->SetCoordType(String2Coord3DType(Name));
       continue;

      case 'm':
       Interp.LookForChar(':');  Interp.GetNum(Value);
       pCItem->SetMin(Value);
       continue;

      case 'x':
       Interp.LookForChar(':');  Interp.GetNum(Value);
       pCItem->SetMax(Value);
       continue;

    SXCMD_END_LOOP(Interp);
    //    if (out) break;
   }
   catch (ViException &Except) {
     throw;
   }
   catch (Sx::Exception &Except) {
     throw ViException_Syntax(Except.GetErrID(),Except.GetErrMsg());
   }
 }

 



 static
 inline
 void ReadInterfaceItems(
                              std::istream      &istrm,
                              ViMultiPolyh      *pMuPolyh,             
                              ViScenePolyhList  &ScnPolyhList
                        )
 {
  ViPolyhDescr   Descr;
  ExtString      InterfDescr;
  int            Idx;

  while ((Idx = Descr.SeekLineKeyWords(istrm,KW_CTRLINTERFACEITEM_BEGIN,
                                             KW_CTRLINTERFACE_END,0L))) {
    switch (Idx) {
     case 1:
       Descr.StoreUntilKeyWord(istrm,KW_CTRLINTERFACEITEM_END,InterfDescr);
       ReadSingleInterfaceItem(InterfDescr,pMuPolyh->UseCtrlInterface(),
                               ScnPolyhList);
       continue;
     case 2: // KW_CTRLINTERFACE_END
       return;
    }
  }
 }


 static
 inline
 void ReadMultiPolyhAndInterface(  
                       std::istream      &istrm, 
                       const ViPatteLibList     &PatteLibList,
                       ViScenePolyhList  &ScnPolyhList,
                       ViNTreeNode * (*fun)(const char *ClassName)
                     ) // throw (ViException_Syntax)
 {
  ViPolyhDescr   Descr;
  ViMultiPolyh  *pMuPolyh = 0L;
  int            Idx;

  while ((Idx = Descr.SeekLineKeyWords(istrm,KW_MULTIPOLYH_BEGIN,
                                             KW_CTRLINTERFACE_BEGIN,"",0L))) {
     switch (Idx) {
       case 0: // Gdy koniec pliku.
         return;
       case 1: // KW_MULTIPOLYH_BEGIN
          pMuPolyh = ReadOnlyMultiPolyh(istrm,PatteLibList,ScnPolyhList,fun);
          break;
       case 2: // KW_CTRLINTERFACEITEM_BEGIN
         if (!pMuPolyh) return;
         ReadInterfaceItems(istrm,pMuPolyh,ScnPolyhList);
         return;
       case 3: // Gdy brak slowa.
         return;
     }
  }
 }


 static
 inline
 void ReadMultiPolyh(  std::istream      &istrm, 
                       const ViScene     &Scn,
                       ViScenePolyhList  &ScnPolyhList,
                       ViNTreeNode * (*fun)(const char *ClassName)
		     ) // throw (ViException_Syntax)
 { 
   ViSynxInterp::SetScene(Scn);
   ReadMultiPolyhAndInterface(istrm,Scn.GetList_PatteLibs(),ScnPolyhList,fun);
 }






 void ReadMultiPolyh(  std::istream  &istrm, 
                       ViScene &Scn,
                       Vi::MultiPolyhListType  ListType, 
                       ViNTreeNode * (*fun)(const char *ClassName)
                    ) // throw (ViException_Syntax)
 { 
  ViScenePolyhList &ScnPolyhList = (ListType == Vi::LT_Norm ?
                     Scn.UseList_NormMultiPolyh() : Scn.UseList_SpecMultiPolyh());
  ReadMultiPolyh(istrm,Scn,ScnPolyhList,fun);
 }


 static
 void ReadMultiPolyh( const char               *FileName, 
                      const ViPatteLibList     &PatteLibList, 
                      ViScenePolyhList  &ScnPolyhList,
                      ViNTreeNode * (*fun)(const char *ClassName)
		     ) // throw (ViException, ViException_File, ViException_Syntax)
 {
   std::ifstream  istrm(FileName);

   if (istrm.fail()) 
     throw ViException_File(ERRNUM_FILE__OPEN2READ_FAILED,
                       (MSG(ERRMSG_FILE__OPEN2READ_FAILED),FileName));
   ReadMultiPolyhAndInterface(istrm,PatteLibList,ScnPolyhList,fun); 
 }



 static
 void ReadMultiPolyh( const char        *FileName, 
                      const ViScene     &Scn, 
                      ViScenePolyhList  &ScnPolyhList,
                      ViNTreeNode * (*fun)(const char *ClassName)
		    ) // throw (ViException, ViException_File, ViException_Syntax)
 {
   std::ifstream  istrm(FileName);
   if (istrm.fail()) 
     throw ViException_File(ERRNUM_FILE__OPEN2READ_FAILED,
                       (MSG(ERRMSG_FILE__OPEN2READ_FAILED),FileName));
   ReadMultiPolyh(istrm,Scn,ScnPolyhList,fun); 
 }





 void ReadMultiPolyh( const char *FileName, 
                      ViScene &Scn, 
                      Vi::MultiPolyhListType  ListType,
                      ViNTreeNode * (*fun)(const char *ClassName)
		    ) // throw (ViException, ViException_File, ViException_Syntax)
 {
   std::ifstream  istrm(FileName);

   if (istrm.fail()) 
     throw ViException_File(ERRNUM_FILE__OPEN2READ_FAILED,
                       (MSG(ERRMSG_FILE__OPEN2READ_FAILED),FileName));
   ReadMultiPolyh(istrm,Scn,ListType,fun); 
 }







 int ReadMultiPolyh(
                   const char  *      FileName, 
                   ViScene     &      Scn, 
                   Vi::MultiPolyhListType  ListType,
                   ViException &      Excep,
                   ViNTreeNode * (*ObjectCreator)(const char *ClassName)
                  )
 {
  try {
    Vi::ReadMultiPolyh(FileName,Scn,ListType,ObjectCreator);

  } catch (ViException_File const &Ex) {
     Excep = Ex;
     return -1;
  } catch (ViException const &Ex) {
     Excep = Ex;
     return -2;
  }
  return 0;
 }








 int ReadMultiPolyh(
                 const char   *            FileName, 
                 const ViPatteLibList&     PatteLibList,
                 ViMultiPolyh **           ppMultiPolyh, 
                 ViException &             Excep,
                 ViNTreeNode * (*ObjectCreator)(const char *ClassName)
               )
 {
  ViScenePolyhList  ScnPolyhList;
  try {
    Vi::ReadMultiPolyh(FileName,PatteLibList,ScnPolyhList,ObjectCreator);
  } catch (ViException_File const &Ex) {
     Excep = Ex;
     return -1;
  } catch (ViException const &Ex) {
     Excep = Ex;
     return -2;
  }
  *ppMultiPolyh = ScnPolyhList.GetFirstMultiPolyh();
  if (*ppMultiPolyh) 
        (*ppMultiPolyh)->PolyhHierListItemField().RemoveFromList();
  return 0;
 }


 int ReadMultiPolyh(
                 const char   *     FileName, 
                 const ViScene&     Scn,
                 ViMultiPolyh **    ppMultiPolyh, 
                 ViException &      Excep,
                 ViNTreeNode * (*ObjectCreator)(const char *ClassName)
               )
 {
  ViScenePolyhList  ScnPolyhList;
  ViSynxInterp::SetScene(Scn);

  return Vi::ReadMultiPolyh(FileName,Scn.GetList_PatteLibs(),
                                      ppMultiPolyh,Excep,ObjectCreator);
 }

}
