//=====================================================================
//	Blender source code
//
//	This is the simplified version, restricted to word sizes that are
//	a power of 2 and omitting all of the gate-reduced variations.
//	The upper limits have been arbitrarily set at eight bytes per
//	word and ten words per message digest.
//	The source code for a specific variation in a specific environment
//	should be a lot smaller than the code presented here.
//
//=====================================================================

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "sph_sha3api.h"

char *Author = "Colin Bradbury";
char *Algorithm = "Blender";

	// hash engine codes
typedef enum { Vgen=1,			// general case - no optimised routine available
		V96, V112, V128, V144, V160,		// 16-bit words
		//V168, V216, V240,					// 24-bit words
		V192, V224, V256, V288, V320,		// 32-bit words
		//V280, V360, V400,					// 40-bit words
		//V336, V432, V480,					// 48-bit words
		//V392, V504, V560,					// 56-bit words
		V384, V448, V512, V576, V640		// 64-bit words
} Variant;

	// hash engine lookup table - index by [wordSizeBytes-2][wordCount-6]
const Uint8 memberTable[7][5] = {
	{ V96, V112, V128, V144, V160 },		// 16-bit words
	{ Vgen, Vgen, Vgen, Vgen, Vgen },		// 24-bit words
	{ V192, V224, V256, V288, V320 },		// 32-bit words
	{ Vgen, Vgen, Vgen, Vgen, Vgen },		// 40-bit words
	{ Vgen, Vgen, Vgen, Vgen, Vgen },		// 48-bit words
	{ Vgen, Vgen, Vgen, Vgen, Vgen },		// 56-bit words
	{ V384, V448, V512, V576, V640 }		// 64-bit words
};

// constants used in padding the last byte of the message
const BitSequence bigendbit[8] = {
	0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02 };
const BitSequence bigendfill[8] = {
	0x00, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01 };
const BitSequence littleendbit[8] = {
	0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 };
const BitSequence littleendfill[8] = {
	0x00, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80 };

// initial values of state variables
#ifndef NO_LONG_LONG			// 64-bit values ok
const Uint64 Hinit64 [] = {		// SHA-512 and SHA-384 H0 values
	0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b,
	0xa54ff53a5f1d36f1, 0x510e527fade682d1, 0x9b05688c2b3e6c1f,
	0x1f83d9abfb41bd6b, 0x5be0cd19137e2179,
	0xcbbb9d5dc1059ed8, 0x629a292a367cd507, 0x9159015a3070dd17,
	0x152fecd8f70e5939, 0x67332667ffc00b31, 0x8eb44a8768581511 };
#else							// split values in half (upper, lower)
const Uint32 Hinit64 [] = {		// SHA-512 and SHA-384 H0 values
	0x6a09e667, 0xf3bcc908, 0xbb67ae85, 0x84caa73b, 0x3c6ef372, 0xfe94f82b,
	0xa54ff53a, 0x5f1d36f1, 0x510e527f, 0xade682d1, 0x9b05688c, 0x2b3e6c1f,
	0x1f83d9ab, 0xfb41bd6b, 0x5be0cd19, 0x137e2179,
	0xcbbb9d5d, 0xc1059ed8, 0x629a292a, 0x367cd507, 0x9159015a, 0x3070dd17,
	0x152fecd8, 0xf70e5939, 0x67332667, 0xffc00b31, 0x8eb44a87, 0x68581511 };
#endif

const Uint32 Hinit32 [] = {		// SHA-256 and SHA-224 H0 values
	0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f,
	0x9b05688c, 0x1f83d9ab, 0x5be0cd19, 0xcbbb9d5d, 0x629a292a,
	0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
	0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4 };

const Uint16 Hinit16 [] = {		// SHA-1 H0 values expressed as shorts
	0x6745, 0x2301, 0xefcd, 0xab89, 0x98ba, 0xdcfe,
	0x1032, 0x5476, 0xc3d2, 0xe1f0 };

Blender_hashState ss;		// local workspace


//========================================================
// utility routines to output intermediate values in each round
//========================================================
#ifdef VERBOSE
FILE *fp_log;
Uint32 vround;					// round number
void showHex64 (unsigned long long val);
void showBytes (int count, Uint8 *values);
// dual compression function versions
void showState64 (unsigned long long fragment, unsigned long long T1, 
				  unsigned long long T2, int carry1, int carry2);
void showState32 (Uint32 fragment, Uint32 T1, Uint32 T2, int carry1, int carry2);
void showState16 (Uint16 fragment, Uint16 T1, Uint16 T2, int carry1, int carry2);
void showState64n (Uint32 fraglo, Uint32 fraghi, Uint32 T1lo, Uint32 T1hi,
				   Uint32 T2lo, Uint32 T2hi, int carry1, int carry2);
// triple compression function versions
void showState64t (unsigned long long fragment, unsigned long long T1, 
		unsigned long long T2, unsigned long long T3, int carry1, int carry2, int carry3);
void showState32t (Uint32 fragment, Uint32 T1, Uint32 T2, Uint32 T3,
				   int carry1, int carry2, int carry3);
void showState16t (Uint16 fragment, Uint16 T1, Uint16 T2, Uint16 T3,
				   int carry1, int carry2, int carry3);
void showState64tn (Uint32 fraglo, Uint32 fraghi, Uint32 T1lo, Uint32 T1hi, Uint32 T2lo,
		Uint32 T2hi, Uint32 T3lo, Uint32 T3hi, int carry1, int carry2, int carry3);
#endif


//========================================================
// Initialise the state structure appropriately for the given
// digest length - the settings may be overridden after this call
//========================================================
HashReturn Blender_Init (Blender_hashState *state, int hashbitlen) {
	register int b, f, w, i = 0;
	// first extract the word size and number of words
	if (((hashbitlen % 64) == 0) && (hashbitlen >= 384)) {
		b = f = 8;					// 8 bytes / word
		w = hashbitlen / 64;		// 6 to 10 words
	} else if (((hashbitlen % 32) == 0) && (hashbitlen > 160)) {
		b = f = 4;					// 4 bytes / word
		w = hashbitlen / 32;		// 6 to 10 words
	} else if ((hashbitlen % 16) == 0) {
		b = f = 2;					// 2 bytes / word
		w = hashbitlen / 16;		// 6 to 10 words
	}	// any others need to be set in the structure outside here
	else
		return BAD_HASHBITLEN;				// unknown digest length
	// validate the derived parameters
	if ((w < 6) || (w > MAXWORDS) || (b < 2) || (b > 8))
		return BAD_HASHBITLEN;				// invalid parameters
	if (f == b)								// not gate-reduced
		i = memberTable[b-2][w-6];			// look up member id
	else
		i = Vgen;		// use generalised/universal  hash routine

	memset(state, 0x00, sizeof(*state));	// clear whole sructure
	//state->hashBitLen = hashbitlen;		// not used
	state->member = i;				// remember which variant is being used
	state->wordCount = w;			// save number of words in digest
	state->wordSizeBytes = b;		// save number of bytes per word
	state->fragSizeBytes = f;		// save number of bytes per fragment
	state->bitEndianity = 1;		// default to big-endian bit packing
									// change outside if little-endian
	state->blockSizeFrags = 16;		// default block size is 16 fragments
	state->minimumRounds = 32;		// note these can be changed outside
	state->roundsToGo = 32;			// first "block" is minimum rounds
	if (state->wordSizeBytes > 4) {		// 64-bit variants
#ifndef NO_LONG_LONG					// 64-bit values ok
		if (hashbitlen == 384) {		// 384-bit digest - load SHA-384 Hinit
			for (i=0; i<5; ++i)
				state->Word[i].ui64 = Hinit64 [8+i];
		} else {					// 512 or 640 - load SHA-512 Hinit
			for (i=0; i<10; ++i)
				state->Word[i].ui64 = Hinit64 [i];
		}
#else	// no long long variables - use two 32-bit values
		if (hashbitlen == 384) {		// 384-bit digest - load SHA-384 Hinit
			for (i=f=0; i<5; ++i) {
				state->Word[i].ui64.hlw = Hinit64 [16+f];
				state->Word[i].ui64.llw = Hinit64 [17+f];
				f += 2;
			}
		} else {					// 512 or 640 - load SHA-512 Hinit
			for (i=f=0; i<MAXWORDS; ++i) {
				state->Word[i].ui64.hlw = Hinit64 [f];
				state->Word[i].ui64.llw = Hinit64 [f+1];
				f += 2;
			}
		}
#endif
	}
	else if (state->wordSizeBytes > 2) {	// 32-bit variants
		if (hashbitlen == 224) {			// 224-bit digest - load SHA-224 Hinit
			for (i=0; i<8; ++i)
				state->Word[i].ui32 = Hinit32 [10+i];
		} else {					// 256 or 320 - load SHA-256 Hinit
			for (i=0; i<MAXWORDS; ++i)
				state->Word[i].ui32 = Hinit32 [i];
		}
	}
	else {							// 16-bit variants - load SHA-1 Hinit
			for (i=0; i<MAXWORDS; ++i)
				state->Word[i].ui16 = Hinit16 [i];
	}

#ifdef VERBOSE
	// output initial state to log file
	if (fp_log == NULL)
		fp_log = fopen("hashlog.txt", "a");
	memcpy (&ss, state, sizeof(*state));
	fprintf(fp_log, "Init(%d)\r\n", (ss.wordCount * ss.wordSizeBytes * 8));
	vround = 0;
	if (state->member == Vgen)
		;
	else if (state->wordSizeBytes > 4)		// 64-bit variants
#ifndef NO_LONG_LONG					// 64-bit values ok
		showState64 (0, 0, 0, 0, 0);
#else
		showState64n (0, 0, 0, 0, 0, 0, 0, 0);
#endif
	else if (state->wordSizeBytes > 2)		// 32-bit variants
		showState32 (0, 0, 0, 0, 0);
	else									// 16-bit variants
		showState16 (0, 0, 0, 0, 0);
#endif

	return SUCCESS;
}

//=============================================================================


//========================================================
// hash engine for 32-bit words, dual compression function
// note that the bytecount is guaranteed to be a multiple of 4
//========================================================
void doHash32x2 (const BitSequence *dta, Uint32 byteCount) {
	// declare register variables in order of frequency of use
	register Uint32 fragment;			// holds assembled input bytes
	register const BitSequence *dptr;	// fast pointer to data
	register Uint32 T1, T2, temp;		// work resisters
	register Uint32 bcount;				// loop control counter
	register Uint8 carry1, carry2;		// final state bits
#ifdef VERBOSE
	register Uint32 fragmem;			// memory of fragment
#endif

	if ((dptr = dta) == 0)	return;		// null pointer
	if (byteCount == 0)		return;		// no data given

	// unpack the carry bits from the state structure
	carry1 = ss.carries & 1;			// first carry bit
	carry2 = (ss.carries >> 1) & 1;	// second carry bit

	// process data 4 bytes at a time until all done
	for (bcount = byteCount; bcount > 0; bcount -= 4) {
		// first pack 4 bytes into a fragment
		fragment = (((((dptr[3] << 8) | dptr[2]) << 8) | dptr[1]) << 8) | dptr[0];
		dptr += 4;						// advance data pointer

		// update the checksum accumulators
		ss.Checksum1.ui32 += fragment;
		ss.Checksum2.ui32 += ~fragment;
#ifdef VERBOSE
		fragmem = fragment;				// save for verbose output
#endif

		// do the even side compression using T1 as a temporary variable
		T1 = ((fragment >> 8) | (fragment << 24)) ^ ss.Word[0].ui32;
		temp = ss.Word[2].ui32;	// fetch the middle even word
		temp = ((temp >> 8) | (temp << 24)) ^ ss.Word[4].ui32;
		if (carry2 == 0) {			// no previous carry
			T2 = T1 + temp;			// add the two pieces together
			if (T2 < (T1 | temp))	// did overflow happen?
				carry2 = 1;			// yes - remember that
			//else carry2 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T2 = T1 + temp + 1;		// add the pieces plus carry
			if (T2 > (T1 | temp))	// did overflow happen?
				carry2 = 0;			// no - remember that
			//else carry2 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T2: %08X", T1);
		//fprintf (fp_log, " + %08X", temp);
		//fprintf (fp_log, " = %d,%08X", carry2, T2);
		//fprintf (fp_log, "\r\n");

		// do the odd side compression using fragment as a temporary variable
		fragment ^= ss.Word[5].ui32;
		temp = ss.Word[3].ui32;	// fetch the middle odd word
		temp = ((temp << 8) | (temp >> 24)) ^ ss.Word[1].ui32;
		if (carry1 == 0) {			// no previous carry
			T1 = fragment + temp;	// add the two pieces together
			if (T1 < (fragment | temp))	// did overflow happen?
				carry1 = 1;			// yes - remember that
			//else carry1 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T1 = fragment + temp + 1;	// add the pieces plus carry
			if (T1 > (fragment | temp))	// did overflow happen?
				carry1 = 0;			// no - remember that
			//else carry1 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T1: %08X", fragment);
		//fprintf (fp_log, " + %08X", temp);
		//fprintf (fp_log, " = %d,%08X", carry1, T1);
		//fprintf (fp_log, "\r\n");

		// now rotate the compression outputs
		if ((carry1 ^ carry2) != 0) {	// one carry - rotate 7
			T1 = (T1 << 7) | (T1 >> 25);
			T2 = (T2 >> 7) | (T2 << 25);
		} else if (carry1 == 0) {		// no carries - rotate 8
			T1 = (T1 << 8) | (T1 >> 24);
			T2 = (T2 >> 8) | (T2 << 24);
		} else {						// two carries - rotate 6
			T1 = (T1 << 6) | (T1 >> 26);
			T2 = (T2 >> 6) | (T2 << 26);
		}

		// finally do the expansion and summation
		temp = ss.Word[0].ui32;		// word to rotate and wrap around
		temp = (temp >> 7) | (temp << 25);	// do rotation
		ss.Sum[0].ui32 += 
			(ss.Word[0].ui32 = ss.Word[1].ui32 ^ T2);
		ss.Sum[1].ui32 += 
			(ss.Word[1].ui32 = ss.Word[2].ui32 ^ T1);
		ss.Sum[2].ui32 += 
			(ss.Word[2].ui32 = ss.Word[3].ui32 ^ T2);
		ss.Sum[3].ui32 += 
			(ss.Word[3].ui32 = ss.Word[4].ui32 ^ T1);
		ss.Sum[4].ui32 += 
			(ss.Word[4].ui32 = ss.Word[5].ui32 ^ T2);
		if (ss.wordCount == 6)			// 6 words
			ss.Sum[5].ui32 += 
				(ss.Word[5].ui32 = temp ^ T1);
		else {								// 7 or 8 words
			ss.Sum[5].ui32 += 
				(ss.Word[5].ui32 = ss.Word[6].ui32 ^ T1);
			if (ss.wordCount == 7)		// 7 words
				ss.Sum[6].ui32 += 
					(ss.Word[6].ui32 = temp ^ T2);
			else {							// 8 words
				ss.Sum[6].ui32 += 
					(ss.Word[6].ui32 = ss.Word[7].ui32 ^ T2);
				ss.Sum[7].ui32 += 
					(ss.Word[7].ui32 = temp ^ T1);
			}
		}

		if (--ss.roundsToGo == 0)	// reduce space left in current block
			ss.roundsToGo = ss.blockSizeFrags;

#ifdef VERBOSE
		++vround;
		showState32 (fragmem, T1, T2, carry1, carry2);
#endif
	}	// end of round

	ss.carries = (carry2 << 1) | (carry1 & 1);		// save the carry bits
}

//========================================================
// hash engine for 16-bit words, dual compression function
// note that the bytecount is guaranteed to be a multiple of 4
//========================================================
void doHash16x2 (const BitSequence *dta, Uint32 byteCount) {
	// declare register variables in order of frequency of use
	register Uint16 fragment;			// holds assembled input bytes
	register const BitSequence *dptr;	// fast pointer to data
	register Uint16 T1, T2, temp;		// work resisters
	register Uint32 bcount;				// loop control counter
	register Uint8 carry1, carry2;		// final state bits
#ifdef VERBOSE
	register Uint16 fragmem;			// memory of fragment
#endif

	if ((dptr = dta) == 0)	return;		// null pointer
	if (byteCount == 0)		return;		// no data given

	// unpack the carry bits from the state structure
	carry1 = ss.carries & 1;			// first carry bit
	carry2 = (ss.carries >> 1) & 1;	// second carry bit

	// process data 2 bytes at a time until all done
	for (bcount = byteCount; bcount > 0; bcount -= 2) {
		// first pack 2 bytes into a fragment
		fragment = (dptr[1] << 8) | dptr[0];
		dptr += 2;						// advance data pointer

		// update the checksum accumulators
		ss.Checksum1.ui16 += fragment;
		ss.Checksum2.ui16 += ~fragment;
#ifdef VERBOSE
		fragmem = fragment;				// save for verbose output
#endif

		// do the even side compression using T1 as a temporary variable
		T1 = ((fragment >> 8) | (fragment << 8)) ^ ss.Word[0].ui16;
		temp = ss.Word[2].ui16;	// fetch the middle even word
		temp = ((temp >> 8) | (temp << 8)) ^ ss.Word[4].ui16;
		if (carry2 == 0) {			// no previous carry
			T2 = T1 + temp;			// add the two pieces together
			if (T2 < (T1 | temp))	// did overflow happen?
				carry2 = 1;			// yes - remember that
			//else carry2 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T2 = T1 + temp + 1;		// add the pieces plus carry
			if (T2 > (T1 | temp))	// did overflow happen?
				carry2 = 0;			// no - remember that
			//else carry2 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T2: %04X", T1);
		//fprintf (fp_log, " + %04X", temp);
		//fprintf (fp_log, " = %d,%04X", carry2, T2);
		//fprintf (fp_log, "\r\n");

		// do the odd side compression using fragment as a temporary variable
		fragment ^= ss.Word[5].ui16;
		temp = ss.Word[3].ui16;	// fetch the middle odd word
		temp = ((temp << 8) | (temp >> 8)) ^ ss.Word[1].ui16;
		if (carry1 == 0) {			// no previous carry
			T1 = fragment + temp;	// add the two pieces together
			if (T1 < (fragment | temp))	// did overflow happen?
				carry1 = 1;			// yes - remember that
			//else carry1 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T1 = fragment + temp + 1;	// add the pieces plus carry
			if (T1 > (fragment | temp))	// did overflow happen?
				carry1 = 0;			// no - remember that
			//else carry1 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T1: %04X", fragment);
		//fprintf (fp_log, " + %04X", temp);
		//fprintf (fp_log, " = %d,%04X", carry1, T1);
		//fprintf (fp_log, "\r\n");

		// now rotate the compression outputs
		if ((carry1 ^ carry2) != 0) {	// one carry - rotate 7
			T1 = (T1 << 7) | (T1 >> 9);
			T2 = (T2 >> 7) | (T2 << 9);
		} else if (carry1 == 0) {		// no carries - rotate 8
			T1 = (T1 << 8) | (T1 >> 8);
			T2 = (T2 >> 8) | (T2 << 8);
		} else {						// two carries - rotate 6
			T1 = (T1 << 6) | (T1 >> 10);
			T2 = (T2 >> 6) | (T2 << 10);
		}

		// finally do the expansion and summation
		temp = ss.Word[0].ui16;		// word to rotate and wrap around
		temp = (temp >> 7) | (temp << 9);	// do rotation
		ss.Sum[0].ui16 += 
			(ss.Word[0].ui16 = ss.Word[1].ui16 ^ T2);
		ss.Sum[1].ui16 += 
			(ss.Word[1].ui16 = ss.Word[2].ui16 ^ T1);
		ss.Sum[2].ui16 += 
			(ss.Word[2].ui16 = ss.Word[3].ui16 ^ T2);
		ss.Sum[3].ui16 += 
			(ss.Word[3].ui16 = ss.Word[4].ui16 ^ T1);
		ss.Sum[4].ui16 += 
			(ss.Word[4].ui16 = ss.Word[5].ui16 ^ T2);
		if (ss.wordCount == 6)			// 6 words
			ss.Sum[5].ui16 += 
				(ss.Word[5].ui16 = temp ^ T1);
		else {								// 7 or 8 words
			ss.Sum[5].ui16 += 
				(ss.Word[5].ui16 = ss.Word[6].ui16 ^ T1);
			if (ss.wordCount == 7)		// 7 words
				ss.Sum[6].ui16 += 
					(ss.Word[6].ui16 = temp ^ T2);
			else {							// 8 words
				ss.Sum[6].ui16 += 
					(ss.Word[6].ui16 = ss.Word[7].ui16 ^ T2);
				ss.Sum[7].ui16 += 
					(ss.Word[7].ui16 = temp ^ T1);
			}
		}

		if (--ss.roundsToGo == 0)	// reduce space left in current block
			ss.roundsToGo = ss.blockSizeFrags;

#ifdef VERBOSE
		++vround;
		showState16 (fragmem, T1, T2, carry1, carry2);
#endif
	}	// end of round

	ss.carries = (carry2 << 1) | (carry1 & 1);		// save the carry bits
}


//========================================================
// hash engine for 64-bit words, dual compression function
// note that the bytecount is guaranteed to be a multiple of 8
//========================================================
#ifndef NO_LONG_LONG					// 64-bit values ok
void doHash64x2 (const BitSequence *dta, Uint32 byteCount) {
	// declare register variables in order of frequency of use
	register Uint64 fragment;			// holds assembled input bytes
	register const BitSequence *dptr;	// fast pointer to data
	register Uint64 T1, T2, temp;		// work resisters
	register Uint32 bcount;				// loop control counter
	register Uint8 carry1, carry2;		// final state bits
#ifdef VERBOSE
	register Uint64 fragmem;			// memory of fragment
#endif

	if ((dptr = dta) == 0)	return;		// null pointer
	if (byteCount == 0)		return;		// no data given

	// unpack the carry bits from the state structure
	carry1 = ss.carries & 1;			// first carry bit
	carry2 = (ss.carries >> 1) & 1;		// second carry bit

	// process data 8 bytes at a time until all done
	for (bcount = byteCount; bcount > 0; bcount -= 8) {
		// first pack 8 bytes into a fragment
		fragment = ((((dptr[7] << 8) | dptr[6]) << 8) | dptr[5]) << 8;
		fragment = ((((fragment | dptr[4]) << 8) | dptr[3]) << 8) | dptr[2];
		fragment = (((fragment << 8) | dptr[1]) << 8) | dptr[0];
		dptr += 8;						// advance data pointer

		// update the checksum accumulators
		ss.Checksum1.ui64 += fragment;
		ss.Checksum2.ui64 += ~fragment;
#ifdef VERBOSE
		fragmem = fragment;				// save for verbose output
#endif

		// do the even side compression using T1 as a temporary variable
		T1 = ((fragment >> 8) | (fragment << 56)) ^ ss.Word[0].ui64;
		temp = ss.Word[2].ui64;	// fetch the middle even word
		temp = ((temp >> 8) | (temp << 56)) ^ ss.Word[4].ui64;
		if (carry2 == 0) {			// no previous carry
			T2 = T1 + temp;			// add the two pieces together
			if (T2 < (T1 | temp))	// did overflow happen?
				carry2 = 1;			// yes - remember that
			//else carry2 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T2 = T1 + temp + 1;		// add the pieces plus carry
			if (T2 > (T1 | temp))	// did overflow happen?
				carry2 = 0;			// no - remember that
			//else carry2 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T2: "); showHex64 (T1);
		//fprintf (fp_log, " + "); showHex64 (temp);
		//fprintf (fp_log, " = %d,", carry2); showHex64 (T2);
		//fprintf (fp_log, "\r\n");

		// do the odd side compression using fragment as a temporary variable
		fragment ^= ss.Word[5].ui64;
		temp = ss.Word[3].ui64;	// fetch the middle odd word
		temp = ((temp << 8) | (temp >> 56)) ^ ss.Word[1].ui64;
		if (carry1 == 0) {			// no previous carry
			T1 = fragment + temp;	// add the two pieces together
			if (T1 < (fragment | temp))	// did overflow happen?
				carry1 = 1;			// yes - remember that
			//else carry1 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T1 = fragment + temp + 1;	// add the pieces plus carry
			if (T1 > (fragment | temp))	// did overflow happen?
				carry1 = 0;			// no - remember that
			//else carry1 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T1: "); showHex64 (fragment);
		//fprintf (fp_log, " + "); showHex64 (temp);
		//fprintf (fp_log, " = %d,", carry1); showHex64 (T1);
		//fprintf (fp_log, "\r\n");

		// now rotate the compression outputs
		if ((carry1 ^ carry2) != 0) {	// one carry - rotate 7
			T1 = (T1 << 7) | (T1 >> 57);
			T2 = (T2 >> 7) | (T2 << 57);
		} else if (carry1 == 0) {		// no carries - rotate 8
			T1 = (T1 << 8) | (T1 >> 56);
			T2 = (T2 >> 8) | (T2 << 56);
		} else {						// two carries - rotate 6
			T1 = (T1 << 6) | (T1 >> 58);
			T2 = (T2 >> 6) | (T2 << 58);
		}

		// finally do the expansion and summation
		temp = ss.Word[0].ui64;		// word to rotate and wrap around
		temp = (temp >> 7) | (temp << 57);	// do rotation
		ss.Sum[0].ui64 += 
			(ss.Word[0].ui64 = ss.Word[1].ui64 ^ T2);
		ss.Sum[1].ui64 += 
			(ss.Word[1].ui64 = ss.Word[2].ui64 ^ T1);
		ss.Sum[2].ui64 += 
			(ss.Word[2].ui64 = ss.Word[3].ui64 ^ T2);
		ss.Sum[3].ui64 += 
			(ss.Word[3].ui64 = ss.Word[4].ui64 ^ T1);
		ss.Sum[4].ui64 += 
			(ss.Word[4].ui64 = ss.Word[5].ui64 ^ T2);
		if (ss.wordCount == 6)			// 6 words
			ss.Sum[5].ui64 += 
				(ss.Word[5].ui64 = temp ^ T1);
		else {								// 7 or 8 words
			ss.Sum[5].ui64 += 
				(ss.Word[5].ui64 = ss.Word[6].ui64 ^ T1);
			if (ss.wordCount == 7)		// 7 words
				ss.Sum[6].ui64 += 
					(ss.Word[6].ui64 = temp ^ T2);
			else {							// 8 words
				ss.Sum[6].ui64 += 
					(ss.Word[6].ui64 = ss.Word[7].ui64 ^ T2);
				ss.Sum[7].ui64 += 
					(ss.Word[7].ui64 = temp ^ T1);
			}
		}

		if (--ss.roundsToGo == 0)	// reduce space left in current block
			ss.roundsToGo = ss.blockSizeFrags;

#ifdef VERBOSE
		++vround;
		showState64 (fragmem, T1, T2, carry1, carry2);
#endif
	}	// end of round

	ss.carries = (carry2 << 1) | (carry1 & 1);		// save the carry bits
}

#else	//NO_LONG_LONG - 8-bit microcontroller version

void Blender_accumulate (Uint64 *sumptr, Uint32 lolw, Uint32 hilw) {
	// update an accumulator in-situ within state structure
	register Uint32 temp;
	temp = sumptr->llw | lolw;
	if ((sumptr->llw += lolw) < temp)	// overflowed
		sumptr->hlw += hilw + 1;
	else
		sumptr->hlw += hilw;
}
void doHash64x2 (const BitSequence *dta, Uint32 byteCount) {
	// declare register variables in order of frequency of use
	register Uint64 fragment;			// holds assembled input bytes
	register const BitSequence *dptr;	// fast pointer to data
	register Uint64 T1, T2, temp, rot;	// work resisters
	register Uint32 bcount;				// loop control counter
	register Uint8 carry1, carry2;		// final state bits
#ifdef VERBOSE
	register Uint64 fragmem;			// memory of fragment
#endif

	if ((dptr = dta) == 0)	return;		// null pointer
	if (byteCount == 0)		return;		// no data given

	// unpack the carry bits from the state structure
	carry1 = ss.carries & 1;			// first carry bit
	carry2 = (ss.carries >> 1) & 1;		// second carry bit

	// process data 8 bytes at a time until all done
	for (bcount = byteCount; bcount > 0; bcount -= 8) {
		// first pack 8 bytes into a fragment
		fragment.hlw = (((((dptr[7] << 8) | dptr[6]) << 8) | dptr[5]) << 8) | dptr[4];
		fragment.llw = (((((dptr[3] << 8) | dptr[2]) << 8) | dptr[1]) << 8) | dptr[0];
		dptr += 8;						// advance data pointer

		// update the checksum accumulators
		temp.llw = ss.Checksum1.ui64.llw | fragment.llw;
		if ((ss.Checksum1.ui64.llw += fragment.llw) < temp.llw)
			ss.Checksum1.ui64.hlw += 1;		// carry out of low half
		ss.Checksum1.ui64.hlw += fragment.hlw;
		temp.llw = ss.Checksum2.ui64.llw | ~fragment.llw;
		if ((ss.Checksum2.ui64.llw += ~fragment.llw) < temp.llw)
			ss.Checksum2.ui64.hlw += 1;		// carry out of low half
		ss.Checksum2.ui64.hlw += ~fragment.hlw;
#ifdef VERBOSE
		fragmem.llw = fragment.llw;			// save for verbose output
		fragmem.hlw = fragment.hlw;
#endif

		// do the even side compression using T1 as a temporary variable
		rot.llw = (fragment.llw >> 8) | (fragment.hlw << 24);
		rot.hlw = (fragment.hlw >> 8) | (fragment.llw << 24);
		T1.llw = rot.llw ^ ss.Word[0].ui64.llw;
		T1.hlw = rot.hlw ^ ss.Word[0].ui64.hlw;
		rot.llw = (ss.Word[2].ui64.llw >> 8) | (ss.Word[2].ui64.hlw << 24);
		rot.hlw = (ss.Word[2].ui64.hlw >> 8) | (ss.Word[2].ui64.llw << 24);
		temp.llw = rot.llw ^ ss.Word[4].ui64.llw;	// fetch the middle even word
		temp.hlw = rot.hlw ^ ss.Word[4].ui64.hlw;
		if (carry2 == 0) {			// no previous carry
			T2.llw = T1.llw + temp.llw;			// add the two pieces together
			if (T2.llw < (T1.llw | temp.llw))	// did overflow happen?
				carry2 = 1;			// yes - remember that
			//else carry2 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T2.llw = T1.llw + temp.llw + 1;		// add the pieces plus carry
			if (T2.llw > (T1.llw | temp.llw))	// did overflow happen?
				carry2 = 0;			// no - remember that
			//else carry2 = 1;		// redundant - it was already 1
		}	// carry2 now holds the carry out of the low half addition
		if (carry2 == 0) {			// no previous carry
			T2.hlw = T1.hlw + temp.hlw;			// add the two pieces together
			if (T2.hlw < (T1.hlw | temp.hlw))	// did overflow happen?
				carry2 = 1;			// yes - remember that
			//else carry2 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T2.hlw = T1.hlw + temp.hlw + 1;		// add the pieces plus carry
			if (T2.hlw > (T1.hlw | temp.hlw))	// did overflow happen?
				carry2 = 0;			// no - remember that
			//else carry2 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T2: %08X%08X", T1.hlw, T1.llw);
		//fprintf (fp_log, " + %08X%08X", temp.hlw, temp.llw);
		//fprintf (fp_log, " = %d,%08X%08X", carry2, T2.hlw, T2.llw);
		//fprintf (fp_log, "\r\n");

		// do the odd side compression using fragment as a temporary variable
		fragment.llw ^= ss.Word[5].ui64.llw;
		fragment.hlw ^= ss.Word[5].ui64.hlw;
		rot.llw = (ss.Word[3].ui64.llw << 8) | (ss.Word[3].ui64.hlw >> 24);
		rot.hlw = (ss.Word[3].ui64.hlw << 8) | (ss.Word[3].ui64.llw >> 24);
		temp.llw = rot.llw ^ ss.Word[1].ui64.llw;	// fetch the middle odd word
		temp.hlw = rot.hlw ^ ss.Word[1].ui64.hlw;
		if (carry1 == 0) {			// no previous carry
			T1.llw = fragment.llw + temp.llw;	// add the two pieces together
			if (T1.llw < (fragment.llw | temp.llw))	// did overflow happen?
				carry1 = 1;			// yes - remember that
			//else carry1 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T1.llw = fragment.llw + temp.llw + 1;	// add the pieces plus carry
			if (T1.llw > (fragment.llw | temp.llw))	// did overflow happen?
				carry1 = 0;			// no - remember that
			//else carry1 = 1;		// redundant - it was already 1
		}	// carry1 now holds the carry out of the low half addition
		if (carry1 == 0) {			// no previous carry
			T1.hlw = fragment.hlw + temp.hlw;	// add the two pieces together
			if (T1.hlw < (fragment.hlw | temp.hlw))	// did overflow happen?
				carry1 = 1;			// yes - remember that
			//else carry1 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T1.hlw = fragment.hlw + temp.hlw + 1;	// add the pieces plus carry
			if (T1.hlw > (fragment.hlw | temp.hlw))	// did overflow happen?
				carry1 = 0;			// no - remember that
			//else carry1 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T1: %08X%08X", fragment.hlw, fragment.llw);
		//fprintf (fp_log, " + %08X%08X", temp.hlw, temp.llw);
		//fprintf (fp_log, " = %d,%08X%08X", carry1, T1.hlw, T1.llw);
		//fprintf (fp_log, "\r\n");

		// now rotate the compression outputs
		if ((carry1 ^ carry2) != 0) {	// one carry - rotate 7
			rot.llw = (T1.llw << 7) | (T1.hlw >> 25);
			T1.hlw = (T1.hlw << 7) | (T1.llw >> 25);
			T1.llw = rot.llw;
			rot.llw = (T2.llw >> 7) | (T2.hlw << 25);
			T2.hlw = (T2.hlw >> 7) | (T2.llw << 25);
			T2.llw = rot.llw;
		} else if (carry1 == 0) {		// no carries - rotate 8
			rot.llw = (T1.llw << 8) | (T1.hlw >> 24);
			T1.hlw = (T1.hlw << 8) | (T1.llw >> 24);
			T1.llw = rot.llw;
			rot.llw = (T2.llw >> 8) | (T2.hlw << 24);
			T2.hlw = (T2.hlw >> 8) | (T2.llw << 24);
			T2.llw = rot.llw;
		} else {						// two carries - rotate 6
			rot.llw = (T1.llw << 6) | (T1.hlw >> 26);
			T1.hlw = (T1.hlw << 6) | (T1.llw >> 26);
			T1.llw = rot.llw;
			rot.llw = (T2.llw >> 6) | (T2.hlw << 26);
			T2.hlw = (T2.hlw >> 6) | (T2.llw << 26);
			T2.llw = rot.llw;
		}

		// finally do the expansion and summation
		temp.llw = (ss.Word[0].ui64.llw >> 7) | (ss.Word[0].ui64.hlw << 25);
		temp.hlw = (ss.Word[0].ui64.hlw >> 7) | (ss.Word[0].ui64.llw << 25);

		ss.Word[0].ui64.llw = ss.Word[1].ui64.llw ^ T2.llw;
		ss.Word[0].ui64.hlw = ss.Word[1].ui64.hlw ^ T2.hlw;
		accumulate (&ss.Sum[0].ui64, ss.Word[0].ui64.llw, ss.Word[0].ui64.hlw);
		ss.Word[1].ui64.llw = ss.Word[2].ui64.llw ^ T1.llw;
		ss.Word[1].ui64.hlw = ss.Word[2].ui64.hlw ^ T1.hlw;
		accumulate (&ss.Sum[1].ui64, ss.Word[1].ui64.llw, ss.Word[1].ui64.hlw);

		ss.Word[2].ui64.llw = ss.Word[3].ui64.llw ^ T2.llw;
		ss.Word[2].ui64.hlw = ss.Word[3].ui64.hlw ^ T2.hlw;
		accumulate (&ss.Sum[2].ui64, ss.Word[2].ui64.llw, ss.Word[2].ui64.hlw);
		ss.Word[3].ui64.llw = ss.Word[4].ui64.llw ^ T1.llw;
		ss.Word[3].ui64.hlw = ss.Word[4].ui64.hlw ^ T1.hlw;
		accumulate (&ss.Sum[3].ui64, ss.Word[3].ui64.llw, ss.Word[3].ui64.hlw);

		ss.Word[4].ui64.llw = ss.Word[5].ui64.llw ^ T2.llw;
		ss.Word[4].ui64.hlw = ss.Word[5].ui64.hlw ^ T2.hlw;
		accumulate (&ss.Sum[4].ui64, ss.Word[4].ui64.llw, ss.Word[4].ui64.hlw);
		if (ss.wordCount == 6) {			// 6 words
			ss.Word[5].ui64.llw = temp.llw ^ T1.llw;
			ss.Word[5].ui64.hlw = temp.hlw ^ T1.hlw;
			accumulate (&ss.Sum[5].ui64, ss.Word[5].ui64.llw, ss.Word[5].ui64.hlw);
		} else {
			ss.Word[5].ui64.llw = ss.Word[6].ui64.llw ^ T1.llw;
			ss.Word[5].ui64.hlw = ss.Word[6].ui64.hlw ^ T1.hlw;
			accumulate (&ss.Sum[5].ui64, ss.Word[5].ui64.llw, ss.Word[5].ui64.hlw);

			if (ss.wordCount == 7) {		// 7 words
				ss.Word[6].ui64.llw = temp.llw ^ T2.llw;
				ss.Word[6].ui64.hlw = temp.hlw ^ T2.hlw;
				accumulate (&ss.Sum[6].ui64, ss.Word[6].ui64.llw, ss.Word[6].ui64.hlw);
			} else {						// 8 words
				ss.Word[6].ui64.llw = ss.Word[7].ui64.llw ^ T2.llw;
				ss.Word[6].ui64.hlw = ss.Word[7].ui64.hlw ^ T2.hlw;
				accumulate (&ss.Sum[6].ui64, ss.Word[6].ui64.llw, ss.Word[6].ui64.hlw);
				ss.Word[7].ui64.llw = temp.llw ^ T1.llw;
				ss.Word[7].ui64.hlw = temp.hlw ^ T1.hlw;
				accumulate (&ss.Sum[7].ui64, ss.Word[7].ui64.llw, ss.Word[7].ui64.hlw);
			}
		}

		if (--ss.roundsToGo == 0)	// reduce space left in current block
			ss.roundsToGo = ss.blockSizeFrags;

#ifdef VERBOSE
		++vround;
		showState64n (fragmem.llw, fragmem.hlw, T1.llw, T1.hlw,
			T2.llw, T2.hlw, carry1, carry2);
#endif
	}	// end of round

	ss.carries = (carry2 << 1) | (carry1 & 1);		// save the carry bits
}

#endif	//NO_LONG_LONG

//=============================================================================


//========================================================
// hash engine for 32-bit words, triple compression function
// note that the byte count is guaranteed to be a multiple of 8
//========================================================
void doHash32x3 (const BitSequence *dta, Uint32 byteCount) {
	// declare register variables in order of frequency of use
	register Uint32 fragment;			// holds assembled input bytes
	register const BitSequence *dptr;	// fast pointer to data
	register Uint32 temp, T1, T2, T3;	// work resisters
	register Uint32 bcount;				// loop control counter
	register Uint8 carry1, carry2, carry3;	// final state bits
#ifdef VERBOSE
	register Uint32 fragmem;			// memory of fragment
#endif

	if ((dptr = dta) == 0)	return;		// null pointer
	if (byteCount == 0)		return;		// no data given

	// unpack the carry bits from the state structure
	carry1 = ss.carries & 1;			// first carry bit
	carry2 = (ss.carries >> 1) & 1;		// second carry bit
	carry3 = (ss.carries >> 2) & 1;		// third carry bit

	for (bcount = byteCount; bcount > 0; bcount -= 4) {
		// first pack 4 bytes into a fragment
		fragment = ((((((dptr[3]) << 8) | dptr[2]) << 8) | dptr[1]) << 8) | dptr[0];
		dptr += 4;						// advance data pointer

		// update the checksum accumulators
		ss.Checksum1.ui32 += fragment;
		ss.Checksum2.ui32 += ~fragment;
#ifdef VERBOSE
		fragmem = fragment;				// save for verbose output
#endif

		// do the right side compression using T1 as a temporary variable
		T1 = ((fragment << 8) | (fragment >> 24)) ^ ss.Word[5].ui32;
		temp = ss.Word[2].ui32;		// fetch the middle word
		temp = ((temp << 8) | (temp >> 24)) ^ ss.Word[8].ui32;
		if (carry3 == 0) {			// no previous carry
			T3 = T1 + temp;			// add the two pieces together
			if (T3 < (T1 | temp))	// did overflow happen?
				carry3 = 1;			// yes - remember that
			//else carry3 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T3 = T1 + temp + 1;		// add the pieces plus carry
			if (T3 > (T1 | temp))	// did overflow happen?
				carry3 = 0;			// no - remember that
			//else carry3 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T3: %8x", T1);
		//fprintf (fp_log, " + %8x", temp);
		//fprintf (fp_log, " = %d,%8x", carry3, T3);
		//fprintf (fp_log, "\r\n");

		// do the left side compression using T1 as a temporary variable
		T1 = ((fragment >> 8) | (fragment << 24)) ^ ss.Word[0].ui32;
		temp = ss.Word[3].ui32;		// fetch the middle word
		temp = ((temp >> 8) | (temp << 24)) ^ ss.Word[6].ui32;
		if (carry2 == 0) {			// no previous carry
			T2 = T1 + temp;			// add the two pieces together
			if (T2 < (T1 | temp))	// did overflow happen?
				carry2 = 1;			// yes - remember that
			//else carry2 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T2 = T1 + temp + 1;		// add the pieces plus carry
			if (T2 > (T1 | temp))	// did overflow happen?
				carry2 = 0;			// no - remember that
			//else carry2 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T2: %8x", T1);
		//fprintf (fp_log, " + %8x", temp);
		//fprintf (fp_log, " = %d,%8x", carry2, T2);
		//fprintf (fp_log, "\r\n");

		// do the center compression using fragment as a temporary variable
		fragment ^= ss.Word[7].ui32;
		temp = ss.Word[4].ui32;			// fetch the middle word
		temp = ((temp << 8) | (temp >> 24)) ^ ss.Word[1].ui32;
		if (carry1 == 0) {				// no previous carry
			T1 = fragment + temp;		// add the two pieces together
			if (T1 < (fragment | temp))	// did overflow happen?
				carry1 = 1;				// yes - remember that
			//else carry1 = 0;			// redundant - it was already 0
		} else {						// previous carry flagged
			T1 = fragment + temp + 1;	// add the pieces plus carry
			if (T1 > (fragment | temp))	// did overflow happen?
				carry1 = 0;				// no - remember that
			//else carry1 = 1;			// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T1: %8x", fragment);
		//fprintf (fp_log, " + %8x", temp);
		//fprintf (fp_log, " = %d,%8x", carry1, T1);
		//fprintf (fp_log, "\r\n");

		// now rotate the compression outputs
		if ((carry1 ^ carry2) != 0) {	// one carry - rotate 7
			T1 = (T1 << 7) | (T1 >> 25);
			T2 = (T2 >> 7) | (T2 << 25);
			if (carry3 == 0)			// one carry - rotate 9
				T3 = (T3 << 9) | (T3 >> 23);
			else						// two carries - rotate 10
				T3 = (T3 << 10) | (T3 >> 22);
		} else if (carry1 == 0) {		// no carries - rotate 8
			T1 = (T1 << 8) | (T1 >> 24);
			T2 = (T2 >> 8) | (T2 << 24);
			if (carry3 == 0)			// no carries - rotate 8
				T3 = (T3 << 8) | (T3 >> 24);
			else						// one carry - rotate 9
				T3 = (T3 << 9) | (T3 >> 23);
		} else {						// two carries - rotate 6
			T1 = (T1 << 6) | (T1 >> 26);
			T2 = (T2 >> 6) | (T2 << 26);
			if (carry3 == 0)			// two carries - rotate 10
				T3 = (T3 << 10) | (T3 >> 22);
			else						// three carries - rotate 11
				T3 = (T3 << 11) | (T3 >> 21);
		}

		// finally do the expansion and summation
		temp = ss.Word[0].ui32;		// word to rotate and wrap around
		temp = (temp >> 7) | (temp << 25);	// do rotation
		ss.Sum[0].ui32 += 
			(ss.Word[0].ui32 = ss.Word[1].ui32 ^ T2);
		ss.Sum[1].ui32 += 
			(ss.Word[1].ui32 = ss.Word[2].ui32 ^ T1);
		ss.Sum[2].ui32 += 
			(ss.Word[2].ui32 = ss.Word[3].ui32 ^ T3);
		ss.Sum[3].ui32 += 
			(ss.Word[3].ui32 = ss.Word[4].ui32 ^ T2);
		ss.Sum[4].ui32 += 
			(ss.Word[4].ui32 = ss.Word[5].ui32 ^ T1);
		ss.Sum[5].ui32 += 
			(ss.Word[5].ui32 = ss.Word[6].ui32 ^ T3);
		ss.Sum[6].ui32 += 
			(ss.Word[6].ui32 = ss.Word[7].ui32 ^ T2);
		ss.Sum[7].ui32 += 
			(ss.Word[7].ui32 = ss.Word[8].ui32 ^ T1);
		if (ss.wordCount == 9)				// 9 words
			ss.Sum[8].ui32 += 
				(ss.Word[8].ui32 = temp ^ T3);
		else {								// 10 words
			ss.Sum[8].ui32 += 
				(ss.Word[8].ui32 = ss.Word[9].ui32 ^ T3);
			ss.Sum[9].ui32 += 
				(ss.Word[9].ui32 = temp ^ T2);
		}

		if (--ss.roundsToGo == 0)	// reduce space left in current block
			ss.roundsToGo = ss.blockSizeFrags;

#ifdef VERBOSE
		++vround;
		showState32t (fragmem, T1, T2, T3, carry1, carry2, carry3);
#endif
	}	// end of round

	ss.carries = (carry3 << 2) | (carry2 << 1) | (carry1 & 1);	// save the carry bits
}


//========================================================
// hash engine for 16-bit words, triple compression function
// note that the byte count is guaranteed to be a multiple of 8
//========================================================
void doHash16x3 (const BitSequence *dta, Uint32 byteCount) {
	// declare register variables in order of frequency of use
	register Uint16 fragment;			// holds assembled input bytes
	register const BitSequence *dptr;	// fast pointer to data
	register Uint16 temp, T1, T2, T3;	// work resisters
	register Uint32 bcount;				// loop control counter
	register Uint8 carry1, carry2, carry3;	// final state bits
#ifdef VERBOSE
	register Uint16 fragmem;			// memory of fragment
#endif

	if ((dptr = dta) == 0)	return;		// null pointer
	if (byteCount == 0)		return;		// no data given

	// unpack the carry bits from the state structure
	carry1 = ss.carries & 1;			// first carry bit
	carry2 = (ss.carries >> 1) & 1;		// second carry bit
	carry3 = (ss.carries >> 2) & 1;		// third carry bit

	for (bcount = byteCount; bcount > 0; bcount -= 2) {
		// first pack 2 bytes into a fragment
		fragment = (dptr[1] << 8) | dptr[0];
		dptr += 2;						// advance data pointer

		// update the checksum accumulators
		ss.Checksum1.ui16 += fragment;
		ss.Checksum2.ui16 += ~fragment;
#ifdef VERBOSE
		fragmem = fragment;				// save for verbose output
#endif

		// do the right side compression using T1 as a temporary variable
		T1 = ((fragment << 8) | (fragment >> 8)) ^ ss.Word[5].ui16;
		temp = ss.Word[2].ui16;		// fetch the middle word
		temp = ((temp << 8) | (temp >> 8)) ^ ss.Word[8].ui16;
		if (carry3 == 0) {			// no previous carry
			T3 = T1 + temp;			// add the two pieces together
			if (T3 < (T1 | temp))	// did overflow happen?
				carry3 = 1;			// yes - remember that
			//else carry3 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T3 = T1 + temp + 1;		// add the pieces plus carry
			if (T3 > (T1 | temp))	// did overflow happen?
				carry3 = 0;			// no - remember that
			//else carry3 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T3: %4x", T1);
		//fprintf (fp_log, " + %4x", temp);
		//fprintf (fp_log, " = %d,%4x", carry3, T3);
		//fprintf (fp_log, "\r\n");

		// do the left side compression using T1 as a temporary variable
		T1 = ((fragment >> 8) | (fragment << 8)) ^ ss.Word[0].ui16;
		temp = ss.Word[3].ui16;		// fetch the middle word
		temp = ((temp >> 8) | (temp << 8)) ^ ss.Word[6].ui16;
		if (carry2 == 0) {			// no previous carry
			T2 = T1 + temp;			// add the two pieces together
			if (T2 < (T1 | temp))	// did overflow happen?
				carry2 = 1;			// yes - remember that
			//else carry2 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T2 = T1 + temp + 1;		// add the pieces plus carry
			if (T2 > (T1 | temp))	// did overflow happen?
				carry2 = 0;			// no - remember that
			//else carry2 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T2: %4x", T1);
		//fprintf (fp_log, " + %4x", temp);
		//fprintf (fp_log, " = %d,%4x", carry2, T2);
		//fprintf (fp_log, "\r\n");

		// do the center compression using fragment as a temporary variable
		fragment ^= ss.Word[7].ui16;
		temp = ss.Word[4].ui16;			// fetch the middle word
		temp = ((temp << 8) | (temp >> 8)) ^ ss.Word[1].ui16;
		if (carry1 == 0) {				// no previous carry
			T1 = fragment + temp;		// add the two pieces together
			if (T1 < (fragment | temp))	// did overflow happen?
				carry1 = 1;				// yes - remember that
			//else carry1 = 0;			// redundant - it was already 0
		} else {						// previous carry flagged
			T1 = fragment + temp + 1;	// add the pieces plus carry
			if (T1 > (fragment | temp))	// did overflow happen?
				carry1 = 0;				// no - remember that
			//else carry1 = 1;			// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T1: %4x", fragment);
		//fprintf (fp_log, " + %4x", temp);
		//fprintf (fp_log, " = %d,%4x", carry1, T1);
		//fprintf (fp_log, "\r\n");

		// now rotate the compression outputs
		if ((carry1 ^ carry2) != 0) {	// one carry - rotate 7
			T1 = (T1 << 7) | (T1 >> 9);
			T2 = (T2 >> 7) | (T2 << 9);
			if (carry3 == 0)			// one carry - rotate 9
				T3 = (T3 << 9) | (T3 >> 7);
			else						// two carries - rotate 10
				T3 = (T3 << 10) | (T3 >> 6);
		} else if (carry1 == 0) {		// no carries - rotate 8
			T1 = (T1 << 8) | (T1 >> 8);
			T2 = (T2 >> 8) | (T2 << 8);
			if (carry3 == 0)			// no carries - rotate 8
				T3 = (T3 << 8) | (T3 >> 8);
			else						// one carry - rotate 9
				T3 = (T3 << 9) | (T3 >> 7);
		} else {						// two carries - rotate 6
			T1 = (T1 << 6) | (T1 >> 10);
			T2 = (T2 >> 6) | (T2 << 10);
			if (carry3 == 0)			// two carries - rotate 10
				T3 = (T3 << 10) | (T3 >> 6);
			else						// three carries - rotate 11
				T3 = (T3 << 11) | (T3 >> 5);
		}

		// finally do the expansion and summation
		temp = ss.Word[0].ui16;		// word to rotate and wrap around
		temp = (temp >> 7) | (temp << 9);	// do rotation
		ss.Sum[0].ui16 += 
			(ss.Word[0].ui16 = ss.Word[1].ui16 ^ T2);
		ss.Sum[1].ui16 += 
			(ss.Word[1].ui16 = ss.Word[2].ui16 ^ T1);
		ss.Sum[2].ui16 += 
			(ss.Word[2].ui16 = ss.Word[3].ui16 ^ T3);
		ss.Sum[3].ui16 += 
			(ss.Word[3].ui16 = ss.Word[4].ui16 ^ T2);
		ss.Sum[4].ui16 += 
			(ss.Word[4].ui16 = ss.Word[5].ui16 ^ T1);
		ss.Sum[5].ui16 += 
			(ss.Word[5].ui16 = ss.Word[6].ui16 ^ T3);
		ss.Sum[6].ui16 += 
			(ss.Word[6].ui16 = ss.Word[7].ui16 ^ T2);
		ss.Sum[7].ui16 += 
			(ss.Word[7].ui16 = ss.Word[8].ui16 ^ T1);
		if (ss.wordCount == 9)				// 9 words
			ss.Sum[8].ui16 += 
				(ss.Word[8].ui16 = temp ^ T3);
		else {								// 10 words
			ss.Sum[8].ui16 += 
				(ss.Word[8].ui16 = ss.Word[9].ui16 ^ T3);
			ss.Sum[9].ui16 += 
				(ss.Word[9].ui16 = temp ^ T2);
		}

		if (--ss.roundsToGo == 0)	// reduce space left in current block
			ss.roundsToGo = ss.blockSizeFrags;

#ifdef VERBOSE
		++vround;
		showState16t (fragmem, T1, T2, T3, carry1, carry2, carry3);
#endif
	}	// end of round

	ss.carries = (carry3 << 2) | (carry2 << 1) | (carry1 & 1);	// save the carry bits
}


//========================================================
// hash engine for 64-bit words, triple compression function
// note that the byte count is guaranteed to be a multiple of 8
//========================================================
#ifndef NO_LONG_LONG					// 64-bit values ok
void doHash64x3 (const BitSequence *dta, Uint32 byteCount) {
	// declare register variables in order of frequency of use
	register Uint64 fragment;			// holds assembled input bytes
	register const BitSequence *dptr;	// fast pointer to data
	register Uint64 temp, T1, T2, T3;	// work resisters
	register Uint32 bcount;				// loop control counter
	register Uint8 carry1, carry2, carry3;	// final state bits
#ifdef VERBOSE
	register Uint64 fragmem;			// memory of fragment
#endif

	if ((dptr = dta) == 0)	return;		// null pointer
	if (byteCount == 0)		return;		// no data given

	// unpack the carry bits from the state structure
	carry1 = ss.carries & 1;			// first carry bit
	carry2 = (ss.carries >> 1) & 1;		// second carry bit
	carry3 = (ss.carries >> 2) & 1;		// third carry bit

	for (bcount = byteCount; bcount > 0; bcount -= 8) {
		// first pack 8 bytes into a fragment
		fragment = ((((dptr[7] << 8) | dptr[6]) << 8) | dptr[5]) << 8;
		fragment = ((((fragment | dptr[4]) << 8) | dptr[3]) << 8) | dptr[2];
		fragment = (((fragment << 8) | dptr[1]) << 8) | dptr[0];
		dptr += 8;						// advance data pointer

		// update the checksum accumulators
		ss.Checksum1.ui64 += fragment;
		ss.Checksum2.ui64 += ~fragment;
#ifdef VERBOSE
		fragmem = fragment;				// save for verbose output
#endif

		// do the right side compression using T1 as a temporary variable
		T1 = ((fragment << 8) | (fragment >> 56)) ^ ss.Word[5].ui64;
		temp = ss.Word[2].ui64;		// fetch the middle word
		temp = ((temp << 8) | (temp >> 56)) ^ ss.Word[8].ui64;
		if (carry3 == 0) {			// no previous carry
			T3 = T1 + temp;			// add the two pieces together
			if (T3 < (T1 | temp))	// did overflow happen?
				carry3 = 1;			// yes - remember that
			//else carry3 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T3 = T1 + temp + 1;		// add the pieces plus carry
			if (T3 > (T1 | temp))	// did overflow happen?
				carry3 = 0;			// no - remember that
			//else carry3 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T3: "); showHex64 (T1);
		//fprintf (fp_log, " + "); showHex64 (temp);
		//fprintf (fp_log, " = %d,", carry3); showHex64 (T3);
		//fprintf (fp_log, "\r\n");

		// do the left side compression using T1 as a temporary variable
		T1 = ((fragment >> 8) | (fragment << 56)) ^ ss.Word[0].ui64;
		temp = ss.Word[3].ui64;		// fetch the middle word
		temp = ((temp >> 8) | (temp << 56)) ^ ss.Word[6].ui64;
		if (carry2 == 0) {			// no previous carry
			T2 = T1 + temp;			// add the two pieces together
			if (T2 < (T1 | temp))	// did overflow happen?
				carry2 = 1;			// yes - remember that
			//else carry2 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T2 = T1 + temp + 1;		// add the pieces plus carry
			if (T2 > (T1 | temp))	// did overflow happen?
				carry2 = 0;			// no - remember that
			//else carry2 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T2: "); showHex64 (T1);
		//fprintf (fp_log, " + "); showHex64 (temp);
		//fprintf (fp_log, " = %d,", carry2); showHex64 (T2);
		//fprintf (fp_log, "\r\n");

		// do the center compression using fragment as a temporary variable
		fragment ^= ss.Word[7].ui64;
		temp = ss.Word[4].ui64;			// fetch the middle word
		temp = ((temp << 8) | (temp >> 56)) ^ ss.Word[1].ui64;
		if (carry1 == 0) {				// no previous carry
			T1 = fragment + temp;		// add the two pieces together
			if (T1 < (fragment | temp))	// did overflow happen?
				carry1 = 1;				// yes - remember that
			//else carry1 = 0;			// redundant - it was already 0
		} else {						// previous carry flagged
			T1 = fragment + temp + 1;	// add the pieces plus carry
			if (T1 > (fragment | temp))	// did overflow happen?
				carry1 = 0;				// no - remember that
			//else carry1 = 1;			// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T1: "); showHex64 (fragment);
		//fprintf (fp_log, " + "); showHex64 (temp);
		//fprintf (fp_log, " = %d,", carry1); showHex64 (T1);
		//fprintf (fp_log, "\r\n");

		// now rotate the compression outputs
		if ((carry1 ^ carry2) != 0) {	// one carry - rotate 7
			T1 = (T1 << 7) | (T1 >> 57);
			T2 = (T2 >> 7) | (T2 << 57);
			if (carry3 == 0)			// one carry - rotate 9
				T3 = (T3 << 9) | (T3 >> 55);
			else						// two carries - rotate 10
				T3 = (T3 << 10) | (T3 >> 54);
		} else if (carry1 == 0) {		// no carries - rotate 8
			T1 = (T1 << 8) | (T1 >> 56);
			T2 = (T2 >> 8) | (T2 << 56);
			if (carry3 == 0)			// no carries - rotate 8
				T3 = (T3 << 8) | (T3 >> 56);
			else						// one carry - rotate 9
				T3 = (T3 << 9) | (T3 >> 55);
		} else {						// two carries - rotate 6
			T1 = (T1 << 6) | (T1 >> 58);
			T2 = (T2 >> 6) | (T2 << 58);
			if (carry3 == 0)			// two carries - rotate 10
				T3 = (T3 << 10) | (T3 >> 54);
			else						// three carries - rotate 11
				T3 = (T3 << 11) | (T3 >> 53);
		}

		// finally do the expansion and summation
		temp = ss.Word[0].ui64;		// word to rotate and wrap around
		temp = (temp >> 7) | (temp << 57);	// do rotation
		ss.Sum[0].ui64 += 
			(ss.Word[0].ui64 = ss.Word[1].ui64 ^ T2);
		ss.Sum[1].ui64 += 
			(ss.Word[1].ui64 = ss.Word[2].ui64 ^ T1);
		ss.Sum[2].ui64 += 
			(ss.Word[2].ui64 = ss.Word[3].ui64 ^ T3);
		ss.Sum[3].ui64 += 
			(ss.Word[3].ui64 = ss.Word[4].ui64 ^ T2);
		ss.Sum[4].ui64 += 
			(ss.Word[4].ui64 = ss.Word[5].ui64 ^ T1);
		ss.Sum[5].ui64 += 
			(ss.Word[5].ui64 = ss.Word[6].ui64 ^ T3);
		ss.Sum[6].ui64 += 
			(ss.Word[6].ui64 = ss.Word[7].ui64 ^ T2);
		ss.Sum[7].ui64 += 
			(ss.Word[7].ui64 = ss.Word[8].ui64 ^ T1);
		if (ss.wordCount == 9)				// 9 words
			ss.Sum[8].ui64 += 
				(ss.Word[8].ui64 = temp ^ T3);
		else {								// 10 words
			ss.Sum[8].ui64 += 
				(ss.Word[8].ui64 = ss.Word[9].ui64 ^ T3);
			ss.Sum[9].ui64 += 
				(ss.Word[9].ui64 = temp ^ T2);
		}

		if (--ss.roundsToGo == 0)	// reduce space left in current block
			ss.roundsToGo = ss.blockSizeFrags;

#ifdef VERBOSE
		++vround;
		showState64t (fragmem, T1, T2, T3, carry1, carry2, carry3);
#endif
	}	// end of round

	ss.carries = (carry3 << 2) | (carry2 << 1) | (carry1 & 1);	// save the carry bits
}

#else	//NO_LONG_LONG

void doHash64x3 (const BitSequence *dta, Uint32 byteCount) {
	// declare register variables in order of frequency of use
	register Uint64 fragment;			// holds assembled input bytes
	register const BitSequence *dptr;	// fast pointer to data
	register Uint64 temp, T1, T2, T3, rot;	// work resisters
	register Uint32 bcount;				// loop control counter
	register Uint8 carry1, carry2, carry3;	// final state bits
#ifdef VERBOSE
	register Uint64 fragmem;			// memory of fragment
#endif

	if ((dptr = dta) == 0)	return;		// null pointer
	if (byteCount == 0)		return;		// no data given

	// unpack the carry bits from the state structure
	carry1 = ss.carries & 1;			// first carry bit
	carry2 = (ss.carries >> 1) & 1;		// second carry bit
	carry3 = (ss.carries >> 2) & 1;		// third carry bit

	for (bcount = byteCount; bcount > 0; bcount -= 8) {
		// first pack 8 bytes into a fragment
		fragment.hlw = (((((dptr[7] << 8) | dptr[6]) << 8) | dptr[5]) << 8) | dptr[4];
		fragment.llw = (((((dptr[3] << 8) | dptr[2]) << 8) | dptr[1]) << 8) | dptr[0];
		dptr += 8;						// advance data pointer

		// update the checksum accumulators
		temp.llw = ss.Checksum1.ui64.llw | fragment.llw;
		if ((ss.Checksum1.ui64.llw += fragment.llw) < temp.llw)
			ss.Checksum1.ui64.hlw += 1;		// carry out of low half
		ss.Checksum1.ui64.hlw += fragment.hlw;
		temp.llw = ss.Checksum2.ui64.llw | ~fragment.llw;
		if ((ss.Checksum2.ui64.llw += ~fragment.llw) < temp.llw)
			ss.Checksum2.ui64.hlw += 1;		// carry out of low half
		ss.Checksum2.ui64.hlw += ~fragment.hlw;
#ifdef VERBOSE
		fragmem.llw = fragment.llw;			// save for verbose output
		fragmem.hlw = fragment.hlw;
#endif

		// do the right side compression using T1 as a temporary variable
		rot.llw = (fragment.llw << 8) | (fragment.hlw >> 24);
		rot.hlw = (fragment.hlw << 8) | (fragment.llw >> 24);
		T1.llw = rot.llw ^ ss.Word[5].ui64.llw;
		T1.hlw = rot.hlw ^ ss.Word[5].ui64.hlw;
		rot.llw = (ss.Word[2].ui64.llw << 8) | (ss.Word[2].ui64.hlw >> 24);
		rot.hlw = (ss.Word[2].ui64.hlw << 8) | (ss.Word[2].ui64.llw >> 24);
		temp.llw = rot.llw ^ ss.Word[8].ui64.llw;	// fetch the middle even word
		temp.hlw = rot.hlw ^ ss.Word[8].ui64.hlw;
		if (carry3 == 0) {			// no previous carry
			T3.llw = T1.llw + temp.llw;			// add the two pieces together
			if (T3.llw < (T1.llw | temp.llw))	// did overflow happen?
				carry3 = 1;			// yes - remember that
			//else carry3 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T3.llw = T1.llw + temp.llw + 1;		// add the pieces plus carry
			if (T3.llw > (T1.llw | temp.llw))	// did overflow happen?
				carry3 = 0;			// no - remember that
			//else carry3 = 1;		// redundant - it was already 1
		}	// carry3 now holds the carry out of the low half addition
		if (carry3 == 0) {			// no previous carry
			T3.hlw = T1.hlw + temp.hlw;			// add the two pieces together
			if (T3.hlw < (T1.hlw | temp.hlw))	// did overflow happen?
				carry3 = 1;			// yes - remember that
			//else carry3 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T3.hlw = T1.hlw + temp.hlw + 1;		// add the pieces plus carry
			if (T3.hlw > (T1.hlw | temp.hlw))	// did overflow happen?
				carry3 = 0;			// no - remember that
			//else carry3 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T3: "); showHex64 (T1);
		//fprintf (fp_log, " + "); showHex64 (temp);
		//fprintf (fp_log, " = %d,", carry3); showHex64 (T3);
		//fprintf (fp_log, "\r\n");

		// do the left side compression using T1 as a temporary variable
		rot.llw = (fragment.llw >> 8) | (fragment.hlw << 24);
		rot.hlw = (fragment.hlw >> 8) | (fragment.llw << 24);
		T1.llw = rot.llw ^ ss.Word[0].ui64.llw;
		T1.hlw = rot.hlw ^ ss.Word[0].ui64.hlw;
		rot.llw = (ss.Word[3].ui64.llw >> 8) | (ss.Word[3].ui64.hlw << 24);
		rot.hlw = (ss.Word[3].ui64.hlw >> 8) | (ss.Word[3].ui64.llw << 24);
		temp.llw = rot.llw ^ ss.Word[6].ui64.llw;	// fetch the middle even word
		temp.hlw = rot.hlw ^ ss.Word[6].ui64.hlw;
		if (carry2 == 0) {			// no previous carry
			T2.llw = T1.llw + temp.llw;			// add the two pieces together
			if (T2.llw < (T1.llw | temp.llw))	// did overflow happen?
				carry2 = 1;			// yes - remember that
			//else carry2 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T2.llw = T1.llw + temp.llw + 1;		// add the pieces plus carry
			if (T2.llw > (T1.llw | temp.llw))	// did overflow happen?
				carry2 = 0;			// no - remember that
			//else carry2 = 1;		// redundant - it was already 1
		}	// carry2 now holds the carry out of the low half addition
		if (carry2 == 0) {			// no previous carry
			T2.hlw = T1.hlw + temp.hlw;			// add the two pieces together
			if (T2.hlw < (T1.hlw | temp.hlw))	// did overflow happen?
				carry2 = 1;			// yes - remember that
			//else carry2 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T2.hlw = T1.hlw + temp.hlw + 1;		// add the pieces plus carry
			if (T2.hlw > (T1.hlw | temp.hlw))	// did overflow happen?
				carry2 = 0;			// no - remember that
			//else carry2 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T2: "); showHex64 (T1);
		//fprintf (fp_log, " + "); showHex64 (temp);
		//fprintf (fp_log, " = %d,", carry2); showHex64 (T2);
		//fprintf (fp_log, "\r\n");

		// do the center compression using fragment as a temporary variable
		fragment.llw ^= ss.Word[7].ui64.llw;
		fragment.hlw ^= ss.Word[7].ui64.hlw;
		rot.llw = (ss.Word[4].ui64.llw << 8) | (ss.Word[4].ui64.hlw >> 24);
		rot.hlw = (ss.Word[4].ui64.hlw << 8) | (ss.Word[4].ui64.llw >> 24);
		temp.llw = rot.llw ^ ss.Word[1].ui64.llw;	// fetch the middle odd word
		temp.hlw = rot.hlw ^ ss.Word[1].ui64.hlw;
		if (carry1 == 0) {			// no previous carry
			T1.llw = fragment.llw + temp.llw;	// add the two pieces together
			if (T1.llw < (fragment.llw | temp.llw))	// did overflow happen?
				carry1 = 1;			// yes - remember that
			//else carry1 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T1.llw = fragment.llw + temp.llw + 1;	// add the pieces plus carry
			if (T1.llw > (fragment.llw | temp.llw))	// did overflow happen?
				carry1 = 0;			// no - remember that
			//else carry1 = 1;		// redundant - it was already 1
		}	// carry1 now holds the carry out of the low half addition
		if (carry1 == 0) {			// no previous carry
			T1.hlw = fragment.hlw + temp.hlw;	// add the two pieces together
			if (T1.hlw < (fragment.hlw | temp.hlw))	// did overflow happen?
				carry1 = 1;			// yes - remember that
			//else carry1 = 0;		// redundant - it was already 0
		} else {					// previous carry flagged
			T1.hlw = fragment.hlw + temp.hlw + 1;	// add the pieces plus carry
			if (T1.hlw > (fragment.hlw | temp.hlw))	// did overflow happen?
				carry1 = 0;			// no - remember that
			//else carry1 = 1;		// redundant - it was already 1
		}
		//fprintf (fp_log, "pre T1: "); showHex64 (fragment);
		//fprintf (fp_log, " + "); showHex64 (temp);
		//fprintf (fp_log, " = %d,", carry1); showHex64 (T1);
		//fprintf (fp_log, "\r\n");

		// now rotate the compression outputs
		if ((carry1 ^ carry2) != 0) {	// one carry - rotate 7
			rot.llw = (T1.llw << 7) | (T1.hlw >> 25);
			T1.hlw = (T1.hlw << 7) | (T1.llw >> 25);
			T1.llw = rot.llw;
			rot.llw = (T2.llw >> 7) | (T2.hlw << 25);
			T2.hlw = (T2.hlw >> 7) | (T2.llw << 25);
			T2.llw = rot.llw;
			if (carry3 == 0) {			// one carry - rotate 9
				rot.llw = (T3.llw << 9) | (T3.hlw >> 23);
				T3.hlw = (T3.hlw << 9) | (T3.llw >> 23);
				T3.llw = rot.llw;
			} else {					// two carries - rotate 10
				rot.llw = (T3.llw << 10) | (T3.hlw >> 22);
				T3.hlw = (T3.hlw << 10) | (T3.llw >> 22);
				T3.llw = rot.llw;
			}
		} else if (carry1 == 0) {		// no carries - rotate 8
			rot.llw = (T1.llw << 8) | (T1.hlw >> 24);
			T1.hlw = (T1.hlw << 8) | (T1.llw >> 24);
			T1.llw = rot.llw;
			rot.llw = (T2.llw >> 8) | (T2.hlw << 24);
			T2.hlw = (T2.hlw >> 8) | (T2.llw << 24);
			T2.llw = rot.llw;
			if (carry3 == 0) {			// no carries - rotate 8
				rot.llw = (T3.llw << 8) | (T3.hlw >> 24);
				T3.hlw = (T3.hlw << 8) | (T3.llw >> 24);
				T3.llw = rot.llw;
			} else {					// one carry - rotate 9
				rot.llw = (T3.llw << 9) | (T3.hlw >> 23);
				T3.hlw = (T3.hlw << 9) | (T3.llw >> 23);
				T3.llw = rot.llw;
			}
		} else {						// two carries - rotate 6
			rot.llw = (T1.llw << 6) | (T1.hlw >> 26);
			T1.hlw = (T1.hlw << 6) | (T1.llw >> 26);
			T1.llw = rot.llw;
			rot.llw = (T2.llw >> 6) | (T2.hlw << 26);
			T2.hlw = (T2.hlw >> 6) | (T2.llw << 26);
			T2.llw = rot.llw;
			if (carry3 == 0) {			// two carries - rotate 10
				rot.llw = (T3.llw << 10) | (T3.hlw >> 22);
				T3.hlw = (T3.hlw << 10) | (T3.llw >> 22);
				T3.llw = rot.llw;
			} else {					// three carries - rotate 11
				rot.llw = (T3.llw << 11) | (T3.hlw >> 21);
				T3.hlw = (T3.hlw << 11) | (T3.llw >> 21);
				T3.llw = rot.llw;
			}
		}

		// finally do the expansion and summation
		temp.llw = (ss.Word[0].ui64.llw >> 7) | (ss.Word[0].ui64.hlw << 25);
		temp.hlw = (ss.Word[0].ui64.hlw >> 7) | (ss.Word[0].ui64.llw << 25);

		ss.Word[0].ui64.llw = ss.Word[1].ui64.llw ^ T2.llw;
		ss.Word[0].ui64.hlw = ss.Word[1].ui64.hlw ^ T2.hlw;
		accumulate (&ss.Sum[0].ui64, ss.Word[0].ui64.llw, ss.Word[0].ui64.hlw);
		ss.Word[1].ui64.llw = ss.Word[2].ui64.llw ^ T1.llw;
		ss.Word[1].ui64.hlw = ss.Word[2].ui64.hlw ^ T1.hlw;
		accumulate (&ss.Sum[1].ui64, ss.Word[1].ui64.llw, ss.Word[1].ui64.hlw);
		ss.Word[2].ui64.llw = ss.Word[3].ui64.llw ^ T3.llw;
		ss.Word[2].ui64.hlw = ss.Word[3].ui64.hlw ^ T3.hlw;
		accumulate (&ss.Sum[2].ui64, ss.Word[2].ui64.llw, ss.Word[2].ui64.hlw);

		ss.Word[3].ui64.llw = ss.Word[4].ui64.llw ^ T2.llw;
		ss.Word[3].ui64.hlw = ss.Word[4].ui64.hlw ^ T2.hlw;
		accumulate (&ss.Sum[3].ui64, ss.Word[3].ui64.llw, ss.Word[3].ui64.hlw);
		ss.Word[4].ui64.llw = ss.Word[5].ui64.llw ^ T1.llw;
		ss.Word[4].ui64.hlw = ss.Word[5].ui64.hlw ^ T1.hlw;
		accumulate (&ss.Sum[4].ui64, ss.Word[4].ui64.llw, ss.Word[4].ui64.hlw);
		ss.Word[5].ui64.llw = ss.Word[6].ui64.llw ^ T3.llw;
		ss.Word[5].ui64.hlw = ss.Word[6].ui64.hlw ^ T3.hlw;
		accumulate (&ss.Sum[5].ui64, ss.Word[5].ui64.llw, ss.Word[5].ui64.hlw);

		ss.Word[6].ui64.llw = ss.Word[7].ui64.llw ^ T2.llw;
		ss.Word[6].ui64.hlw = ss.Word[7].ui64.hlw ^ T2.hlw;
		accumulate (&ss.Sum[6].ui64, ss.Word[6].ui64.llw, ss.Word[6].ui64.hlw);
		ss.Word[7].ui64.llw = ss.Word[8].ui64.llw ^ T1.llw;
		ss.Word[7].ui64.hlw = ss.Word[8].ui64.hlw ^ T1.hlw;
		accumulate (&ss.Sum[7].ui64, ss.Word[7].ui64.llw, ss.Word[7].ui64.hlw);
		if (ss.wordCount == 9) {				// 9 words
			ss.Word[8].ui64.llw = temp.llw ^ T1.llw;
			ss.Word[8].ui64.hlw = temp.hlw ^ T1.hlw;
			accumulate (&ss.Sum[8].ui64, ss.Word[8].ui64.llw, ss.Word[8].ui64.hlw);
		} else {								// 10 words
			ss.Word[8].ui64.llw = ss.Word[9].ui64.llw ^ T1.llw;
			ss.Word[8].ui64.hlw = ss.Word[9].ui64.hlw ^ T1.hlw;
			accumulate (&ss.Sum[8].ui64, ss.Word[8].ui64.llw, ss.Word[8].ui64.hlw);
			ss.Word[9].ui64.llw = temp.llw ^ T2.llw;
			ss.Word[9].ui64.hlw = temp.hlw ^ T2.hlw;
			accumulate (&ss.Sum[9].ui64, ss.Word[9].ui64.llw, ss.Word[9].ui64.hlw);
		}

		if (--ss.roundsToGo == 0)	// reduce space left in current block
			ss.roundsToGo = ss.blockSizeFrags;

#ifdef VERBOSE
		++vround;
		showState64tn (fragmem.llw, fragmem.hlw, T1.llw, T1.hlw,
			T2.llw, T2.hlw, T3.llw, T3.hlw, carry1, carry2, carry3);
#endif
	}	// end of round

	ss.carries = (carry3 << 2) | (carry2 << 1) | (carry1 & 1);	// save the carry bits
}

#endif	//NO_LONG_LONG

//=============================================================================


//========================================================
// generic hash engine for all cases < 9 words - runs on all platforms
// First-time readers are advised to skip this routine and look
// at one of the above special-purpose routines instead.
// Note that the bytecount is guaranteed to be a multiple of the fragment size
//========================================================
void doHashGen (const BitSequence *dta, Uint32 byteCount) {
	register int i, j, temp, temp1, temp2, carry, carry1, carry2;
	register Uint32 bcount;
	register const BitSequence *dptr;
	Uint8 fragment [8], T1result [8], T2result [8], word0rot[8];

	if ((dptr = dta) == 0)	return;		// null pointer
	if (byteCount == 0)		return;		// no data given

	// unpack the carry bits from the state structure
	carry1 = ss.carries & 1;			// first carry bit
	carry2 = (ss.carries >> 1) & 1;		// second carry bit

	for (bcount = byteCount; bcount > 0; bcount -= ss.fragSizeBytes) {
		carry = 0;
		for (i=0; i<ss.fragSizeBytes; ++i) {		// build a fragment
			temp = fragment [i] = *dptr++;			// get next byte
			temp += carry + (int)ss.Checksum1.b[i];	// update checksum1
			carry = temp >> 8;						// ripple carry
			ss.Checksum1.b[i] = (Uint8)temp;
		}

		// update checksum2
		carry = 0;
		for (i=0; i<ss.fragSizeBytes; ++i) {
			temp = ((int)~fragment [i]) & 0xFF;
			temp += carry + (int)ss.Checksum2.b[i];
			carry = temp >> 8;			// ripple carry
			ss.Checksum2.b[i] = (Uint8)temp;
		}

		// perform the compression function a byte slice at a time
		for (i=0; i<ss.fragSizeBytes; ++i) {
			// calculate even side
			if ((j = i + 1) >= ss.fragSizeBytes)	// rotate right 8 bits by indexing
				j = 0;				// wrap around
			temp = (fragment[j] ^ ss.Word[0].b[i]) & 0xFF;
			temp2 = (ss.Word[2].b[j] ^ ss.Word[4].b[i]) & 0xFF;
			temp2 += temp + (carry2 & 1);
			carry2 = temp2 >> 8;			// ripple carry
			T2result [i] = (Uint8)temp2;		// T2 value

			// calculate odd side
			if ((j = i - 1) < 0)			// rotate left 8 bits by indexing
				j = ss.fragSizeBytes - 1;	// top byte index
			temp = (fragment[i] ^ ss.Word[5].b[i]) & 0xFF;
			temp1 = (ss.Word[3].b[j] ^ ss.Word[1].b[i]) & 0xFF;
			temp1 += temp + (carry1 & 1);
			carry1 = temp1 >> 8;			// ripple carry
			T1result [i] = (Uint8)temp1;		// T1 value
		}

		// now rotate T1 left 8 bits
		temp = T1result [ss.fragSizeBytes-1];		// grab the top byte
		for (i=ss.fragSizeBytes-1; i>0; --i)
			T1result [i] = T1result [i-1];		// shuffle up one byte
		T1result [0] = (Uint8)temp;				// put the top byte back

		// and rotate T2 right 8 bits
		temp = T2result [0];
		for (i=1; i<ss.fragSizeBytes; ++i)
			T2result [i-1] = T2result [i];
		T2result [ss.fragSizeBytes-1] = (Uint8)temp;

		if (((carry1 ^ carry2) & 1) != 0) {		// one carry - shift back a bit
			// rotate T1 right one bit
			carry = T1result [0] & 1;
			for (i=0; i<7; ++i)				
				T1result [i] = (Uint8)((T1result [i] >> 1) |
					((T1result [i+1] & 1) << 7));
			T1result [7] = (Uint8)(T1result [7] >> 1);
			i = ss.fragSizeBytes - 1;			// highest byte index
			T1result [i] = (Uint8)((T1result [i] & 0x7F) | (carry << 7));

			// rotate T2 left one bit
			carry = 0;					// no carry in for multi-byte shift
			for (i=0; i<ss.fragSizeBytes; ++i) {
				temp = T2result [i] & 0xFF;
				temp = (temp << 1) | (carry & 1);	// shift subfunction
				carry = temp >> 8;			// save the carry out
				T2result [i] = (Uint8)(temp & 0xFF);	// save the shift result
			}
			T2result [0] |= (Uint8)(carry & 1);		// put back the last carry bit
		}
		else if ((carry1 & 1) != 0) {		// two carries - shift back two bits
			// rotate T1 right two bits
			carry = T1result [0] & 3;
			for (i=0; i<7; ++i)				
				T1result [i] = (Uint8)((T1result [i] >> 2) |
					((T1result [i+1] & 3) << 6));
			T1result [7] = (Uint8)(T1result [7] >> 2);
			i = ss.fragSizeBytes - 1;			// highest byte index
			T1result [i] = (Uint8)((T1result [i] & 0x3F) | (carry << 6));

			// rotate T2 left two bits
			carry = 0;					// no carry in for multi-byte shift
			for (i=0; i<ss.fragSizeBytes; ++i) {
				temp = T2result [i] & 0xFF;
				temp = (temp << 2) | (carry & 3);	// shift subfunction
				carry = temp >> 8;			// save the carry out
				T2result [i] = (Uint8)(temp & 0xFF);	// save the shift result
			}
			T2result [0] |= (Uint8)(carry & 3);		// put back the last carry bits
		}

		// inflate the compression results
		i = 0;
		for (j=ss.fragSizeBytes; j<8; ++j) {	// fill all eight bytes
			T1result [j] = T1result [i];
			T2result [j] = T2result [i];
			++i;
		}

		// rotate word0 right seven bits and save in word0rot
		carry = ss.Word [0].b[0] & 0x7F;
		for (i=0; i<7; ++i)
			word0rot[i] = (Uint8)((ss.Word [0].b[i] >> 7) |
				((ss.Word [0].b[i+1] & 0x7F) << 1));
		word0rot[7] = (Uint8)(ss.Word [0].b[7] >> 7);
		i = ss.wordSizeBytes - 1;				// highest byte index
		word0rot[i] = (Uint8)((word0rot[i] & 1) | (carry << 1));

		// rotate all the words down one place
		for (i=0; i<ss.wordSizeBytes; ++i)
			for (j=1; j<ss.wordCount; ++j)
				ss.Word [j-1].b[i] = ss.Word [j].b[i];
		j = ss.wordCount - 1;				// highest numbered word
		for (i=0; i<ss.wordSizeBytes; ++i)
			ss.Word [j].b[i] = word0rot[i];		// replace word0 at the top

		// finally do the expansion and summation functions
		for (j=0; j<ss.wordCount; ++j) {
			carry = 0;				// no carry in for summation
			for (i=0; i<ss.wordSizeBytes; ++i) {
				temp = ss.Word [j].b[i];
				if ((j & 1) != 0)
					temp ^= T1result [i];		// odd word expansion
				else
					temp ^= T2result [i];		// even word expansion
				ss.Word [j].b[i] = (Uint8)temp;
				temp += carry + (int)ss.Sum[j].b[i];
				carry = temp >> 8;
				ss.Sum[j].b[i] = (Uint8)temp;
			}
		}

		if (--ss.roundsToGo == 0)	// reduce space left in current block
			ss.roundsToGo = ss.blockSizeFrags;

#ifdef VERBOSE
		++vround;
		//showStateGen (fragmem, T1, T2, (carry2 << 1) | carry1);
		if (fp_log == NULL)
			fp_log = fopen("hashlog.txt", "a");
		fprintf(fp_log, "Round %d:\r\n", vround);
		i = ss.fragSizeBytes - 1;
		fprintf(fp_log, "fragment[%d-0]=", i); showBytes(i, &fragment[0]);
		fprintf(fp_log, " checksum1[%d-0]=", i); showBytes(i, &ss.Checksum1.b[0]);
		fprintf(fp_log, " checksum2[%d-0]", i); showBytes(i, &ss.Checksum2.b[0]);
		i = ss.wordSizeBytes - 1;
		fprintf(fp_log, "\r\nT1[%d-0]=", i); showBytes(i, &T1result[0]);
		fprintf(fp_log, " T2[%d-0]=", i); showBytes(i, &T2result[0]);
		fprintf(fp_log, " carry[1-2]=%d %d\r\n", carry1, carry2);
		temp = ss.wordCount;		// number of words in hash
		for (j=0; j<temp; ++j) {
			fprintf(fp_log, " Word[%d][%d-0]=", j, i);
			showBytes (i, &ss.Word[j].b[0]);
		}
		fprintf(fp_log, "\r\n");
		for (j=0; j<temp; ++j) {
			fprintf(fp_log, " Sum[%d][%d-0]=", j, i);
			showBytes (i, &ss.Sum[j].b[0]);
		}
		fprintf(fp_log, "\r\n");
#endif
	}	// end of round loop

	ss.carries = (carry2 << 1) | (carry1 & 1);		// save the carry bits
}

//=============================================================================


//========================================================
// process a chunk of data - an internal call
// the chunk is guaranteed to be an exact number of fragments
//========================================================
void doUpdate (const BitSequence *dta, Uint32 byteCount) {
	register Uint32 i, j;
	// first deal with filling the first block buffer ready for end fill
	if (ss.firstByteCount < FBSIZE) {
		i = ss.firstByteCount;		// index of first empty byte
		j = FBSIZE - i;					// potential copy length
		if (byteCount < j)				// not enough new data to fill block
			j = byteCount;				// actual copy length
		memcpy (&ss.firstBlock[i], dta, j);	// stash the data
		ss.firstByteCount += (Uint8)j;		// update amount stored
	}
	// now dispatch to the appropriate processing routine
	switch (ss.member) {
	case V384:
	case V448:
	case V512:	doHash64x2 (dta, byteCount);
			break;
	case V576:
	case V640:	doHash64x3 (dta, byteCount);
			break;
	case V192:
	case V224:
	case V256:	doHash32x2 (dta, byteCount);
			break;
	case V288:
	case V320:	doHash32x3 (dta, byteCount);
			break;
	case V96:
	case V112:
	case V128:	doHash16x2 (dta, byteCount);
			break;
	case V144:
	case V160:	doHash16x3 (dta, byteCount);
			break;
	default:	doHashGen (dta, byteCount);		// use generic hash routine
	}
}

//========================================================
// update the hash with the data given - called from user code
//========================================================
HashReturn Blender_Update(Blender_hashState *state, const BitSequence *dta,DataLength databitlen) {
	register int i;
	register DataLength bcount;
	register const BitSequence *dptr = dta;
	register Uint32 j, k;
	memcpy (&ss, state, sizeof(ss));			// get state in local workspace

	// deal with the length update first
	bcount = ss.sourceDataLength;	// previous length
	ss.sourceDataLength = bcount + databitlen;	// new length
	if (ss.sourceDataLength < (bcount | databitlen))	// overflow
		if (++ss.sourceDataLength2[0] == 0)		// increment higher order count
			if (++ss.sourceDataLength2[1] == 0)	// and the next higher order
				++ss.sourceDataLength2[3];		// and the next one, etc.

	// now deal with moving the data around
	bcount = databitlen >> 3;			// number of complete bytes of data
										// = floor (databitlen / 8)
	if (ss.residueLength != 0) {		// previous partial fragment
		// complete the fragment and process it
		i = ss.residueLength;			// length already used
		k = ss.fragSizeBytes - i;		// length needed to complete fragment
		if ((DataLength)k > bcount)		// if the new addition is tiny
			k = (Uint32)bcount;			// reduce the length
		memcpy (&ss.messageResidue[i], dptr, k);
		dptr += k;						// advance source pointer
		bcount -= k;					// reduce source length
		if ((ss.residueLength += (Uint8)k) >= ss.fragSizeBytes) {
			doUpdate (&ss.messageResidue[0], k+i);	// process it
			ss.residueLength = 0;		// remember nothing remains
		}
	}
	k = ((Uint32)ss.fragSizeBytes) << 24;	// big chunk size in bytes
	while (bcount >= (DataLength)k) {
		doUpdate (dptr, k);				// process a big chunk
		dptr += k;						// advance source pointer
		bcount -= k;					// reduce source length
	}
	j = (Uint32)bcount / ss.fragSizeBytes;		// fragments left
	k = j * ss.fragSizeBytes;			// most of the remainder
	if (k > 0) {
		doUpdate (dptr, k);				// process the small chunk
		dptr += k;						// advance source pointer
		bcount -= k;					// reduce source length
	}
	if ((i = (int)bcount & 7) > 0) {	// save the end for later
		memcpy (&ss.messageResidue[0], dptr, i);
		ss.residueLength = i;			// remember how much saved
		dptr += i;						// advance source pointer
	}

	// now deal with the possible partial byte at the end
	if ((j = (Uint32)databitlen & 7) != 0) {
		k = *dptr;
		if (ss.bitEndianity > 0) {			// big endian
			if ((k & bigendbit[j]) == 0)	// test the last bit
				k |= bigendfill[j];			// fill with ones
			else
				k &= ~bigendfill[j];		// fill with zeros
		} else {							// little endian
			if ((k & littleendbit[j]) == 0)
				k |= littleendfill[j];		// fill with ones
			else
				k &= ~littleendfill[j];		// fill with zeros
		}
		ss.messageResidue[i] = (Uint8)k;	// save the result value
		ss.residueLength += 1;				// update residue byte count
	}
	memcpy (state, &ss, sizeof(ss));		// save local workspace
	return SUCCESS;
}

//=============================================================================

//========================================================
// routines to output the final message digest
//========================================================
void doFinal32 (BitSequence *hashval) {
	register BitSequence *dptr = hashval;
	register Uint32 val;
	register int i, j, k;
	k = ss.wordSizeBytes;				// number of bytes per word
	dptr += (ss.wordCount * k);			// move pointer to the end
	for (i=ss.wordCount-1; i>=0; --i) {
		val = ss.Sum[i].ui32;			// get the result word
		for (j=k; j>0; --j) {
			*--dptr = (Uint8)val;		// output byte
			val >>= 8;					// advance to next byte
		}
	}
}
void doFinal16 (BitSequence *hashval) {
	register BitSequence *dptr = hashval;
	register Uint16 val;
	register int i, j, k;
	k = ss.wordSizeBytes;				// number of bytes per word
	dptr += (ss.wordCount * k);			// move pointer to the end
	for (i=ss.wordCount-1; i>=0; --i) {
		val = ss.Sum[i].ui16;			// get the result word
		for (j=k; j>0; --j) {
			*--dptr = (Uint8)val;		// output byte
			val >>= 8;					// advance to next byte
		}
	}
}
#ifndef NO_LONG_LONG
void doFinal64 (BitSequence *hashval) {
	register BitSequence *dptr = hashval;
	register Uint64 val;
	register int i, j, k;
	k = ss.wordSizeBytes;				// number of bytes per word
	dptr += (ss.wordCount * k);			// move pointer to the end
	for (i=ss.wordCount-1; i>=0; --i) {
		val = ss.Sum[i].ui64;			// get the result word
		for (j=k; j>0; --j) {
			*--dptr = (Uint8)val;		// output byte
			val >>= 8;					// advance to next byte
		}
	}
}
#else	//NO_LONG_LONG
void doFinal64 (BitSequence *hashval) {
	register BitSequence *dptr = hashval;
	register Uint32 val;
	register int i, j, k;
	k = ss.wordSizeBytes;				// number of bytes per word
	dptr += (ss.wordCount * k);			// move pointer to the end
	for (i=ss.wordCount-1; i>=0; --i) {
		val = ss.Sum[i].ui64.llw;		// get the result word
		for (j=4; j>0; --j) {
			*--dptr = (Uint8)val;		// output byte
			val >>= 8;					// advance to next byte
		}
		val = ss.Sum[i].ui64.hlw;		// get the result word
		for (j=4; j>0; --j) {
			*--dptr = (Uint8)val;		// output byte
			val >>= 8;					// advance to next byte
		}
	}
}
#endif	//NO_LONG_LONG
void doFinalGen (BitSequence *hashval) {	// general case - array of bytes
	register BitSequence *dptr = hashval;
	register int i, j;
	for (i=0; i<ss.wordCount; ++i)
		for (j=ss.wordSizeBytes-1; j>=0; --j)
			*dptr++ = ss.Sum[i].b[j];		// get final result byte
}

//========================================================
// finalise the hash and output the message digest
//========================================================
HashReturn Blender_Final(Blender_hashState *state, BitSequence *hashval) {
	register int i, j, k, hwm;
	DataLength datalen;
	int lenlen;					// length of the length
	int spaceleft, spaceneeded, fillsize;
	int filllen;				// amount of fill available
	Uint32 chksum;
	BitSequence buffer[64];	// workspace area
	memcpy (&ss, state, sizeof(ss));			// get state in local workspace

	// 1. determine the length of the length
	lenlen = 0;				// assume short message (<2**64 bits)
	if ((datalen = ss.sourceDataLength2[2]) != 0)
		lenlen = 3 * sizeof (ss.sourceDataLength);	// 3 x 8 bytes plus
	else if ((datalen = ss.sourceDataLength2[1]) != 0)
		lenlen = 2 * sizeof (ss.sourceDataLength);	// 2 x 8 bytes plus
	else if ((datalen = ss.sourceDataLength2[0]) != 0)
		lenlen = sizeof (ss.sourceDataLength);		// 8 bytes plus
	else
		datalen = ss.sourceDataLength;
	do {					// count bytes used
		lenlen += 1;
		datalen >>= 8;		// remove low order byte
	} while (datalen != 0);
	//printf(" lenlen=%d", lenlen);

	// 2. determine the fill size in bytes
	spaceleft = (ss.roundsToGo - 2) * ss.fragSizeBytes;
	spaceneeded = lenlen + 2 + ss.residueLength;
	while (spaceleft < spaceneeded)		// add a block (or more)
		spaceleft += (ss.blockSizeFrags * ss.fragSizeBytes);
	fillsize = spaceleft + 1 - spaceneeded;
	//printf (" fillsize=%d", fillsize);

	// 3. move message residue to work buffer
	if ((i = (int)ss.residueLength) > 0)
		memcpy (&buffer[0], &ss.messageResidue[0], i);
	//printf (" residue moved");

	// 4. inflate the fill buffer if required and possible
	j = (int)ss.firstByteCount;			// amount of fill available
	if ((j < FBSIZE) && (i > 0)) {		// need to concatenate residue
		k = i;							// potential copy size
		if ((k + j) > FBSIZE)
			k = FBSIZE - j;				// reduce copy amount
		memcpy (&ss.firstBlock[j], &ss.messageResidue[0], k);
		j += k;							// new amount of fill available
	}
	if (j == 0)							// no fill data at all
		j = FBSIZE;						// so use all zeroes
	filllen = j;
	if ((fillsize > j) && ((j << 1) <= FBSIZE)) {
		for (k=j; j+k <= FBSIZE; k+=j)	// replicate fill
			memcpy (&ss.firstBlock[k], &ss.firstBlock[0], j);
		filllen = k;					// updated amount available
	}
	//printf (" filllen=%d", filllen);

	// 5. add fill to work buffer
	j = (sizeof (buffer) - filllen) / ss.fragSizeBytes;	// capacity in fragments
	hwm = j * ss.fragSizeBytes;				// buffer high water mark
	while (fillsize > 0) {
		if (filllen > fillsize)
			filllen = fillsize;				// reduce amount to copy
		memcpy (&buffer[i], &ss.firstBlock, filllen);
		fillsize -= filllen;				// reduce amount to go
		if ((i += filllen) > hwm) {			// advance buffer pointer
			doUpdate (&buffer[0], hwm);		// process chunk
			i -= hwm;						// amount of data left in buffer
			memcpy (&buffer[0], &buffer[hwm], i);
		}
	}
	//printf (" buffer filled");

	// 6. add length to work buffer
	datalen = ss.sourceDataLength;			// first part of length
	j = lenlen;								// bytes to be set
	for (k=0; k<32; ++k) {		// only four elements in this implementation
		buffer[i++] = (Uint8)datalen;		// store low order byte
		if (--j == 0)
			break;							// all relevant data set
		datalen >>= 8;						// remove byte
		if (sizeof (ss.sourceDataLength) > 4) {
			if ((k & 7) == 7)					// last byte of word
				datalen = ss.sourceDataLength2[k >> 3];	// get next word
		} else
			if ((k & 3) == 3)					// last byte of word
				datalen = ss.sourceDataLength2[k >> 2];	// get next word
		if ((i > hwm) && ((i + j + 1) > 64)) {
			doUpdate (&buffer[0], hwm);		// process chunk
			i -= hwm;						// amount of data left in buffer
			memcpy (&buffer[0], &buffer[hwm], i); }
	}
	//printf (" length added");

	// 7. add length of length to work buffer
	buffer[i++] = lenlen;				// store length of the length
			// note that should make an exact multiple of the word length

	// 8. process work buffer
	doUpdate (&buffer[0], i);			// process chunk
	//printf (" update done");

	// 9. move checksums to work buffer - ugly, revise later
	k = ss.fragSizeBytes;
	if (ss.member == Vgen) {		// general case - byte sequence
		for (i=0; i<k; ++i)
			buffer[i] = ~ss.Checksum1.b[i];		// first checksum btes
		for (j=0; j<k; ++j)
			buffer[i++] = ss.Checksum2.b[j];	// second checksum bytes
	} else if (ss.wordSizeBytes >= 4) {		// 64-bit variant
#ifndef NO_LONG_LONG
		datalen = ~ss.Checksum1.ui64;		// first checksum
		for (i=j=0; j<k; ++j) {
			buffer[i++] = (Uint8)datalen;	// store low order byte
			datalen >>= 8;					// remove byte
		}
		datalen = ss.Checksum2.ui64;		// second checksum
		for (j=0; j<k; ++j) {
			buffer[i++] = (Uint8)datalen;	// store low order byte
			datalen >>= 8;					// remove byte
		}
#else	//NO_LONG_LONG
		datalen = ~ss.Checksum1.ui64.llw;	// first checksum
		for (i=j=0; j<4; ++j) {
			buffer[i++] = (Uint8)datalen;	// store low order byte
			datalen >>= 8;					// remove byte
		}
		datalen = ~ss.Checksum1.ui64.hlw;	// high half
		for (j=0; j<4; ++j) {
			buffer[i++] = (Uint8)datalen;	// store low order byte
			datalen >>= 8;					// remove byte
		}
		datalen = ss.Checksum2.ui64.llw;	// second checksum
		for (j=0; j<4; ++j) {
			buffer[i++] = (Uint8)datalen;	// store low order byte
			datalen >>= 8;					// remove byte
		}
		datalen = ss.Checksum2.ui64.hlw;	// high half
		for (j=0; j<4; ++j) {
			buffer[i++] = (Uint8)datalen;	// store low order byte
			datalen >>= 8;					// remove byte
		}
#endif	//NO_LONG_LONG
	} else if (ss.wordSizeBytes >= 2) {		// 32-bit variant
		chksum = ~ss.Checksum1.ui32;		// first checksum
		for (i=j=0; j<k; ++j) {
			buffer[i++] = (Uint8)chksum;	// store low order byte
			chksum >>= 8;					// remove byte
		}
		chksum = ss.Checksum2.ui32;			// second checksum
		for (j=0; j<k; ++j) {
			buffer[i++] = (Uint8)chksum;	// store low order byte
			chksum >>= 8;					// remove byte
		}
	} else {								// 16-bit variant
		j = ~ss.Checksum1.ui16;				// first checksum
		buffer[0] = j;
		buffer[1] = j >> 8;
		j = ss.Checksum2.ui16;				// second checksum
		buffer[2] = j;
		buffer[3] = j >> 8;
		i = 4;
	}
	//printf (" checksums prepared");

	// 10. process work buffer
	doUpdate (&buffer[0], i);				// process final chunk
	//printf (" checksums processed");

	// 11. output message digest
	if (ss.member == Vgen)					// general byte format
		doFinalGen (hashval);
	else if (ss.wordSizeBytes >= 4)			// 64-bit variants
		doFinal64 (hashval);
	else if (ss.wordSizeBytes >= 2)			// 32-bit variants
		doFinal32 (hashval);
	else									// 16-bit variants
		doFinal16 (hashval);
	//printf (" doFinal finished");

#ifdef VERBOSE
	//fclose (fp_log);
	//fp_log = NULL;
#endif
	memcpy (state, &ss, sizeof(ss));		// save local workspace
	return SUCCESS;
}

//========================================================
// top level all-in-one function call
//========================================================

int BlenderHash(int hashbitlen, const BitSequence *data,DataLength databitlen, BitSequence *hashval)
{
	Blender_hashState	state;
	HashReturn	retval;

	retval = Blender_Init(&state, hashbitlen);

	if (retval == SUCCESS)	retval = Blender_Update (&state, data, databitlen);
	if (retval == SUCCESS)	retval = Blender_Final (&state, hashval);

	return retval;
}

//=============================================================================


//========================================================
// utility routines to output the state in each round
//========================================================
#ifdef VERBOSE
void showHex64 (unsigned long long val) {
	register Uint32 hi, lo;
	lo = (Uint32)val;
	hi = (Uint32)(val >> 32);
	fprintf(fp_log, "%08X%08X", hi, lo);
}
void showBytes (int count, Uint8 *values) {
	register int i;
	for (i=count; i>=0; --i)
		fprintf (fp_log, " %02X", values[i]);
}
#ifndef NO_LONG_LONG
void showState64 (unsigned long long fragment, unsigned long long T1, 
				  unsigned long long T2, int carry1, int carry2) {
	register int i, j;
	if (fp_log == NULL)
		fp_log = fopen("hashlog.txt", "a");
	if (vround > 0) {
		fprintf(fp_log, "Round %d:\r\n", vround);
		fprintf(fp_log, "frag="); showHex64(fragment);
		fprintf(fp_log, " csum1="); showHex64(ss.Checksum1.ui64);
		fprintf(fp_log, " csum2="); showHex64(ss.Checksum2.ui64);
		fprintf(fp_log, " T1="); showHex64(T1);
		fprintf(fp_log, " T2="); showHex64(T2);
		fprintf(fp_log, " carry[1-2]=%d %d\r\n", carry1, carry2);
	}
	j = ss.wordCount;		// number of words in hash
	fprintf(fp_log, "Word[0-%d]=", j-1);
	for (i=0; i<j; ++i) {
		fprintf(fp_log, " "); showHex64(ss.Word[i].ui64); }
	fprintf(fp_log, "\r\nSum[0-%d]=", j-1);
	for (i=0; i<j; ++i) {
		fprintf(fp_log, " "); showHex64(ss.Sum[i].ui64); }
	fprintf(fp_log, "\r\n");
}
#else	//NO_LONG_LONG
void showState64n (Uint32 fraglo, Uint32 fraghi, Uint32 T1lo, Uint32 T1hi,
				   Uint32 T2lo, Uint32 T2hi, int carry1, int carry2) {
	register int i, j;
	if (fp_log == NULL)
		fp_log = fopen("hashlog.txt", "a");
	if (vround > 0) {
		fprintf(fp_log, "Round %d:\r\n", vround);
		fprintf(fp_log, "frag=%08X%08X", fraghi, fraglo);
		fprintf(fp_log, " csum1=%08X%08X", ss.Checksum1.ui64.hlw, ss.Checksum1.ui64.llw);
		fprintf(fp_log, " csum2=%08X%08X", ss.Checksum2.ui64.hlw, ss.Checksum2.ui64.llw);
		fprintf(fp_log, " T1=%08X%08X", T1hi, T1lo);
		fprintf(fp_log, " T2=%08X%08X", T2hi, T2lo);
		fprintf(fp_log, " carry[1-2]=%d %d\r\n", carry1, carry2);
	}
	j = ss.wordCount;		// number of words in hash
	fprintf(fp_log, "Word[0-%d]=", j-1);
	for (i=0; i<j; ++i) {
		fprintf(fp_log, " %08X%08X", ss.Word[i].ui64.hlw, ss.Word[i].ui64.llw); }
	fprintf(fp_log, "\r\nSum[0-%d]=", j-1);
	for (i=0; i<j; ++i) {
		fprintf(fp_log, " %08X%08X", ss.Sum[i].ui64.hlw, ss.Sum[i].ui64.llw); }
	fprintf(fp_log, "\r\n");
}
#endif	//NO_LONG_LONG
void showState32 (Uint32 fragment, Uint32 T1, Uint32 T2, int carry1, int carry2) {
	register int i, j;
	if (fp_log == NULL)
		fp_log = fopen("hashlog.txt", "a");
	if (vround > 0) {
		fprintf(fp_log, "Round %d:\r\n", vround);
		fprintf(fp_log, "frag=%08X", fragment);
		fprintf(fp_log, " csum1=%08X", ss.Checksum1);
		fprintf(fp_log, " csum2=%08X", ss.Checksum2);
		fprintf(fp_log, " T1=%08X", T1);
		fprintf(fp_log, " T2=%08X", T2);
		fprintf(fp_log, " carry[1-2]=%d %d\r\n", carry1, carry2);
	}
	j = ss.wordCount;		// number of words in hash
	fprintf(fp_log, "Word[0-%d]=", j-1);
	for (i=0; i<j; ++i)
		fprintf(fp_log, " %08X", ss.Word[i]);
	fprintf(fp_log, "\r\nSum[0-%d]=", j-1);
	for (i=0; i<j; ++i)
		fprintf(fp_log, " %08X", ss.Sum[i]);
	fprintf(fp_log, "\r\n");
}
void showState16 (Uint16 fragment, Uint16 T1, Uint16 T2, int carry1, int carry2) {
	register int i, j;
	if (fp_log == NULL)
		fp_log = fopen("hashlog.txt", "a");
	if (vround > 0) {
		fprintf(fp_log, "Round %d:\r\n", vround);
		fprintf(fp_log, "frag=%04X", fragment);
		fprintf(fp_log, " csum1=%04X", ss.Checksum1);
		fprintf(fp_log, " csum2=%04X", ss.Checksum2);
		fprintf(fp_log, " T1=%04X", T1);
		fprintf(fp_log, " T2=%04X", T2);
		fprintf(fp_log, " carry[1-2]=%d %d\r\n", carry1, carry2);
	}
	j = ss.wordCount;		// number of words in hash
	fprintf(fp_log, "Word[0-%d]=", j-1);
	for (i=0; i<j; ++i)
		fprintf(fp_log, " %04X", ss.Word[i]);
	fprintf(fp_log, "\r\nSum[0-%d]=", j-1);
	for (i=0; i<j; ++i)
		fprintf(fp_log, " %04X", ss.Sum[i]);
	fprintf(fp_log, "\r\n");
}
// triple compression function versions
#ifndef NO_LONG_LONG
void showState64t (unsigned long long fragment, unsigned long long T1, 
		unsigned long long T2, unsigned long long T3, int carry1, int carry2, int carry3) {
	register int i, j;
	if (fp_log == NULL)
		fp_log = fopen("hashlog.txt", "a");
	if (vround > 0) {
		fprintf(fp_log, "Round %d:\r\n", vround);
		fprintf(fp_log, "frag="); showHex64(fragment);
		fprintf(fp_log, " csum1="); showHex64(ss.Checksum1.ui64);
		fprintf(fp_log, " csum2="); showHex64(ss.Checksum2.ui64);
		fprintf(fp_log, " T1="); showHex64(T1);
		fprintf(fp_log, " T2="); showHex64(T2);
		fprintf(fp_log, " T3="); showHex64(T3);
		fprintf(fp_log, " carry[1-3]=%d %d %d\r\n", carry1, carry2, carry3);
	}
	j = ss.wordCount;		// number of words in hash
	fprintf(fp_log, "Word[0-%d]=", j-1);
	for (i=0; i<j; ++i) {
		fprintf(fp_log, " "); showHex64(ss.Word[i].ui64); }
	fprintf(fp_log, "\r\nSum[0-%d]=", j-1);
	for (i=0; i<j; ++i) {
		fprintf(fp_log, " "); showHex64(ss.Sum[i].ui64); }
	fprintf(fp_log, "\r\n");
}
#else	//NO_LONG_LONG
void showState64tn (Uint32 fraglo, Uint32 fraghi, Uint32 T1lo, Uint32 T1hi, Uint32 T2lo,
		Uint32 T2hi, Uint32 T3lo, Uint32 T3hi, int carry1, int carry2, int carry3) {
	register int i, j;
	if (fp_log == NULL)
		fp_log = fopen("hashlog.txt", "a");
	if (vround > 0) {
		fprintf(fp_log, "Round %d:\r\n", vround);
		fprintf(fp_log, "frag=%08X%08X", fraghi, fraglo);
		fprintf(fp_log, " csum1=%08X%08X", ss.Checksum1.ui64.hlw, ss.Checksum1.ui64.llw);
		fprintf(fp_log, " csum2=%08X%08X", ss.Checksum2.ui64.hlw, ss.Checksum2.ui64.llw);
		fprintf(fp_log, " T1=%08X%08X", T1hi, T1lo);
		fprintf(fp_log, " T2=%08X%08X", T2hi, T2lo);
		fprintf(fp_log, " T3=%08X%08X", T3hi, T3lo);
		fprintf(fp_log, " carry[1-3]=%d %d %d\r\n", carry1, carry2, carry3);
	}
	j = ss.wordCount;		// number of words in hash
	fprintf(fp_log, "Word[0-%d]=", j-1);
	for (i=0; i<j; ++i) {
		fprintf(fp_log, " %08X%08X", ss.Word[i].ui64.hlw, ss.Word[i].ui64.llw); }
	fprintf(fp_log, "\r\nSum[0-%d]=", j-1);
	for (i=0; i<j; ++i) {
		fprintf(fp_log, " %08X%08X", ss.Sum[i].ui64.hlw, ss.Sum[i].ui64.llw); }
	fprintf(fp_log, "\r\n");
}
#endif	//NO_LONG_LONG
void showState32t (Uint32 fragment, Uint32 T1, Uint32 T2, Uint32 T3,
				   int carry1, int carry2, int carry3) {
	register int i, j;
	if (fp_log == NULL)
		fp_log = fopen("hashlog.txt", "a");
	if (vround > 0) {
		fprintf(fp_log, "Round %d:\r\n", vround);
		fprintf(fp_log, "frag=%08X", fragment);
		fprintf(fp_log, " csum1=%08X", ss.Checksum1);
		fprintf(fp_log, " csum2=%08X", ss.Checksum2);
		fprintf(fp_log, " T1=%08X", T1);
		fprintf(fp_log, " T2=%08X", T2);
		fprintf(fp_log, " T3=%08X", T3);
		fprintf(fp_log, " carry[1-3]=%d %d %d\r\n", carry1, carry2, carry3);
	}
	j = ss.wordCount;		// number of words in hash
	fprintf(fp_log, "Word[0-%d]=", j-1);
	for (i=0; i<j; ++i)
		fprintf(fp_log, " %08X", ss.Word[i]);
	fprintf(fp_log, "\r\nSum[0-%d]=", j-1);
	for (i=0; i<j; ++i)
		fprintf(fp_log, " %08X", ss.Sum[i]);
	fprintf(fp_log, "\r\n");
}
void showState16t (Uint16 fragment, Uint16 T1, Uint16 T2, Uint16 T3,
				   int carry1, int carry2, int carry3) {
	register int i, j;
	if (fp_log == NULL)
		fp_log = fopen("hashlog.txt", "a");
	if (vround > 0) {
		fprintf(fp_log, "Round %d:\r\n", vround);
		fprintf(fp_log, "frag=%04X", fragment);
		fprintf(fp_log, " csum1=%04X", ss.Checksum1);
		fprintf(fp_log, " csum2=%04X", ss.Checksum2);
		fprintf(fp_log, " T1=%04X", T1);
		fprintf(fp_log, " T2=%04X", T2);
		fprintf(fp_log, " T3=%04X", T3);
		fprintf(fp_log, " carry[1-3]=%d %d %d\r\n", carry1, carry2, carry3);
	}
	j = ss.wordCount;		// number of words in hash
	fprintf(fp_log, "Word[0-%d]=", j-1);
	for (i=0; i<j; ++i)
		fprintf(fp_log, " %04X", ss.Word[i]);
	fprintf(fp_log, "\r\nSum[0-%d]=", j-1);
	for (i=0; i<j; ++i)
		fprintf(fp_log, " %04X", ss.Sum[i]);
	fprintf(fp_log, "\r\n");
}
#endif

//=============================================================================
// end of Blender source code
//=============================================================================
