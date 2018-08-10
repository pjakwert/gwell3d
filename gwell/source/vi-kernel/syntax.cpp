/*
 * File:	syntax.cc
 * Purpose: Analizator syntaktyczny  w  wxICARS
 * Author:  Bogdan Kreczmer
 * Created:	Kwiecien 1995
 * Updated:
 * Copyright:	(c) 1995, Bogdan Kreczmer
 */

#ifdef __GNUG__
#pragma implementation
#endif

#include <ctype.h>
#include<string.h>

#include "syntax.h"
#include "getmsg.h"

#include "system.e"
#include "syntax.e"


#include "debug.h"

#define  MSG_NO_MESSAGE  "A message for request no. ##1 wasn't found\n"
#define  FILE_SYNTAX_MSG "syntax.msg"
#define  FILE_SYNTAX_LOG "syntax.log"
#define  LineLength  100
#define  C_SHORT     1
#define  C_LONG      2
#define  STR(x)  #x


static storeFunction  storeChar;


int isWordSign( int ch )
{
  return isalnum(ch) || ch == '_' || ch == '#';
}

LexCharFun  iswordsign = isWordSign;



int storeWord( char *s )
{
 int err;

 while (*s != '\0') if ((err = (*storeChar)( *s++)) != 0) return err;
 return OK;
}

//------------------------------------------
// Tymczasowo pozniej przesniesc do syntax.e
#define ERR_UNEXPC_KEYWORD1      54

static
char *GetSyntaxMsg( int ErrNo )
{
  switch (ErrNo) {
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
    break;

  }
  return NULL;
}



static int getSyntaxErrMsg( int no, char **ErrMsg, char *format, ... )
{ va_list  AList;
 int        err;
 char       *s = NULL;
 FILE       *f;

 if (*ErrMsg != NULL) { RELEASE(*ErrMsg);  *ErrMsg = NULL;}
 if (!(s = GetSyntaxMsg(no))) {
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



/*----------------------------------------

int getSyntaxErrMsg( int no, char **ErrMsg, char *format, ... )
{ va_list  AList;
  int        err;
  char       *s = NULL;
  FILE       *f;

 if (*ErrMsg != NULL) { RELEASE(*ErrMsg);  *ErrMsg = NULL;}
 if ((err = ReadMsg( FILE_SYNTAX_MSG, no, &s)) != OK)
       {
          if ((f = fopen(FILE_SYNTAX_LOG,"w")) != NULL) {
                   fputs("*** Syntax error\n",f);
          }
          switch (err) {
           case ERR_CANNOT_OPEN
           :
              if (f != NULL)
                 fputs("!!! The file "FILE_SYNTAX_MSG" cantaining messages can't be open.\n",f);
                 break;
           case ERR_READ_FILE:
              if (f != NULL) {
                 fprintf(f,
                   "!!! The file "FILE_SYNTAX_MSG" dosen't cantain a message no. %d.\n",
                  no);}  break;
           case ERR_NO_MEMORY:
              if (f != NULL) {
                 fprintf(f,"!!! There is no enough memory to create a message no. %d.\n",
                         no);
              } break;
         }
         fclose(f);  *ErrMsg = NULL;  return err;
       }
 if (*format != '\0') {
  va_start(AList,format);
  *ErrMsg = KernelTransformMsg(s,format,AList);
  va_end(AList);
 } else *ErrMsg = s;
 return OK;
}
*/

/*
int  FileInterpreter::SetErrMess(int errNo, char *FileName, char *format, ... )
{
 char *Msg,*s;
 va_list  AList;

 va_start(AList,format);
 errMesg = KernelFGetMsg(NoErr,fileName,format,AList);
 va_end(AList);
 return errNo;
}
*/

int FileInterpreter::Ungetchar( char c )
{ return ungetc(c,IFile);}


int  FileInterpreter::omitComment(int commType)
{
 int comCounter = 1;
 char  ch,*c_openS=C_Open,*c_closeS=C_Close;
 int   ox=0,cx=0,ol=strlen(C_Open),cl=strlen(C_Close);

 if (commType == C_SHORT) {
   while ((ch = fgetc(IFile)) != EOF) if (ch == '\n') break;
   lineNo++;
   return OK;
 }
 while (comCounter > 0) {
  if ((ch=fgetc(IFile)) == EOF) {
    getSyntaxErrMsg(SyntaxError = ERR_COMMENT_END,&syntaxErrMsg,"%s",FileName);
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










int FileInterpreter::openComment(int *commType)
{
 char  ch,*LOpenC = C_Open, *SOpenC = C_Line;
 char  tab[100];
 char  *ptrTab = tab;
 int   OK_LONG = 1, OK_SHORT = 1, no = 0;

 do {
  if ((ch=fgetc(IFile)) == EOF) {
    for (;no > 0; no--) ungetc(*(--ptrTab),IFile);
    getSyntaxErrMsg(SyntaxError = ERR_UNEXPC_END,&syntaxErrMsg,"%s",FileName);
    return SyntaxError;
  }
  OK_LONG  = (ch == *LOpenC++ && OK_LONG);
  OK_SHORT = (ch == *SOpenC++ && OK_SHORT);
  *ptrTab++ = ch;  no++;
 } while (*LOpenC != '\0' || *SOpenC != '\0');


 if (!(OK_SHORT || OK_LONG)) {
   *ptrTab = '\0';
   for (;no > 0; no--) ungetc(*(--ptrTab),IFile);
   getSyntaxErrMsg(SyntaxError = ERR_UNEXPC_UNIT,&syntaxErrMsg,"%s%d%s",FileName,lineNo,tab);
   return SyntaxError;
 }
 if (OK_SHORT) *commType = C_SHORT;  else *commType = C_LONG;

 return OK;
}





int FileInterpreter::passComments(void)
{
 int err,commType;

 if ((err = openComment(&commType)) != OK) return err;
 return omitComment(commType);
}





int FileInterpreter::getWord( char *lWord, int MaxLn /*, FILE *IFile */ )
{
 char ch;
 int  ix = 0,err,commType;
/* Dlugosc slowa MaxLn + 1   */

 *lWord = '\0';
 while  ((ch = fgetc(IFile)) != EOF) {
  if (ch < 0) return ERR_NOASCII;
  if (!(isspace(ch) || strchr(SeparChars,ch))) {
    if ((*iswordsign)(ch)) break;
    else {
     ungetc( ch,IFile );
     if (ch == PR_Open) return OK;
     if (openComment(&commType) != OK) {
       getSyntaxErrMsg(SyntaxError = ERR_WORD_EXCP,
             &syntaxErrMsg,"%s%1d%c",FileName,lineNo,ch);
       return ERR_NUMBER_EXPC;
     }
    if ((err=omitComment(commType)) != OK) return err;
      }
  } else if (ch == '\n')  lineNo++;
 }
 do {
   if (!(*iswordsign)(ch))  break;
   if (ix < MaxLn) lWord[ix++] = ch /*tolower(ch)*/;
 } while  ((ch = fgetc(IFile)) != EOF);

 lWord[ix] = '\0';
 if (!ix && ch == EOF) return EOF;
 ungetc(ch,IFile);
 return OK;
}






int FileInterpreter::LookForNumber( double *dNo  )
{
 int   p,commType;

 while ((p = fscanf(IFile,"%lf",dNo)) != 1) {
   if (p == EOF) {
     getSyntaxErrMsg(SyntaxError=ERR_NUMBER_END,&syntaxErrMsg,"%s",FileName);
     return ERR_NUMBER_END;
   }
   if (openComment(&commType) != OK) {
     getSyntaxErrMsg(SyntaxError=ERR_NUMBER_EXPC,&syntaxErrMsg,"%s%1d",FileName,lineNo);
     return ERR_NUMBER_EXPC;
   }
   if ((p=omitComment(commType)) != OK) return p;
 }
 return OK;
}



int FileInterpreter::LookForNumber( float *dNo )
{
 int   p,commType;

 while ((p = fscanf(IFile,"%g",dNo)) != 1) {
   if (p == EOF) {
     getSyntaxErrMsg(SyntaxError=ERR_NUMBER_END,&syntaxErrMsg,"%s",FileName);
     return ERR_NUMBER_END;
   }
   if (openComment(&commType) != OK) {
     getSyntaxErrMsg(SyntaxError=ERR_NUMBER_EXPC,&syntaxErrMsg,"%s%1d",FileName,lineNo);
     return ERR_NUMBER_EXPC;
   }
   if ((p=omitComment(commType)) != OK) return p;
 }
 return OK;
}





int FileInterpreter::LookForAnyChar( char *CharSet, char *FoundChar )
{
 int   err,commType;
 char  cx;

 while ((cx = fgetc(IFile)) != EOF) {
   if (strchr(CharSet,cx))  { *FoundChar = cx;  return OK; }
   if (isspace(cx)) {
     if (cx == '\n') lineNo++;
     continue;
    }
   ungetc(cx,IFile);
   if (openComment(&commType) != OK) {
     getSyntaxErrMsg(SyntaxError=ERR_CHARS_EXPC,&syntaxErrMsg,"%s%1d%c%s",
                     FileName,lineNo,cx,CharSet);
     return ERR_CHAR_EXPC;
   }
   if ((err=omitComment(commType)) != OK)  return err;
 }
 getSyntaxErrMsg(SyntaxError=ERR_CHAR_END,&syntaxErrMsg,"%s%1d%c",FileName,lineNo,cx);
 return ERR_CHAR_END;
}




int FileInterpreter::LookForChar( char  ch  )
{
 int   err,commType;
 char  cx;

 while ((cx = fgetc(IFile)) != EOF) {
   if (cx == ch)     return OK;
   if (isspace(cx)) {
     if (cx == '\n') lineNo++;
     continue;
    }
   ungetc(cx,IFile);
   if (openComment(&commType) != OK) {
     getSyntaxErrMsg(SyntaxError=ERR_CHAR_EXPC,&syntaxErrMsg,"%s%1d%c%c",FileName,lineNo,cx,ch);
     return ERR_CHAR_EXPC;
   }
   if ((err=omitComment(commType)) != OK)  return err;
 }
 getSyntaxErrMsg(SyntaxError=ERR_CHAR_END,&syntaxErrMsg,"%s%1d%c",FileName,lineNo,ch);
 return ERR_CHAR_END;
}


int FileInterpreter::LookForWord( char *Word, int lnMax )
{
 int err;

 if ((err = getWord( Word, lnMax ))  != OK) {
    if (err == EOF) {
      getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_END,&syntaxErrMsg,"%s",FileName);
      return ERR_UNEXPC_END;
    }
    return err;
 }
 return OK;
}


int FileInterpreter::LookForKeyword( char *Word )
{
 int err;
 char  KeyWord[100];

 if ((err = LookForWord(KeyWord,99))  != OK) {
    return err;
 }
 if (strcmp(KeyWord,Word)) {
    getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_WORD,&syntaxErrMsg,"%s%i%s%s",
                       FileName,lineNo,KeyWord,Word);
    return SyntaxError;
 }
 return OK;
}



int FileInterpreter::singleSymbol( char* Symbol, int lnMax )
{
 int err;

 if ((err = LookForChar( PR_Open ))       != OK)  return err;
 if ((err = LookForWord( Symbol, lnMax )) != OK)  return err;
 if ((err = LookForChar( PR_Close ))      != OK)  return err;
 return OK;
}



int FileInterpreter::singleParam( char* Word, int Max )
{
 return singleSymbol(Word,Max);
}


int FileInterpreter::singleParam( double *number )
{
 int err;

 if (PR_Open  != NULL_CHAR) if ((err=LookForChar(PR_Open)) != OK)  return err;
 if ((err = LookForNumber( number )) != OK)  return err;
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}



int FileInterpreter::singleParam( int *number )
{
 int err;

 if (PR_Open  != NULL_CHAR) if ((err=LookForChar(PR_Open)) != OK)  return err;
 if ((err = LookForNumber( number ))  != OK)  return err;
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}



int FileInterpreter::twoParam( char* Word1, int Max1, char* Word2, int Max2)
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




int FileInterpreter::twoParam( int *number1, int *number2  )
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





int FileInterpreter::twoParam( float *number1, float *number2  )
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



int FileInterpreter::threeParam( float *num1, float *num2, float *num3  )
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
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}






int FileInterpreter::twoParam( double *number1, double *number2  )
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



int FileInterpreter::threeParam( double *num1, double *num2, double *num3  )
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
 if (PR_Close != NULL_CHAR) if ((err=LookForChar(PR_Close)) != OK) return err;
 return OK;
}










int FileInterpreter::getWordGathering( char *lWord, int MaxLn, FILE *IFile )
{
 char ch;
 int  ix = 0;

// Dlugosc slowa MaxLn + 1

 while  ((ch = fgetc(IFile)) != EOF) {
  if ((*iswordsign)(ch))   break;
  if (ch == '\n') lineNo++;
  if ((*storeChar)( ch)) {
    getSyntaxErrMsg(ERR_SHORT_BUFF,&syntaxErrMsg,"%s%1d",FileName,lineNo);
    return ERR_SHORT_BUFF;
  }
 }
 do {
   if (!(*iswordsign)(ch))  break;
   if (ix < MaxLn) lWord[ix++] = ch;
 } while  ((ch = fgetc(IFile)) != EOF);

 lWord[ix] = '\0';
 if (!ix && ch == EOF) return EOF;
 ungetc(ch,IFile);
 return OK;
}







#define  MAX_WORDS_LINE        256
#define  LINE_LENGHT           77
#define  LINE_HEADER          "***  "

void CopyKeywords( LexStruct lexTab[], int lexMax, char*  WordsLine)
{
 int  inx,TmpLen=0;
 char *Wd;

 strcpy(WordsLine,LINE_HEADER);
 for (inx=0; inx < lexMax; inx++) {
   Wd = lexTab[inx].lexWord;
   if (*Wd == '\0')  continue;
   if (strlen(WordsLine)+strlen(Wd)-TmpLen > MAX_WORDS_LINE - 8)
        { strcat(WordsLine,"...\n");  return; }
   if (strlen(WordsLine)+strlen(Wd)-TmpLen > LINE_LENGHT)
     { strcat(WordsLine,",\n");  TmpLen = strlen(WordsLine); }
   strcat(WordsLine,Wd);
   if (inx == lexMax-1) strcat(WordsLine,"."); else strcat(WordsLine,", ");
 }
}




int FileInterpreter::snxAnalis( LexStruct lexTab[],  int lexMax, AUXDATA AParam )
{
 char  lexWord[LineLength];
 int   ix,err,goOut = 0;
 char  WordsSet[MAX_WORDS_LINE];

 while ((err = getWord(lexWord,LineLength-1)) == 0) {
   for (ix=1; ix < lexMax; ix++) {
     if (!strcmp(lexWord,lexTab[ix].lexWord)) {
      if (lexTab[ix].lexFun == NULL) return OK;
      if ((err = (*lexTab[ix].lexFun)(&goOut,AParam,*this)) != OK)  return err;
      if (goOut) return OK;
      break;
     }
   }
   if (ix >= lexMax) {
     if (*lexWord == '\0') {
      *lexWord = fgetc(IFile);
      getSyntaxErrMsg(SyntaxError=ERR_WORD_EXCP,&syntaxErrMsg,
                             "%s%1d%c",FileName,lineNo,*lexWord);
      return ERR_WORD_EXCP;
     }
    CopyKeywords(lexTab,lexMax,WordsSet);
    getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_KEYWORD,&syntaxErrMsg,
           "%s%1d%s%s",FileName,lineNo,lexWord,WordsSet);
    return ERR_UNEXPC_KEYWORD;
   }
 }
 if (err == EOF)  {
   if (lexTab[0].lexFun == NULL) { goOut = BREAK_LOOP; return OK; }
   return (*lexTab[0].lexFun)(&goOut,AParam,*this);
 }
 return err;
}





int FileInterpreter::LookForSingleWord( char*  keyword, storeFunction  storeF )
{
 char  lexWord[LineLength];
 int   err;

 storeChar = storeF;
 while ((err = getWordGathering(lexWord,LineLength-1,IFile)) == 0) {
     if (!strcmp(lexWord,keyword))  break;
     else if ((err = storeWord( lexWord )) != OK) return err;
 }
 if (err == EOF) {
   getSyntaxErrMsg(ERR_UNEXPC_END,&syntaxErrMsg,"");
   return ERR_UNEXPC_END;
 }
 if (err != OK)   return err;
 if ((*storeChar)( '\0')) {
   getSyntaxErrMsg(ERR_SHORT_BUFF,&syntaxErrMsg,"");
   return ERR_SHORT_BUFF;
 }
 return OK;
}





/*
int noSpace( FILE *f )
{
 char  c;
 c = fgetc(f);  ungetc(c,f);
 return isspace(c);
}
*/



int  FileInterpreter::syntaxAnalis( int noLex, AUXDATA AParam, LexUnitFun  fEOF, ...)
{
 #define   lxMax  40
 LexStruct  lexicalTab[lxMax];
 int       ix;
 va_list   lxParam;
 if (noLex >= lxMax) {
   fprintf(stderr,"Too many arguments for the functon syntaxAnalis.");
   exit(1);
 }
 va_start(lxParam,fEOF);
 lexicalTab[0].lexWord = "";  lexicalTab[0].lexFun = fEOF;
 for (ix = 1; ix <= noLex; ix++) {
  lexicalTab[ix].lexWord = va_arg(lxParam,char*);
  lexicalTab[ix].lexFun  = va_arg(lxParam,LexUnitFun);
 }
 return snxAnalis(lexicalTab,noLex+1,AParam);
}











int FileInterpreter::startAnalis( char const  *Name,
                                  AUXDATA      AParam,
                                  int   (*startFun)(FileInterpreter &, AUXDATA)
                                )
{
  int err;

  syntaxErrMsg = NULL;
  lineNo = 1;  FileName = Name;
  if ((IFile = fopen(Name,"r")) == NULL) {
    getSyntaxErrMsg(SyntaxError=ERR_OPEN_FILE,&syntaxErrMsg,"%s",FileName);
    return ERR_OPEN_FILE;
  }
  err = startFun(*this,AParam);
  if (err != NOTFINISHED) {
    fclose(IFile);
  }
  return err;
}



int FileInterpreter::LookForNumber( int* intNo )
{
 char ch;

 while (isspace(ch = fgetc(IFile))) { if (ch == '\n') lineNo++;}
 ungetc(ch,IFile);
 switch (fscanf(IFile,"%d",intNo)) {
  case EOF : {
         getSyntaxErrMsg(SyntaxError=ERR_UNEXPC_END,&syntaxErrMsg,"%s",FileName);
         return ERR_UNEXPC_END;
       }
  case 1   : return OK;
  default  : { getSyntaxErrMsg(SyntaxError=ERR_FAIL_INT,&syntaxErrMsg,"%s%1d",FileName,lineNo);
         return ERR_FAIL_INT;
       }
 }
}








