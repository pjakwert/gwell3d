#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef diablo
#include <sys/types.h>
#endif


char const *skipString( char const *str )
{
  while (*str && isspace(*str)) str++;
  while (*str && !isspace(*str)) str++;
  return str;
}

char const *SkipFrontSpace( char const * str )
{
 for ( ; isspace(*str) && *str;  str++);
 return str;
}


char *RemoveBegSpace( char * str )
{
 return strcpy(str,(char*)SkipFrontSpace(str));
}


char  *RemoveFrontSpace( char * str)
{
  return (char *)RemoveBegSpace(str);
}

char *RemoveEndSpace( char * const str )
{
 char *s;

 for ( s=str+strlen(str)-1; s != str && isspace(*s);  s--);
 *(s+1) = 0;
 return str;
}


char *RemoveSpace( char  * const str )
{
 return (char *)RemoveBegSpace(RemoveEndSpace(str));
}



char *strchrback(char *str, char c)
{
  char *s;
  
  if (!str) return NULL;
  if (!*str)  return NULL;
  s = str+strlen(str)-1;
  if (*s == c) return s;
  while (++s != str) {
    if (*s == c) return s;
  }
  return *s == c ? s : NULL;
}




static int selectFiles(const struct dirent *pDir)
{
#ifdef merix
  return pDir->d_type == DT_REG;
#endif
#ifdef diablo
  return 0;
#endif
  return 0;
}



#ifdef diablo
int alphasort( struct dirent **pDir1,  struct dirent **pDir2 )
{
  return strcmp((*pDir1)->d_name,(*pDir2)->d_name);
}
#endif


#define MAX_FILENAME 300

int findCopyLastNumber(char const *TaskDirName, char const* FileName)
{
#ifdef SCSANDIR
  struct dirent **pFilesList;
  int             N,  Max = -10, Len = strlen(FileName);
  float           FNum;
  char const     *s;
  

  N = scandir(TaskDirName, &pFilesList, selectFiles, alphasort);
  if (N < 0) return -100;
  while (N--) {
    s = pFilesList[N]->d_name;
    if (strstr(s,FileName) == s) {
      if (s[Len] == '.') {
        sscanf(s+Len+1,"%f",&FNum);
      } else FNum = -1;
      if (FNum > Max) Max = (int)FNum;
    }
    free(pFilesList[N]);
  }
  free(pFilesList);

  return Max;
#endif

  int             Max = -10, Len = strlen(FileName);
  float           FNum;
  struct dirent  *pDirData;
  struct stat     FileData;
  char            FullFileName[MAX_FILENAME+1];
  DIR            *pDir;

  if (!(pDir = opendir(TaskDirName))) return -100;
  while ((pDirData = readdir(pDir))) {
    if (strstr(pDirData->d_name,FileName) != pDirData->d_name) continue;
    sprintf(FullFileName,"%s%s",TaskDirName,pDirData->d_name);
    if (stat(FullFileName,&FileData)) continue;
    if (!(S_ISREG(FileData.st_mode))) continue;
    if (pDirData->d_name[Len] == '.') {
       if (sscanf(pDirData->d_name+Len+1,"%f",&FNum) != 1) FNum = -1;
    } else FNum = -1;
    if (FNum > Max) Max = (int)FNum;
  }

  closedir(pDir);

  return Max;
}

