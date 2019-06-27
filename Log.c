#include <windows.h>
#include "Log.h"

HANDLE	hLogFile ;
BOOL	bLog ;

char	szLogFileName[MAX_PATH] ;

void Log_SetFileName(LPSTR __lpszLogFileName)
{
	lstrcpy(szLogFileName,__lpszLogFileName) ;

	return ;
}

LPSTR Log_GetFileName(void)
{
	return (szLogFileName) ;
}

void Log_Stop(void)
{
	Log("*** Log Stoped ***") ;

	bLog = FALSE ;

	return ;
}

void Log_Start(void)
{
	bLog = TRUE ;
	Log("*** Log Started ***") ;

	return ;
}

void Log(LPSTR __lpszTxt)
{
	char		_szTmp[4096] ;

	char		_szTime[256] ;
	char		_szDate[256] ;

	SYSTEMTIME	_St ;

	DWORD		_dwTmp ;
	int			_iLen ;

	if(!hLogFile)	return ;
	if(!bLog)		return ;

	GetLocalTime(&_St) ;
	GetTimeFormat(LOCALE_USER_DEFAULT,TIME_FORCE24HOURFORMAT,&_St,NULL,_szTime,sizeof(_szTime)) ;
	GetDateFormat(LOCALE_USER_DEFAULT,DATE_LONGDATE,&_St,NULL,_szDate,sizeof(_szDate)) ;

	_iLen = wsprintf(_szTmp,"[%s %s] : %s\n",_szDate,_szTime,__lpszTxt) ;
	WriteFile(hLogFile,_szTmp,_iLen,&_dwTmp,NULL) ;

	return ;
}

void Log_Init(void)
{
	hLogFile = CreateFile(szLogFileName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL) ;
	if(hLogFile == INVALID_HANDLE_VALUE)
	{
		hLogFile = NULL ;
		return ;
	}

	if(hLogFile)	Log_Start() ;
	if(hLogFile)	Log("Openning Log") ;
	if(hLogFile)	Log("Log Ready") ;

	return ;
}

void Log_Exit(void)
{
	if(!hLogFile)	return ;

	if(!bLog)	Log_Start() ;
	Log("Closing Log file") ;
	Log_Stop() ;
	FlushFileBuffers(hLogFile) ;
	CloseHandle(hLogFile) ;
	hLogFile = NULL ;

	return ;
}
