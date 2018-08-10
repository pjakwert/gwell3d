/*
 * File:	synyax.h
 * Purpose: Analizator syntaktyczny w  wxICARS
 * Author:	Bogdan Kreczmer
 * Created:	Kwiecien 1995
 * Updated:
 * Copyright:	(c) 1995, Bogdan Kreczmer
 */

#ifndef SYNTAX_H
#define SYNTAX_H

/* sccsid[] = "%W% %G%" */

#ifdef __GNUG__
#pragma interface
#endif

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif
#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif


class FileInterpreter;

#define    AUXDATA        void*
#define    NOTFINISHED      -1
typedef int (*LexCharFun)(int);
typedef int (*LexUnitFun)(int *, AUXDATA, FileInterpreter &);
typedef int (*storeFunction)(char);


#define  QUESTION(x)  if ((err = x) != OK) return err;


#define FI_START_FUN_HEADER(FunctionName) \
       static int FunctionName(FileInterpreter &FI, AUXDATA AParam)

#define EFI_START_FUN_HEADER(FunctionName) \
        int FunctionName(FileInterpreter &FI, AUXDATA AParam)


#define FI_FUNCTION_HEADER(FunctionName) \
    static int FunctionName( int *LoopBrk, AUXDATA AParam, FileInterpreter &FI)

#define EFI_FUNCTION_HEADER(FunctionName) \
    int FunctionName( int *LoopBrk, AUXDATA AParam, FileInterpreter &FI)


#define FI_FUNCTION_HEADER_011(FunctionName) \
    static int FunctionName( int *, AUXDATA AParam, FileInterpreter &FI)

#define EX_FUNCTION_HEADER_011(FunctionName) \
           int FunctionName( int *, AUXDATA AParam, FileInterpreter &FI)

#define FI_FUNCTION_HEADER_010(FunctionName) \
    static int FunctionName( int *, AUXDATA AParam, FileInterpreter &)

#define FI_FUNCTION_HEADER_001(FunctionName) \
    static int FunctionName( int *, AUXDATA, FileInterpreter &FI)

#define FI_FUNCTION_HEADER_000(FunctionName) \
    static int FunctionName( int *, AUXDATA, FileInterpreter &)

#define FI_FUNCTION_HEADER_101(FunctionName) \
    static int FunctionName( int *LoopBrk, AUXDATA, FileInterpreter &FI)

#define FI_FUNCTION_HEADER_111(FunctionName) \
    static int FunctionName( int *LoopBrk, AUXDATA AParam, FileInterpreter &FI)

#define FI_FUNCTION_HEADER_100(FunctionName) \
    static int FunctionName( int *LoopBrk, AUXDATA, FileInterpreter &)

#define FI_FUNCTION_HEADER_110(FunctionName) \
    static int FunctionName( int *LoopBrk, AUXDATA  AParam, FileInterpreter &)



#define EFI_FUNCTION_HEADER_011(FunctionName) \
    int FunctionName( int *, AUXDATA AParam, FileInterpreter &FI)

#define OK            0
#define BREAK_LOOP    1
#define CONTINUE_LOOP 0

#define  NULL_CHAR   ' '



typedef struct {
      char*       lexWord;
      LexUnitFun  lexFun;
    }  LexStruct;


class  FileInterpreter {

        FILE   *IFile;
        char    PR_Open;
        char    PR_Close;
        char    PR_Separater;
        char   *C_Open;
        char   *C_Close;
        char   *C_Line;
        int     SyntaxError;
        char   *SeparChars;


        int  passComments(void);
        int  openComment(int *);
        int  omitComment(int);
        int  getWordGathering( char *lWord, int MaxLn, FILE *IFile );
        int  snxAnalis( LexStruct lexTab[],  int lexMax, AUXDATA aParam );

       public:
        char const  *FileName;
        char        *syntaxErrMsg;
        int          lineNo;
        void        *AuxParam;

        int  singleSymbol( char* Symbol, int lnMax );
        int  LookForSingleWord( char*  keyword, storeFunction storeF );
        int  LookForNumber( int* intNo );
        int  LookForNumber( float  *no );
        int  LookForNumber( double *no );
        int  LookForChar( char  ch );
        int  LookForWord( char *Word, int lnMax );
        int  LookForKeyword( char *Word );
        int  LookForAnyChar( char *CharsSet, char *FoundChar );
        int  syntaxAnalis( int noLex, AUXDATA AParam, LexUnitFun  fEOF, ...);
        int  startAnalis( char const  *Name, 
                          AUXDATA      AParam, 
                          int (*startFun)(FileInterpreter &, AUXDATA) 
                        );
        int  singleParam( char* Word, int Max );
        int  singleParam( double *number );
        int  singleParam( int    *);
        int  twoParam( char* Word1, int Max1, char* Word2, int Max2);
        int  twoParam( float *number1, float *number2  );
        int  twoParam( double *number1, double *number2  );
        int  twoParam( int *,  int *);
        int  threeParam( float *, float *, float *);
        int  threeParam( double *, double *, double *);
        int  getWord( char *lWord, int MaxLn  );
        void SetSeparaters(char *s){ SeparChars = s; }
        void SetParamEnvironment(char Op, char Sp, char Cl)
                        { PR_Open = Op;  PR_Separater = Sp;  PR_Close = Cl; }
        void  SetFileMsg( char *FName) { FileName = FName; }
        char const *GetFileMsg() const { return FileName; }
        void ResetAnalis(void){ if (IFile != NULL) fclose(IFile);
                                lineNo = SyntaxError = 0;
                                if (syntaxErrMsg != NULL) free(syntaxErrMsg);
                              };
        void Close() { fclose(IFile);}
        int  Ungetchar(char c);
        FileInterpreter(void){ lineNo = SyntaxError = 0;
                               syntaxErrMsg = "\0";
                               FileName = "syntax.msg";  IFile = NULL;
                               SeparChars = ";";
                               PR_Open = '{';  PR_Close = '}';
                               PR_Separater = ',';
                               C_Open = "/*";
                               C_Close = "*/";
                               C_Line = "//";
                               AuxParam = NULL;
                             };
    };


#endif
