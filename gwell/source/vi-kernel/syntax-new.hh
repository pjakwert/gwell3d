/*
 * File:	syntax.cpp
 * Purpose:     Analizator syntaktyczny 
 * Version:     1.0.3
 * Author:      Bogdan Kreczmer
 * Created:	Kwiecien 1995
 * Updated:     2001
 * Copyright:	(c) 2001, Bogdan Kreczmer
 */


#ifndef SYNTAX_NEW_H
#define SYNTAX_NEW_H

#ifdef __GNUG__
#pragma interface
#endif

#include <cstdio>
#include <string>

#include <stdarg.h>

#include "syntax-new.e"
#include "extstring.hh"

using namespace std;

#define    AUXDATA        void*
#define    NOTFINISHED      -1

typedef int (*LexCharFun)(int);
//typedef int (*LexUnitFun)(int *, AUXDATA, FileSyntaxReader &);
typedef int (*storeFunction)(char);


#define  QUESTION(x)  if ((err = x) != OK) return err;




#define OK            0
#define BREAK_LOOP    1
#define CONTINUE_LOOP 0

#define  NULL_CHAR   ' '
#define  MAX_SEPARCHARS   29




#define BEGIN_SYNTAX_SEQUENCE  if ((_errno = sequenceAnalis(
#define END_SYNTAX_SEQUENCE    NULL))) return _errno;
#define BEGIN_SYNTAX_LOOP  if ((_errno = syntaxAnalis(
#define END_SYNTAX_LOOP    NULL))) return _errno;
#define BREAK_SYNTAX_LOOP  BreakLocalLoop();



#define SYNTAX_INTERPRETER_CLASS  YouMustHereGetClassName
#define DEFINE_INTERPRETER_CLASS\
  class SYNTAX_INTERPRETER_CLASS:\
      public FileSyntaxReader<SYNTAX_INTERPRETER_CLASS>


#define SYNTAX_PAIRNULL(x) x,(LexicalFunType)0L,

#define DECLARE_SYNTAX_METHOD(Method) int Method();


#define SYNTAX_METHOD(x) int SYNTAX_INTERPRETER_CLASS::x()
#define BEGIN_SYNTAX_METHOD(x) int SYNTAX_INTERPRETER_CLASS::x() { int err=0;
#define END_SYNTAX_METHOD return err; }
#define SYNTAX_PAIR(x,y) x,&SYNTAX_INTERPRETER_CLASS::y,
#define LOOKFORCOLON   if ((_errno = LookForChar(':'))) return _errno;
#define LOOKFORSEMICOLON   if ((_errno = LookForChar(';'))) return _errno;




class InterpreterKern {
 protected:
   int  getWordGathering( char *lWord, int MaxLn, FILE *IFile );
   int  getString(char* Word, int Max, bool NL_IsSpace=true );
   int  passComments(void);
   int  openComment(int *);
   int  omitComment(int);

   int (InterpreterKern::*iswordsign)(int);
   char    PR_Open;
   char    PR_Close;
   char    PR_Separater;
   char const *C_Open;
   char const *C_Close;
   char    C_Line[3];
   int     SyntaxError;
   char    SeparChars[MAX_SEPARCHARS+1];
   char const *AddValidChars;
   fpos_t  FilePos;
   bool    _BreakLocalLoop;
   bool    _BreakGlobalLoop;
   bool    _FileCanEnd;
   AUXDATA _pStoreRecord;   // Ma znaczenie pomocnicze, aby nie 
                                 // przekazywac parametrow.

     //---------------------------------------------------------------------
     // Nazwa pliku z komunikatami o bledach.
     //
   char const  *FileName;

   ExtString  _userErrMsg;
   ExtString  _syntaxErrMsg;

 public:
   void        *AuxParam;
   FILE        *IFile;

   int          lineNo;
   int          _errno;


   InterpreterKern();
   virtual ~InterpreterKern() {}

   int  GetLineNo() const { return lineNo; }
   char const *GetFileName() const { return FileName; }
   void SetUserErrMsg(char const *Msg) { _userErrMsg = Msg;  }

   void SetErrMsg(char const *Msg);
   int  SetErrMsgForFile( int         ErrNo, 
                          char const *Msg, 
                          char const *Format = 0L,  
                          ...
                        ); 
   char const *GetUserErrMsg() const {return _userErrMsg;}

   char const *GetErrMsg() const { return _syntaxErrMsg(); }
   int  GetError() const { return SyntaxError; }
   bool IsBreakLocalLoop() const { return _BreakLocalLoop; }
   bool IsBreakGlobalLoop() const { return _BreakGlobalLoop; }
       
   //   char const *ProduceErrMsgForFile(int ErrNo, char const *Msg, 
   //				    char const *format = "", ... );

     //----------------------------------------------------------------------
     // Tworzy komunikat o zaistnialym bledzie i emituje wyjatek
     // typu 'int' o wartosci ErrNo.
     // Wskaznik na utworzony komunikat jest podstawiany do syntaxErrMsg,
     // zas numer bledu do _errno.
     //
   void  EmitError_Msg(int  ErrNo, char const *Msg, 
				  char const *format = "", ... );

     //----------------------------------------------------------------------
     // Robi to samo co metoda powyzej i dodatkowo dopisuje na poczatku
     // informacje dla jakiego pliku i w linii o jakim numerze zdarzyl sie
     // dany blad.
     //
   void  EmitErrorForFile_Msg(int  ErrNo, char const *Msg, 
				  char const *format = "", ... );

   AUXDATA GetStoreRecord() { return _pStoreRecord; }

   void SetLineComment(char const *str);
   void SetBlockComment(char const *OpDelim, char const *ClDelim);


   void BreakLocalLoop()     { _BreakLocalLoop = true; }
   void ContinueLocalLoop()  { _BreakLocalLoop = false; }
  void BreakGlobalLoop()    { _BreakGlobalLoop = true; }
   void ContinueGlobalLoop() { _BreakGlobalLoop = false; }

   bool CanFileEnd() const { return _FileCanEnd; }
   void FileCanEnd() { _FileCanEnd = true; }
   void FileMustBeContinued() { _FileCanEnd = false; }
   void FileCanNotEnd() { FileMustBeContinued(); }

   void SetParamEnvironment(char Op, char Sp, char Cl)
                        { PR_Open = Op;  PR_Separater = Sp;  PR_Close = Cl; }
   void SetFileMsg( char *FName) { FileName = FName; }
   char const *GetFileMsg() { return FileName; }

   int  SetFilePos() { return fsetpos(IFile,&FilePos);}
   void SetAdditionalValCh(char const *str) { AddValidChars = str;}
   void Close() { fclose(IFile);}


   char *ReadCharsToNL(char *Line, int Size);
   char *ReadString(char *Line, int Size);
   int  Ungetchar(char c);

   void SetArgSeparater(char ch) { PR_Separater = ch;}
   void RemoveComment(char *Line) {}
   int  getWord( char *lWord, int MaxLn  );
   int  GetWord( string & );
   void SetSeparaters(char *s);

   void ResetAnalis(void);
   int  isWordSign( int ch );

 //====================================================================
 // String of any characters except separators defined by SetSeparators
 //     default: 

   int  LookForString( char *Str, int lnMax, bool NL_IsSpace=true );
   int  LookForString( ExtString &Str );
   int  LookForStringToNL( ExtString &Str );
   int  LookForStringAfterChar( char Keychar, char *Str, int Size );
   int  LookForChar( char  ch );
   int  LookForWord( char *Word, int lnMax );
   int  LookForNumber( unsigned int*  intNo );
   int  LookForNumber( int*  intNo );
   int  LookForNumber( unsigned long* intNo );
   int  LookForNumber( long* intNo );
   int  LookForNumber( float *no );
   int  LookForNumber( double *no );

   int  LookForKeyword( char const *Word );
   int  LookForKeywordChar( char const *Keyword, char Keychar );
   int  LookForSingleWord( char*  keyword, storeFunction storeF );

   int  LookForParString( char *Word, int lnMax );
   int  LookForAnyChar( char *CharsSet, char *FoundChar );

   int  singleSymbol( char* Symbol, int lnMax );
   int  singleParam( char* Word, int Max );
   int  singleParam( double *number );
   int  singleParam( float* );
   int  singleParam( int* );
   int  singleParam( short int* );

   int  twoParam( char* Word1, int Max1, char* Word2, int Max2);
   int  twoParam( double *number1, double *number2  );
   int  twoParam( float *, float * );
   int  twoParam( int *,  int *);
   int  threeParam( double *, double *, double *);
   int  threeParam( int *, int *, int *);
   int  threeParam( float *, float *, float *);
   int  fiveParam( float *, float *, float *, float *, float *);


     //---------------------------------------------------------------------
     // Sprawdza czy nastêpnym znakiem jest Ch (omija znaki bia³e i 
     // komentarze). Je¿eli tak, to zwraca true. W przeciwnym przypadku
     // false. Napotkany znak jest zwrocony.
     //
   bool IsCharNext(char const Ch); 
   int  IsNotCharNext(char const Ch); 
   int  IsNotSeparaterNext() { return IsNotCharNext(PR_Separater);}

   virtual int BeforReading() { return 0; }
   virtual int StartReading() { return 0; }
   virtual int AfterReading() { return 0; }
   virtual int AfterFindingKeyword(char const *FoundKeyword) { return 0; }

   //   int  Start(char const *FileName, char const ** pErrMsg, AUXDATA AD=0L);
   int  Start(char const *FileName, ExtString &ErrMsg, AUXDATA AD=0L);
   int  startAnalis();
};



int getSyntaxErrMsg( int no, ExtString &ErrMsg, char const *format, ... );

template <class ClassName>
class LexPairTemp {
  public:
   typedef int (ClassName::*LexFunType)(void);
   char const *lexWord;
   LexFunType  lexFun;
};

#define  MAX_WORDS_LINE        1024
#define  SIZE_LEXMAX            200
#define  SIZE_LINELENGTH        140
#define  LINE_LENGHT             77
#define  LINE_HEADER            "  "


template <class ClassXName>
class  FileSyntaxReader :  public InterpreterKern {
        int  snxAnalis( LexPairTemp<ClassXName>  lexTab[],  int lexMax );
        int  seqAnalis( LexPairTemp<ClassXName>  lexTab[],  int lexMax );

        /* New object oriented construction */

       public:
        typedef typename LexPairTemp<ClassXName>::LexFunType LexicalFunType;

        int  syntaxAnalis(char const *KeyWord, ...);
        int  sequenceAnalis(char const *KeyWord, ...);

  //  int  LookForWordAfterChar( char Keychar, char *Str, int Size );

        FileSyntaxReader() {};
        virtual ~FileSyntaxReader() {};
    };



template <class ClassXName>
static void CopyKeywords( LexPairTemp<ClassXName> lexTab[], 
                          int                     lexMax, 
                          char*                   WordsLine
                        )
{
 int  inx,TmpLen=0;
 char const *Wd;

 strcpy(WordsLine,LINE_HEADER);
 for (inx=0; inx < lexMax; inx++) {
   Wd = lexTab[inx].lexWord;
   if (*Wd == '\0')  continue;
   if (strlen(WordsLine)+strlen(Wd)-TmpLen > MAX_WORDS_LINE - 8)
        { strcat(WordsLine,"...\n");  return; }
   if (strlen(WordsLine)+strlen(Wd)-TmpLen > LINE_LENGHT-10)
     { strcat(WordsLine,"\n        ");  TmpLen = strlen(WordsLine); }
   strcat(WordsLine,Wd);
   if (inx == lexMax-1) strcat(WordsLine,""); else strcat(WordsLine,", ");
 }
}




template <class ClassXName>
int  FileSyntaxReader<ClassXName>::sequenceAnalis(char const *KeyWord, ...)
{
 LexPairTemp<ClassXName>   lexicalTab[SIZE_LEXMAX];
 int       ix;
 va_list   lxParam;
 va_start(lxParam,KeyWord);

 if (!(lexicalTab[ix = 0].lexWord = KeyWord)) return 0;
 do {
  lexicalTab[ix].lexFun = 
                va_arg(lxParam, typename LexPairTemp<ClassXName>::LexFunType);
  if (++ix > SIZE_LEXMAX) {
   fprintf(stderr,"Too many arguments for the functon syntaxAnalis.");
   throw -1;
  }
 } while ((lexicalTab[ix].lexWord = va_arg(lxParam,char*)));
 return seqAnalis(lexicalTab,ix);
}


template <class ClassXName>
int  FileSyntaxReader<ClassXName>::syntaxAnalis(char const *KeyWord, ...)
{
 LexPairTemp<ClassXName>  lexicalTab[SIZE_LEXMAX];
 int       ix;
 va_list   lxParam;
 va_start(lxParam,KeyWord);

 if (!(lexicalTab[ix = 0].lexWord = KeyWord)) return 0;
 do {
  lexicalTab[ix].lexFun = 
          va_arg(lxParam, typename LexPairTemp<ClassXName>::LexFunType);
  if (++ix > SIZE_LEXMAX) {
   fprintf(stderr,"Too many arguments for the functon syntaxAnalis.");
   throw -1;
  }
 } while ((lexicalTab[ix].lexWord = va_arg(lxParam,char*)));
 return snxAnalis(lexicalTab,ix);
}





template <class ClassXName>
int FileSyntaxReader<ClassXName>::seqAnalis( LexPairTemp<ClassXName> lexTab[],
                                             int                     lexMax 
                                           )
{
 char  lexWord[SIZE_LINELENGTH];
 int   ix = 0, err;

 while (!(err = getWord(lexWord,SIZE_LINELENGTH-1))) {
   if (!*lexWord) return 0;  // Napotkany dozwolony koniec pliku

   if (!strcmp(lexWord,lexTab[ix].lexWord)) {

      if (lexTab[ix].lexFun == 0L) return 0;
      if ((err = AfterFindingKeyword(lexWord))) throw err;
      if ((err = (((ClassXName*)this)->*lexTab[ix].lexFun)())) throw err;
      if (IsBreakLocalLoop() || IsBreakGlobalLoop()) { 
           ContinueLocalLoop();  return OK;
      }
      if (++ix >= lexMax) return 0;

   } else {

      if (!*lexWord) {
        *lexWord = fgetc(IFile);
         getSyntaxErrMsg(SyntaxError=ERR_WORD_EXCP,_syntaxErrMsg,
                          "%s%1d%c",FileName,lineNo,*lexWord);
         throw ERR_WORD_EXCP;
      }
      getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_KEYWORD1,_syntaxErrMsg,
                          "%s%1d%s%s",FileName,lineNo,lexWord,
                                      lexTab[ix].lexWord);
      throw ERR_UNEXPC_KEYWORD;
   }
 }
 if (err) throw err;
 return 0;
}



template <class ClassXName>
int FileSyntaxReader<ClassXName>::snxAnalis( LexPairTemp<ClassXName> lexTab[],
                                             int                     lexMax 
                                           )
{
 char  lexWord[SIZE_LINELENGTH];
 int   ix,err;
 char  WordsSet[MAX_WORDS_LINE];

 while (!(err = getWord(lexWord,SIZE_LINELENGTH-1))) {
   if (!*lexWord) return 0;  // Napotkany dozwolony koniec pliku
   for (ix=0; ix < lexMax; ix++) {
    if (!strcmp(lexWord,lexTab[ix].lexWord)) {
      if (lexTab[ix].lexFun == 0L) return 0;
      if ((err = AfterFindingKeyword(lexWord))) throw err;
      if ((err = (((ClassXName*)this)->*lexTab[ix].lexFun)())) throw err;
      if (IsBreakLocalLoop() || IsBreakGlobalLoop()) { 
           ContinueLocalLoop();  return OK;
      }
      break;
     }
   }
   if (ix >= lexMax) {
     if (!*lexWord) {
      *lexWord = fgetc(IFile);
      getSyntaxErrMsg(SyntaxError=ERR_WORD_EXCP,_syntaxErrMsg,
                             "%s%1d%c",FileName,lineNo,*lexWord);
      throw ERR_WORD_EXCP;
     }
    CopyKeywords(lexTab,lexMax,WordsSet);
    getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_KEYWORD,_syntaxErrMsg,
           "%s%1d%s%s",FileName,lineNo,lexWord,WordsSet);
    throw ERR_UNEXPC_KEYWORD;
   }
 }
 if (err) throw err;
 return 0;
}



#endif


