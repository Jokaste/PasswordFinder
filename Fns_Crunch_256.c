/*
This algorithm doesn't shift the data between each round of the Feistel Scheme.
*/
#include <stdio.h>
#include <stdlib.h>

#include "Fns_Crunch_Type.h"

// Constantes liées à l'algorithme

#define CRUNCH_K_256 128 // number of subdivisions of input
// Constantes pour l'entrée et la sortie
#define CRUNCH_BLOCKSIZE_256 1024 //in bits
#define CRUNCH_HASHLEN_256 256

#define CRUNCH_NBROUND_256 CRUNCH_HASHLEN_256  //nombre de tours pour chacune des schemas de Feistel non symetriques

#ifdef M64
#define CRUNCH_LONGSIZE_256 64
#else
#define CRUNCH_LONGSIZE_256 32
#endif

#define CRUNCH_NE_256 (CRUNCH_BLOCKSIZE_256/CRUNCH_LONGSIZE_256)	// Number of long in input
#define CRUNCH_NS_256 (CRUNCH_HASHLEN_256/CRUNCH_LONGSIZE_256)	// Number of long in outpout
#define CRUNCH_NPM_256 ((CRUNCH_LONGSIZE_256*CRUNCH_K_256)/CRUNCH_BLOCKSIZE_256)	//Longs (32 or 64 bits) are divided in CRUNCH_NPM_256 parts

#define CRUNCH_NA_256 256			// = 2^CRUNCH_NBE_256 number of elements in start ensemble of random function
#define CRUNCH_NBE_256 (CRUNCH_BLOCKSIZE_256/CRUNCH_K_256)		//  number of bits in elements in start ensemble of random function

//macro used to send final results in same order in 32 and 64  bits version (due to integers representation on X86)
#define idx(a)  ( (CRUNCH_LONGSIZE_256/8) * ((a)/(CRUNCH_LONGSIZE_256/8)) + ((CRUNCH_LONGSIZE_256/8)-1) - (a)%(CRUNCH_LONGSIZE_256/8))

#define CRUNCH_SHIFT_256	((CRUNCH_NBROUND_256%128)*8)/CRUNCH_LONGSIZE_256

#define CRUNCH_MAXDATAPERUPDATE_256 1024ULL*1024ULL*1024ULL

/* With a 32 bit compilation nbalea[i] is exactly K_{i-28}&Mask
where K_i are the decimals of 8*abs(sin(i+29))
and Mask value is 0xffffffff most of the time
Other value of Mask are 0x00ffffff, 0xff00ffff, 0xffff00ff, 0xffffff00
see the file gen_alea.c for details
In this way we can xor all the bytes, even the byte which give the value of i in g(i)
*/
extern unsigned long int nbalea[];

//Left data after a call of Update function
unsigned long int LeftData[(CRUNCH_BLOCKSIZE_256-CRUNCH_HASHLEN_256)/CRUNCH_LONGSIZE_256];
unsigned int SizeLeft; //size of left data in bytes
unsigned long int PrevHash[CRUNCH_HASHLEN_256/CRUNCH_LONGSIZE_256];
DataLength TotalInputSizeInBit; //Total size of message in bits


unsigned long int *padding_256(int *nb_final_block)
{
	int new_nb_bit,i,no_block;
	unsigned long int *mes;
	char *mes_char,*DL_char;
	int temp;
	new_nb_bit=SizeLeft*8+1+2*CRUNCH_LONGSIZE_256;
	i=new_nb_bit % (CRUNCH_BLOCKSIZE_256-CRUNCH_HASHLEN_256);
	new_nb_bit+=(CRUNCH_BLOCKSIZE_256-CRUNCH_HASHLEN_256)-i;
	*nb_final_block=new_nb_bit/CRUNCH_LONGSIZE_256;

	mes=(unsigned long  int *)calloc((*nb_final_block),sizeof(unsigned long int));
	mes_char=(char*)mes;
	DL_char=(char*)LeftData;
	/*copy left data in beginning of the block*/
	for(i=0;i<(int) SizeLeft;i++)
	{
 		temp =idx(i) ;
		mes_char[temp]=DL_char[temp];
	}
	no_block=((SizeLeft)*8+1)/CRUNCH_LONGSIZE_256;
	mes[no_block]|=1UL<<( (CRUNCH_LONGSIZE_256-1)-( ((SizeLeft)*8 )%CRUNCH_LONGSIZE_256));
	/*complete block with 0 and stock message size in the last 64bits*/
	#if CRUNCH_LONGSIZE_256==32
	for(i=no_block+1;i<*nb_final_block-2;i++)
	{
		mes[i]=0;
	}
	mes[*nb_final_block-2]=(unsigned long int)(TotalInputSizeInBit>>32);
	mes[*nb_final_block-1]=(unsigned long int)(TotalInputSizeInBit);
	#endif
	#if CRUNCH_LONGSIZE_256==64
	for(i=no_block+1;i<*nb_final_block-1;i++)
	{
		mes[i]=0;
	}
	mes[*nb_final_block-1]=TotalInputSizeInBit; 
	#endif
	return(mes);
}

void Merkle_256(unsigned long int H[],unsigned long int mes[],int nb_merkle) {
	int n,k;
	int j_round,j,a,aa,aa2,p,block;
    	int alpha;
	unsigned long int message[CRUNCH_NE_256],res[CRUNCH_NE_256];
	unsigned long i,i2;
	for(k=0;k<(CRUNCH_NS_256);k++)
	{
		message[k]=H[k];
	}

	for(n=0;n<nb_merkle;n++)
	{
		for(k=0;k<CRUNCH_NS_256;k++)
		{
			res[k]=message[k];
		}
		for(k=(CRUNCH_NS_256) ;k<CRUNCH_NE_256;k++)
		{
			message[k]=mes[k-(CRUNCH_NS_256)];
			res[k]=message[k];
		}
		mes=mes+(CRUNCH_NE_256-CRUNCH_NS_256);


		/*a is the index for the internal function. First value point to the K0 S-box */
		a=CRUNCH_NE_256-(128/CRUNCH_LONGSIZE_256);
 	   	p=0;block=0;
	   	alpha=1;
 	   	for(j_round=0;j_round<CRUNCH_NBROUND_256;j_round++)
 	   	{
        		/* Computation of i and i2 to get g(i) and g'(i2)*/
			i2=(res[block]>>((CRUNCH_NPM_256-1-p)*CRUNCH_NBE_256))&(CRUNCH_NA_256-1);
			i2=(i2*alpha)&0xff;
			i=(message[block]>>((CRUNCH_NPM_256-1-p)*CRUNCH_NBE_256))&(CRUNCH_NA_256-1);
			i=(i*alpha)&0xff;
			aa2=a+CRUNCH_NE_256*CRUNCH_NA_256*16+i2*CRUNCH_NE_256;
			aa=a+i*CRUNCH_NE_256;
        		for(j=0;j<CRUNCH_NE_256;j++)
			{
	   			message[j]^=nbalea[aa];
				aa++;
            			res[j]^=nbalea[aa2];
	    			aa2++;
        		}
        		if ((j_round & 15) == 15)
			{
				alpha=alpha+2;
				if ( (j_round&127) == 127)
				{
					a=CRUNCH_NE_256-(128/CRUNCH_LONGSIZE_256);
				}
				else
				{
					a-=15*CRUNCH_NA_256*CRUNCH_NE_256+128/CRUNCH_LONGSIZE_256;
				}
			}
			else
			{
				a+=CRUNCH_NA_256*CRUNCH_NE_256;
			}
        		p++;
        		if (p==CRUNCH_NPM_256)
			{
        	    		block++;
		    		if (block==CRUNCH_NE_256) block=0;
        	    		p=0;
        		}
		}
		#if CRUNCH_SHIFT_256==0
		for(j=0;j<CRUNCH_NS_256;j++) message[j]^=res[j];
		#else
		for(j=CRUNCH_SHIFT_256;j<CRUNCH_SHIFT_256+CRUNCH_NS_256;j++) res[j%CRUNCH_NE_256]^=message[j%CRUNCH_NE_256];
		for(j=0;j<CRUNCH_NS_256;j++) message[j]=res[(j+CRUNCH_SHIFT_256)%CRUNCH_NE_256];
		#endif
	}
	for(i=0;i<CRUNCH_NS_256;i++) H[i]=message[i];
}

//concatenate the left data of the previous call of update with the new data 
unsigned long int *concatenation_update_256(const BitSequence *data,int databitlen,int *nb_block)
{
	unsigned long int *mes;
	int nb_bits_restants;
	int nb_block_in_new_mes;
	int nb_bits_in_new_mes;
	int i;
	int bits_traite_dans_data;
	int no_block,pos_block;
	int temp;
	char *mes_char,*DL_char;
	nb_bits_in_new_mes=( (databitlen+8*SizeLeft)/(CRUNCH_BLOCKSIZE_256-CRUNCH_HASHLEN_256) )*(CRUNCH_BLOCKSIZE_256-CRUNCH_HASHLEN_256);
	nb_bits_restants=(databitlen+8*SizeLeft)%(CRUNCH_BLOCKSIZE_256-CRUNCH_HASHLEN_256);
	nb_block_in_new_mes=nb_bits_in_new_mes/(CRUNCH_LONGSIZE_256);

	mes = NULL ;

	if(nb_block_in_new_mes>0) 
	{
		/*there is enough of new data to complete a block*/
		mes = (unsigned long int *)calloc( nb_block_in_new_mes,(CRUNCH_LONGSIZE_256/8) );
		if(mes==NULL) return NULL;
		//copy left data to the beginning of the new "message"
		mes_char=(char*)mes;
		DL_char=(char*)LeftData;
		for(i=0;i<(int) SizeLeft;i++)
		{
			temp =(i/(CRUNCH_LONGSIZE_256/8))*(CRUNCH_LONGSIZE_256/8) + ( (CRUNCH_LONGSIZE_256/8-1)-(i%(CRUNCH_LONGSIZE_256/8))) ;
			mes_char[temp]=DL_char[temp];
		}
		/*complete message with new datas*/
		no_block=(i*8)/(CRUNCH_LONGSIZE_256);
		pos_block=(CRUNCH_LONGSIZE_256-8)-( ((i)*8 )%CRUNCH_LONGSIZE_256);
		for(i=0;8*i<(int) nb_bits_in_new_mes-8*(int) SizeLeft;i++) 
		{
			mes[no_block]|=(unsigned long int)data[i] << pos_block;
			pos_block-=8;
			if (pos_block<0) 
			{
				pos_block=CRUNCH_LONGSIZE_256-8;
				no_block++;
			}
		}
		bits_traite_dans_data=i;
		no_block=0;pos_block=CRUNCH_LONGSIZE_256-8;
		SizeLeft=(nb_bits_restants)/8;
		LeftData[0]=0;
	}
	else
	{
		//no new block with new data
		i=0;
		no_block=((SizeLeft)*8+1)/CRUNCH_LONGSIZE_256;
		pos_block= (CRUNCH_LONGSIZE_256-8)-( ((SizeLeft)*8 )%CRUNCH_LONGSIZE_256);
		SizeLeft=SizeLeft+databitlen/8;
	}
	/*save left data of new data for the next call of update/final*/
	for( ;8*i<databitlen;i++) 
	{
		LeftData[no_block]|=(unsigned long int)data[i] << pos_block;
		pos_block-=8;
		if (pos_block<0) 
		{
			pos_block=CRUNCH_LONGSIZE_256-8;
			no_block++;
			LeftData[no_block]=0UL;
		}
	}
	*nb_block=nb_block_in_new_mes;
	return mes;	
}

int Sph_Crunch_Update_256(const BitSequence * data,DataLength databitlen)
{
	unsigned long int *mes;int nb_final_block[1];
//	int i;
	if(databitlen>=CRUNCH_MAXDATAPERUPDATE_256)
	{
		printf("too many data for an update\n");
		return CRUNCH_FAIL;
	}
	mes= concatenation_update_256(data,databitlen,nb_final_block);
	if(*nb_final_block>0)
	{
		if(mes == NULL)
		{
			printf("fail: can't allocate enough memory\n");
			return CRUNCH_FAIL;
		}
	}
	if(*nb_final_block>0)
	{
		Merkle_256(PrevHash,mes,*nb_final_block/(CRUNCH_NE_256-CRUNCH_NS_256));
		free(mes);
	}
	TotalInputSizeInBit+=databitlen;
	return CRUNCH_SUCCESS;
}

int Sph_Crunch_Init_256(void)
{
	int k;
	for(k=0;k<(CRUNCH_HASHLEN_256/CRUNCH_LONGSIZE_256);k++) 
	{
		PrevHash[k]=nbalea[k];
	}
	for(k=0;k<(CRUNCH_BLOCKSIZE_256-CRUNCH_HASHLEN_256)/CRUNCH_LONGSIZE_256;k++)
	{
		LeftData[k]=0;
	}
	SizeLeft=0;
	TotalInputSizeInBit=0;
	return CRUNCH_SUCCESS;
}

int Sph_Crunch_Final_256(BitSequence *hash)
{
	unsigned long int *mes;
	int i;
	int nb_final_block[1];
	char *tocopy;
	mes=padding_256(nb_final_block);
	tocopy=(char*)mes;
	Merkle_256(PrevHash,mes,*nb_final_block/(CRUNCH_NE_256-CRUNCH_NS_256));
	
	tocopy=(char*)PrevHash;
	for(i=0;i<CRUNCH_HASHLEN_256/8;i++)
	{
		hash[i]=tocopy[idx(i)];
	}

	free(mes);
	return CRUNCH_SUCCESS;
}

int Sph_Crunch_Hash_256(const BitSequence *data,DataLength databitlen,BitSequence *hashval) 
{
	CRUNCH_HASHSTATE state;
	int HR;
	int i;
	state.hashbitlen=256;
	HR=Sph_Crunch_Init_256();
	if(HR!=CRUNCH_SUCCESS) return HR;
	i=0;
	while(databitlen>CRUNCH_MAXDATAPERUPDATE_256)
	{
		HR=Sph_Crunch_Update_256(&(data[i*CRUNCH_MAXDATAPERUPDATE_256/8]),CRUNCH_MAXDATAPERUPDATE_256);
		if(HR!=CRUNCH_SUCCESS) return HR;
		databitlen-=(CRUNCH_MAXDATAPERUPDATE_256);
		i++;
	}
	HR=Sph_Crunch_Update_256(&(data[i*CRUNCH_MAXDATAPERUPDATE_256/8]),databitlen);
	HR=Sph_Crunch_Final_256(hashval);
	return HR;
}
