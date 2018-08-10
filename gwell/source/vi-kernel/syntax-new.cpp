/*
 * File:	syntax.cpp
 * Purpose:     Analizator syntaktyczny 
 * Version:     1.0.2
 * Author:      Bogdan Kreczmer
 * Created:	Kwiecien 1995
 * Updated:     2001
 * Copyright:	(c) 2001, Bogdan Kreczmer
 */

#ifdef __GNUG__
#pragma implementation
#endif

#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
using namespace std;

#include "extstring.hh"
#include "syntax-new.hh"
#include "syntax-new.e"
#include "getmsg.h"

//#define  SIZE_LEXMAX            50



#define  MSG_NO_MESSAGE  "A message for request no. ##1 wasn't found\n"
#define  FILE_SYNTAX_MSG "syntax.msg"
#define  FILE_SYNTAX_LOG "syntax.log"
#define  C_SHORT     1
#define  C_LONG      2
#define  STR(x)  #x


static storeFunction  storeChar;




static int isWordSign( int ch )
{
  return isalnum(ch) || ch == '_';
}


static int storeWord( char *s )
{
 int err;

 while (*s != '\0') if ((err = (*storeChar)( *s++)) != 0) return err;
 return OK;
}

static
char const *GetSyntaxErrMsg( int ErrNo )
{
  switch (ErrNo) {
    //== To blad z modulu readfig-new. Trzeba bedzie to rozdzielic.
   case  ERR_NO_MEMORY_FOR_FACEVTX: return
   "***  Not enough memory to allocate a face vertex table.";

     //== Te bledy sa zwiazane tylko z pakietem syntax.

   case  ERR_OPEN_FILE: return "*** The file `##1' can't be opened.";

   case  ERR_CHAR_EXPC: return
   "*** Syntax error in ##1 at line ##2:\n"
   "***  The character `##3' was found while `##4' was being looked for.";

   case  ERR_CHAR_END: return
   "*** Syntax error in ##1:\n"
   "***  The end of the file was reached while the character"
   " `##3' was being looked for.";

   case  ERR_UNEXPC_UNIT:   return 
   "*** Syntax error in ##1 at line ##2: Unexpected word `##3'.";

   case ERR_WORD_EXCP:      return
   "*** Syntax error in ##1 at line ##2:\n"
   "***  A keyword had been looking for while the character `##3' was found\n"
   "***  that couldn't start any word.";

   case ERR_UNEXPC_KEYWORD: return
   "*** Syntax error in ##1 at line ##2:\n"
   "***  An unexpected keyword `##3' had been found.\n"
   "***  An expceted keyword has to belong to the set:\n"
   "***     ##4.";

   case ERR_UNEXPC_KEYWORD1: return
   "*** Syntax error in ##1 at line ##2:\n"
   "***  An unexpected keyword `##3' had been found\n"
   "***  while the keyword '##4' had been looking for.\n";

   case ERR_NUMBER_EXPC:    return
   "*** Syntax error in ##1 at line ##2:\n"
   "***  No digit symbol has been met while a `double'"
                                            " number has been expected.";

   case ERR_UNEXPC_END:
     return "*** Syntax error in ##1: Unexpected end of the file.";

   default: 
     std::cout << "called: " << ErrNo << std::endl;
     break;

  }
 return NULL;
}





void InterpreterKern::SetErrMsg(char const *Msg)
{
 _syntaxErrMsg = Msg;
}



void  InterpreterKern::EmitError_Msg( int          ErrNo, 
                                      char const  *ErrPattMsg, 
				      char const  *format,
                                      ... 
                                    )
{
 va_list  AList;
 char Line[2024];

 _errno = ErrNo;
 char *Msg = new char [strlen(Line)+strlen(ErrPattMsg)+1];  
 strcpy(Msg,Line);

 if (*format) {
  va_start(AList,format);
  _syntaxErrMsg = KernelTransformMsg(Msg,format,AList);
  va_end(AList);
 }
 delete Msg;
 throw ErrNo;
}



void  InterpreterKern::EmitErrorForFile_Msg( int          ErrNo, 
                                             char const  *ErrPattMsg, 
				             char const  *format, 
                                             ... 
                                           )
{
 va_list  AList;
 char Line[2024];

 _errno = ErrNo;
 sprintf(Line,"Error: %i\nIn file: %s\nAt line: %i\n",ErrNo,FileName,lineNo);
 char *Msg = new char [strlen(Line)+strlen(ErrPattMsg)+1];  
 strcpy(Msg,Line);
 strcat(Msg,ErrPattMsg);

 if (*format) {
  va_start(AList,format);
  _syntaxErrMsg = KernelTransformMsg(Msg,format,AList);
  va_end(AList);
 }
 delete Msg;
 throw ErrNo;
}

/*
char const *InterpreterKern::ProduceErrMsgForFile( int         ErrNo, 
                                                   char const *ErrPattMsg, 
                                                   char const *format, 
                                                   ...
                                                 )
{
 char Line[2024];
 va_list  AList;

 _errno = ErrNo;
 sprintf(Line,"Error: %i\nIn file: %s\nAt line: %i\n",ErrNo,FileName,lineNo);

 char *Msg = new char [strlen(Line)+strlen(ErrPattMsg)+1];  

 strcpy(Msg,Line);
 strcat(Msg,ErrPattMsg);

 if (*format) {
  va_start(AList,format);
  Msg = KernelTransformMsg(Msg,format,AList);
  va_end(AList);
 }
 return Msg;
}
*/


int InterpreterKern::SetErrMsgForFile( int         ErrNo, 
                                       char const *ErrPattMsg, 
                                       char const *format, 
                                       ...
                                     )
{
 char Line[2024];
 va_list  AList;

 _errno = ErrNo;
 sprintf(Line,"Error: %i\nIn file: %s\nAt line: %i\n",ErrNo,FileName,lineNo);

 char *Msg = new char [strlen(Line)+strlen(ErrPattMsg)+1];  

 strcpy(Msg,Line);
 strcat(Msg,ErrPattMsg);

 if (*format) {
  va_start(AList,format);
  Msg = KernelTransformMsg(Msg,format,AList);
  va_end(AList);
 }
 SetErrMsg(Msg);
 delete Msg;
 return _errno;
}



/*
char const *ProduceErrMsg(  int         ErrNo,
                            char const *ErrPattMsg,
                            char const *format,
                            ...
                         )
{
 char *Msg = new char [strlen(ErrPattMsg)+1];  
 va_list  AList;

 strcpy(Msg,ErrPattMsg);

 if (*format) {
  va_start(AList,format);
  Msg = KernelTransformMsg(Msg,format,AList);
  va_end(AList);
 }
 return Msg;
}
*/


/*
int getSyntaxErrMsg( int no, char const **ErrMsg, char const *format, ... )
{ va_list  AList;
  int        err;
  char       *s = NULL;
  FILE       *f;

 if (*ErrMsg != NULL) { RELEASE(*ErrMsg);  *ErrMsg = NULL;}
 if (!(s = GetSyntaxErrMsg(no))) {
  if ((err = ReadMsg( FILE_SYNTAX_MSG, no, &s)) != OK) {
    if ((f = fopen(FILE_SYNTAX_LOG,"w"))) fputs("*** Syntax error\n",f);
    switch (err) {
      case ERR_CANNOT_OPEN:
        if (f)  fputs("!!! The file "FILE_SYNTAX_MSG
                      " cantaining messages can't be open.\n",f);
        break;

      case ERR_READ_FILE:
        if (f) fprintf(f,"!!! The file "FILE_SYNTAX_MSG
                         " dosen't cantain a message no. %d.\n",no);
        break;

      case ERR_NO_MEMORY:
        if (f) fprintf(f,"!!! There is no enough memory to"
                         " create a message no. %d.\n",no);
         break;
    }
   fclose(f);  *ErrMsg = NULL;  return err;
  }
 } else {
    char *tmp = new char [strlen(s)+1];  strcpy(tmp,s);  s = tmp;
 }
 if (*format) {
  va_start(AList,format);
  *ErrMsg = KernelTransformMsg(s,format,AList);
  va_end(AList);
 } else *ErrMsg = s;
 return OK;
}
*/






int getSyntaxErrMsg( int no, ExtString &ErrMsg, char const *format, ... )
{ va_list  AList;
  int        err;
  char const *s = 0L;
  char       *s_tmp = 0L;
  FILE       *f;

 if (!(s = GetSyntaxErrMsg(no))) {
  if ((err = ReadMsg( FILE_SYNTAX_MSG, no, &s_tmp)) != OK) {
    if ((f = fopen(FILE_SYNTAX_LOG,"w"))) fputs("*** Syntax error\n",f);
    switch (err) {
      case ERR_CANNOT_OPEN:
        if (f)  fputs("!!! The file "FILE_SYNTAX_MSG
                      " cantaining messages can't be open.\n",f);
        break;

      case ERR_READ_FILE:
        if (f) fprintf(f,"!!! The file "FILE_SYNTAX_MSG
                         " dosen't cantain a message no. %d.\n",no);
        break;

      case ERR_NO_MEMORY:
        if (f) fprintf(f,"!!! There is no enough memory to"
                         " create a message no. %d.\n",no);
         break;
    }
   fclose(f);  ErrMsg = "";  
   return err;
  }
 } else {
    s_tmp = new char [strlen(s)+1];  strcpy(s_tmp,s); 
 }
 if (*format) {
  va_start(AList,format);
  ErrMsg = s_tmp = KernelTransformMsg(s_tmp,format,AList);
  va_end(AList);
 } else ErrMsg = s_tmp;
 if (s_tmp) delete s_tmp;
 return OK;
}



/*
int InterpreterKern::SetErrMsgForFile( int          ErrNo, 
                                       char const  *Msg, 
                                       char const  *format, 
                                       ... 
                                     )
{ 
 va_list  AList;

 _errno = ErrNo;
 if (*format) {
  va_start(AList,format);
  char *s_tmp = new char [strlen(Msg)+1];  strcpy(s_tmp,Msg);
  ErrMsg = s_tmp = KernelTransformMsg(s_tmp,format,AList);
  if (s_tmp) delete s_tmp;
  va_end(AList);
 } else ErrMsg = Msg;
 return ErrNo;
}
*/






void RemoveSpaces(char *str)
{
 int i;

 for (i=0; isspace(str[i]); i++);
 if (i) strcpy(str,str+i);
 for (i=strlen(str)-1; i > -1  && isspace(str[i]); i--);
 str[i+1] = '\0';
}




//=======================================================================
//.................... InterpreterKern  .................................

InterpreterKern::InterpreterKern()
{
 _errno = 0;
 _BreakLocalLoop = _BreakGlobalLoop = false;
 lineNo = SyntaxError = 0;
 _pStoreRecord = 0L;
 FileName = "syntax.msg";  IFile = NULL;
 AuxParam = NULL;

 SetSeparaters(";");
 SetParamEnvironment('{',',','}');
 SetBlockComment("/*","*/");
 SetLineComment("//");
 SetAdditionalValCh("");
 SetUserErrMsg("");

 iswordsign = &InterpreterKern::isWordSign;
}




char *InterpreterKern::ReadString(char *Line, int Size)
{
  if (!ReadCharsToNL(Line,Size)) return NULL;
  RemoveSpaces(Line);
  RemoveComment(Line);
  return Line;
}


int InterpreterKern::Ungetchar( char c )
{ return ungetc(c,IFile);}


int  InterpreterKern::omitComment(int commType)
{
 int comCounter = 1,ch;
 char const *c_openS=C_Open,*c_closeS=C_Close;
 int   ox=0,cx=0,ol=strlen(C_Open),cl=strlen(C_Close);
 
 if (commType == C_SHORT) {
   while ((ch = fgetc(IFile)) != EOF) if (ch == '\n') break;
   lineNo++;
   return OK;
 }

 while (comCounter > 0) {
  if ((ch=fgetc(IFile)) == EOF) {
    getSyntaxErrMsg(SyntaxError = ERR_COMMENT_END,_syntaxErrMsg,"%s",FileName);
    return SyntaxError;
  }
  if (ch == '\n') { lineNo++;  continue;}
  if (cx == 0 && ch == c_openS[ox]) { if (++ox >= ol) { ox=0;  comCounter++;}}
  else {
    ox = 0;
    if (ch == c_closeS[cx]) { if (++cx >= cl) { cx=0;  comCounter--;}}
    else  cx=0;
  }
 }
 return OK;
}


char *InterpreterKern::ReadCharsToNL(char *Line, int Size)
{
 char *s;
 s = fgets(Line,Size,IFile);
 if (s) lineNo++;
 return s;
}



int InterpreterKern::openComment(int *commType)
{
 char const *LOpenC = C_Open, *SOpenC = C_Line;
 int   ch;
 char  tab[400];
 char  *ptrTab = tab;
 bool   OK_LONG = *C_Open, OK_SHORT = *C_Line;
 int    no = 0;

 do {
  if ((ch=fgetc(IFile)) == EOF) {
    for (;no > 0; no--) ungetc(*(--ptrTab),IFile);
    getSyntaxErrMsg(SyntaxError = ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
    return SyntaxError;
  }
  if (*LOpenC) {
      OK_LONG  = ((ch == *LOpenC++) && OK_LONG);
      if (!*LOpenC++ && OK_LONG) break;
  }
  if (*SOpenC) {
      OK_SHORT = ((ch == *SOpenC++) && OK_SHORT);
      if (!*SOpenC && OK_SHORT)  break;
  }
  *ptrTab++ = ch;  no++;
 } while (*LOpenC || *SOpenC);

 if (!(OK_SHORT || OK_LONG)) {
   *ptrTab = '\0';
   for (;no > 0; no--) ungetc(*(--ptrTab),IFile);
   getSyntaxErrMsg(SyntaxError = ERR_UNEXPC_UNIT,_syntaxErrMsg,
                   "%s%d%s",FileName,lineNo,tab);
   return SyntaxError;
 }
 if (OK_SHORT) *commType = C_SHORT;  else *commType = C_LONG;

 return OK;
}





int InterpreterKern::passComments(void)
{
 int err,commType;

 if ((err = openComment(&commType)) != OK) return err;
 return omitComment(commType);
}




int InterpreterKern::getString( char *lWord, int MaxLn, bool NL_IsSpace )
{
 int  ch;
 int  ix = 0,err,commType;
/* Dlugosc slowa MaxLn + 1   */

 *lWord = '\0';

 while  ((ch = fgetc(IFile)) != EOF) {
  if (ch < 0) return ERR_NOASCII;
  if (PR_Separater == ch) return OK;
  if (!(isspace(ch) || strchr(SeparChars,ch))) {
  if (ch != C_Line[0] && ch != C_Open[0] && ch != PR_Open) break; 
    else {
     ungetc( ch,IFile );
     if (ch == PR_Open) return OK; //????
     if ((err = openComment(&commType)) != OK) {
       ch = fgetc(IFile); // Gdyz w openComment zostal zwrocony.
       break;
       // Tutaj jest roznica w stosunku do GetWord
       /*
       getSyntaxErrMsg(SyntaxError = ERR_WORD_EXCP,
             &syntaxErrMsg,"%s%1d%c",FileName,lineNo,ch);
       return ERR_NUMBER_EXPC;
       */
     } else if ((err=omitComment(commType)) != OK) return err;
    }
  } else if (ch == '\n') { lineNo++; if (!NL_IsSpace) return OK; }
 }
 if (ch == EOF) {
   if (CanFileEnd()) { BreakGlobalLoop();  return 0; }
   getSyntaxErrMsg(SyntaxError = ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
   return SyntaxError;
 }
 do {
   //   if (!(*iswordsign)(ch))  break;
   if (isspace(ch) || strchr(SeparChars,ch) || PR_Separater == ch) break;
   if (ix < MaxLn) lWord[ix++] = ch /*tolower(ch)*/;
 } while  ((ch = fgetc(IFile)) != EOF);
 lWord[ix] = '\0';
 if (!ix && ch == EOF) {
   if (CanFileEnd()) { BreakGlobalLoop();  return 0; }
   getSyntaxErrMsg(SyntaxError = ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
   return SyntaxError;
 }
 ungetc(ch,IFile);
 return OK;
}


void InterpreterKern::ResetAnalis(void)
{ 
  if (IFile) fclose(IFile);
  lineNo = SyntaxError = 0;
}


void InterpreterKern::SetSeparaters(char *s)
{
   strncpy(SeparChars,s,MAX_SEPARCHARS); 
   SeparChars[MAX_SEPARCHARS] = '\0';
}



/* Dlugosc slowa MaxLn + 1   */
int InterpreterKern::getWord( char *lWord, int MaxLn )
{
 int  ch;
 int  ix = 0,err,commType;


 *lWord = '\0';
 while  ((ch = fgetc(IFile)) != EOF) {
  if (ch < 0) return ERR_NOASCII;
  if (!(isspace(ch) || strchr(SeparChars,ch))) {
    if (PR_Separater == ch) return OK;
    if ((this->*iswordsign)(ch)) break;
    else {
     ungetc( ch,IFile );
     if (ch == PR_Open) return OK;
     if (openComment(&commType) != OK) {
       getSyntaxErrMsg(SyntaxError = ERR_WORD_EXCP,
             _syntaxErrMsg,"%s%1d%c",FileName,lineNo,ch);
       return ERR_NUMBER_EXPC;
     }
     if ((err=omitComment(commType)) != OK) return err;
    }
  } else if (ch == '\n')  lineNo++;
 }
 if (ch == EOF) {
   if (CanFileEnd()) { BreakGlobalLoop();  return 0; }
   getSyntaxErrMsg(SyntaxError = ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
   return SyntaxError;
 }
 ungetc(ch,IFile);
 fgetpos(IFile,&FilePos);
 fgetc(IFile);
  // Ustawienie znacznik w momencie
  //  rozpoczecia sie slowa
 do {
   if (!(this->*iswordsign)(ch))  break;
   if (isspace(ch) || strchr(SeparChars,ch) || PR_Separater == ch) break;
   if (ix < MaxLn) lWord[ix++] = ch;
 } while  ((ch = fgetc(IFile)) != EOF);
 lWord[ix] = '\0';
 if (!ix && ch == EOF) {
   if (CanFileEnd()) { BreakGlobalLoop();  return 0; }
   getSyntaxErrMsg(SyntaxError = ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
   return SyntaxError;
 }
 ungetc(ch,IFile);
 return OK;
}








int InterpreterKern::GetWord( string &Word )
{
 int  ch;
 int  ix = 0,err,commType;


 Word = "";
 while  ((ch = fgetc(IFile)) != EOF) {
  if (ch < 0) return ERR_NOASCII;
  if (!(isspace(ch) || strchr(SeparChars,ch))) {
    if (PR_Separater == ch) return OK;
    if ((this->*iswordsign)(ch)) break;
    else {
     ungetc( ch,IFile );
     if (ch == PR_Open) return OK;
     if (openComment(&commType) != OK) {
       getSyntaxErrMsg(SyntaxError = ERR_WORD_EXCP,
             _syntaxErrMsg,"%s%1d%c",FileName,lineNo,ch);
       return ERR_NUMBER_EXPC;
     }
     if ((err=omitComment(commType)) != OK) return err;
    }
  } else if (ch == '\n')  lineNo++;
 }
 if (ch == EOF) {
   if (CanFileEnd()) { cout << "EEEEND" << endl; BreakGlobalLoop();  return 0; }
   getSyntaxErrMsg(SyntaxError = ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
   return SyntaxError;
 }
 ungetc(ch,IFile);
 fgetpos(IFile,&FilePos);
 fgetc(IFile);
  // Ustawienie znacznik w momencie
  //  rozpoczecia sie slowa
 do {
   if (!(this->*iswordsign)(ch))  break;
   if (isspace(ch) || strchr(SeparChars,ch) || PR_Separater == ch) break;
   Word += ch;
 } while  ((ch = fgetc(IFile)) != EOF);
 if (!ix && ch == EOF) {
   if (CanFileEnd()) { cout << "XEEEND" << endl; BreakGlobalLoop();  return 0; }
   getSyntaxErrMsg(SyntaxError = ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
   return SyntaxError;
 }
 ungetc(ch,IFile);
 return OK;
}









int InterpreterKern::isWordSign( int ch )
{
  return isalnum(ch) || ch == '_' || strchr(AddValidChars,ch);
}



void InterpreterKern::SetLineComment(char const *str) 
{ 
  strncpy(C_Line,str,2); C_Line[2] = 0;
}


void InterpreterKern::SetBlockComment( char const *OpDelim, 
                                        char const *ClDelim
                                      ) 
{
 C_Open  = OpDelim;  C_Close = ClDelim;
}


int InterpreterKern::LookForString(char *Str, int lnMax, bool NL_IsSpace)
{
 if ((_errno = getString(Str,lnMax,NL_IsSpace))) {
    if (_errno == EOF) {
      getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
      throw ERR_UNEXPC_END;
    }
    throw _errno;
 }
 return OK;
}


int InterpreterKern::LookForString( ExtString &Str )
{
  char LongStr[512];
 
  if ((_errno = LookForString(LongStr,511))) return _errno;
  LongStr[511] = 0;
  Str = LongStr;
  return 0;
}



int InterpreterKern::LookForStringToNL( ExtString &Str )
{
  char LongStr[512];
 
  if ((_errno = LookForString(LongStr,511,false))) return _errno;
  LongStr[511] = 0;
  Str = LongStr;
  return 0;
}




int InterpreterKern::LookForStringAfterChar( char Keychar,
                                             char *Str,
                                             int   Size
                                           )
{
 if ((_errno = LookForChar(Keychar))) return _errno;
 if ((_errno = LookForString(Str,Size))) return _errno;
 return 0;
}

bool InterpreterKern::IsCharNext(char const ch)
{
 int   err,commType;
 int   cx;

 while ((cx = fgetc(IFile)) != EOF) {
   if (cx == ch)  { ungetc(cx,IFile);  return true; }
   if (isspace(cx)) {
     if (cx == '\n') lineNo++;
     continue;
    }
   ungetc(cx,IFile);
   if (openComment(&commType) != OK) {
     return false;
   }
   if ((err=omitComment(commType)) != OK)  return err;
 }
 ungetc(cx,IFile);
 return false;
}




int InterpreterKern::IsNotCharNext(char const ch)
{
 return IsCharNext(ch) ? 0 : -1;
}




int InterpreterKern::LookForChar( char  ch  )
{
 int   err,commType;
 int   cx;

 while ((cx = fgetc(IFile)) != EOF) {
   if (cx == ch)     return OK;
   if (isspace(cx)) {
     if (cx == '\n') lineNo++;
     continue;
    }
   ungetc(cx,IFile);
   if (openComment(&commType) != OK) {
     getSyntaxErrMsg(SyntaxError=ERR_CHAR_EXPC,_syntaxErrMsg,
                             "%s%1d%c%c",FileName,lineNo,cx,ch);
     throw ERR_CHAR_EXPC;
   }
   if ((err=omitComment(commType)))  throw err;
 }
 getSyntaxErrMsg(SyntaxError=ERR_CHAR_END,_syntaxErrMsg,
                              "%s%1d%c",FileName,lineNo,ch);
 throw ERR_CHAR_END;
}


int InterpreterKern::singleSymbol( char* Symbol, int lnMax )
{
 int err;

 if ((err = LookForChar( PR_Open ))       != OK)  return err;
 if ((err = LookForWord( Symbol, lnMax )) != OK)  return err;
 if ((err = LookForChar( PR_Close ))      != OK)  return err;
 return OK;
}

int InterpreterKern::singleParam( char* Word, int Max )
{
 int err;

 if ((err = LookForChar( PR_Open ))     != OK)  return err;
 if ((err = LookForParString(Word,Max)) != OK)  return err;
 if ((err = LookForChar( PR_Close ))    != OK)  return err;
 return OK;
}


int InterpreterKern::singleParam( double *number )
{
 int err;

 if (PR_Open  != NULL_CHAR) if ((err=LookForChar(PR_Open)) != OK)  return err;
 if ((err = LookForNumber( number )) != OK)  return err;
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}



int InterpreterKern::singleParam( int *number )
{
 int err;

 if (PR_Open  != NULL_CHAR) if ((err=LookForChar(PR_Open)) != OK)  return err;
 if ((err = LookForNumber( number ))  != OK)  return err;
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}


int InterpreterKern::singleParam( short int *number )
{
 int d;
 int err = singleParam(&d);
 *number = (short int)(d);
 return err;
}



int InterpreterKern::singleParam( float *number )
{
 double d;
 int err = singleParam(&d);
 *number = float(d);
 return err;
}


int InterpreterKern::LookForWord( char *Word, int lnMax )
{
 int err;

 if ((err = getWord( Word, lnMax ))  != OK) {
    if (err == EOF) {
      getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
      return ERR_UNEXPC_END;
    }
    return err;
 }
 return OK;
}


int InterpreterKern::LookForKeyword( char const *Word )
{
 int err;
 char  KeyWord[200];

 if ((err = LookForWord(KeyWord,99))  != OK) {
    return err;
 }
 if (strcmp(KeyWord,Word)) {
    getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_WORD,_syntaxErrMsg,"%s%i%s%s",
                       FileName,lineNo,KeyWord,Word);
    return SyntaxError;
 }
 return OK;
}



int InterpreterKern::LookForKeywordChar( char const *Keyword, char Keychar )
{
 int err;

 if ((err = LookForKeyword(Keyword))) return err;
 if ((err = LookForChar(Keychar)))    return err;
 return 0;
}




int InterpreterKern::LookForNumber( double *dNo  /*, FILE *IFile*/ )
{
 int   p,commType;

 while ((p = fscanf(IFile,"%lf",dNo)) != 1) {
   if (p == EOF) {
     getSyntaxErrMsg(SyntaxError=ERR_NUMBER_END,_syntaxErrMsg,"%s",FileName);
     return ERR_NUMBER_END;
   }
   if (openComment(&commType) != OK) {
     getSyntaxErrMsg(SyntaxError=ERR_NUMBER_EXPC,_syntaxErrMsg,"%s%1d",FileName,lineNo);
     return ERR_NUMBER_EXPC;
   }
   if ((p=omitComment(commType)) != OK) return p;
 }
 return OK;
}



int InterpreterKern::LookForNumber( float *fNo )
{
 double dNo;
 int err;

 if ((err = LookForNumber(&dNo)) != OK) return err;
 *fNo = (float) dNo;
 return err;
}


int InterpreterKern::LookForNumber( long* intNo )
{
 char ch;

 while (isspace(ch = fgetc(IFile))) { if (ch == '\n') lineNo++;}
 ungetc(ch,IFile);
 switch (fscanf(IFile,"%li",intNo)) {
  case EOF :
    getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
    throw ERR_UNEXPC_END;
  case 1   : return OK;
  default  : 
    getSyntaxErrMsg(SyntaxError=ERR_FAIL_INT,_syntaxErrMsg,
                                                   "%s%1d",FileName,lineNo);
    throw ERR_FAIL_INT;
 }
}



int InterpreterKern::LookForNumber( unsigned long* intNo )
{
 char ch;

 while (isspace(ch = fgetc(IFile))) { if (ch == '\n') lineNo++;}
 ungetc(ch,IFile);
 switch (fscanf(IFile,"%ui",intNo)) {
  case EOF :
    getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
    throw ERR_UNEXPC_END;
  case 1   : return OK;
  default  : 
    getSyntaxErrMsg(SyntaxError=ERR_FAIL_INT,_syntaxErrMsg,
                                                   "%s%1d",FileName,lineNo);
    throw ERR_FAIL_INT;
 }
}




int InterpreterKern::LookForNumber( int* intNo )
{
 long Dig;
 int  err;
 QUESTION(LookForNumber(&Dig))
 *intNo = int(Dig);
 return OK;
}



int InterpreterKern::LookForNumber( unsigned int* intNo )
{
 unsigned long Dig;
 int  err;
 QUESTION(LookForNumber(&Dig))
 *intNo = int(Dig);
 return OK;
}


int InterpreterKern::LookForParString( char *lWord, int MaxLn )
{
 int  ch;
 int  ix = 0;
/* Dlugosc slowa MaxLn + 1   */

*lWord = '\0';
 ch = fgetc(IFile);
 if (ch < 0) return ERR_NOASCII;
 do {
   if (ch == PR_Close || ch == PR_Separater) { ungetc(ch,IFile); return OK;}
   if (ix < MaxLn) lWord[ix++] = ch;
 } while  ((ch = fgetc(IFile)) != EOF);

 lWord[ix] = '\0';
 if (!ix && ch == EOF) {
   getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_END,_syntaxErrMsg,"%s",FileName);
   return ERR_UNEXPC_END;
 }
 ungetc(ch,IFile);
 return OK;
}





int InterpreterKern::LookForAnyChar( char *CharSet, char *FoundChar )
{
 int   err,commType;
 int   cx;

 while ((cx = fgetc(IFile)) != EOF) {
   if (strchr(CharSet,cx))  { *FoundChar = cx;  return OK; }
   if (isspace(cx)) {
     if (cx == '\n') lineNo++;
     continue;
    }
   ungetc(cx,IFile);
   if (openComment(&commType) != OK) {
     getSyntaxErrMsg(SyntaxError=ERR_CHARS_EXPC,_syntaxErrMsg,"%s%1d%c%s",
                     FileName,lineNo,cx,CharSet);
     throw ERR_CHAR_EXPC;
   }
   if ((err=omitComment(commType)))  throw err;
 }
 getSyntaxErrMsg(SyntaxError=ERR_CHAR_END,_syntaxErrMsg,
                                               "%s%1d%c",FileName,lineNo,cx);
 throw ERR_CHAR_END;
}



int InterpreterKern::LookForSingleWord( char*  keyword, storeFunction  storeF )
{
 char  lexWord[SIZE_LINELENGTH];
 int   err;

 storeChar = storeF;
 while ((err = getWordGathering(lexWord,SIZE_LINELENGTH-1,IFile)) == 0) {
     if (!strcmp(lexWord,keyword))  break;
     else if ((err = storeWord( lexWord )) != OK) return err;
 }
 if (err == EOF) {
   getSyntaxErrMsg(ERR_UNEXPC_END,_syntaxErrMsg,"");
   return ERR_UNEXPC_END;
 }
 if (err != OK)   return err;
 if ((*storeChar)( '\0')) {
   getSyntaxErrMsg(ERR_SHORT_BUFF,_syntaxErrMsg,"");
   return ERR_SHORT_BUFF;
 }
 return OK;
}



int InterpreterKern::twoParam( char* Word1, int Max1, char* Word2, int Max2)
{
 int err;

 if (PR_Open != NULL_CHAR) if ((err=LookForChar(PR_Open)) != OK)  return err;
 if ((err = LookForWord(Word1,Max1))   != OK)  return err;
 if (PR_Separater != NULL_CHAR)
                  if ((err=LookForChar(PR_Separater)) != OK)  return err;
 if ((err = LookForWord(Word2,Max2))   != OK)  return err;
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}




int InterpreterKern::twoParam( int *number1, int *number2  )
{
 int err;

 if (PR_Open != NULL_CHAR) if ((err=LookForChar(PR_Open)) != OK)  return err;
 if ((err = LookForNumber( number1 ))   != OK)  return err;
 if (PR_Separater != NULL_CHAR)
                  if ((err=LookForChar(PR_Separater)) != OK)  return err;
 if ((err = LookForNumber( number2 ))   != OK)  return err;
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}



int InterpreterKern::twoParam( double *number1, double *number2  )
{
 int err;

 if (PR_Open != NULL_CHAR) if ((err=LookForChar(PR_Open)) != OK)  return err;
 if ((err = LookForNumber( number1 ))   != OK)  return err;
 if (PR_Separater != NULL_CHAR)
                  if ((err=LookForChar(PR_Separater)) != OK)  return err;
 if ((err = LookForNumber( number2 ))   != OK)  return err;
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}



int InterpreterKern::twoParam( float *f1, float *f2)
{
 double d1,d2;
 int    err;

 if ((err = twoParam(&d1,&d2)) != OK) return err;
 *f1 = (float) d1;  *f2 = (float) d2;
 return err;
}


int InterpreterKern::threeParam( double *num1, double *num2, double *num3  )
{
 int err;

 if (PR_Open != NULL_CHAR) {
   if ((err=LookForChar(PR_Open)) != OK)  {
     return err;
   }
 }
 if ((err = LookForNumber( num1 )) != OK)  return err;
 if (PR_Separater != NULL_CHAR)
                  if ((err=LookForChar(PR_Separater)) != OK)  return err;
 if ((err = LookForNumber( num2 ))   != OK)  return err;
 if (PR_Separater != NULL_CHAR)
                  if ((err=LookForChar(PR_Separater)) != OK)  return err;
 if ((err = LookForNumber( num3 ))   != OK)  return err;
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}



int InterpreterKern::threeParam( float *f1, float *f2, float *f3)
{
 double d1,d2,d3;
 int    err;

 if ((err = threeParam(&d1,&d2,&d3)) != OK) return err;
 *f1 = (float) d1;  *f2 = (float) d2; *f3 = (float) d3;
 return err;
}


int InterpreterKern::threeParam( int *f1, int *f2, int *f3)
{
 double d1,d2,d3;
 int    err;

 if ((err = threeParam(&d1,&d2,&d3)) != OK) return err;
 *f1 = (int) d1;  *f2 = (int) d2; *f3 = (int) d3;
 return err;
}



int InterpreterKern::fiveParam( float *num1, float *num2, float *num3, float *num4, float *num5)
{
 int err;

 if (PR_Open != NULL_CHAR) if ((err=LookForChar(PR_Open)) != OK)  return err;
 if ((err = LookForNumber( num1 ))   != OK)  return err;
 if (PR_Separater != NULL_CHAR)
                  if ((err=LookForChar(PR_Separater)) != OK)  return err;
 if ((err = LookForNumber( num2 ))   != OK)  return err;
 if (PR_Separater != NULL_CHAR)
                  if ((err=LookForChar(PR_Separater)) != OK)  return err;
 if ((err = LookForNumber( num3 ))   != OK)  return err;
 if (PR_Separater != NULL_CHAR)
                  if ((err=LookForChar(PR_Separater)) != OK)  return err;
 if ((err = LookForNumber( num4 ))   != OK)  return err;
 if (PR_Separater != NULL_CHAR)
                  if ((err=LookForChar(PR_Separater)) != OK)  return err;
 if ((err = LookForNumber( num5 ))   != OK)  return err;
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}


int InterpreterKern::getWordGathering( char *lWord, int MaxLn, FILE *IFile )
{
 int  ch;
 int  ix = 0;

// Dlugosc slowa MaxLn + 1

 while  ((ch = fgetc(IFile)) != EOF) {
  if ((this->*iswordsign)(ch))   break;
  if (ch == '\n') lineNo++;
  if ((*storeChar)( ch)) {
    getSyntaxErrMsg(ERR_SHORT_BUFF,_syntaxErrMsg,"%s%1d",FileName,lineNo);
    return ERR_SHORT_BUFF;
  }
 }
 do {
   if (!(this->*iswordsign)(ch))  break;
   if (ix < MaxLn) lWord[ix++] = ch;
 } while  ((ch = fgetc(IFile)) != EOF);

 lWord[ix] = '\0';
 if (!ix && ch == EOF) return EOF;
 ungetc(ch,IFile);
 return OK;
}



int InterpreterKern::Start( char const  *      FileName, 
                            ExtString &      ErrMsg,
                            AUXDATA            pStoreRecord
                          )
{
  _pStoreRecord = pStoreRecord;
  InterpreterKern::FileName = FileName;
  ContinueGlobalLoop();   ContinueLocalLoop();

  try {
     _errno = BeforReading();
     if (!_errno) _errno = startAnalis();
     if (!_errno) _errno = AfterReading();
     ErrMsg = GetErrMsg();
  } catch (int e) {
     ErrMsg = GetErrMsg(); 
     _errno = e;
     return e;   
  }
  return _errno;
}


/*
int InterpreterKern::Start( char const *         FileName, 
                            ExtString         &ErrMsg,
                            AUXDATA              pStoreRecord
                          )
{
  char const *pErrMsg = NULL;
  
  if (Start(FileName,&pErrMsg,pStoreRecord)) {
    if (pErrMsg) { ErrMsg = pErrMsg;  delete pErrMsg; }
  }
  return _errno;
}
*/


int InterpreterKern::startAnalis()
{
  lineNo = 1;  
  if ((IFile = fopen(FileName,"r")) == NULL) {
    getSyntaxErrMsg(SyntaxError=ERR_OPEN_FILE,_syntaxErrMsg,"%s",FileName);
    throw ERR_OPEN_FILE;
  }

  if ((_errno = StartReading()) != NOTFINISHED) {
    fclose(IFile);
  }
  if (_errno) throw _errno;
  return 0;
}




//.................... InterpreterKern  .................................
//=======================================================================





//===========================================================================
//______________________ FileSyntaxReader ____________________________________



/*
static void CopyKeywords( LexStruct lexTab[], int lexMax, char*  WordsLine)
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
*/





