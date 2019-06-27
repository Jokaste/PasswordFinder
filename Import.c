#include "Crack.h"

int DecodeBuffer(HWND __hWnd,LPBYTE __lpBuffer,DWORD __dwBufferSize,LPDB_INFOS __lpDb)
{
	register	LPBYTE		_lpTmp, _lpDebut ;
				char		_c ;
	register	int			_iLen ;
				int			_iStringLength ;
				int			_i ;
	unsigned	int			_uNumberOfPasswords ;
				LPDB_INFOS	*_lpTmpDataBase ;
				char		_szTmp[1024], _szOutput[256] ;
				DB_GEN 		_DbImport[MAX_IMPORT_LEN_PASSWORD + 1] ;

	Message(__hWnd,"Creating/Openning the 64 tables can take a long time...") ;

	__stosq((unsigned long long *) _DbImport,0,sizeof(_DbImport) / 8) ;
	wsprintf(_DbImport[0].szAlgorithme,"%s Import",__lpDb->lpszAlgorithme) ;

	_i = SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_GETCURSEL,0,0) ;
	_lpTmpDataBase = (LPDB_INFOS *) SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_GETITEMDATA,_i,0) ;
	_DbImport[0].iAlgorithme = 500 + (*_lpTmpDataBase)->iKeyCode ;

	_DbImport[0].Alphabet.iAlphabet = iCodeAlphabetLePlusLong ;
	_DbImport[0].Alphabet.iAlphabetLength = iAlphabetLePlusLong ;
	_DbImport[0].Alphabet.iNumAlphabets = 1 ;
	_DbImport[0].Insert = __lpDb->Insert ;
	_DbImport[0].iHashNumberOfBytes = __lpDb->iHashNumberOfBytes ;
	_DbImport[0].iHashNumberOfBits = __lpDb->iHashNumberOfBits ;
	_DbImport[0].hWnd = __hWnd ;

	Db_Open(&_DbImport[0],0,__lpDb->iHashNumberOfBits) ;

	_uNumberOfPasswords = 1 ;

	Log("Start importing file") ;

	_i = 0 ;

	while(lpDatabaseInfos[_i])
	{
		if(lstrcmp(__lpDb->lpszAlgorithme,lpDatabaseInfos[_i]->lpszAlgorithme) == 0)
		{
			_DbImport[0].iAlgorithme = 500 + lpDatabaseInfos[_i]->iKeyCode ;
			break ;
		}

		_i++ ;
	}

	for(_i = 1 ; _i < (MAX_IMPORT_LEN_PASSWORD + 1) ; _i++)
	{
		memcpy(&_DbImport[_i],&_DbImport[0],sizeof(DB_GEN)) ;

		lstrcpy(_DbImport[_i].szAlgorithme,__lpDb->lpszAlgorithme) ;

		_DbImport[_i].Db = NULL ;
		_DbImport[_i].hWnd = __hWnd ;

		Db_Open(&_DbImport[_i],_i,__lpDb->iHashNumberOfBits) ;
	}

	Message(__hWnd,"Importing the passwords") ;

	_lpTmp = _lpDebut = __lpBuffer ;
	_iLen = 0 ;

	while(__dwBufferSize)
	{
		_c = *_lpTmp ;

		if(_c == 0x0d)
		{
			*(_lpTmp) = '\0' ;
		}
		else
		{
			if(_c == 0x0a)
			{
				*(_lpTmp) = '\0' ;
				_iStringLength = _iLen = lstrlen(_lpDebut) ;

				if(_iLen)
				{
					if(_iLen > MAX_IMPORT_LEN_PASSWORD)	_iLen = 0 ;

					if(_DbImport[_iLen].Db)
					{
						_DbImport[_iLen].iStringLength = _iStringLength ;
						_DbImport[_iLen].iPasswordLength = _iStringLength ;
						_DbImport[_iLen].lpszStringToHash = _lpDebut ;

						if(__lpDb->Insert(&_DbImport[_iLen],_DbImport[_iLen].lpszStringToHash) == CRACK_SUCCESS)
						{
							_uNumberOfPasswords++ ;
							sprintf(_szTmp,"%lu",_uNumberOfPasswords) ;
							GetNumberFormat(LOCALE_USER_DEFAULT,0,_szTmp,&NumFmt,_szOutput,sizeof(_szOutput)) ;
							Message(__hWnd,_szOutput) ;
						}
					}
				}

				_lpDebut = _lpTmp + 1 ;
			}

			_lpTmp++ ;
			__dwBufferSize-- ;
		}
	}

	if(_uNumberOfPasswords)
	{
		if(_uNumberOfPasswords > 1)
			wsprintf(_szTmp,"%lu passwords imported",_uNumberOfPasswords) ;
		else
			lstrcpy(_szTmp,"Only one password imported") ;
	}
	else
	{
		lstrcpy(_szTmp,"No password imported") ;
	}

	Log(_szTmp) ;
	Log("End importing file") ;

	if(GetPrivateProfileInt(szDatabases,szSQLiteVacuum,1,szProfile))
	{
		for(_i = 0 ; _i < (MAX_IMPORT_LEN_PASSWORD + 1) ; _i++)
		{
			sqlite3_exec(_DbImport[_i].Db,szSQLiteVacuum,0,0,NULL) ;
			sqlite3_close(_DbImport[_i].Db) ;
		}
	}
	else
	{
		for(_i = 0 ; _i < (MAX_IMPORT_LEN_PASSWORD + 1) ; _i++)
			sqlite3_close(_DbImport[_i].Db) ;
	}

	return (CRACK_SUCCESS) ;
}

int ImportFile(HWND __hWnd,LPSTR __lpszFileName,LPDB_INFOS __lpDb)
{
	HANDLE	_hFile ;
	DWORD	_dwFileSizeHigh, _dwFileSize ;
	LPBYTE	_lpBuffer ;
	int		_iRes ;
	DWORD	_dwTmp ;

				char	_szTmp[1024] ;

	wsprintf(_szTmp,"Importing file : %s",__lpszFileName) ;
	Log(_szTmp) ;

	_hFile = CreateFile(__lpszFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL) ;
	if(_hFile == INVALID_HANDLE_VALUE)
	{
		SystemErrorBox("ImportFile::CreateFile") ;

		ShowWindow(GetDlgItem(__hWnd,IDCANCEL),SW_SHOW) ;

		return (FALSE) ;
	}

	_dwFileSize = GetFileSize(_hFile,&_dwFileSizeHigh) ;
	if(_dwFileSizeHigh != 0)
	{
		CloseHandle(_hFile) ;

		ShowWindow(GetDlgItem(__hWnd,IDCANCEL),SW_SHOW) ;

		return (Error("ImportFile::The file is too big")) ;
	}

	if(_dwFileSize == 0)
	{
		CloseHandle(_hFile) ;

		ShowWindow(GetDlgItem(__hWnd,IDCANCEL),SW_SHOW) ;

		return (Error("ImportFile::The file is empty")) ;
	}

	_lpBuffer = (LPBYTE) VirtualAlloc(NULL,_dwFileSize,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE) ;
	if(!_lpBuffer)
	{
		SystemErrorBox("ImportFile::VirtualAlloc") ;

		ShowWindow(GetDlgItem(__hWnd,IDCANCEL),SW_SHOW) ;

		CloseHandle(_hFile) ;
		return (CRACK_FAIL) ;
	}

	if(ReadFile(_hFile,_lpBuffer,_dwFileSize,&_dwTmp,NULL))
	{
		if(_dwTmp != _dwFileSize)
		{
			VirtualFree(_lpBuffer,0,MEM_RELEASE) ;
			CloseHandle(_hFile) ;

			ShowWindow(GetDlgItem(__hWnd,IDCANCEL),SW_SHOW) ;

			return (Error("ImportFile::Error while reading file to import")) ;
		}
	}
	else
	{
		VirtualFree(_lpBuffer,0,MEM_RELEASE) ;
		CloseHandle(_hFile) ;

		ShowWindow(GetDlgItem(__hWnd,IDCANCEL),SW_SHOW) ;

		return (Error("ImportFile::Error while reading file to import")) ;
	}

	CloseHandle(_hFile) ;

	_iRes = DecodeBuffer(__hWnd,_lpBuffer,_dwFileSize,__lpDb) ;

	VirtualFree(_lpBuffer,0,MEM_RELEASE) ;
	Log("Importing file finished") ;

	ShowWindow(GetDlgItem(__hWnd,IDCANCEL),SW_SHOW) ;

	return (_iRes) ;
}

void ImportThisFile(HWND __hWnd)
{
	register	int			_iIndex ;
	register	LPSTR		_lpszTmp ;
				LPDB_INFOS	*_lpTmpDataBase ;
				char		_szTmp[1024] ;

	_lpszTmp = _szTmp ;

	if(GetDlgItemText(__hWnd,IDC_EDIT_01,_szTmp,sizeof(_szTmp)))
	{
		_iIndex = SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_GETCURSEL,0,0) ;
		_lpTmpDataBase = (LPDB_INFOS *) SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_GETITEMDATA,_iIndex,0) ;

		Message(__hWnd,szRunning) ;

		if(ImportFile(__hWnd,_szTmp,*_lpTmpDataBase))
			Message(__hWnd,szSuccess) ;
		else
			Message(__hWnd,szFailure) ;
	}
	else
		Error("There is no file name!") ;

	ShowWindow(GetDlgItem(__hWnd,IDOK),SW_SHOW) ;
	ShowWindow(GetDlgItem(__hWnd,IDCANCEL),SW_SHOW) ;

	return ;
}

void Import_Run(HWND __hWnd)
{
	register	HANDLE	_hThread ;

	ShowWindow(GetDlgItem(__hWnd,IDOK),SW_HIDE) ;
	ShowWindow(GetDlgItem(__hWnd,IDCANCEL),SW_HIDE) ;

	_hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) ImportThisFile,__hWnd,0,NULL) ;
	CloseHandle(_hThread) ;

	return ;
}

void Import_InitDialog(HWND __hWnd)
{
	register	int			_iIndex ;
				LPDB_INFOS	*_lpTmpDataBase ;
				LPHASHSIZE	_lpTmpHashSize ;

	hDialogs = __hWnd ;
			
	SendDlgItemMessage(__hWnd,IDC_EDIT_01,EM_LIMITTEXT,MAX_PATH,0) ;
	SetDlgItemText(__hWnd,IDC_EDIT_01,szNullString) ;

	Message(__hWnd,szWaiting) ;

	_lpTmpHashSize = lpHashSize ;

	while(_lpTmpHashSize->iKeyCode)
	{
		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_ADDSTRING,0,(LPARAM) _lpTmpHashSize->lpszHashSize) ;
		SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_SETITEMDATA,_iIndex,(LPARAM) _lpTmpHashSize) ;

		_lpTmpHashSize++ ;
	}

	SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_SETCURSEL,0,0) ;
	SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_SETTOPINDEX,0,0) ;

	_lpTmpHashSize = (LPHASHSIZE) SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_GETITEMDATA,0,0) ;
	_lpTmpDataBase = GetDataBase(_lpTmpHashSize->iHashNumberOfBits) ;

	while(*_lpTmpDataBase)
	{
		_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_ADDSTRING,0,(LPARAM) (*_lpTmpDataBase)->lpszAlgorithme) ;
		SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_SETITEMDATA,_iIndex,(LPARAM) _lpTmpDataBase) ;

		_lpTmpDataBase++ ;
	}

	SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_SETCURSEL,0,0) ;
	SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_SETTOPINDEX,0,0) ;

	return ;
}

LRESULT Import_WmCommand(HWND __hWnd,WPARAM __wParam)
{
	register	int			_iIndex ;
				LPDB_INFOS	*_lpTmpDataBase ;
				LPHASHSIZE	_lpTmpHashSize ;
				char		_szTmp[1024] ;

				OPENFILENAME	_Ofn ;

	switch (LOWORD(__wParam))
	{
		case	IDC_COMBO_01 :	if(HIWORD(__wParam) == CBN_SELCHANGE)
								{
									Message(__hWnd,szWaiting) ;
									SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_RESETCONTENT,0,0) ;
									_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_GETCURSEL,0,0) ;
									_lpTmpHashSize = (LPHASHSIZE) SendDlgItemMessage(__hWnd,IDC_COMBO_01,CB_GETITEMDATA,_iIndex,0) ;
									_lpTmpDataBase = GetDataBase(_lpTmpHashSize->iHashNumberOfBits) ;

									while(*_lpTmpDataBase)
									{
										_iIndex = (int) SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_ADDSTRING,0,(LPARAM) (*_lpTmpDataBase)->lpszAlgorithme) ;
										SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_SETITEMDATA,_iIndex,(LPARAM) _lpTmpDataBase) ;

										_lpTmpDataBase++ ;
									}

									SendDlgItemMessage(__hWnd,IDC_COMBO_02,CB_SETCURSEL,0,0) ;

									return (TRUE) ;
								}

								break ;

		case	IDC_COMBO_02 :	if(HIWORD(__wParam) == CBN_SELCHANGE)
								{
									Message(__hWnd,szWaiting) ;
									return (TRUE) ;
								}

								break ;

		case	IDC_BUTTON_01 :	if(HIWORD(__wParam) == BN_CLICKED)
								{
									__stosq((unsigned long long *) &_Ofn,0,sizeof(OPENFILENAME) / 8) ;
									__stosq((unsigned long long *) _szTmp,0,sizeof(_szTmp) / 8) ;

									Message(__hWnd,szWaiting) ;

									_Ofn.Flags = OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_LONGNAMES|OFN_NONETWORKBUTTON|OFN_PATHMUSTEXIST ;
									_Ofn.hInstance = hInstance ;
									_Ofn.hwndOwner = __hWnd ;
									_Ofn.lpstrDefExt = "txt" ;
									_Ofn.lpstrFile = _szTmp ;
									_Ofn.nMaxFile = sizeof(_szTmp) ;
									_Ofn.lStructSize = sizeof(OPENFILENAME) ;
									_Ofn.nFilterIndex = 1 ;
									_Ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0Password files (*.Psw)\0*.Psw\0Csv Files (*.csv)\0*.csv\0All files\0*.*\0\0" ;

									if(GetOpenFileName(&_Ofn))
									{
										SetDlgItemText(__hWnd,IDC_EDIT_01,_szTmp) ;
										Message(__hWnd,szWaiting) ;
									}

									return (TRUE) ;
								}

								break ;

		case	IDOK :			if(HIWORD(__wParam) == BN_CLICKED)
								{
									if(!GetDlgItemText(__hWnd,IDC_EDIT_01,_szTmp,sizeof(_szTmp)))
										Error("You have not selected a file to import!") ;
									else
										Import_Run(__hWnd) ;

									return (TRUE) ;
								}

								break ;

		case	IDCANCEL :		if(HIWORD(__wParam) == BN_CLICKED)
								{
									DestroyWindow(__hWnd) ;
									return (TRUE) ;
								}

								break ;
	}

	return (FALSE) ;
}

LRESULT CALLBACK DlgImportPassword(HWND __hWnd,UINT __uMsg,WPARAM __wParam,LPARAM __lParam)
{
	switch (__uMsg)
	{
		case	WM_INITDIALOG :	Import_InitDialog(__hWnd) ;
								return (TRUE) ;

		case	WM_ACTIVATE :	if(LOWORD(__wParam) == WA_INACTIVE)	hDialogs = NULL ;
								else								hDialogs = __hWnd ;

								return (TRUE) ;

		case	WM_COMMAND :	return (Import_WmCommand(__hWnd,__wParam)) ;

		case	WM_CTLCOLORSTATIC :
		case	WM_CTLCOLORBTN :
		case	WM_CTLCOLORLISTBOX :
		case	WM_CTLCOLOREDIT :
		case	WM_CTLCOLORDLG :
									return (DlgCtlColor(__hWnd,__uMsg,__wParam)) ;
	}

	return (FALSE) ;
}
