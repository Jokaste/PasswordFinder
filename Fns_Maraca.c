/*
-----------------------------------------------------------------
Alternative implementation of Maraca,a candidate for the NIST 
SHA-3 cryptographic hash competition.  Lengths here are in bytes,
not bits,and there is no way to hash fractional bytes.

Bits are arranged in an 8x8 grid of 16-bit chunks.  A 1024-bit 
permutation (perm()) consists of applying a 16-bit permutation to 
each chunk,then 
rotating each of the 16 bit positions by different amounts through 
the 64 chunks.  The rotates are chosen so 2 bits each are shifted 
up by 0..7 and left by 0..7.

The nonlinear mix of 16-bit chunks is actually an 8-bit permutation 
applied to the even bits and again to the odd bits,with the 16 bits 
shuffled at the end.  This is 5 NAND-gates deep.  6 of the 16 bits
implement a^b^c^d,and can be inverted and still be implemented 5 
NAND-gates deep.  Symmetry is broken by inverting different subsets
of these 6 bits in each of the 64 chunks.  Symmetry breaking is done
in software by XORing constants.  The 16-bit permutation has avalanche
of 0.3906 when applied to itself three times.

The 64 16-bit permutations are actually 128 8-bit permutations.  All
128 8-bit permutations are done at once with SSE instructions.  It 
takes 8 perms forward or 7 perms backwards for all bits to be 
affected by all one-bit deltas for nearly-zero states (avalanche 
0.12 forward,0.41 backward).  (7 perms forward (avalanche 0.37) 
or 6 backwards (avalanche 0.38) for random states.)  

I'm making an ungrounded assumption that twice forward + backward
avalanche,30 perms that is,is enough to thwart cryptanalysis.
Further,I'm assuming it doesn't matter if these are consecutive 
perms.  This is done by combining a block every 3 perms.  Each block 
is combined four times,before permutations 3i,3(i+21-6(i%4))+1,
3(i+41-6((i+2)%4))+1,and 3(i+46)+1.  The offset by two perms for 
the first use guarantees at least one perm of differentials is 
required per blocks.

(by Bob Jenkins,October 21 2008,public domain)
-----------------------------------------------------------------
*/

#include <stdio.h>
#include <stddef.h>
#include <windows.h>
#include <emmintrin.h>

typedef unsigned long  u4;
typedef unsigned long long u8;

#define LEN 16     /* number of 8-byte values per block */

#define ROWS 8
#define COLS 8

#define ROUNDS 20000

#define xor(a,b) (a ^ b)
#define or(a,b) (a | b)
#define and(a,b) (a & b)
#define ant(a,b) (~a & b)
#define not(a) ~a
#define read(x,i) x[i*2]
#define write(y,i,a) y[i*2] = a

/* apply the 8-bit permutation to all 64 bits of the even values */
static void eight( u8 *x,u8 *y)
{
  u8 q,r;
  u8 a0 = read(x,0);
  u8 a1 = read(x,1);
  u8 a2 = read(x,2);
  u8 a3 = read(x,3);
  u8 a4 = read(x,4);
  u8 a5 = read(x,5);
  u8 a6 = read(x,6);
  u8 a7 = read(x,7);

  q = xor(a4,a5);
  r = xor(a7,a0);
  write(y,0,xor(q,r));

  q = xor(a5,a1);
  r = xor(a3,a2);
  write(y,1,xor(q,r));

  q = xor(a3,a4);
  r = xor(a5,a1);
  write(y,2,xor(q,r));

  q = ant(xor(a0,a3),xor(a6,a4));
  r = ant(xor(a4,a6),or(and(a0,a1),ant(a0,a3)));
  write(y,3,or(q,r));

  q = ant(xor(a6,a7),xor(a5,a2));
  r = and(or(not(or(a2,a5)),and(a4,a5)),xor(a7,a6));
  write(y,4,or(q,r));

  q = and(xor(a5,a0),xor(a4,a2));
  r = ant(xor(a2,a4),or(and(a0,a5),ant(a0,a1)));
  write(y,5,or(q,r));

  q = and(xor(a4,a2),xor(a7,a6));
  r = ant(xor(a2,a4),or(ant(a7,a0),and(a6,a7)));
  write(y,6,or(q,r));

  q = and(or(not(or(a6,a7)),ant(and(a6,a7),a0)),xor(a4,a2));
  r = ant(xor(a2,a4),or(ant(and(a0,a2),a6),ant(a0,a7)));
  write(y,7,or(q,r));

}

#undef xor
#undef or
#undef and
#undef ant
#undef not
#undef read
#undef write

#define xor(a,b) _mm_xor_si128(a,b)
#define or(a,b) _mm_or_si128(a,b)
#define and(a,b) _mm_and_si128(a,b)
#define ant(a,b) _mm_andnot_si128(a,b)
#define not(a) _mm_xor_si128(a,_mm_set_epi32(0xffffffff,0xffffffff,0xffffffff,0xffffffff))
#define read(x,i) _mm_load_si128((void *)&x[i])
#define write(y,i,a) _mm_storeu_si128((void *)&y[i],a)

/* apply the 8-bit permutation to all 128 bits of all values */
static void eightSSE(__m128i *x,__m128i *y)
{
  __m128i q,r;
  __m128i a0 = read(x,0);
  __m128i a1 = read(x,1);
  __m128i a2 = read(x,2);
  __m128i a3 = read(x,3);
  __m128i a4 = read(x,4);
  __m128i a5 = read(x,5);
  __m128i a6 = read(x,6);
  __m128i a7 = read(x,7);

  q = xor(a4,a5);
  r = xor(a7,a0);
  write(y,0,xor(q,r));

  q = xor(a5,a1);
  r = xor(a3,a2);
  write(y,1,xor(q,r));

  q = xor(a3,a4);
  r = xor(a5,a1);
  write(y,2,xor(q,r));

  q = ant(xor(a0,a3),xor(a6,a4));
  r = ant(xor(a4,a6),or(and(a0,a1),ant(a0,a3)));
  write(y,3,or(q,r));

  q = ant(xor(a6,a7),xor(a5,a2));
  r = and(or(not(or(a2,a5)),and(a4,a5)),xor(a7,a6));
  write(y,4,or(q,r));

  q = and(xor(a5,a0),xor(a4,a2));
  r = ant(xor(a2,a4),or(and(a0,a5),ant(a0,a1)));
  write(y,5,or(q,r));

  q = and(xor(a4,a2),xor(a7,a6));
  r = ant(xor(a2,a4),or(ant(a7,a0),and(a6,a7)));
  write(y,6,or(q,r));

  q = and(or(not(or(a6,a7)),ant(and(a6,a7),a0)),xor(a4,a2));
  r = ant(xor(a2,a4),or(ant(and(a0,a2),a6),ant(a0,a7)));
  write(y,7,or(q,r));

}

/* one permutation of the internal state */
static void perm(u8 *x)
{
  __m128i y2[LEN/2];
  u8 *y = (u8 *)y2;

  /* do 128 8-bit permutations */
  eightSSE((__m128i *)x,(__m128i *)y);

  /* break symmetry among the 64 16-bit permutations */
  y[0] ^= 0x18f8aa72369b75c2LL;
  y[1] ^= 0x337b824aab77201fLL;
  y[2] ^= 0x60bd51315e37b49cLL;
  y[3] ^= 0x82ed31eb138e02efLL;
  y[4] ^= 0x5fe101ed66fc3130LL;
  y[5] ^= 0x1019906dca58dffbLL;

  /* shuffle and rotate the 16 output bits among the 64 chunks */
  x[ 2] = (y[0] << 14) | (y[0] >> (64-14));
  x[12] = (y[1] << 55) | (y[1] >> (64-55));
  x[ 8] = (y[2] << 61) | (y[2] >> (64-61));
  x[ 3] = (y[3] << 35) | (y[3] >> (64-35));
  x[ 1] = (y[4] << 30) | (y[4] >> (64-30));
  x[15] = (y[5] << 60) | (y[5] >> (64-60));
  x[11] = (y[6] << 32) | (y[6] >> (64-32));
  x[ 0] = (y[7] << 49) | (y[7] >> (64-49));
  x[14] = (y[8] << 16) | (y[8] >> (64-16));
  x[ 5] = (y[9] <<  4) | (y[9] >> (64- 4));
  x[13] = (y[10]<< 42) | (y[10]>> (64-42));
  x[ 7] = (y[11]<<  5) | (y[11]>> (64- 5));
  x[ 9] = (y[12]<< 26) | (y[12]>> (64-26));
  x[ 4] = (y[13]<< 11) | (y[13]>> (64-11));
  x[10] = (y[14]<< 47) | (y[14]>> (64-47));
  x[ 6] = (y[15]<< 17) | (y[15]>> (64-17));
}

static int unperm[256];

/* a random number generator,for testing,not part of the hash */
typedef struct ranctx { u4 a; u4 b; u4 c; u4 d; } ranctx;

#define rot(x,k) ((x<<k)|(x>>(32-k)))
u4 ranval( ranctx *x ) {
  u4 e = x->a - rot(x->b,27);
  x->a = x->b ^ rot(x->c,17);
  x->b = x->c + x->d;
  x->c = x->d + e;
  x->d = e + x->a;
  return e;
}

void showx(float x,float *worst,int verbose)
{
  x = x/ROUNDS;
  if (x < *worst) *worst = x;
  if (verbose) printf("%3d",(int)(100*x + 0.5));
  if (1.0-x < *worst) *worst = 1.0-x;
}

float showc(float c[ROWS][COLS][LEN],int verbose)
{
  int i,j,k;
  float worst = 1.0;
  for (i=0; i<ROWS; ++i) {
    for (j=0; j<COLS; ++j) {
      for (k=0; k<4; ++k) {
	showx(c[i][j][k],&worst,verbose);
      }
      if (verbose) printf(" ");
    }
    if (verbose) printf("\n");
    for (j=0; j<COLS; ++j) {
      for (k=4; k<8; ++k) {
	showx(c[i][j][k],&worst,verbose);
      }
      if (verbose) printf(" ");
    }
    if (verbose) printf("\n");
    for (j=0; j<COLS; ++j) {
      for (k=8; k<12; ++k) {
	showx(c[i][j][k],&worst,verbose);
      }
      if (verbose) printf(" ");
    }
    if (verbose) printf("\n");
    for (j=0; j<COLS; ++j) {
      for (k=12; k<16; ++k) {
	showx(c[i][j][k],&worst,verbose);
      }
      if (verbose) printf(" ");
    }
    if (verbose) printf("\n\n");
  }
  /* printf("  worst = %f\n",worst); */
  return worst;
}

void set_unperm(void)
{
  u8 x[LEN];
  u8 y[LEN];
  int perm[256];
  int i,j;
  for (i=0; i<256; ++i) {
    for (j=0; j<8; ++j) {
      x[2*j] = (i & (1<<j)) ? 1 : 0;
    }
    eight(x,y);
    perm[i] = 0;

    for (j=0; j<8; ++j) {
      if (y[2*j] & 1) {
	perm[i] ^= (1<<j);
      }
    }
  }
  for (i=0; i<256; ++i) {
    unperm[perm[i]] = i;
  }
}

#define BYTES_PER_BLOCK (sizeof(u8)*LEN)
#define BLOCKS  64    /* pointers to accumulators */
#define ACCUM   47    /* number of actual accumulators */
#define SECOND  21
#define THIRD   41
#define FOURTH  46    /* offset of fourth use of a block */

/* the complete hash state */
typedef  struct maraca_state {
  __m128i hash[LEN/2];      /* the internal state */
  __m128i key[LEN/2];       /* the key */
  __m128i buf[LEN/2];       /* an aligned block of data */
  __m128i abuf[ACCUM][LEN/2];
  __m128i *a[BLOCKS];       /* accumulators */
  u8            length;     /* total length hashed */
  u8            keylen;     /* length of the key */
  unsigned int  offset;     /* offset into the accumulators */
} maraca_state;

#define DO(x) \
  x(0); x(1); x(2); x(3); x(4); x(5); x(6); x(7)

#define COMBINE(i) \
  {						        \
    __m128i  val1 = _mm_load_si128((void *)&accum[i]);	\
    __m128i *where = &state[i];				\
    __m128i  val2 = _mm_load_si128(where);		\
    val2 = _mm_xor_si128(val2,val1);			\
    _mm_storeu_si128(where,val2);			\
  }

static void do_combine(const __m128i *accum,__m128i *state)
{
  DO(COMBINE);
}

#define ACCUMULATE(i) \
  { \
    __m128i  val1 = _mm_load_si128((void *)&((const __m128i *)next)[i]); \
    __m128i *where = &fourth[(i+6) % (LEN/2)];		\
    __m128i  val2;                                      \
    _mm_storeu_si128(where,val1);			\
    where = &third[(i+3) % (LEN/2)];			\
    val2 = _mm_load_si128(where);			\
    val2 = _mm_xor_si128(val2,val1);			\
    _mm_storeu_si128(where,val2);			\
    where = &second[(i+1) % (LEN/2)];			\
    val2 = _mm_load_si128(where);			\
    val2 = _mm_xor_si128(val2,val1);			\
    _mm_storeu_si128(where,val2);			\
    where = &state[i % (LEN/2)];			\
    val2 = _mm_load_si128(where);			\
    val2 = _mm_xor_si128(val2,val1);			\
    _mm_storeu_si128(where,val2);			\
  }

void accumulate(__m128i **a,const __m128i *next,__m128i *state,int x)
{
    __m128i *second = a[(x + SECOND - 6*(x%4)) % BLOCKS];
    __m128i *third  = a[(x + THIRD - 6*((x+2)%4)) % BLOCKS];
    __m128i *fourth = a[(x + FOURTH) % BLOCKS];
    a[(x + ACCUM) % BLOCKS] = a[x % BLOCKS];
    DO(ACCUMULATE);
}

/* one combine */
static void one_combine(
  __m128i  **a,
  unsigned int *index,
  __m128i  *state,
  const void *next)
{
  int x = *index;
  accumulate(a,(const __m128i *)next,state,x);
  perm((u8 *)state);
  do_combine(a[x % BLOCKS],state);
  perm((u8 *)state);
  perm((u8 *)state);
  ++*index;
}

/* add an array of bytes to the hash */
void add( maraca_state *state,const void *data,u8 length)
{
  
//  __m128i buf[LEN/2];   /* hold a block of data */
  unsigned int start = state->length % BYTES_PER_BLOCK;
  size_t stop;
  size_t dataoff = 0;

  /* get started */
  state->length += length;
  if (start != 0) {
    if (length + start < BYTES_PER_BLOCK) {
      memcpy(&((char *)state->buf)[start],data,length);
      return;
    } else {
      unsigned int piece = BYTES_PER_BLOCK-start;
      memcpy(&((char *)state->buf)[start],data,piece);
      one_combine(state->a,&state->offset,state->hash,state->buf);
      data = &((char *)data)[piece];
      length -= piece;
    }
  }

  /* loop: handle whole blocks at a time */
  stop = length - (length % BYTES_PER_BLOCK);
  if ((((size_t)data) % 16) == 0) {
    /* aligned: hash the data directly */
    for (dataoff = 0; dataoff < stop; dataoff += BYTES_PER_BLOCK) {
      one_combine(state->a,&state->offset,state->hash,
		  &((const char *)data)[dataoff]);
    }
  } else {
    for (dataoff = 0; dataoff < stop; dataoff += BYTES_PER_BLOCK) {
      memcpy((char *)state->buf,&((char *)data)[dataoff],BYTES_PER_BLOCK);
      one_combine(state->a,&state->offset,state->hash,state->buf);
    }
  }
  if (dataoff != stop) printf("bob you have a bug\n");

  /* remember the last partial block */
  memcpy(state->buf,&((char *)data)[stop],length-stop);
}

/* initialize the hash */
void init( maraca_state *state,const void *key,int keylen)
{
  register	int i;

  if ((keylen % 16) != 0) { 
    fprintf(stderr,"keylen must be a multiple of 16 bytes\n");
    exit(1);
  }
  /* use the key to set up the state and the accumulators */
  state->offset = 0;
  state->length = 0;
  state->keylen = keylen;
  memset((char *)state->hash,0,BYTES_PER_BLOCK);
  memset((char *)state->abuf,0,sizeof(state->abuf));
  for (i=0; i<ACCUM; ++i) {
    state->a[i] = state->abuf[i];
  }
  if (state->keylen) {
    memcpy((char *)state->key,key,keylen);
    add(state,state->key,state->keylen);
  }
}

/* hash the last piece,the key and length,then report the result */
void final(maraca_state *state,void *hash)
{
  int i;
  int start = state->length % BYTES_PER_BLOCK;
  unsigned short int lengths;  /* two byte length */

  /* Use the key again */
  if (state->keylen) {
    add( state,state->key,state->keylen);
  }

  /* add the keylen,and the padlen,and a 1 */
  lengths = (8*state->keylen)*16 + 1;
  add( state,&lengths,2);

  /* finish off the last partial block */
  start = state->length % BYTES_PER_BLOCK;
  if (start) {
    memset(&((char *)state->buf)[start],0,BYTES_PER_BLOCK-start);
    one_combine(state->a,&state->offset,state->hash,state->buf);
  }

  /* use up the accumulators */
  for (i=1; i<=FOURTH; ++i) {
    perm((u8 *)state->hash);
    do_combine(state->a[state->offset++ % BLOCKS],state->hash);
    perm((u8 *)state->hash);
    perm((u8 *)state->hash);
  }

  /* do 30 strengthening permutations after the final block use */
  for (i=2; i<30; ++i) {
    perm((u8 *)state->hash);
  }

  /* report the final state */
  memcpy(hash,state->hash,BYTES_PER_BLOCK);
}

void Maraca_Hash(
  const void *data,/* array of bytes to hash,align to 8-byte boundary! */
  u8 data_length,       /* original length of the data,in bytes */
  const void *key, /* 128-byte key */
  int keylen,      /* length of key */
  void  *result)      /* 128-byte hash value */
{
  maraca_state state;

  init(&state,key,keylen);
  add(&state,data,data_length);
  final(&state,result);
}

