#include "Crack_All.h"
#include <stdlib.h>

int HashEnd(register LPDB_GEN __lpDb,LPBYTE __lpszHashVal)
{
	char				_szTmp[1024], _szHexString[1024] ;
	register LPSTR		_lpszTmp ;

	_lpszTmp = _szTmp ;

	Hack_Hex(__lpszHashVal,_szHexString,__lpDb->iHashNumberOfBytes) ;

	if(__lpDb->iSecure == 1)
	{
		if(SQLiteFindHash(__lpDb,_szHexString) == CRACK_FAIL)
		{
			sqlite3_snprintf(sizeof(_szTmp),_lpszTmp,szTbl_Fmt_Insert,__lpDb->lpszStringToHash,_szHexString) ;
			return (SQLiteExec(__lpDb->Db,_lpszTmp)) ;
		}
	}
	else
	{
		sqlite3_snprintf(sizeof(_szTmp),_lpszTmp,szTbl_Fmt_Insert,__lpDb->lpszStringToHash,_szHexString) ;

		if(sqlite3_exec(__lpDb->Db,_lpszTmp,0,0,NULL) == SQLITE_OK)
			return (CRACK_SUCCESS) ;
	}

	return (CRACK_FAIL) ;
}

int Abacus_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	register LPSTR		_lpszTmp, _lpszHashVal ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	if(Abacus_Hash(__lpDb->iHashNumberOfBits,__lpDb->lpszStringToHash,__lpDb->iStringLength * 8,_lpszHashVal))
		return (CRACK_FAIL) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int AriRang_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	register LPSTR		_lpszTmp, _lpszHashVal ;
	unsigned __int64	_DataBitLength ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	_DataBitLength = __lpDb->iStringLength * 8 ;

	if(AriRang_Hash(__lpDb->iHashNumberOfBits,__lpDb->lpszStringToHash,&_DataBitLength,_lpszHashVal) != 1)
		return (CRACK_FAIL) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Aurora_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	register LPSTR		_lpszTmp, _lpszHashVal ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	if(Aurora_Hash(__lpDb->iHashNumberOfBits,__lpDb->lpszStringToHash,__lpDb->iStringLength * 8,_lpszHashVal))
		return (CRACK_FAIL) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Blake_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_blake224_context	_Context224 ;
	sph_blake256_context	_Context256 ;
	sph_blake384_context	_Context384 ;
	sph_blake512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_blake224_init(&_Context224) ;
						sph_blake224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_blake224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_blake256_init(&_Context256) ;
						sph_blake256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_blake256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_blake384_init(&_Context384) ;
						sph_blake384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_blake384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_blake512_init(&_Context512) ;
						sph_blake512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_blake512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Blender_Db_Insert(LPDB_GEN __lpDb,char *__lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	if(BlenderHash(__lpDb->iHashNumberOfBits,__lpDb->lpszStringToHash,__lpDb->iStringLength * 8,_lpszHashVal))
		return (CRACK_FAIL) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Bmw_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_bmw224_context	_Context224 ;
	sph_bmw256_context	_Context256 ;
	sph_bmw384_context	_Context384 ;
	sph_bmw512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_bmw224_init(&_Context224) ;
						sph_bmw224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_bmw224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_bmw256_init(&_Context256) ;
						sph_bmw256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_bmw256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_bmw384_init(&_Context384) ;
						sph_bmw384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_bmw384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_bmw512_init(&_Context512) ;
						sph_bmw512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_bmw512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Cheetah_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	if(Cheetah_Hash(__lpDb->iHashNumberOfBits,__lpDb->lpszStringToHash,__lpDb->iStringLength * 8,_lpszHashVal))
		return (CRACK_FAIL) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Crunch_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	Sph_Crunch_Init_224() ;
						Sph_Crunch_Hash_224(__lpDb->lpszStringToHash,__lpDb->iStringLength * 8,_lpszHashVal) ;
						Sph_Crunch_Final_224(_lpszHashVal);
						break ;

		case	256 :	Sph_Crunch_Init_256() ;
						Sph_Crunch_Hash_256(__lpDb->lpszStringToHash,__lpDb->iStringLength * 8,_lpszHashVal) ;
						Sph_Crunch_Final_256(_lpszHashVal);
						break ;

		case	384 :	Sph_Crunch_Init_384() ;
						Sph_Crunch_Hash_384(__lpDb->lpszStringToHash,__lpDb->iStringLength * 8,_lpszHashVal) ;
						Sph_Crunch_Final_384(_lpszHashVal);
						break ;

		case	512 :	Sph_Crunch_Init_512() ;
						Sph_Crunch_Hash_512(__lpDb->lpszStringToHash,__lpDb->iStringLength * 8,_lpszHashVal) ;
						Sph_Crunch_Final_512(_lpszHashVal);
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int CubeHash_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_cubehash224_context	_Context224 ;
	sph_cubehash256_context	_Context256 ;
	sph_cubehash384_context	_Context384 ;
	sph_cubehash512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_cubehash224_init(&_Context224) ;
						sph_cubehash224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_cubehash224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_cubehash256_init(&_Context256) ;
						sph_cubehash256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_cubehash256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_cubehash384_init(&_Context384) ;
						sph_cubehash384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_cubehash384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_cubehash512_init(&_Context512) ;
						sph_cubehash512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_cubehash512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Echo_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_echo224_context	_Context224 ;
	sph_echo256_context	_Context256 ;
	sph_echo384_context	_Context384 ;
	sph_echo512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_echo224_init(&_Context224) ;
						sph_echo224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_echo224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_echo256_init(&_Context256) ;
						sph_echo256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_echo256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_echo384_init(&_Context384) ;
						sph_echo384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_echo384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_echo512_init(&_Context512) ;
						sph_echo512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_echo512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Fugue_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_fugue224_context	_Context224 ;
	sph_fugue256_context	_Context256 ;
	sph_fugue384_context	_Context384 ;
	sph_fugue512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_fugue224_init(&_Context224) ;
						sph_fugue224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_fugue224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_fugue256_init(&_Context256) ;
						sph_fugue256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_fugue256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_fugue384_init(&_Context384) ;
						sph_fugue384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_fugue384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_fugue512_init(&_Context512) ;
						sph_fugue512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_fugue512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Groestl_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_groestl224_context	_Context224 ;
	sph_groestl256_context	_Context256 ;
	sph_groestl384_context	_Context384 ;
	sph_groestl512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_groestl224_init(&_Context224) ;
						sph_groestl224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_groestl224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_groestl256_init(&_Context256) ;
						sph_groestl256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_groestl256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_groestl384_init(&_Context384) ;
						sph_groestl384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_groestl384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_groestl512_init(&_Context512) ;
						sph_groestl512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_groestl512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Hamsi_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_hamsi224_context	_Context224 ;
	sph_hamsi256_context	_Context256 ;
	sph_hamsi384_context	_Context384 ;
	sph_hamsi512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_hamsi224_init(&_Context224) ;
						sph_hamsi224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_hamsi224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_hamsi256_init(&_Context256) ;
						sph_hamsi256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_hamsi256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_hamsi384_init(&_Context384) ;
						sph_hamsi384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_hamsi384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_hamsi512_init(&_Context512) ;
						sph_hamsi512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_hamsi512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Haval_3_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[160] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_haval128_3_context	_Context128 ;
	sph_haval160_3_context	_Context160 ;
	sph_haval192_3_context	_Context192 ;
	sph_haval224_3_context	_Context224 ;
	sph_haval256_3_context	_Context256 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	128 :	sph_haval128_3_init(&_Context128) ;
						sph_haval128_3(&_Context128,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval128_3_close(&_Context128,_lpszHashVal) ;
						break ;

		case	160 :	sph_haval160_3_init(&_Context160) ;
						sph_haval160_3(&_Context160,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval160_3_close(&_Context160,_lpszHashVal) ;
						break ;

		case	192 :	sph_haval192_3_init(&_Context192) ;
						sph_haval192_3(&_Context192,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval192_3_close(&_Context192,_lpszHashVal) ;
						break ;

		case	224 :	sph_haval224_3_init(&_Context224) ;
						sph_haval224_3(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval224_3_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_haval256_3_init(&_Context256) ;
						sph_haval256_3(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval256_3_close(&_Context256,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Haval_4_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[160] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_haval128_4_context	_Context128 ;
	sph_haval160_4_context	_Context160 ;
	sph_haval192_4_context	_Context192 ;
	sph_haval224_4_context	_Context224 ;
	sph_haval256_4_context	_Context256 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	128 :	sph_haval128_4_init(&_Context128) ;
						sph_haval128_4(&_Context128,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval128_4_close(&_Context128,_lpszHashVal) ;
						break ;

		case	160 :	sph_haval160_4_init(&_Context160) ;
						sph_haval160_4(&_Context160,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval160_4_close(&_Context160,_lpszHashVal) ;
						break ;

		case	192 :	sph_haval192_4_init(&_Context192) ;
						sph_haval192_4(&_Context192,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval192_4_close(&_Context192,_lpszHashVal) ;
						break ;

		case	224 :	sph_haval224_4_init(&_Context224) ;
						sph_haval224_4(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval224_4_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_haval256_4_init(&_Context256) ;
						sph_haval256_4(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval256_4_close(&_Context256,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Haval_5_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[160] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_haval128_5_context	_Context128 ;
	sph_haval160_5_context	_Context160 ;
	sph_haval192_5_context	_Context192 ;
	sph_haval224_5_context	_Context224 ;
	sph_haval256_5_context	_Context256 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	128 :	sph_haval128_5_init(&_Context128) ;
						sph_haval128_5(&_Context128,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval128_5_close(&_Context128,_lpszHashVal) ;
						break ;

		case	160 :	sph_haval160_5_init(&_Context160) ;
						sph_haval160_5(&_Context160,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval160_5_close(&_Context160,_lpszHashVal) ;
						break ;

		case	192 :	sph_haval192_5_init(&_Context192) ;
						sph_haval192_5(&_Context192,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval192_5_close(&_Context192,_lpszHashVal) ;
						break ;

		case	224 :	sph_haval224_5_init(&_Context224) ;
						sph_haval224_5(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval224_5_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_haval256_5_init(&_Context256) ;
						sph_haval256_5(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_haval256_5_close(&_Context256,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Jh_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_jh224_context	_Context224 ;
	sph_jh256_context	_Context256 ;
	sph_jh384_context	_Context384 ;
	sph_jh512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_jh224_init(&_Context224) ;
						sph_jh224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_jh224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_jh256_init(&_Context256) ;
						sph_jh256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_jh256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_jh384_init(&_Context384) ;
						sph_jh384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_jh384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_jh512_init(&_Context512) ;
						sph_jh512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_jh512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Keccak_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_keccak224_context	_Context224 ;
	sph_keccak256_context	_Context256 ;
	sph_keccak384_context	_Context384 ;
	sph_keccak512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_keccak224_init(&_Context224) ;
						sph_keccak224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_keccak224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_keccak256_init(&_Context256) ;
						sph_keccak256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_keccak256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_keccak384_init(&_Context384) ;
						sph_keccak384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_keccak384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_keccak512_init(&_Context512) ;
						sph_keccak512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_keccak512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Luffa_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_luffa224_context	_Context224 ;
	sph_luffa256_context	_Context256 ;
	sph_luffa384_context	_Context384 ;
	sph_luffa512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_luffa224_init(&_Context224) ;
						sph_luffa224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_luffa224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_luffa256_init(&_Context256) ;
						sph_luffa256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_luffa256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_luffa384_init(&_Context384) ;
						sph_luffa384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_luffa384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_luffa512_init(&_Context512) ;
						sph_luffa512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_luffa512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Maraca_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	Maraca_Hash(__lpDb->lpszStringToHash,__lpDb->iStringLength,NULL,0,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Md2_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_md2_context	_Context ;
	_lpszTmp = _szTmp ;

	_lpszHashVal = _szHashVal ;

	sph_md2_init(&_Context) ;
	sph_md2(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_md2_close(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Md4_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_md4_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_md4_init(&_Context) ;
	sph_md4(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_md4_close(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Md5_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
				char	_szTmp[1024], _szHashVal[256] ;
	register	LPSTR	_lpszTmp, _lpszHashVal ;

	sph_md5_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_md5_init(&_Context) ;
	sph_md5(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_md5_close(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Md6_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	Md6_Hash(__lpDb->iHashNumberOfBits,__lpDb->lpszStringToHash,__lpDb->iStringLength * 8,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Panama_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_panama_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_panama_init(&_Context) ;
	sph_panama(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_panama_close(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int RadioGatun32_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_radiogatun32_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_radiogatun32_init(&_Context) ;
	sph_radiogatun32(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_radiogatun32_close(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int RadioGatun64_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_radiogatun64_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_radiogatun64_init(&_Context) ;
	sph_radiogatun64(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_radiogatun64_close(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int RipeMd_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[160] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_ripemd128_context	_Context128 ;
	sph_ripemd160_context	_Context160 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	128 :	sph_ripemd128_init(&_Context128) ;
						sph_ripemd128(&_Context128,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_ripemd128_close(&_Context128,_lpszHashVal) ;
						break ;

		case	160 :	sph_ripemd160_init(&_Context160) ;
						sph_ripemd160(&_Context160,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_ripemd160_close(&_Context160,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Sarmal_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	Sarmal_HashState	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	Sph_Sarmal_Init(&_Context,__lpDb->iHashNumberOfBits) ;
	Sph_Sarmal_Update(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength * 8) ;
	Sph_Sarmal_Final(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Sha0_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_sha0_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_sha0_init(&_Context) ;
	sph_sha0(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_sha0_close(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Sha1_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_sha1_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_sha1_init(&_Context) ;
	sph_sha1(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_sha1_close(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Sha_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_sha224_context	_Context224 ;
	sph_sha256_context	_Context256 ;
	sph_sha384_context	_Context384 ;
	sph_sha512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_sha224_init(&_Context224) ;
						sph_sha224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_sha224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_sha256_init(&_Context256) ;
						sph_sha256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_sha256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_sha384_init(&_Context384) ;
						sph_sha384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_sha384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_sha512_init(&_Context512) ;
						sph_sha512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_sha512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Shabal_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_shabal192_context	_Context192 ;
	sph_shabal224_context	_Context224 ;
	sph_shabal256_context	_Context256 ;
	sph_shabal384_context	_Context384 ;
	sph_shabal512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	192 :	sph_shabal192_init(&_Context192) ;
						sph_shabal192(&_Context192,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_shabal192_close(&_Context192,_lpszHashVal) ;
						break ;

		case	224 :	sph_shabal224_init(&_Context224) ;
						sph_shabal224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_shabal224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_shabal256_init(&_Context256) ;
						sph_shabal256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_shabal256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_shabal384_init(&_Context384) ;
						sph_shabal384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_shabal384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_shabal512_init(&_Context512) ;
						sph_shabal512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_shabal512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Shavite_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_shavite224_context	_Context224 ;
	sph_shavite256_context	_Context256 ;
	sph_shavite384_context	_Context384 ;
	sph_shavite512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_shavite224_init(&_Context224) ;
						sph_shavite224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_shavite224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_shavite256_init(&_Context256) ;
						sph_shavite256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_shavite256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_shavite384_init(&_Context384) ;
						sph_shavite384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_shavite384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_shavite512_init(&_Context512) ;
						sph_shavite512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_shavite512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Skein_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_skein224_context	_Context224 ;
	sph_skein256_context	_Context256 ;
	sph_skein384_context	_Context384 ;
	sph_skein512_context	_Context512 ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	switch(__lpDb->iHashNumberOfBits)
	{
		case	224 :	sph_skein224_init(&_Context224) ;
						sph_skein224(&_Context224,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_skein224_close(&_Context224,_lpszHashVal) ;
						break ;

		case	256 :	sph_skein256_init(&_Context256) ;
						sph_skein256(&_Context256,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_skein256_close(&_Context256,_lpszHashVal) ;
						break ;

		case	384 :	sph_skein384_init(&_Context384) ;
						sph_skein384(&_Context384,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_skein384_close(&_Context384,_lpszHashVal) ;
						break ;

		case	512 :	sph_skein512_init(&_Context512) ;
						sph_skein512(&_Context512,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
						sph_skein512_close(&_Context512,_lpszHashVal) ;
						break ;
	}

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int StreamHash_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	HashStream_HashState	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	HashStream_Init(&_Context,__lpDb->iHashNumberOfBits) ;
	HashStream_Update(&_Context,__lpDb->lpszStringToHash,__lpDb->iHashNumberOfBytes * 8) ;
	HashStream_Final(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Tiger_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_tiger_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_tiger_init(&_Context) ;
	sph_tiger(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_tiger_close(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Waterfall_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	Waterfall_HashState	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	Waterfall_Init(&_Context,__lpDb->iHashNumberOfBits) ;
	Waterfall_Update(&_Context,__lpDb->lpszStringToHash,__lpDb->iHashNumberOfBytes * 8) ;
	Waterfall_Final(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Whirlpool_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	LPSTR				_lpszTmp ;
	register LPSTR		_lpszHashVal ;

	sph_whirlpool_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_whirlpool_init(&_Context) ;
	sph_whirlpool(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_whirlpool_close(&_Context,_lpszHashVal) ;

	return (HashEnd(__lpDb,_lpszHashVal)) ;
}

int Sha1Md5_N_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	char				_szMd5[256], _szSha1[256] ;
	LPSTR				_lpszTmp ;
	LPSTR				_lpszSha1, _lpszMd5 ;
	register LPSTR		_lpszHashVal ;

	sph_md5_context		_Md5Context ;
	sph_sha1_context	_ShaContext ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;
	_lpszSha1 = _szSha1 ;
	_lpszMd5 = _szMd5 ;

	sph_sha1_init(&_ShaContext) ;
	sph_sha1(&_ShaContext,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_sha1_close(&_ShaContext,_lpszSha1) ;

	sph_md5_init(&_Md5Context) ;
	sph_md5(&_Md5Context,_lpszSha1,HASH_BYTES_160) ;
	sph_md5_close(&_Md5Context,_lpszMd5) ;

	return (HashEnd(__lpDb,_lpszMd5)) ;
}

int Md5Sha1_N_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	char				_szMd5[256], _szSha1[256] ;
	LPSTR				_lpszTmp ;
	LPSTR				_lpszSha1, _lpszMd5 ;
	register LPSTR		_lpszHashVal ;

	sph_md5_context		_Md5Context ;
	sph_sha1_context	_ShaContext ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;
	_lpszSha1 = _szSha1 ;
	_lpszMd5 = _szMd5 ;

	sph_md5_init(&_Md5Context) ;
	sph_md5(&_Md5Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_md5_close(&_Md5Context,_lpszMd5) ;

	sph_sha1_init(&_ShaContext) ;
	sph_sha1(&_ShaContext,_lpszMd5,HASH_BYTES_128) ;
	sph_sha1_close(&_ShaContext,_lpszSha1) ;

	return (HashEnd(__lpDb,_lpszSha1)) ;
}

int Sha1Sha1_N_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	char				_szSha1_1[256], _szSha1_2[256] ;
	LPSTR				_lpszTmp ;
	LPSTR				_lpszSha1_1, _lpszSha1_2 ;
	register LPSTR		_lpszHashVal ;

	sph_sha1_context	_ShaContext ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;
	_lpszSha1_1 = _szSha1_1 ;
	_lpszSha1_2 = _szSha1_2 ;

	sph_sha1_init(&_ShaContext) ;
	sph_sha1(&_ShaContext,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_md5_close(&_ShaContext,_lpszSha1_1) ;

	sph_sha1_init(&_ShaContext) ;
	sph_sha1(&_ShaContext,_lpszSha1_1,HASH_BYTES_160) ;
	sph_sha1_close(&_ShaContext,_lpszSha1_2) ;

	return (HashEnd(__lpDb,_lpszSha1_2)) ;
}

int Sha1Md5_A_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	char				_szMd5[256], _szSha1[256] ;
	char				_szHexString[512] ;
	LPSTR				_lpszTmp ;
	LPSTR				_lpszSha1, _lpszMd5 ;
	register LPSTR		_lpszHashVal ;

	sph_md5_context		_Md5Context ;
	sph_sha1_context	_ShaContext ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;
	_lpszSha1 = _szSha1 ;
	_lpszMd5 = _szMd5 ;

	sph_sha1_init(&_ShaContext) ;
	sph_sha1(&_ShaContext,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_sha1_close(&_ShaContext,_lpszSha1) ;

	Hack_Hex(_lpszSha1,_szHexString,__lpDb->iHashNumberOfBytes) ;

	sph_md5_init(&_Md5Context) ;
	sph_md5(&_Md5Context,_szHexString,HASH_BYTES_160 * 2) ;
	sph_md5_close(&_Md5Context,_lpszMd5) ;

	return (HashEnd(__lpDb,_lpszMd5)) ;
}

int Md5Sha1_A_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	char				_szMd5[256], _szSha1[256] ;
	char				_szHexString[512] ;
	LPSTR				_lpszTmp ;
	LPSTR				_lpszSha1, _lpszMd5 ;
	register LPSTR		_lpszHashVal ;

	sph_md5_context		_Md5Context ;
	sph_sha1_context	_ShaContext ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;
	_lpszSha1 = _szSha1 ;
	_lpszMd5 = _szMd5 ;

	sph_md5_init(&_Md5Context) ;
	sph_md5(&_Md5Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_md5_close(&_Md5Context,_lpszMd5) ;

	Hack_Hex(_lpszMd5,_szHexString,16) ;

	sph_sha1_init(&_ShaContext) ;
	sph_sha1(&_ShaContext,_szHexString,HASH_BYTES_128 * 2) ;
	sph_sha1_close(&_ShaContext,_lpszSha1) ;

	return (HashEnd(__lpDb,_lpszSha1)) ;
}

int Sha1Sha1_A_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
	char				_szTmp[1024], _szHashVal[256] ;
	char				_szSha1_1[256], _szSha1_2[256] ;
	char				_szHexString[512] ;
	LPSTR				_lpszTmp ;
	LPSTR				_lpszSha1_1, _lpszSha1_2 ;
	register LPSTR		_lpszHashVal ;

	sph_sha1_context	_ShaContext ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;
	_lpszSha1_1 = _szSha1_1 ;
	_lpszSha1_2 = _szSha1_2 ;

	sph_sha1_init(&_ShaContext) ;
	sph_sha1(&_ShaContext,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_md5_close(&_ShaContext,_lpszSha1_1) ;

	Hack_Hex(_lpszSha1_1,_szHexString,16) ;

	sph_sha1_init(&_ShaContext) ;
	sph_sha1(&_ShaContext,_szHexString,HASH_BYTES_160 * 2) ;
	sph_sha1_close(&_ShaContext,_lpszSha1_2) ;

	return (HashEnd(__lpDb,_lpszSha1_2)) ;
}

int Md5Md5_N_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
				char	_szTmp[1024], _szHashVal[256] ;
	register	LPSTR	_lpszTmp, _lpszHashVal ;

	sph_md5_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_md5_init(&_Context) ;
	sph_md5(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_md5_close(&_Context,_lpszHashVal) ;

	sph_md5_init(&_Context) ;
	sph_md5(&_Context,_lpszHashVal,16) ;
	sph_md5_close(&_Context,_lpszTmp) ;

	return (HashEnd(__lpDb,_lpszTmp)) ;
}

int Md5Md5_A_Db_Insert(LPDB_GEN __lpDb,LPSTR __lpszUnUsed)
{
				char	_szTmp[1024], _szHashVal[256] ;
	char				_szHexString[512] ;
	register	LPSTR	_lpszTmp, _lpszHashVal ;

	sph_md5_context	_Context ;

	_lpszTmp = _szTmp ;
	_lpszHashVal = _szHashVal ;

	sph_md5_init(&_Context) ;
	sph_md5(&_Context,__lpDb->lpszStringToHash,__lpDb->iStringLength) ;
	sph_md5_close(&_Context,_lpszHashVal) ;

	Hack_Hex(_lpszHashVal,_szHexString,16) ;

	sph_md5_init(&_Context) ;
	sph_md5(&_Context,_szHexString,16) ;
	sph_md5_close(&_Context,_lpszTmp) ;

	return (HashEnd(__lpDb,_lpszTmp)) ;
}
