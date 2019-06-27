#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

typedef int (*Fn_Insert)(LPVOID __lpDb,LPSTR __lpszString) ;

typedef	struct
{
	unsigned int	iKeyCode ;
	unsigned int	iHashNumberOfBits ;
	LPSTR			lpszHashSize ;
} HASHSIZE, *LPHASHSIZE ;

typedef	struct
{
	unsigned int	iAlphabet ;
	unsigned int	iAlphabetLength ;
	unsigned int	iNumAlphabets ;
	LPSTR			lpszAlphabet1 ;
	LPSTR			lpszAlphabet2 ;
	LPSTR			lpszAlphabet3 ;
	LPSTR			lpszAlphabet4 ;
	LPSTR			lpszAlphabet5 ;
	LPSTR			lpszAlphabet6 ;
	LPSTR			lpszAlphabet7 ;
	LPSTR			lpszAlphabet8 ;
	LPSTR			lpszAlphabet9 ;
	LPSTR			lpszAlphabet10 ;
	LPSTR			lpszAlphabet11 ;
	LPSTR			lpszAlphabet12 ;
	char			szTitle[256] ;
	char			szAlphabet[256] ;
} ALPHABET, *LPALPHABET ;

typedef	struct
{
	unsigned int	iKeyCode ;
	unsigned int	iPasswordLength ;
	char			szPasswordLength[4] ;
} PASSWORD, *LPPASSWORD ;

typedef	struct
{
	Fn_Insert		Insert ;
	sqlite3			*Db ;
	sqlite3			*DbUnique ;
	sqlite3			*DbColHash ;
	sqlite3			*DbColPsw ;
	LPVOID			lpImport ;
	LPBYTE			lpImportBuffer ;
	LPSTR			lpszStringToHash ;
	HINSTANCE		hThread ;
	HWND			hWnd ;
	unsigned int	iRound ;
	unsigned int	iThreadMode ;
	unsigned int	iThreadAction ;
	unsigned int	iRecNum ;
	unsigned int	iStringLength ;
	unsigned int	iHashNumberOfBytes ;
	unsigned int	iHashNumberOfBits ;
	unsigned int	iPasswordLength ;
	unsigned int	iAlgorithme ;
	unsigned int	iSecure ;
	unsigned int	iCount ;
	ALPHABET		Alphabet ;
	unsigned char	szAlgorithme[128] ;
} DB_GEN, *LPDB_GEN ;

typedef	struct
{
	unsigned int	iKeyCode ;
	LPSTR			lpszAlgorithme ;
	unsigned int	iHashNumberOfBytes ;
	unsigned int	iHashNumberOfBits ;
	Fn_Insert		Insert ;
	sqlite3			*Db ;
	LPVOID			lpUnUsed ;
} DB_INFOS, *LPDB_INFOS ;
#endif // __STRUCTURES_H__
