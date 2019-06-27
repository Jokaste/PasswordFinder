/* streamhash_64.c by Michal Trojnara 2007-2008 */

#include "Fns_StreamHash.h"
#include "Fns_StreamHash_Sbox32.h"

int buffer[1<<24] ;

int HashStream_Init(HashStream_HashState *state,int hashbitlen)
{
    register	int i ;

    switch(hashbitlen) {
        case 224:
		case 256:
		case 384:
		case 512: break ;
        default: return HASHSTREAM_BAD_HASHLEN ;
    }
    state->hashbitlen=hashbitlen ;
    state->tablen=hashbitlen/32 ;

    for(i=0 ; i<state->tablen ; ++i)
        state->tabval[i]=0 ; /* initial state value */

    state->bitval=state->bitlen=0 ;

    return HASHSTREAM_SUCCESS ;
}

#define process_word(i) state->tabval[i]^=sbox32[(state->tabval[i]^b^i)&0xff]

int HashStream_Update(HashStream_HashState *state,const unsigned char *data,unsigned long long databitlen)
{
    unsigned long long p,divlen=databitlen/8 ;
    unsigned char modlen=databitlen%8 ;
    int b ;

    /* "all calls to  update will contain data lengths that
       are divisible by 8,except,possibly,the last call" */

    if(state->bitlen) /* it was previously changed to a non-zero value */
        return HASHSTREAM_FAIL ;

    /* the main loop */

    for(p=0 ; p<divlen ; ++p) { /* each input byte */
        b=data[p] ;
        switch(state->tablen) {
        case 16: /* 512 bits */
            process_word(15) ;
            process_word(14) ;
            process_word(13) ;
            process_word(12) ;
        case 12: /* 384 bits */
            process_word(11) ;
            process_word(10) ;
            process_word(9) ;
            process_word(8) ;
        case 8: /* 256 bits */
            process_word(7) ;
        case 7: /* 224 bits */
            process_word(6) ;
            process_word(5) ;
            process_word(4) ;
            process_word(3) ;
            process_word(2) ;
            process_word(1) ;
            process_word(0) ;
        }
    }

    /* save the remaining bits if any */
    if(modlen)
	{ /* data length is not divisible by 8 (last call) */
        state->bitval=(unsigned char)(data[p] & 0xff<<(8-modlen)) ;
        state->bitlen=modlen ;
    }

    return HASHSTREAM_SUCCESS ;
}

int HashStream_Final(HashStream_HashState *state,unsigned char *hashval)
{
    register	int i ;

    /* update the state vector with the remaining input bits */
    hashval[0]=state->bitval ;
    hashval[1]=state->bitlen ;
    state->bitlen=0 ; /* reset the number of remaining bits */
    HashStream_Update(state,hashval,16) ; /* two bytes */

    /* update with least significant bytes of the state vector */

    for(i = 0 ; i < state->tablen ; ++i)
	{
        hashval[2*i+1]=(unsigned char)(state->tabval[i]>>8) ;
        hashval[2*i]=(unsigned char)(state->tabval[i]) ; /* LSB */
    }

    HashStream_Update(state,hashval,16*state->tablen) ;

    /* diffuse the state vector  */

    for(i=0 ; i<3*state->tablen ; ++i) /* 3 interations per 32-bit word */
        state->tabval[(i+1)%state->tablen]+=state->tabval[i%state->tablen] ;

    /* copy the state vector using high-endian byte order */

    for(i=0 ; i<state->tablen ; ++i) {
        hashval[4*i]=(unsigned char)(state->tabval[i]>>24) ; /* MSB */
        hashval[4*i+1]=(unsigned char)(state->tabval[i]>>16) ;
        hashval[4*i+2]=(unsigned char)(state->tabval[i]>>8) ;
        hashval[4*i+3]=(unsigned char)(state->tabval[i]) ; /* LSB */
    }

    /* diffuse the returned vector */

    for(i=0 ; i<4*state->tablen ; ++i) /* 1 iteration per octet */
        hashval[(i+1)%(4*state->tablen)]+=hashval[i] ;

    return HASHSTREAM_SUCCESS ;
}

int HashStream_Hash(int hashbitlen,const unsigned char *data,unsigned long long databitlen,unsigned char *hashval)
{
    HashStream_HashState state ;

	return	(int)	((int)HashStream_Init(&state,hashbitlen) ||
					(int) HashStream_Update(&state,data,databitlen) ||
					(int) HashStream_Final(&state,hashval)) ;
}

/* end of streamhash_64.c */
