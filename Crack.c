#include "Crack.h"
#include "windowsx.h"

int ValidPassword(LPSTR __lpszFinalPassword,LPALPHABET __lpAlphabet)
{
	if(__lpAlphabet->iNumAlphabets < 2)
		return (0) ;

	if(__lpAlphabet->lpszAlphabet1)		if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet1))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet2)		if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet2))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet3)		if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet3))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet4)		if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet4))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet5)		if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet5))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet6)		if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet6))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet7)		if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet7))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet8)		if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet8))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet9)		if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet9))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet10)	if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet10))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet11)	if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet11))	return (TRUE) ;
	if(__lpAlphabet->lpszAlphabet12)	if(IsPasswordInThisAlphabet(__lpszFinalPassword,__lpAlphabet->lpszAlphabet12))	return (TRUE) ;

	return (0) ;
}

HWND Crack_Init(LPDB_GEN __lpDb,unsigned int __iPasswordLength,LPSTR __lpszPassword)
{
	register	int		_iControl ;
	register	int		_i ;
				HWND	_hControl ;
				char	_szTmp[1024] ;

	Message(__lpDb->hWnd,szPleaseWait) ;

	__lpDb->lpszStringToHash = __lpszPassword ;
	__lpDb->iPasswordLength = __iPasswordLength ;
	__lpDb->iStringLength = __iPasswordLength ;
/*
	wsprintf(_szTmp,"Alphabet #%d",__lpDb->Alphabet.iAlphabet) ;
	SetDlgItemText(__lpDb->hWnd,IDC_STATIC_05,_szTmp) ;

	wsprintf(_szTmp,"Alphabet Size : %d chars",__lpDb->Alphabet.iAlphabetLength) ;
	SetDlgItemText(__lpDb->hWnd,IDC_STATIC_06,_szTmp) ;

	wsprintf(_szTmp,"Number of Subsets : %d",__lpDb->Alphabet.iNumAlphabets) ;
	SetDlgItemText(__lpDb->hWnd,IDC_STATIC_07,_szTmp) ;
*/
	__stosq((unsigned long long *) __lpDb->lpszStringToHash,0,(MAX_LEN_PASSWORD * 2) / 8) ;

	_iControl = IDC_PROGRESS_01 ;

	for(_i = 0 ; _i < MAX_LEN_PASSWORD ; _i++)
	{
		_hControl = GetDlgItem(__lpDb->hWnd,_iControl) ;

		SendMessage(_hControl,PBM_SETRANGE,0,MAKELPARAM(0,__lpDb->Alphabet.iAlphabetLength)) ;
		SendMessage(_hControl,PBM_SETPOS,0,0) ;
		SendMessage(_hControl,PBM_SETSTEP,1,0) ;
		SendMessage(_hControl,PBM_SETBARCOLOR,0,dwColors[_i]) ;
		SendMessage(_hControl,PBM_SETBKCOLOR,0,0) ;

		_iControl++ ;
	}

	wsprintf(_szTmp,"Generating Passwords (Length = %d)",__lpDb->iPasswordLength) ;
	Log(_szTmp) ;
	Message(__lpDb->hWnd,_szTmp) ;

	return (__lpDb->hWnd) ;
}

int FinishTask(register LPDB_GEN __lpDb)
{
				char	_szTmp[1024] ;
	register	LPSTR	_lpszTmp = _szTmp ;

	ShowWindow(GetDlgItem(__lpDb->hWnd,IDC_STOP),SW_HIDE) ;

	ShowWindow(GetDlgItem(__lpDb->hWnd,IDC_BACKGROUND),SW_HIDE) ;
	ShowWindow(GetDlgItem(__lpDb->hWnd,IDC_FOREGROUND),SW_HIDE) ;

	if(__lpDb->iPasswordLength < 3)
	{
		sqlite3_exec(__lpDb->Db,szEndTransaction,0,0,NULL) ;
		sqlite3_db_release_memory(__lpDb->Db) ;

		Message(__lpDb->hWnd,szVacuum) ;
		sqlite3_exec(__lpDb->Db,szSQLiteVacuum,0,0,NULL) ;

		sqlite3_close(__lpDb->Db) ;
	}

	wsprintf(_lpszTmp,"%s(%d), %d signs Finished",	__lpDb->szAlgorithme,
													__lpDb->iPasswordLength,
													__lpDb->Alphabet.iAlphabetLength) ;
	Log(_lpszTmp) ;

	Message(__lpDb->hWnd,szReady) ;

	ShowWindow(GetDlgItem(__lpDb->hWnd,IDOK),SW_SHOW) ;
	ShowWindow(GetDlgItem(__lpDb->hWnd,IDCANCEL),SW_SHOW) ;

	CloseHandle(__lpDb->hThread) ;
	VirtualFree(__lpDb,0,MEM_RELEASE) ;

	ExitThread(TRUE) ;

	return (TRUE) ;
}

int Round_Terminate(register LPDB_GEN __lpDb)
{
				char	_szTmp[256] ;
	register	LPSTR	_lpszTmp = _szTmp ;
	register	int		_iTmp ;

	sqlite3_exec(__lpDb->Db,szEndTransaction,0,0,NULL) ;
	sqlite3_exec(__lpDb->Db,szSQLiteVacuum,0,0,NULL) ;
	sqlite3_db_release_memory(__lpDb->Db) ;
	sqlite3_close(__lpDb->Db) ;

	_iTmp = __lpDb->iCount % 8 ;
	__lpDb->iCount++ ;

	if(_iTmp == 0)
		__lpDb->iRound++ ;

	if(!Db_Round_Open(__lpDb,__lpDb->iPasswordLength,__lpDb->iHashNumberOfBits))
	{
		CloseHandle(__lpDb->hThread) ;
		VirtualFree(__lpDb,0,MEM_RELEASE) ;
		ExitThread(TRUE) ;
		return (FALSE) ;
	}

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	if(__lpDb->iRound > 1)	wsprintf(_lpszTmp,"Round %lu started!",__lpDb->iRound) ;
	else					lstrcpy(_lpszTmp,"Round 1 finished!") ;

	Message(__lpDb->hWnd,_lpszTmp) ;

	return (TRUE) ;
}

int Round_Finish(register LPDB_GEN __lpDb)
{
	sqlite3_exec(__lpDb->Db,szEndTransaction,0,0,NULL) ;
	sqlite3_exec(__lpDb->Db,szSQLiteVacuum,0,0,NULL) ;
	sqlite3_db_release_memory(__lpDb->Db) ;
	sqlite3_close(__lpDb->Db) ;

	return (TRUE) ;
}

int Crack_HandleMutex(LPDB_GEN __lpDb)
{
	DWORD	_dwWaitResult ;
	int		_iResult ;

	_dwWaitResult = WaitForSingleObject(hMutex,PSW_WAIT_TIMEOUT) ;
	if(_dwWaitResult != WAIT_OBJECT_0)
	{
		ReleaseMutex(hMutex) ;
		return (FALSE) ;
	}

	_iResult = FALSE ;

	if(__lpDb->iThreadAction == THREAD_ACTION_STOPPED)
	{
		__lpDb->iThreadMode &= ~THREAD_MODE_RUNNING ;
		__lpDb->iThreadMode |= THREAD_MODE_STOPPED ;

		if(__lpDb->iThreadMode & THREAD_MODE_BACKGROUND)
			SetThreadPriority(__lpDb->hThread,THREAD_MODE_BACKGROUND_END) ;

		Round_Finish(__lpDb) ;

		return (FinishTask(__lpDb)) ;
	}
	else
	{
		if(__lpDb->iThreadAction == THREAD_ACTION_FOREGROUND)
		{
			if(__lpDb->iThreadMode & THREAD_MODE_BACKGROUND)
			{
				__lpDb->iThreadMode &= ~THREAD_MODE_BACKGROUND ;
				__lpDb->iThreadMode |= THREAD_MODE_FOREGROUND ;

				SetThreadPriority(__lpDb->hThread,THREAD_MODE_BACKGROUND_END) ;
				SetThreadPriority(__lpDb->hThread,THREAD_PRIORITY_ABOVE_NORMAL) ;
			}
			else
			{
				if(__lpDb->iThreadAction == THREAD_ACTION_BACKGROUND)
				{
					if(__lpDb->iThreadMode & THREAD_MODE_FOREGROUND)
					{
						__lpDb->iThreadMode &= ~THREAD_ACTION_FOREGROUND ;
						__lpDb->iThreadMode |= THREAD_MODE_BACKGROUND ;

						SetThreadPriority(__lpDb->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
					}
				}
			}
		}
	}

	if(__lpDb)	__lpDb->iThreadAction = 0 ;

	ReleaseMutex(hMutex) ;

	return (_iResult) ;
}

int Crack_CreatePsw_01(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = _szPassword ;
	register	LPSTR	_lpszAlphabet_0 ;

	Crack_Init(__lpDb,1,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;

	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	while(*_lpszAlphabet_0)
	{
		*_lpszPassword = *_lpszAlphabet_0++ ;
		__lpDb->Insert(__lpDb,_szPassword) ;
		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	sqlite3_exec(__lpDb->Db,szEndTransaction,0,0,NULL) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_02(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

				LPSTR	_lpszAlphabet_0 ;
	register	LPSTR	_lpszAlphabet_1 ;

	Crack_Init(__lpDb,2,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;

	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;

			if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
				__lpDb->Insert(__lpDb,_szPassword) ;

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	sqlite3_exec(__lpDb->Db,szEndTransaction,0,0,NULL) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_03(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[2] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2 ;
	register	LPSTR	_lpszFinalPassword ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	_lpszFinalPassword = _szPassword ;
	Crack_Init(__lpDb,3,_lpszFinalPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

			while(*_lpszAlphabet_2)
			{
				*_lpszPassword = *_lpszAlphabet_2++ ;

				if(!ValidPassword(_lpszFinalPassword,&__lpDb->Alphabet))
				{
					__lpDb->Insert(__lpDb,_lpszFinalPassword) ;

					if(_iCount >= MAX_RECORDS_STORED)
					{
						if(!Round_Terminate(__lpDb))
							return (FinishTask(__lpDb)) ;

						_iCount = 0 ;

						sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
					}

					_iCount++ ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_04(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[3] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2 ;
				LPSTR	_lpszAlphabet_3 ;
	register	LPSTR	_lpszFinalPassword ;
				int		_iRound, _iCount, _bRes ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;
	_bRes = 0 ;

	_lpszFinalPassword = _szPassword ;
	Crack_Init(__lpDb,4,_lpszFinalPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;

	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		*_lpszFinalPassword = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			*(_lpszFinalPassword + 1) = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;

			if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				*(_lpszFinalPassword + 2) = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					*_lpszPassword = *_lpszAlphabet_3++ ;

					if(!ValidPassword(_lpszFinalPassword,&__lpDb->Alphabet))
					{
						__lpDb->Insert(__lpDb,_lpszFinalPassword) ;

						if(_iCount >= MAX_RECORDS_STORED)
						{
							if(!Round_Terminate(__lpDb))
								return (FinishTask(__lpDb)) ;

							_iCount = 0 ;
							sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
						}

						_iCount++ ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_05(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[4] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2 ;
				LPSTR	_lpszAlphabet_3, _lpszAlphabet_4 ;
	register	LPSTR	_lpszFinalPassword ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	_lpszFinalPassword = _szPassword ;
	Crack_Init(__lpDb,5,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;
	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		*_lpszFinalPassword = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			*(_lpszFinalPassword + 1) = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

				*(_lpszFinalPassword + 2) = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					*(_lpszFinalPassword + 3) = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						*_lpszPassword = *_lpszAlphabet_4++ ;

						if(!ValidPassword(_lpszFinalPassword,&__lpDb->Alphabet))
						{
							__lpDb->Insert(__lpDb,_lpszFinalPassword) ;

							if(_iCount >= MAX_RECORDS_STORED)
							{
								if(!Round_Terminate(__lpDb))
									return (FinishTask(__lpDb)) ;

								_iCount = 0 ;

								sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
							}

							_iCount++ ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_06(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[5] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2, _lpszAlphabet_3 ;
				LPSTR	_lpszAlphabet_4 ;
	register	LPSTR	_lpszAlphabet_5 ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	Crack_Init(__lpDb,6,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;
	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							*_lpszPassword = *_lpszAlphabet_5++ ;

							if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
							{
								__lpDb->Insert(__lpDb,_szPassword) ;

								if(_iCount >= MAX_RECORDS_STORED)
								{
									if(!Round_Terminate(__lpDb))
										return (FinishTask(__lpDb)) ;

									_iCount = 0 ;

									sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
								}

								_iCount++ ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_07(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[6] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2, _lpszAlphabet_3 ;
				LPSTR	_lpszAlphabet_4, _lpszAlphabet_5 ;
	register	LPSTR	_lpszAlphabet_6 ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	Crack_Init(__lpDb,7,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;
	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							_szPassword[5] = *_lpszAlphabet_5++ ;
							_lpszAlphabet_6 = __lpDb->Alphabet.szAlphabet ;

							while(*_lpszAlphabet_6)
							{
								*_lpszPassword = *_lpszAlphabet_6++ ;

								if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
								{
									__lpDb->Insert(__lpDb,_szPassword) ;

									if(_iCount >= MAX_RECORDS_STORED)
									{
										if(!Round_Terminate(__lpDb))
											return (FinishTask(__lpDb)) ;

										_iCount = 0 ;

										sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
									}

									_iCount++ ;
								}

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_STEPIT,0,0) ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_08(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[7] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2, _lpszAlphabet_3 ;
				LPSTR	_lpszAlphabet_4, _lpszAlphabet_5, _lpszAlphabet_6 ;
	register	LPSTR	_lpszAlphabet_7 ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	Crack_Init(__lpDb,8,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;

	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

							_szPassword[5] = *_lpszAlphabet_5++ ;
							_lpszAlphabet_6 = __lpDb->Alphabet.szAlphabet ;

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_SETPOS,0,0) ;

							while(*_lpszAlphabet_6)
							{
								_szPassword[6] = *_lpszAlphabet_6++ ;
								_lpszAlphabet_7 = __lpDb->Alphabet.szAlphabet ;

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_SETPOS,0,0) ;

								while(*_lpszAlphabet_7)
								{
									*_lpszPassword = *_lpszAlphabet_7++ ;

									if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
									{
										__lpDb->Insert(__lpDb,_szPassword) ;

										if(_iCount >= MAX_RECORDS_STORED)
										{
											if(!Round_Terminate(__lpDb))
												return (FinishTask(__lpDb)) ;

											_iCount = 0 ;

											sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
										}

										_iCount++ ;
									}

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_STEPIT,0,0) ;
								}

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_STEPIT,0,0) ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_09(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[8] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2, _lpszAlphabet_3 ;
				LPSTR	_lpszAlphabet_4, _lpszAlphabet_5, _lpszAlphabet_6, _lpszAlphabet_7 ;
	register	LPSTR	_lpszAlphabet_8 ;

	Crack_Init(__lpDb,9,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;
	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;
		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;
			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;
				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;
					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;
						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							_szPassword[5] = *_lpszAlphabet_5++ ;
							_lpszAlphabet_6 = __lpDb->Alphabet.szAlphabet ;
							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_SETPOS,0,0) ;

							while(*_lpszAlphabet_6)
							{
								if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

								_szPassword[6] = *_lpszAlphabet_6++ ;
								_lpszAlphabet_7 = __lpDb->Alphabet.szAlphabet ;
								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_SETPOS,0,0) ;

								while(*_lpszAlphabet_7)
								{
									_szPassword[7] = *_lpszAlphabet_7++ ;
									_lpszAlphabet_8 = __lpDb->Alphabet.szAlphabet ;
									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_SETPOS,0,0) ;

									while(*_lpszAlphabet_8)
									{
										*_lpszPassword = *_lpszAlphabet_8++ ;

										if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
										{
											__lpDb->Insert(__lpDb,_szPassword) ;

											if(_iCount >= MAX_RECORDS_STORED)
											{
												if(!Round_Terminate(__lpDb))
													return (FinishTask(__lpDb)) ;

												_iCount = 0 ;

												sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
											}

											_iCount++ ;
										}

										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_STEPIT,0,0) ;
									}

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_STEPIT,0,0) ;
								}

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_STEPIT,0,0) ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_10(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[9] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2, _lpszAlphabet_3 ;
				LPSTR	_lpszAlphabet_4, _lpszAlphabet_5, _lpszAlphabet_6, _lpszAlphabet_7 ;
				LPSTR	_lpszAlphabet_8 ;
	register	LPSTR	_lpszAlphabet_9 ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	Crack_Init(__lpDb,10,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;

	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;
		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;
			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;
				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;
					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;
						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							_szPassword[5] = *_lpszAlphabet_5++ ;
							_lpszAlphabet_6 = __lpDb->Alphabet.szAlphabet ;
							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_SETPOS,0,0) ;

							while(*_lpszAlphabet_6)
							{
								_szPassword[6] = *_lpszAlphabet_6++ ;
								_lpszAlphabet_7 = __lpDb->Alphabet.szAlphabet ;
								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_SETPOS,0,0) ;

								while(*_lpszAlphabet_7)
								{
									if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

									_szPassword[7] = *_lpszAlphabet_7++ ;
									_lpszAlphabet_8 = __lpDb->Alphabet.szAlphabet ;
									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_SETPOS,0,0) ;

									while(*_lpszAlphabet_8)
									{
										_szPassword[8] = *_lpszAlphabet_8++ ;
										_lpszAlphabet_9 = __lpDb->Alphabet.szAlphabet ;
										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_SETPOS,0,0) ;

										while(*_lpszAlphabet_9)
										{
											*_lpszPassword = *_lpszAlphabet_9++ ;

											if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
											{
												__lpDb->Insert(__lpDb,_szPassword) ;

												if(_iCount >= MAX_RECORDS_STORED)
												{
													if(!Round_Terminate(__lpDb))
														return (FinishTask(__lpDb)) ;

													_iCount = 0 ;

													sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
												}

												_iCount++ ;
											}

											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_STEPIT,0,0) ;
										}

										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_STEPIT,0,0) ;
									}

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_STEPIT,0,0) ;
								}

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_STEPIT,0,0) ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;

}

int Crack_CreatePsw_11(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[10] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2, _lpszAlphabet_3 ;
				LPSTR	_lpszAlphabet_4, _lpszAlphabet_5, _lpszAlphabet_6, _lpszAlphabet_7 ;
				LPSTR	_lpszAlphabet_8, _lpszAlphabet_9 ;
	register	LPSTR	_lpszAlphabet_10 ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	Crack_Init(__lpDb,11,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;
	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							_szPassword[5] = *_lpszAlphabet_5++ ;
							_lpszAlphabet_6 = __lpDb->Alphabet.szAlphabet ;

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_SETPOS,0,0) ;

							while(*_lpszAlphabet_6)
							{
								_szPassword[6] = *_lpszAlphabet_6++ ;
								_lpszAlphabet_7 = __lpDb->Alphabet.szAlphabet ;

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_SETPOS,0,0) ;

								while(*_lpszAlphabet_7)
								{
									_szPassword[7] = *_lpszAlphabet_7++ ;
									_lpszAlphabet_8 = __lpDb->Alphabet.szAlphabet ;

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_SETPOS,0,0) ;

									while(*_lpszAlphabet_8)
									{
										if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

										_szPassword[8] = *_lpszAlphabet_8++ ;
										_lpszAlphabet_9 = __lpDb->Alphabet.szAlphabet ;

										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_SETPOS,0,0) ;

										while(*_lpszAlphabet_9)
										{
											_szPassword[9] = *_lpszAlphabet_9++ ;
											_lpszAlphabet_10 = __lpDb->Alphabet.szAlphabet ;

											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_SETPOS,0,0) ;

											while(*_lpszAlphabet_10)
											{
												*_lpszPassword = *_lpszAlphabet_10++ ;

												if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
												{
													__lpDb->Insert(__lpDb,_szPassword) ;

													if(_iCount >= MAX_RECORDS_STORED)
													{
														if(!Round_Terminate(__lpDb))
															return (FinishTask(__lpDb)) ;

														_iCount = 0 ;

														sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
													}

													_iCount++ ;
												}

												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_STEPIT,0,0) ;
											}

											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_STEPIT,0,0) ;
										}

										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_STEPIT,0,0) ;
									}

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_STEPIT,0,0) ;
								}

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_STEPIT,0,0) ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_12(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[11] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2, _lpszAlphabet_3 ;
				LPSTR	_lpszAlphabet_4, _lpszAlphabet_5, _lpszAlphabet_6, _lpszAlphabet_7 ;
				LPSTR	_lpszAlphabet_8, _lpszAlphabet_9, _lpszAlphabet_10 ;
	register	LPSTR	_lpszAlphabet_11 ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	Crack_Init(__lpDb,12,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;
	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							_szPassword[5] = *_lpszAlphabet_5++ ;
							_lpszAlphabet_6 = __lpDb->Alphabet.szAlphabet ;

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_SETPOS,0,0) ;

							while(*_lpszAlphabet_6)
							{
								_szPassword[6] = *_lpszAlphabet_6++ ;
								_lpszAlphabet_7 = __lpDb->Alphabet.szAlphabet ;

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_SETPOS,0,0) ;

								while(*_lpszAlphabet_7)
								{
									_szPassword[7] = *_lpszAlphabet_7++ ;
									_lpszAlphabet_8 = __lpDb->Alphabet.szAlphabet ;

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_SETPOS,0,0) ;

									while(*_lpszAlphabet_8)
									{
										_szPassword[8] = *_lpszAlphabet_8++ ;
										_lpszAlphabet_9 = __lpDb->Alphabet.szAlphabet ;

										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_SETPOS,0,0) ;

										while(*_lpszAlphabet_9)
										{
											if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

											_szPassword[9] = *_lpszAlphabet_9++ ;
											_lpszAlphabet_10 = __lpDb->Alphabet.szAlphabet ;

											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_SETPOS,0,0) ;

											while(*_lpszAlphabet_10)
											{
												_szPassword[10] = *_lpszAlphabet_10++ ;
												_lpszAlphabet_11 = __lpDb->Alphabet.szAlphabet ;

												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_12,PBM_SETPOS,0,0) ;

												while(*_lpszAlphabet_11)
												{
													*_lpszPassword = *_lpszAlphabet_11++ ;

													if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
													{
														__lpDb->Insert(__lpDb,_szPassword) ;

														if(_iCount >= MAX_RECORDS_STORED)
														{
															if(!Round_Terminate(__lpDb))
																return (FinishTask(__lpDb)) ;

															_iCount = 0 ;

															sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
														}

														_iCount++ ;
													}

													SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_12,PBM_STEPIT,0,0) ;
												}

												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_STEPIT,0,0) ;
											}

											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_STEPIT,0,0) ;
										}

										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_STEPIT,0,0) ;
									}

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_STEPIT,0,0) ;
								}

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_STEPIT,0,0) ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_13(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[12] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2, _lpszAlphabet_3 ;
				LPSTR	_lpszAlphabet_4, _lpszAlphabet_5, _lpszAlphabet_6, _lpszAlphabet_7 ;
				LPSTR	_lpszAlphabet_8, _lpszAlphabet_9, _lpszAlphabet_10, _lpszAlphabet_11 ;
	register	LPSTR	_lpszAlphabet_12 ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	Crack_Init(__lpDb,13,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;
	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;
		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;
			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;
				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;
					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;
						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							_szPassword[5] = *_lpszAlphabet_5++ ;
							_lpszAlphabet_6 = __lpDb->Alphabet.szAlphabet ;
							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_SETPOS,0,0) ;

							while(*_lpszAlphabet_6)
							{
								_szPassword[6] = *_lpszAlphabet_6++ ;
								_lpszAlphabet_7 = __lpDb->Alphabet.szAlphabet ;
								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_SETPOS,0,0) ;

								while(*_lpszAlphabet_7)
								{
									_szPassword[7] = *_lpszAlphabet_7++ ;
									_lpszAlphabet_8 = __lpDb->Alphabet.szAlphabet ;
									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_SETPOS,0,0) ;

									while(*_lpszAlphabet_8)
									{
										_szPassword[8] = *_lpszAlphabet_8++ ;
										_lpszAlphabet_9 = __lpDb->Alphabet.szAlphabet ;
										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_SETPOS,0,0) ;

										while(*_lpszAlphabet_9)
										{
											_szPassword[9] = *_lpszAlphabet_9++ ;
											_lpszAlphabet_10 = __lpDb->Alphabet.szAlphabet ;
											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_SETPOS,0,0) ;

											while(*_lpszAlphabet_10)
											{
												if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

												_szPassword[10] = *_lpszAlphabet_10++ ;
												_lpszAlphabet_11 = __lpDb->Alphabet.szAlphabet ;
												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_12,PBM_SETPOS,0,0) ;

												while(*_lpszAlphabet_11)
												{
													_szPassword[11] = *_lpszAlphabet_11++ ;
													_lpszAlphabet_12 = __lpDb->Alphabet.szAlphabet ;

													SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_13,PBM_SETPOS,0,0) ;

													while(*_lpszAlphabet_12)
													{
														*_lpszPassword = *_lpszAlphabet_12++ ;

														if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
														{
															__lpDb->Insert(__lpDb,_szPassword) ;

															if(_iCount >= MAX_RECORDS_STORED)
															{
																if(!Round_Terminate(__lpDb))
																	return (FinishTask(__lpDb)) ;

																_iCount = 0 ;

																sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
															}

															_iCount++ ;
														}

														SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_13,PBM_STEPIT,0,0) ;
													}

													SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_12,PBM_STEPIT,0,0) ;
												}

												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_STEPIT,0,0) ;
											}

											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_STEPIT,0,0) ;
										}

										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_STEPIT,0,0) ;
									}

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_STEPIT,0,0) ;
								}

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_STEPIT,0,0) ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_14(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[13] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2 ;
				LPSTR	_lpszAlphabet_3, _lpszAlphabet_4, _lpszAlphabet_5, _lpszAlphabet_6 ;
				LPSTR	_lpszAlphabet_7, _lpszAlphabet_8, _lpszAlphabet_9, _lpszAlphabet_10 ;
				LPSTR	_lpszAlphabet_11, _lpszAlphabet_12 ;
	register	LPSTR	_lpszAlphabet_13 ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	Crack_Init(__lpDb,14,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;
	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;
		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;
			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;
				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;
					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;
						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							_szPassword[5] = *_lpszAlphabet_5++ ;
							_lpszAlphabet_6 = __lpDb->Alphabet.szAlphabet ;
							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_SETPOS,0,0) ;

							while(*_lpszAlphabet_6)
							{
								_szPassword[6] = *_lpszAlphabet_6++ ;
								_lpszAlphabet_7 = __lpDb->Alphabet.szAlphabet ;
								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_SETPOS,0,0) ;

								while(*_lpszAlphabet_7)
								{
									_szPassword[7] = *_lpszAlphabet_7++ ;
									_lpszAlphabet_8 = __lpDb->Alphabet.szAlphabet ;
									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_SETPOS,0,0) ;

									while(*_lpszAlphabet_8)
									{
										_szPassword[8] = *_lpszAlphabet_8++ ;
										_lpszAlphabet_9 = __lpDb->Alphabet.szAlphabet ;
										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_SETPOS,0,0) ;

										while(*_lpszAlphabet_9)
										{
											_szPassword[9] = *_lpszAlphabet_9++ ;
											_lpszAlphabet_10 = __lpDb->Alphabet.szAlphabet ;
											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_SETPOS,0,0) ;

											while(*_lpszAlphabet_10)
											{
												_szPassword[10] = *_lpszAlphabet_10++ ;
												_lpszAlphabet_11 = __lpDb->Alphabet.szAlphabet ;
												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_12,PBM_SETPOS,0,0) ;

												while(*_lpszAlphabet_11)
												{
													if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

													_szPassword[11] = *_lpszAlphabet_11++ ;
													_lpszAlphabet_12 = __lpDb->Alphabet.szAlphabet ;
													SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_13,PBM_SETPOS,0,0) ;

													while(*_lpszAlphabet_12)
													{
														_szPassword[12] = *_lpszAlphabet_12++ ;
														_lpszAlphabet_13 = __lpDb->Alphabet.szAlphabet ;
														SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_14,PBM_SETPOS,0,0) ;

														while(*_lpszAlphabet_13)
														{
															*_lpszPassword = *_lpszAlphabet_13++ ;

															if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
															{
																__lpDb->Insert(__lpDb,_szPassword) ;

																if(_iCount >= MAX_RECORDS_STORED)
																{
																	if(!Round_Terminate(__lpDb))
																		return (FinishTask(__lpDb)) ;

																	_iCount = 0 ;

																	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
																}

																_iCount++ ;
															}

															SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_14,PBM_STEPIT,0,0) ;
														}

														SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_13,PBM_STEPIT,0,0) ;
													}

													SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_12,PBM_STEPIT,0,0) ;
												}

												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_STEPIT,0,0) ;
											}

											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_STEPIT,0,0) ;
										}

										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_STEPIT,0,0) ;
									}

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_STEPIT,0,0) ;
								}

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_STEPIT,0,0) ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_15(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[14] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2, _lpszAlphabet_3 ;
				LPSTR	_lpszAlphabet_4, _lpszAlphabet_5, _lpszAlphabet_6, _lpszAlphabet_7 ;
				LPSTR	_lpszAlphabet_8, _lpszAlphabet_9, _lpszAlphabet_10, _lpszAlphabet_11 ;
				LPSTR	_lpszAlphabet_12, _lpszAlphabet_13 ;
	register	LPSTR	_lpszAlphabet_14 ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	Crack_Init(__lpDb,15,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;

	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;
				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;
					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;
						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							_szPassword[5] = *_lpszAlphabet_5++ ;
							_lpszAlphabet_6 = __lpDb->Alphabet.szAlphabet ;
							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_SETPOS,0,0) ;

							while(*_lpszAlphabet_6)
							{
								_szPassword[6] = *_lpszAlphabet_6++ ;
								_lpszAlphabet_7 = __lpDb->Alphabet.szAlphabet ;
								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_SETPOS,0,0) ;

								while(*_lpszAlphabet_7)
								{
									_szPassword[7] = *_lpszAlphabet_7++ ;
									_lpszAlphabet_8 = __lpDb->Alphabet.szAlphabet ;
									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_SETPOS,0,0) ;

									while(*_lpszAlphabet_8)
									{
										_szPassword[8] = *_lpszAlphabet_8++ ;
										_lpszAlphabet_9 = __lpDb->Alphabet.szAlphabet ;
										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_SETPOS,0,0) ;

										while(*_lpszAlphabet_9)
										{
											_szPassword[9] = *_lpszAlphabet_9++ ;
											_lpszAlphabet_10 = __lpDb->Alphabet.szAlphabet ;
											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_SETPOS,0,0) ;

											while(*_lpszAlphabet_10)
											{
												_szPassword[10] = *_lpszAlphabet_10++ ;
												_lpszAlphabet_11 = __lpDb->Alphabet.szAlphabet ;
												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_12,PBM_SETPOS,0,0) ;

												while(*_lpszAlphabet_11)
												{
													_szPassword[11] = *_lpszAlphabet_11++ ;
													_lpszAlphabet_12 = __lpDb->Alphabet.szAlphabet ;
													SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_13,PBM_SETPOS,0,0) ;

													while(*_lpszAlphabet_12)
													{
														if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

														_szPassword[12] = *_lpszAlphabet_12++ ;
														_lpszAlphabet_13 = __lpDb->Alphabet.szAlphabet ;
														SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_14,PBM_SETPOS,0,0) ;

														while(*_lpszAlphabet_13)
														{
															_szPassword[13] = *_lpszAlphabet_13++ ;
															_lpszAlphabet_14 = __lpDb->Alphabet.szAlphabet ;
															SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_15,PBM_SETPOS,0,0) ;

															while(*_lpszAlphabet_14)
															{
																*_lpszPassword = *_lpszAlphabet_14++ ;

																if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
																{
																	__lpDb->Insert(__lpDb,_szPassword) ;

																	if(_iCount >= MAX_RECORDS_STORED)
																	{
																		if(!Round_Terminate(__lpDb))
																			return (FinishTask(__lpDb)) ;

																		_iCount = 0 ;

																		sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
																	}

																	_iCount++ ;
																}

																SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_15,PBM_STEPIT,0,0) ;
															}

															SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_14,PBM_STEPIT,0,0) ;
														}

														SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_13,PBM_STEPIT,0,0) ;
													}

													SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_12,PBM_STEPIT,0,0) ;
												}

												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_STEPIT,0,0) ;
											}

											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_STEPIT,0,0) ;
										}

										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_STEPIT,0,0) ;
									}

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_STEPIT,0,0) ;
								}

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_STEPIT,0,0) ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int Crack_CreatePsw_16(LPDB_GEN __lpDb)
{
				char	_szPassword[MAX_LEN_PASSWORD * 2] ;

	register	LPSTR	_lpszPassword = &_szPassword[15] ;
				LPSTR	_lpszAlphabet_0, _lpszAlphabet_1, _lpszAlphabet_2, _lpszAlphabet_3 ;
				LPSTR	_lpszAlphabet_4, _lpszAlphabet_5, _lpszAlphabet_6, _lpszAlphabet_7 ;
				LPSTR	_lpszAlphabet_8, _lpszAlphabet_9, _lpszAlphabet_10, _lpszAlphabet_11 ;
				LPSTR	_lpszAlphabet_12, _lpszAlphabet_13, _lpszAlphabet_14 ;
	register	LPSTR	_lpszAlphabet_15 ;
				int		_iRound, _iCount ;

	sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;

	_iRound = 2 ;
	_iCount = 1 ;

	Crack_Init(__lpDb,16,_szPassword) ;
	_lpszAlphabet_0 = __lpDb->Alphabet.szAlphabet ;

	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_SETPOS,0,0) ;

	while(*_lpszAlphabet_0)
	{
		_szPassword[0] = *_lpszAlphabet_0++ ;
		_lpszAlphabet_1 = __lpDb->Alphabet.szAlphabet ;
		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_SETPOS,0,0) ;

		while(*_lpszAlphabet_1)
		{
			_szPassword[1] = *_lpszAlphabet_1++ ;
			_lpszAlphabet_2 = __lpDb->Alphabet.szAlphabet ;
			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_SETPOS,0,0) ;

			while(*_lpszAlphabet_2)
			{
				_szPassword[2] = *_lpszAlphabet_2++ ;
				_lpszAlphabet_3 = __lpDb->Alphabet.szAlphabet ;
				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_SETPOS,0,0) ;

				while(*_lpszAlphabet_3)
				{
					_szPassword[3] = *_lpszAlphabet_3++ ;
					_lpszAlphabet_4 = __lpDb->Alphabet.szAlphabet ;
					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_SETPOS,0,0) ;

					while(*_lpszAlphabet_4)
					{
						_szPassword[4] = *_lpszAlphabet_4++ ;
						_lpszAlphabet_5 = __lpDb->Alphabet.szAlphabet ;
						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_SETPOS,0,0) ;

						while(*_lpszAlphabet_5)
						{
							_szPassword[5] = *_lpszAlphabet_5++ ;
							_lpszAlphabet_6 = __lpDb->Alphabet.szAlphabet ;
							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_SETPOS,0,0) ;

							while(*_lpszAlphabet_6)
							{
								_szPassword[6] = *_lpszAlphabet_6++ ;
								_lpszAlphabet_7 = __lpDb->Alphabet.szAlphabet ;
								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_SETPOS,0,0) ;

								while(*_lpszAlphabet_7)
								{
									_szPassword[7] = *_lpszAlphabet_7++ ;
									_lpszAlphabet_8 = __lpDb->Alphabet.szAlphabet ;
									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_SETPOS,0,0) ;

									while(*_lpszAlphabet_8)
									{
										_szPassword[8] = *_lpszAlphabet_8++ ;
										_lpszAlphabet_9 = __lpDb->Alphabet.szAlphabet ;
										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_SETPOS,0,0) ;

										while(*_lpszAlphabet_9)
										{
											_szPassword[9] = *_lpszAlphabet_9++ ;
											_lpszAlphabet_10 = __lpDb->Alphabet.szAlphabet ;
											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_SETPOS,0,0) ;

											while(*_lpszAlphabet_10)
											{
												_szPassword[10] = *_lpszAlphabet_10++ ;
												_lpszAlphabet_11 = __lpDb->Alphabet.szAlphabet ;
												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_12,PBM_SETPOS,0,0) ;

												while(*_lpszAlphabet_11)
												{
													_szPassword[11] = *_lpszAlphabet_11++ ;
													_lpszAlphabet_12 = __lpDb->Alphabet.szAlphabet ;
													SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_13,PBM_SETPOS,0,0) ;

													while(*_lpszAlphabet_12)
													{
														_szPassword[12] = *_lpszAlphabet_12++ ;
														_lpszAlphabet_13 = __lpDb->Alphabet.szAlphabet ;
														SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_14,PBM_SETPOS,0,0) ;

														while(*_lpszAlphabet_13)
														{
															if(Crack_HandleMutex(__lpDb))	return (TRUE) ;

															_szPassword[13] = *_lpszAlphabet_13++ ;
															_lpszAlphabet_14 = __lpDb->Alphabet.szAlphabet ;
															SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_15,PBM_SETPOS,0,0) ;

															while(*_lpszAlphabet_14)
															{
																_szPassword[14] = *_lpszAlphabet_14++ ;
																_lpszAlphabet_15 = __lpDb->Alphabet.szAlphabet ;

																while(*_lpszAlphabet_15)
																{
																	*_lpszPassword = *_lpszAlphabet_15++ ;

																	if(!ValidPassword(_szPassword,&__lpDb->Alphabet))
																	{
																		__lpDb->Insert(__lpDb,_szPassword) ;

																		if(_iCount >= MAX_RECORDS_STORED)
																		{
																			if(!Round_Terminate(__lpDb))
																				return (FinishTask(__lpDb)) ;

																			_iCount = 0 ;

																			sqlite3_exec(__lpDb->Db,szBeginTransaction,0,0,NULL) ;
																		}

																		_iCount++ ;
																	}

																	SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_16,PBM_STEPIT,0,0) ;
																}

																SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_15,PBM_STEPIT,0,0) ;
															}

															SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_14,PBM_STEPIT,0,0) ;
														}

														SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_13,PBM_STEPIT,0,0) ;
													}

													SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_12,PBM_STEPIT,0,0) ;
												}

												SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_11,PBM_STEPIT,0,0) ;
											}

											SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_10,PBM_STEPIT,0,0) ;
										}

										SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_09,PBM_STEPIT,0,0) ;
									}

									SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_08,PBM_STEPIT,0,0) ;
								}

								SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_07,PBM_STEPIT,0,0) ;
							}

							SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_06,PBM_STEPIT,0,0) ;
						}

						SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_05,PBM_STEPIT,0,0) ;
					}

					SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_04,PBM_STEPIT,0,0) ;
				}

				SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_03,PBM_STEPIT,0,0) ;
			}

			SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_02,PBM_STEPIT,0,0) ;
		}

		SendDlgItemMessage(__lpDb->hWnd,IDC_PROGRESS_01,PBM_STEPIT,0,0) ;
	}

	Round_Finish(__lpDb) ;

	return (FinishTask(__lpDb)) ;
}

int DoGeneratePasswords(LPDB_GEN __lpDbGen)
{
	__lpDbGen->iThreadMode |= THREAD_MODE_RUNNING ;

	switch(__lpDbGen->iPasswordLength)
	{
		case	1 :		if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_01,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_01,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	2 :		if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_02,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_02,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	3 :		if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_03,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_03,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	4 :		if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_04,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_04,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	5 :		if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_05,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_05,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	6 :		if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_06,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_06,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	7 :		if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_07,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_07,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	8 :		if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_08,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_08,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	9 :		if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_09,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_09,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	10 :	if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_10,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_10,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	11 :	if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_11,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_11,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	12 :	if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_12,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_12,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	13 :	if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_13,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_13,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	14 :	if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_14,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_14,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	15 :	if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_15,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_15,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;

		case	16 :	if(__lpDbGen->hThread == NULL)
						{
							if(__lpDbGen->iThreadMode == THREAD_MODE_BACKGROUND)
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_16,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_MODE_BACKGROUND_BEGIN) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
							else
							{
								__lpDbGen->hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) Crack_CreatePsw_16,__lpDbGen,CREATE_SUSPENDED,NULL) ;
								SetThreadPriority(__lpDbGen->hThread,THREAD_PRIORITY_HIGHEST) ;
								ResumeThread(__lpDbGen->hThread) ;
							}
						}

						return (CRACK_SUCCESS) ;
	}

	return (CRACK_FAIL) ;
}

void Crack_RunGeneratePasswords(HWND __hWnd)
{
	register	int			_iIndex ;
	register	int			_i ;

				LPPASSWORD	_lpTmpPassword ;
				LPALPHABET	*_lpTmpAlphabet ;
				LPDB_INFOS	*_lpTmpDataBase ;
				LPHASHSIZE	_lpTmpHashSize ;
				LPDB_GEN	_lpDbGen ;

	_lpDbGen = (LPDB_GEN) VirtualAlloc(NULL,sizeof(DB_GEN),MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE) ;
	if(_lpDbGen)
	{
		_lpDbGen->hWnd = __hWnd ;
		_lpDbGen->iCount = 1 ;

		SetWindowLongPtr(__hWnd,DWLP_USER,(LPARAM) _lpDbGen) ;

		ShowWindow(GetDlgItem(__hWnd,IDC_BACKGROUND),SW_SHOW) ;
		ShowWindow(GetDlgItem(__hWnd,IDC_FOREGROUND),SW_HIDE) ;

		_lpDbGen->iThreadMode = THREAD_MODE_BACKGROUND ;

		for(_i = 0 ; _i < MAX_LEN_PASSWORD ; _i++)
			SendDlgItemMessage(__hWnd,IDC_PROGRESS_01 + _i,PBM_SETPOS,0,0) ;

		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_GETCURSEL,0,0) ;
		_lpTmpDataBase = (LPDB_INFOS *) SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_GETITEMDATA,_iIndex,0) ;

		_lpDbGen->Insert = (*_lpTmpDataBase)->Insert ;
		lstrcpy(_lpDbGen->szAlgorithme,(*_lpTmpDataBase)->lpszAlgorithme) ;

		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_03,CB_GETCURSEL,0,0) ;
		_lpTmpHashSize = (LPHASHSIZE) SendDlgItemMessage(__hWnd,IDC_COMBO_03,CB_GETITEMDATA,_iIndex,0) ;

		_lpDbGen->iHashNumberOfBits = _lpTmpHashSize->iHashNumberOfBits ;
		_lpDbGen->iHashNumberOfBytes = _lpTmpHashSize->iHashNumberOfBits / 8 ;
		_lpDbGen->iAlgorithme = (*_lpTmpDataBase)->iKeyCode ;

		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_GETCURSEL,0,0) ;
		_lpTmpPassword = (LPPASSWORD) SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_GETITEMDATA,_iIndex,0) ;

		_lpDbGen->iPasswordLength = _lpTmpPassword->iPasswordLength ;
		_lpDbGen->iStringLength = _lpDbGen->iPasswordLength ;
		_lpDbGen->iRecNum = (*_lpTmpDataBase)->iKeyCode ;

		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_GETCURSEL,0,0) ;
		_lpTmpAlphabet = (LPALPHABET *) SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_GETITEMDATA,_iIndex,0) ;

		memcpy(&_lpDbGen->Alphabet,*_lpTmpAlphabet,sizeof(ALPHABET)) ;

		if(Db_Open(_lpDbGen,_lpDbGen->iPasswordLength,_lpDbGen->iHashNumberOfBits))
		{
			ShowWindow(GetDlgItem(__hWnd,IDOK),SW_HIDE) ;
			ShowWindow(GetDlgItem(__hWnd,IDCANCEL),SW_HIDE) ;
			ShowWindow(GetDlgItem(__hWnd,IDC_STOP),SW_SHOW) ;

			Message(__hWnd,szRunning) ;

			DoGeneratePasswords(_lpDbGen) ;
		}
	}

	return ;
}

void Crack_StopThisThread(HWND __hWnd)
{
	register	LPDB_GEN	_lpDb ;
	register	DWORD		_dwWaitResult ;

	_dwWaitResult = WaitForSingleObject(hMutex,PSW_WAIT_TIMEOUT) ;
	if(_dwWaitResult == WAIT_OBJECT_0)
	{
		_lpDb = (LPDB_GEN) GetWindowLongPtr(__hWnd,DWLP_USER) ;
		if(_lpDb)
		{
			ShowWindow(GetDlgItem(__hWnd,IDC_STOP),SW_HIDE) ;
			_lpDb->iThreadAction = THREAD_ACTION_STOPPED ;
			sqlite3_exec(_lpDb->Db,szEndTransaction,0,0,NULL) ;
		}
	}

	ReleaseMutex(hMutex) ;

	return ;
}

void Crack_BackGroundThisThread(HWND __hWnd)
{
	register	LPDB_GEN	_lpDb ;
	register	DWORD		_dwWaitResult ;

	_dwWaitResult = WaitForSingleObject(hMutex,PSW_WAIT_TIMEOUT) ;
	if(_dwWaitResult == WAIT_OBJECT_0)
	{
		_lpDb = (LPDB_GEN) GetWindowLongPtr(__hWnd,DWLP_USER) ;
		if(_lpDb)
		{
			_lpDb->iThreadAction = THREAD_ACTION_BACKGROUND ;

			ShowWindow(GetDlgItem(__hWnd,IDC_BACKGROUND),SW_HIDE) ;
			ShowWindow(GetDlgItem(__hWnd,IDC_FOREGROUND),SW_SHOW) ;
		}
	}

	ReleaseMutex(hMutex) ;

	return ;
}

void Crack_ForegroundThisThread(HWND __hWnd)
{
	register	LPDB_GEN	_lpDb ;
	register	DWORD		_dwWaitResult ;

	_dwWaitResult = WaitForSingleObject(hMutex,PSW_WAIT_TIMEOUT) ;
	if(_dwWaitResult == WAIT_OBJECT_0)
	{
		_lpDb = (LPDB_GEN) GetWindowLongPtr(__hWnd,DWLP_USER) ;
		if(_lpDb)
		{
			_lpDb->iThreadAction = THREAD_ACTION_FOREGROUND ;

			ShowWindow(GetDlgItem(__hWnd,IDC_BACKGROUND),SW_SHOW) ;
			ShowWindow(GetDlgItem(__hWnd,IDC_FOREGROUND),SW_HIDE) ;
		}
	}

	ReleaseMutex(hMutex) ;

	return ;
}

void Crack_InitDialog(HWND __hWnd)
{
	register	int			_iIndex ;
	register	LPDB_INFOS	*_lpTmpDataBase ;
				LPPASSWORD	_lpTmpPassword ;
				LPALPHABET	*_lpTmpAlphabet ;
				LPHASHSIZE	_lpTmpHashSize ;

	hDialogs = __hWnd ;

	ShowWindow(GetDlgItem(__hWnd,IDC_STOP),SW_HIDE) ;
	ShowWindow(GetDlgItem(__hWnd,IDC_BACKGROUND),SW_SHOW) ;
	ShowWindow(GetDlgItem(__hWnd,IDC_FOREGROUND),SW_HIDE) ;

	_lpTmpAlphabet = lpAlphabet ;

	while(*_lpTmpAlphabet)
	{
		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_ADDSTRING,0,(LPARAM) (*_lpTmpAlphabet)->szTitle) ;
		SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_SETITEMDATA,_iIndex,(LPARAM) _lpTmpAlphabet) ;

		_lpTmpAlphabet++ ;
	}

	SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_SETCURSEL,0,0) ;
	SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_SETTOPINDEX,0,0) ;

	_lpTmpPassword = lpPassword ;

	while(_lpTmpPassword->iKeyCode)
	{
		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_ADDSTRING,0,(LPARAM) _lpTmpPassword->szPasswordLength) ;
		SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_SETITEMDATA,_iIndex,(LPARAM) _lpTmpPassword) ;

		_lpTmpPassword++ ;
	}

	SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_SETCURSEL,0,0) ;
	SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_SETTOPINDEX,0,0) ;

	_lpTmpHashSize = lpHashSize ;

	while(_lpTmpHashSize->iKeyCode)
	{
		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_03,CB_ADDSTRING,0,(LPARAM) _lpTmpHashSize->lpszHashSize) ;
		SendDlgItemMessage(__hWnd,IDC_COMBO_03,CB_SETITEMDATA,_iIndex,(LPARAM) _lpTmpHashSize) ;

		_lpTmpHashSize++ ;
	}

	SendDlgItemMessage(__hWnd,IDC_COMBO_03,CB_SETCURSEL,0,0) ;
	SendDlgItemMessage(__hWnd,IDC_COMBO_03,CB_SETTOPINDEX,0,0) ;

	_lpTmpHashSize = (LPHASHSIZE) SendDlgItemMessage(__hWnd,IDC_COMBO_03,CB_GETITEMDATA,0,0) ;

	_lpTmpDataBase = GetDataBase(_lpTmpHashSize->iHashNumberOfBits) ;

	while(*_lpTmpDataBase)
	{
		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_ADDSTRING,0,(LPARAM) (*_lpTmpDataBase)->lpszAlgorithme) ;
		SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_SETITEMDATA,_iIndex,(LPARAM) _lpTmpDataBase) ;

		_lpTmpDataBase++ ;
	}

	SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_SETCURSEL,0,0) ;
	SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_SETTOPINDEX,0,0) ;

	Message(__hWnd,szWaiting) ;

	return ;
}

void Crack_Init_03(HWND __hWnd)
{
	register	int			_iIndex ;
	register	LPDB_INFOS	*_lpTmpDataBase ;
				LPHASHSIZE	_lpTmpHashSize ;

	Message(__hWnd,szWaiting) ;
	SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_RESETCONTENT,0,0) ;

	_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_03,CB_GETCURSEL,0,0) ;
	_lpTmpHashSize = (LPHASHSIZE) SendDlgItemMessage(__hWnd,IDC_COMBO_03,CB_GETITEMDATA,_iIndex,0) ;
	_lpTmpDataBase = GetDataBase(_lpTmpHashSize->iHashNumberOfBits) ;

	while(*_lpTmpDataBase)
	{
		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_ADDSTRING,0,(LPARAM) (*_lpTmpDataBase)->lpszAlgorithme) ;
		SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_SETITEMDATA,_iIndex,(LPARAM) _lpTmpDataBase) ;

		_lpTmpDataBase++ ;
	}

	SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_SETCURSEL,0,0) ;
	SendDlgItemMessage(__hWnd,IDC_COMBO_04,CB_SETTOPINDEX,0,0) ;

	return ;
}

LRESULT CALLBACK DlgGeneratePassword(HWND __hWnd,UINT __uMsg,WPARAM __wParam,LPARAM __lParam)
{
	int			_iIndex ;
	RECT		_Rc ;
	char		_szTmp[1024] ;
	LPALPHABET	*_lpTmpAlphabet ;

	switch (__uMsg)
	{
		case	WM_INITDIALOG :	Crack_InitDialog(__hWnd) ;

								return (TRUE) ;

		case	WM_ACTIVATE :	if(LOWORD(__wParam) == WA_INACTIVE)	hDialogs = NULL ;
								else								hDialogs = __hWnd ;

								return (TRUE) ;

		case	WM_ERASEBKGND :	GetClientRect(__hWnd,&_Rc) ;
								FillRect((HDC) __wParam,&_Rc,GetStockObject(BLACK_BRUSH)) ;
								return (TRUE) ;

		case	WM_CTLCOLORSTATIC :
		case	WM_CTLCOLORBTN :
		case	WM_CTLCOLORLISTBOX :
		case	WM_CTLCOLOREDIT :
		case	WM_CTLCOLORDLG :
									return (DlgCtlColor(__hWnd,__uMsg,__wParam)) ;

		case	SC_CLOSE :
		case	WM_CLOSE :		if(IsWindowVisible(GetDlgItem(__hWnd,IDC_STOP)))
									Crack_StopThisThread(__hWnd) ;

								SetWindowLongPtr(__hWnd,DWLP_USER,(LPARAM) NULL) ;
								hDialogs = NULL ;
								return (TRUE) ;

		case	WM_COMMAND :	switch (LOWORD(__wParam))
            					{
									case	IDC_COMBO_01 :	if(HIWORD(__wParam) != CBN_SELCHANGE)
																	break ;

															Message(__hWnd,szWaiting) ;

															_iIndex = SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_GETCURSEL,0,0) ;
															_lpTmpAlphabet = (LPALPHABET *) SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_GETITEMDATA,_iIndex,0) ;

															wsprintf(_szTmp,"Alphabet #%d",(*_lpTmpAlphabet)->iAlphabet) ;
															SetDlgItemText(__hWnd,IDC_STATIC_05,_szTmp) ;

															wsprintf(_szTmp,"Alphabet Size : %d chars",(*_lpTmpAlphabet)->iAlphabetLength) ;
															SetDlgItemText(__hWnd,IDC_STATIC_06,_szTmp) ;

															wsprintf(_szTmp,"Number of Subsets : %d",(*_lpTmpAlphabet)->iNumAlphabets) ;
															SetDlgItemText(__hWnd,IDC_STATIC_07,_szTmp) ;

															break ;

									case	IDC_COMBO_02 :	if(HIWORD(__wParam) != CBN_SELCHANGE)
																	break ;

															Message(__hWnd,szWaiting) ;
															break ;

									case	IDC_COMBO_03 :	if(HIWORD(__wParam) != CBN_SELCHANGE)
																	break ;

															Crack_Init_03(__hWnd) ;

															break ;

									case	IDC_STOP :			//	Stop

															if(HIWORD(__wParam) == BN_CLICKED)
																Crack_StopThisThread(__hWnd) ;

															break ;

									case	IDC_BACKGROUND :	//	Background

															if(HIWORD(__wParam) == BN_CLICKED)
																Crack_BackGroundThisThread(__hWnd) ;

															break ;

									case	IDC_FOREGROUND :	//	Foreground

															if(HIWORD(__wParam) == BN_CLICKED)
																Crack_ForegroundThisThread(__hWnd) ;

															break ;

									case	IDOK :		if(HIWORD(__wParam) == BN_CLICKED)
														{
															Crack_RunGeneratePasswords(__hWnd) ;
														}

														break ;

									case	IDCANCEL :	if(HIWORD(__wParam) == BN_CLICKED)
														{
															if(IsWindowVisible(GetDlgItem(__hWnd,IDC_STOP)))
																Crack_StopThisThread(__hWnd) ;

															SetWindowLongPtr(__hWnd,DWLP_USER,(LPARAM) NULL) ;
															hDialogs = NULL ;
															DestroyWindow(__hWnd) ;
															return (TRUE) ;
														}
														break ;
								}

								break ;
	}

	return (FALSE) ;
}
