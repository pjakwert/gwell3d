#ifndef SYNTAX_NEW_E
#define SYNTAX_NEW_E

#define OK                         0
#define ERR_NOT_EMPTY             20
  //  No enough memory
#define  ERR_NO_MEMORY            21
  //  Error while a file is read or the statement fseek is executed.
#define  ERR_READ_FILE            22
  // A file can not be opened
#define  ERR_CANNOT_OPEN          62

//  An end of a file is met while a characrer is expected to be read.
#define  ERR_FILE_END             24

// A message is expcted to be read by f. readMsg but there isn't a message
//  in a text file.
#define  ERR_NOMSG                25
#define  ERR_NOT_ENOGHT_MEMORY    41




#define ERR_COMMENT_END           1
#define ERR_NUMBER_END            2
#define ERR_NUMBER_EXPC           3
#define ERR_UNEXPC_END            4
#define ERR_UNEXPC_UNIT           5
#define ERR_CHAR_END              6
#define ERR_CHAR_EXPC             7
#define ERR_READ                  8
#define ERR_OPEN_FILE             9
#define ERR_SHORT_BUFF           10
#define ERR_FAIL_INT             11
#define ERR_CHARS_EXPC           12
#define ERR_WORD_EXCP            13
//
#define ERR_UNEXPC_KEYWORD         51
#define ERR_NOASCII                52
#define ERR_UNEXPC_WORD            53
#define ERR_UNEXPC_KEYWORD1        54
#define ERR_FACE_VTX_TOO_MUCH      60
#define ERR_NO_MEMORY_FOR_FACEVTX  61
#define ERR_FIRST_VTX_NUM_ECEEDS   62
#define ERR_SECOND_VTX_NUM_ECEEDS  63
#define ERR_NO_MEMORY_FOR_EDGEFIG  64


#endif
