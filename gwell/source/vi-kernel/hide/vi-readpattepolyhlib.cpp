/*------------------------------------------------------------
 * File: readfig.cpp
 * Purpose: Odczyt figur elementarnych w wxICARS
 * Author:  Bogdan Kreczmer
 * Created: Maj 1995
 * Updated:
 * Copyright: (c) 1995, Bogdan Kreczmer
 */


#ifdef __GNUG__
#pragma implementation
#endif

#include <iostream>
#include <stdio.h>
#include <ctype.h>

#include <stdarg.h>
#include <string.h>
#include "syntax-new.hh"
#include "extstring.hh"
#include "getmsg.h"
#include "vipattepolyh.hh"
#include "vipattepolyhlib.hh"
#include "viedge.hh"
#include "viface.hh"
#include "system.e"
#include "readfig.e"
#include "keywords-figurefile.h"
#include "debug.h"

//#include "wxgetmsg.h"
#include "colorsid.h"



#define  KW_FIGURES_LIBRARY          "FiguresLibrary"
#define  KW_SPECIAL_FIGURES          "SpecialFigures"
#define  KW_FIGURE                   "Figure"
#define  KW_NODE_NUMBER              "NodeNumber"
#define  KW_EDGE_NUMBER              "EdgeNumber"
#define  KW_FACE_NUMBER              "FaceNumber"
#define  KW_NODES                    "Nodes"
#define  KW_EDGES                    "Edges"
#define  KW_FACES                    "Faces"
#define  KW_END_FIGURE               "EndFigure"
#define  KW_END_LIBRARY              "EndLibrary"

#define  EMPTY_NO           -1
#define  MAX_FACE_EDGES     20
#define  MSG_FILE   "common.msg"
#define  MSG_FILE_NAME        "syntax.msg"
#define  MAXCOLORNAME        80

using namespace std;

class EdgeData: public ListItem<EdgeData> {
   public:
     unsigned int _First, _Last, _Color;
     void SetColorID(unsigned int Color) { _Color = Color; }
     EdgeData(unsigned int Frt, unsigned int Lst): 
           _First(Frt), _Last(Lst), _Color(0) {}
     ~EdgeData() {}
};

class List4EdgeData: public List<EdgeData> {
   public:
    EdgeData *Add(unsigned int Frt, unsigned int Lst) 
            { return AddToTail(new EdgeData(Frt,Lst)); }
    ~List4EdgeData() {}
};



class NodeData: public ListItem<NodeData>, public Vector3f  {
  public:
     NodeData(float xx, float yy, float zz): Vector3f(xx,yy,zz) {}
     ~NodeData() {}
};

class List4NodeData: public List<NodeData> {
  public:
    NodeData *Add(float xx, float yy, float zz) 
            { return AddToTail(new NodeData(xx,yy,zz)); }
    ~List4NodeData() {}
};


class FaceData: public ListItem<FaceData>, public ViFace {
  public:
    FaceData(ViPattePolyh &Owner): ViFace(Owner) {}
    ~FaceData() {}
};

class List4FaceData: public List<FaceData> {
  public:
    FaceData *Add(ViPattePolyh &Fig) { return AddToTail(new FaceData(Fig)); }
    ~List4FaceData() {}
};


#define SYNTAX_INTERPRETER_CLASS   FigFileInterpreter

DEFINE_INTERPRETER_CLASS {

   ExtString        _SysVersion;
   ViPattePolyh    *_pFig;
 ViPattePolyhLib   *_pBFSet;
   bool             _LookForColon;
  public:

   void LookForColon_YES() { _LookForColon = true; }
   void LookForColon_NO()   { _LookForColon = false; }
   bool MustLookForColon() const { return _LookForColon; }

   int StartReading();
   int ReadSystemVersion();
   //   int ReadFigTypeName();

   //   int AfterFindingKeyword(char const *);

   bool ReadSingleFace( unsigned int  &FaceNodeNo, 
                        unsigned int *pTab,
                        unsigned int  TabSize
                      );

   DECLARE_SYNTAX_METHOD(ReadViPattePolyh)
   DECLARE_SYNTAX_METHOD(ReadSpecialFigures)
   DECLARE_SYNTAX_METHOD(ReadViPattePolyhData)
   DECLARE_SYNTAX_METHOD(ReadSFigData)
   DECLARE_SYNTAX_METHOD(ReadNumber) // Nodes, Edges, Nodes
   DECLARE_SYNTAX_METHOD(ReadNodes)
   DECLARE_SYNTAX_METHOD(ReadEdges)
   DECLARE_SYNTAX_METHOD(ReadFaces)
   DECLARE_SYNTAX_METHOD(InitPolyhData)
   DECLARE_SYNTAX_METHOD(ReadEndViPattePolyh)
   DECLARE_SYNTAX_METHOD(Quit)


   FigFileInterpreter(ViPattePolyhLib *pBFSet): 
              _pFig(0L),  _pBFSet(pBFSet),  _LookForColon(false) {}
   virtual ~FigFileInterpreter() { }
};




BEGIN_SYNTAX_METHOD(ReadSystemVersion)
  LOOKFORCOLON;
  QUESTION(LookForString(_SysVersion));   // Powinno byc tylko do konca linii
END_SYNTAX_METHOD


int FigFileInterpreter::StartReading()
{
  BEGIN_SYNTAX_LOOP
    SYNTAX_PAIR(KW_VERSION,ReadSystemVersion)
    SYNTAX_PAIR(KW_FIGURES_LIBRARY,ReadViPattePolyh)
    SYNTAX_PAIR(KW_END_LIBRARY,Quit) 
  END_SYNTAX_LOOP
  return _errno;
}



BEGIN_SYNTAX_METHOD(Quit)
  BreakGlobalLoop();
END_SYNTAX_METHOD


BEGIN_SYNTAX_METHOD(InitPolyhData)
  _pFig->InitFacesData();
  BreakLocalLoop();
END_SYNTAX_METHOD


BEGIN_SYNTAX_METHOD(ReadViPattePolyh)
  QUESTION(LookForChar(':'));
  string  LibName;
  QUESTION(GetWord(LibName));
  _pBFSet->SetLibName(LibName.c_str());
  FileCanNotEnd();
  BEGIN_SYNTAX_LOOP
    SYNTAX_PAIR(KW_SPECIAL_FIGURES,ReadSpecialFigures)
    SYNTAX_PAIR("AleMuzyka",Quit)
    SYNTAX_PAIR(KW_FIGURE,ReadViPattePolyhData)
    SYNTAX_PAIR(KW_END_LIBRARY,Quit)
  END_SYNTAX_LOOP
END_SYNTAX_METHOD



BEGIN_SYNTAX_METHOD(ReadSpecialFigures)
  BEGIN_SYNTAX_LOOP
    SYNTAX_PAIR(KW_FIGURE,ReadSFigData)
    SYNTAX_PAIR(KW_END_LIBRARY,Quit)
  END_SYNTAX_LOOP
END_SYNTAX_METHOD


BEGIN_SYNTAX_METHOD(ReadNumber)
  int No;
  QUESTION(LookForChar('='));
  QUESTION(LookForNumber(&No));
  LOOKFORSEMICOLON;
END_SYNTAX_METHOD

  //------------------------------------------------------------------------
  // Oczekuje slowa kluczowego "ViPattePolyh"  "EndViPattePolyhLibrary"
BEGIN_SYNTAX_METHOD(ReadViPattePolyhData)
  if (!(_pFig = new ViPattePolyh)) {
    cerr << "!!! ReadViPattePolyhData:" << endl;
    cerr << "!!!  Memovery allocation of a new pattern figure failed." << endl;
    return -1;
  }
  char FigName[500];
  QUESTION(LookForWord(FigName,499))
  _pFig->SetName(FigName);
//  cerr << "!!! Name: " << FigName << endl;

  BEGIN_SYNTAX_LOOP
    SYNTAX_PAIR(KW_NODE_NUMBER,ReadNumber)
    SYNTAX_PAIR(KW_EDGE_NUMBER,ReadNumber)
    SYNTAX_PAIR(KW_FACE_NUMBER,ReadNumber)
    SYNTAX_PAIR(KW_NODES,ReadNodes)
    SYNTAX_PAIRNULL(KW_END_FIGURE)
  END_SYNTAX_LOOP
  _pBFSet->AddNormPattePolyh(_pFig);
  _pFig = 0L;
END_SYNTAX_METHOD





  //------------------------------------------------------------------------
  // Oczekuje slowa kluczowego "ViPattePolyh"  "EndViPattePolyhLibrary"
BEGIN_SYNTAX_METHOD(ReadSFigData)
  if (!(_pFig = new ViPattePolyh)) {
    cerr << "!!! ReadSFigData:" << endl;
    cerr << "!!!  Memovery allocation of a new pattern figure failed." << endl;
    return -1;
  }
  char FigName[500];
  QUESTION(LookForWord(FigName,499))
  _pFig->SetName(FigName);

  BEGIN_SYNTAX_LOOP
    SYNTAX_PAIR(KW_NODE_NUMBER,ReadNumber)
    SYNTAX_PAIR(KW_EDGE_NUMBER,ReadNumber)
    SYNTAX_PAIR(KW_FACE_NUMBER,ReadNumber)
    SYNTAX_PAIR(KW_NODES,ReadNodes)
    SYNTAX_PAIRNULL(KW_END_FIGURE)
  END_SYNTAX_LOOP
  _pBFSet->AddSpecPattePolyh(_pFig);
  _pFig = 0L;
END_SYNTAX_METHOD




BEGIN_SYNTAX_METHOD(ReadEdges)
  int  FrtEdge, LstEdge;
  unsigned int No = 0;
  unsigned int idx;
  List4EdgeData  Lst;  
  EdgeData  *pEdge;

  QUESTION(LookForChar(':'));
  SetParamEnvironment('(',',',')');
  while (IsCharNext('(')) {
    QUESTION(twoParam(&FrtEdge,&LstEdge))
    No++;
    if (FrtEdge > (int)_pFig->GetVtxNo()) {
      return SetErrMsgForFile(ERR_FIRST_VTX_NUM_ECEEDS,
        " ReadEdges:\n"
        "  The first vertex number of the edge no. ##1,\n"
        "  exceeds the total number of vertex (##2).",
        "%i%i",No,_pFig->GetVtxNo());
    }
    if (LstEdge > (int)_pFig->GetVtxNo()) {
      return SetErrMsgForFile(ERR_SECOND_VTX_NUM_ECEEDS,
        " ReadEdges:\n"
        "  The second vertex number of the edge no. ##1,\n"
        "  exceeds the total number of vertex (##2).",
        "%i%i",No,_pFig->GetVtxNo());
    }

     // Sprawdzanie czy ta sama krawedz juz nie wystepowala.
    idx = 0;
    for (List<EdgeData>::VariaIterator Iter2 = Lst.Begin();  Iter2;  ++Iter2, ++idx) {
      if (((int)(Iter2->_First) == FrtEdge) && 
          ((int)(Iter2->_Last) == LstEdge)) {
        SetErrMsgForFile(ERR_DOUBLE_EDGES,
          "In the figure `##1' the edges ##2 and ##3 are the same.  Edge = (##4,##5)",
       	  "%s%i%i%i%i",_pFig->GetName(),(int)(idx+1),(int)(No+1),
                                    FrtEdge,LstEdge);
        throw ERR_DOUBLE_EDGES;
      }
    }

    if (!(pEdge = Lst.Add(FrtEdge,LstEdge))) {
      return SetErrMsgForFile(ERR_NO_MEMORY_FOR_EDGEFIG,
        " ReadEdges:\n"
        "  Memory allocation of a new figure edge failed.\n"
        "  Error appeared while an edge no. %i was being created.",
        "%i%i",No,_pFig->GetVtxNo());
    }



    char        ColorName[MAXCOLORNAME+1];

    if (IsCharNext('=')) {
      QUESTION(LookForChar('='));
      QUESTION(LookForWord(ColorName,MAXCOLORNAME));
      for (char *s = ColorName; *s; s++) *s = toupper(*s);
      if (!strcmp(ColorName,"GREEN")) pEdge->SetColorID(ID_GREEN);
      else if (!strcmp(ColorName,"RED")) pEdge->SetColorID(ID_RED);
      else if (!strcmp(ColorName,"BLUE")) pEdge->SetColorID(ID_BLUE);
      else if (!strcmp(ColorName,"BLACK")) pEdge->SetColorID(ID_BLACK);
      else if (!strcmp(ColorName,"WHITE")) pEdge->SetColorID(ID_WHITE);
      else return SetErrMsgForFile(ERR_COLOR_NAME,
                     " The name of color '##1' is unknown.\n"
                     " acceptable names are: gren, red, blue, black, white",
                     "%s",ColorName);
    }
  }
  if (!_pFig->CreateEdgesTable(No)) { 
      return SetErrMsgForFile(ERR_NO_MEMORY_FOR_EDGEFIG,
        " ReadEdges:\n"
        "  Memory allocation of a new figure edge failed.\n"
        "  Error appeared while an edges table was being created.\n"
        "  for a figure '%s'",
        "%s",_pFig->GetName());
  } 
  No = 0;
  for (List<EdgeData>::VariaIterator Iter = Lst.Begin();  Iter;  ++Iter, No++) {
    _pFig->SetEdgeVtx(No,Iter->_First-1,Iter->_Last-1);
    _pFig->SetEdgeColorID(No,Iter->_Color);
  }  
END_SYNTAX_METHOD




#define MAX_FACENODES  100
/*==========================================================================
 * Zwraca false, gdy nie powiedzie siê wczytanie nowej ¶cianki.
 */
bool FigFileInterpreter::ReadSingleFace( unsigned int  &FaceNodeNo, 
                                         unsigned int *pTab,
                                         unsigned int  TabSize
                                       )
{
  int Val;
  int err = 0;

  FaceNodeNo = 0;
  if (IsNotCharNext('(')) return false;
  QUESTION(LookForChar('('));
  if (IsCharNext(')')) {   // Gdy ¶cianka pusta.
     QUESTION(LookForChar(')'));
     return true;
  }
  do {
    QUESTION(LookForNumber(&Val));
    if (FaceNodeNo >= TabSize) {
      SetErrMsgForFile(ERR_FACE_VTX_TOO_MUCH,
           "***  ReadSingleFace\n"
           "***   The vertex number of a face exceedes the limit (##1)",
           "%i",TabSize);
      return false;
    }
    if (Val <= 0) {
      SetErrMsgForFile(ERR_FACE_VERTEX_NONPOS,
           "In the figure `##1' for a face ##2 a cardinal number of a vertex\n"
		       "isn't a positive number.",
           "%i%i",_pFig->GetName(),FaceNodeNo+1);
    }
    pTab[FaceNodeNo++] = (unsigned int)(Val-1);
    if (IsNotCharNext(',')) break;
  } while (!(err = LookForChar(',')));

  if (err) return false;

  QUESTION(LookForChar(')'));
  return true;
}


void ShowFace(ViFace const &F)
{
  char *sep = "";
  cout << "    F: (";
  for (unsigned int idx = 0; idx < F.GetVtxNo(); idx++) {
    cout << sep << F.GetVtxIdx(idx);
    sep = ",";
  }
  cout << ")" << endl;
}


BEGIN_SYNTAX_METHOD(ReadFaces)
 unsigned int   No = 0;
 List4FaceData  Lst;
 FaceData      *pFData;
 unsigned int   VtxTab[MAX_FACENODES+1];
 unsigned int  &VtxNo = VtxTab[0];

 QUESTION(LookForChar(':'));
 SetParamEnvironment('(',',',')');
 while (IsCharNext('(')) {
   if (!ReadSingleFace(VtxNo,VtxTab+1,MAX_FACENODES)) return -1;
   pFData = Lst.Add(*_pFig);
   if (pFData->CreateAndInitNodeIndexTable(VtxTab)) {
      getSyntaxErrMsg(SyntaxError=ERR_NO_MEMORY_FOR_FACEVTX,_syntaxErrMsg,""); 
      return ERR_NO_MEMORY_FOR_FACEVTX;    
   }
   No++;
 }
 QUESTION(LookForChar(';'));
 _pFig->CreateFacesTab(No);
 List<FaceData>::VariaIterator Iter = Lst.Begin(); 
 for (unsigned int i = 0; i < No; i++, ++Iter) {
   *_pFig->UseFace(i) = *Iter;
 }
END_SYNTAX_METHOD





BEGIN_SYNTAX_METHOD(ReadNodes)
  float           xx, yy, zz;
  List4NodeData   Lst;
  unsigned int    No = 0;

  LOOKFORCOLON;
  SetParamEnvironment('(',',',')');
  while (IsCharNext('(')) {
    QUESTION(threeParam(&xx,&yy,&zz))
    No++;
    if (!Lst.Add(xx,yy,zz)) {
      cerr << "!!! ReadNodes:" << endl;
      cerr << "!!!  Memory allocation of a new pattern figure vertax failed."
           << endl;
      cerr << "!!!  Error appeared while a vertex no. " << No 
           << " was being created." << endl;
      return -1;
    }
  }
  _pFig->CreateVertexTable(No);
  No = 0;
  for (List<NodeData>::VariaIterator Iter = Lst.Begin();
       Iter;  Iter++, No++) {
    _pFig->SetVtx(No,*Iter);
  }
  LOOKFORSEMICOLON;
  BEGIN_SYNTAX_LOOP
    SYNTAX_PAIR(KW_EDGES,ReadEdges)
    SYNTAX_PAIR(KW_FACES,ReadFaces)
    SYNTAX_PAIR(KW_END_FIGURE,ReadEndViPattePolyh)
  END_SYNTAX_LOOP
  BreakLocalLoop();
END_SYNTAX_METHOD






BEGIN_SYNTAX_METHOD(ReadEndViPattePolyh)
 int EdgNo = _pFig->GetEdgesNo();

 if (!EdgNo) return 0;

 ViEdge        *Edges   = _pFig->ModifyEdge(0);
 ViFace const  *Face;
 unsigned int   *Vtx0, *VtxN;
 unsigned int   FNo, ind;


 for (; EdgNo > 0; EdgNo--, Edges++) {

     //------------------------------------------------------------------
     // W ponizszej petli szukamy czy krawedz nalezy do danej scianki.
     // Jest to niezbedne aby ustalic po ktorej stronie krawedz ta jest 
     //  wzgledem tej scianki.
     //
   for (Face=_pFig->GetFacesTab(), FNo=0; 
           FNo < _pFig->GetFacesNo(); FNo++, ++Face) {

     VtxN = Face->GetFaceVtxTable();
     Vtx0 = VtxN + Face->GetVtxNo() - 1;

       //-----------------------------------------------------------------
       // Przegladane sa wszystkie krawedzie wierzcholki danej scianki,
       // aby odnalezc odpowiednie krawedzie i ustalic ich wzgledne 
       // polozenie 
     for( ind=0; 
          ind < Face->GetVtxNo(); ind++, Vtx0=VtxN, 
          VtxN++) {

         //---------------------------------------------------------------
         //  Czy jest po prawej stronie
       if (Edges->GetFirstVtxIdx() == *Vtx0 && 
           Edges->GetSecondVtxIdx() == *VtxN) {

          if (Edges->IsRightFace()) {
             SetErrMsgForFile(ERR_NODE_IN_MORE_FACES,
               "In the figure `##1' the edge no. ##2 is on the right side"
			      " of two faces: ##3, ##4",
                  "%s%i%i%i",_pFig->GetName(),
                  int(_pFig->GetEdgesNo()-EdgNo+1),
                  int(Edges->GetRightFaceIdx()+1),int(FNo+1));
             throw ERR_NODE_IN_MORE_FACES;
         }
         Edges->SetRightFaceIdx(FNo); 
         continue;
         // break; Zablokowane, aby sprawdzic czy sa inne jeszcze scianki (blad)
       }
         //---------------------------------------------------------------
         //  Czy jest po lewej stronie
       if (Edges->GetSecondVtxIdx() == *Vtx0 && 
           Edges->GetFirstVtxIdx() == *VtxN) {
	 //         cerr << "       -- Found Left"  << endl;
         if (Edges->IsLeftFace()) {
             SetErrMsgForFile(ERR_NODE_IN_MORE_FACES,
               "In the figure `##1' the edge no. ##2 is on the left side"
                " of two faces: ##3, ##4",
                "%s%i%i%i",_pFig->GetName(),
                int(_pFig->GetEdgesNo()-EdgNo+1),
                int(Edges->GetLeftFaceIdx()+1),int(FNo+1),_pFig->GetName());
           throw ERR_NODE_IN_MORE_FACES;
         }
         Edges->SetLeftFaceIdx(FNo); 
         continue; 
         // break; Zablokowane, aby sprawdzic czy sa inne jeszcze scianki
        }
     }
   }
 }
 _pFig->InitFacesData();
 BreakLocalLoop();
 FileCanEnd();  

END_SYNTAX_METHOD





int ReadPatternPolyhedronLib(ViPattePolyhLib   &BFSet,
                        char  const            *FileName,
                        ExtString              &ErrMsg
                      )
{
 int err = 0;
 FigFileInterpreter  FF(&BFSet);
 try {
   err =  FF.Start(FileName,ErrMsg);
 }
 catch (ViException const &Ex) {
   cerr << "Blad!!!" << endl;
   cerr << "  Error:  " <<  Ex.GetErrID() << endl;
   cerr << "  ErrAux: " <<  Ex.GetErrAuxID() << endl;
   cerr << "  Msg:    " <<  Ex.GetErrMsg() << endl;
   return -1;
 }
 catch (...) {
   cerr << "Blad!!!" << endl;
   cerr << FF.GetErrMsg() << endl;
   cerr << endl;
   if (!err) return -1;
 }
 return err;
}


