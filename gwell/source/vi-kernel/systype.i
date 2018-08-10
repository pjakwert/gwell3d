
#define  SYSTEM   DOS
#define  WIDTH_DIGIT     5

static int baseWidth(void)
{
 return
  #if  SYSTEM == DOS
      WIDTH_DIGIT + 2
  #else
      WIDTH_DIGIT + 1
  #endif
;}
