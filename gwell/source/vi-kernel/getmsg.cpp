/*
 * File:	getmsg.cpp
 * Purpose:     Komunikaty dla systemu VIONA
 * Author:	Bogdan Kreczmer
 * Created:	Kwiecien 1995
 * Updated:     2003
 * Copyright:	(c) 1995, Bogdan Kreczmer
 */


#ifdef __GNUG__
#pragma implementation
#endif




/***************************************************************************
 *                                                                         *
 *   ## - znake te poprzedzaj oznaczenie parametru.                       *
 *                                                                         *
 ***************************************************************************/

/*char  *ErrMessage;  */
int  errGetMsg = 0;

#include "getmsg.h"
#include "readfig.e"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#include "systype.i"
#include "system.e"



#define  ErrBaseMsg  100
#define  ErrFormatMsgE    ErrBaseMsg + 1
#define  ErrFormatMsgF    ErrBaseMsg + 2
#define  ERR_BAD_FORMAT   ErrBaseMsg + 3


#define  PrefParam   "##"





int catstrc( char *Sum, int Max, char c)
{
	int i;

	if ((i = strlen(Sum)) >= Max-1) return 0;
	Sum[i] = c;  Sum[i+1] = '\0';
	return 1;
}




char *strglu( char **sPtr, char const *s2 )
{
	char  *sbuf;
	size_t    lnS = 1;
	if (*sPtr != NULL) lnS += strlen(*sPtr);
	if (s2   != NULL) lnS += strlen(s2);
		 else return *sPtr;
	if (lnS == 1)  return *sPtr;
	sbuf = ALLOC_OBJ_STR(lnS);
  *sbuf = '\0';
	if (*sPtr != NULL) strcat(sbuf,*sPtr);
	if (s2    != NULL) strcat(sbuf,s2);
	RELEASE(*sPtr);
	return *sPtr = sbuf;
}





int  replacePar( char **ErrMsgPtr, char *bMsg, int ErrNo)
{
 char sNo[10],sPar[10], *bErrMsg, *bErrF = *ErrMsgPtr,*bErrL;
 int  i = 0,u;
 size_t lnPar;
 int  TotalLen, ParamLen;
 
 strcpy(sPar,PrefParam);
 sprintf(sNo, "%i", ErrNo);

 strcat(sPar,sNo);
 while ((bErrF = strstr(bErrF,sPar)) != NULL) { i++; bErrF++;}
 if (!i) return 0;
 lnPar = strlen(sPar);
 TotalLen = (int) strlen(*ErrMsgPtr);
 ParamLen = (int) strlen(bMsg);
 bErrMsg = ALLOC_OBJ_STR(TotalLen+i*(ParamLen-int(lnPar))+1);
 if (bErrMsg == NULL) return 0;
 u = i;  bErrF = *ErrMsgPtr;
 *bErrMsg = '\0';
 for (; i > 0; i--) {
		bErrL = strstr(bErrF,sPar);  strncat(bErrMsg,bErrF,bErrL-bErrF);
		strcat(bErrMsg,bMsg);
		bErrF = bErrL+lnPar;
 }
 strcat(bErrMsg,bErrF);
 if (*ErrMsgPtr != NULL) RELEASE(*ErrMsgPtr);
 *ErrMsgPtr = bErrMsg;
 return u;
}




int cpyFormatUnit( char const **ptrFormat, int maxUnit, char *FUnit )
{
	int i=0,wasLetter = 0;

	*FUnit = '\0';
	while ((*ptrFormat = strchr(*ptrFormat,'%')) != NULL) {
	 if (*++*ptrFormat == '%') { ++*ptrFormat;  continue; }
	 *FUnit++ = '%';
	 do { *FUnit++ = *(*ptrFormat)++;
	if (maxUnit <= ++i) {return 0;}
	if (wasLetter) { if (!isalpha(**ptrFormat)) break; }
		else wasLetter = isalpha(**ptrFormat);
	 }
	 while (**ptrFormat != '%' && **ptrFormat != '\0');
	 *FUnit = '\0';
	 return 1;
	}
	return 0;
}


            

void  ReleaseStr( char **pStr)
{  delete [] (*pStr);  *pStr = NULL; }

// Transformuje FMsg w nowy lancuch i zwalnia FMsg !!!!
// Zwracany lancuch jest alokowany.
char*   KernelTransformMsg( char const * const  ErrMsg, 
                            char const         *format,  
                            va_list             APtr
                          )
{
#define  MAX_BUFF   2048
 char   bFormat[100];
 char   bMsg[MAX_BUFF+1];
 char  *FMsg =  ALLOC_OBJ_STR(strlen(ErrMsg)+1);
 int    NoV=1;

 strcpy(FMsg,ErrMsg);
 
 while (cpyFormatUnit(&format,100,bFormat)) {
   switch (*(format-1)) {
    case 's': vsprintf(bMsg,bFormat,APtr);
              (void) va_arg(APtr,char *);      
              break;
    case 'd':;
    case 'i': 
             switch (*(format-2)) {
	       case 'h': // `short int' is promoted to `int' when 
	                 //  passed through `...'
                         vsprintf(bMsg,bFormat,APtr);
                         (void) va_arg(APtr, int);  
                         break;
               default : vsprintf(bMsg,bFormat,APtr);
                         (void) va_arg(APtr, int); 
                         break;
             }
   break;
    case 'o':;
    case 'u':;
    case 'x':;
    case 'X':
     switch (*(format-2)) {
      case 'h': vsprintf(bMsg,bFormat,APtr);
                (void) va_arg(APtr, unsigned int);  
                break;

      case 'l': vsprintf(bMsg,bFormat,APtr);
                (void) va_arg(APtr, unsigned long  int);   
                break;

      default : vsprintf(bMsg,bFormat,APtr);
                (void) va_arg(APtr, unsigned int);         
                break;
      }
      break;
    case 'f':;
    case 'e':;
    case 'g':;
    case 'E':;
    case 'G':
      switch (*(format-2)) {
        case 'L': vsprintf(bMsg,bFormat,APtr);
                  (void) va_arg(APtr, long  double); 
                  break;

        default : vsprintf(bMsg,bFormat,APtr);
                  (void) va_arg(APtr, double);       
                  break;
      }
      break;
    case 'c': vsprintf(bMsg,bFormat,APtr);
              (void) va_arg(APtr, int);
              break;

    case 'p': switch (*(format-2)) {
               default: vsprintf(bMsg,bFormat,APtr);
                        (void) va_arg(APtr, void*);         
                        break;
              }
              break;

    default : errGetMsg = ERR_BAD_FORMAT;
              return FMsg;
   }
   replacePar( &FMsg,bMsg,NoV++);
  }

 return FMsg;
}




char*  TransformMsg( char* Msg, char const * format, ... )
{
 char *s;
 va_list  AList;

 va_start(AList,format);
 s = KernelTransformMsg( Msg,format,AList);
 va_end(AList);
 return s;
}







int  ReadMsg( char const *nameFile, int no, char **ptrMsg )
{
 FILE *msgFile;
 int  maxNo,i;
 long  bNo=0, eNo=0;
 char *r;


 if ((msgFile = fopen(nameFile,"r")) == NULL) return ERR_CANNOT_OPEN;
 if (fscanf(msgFile,"%d",&maxNo) != 1) return ERR_READ_FILE;
 if (no > maxNo)  return ERR_NOMSG;
 if (fseek(msgFile,(long)(baseWidth()*(no+1)),SEEK_SET)) return ERR_READ_FILE;
 if (fscanf(msgFile,"%li",&bNo) != 1) return ERR_READ_FILE;
 if (fscanf(msgFile,"%li",&eNo) != 1) return ERR_READ_FILE;
 eNo -= bNo;
 if ((r = *ptrMsg = ALLOC_OBJ_STR(eNo+1)) == NULL)
       return ERR_NO_MEMORY;

 if (eNo != 0) {
 if (fseek(msgFile,bNo,SEEK_SET)) return ERR_READ_FILE;

  for (i = 0; i < eNo; i++) {
   if ((*r = (char) fgetc(msgFile)) == EOF) return ERR_FILE_END;
    r++;
  }
 }
 *r = '\0';
 fclose(msgFile);
 return OK;
}




char const *GetVionaErrMsg(int Err)
{
  switch (Err) {
    case ERR_NODE_IN_MORE_FACES: return
       "In a library `##1' in a figure `##5' was found an edge no ##2\n"
       "which belongs to a face ##3 and ##4 along the left side.";
  }
  return NULL;
}


char*  KernelFGetMsg( int         NoErr, 
                      char const *fileName, 
                      char const *format, 
                      va_list     AList 
                    )
{
 char *Msg,*s;

 s = ((errGetMsg = ReadMsg(fileName,NoErr,&Msg)) != 0) ?  
                         NULL : KernelTransformMsg( Msg,format,AList);
 return s;
}






  // Nie nalezy juz z tego korzystac.
char*  FGetMsg( int NoErr, char const * fileName, char const * format, ... )
{
 char *Msg;
 va_list  AList;

 va_start(AList,format);
 Msg = KernelFGetMsg(NoErr,fileName,format,AList);
 va_end(AList);
 return Msg;
}





std::string  SGetMsg( int NoErr, char const * format, ... )
{
 char       *Msg;
 char const *ErrMsg = GetVionaErrMsg(NoErr);

 if (!ErrMsg) return 0L;

 std::string   StrMsg;
 va_list  AList;
 
 
 va_start(AList,format);
 Msg = KernelTransformMsg( ErrMsg,format,AList);
 va_end(AList);
 std::string str = Msg;
 RELEASE(Msg);

 return str;
}


