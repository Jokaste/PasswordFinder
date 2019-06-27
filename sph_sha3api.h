//=====================================================================
//	SHA3api_ref.h - definition of the cryptographic API
//=====================================================================
#ifndef SHA3API_H
#define SHA3API_H

//#define NO_LONG_LONG		// uncomment if 64-bit values not supported
//#define const
		// uncoment if "const" not recognised by the target compiler
		// also note that "data" is a reserved word in some systems

typedef unsigned char BitSequence;

#ifndef NO_LONG_LONG
typedef unsigned long long DataLength;
#else
typedef unsigned long DataLength;
#endif

typedef enum { SUCCESS = 0, FAIL = 1, BAD_HASHBITLEN = 2 } HashReturn;

#include "sph_blender.h"		// structure definition

//========================================================
// initialise the state structure for the given digest length
//========================================================
HashReturn Blender_Init(Blender_hashState *state, int hashbitlen);

//========================================================
// update the hash with the data given 
//========================================================
HashReturn Blender_Update (Blender_hashState *state, const BitSequence *dta,DataLength databitlen);

//========================================================
// finalise the hash and output the message digest
//========================================================
HashReturn Blender_Final(Blender_hashState *state, BitSequence *hashval);


//========================================================
// top level all-in-one function call
//========================================================

HashReturn Blender_Hash(int hashbitlen,const BitSequence *data,DataLength databitlen,BitSequence *hashval) ;


//#include "Blender.c"

#endif	//SHA3API_H
