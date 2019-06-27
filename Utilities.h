LPSTR Hack_GetAlphabet(void) ;
unsigned char * Hack_Hex(unsigned char * __lpBuffer,unsigned char * __lpszResult,int __iSize) ;
char * Hack_Char2Hex(char * __lpszHash,char * __lpszHashResult) ;
int Hack_Hex2Bin(char * __lpszHash,unsigned char * __lpszResult) ;
char * Hack_SkipLeadingAndTrailingSpaces(char *__lpszString) ;
int IsPasswordInThisAlphabet(LPSTR __lpszPassword,LPSTR __lpszAlphabet) ;
extern	char	szAlphabet[] ;
