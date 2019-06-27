#include <stdio.h>
#include <stdlib.h>

#include "Fns_Crunch_Type.h"

// Constantes liées à l'algorithme

#define CRUNCH_K_512 128 // number of subdivisions of input
// Constantes pour l'entrée et la sortie
#define CRUNCH_BLOCKSIZE_512 1024 //in bits
#define CRUNCH_HASHLEN_512 512

#define CRUNCH_NBROUND_512 CRUNCH_HASHLEN_512  //nombre de tours pour chacune des schemas de Feistel non symetriques

#ifdef M64
#define CRUNCH_LONGSIZE_512 64
#else
#define CRUNCH_LONGSIZE_512 32
#endif

#define CRUNCH_NE_512 (CRUNCH_BLOCKSIZE_512/CRUNCH_LONGSIZE_512)	// Number of long in input
#define CRUNCH_NS_512 (CRUNCH_HASHLEN_512/CRUNCH_LONGSIZE_512)	// Number of long in outpout
#define CRUNCH_NPM_512 ((CRUNCH_LONGSIZE_512*CRUNCH_K_512)/CRUNCH_BLOCKSIZE_512)	//Longs (32 or 64 bits) are divided in CRUNCH_NPM_512 parts

#define CRUNCH_NA_512 256			// = 2^CRUNCH_NBE_512 number of elements in start ensemble of random function
#define CRUNCH_NBE_512 (CRUNCH_BLOCKSIZE_512/CRUNCH_K_512)		//  number of bits in elements in start ensemble of random function

//macro used to send final results in same order in 32 and 64  bits version (due to integers representation on X86)
#define idx(a)  ( (CRUNCH_LONGSIZE_512/8) * ((a)/(CRUNCH_LONGSIZE_512/8)) + ((CRUNCH_LONGSIZE_512/8)-1) - (a)%(CRUNCH_LONGSIZE_512/8))

#define CRUNCH_SHIFT_512	((CRUNCH_NBROUND_512%128)*8)/CRUNCH_LONGSIZE_512

#define CRUNCH_MAXDATAPERUPDATE_512 1024ULL*1024ULL*1024ULL

extern unsigned long int nbalea[];

//Left data after a call of Update function
unsigned long int LeftData[(CRUNCH_BLOCKSIZE_512-CRUNCH_HASHLEN_512)/CRUNCH_LONGSIZE_512];
unsigned int SizeLeft; //size of left data in bytes
unsigned long int PrevHash[CRUNCH_HASHLEN_512/CRUNCH_LONGSIZE_512];
DataLength TotalInputSizeInBit; //Total size of message in bits


unsigned long int *padding_512(int *nb_final_block)
{
	int new_nb_bit,i,no_block;
	unsigned long int *mes;
	char *mes_char,*DL_char;
	int temp;
	new_nb_bit=SizeLeft*8+1+2*CRUNCH_LONGSIZE_512;
	i=new_nb_bit % (CRUNCH_BLOCKSIZE_512-CRUNCH_HASHLEN_512);
	new_nb_bit+=(CRUNCH_BLOCKSIZE_512-CRUNCH_HASHLEN_512)-i;
	*nb_final_block=new_nb_bit/CRUNCH_LONGSIZE_512;

	mes=(unsigned long  int *)calloc((*nb_final_block),sizeof(unsigned long int));
	mes_char=(char*)mes;
	DL_char=(char*)LeftData;
	/*copy left data in beginning of the block*/
	for(i=0;i<(int)SizeLeft;i++)
	{
 		temp =idx(i) ;
		mes_char[temp]=DL_char[temp];
	}
	no_block=((SizeLeft)*8+1)/CRUNCH_LONGSIZE_512;
	mes[no_block]|=1UL<<( (CRUNCH_LONGSIZE_512-1)-( ((SizeLeft)*8 )%CRUNCH_LONGSIZE_512));
	/*complete block with 0 and stock message size in the last 64bits*/
	#if CRUNCH_LONGSIZE_512==32
	for(i=no_block+1;i<*nb_final_block-2;i++)
	{
		mes[i]=0;
	}
	mes[*nb_final_block-2]=(unsigned long int)(TotalInputSizeInBit>>32);
	mes[*nb_final_block-1]=(unsigned long int)(TotalInputSizeInBit);
	#endif
	#if CRUNCH_LONGSIZE_512==64
	for(i=no_block+1;i<*nb_final_block-1;i++)
	{
		mes[i]=0;
	}
	mes[*nb_final_block-1]=TotalInputSizeInBit; 
	#endif
	return(mes);
}

void Merkle_512(unsigned long int H[],unsigned long int mes[],int nb_merkle) {
	int n,k;
	int j_round,j,a,aa,aa2,p,block;
    	int alpha;
	unsigned long int message[CRUNCH_NE_512],res[CRUNCH_NE_512];
	unsigned long i,i2;
	for(k=0;k<(CRUNCH_NS_512);k++)
	{
		message[k]=H[k];
	}

	for(n=0;n<nb_merkle;n++)
	{
		for(k=0;k<CRUNCH_NS_512;k++)
		{
			res[k]=message[k];
		}
		for(k=(CRUNCH_NS_512) ;k<CRUNCH_NE_512;k++)
		{
			message[k]=mes[k-(CRUNCH_NS_512)];
			res[k]=message[k];
		}
		mes=mes+(CRUNCH_NE_512-CRUNCH_NS_512);

		a=CRUNCH_NE_512-(128/CRUNCH_LONGSIZE_512);
 	   	p=0;block=0;
	   	alpha=1;
 	   	for(j_round=0;j_round<CRUNCH_NBROUND_512;j_round++)
 	   	{
			i2=(res[block]>>((CRUNCH_NPM_512-1-p)*CRUNCH_NBE_512))&(CRUNCH_NA_512-1);
			i2=(i2*alpha)&0xff;
			i=(message[block]>>((CRUNCH_NPM_512-1-p)*CRUNCH_NBE_512))&(CRUNCH_NA_512-1);
			i=(i*alpha)&0xff;
			aa2=a+CRUNCH_NE_512*CRUNCH_NA_512*16+i2*CRUNCH_NE_512;
			aa=a+i*CRUNCH_NE_512;
        		for(j=0;j<CRUNCH_NE_512;j++)
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
					a=CRUNCH_NE_512-(128/CRUNCH_LONGSIZE_512);
				}
				else
				{
					a-=15*CRUNCH_NA_512*CRUNCH_NE_512+128/CRUNCH_LONGSIZE_512;
				}
			}
			else
			{
				a+=CRUNCH_NA_512*CRUNCH_NE_512;
			}
        		p++;
        		if (p==CRUNCH_NPM_512)
			{
        	    		block++;
		    		if (block==CRUNCH_NE_512) block=0;
        	    		p=0;
        		}
		}
		#if CRUNCH_SHIFT_512==0
		for(j=0;j<CRUNCH_NS_512;j++) message[j]^=res[j];
		#else
		for(j=CRUNCH_SHIFT_512;j<CRUNCH_SHIFT_512+CRUNCH_NS_512;j++) res[j%CRUNCH_NE_512]^=message[j%CRUNCH_NE_512];
		for(j=0;j<CRUNCH_NS_512;j++) message[j]=res[(j+CRUNCH_SHIFT_512)%CRUNCH_NE_512];
		#endif
	}
	for(i=0;i<CRUNCH_NS_512;i++) H[i]=message[i];
}

//concatenate the left data of the previous call of update with the new data 
unsigned long int *concatenation_update_512(const BitSequence *data,int databitlen,int *nb_block)
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

	mes = NULL ;

	nb_bits_in_new_mes=( (databitlen+8*SizeLeft)/(CRUNCH_BLOCKSIZE_512-CRUNCH_HASHLEN_512) )*(CRUNCH_BLOCKSIZE_512-CRUNCH_HASHLEN_512);
	nb_bits_restants=(databitlen+8*SizeLeft)%(CRUNCH_BLOCKSIZE_512-CRUNCH_HASHLEN_512);
	nb_block_in_new_mes=nb_bits_in_new_mes/(CRUNCH_LONGSIZE_512);
	if(nb_block_in_new_mes>0) 
	{
		/*there is enough of new data to complete a block*/
		mes = (unsigned long int *)calloc( nb_block_in_new_mes,(CRUNCH_LONGSIZE_512/8) );
		if(mes==NULL) return NULL;
		//copy left data to the beginning of the new "message"
		mes_char=(char*)mes;
		DL_char=(char*)LeftData;
		for(i=0;i<(int)SizeLeft;i++)
		{
			temp =(i/(CRUNCH_LONGSIZE_512/8))*(CRUNCH_LONGSIZE_512/8) + ( (CRUNCH_LONGSIZE_512/8-1)-(i%(CRUNCH_LONGSIZE_512/8))) ;
			mes_char[temp]=DL_char[temp];
		}
		/*complete message with new datas*/
		no_block=(i*8)/(CRUNCH_LONGSIZE_512);
		pos_block=(CRUNCH_LONGSIZE_512-8)-( ((i)*8 )%CRUNCH_LONGSIZE_512);
		for(i=0;8*i<(int)nb_bits_in_new_mes-8*(int) SizeLeft;i++) 
		{
			mes[no_block]|=(unsigned long int)data[i] << pos_block;
			pos_block-=8;
			if (pos_block<0) 
			{
				pos_block=CRUNCH_LONGSIZE_512-8;
				no_block++;
			}
		}
		bits_traite_dans_data=i;
		no_block=0;pos_block=CRUNCH_LONGSIZE_512-8;
		SizeLeft=(nb_bits_restants)/8;
		LeftData[0]=0;
	}
	else
	{
		//no new block with new data
		i=0;
		no_block=((SizeLeft)*8+1)/CRUNCH_LONGSIZE_512;
		pos_block= (CRUNCH_LONGSIZE_512-8)-( ((SizeLeft)*8 )%CRUNCH_LONGSIZE_512);
		SizeLeft=SizeLeft+databitlen/8;
	}
	/*save left data of new data for the next call of update/final*/
	for( ;8*i<databitlen;i++) 
	{
		LeftData[no_block]|=(unsigned long int)data[i] << pos_block;
		pos_block-=8;
		if (pos_block<0) 
		{
			pos_block=CRUNCH_LONGSIZE_512-8;
			no_block++;
			LeftData[no_block]=0UL;
		}
	}
	*nb_block=nb_block_in_new_mes;
	return mes;	
}

int Sph_Crunch_Update_512(const BitSequence * data,DataLength databitlen)
{
	unsigned long int *mes;int nb_final_block[1];
//	int i;
	if(databitlen>=CRUNCH_MAXDATAPERUPDATE_512)
	{
//		printf("too many data for an update\n");
		return CRUNCH_FAIL;
	}
	mes= concatenation_update_512(data,databitlen,nb_final_block);
	if(*nb_final_block>0)
	{
		if(mes == NULL)
		{
//			printf("fail: can't allocate enough memory\n");
			return CRUNCH_FAIL;
		}
	}
	if(*nb_final_block>0)
	{
		Merkle_512(PrevHash,mes,*nb_final_block/(CRUNCH_NE_512-CRUNCH_NS_512));
		free(mes);
	}
	TotalInputSizeInBit+=databitlen;
	return CRUNCH_SUCCESS;
}

int Sph_Crunch_Init_512(void)
{
	int k;
	for(k=0;k<(CRUNCH_HASHLEN_512/CRUNCH_LONGSIZE_512);k++) 
	{
		PrevHash[k]=nbalea[k];
	}
	for(k=0;k<(CRUNCH_BLOCKSIZE_512-CRUNCH_HASHLEN_512)/CRUNCH_LONGSIZE_512;k++)
	{
		LeftData[k]=0;
	}
	SizeLeft=0;
	TotalInputSizeInBit=0;
	return CRUNCH_SUCCESS;
}

int Sph_Crunch_Final_512(BitSequence *hash)
{
	unsigned long int *mes;
	int i;
	int nb_final_block[1];
	char *tocopy;
	mes=padding_512(nb_final_block);
	tocopy=(char*)mes;
	Merkle_512(PrevHash,mes,*nb_final_block/(CRUNCH_NE_512-CRUNCH_NS_512));
	
	tocopy=(char*)PrevHash;
	for(i=0;i<CRUNCH_HASHLEN_512/8;i++)
	{
		hash[i]=tocopy[idx(i)];
	}

	free(mes);
	return CRUNCH_SUCCESS;
}

int Sph_Crunch_Hash_512(const BitSequence *data,DataLength databitlen,BitSequence *hashval) 
{
	CRUNCH_HASHSTATE state;
	int HR;
	int i;
	state.hashbitlen=512;
	HR=Sph_Crunch_Init_512();
	if(HR!=CRUNCH_SUCCESS) return HR;
	i=0;
	while(databitlen>CRUNCH_MAXDATAPERUPDATE_512)
	{
		HR=Sph_Crunch_Update_512(&(data[i*CRUNCH_MAXDATAPERUPDATE_512/8]),CRUNCH_MAXDATAPERUPDATE_512);
		if(HR!=CRUNCH_SUCCESS) return HR;
		databitlen-=(CRUNCH_MAXDATAPERUPDATE_512);
		i++;
	}
	HR=Sph_Crunch_Update_512(&(data[i*CRUNCH_MAXDATAPERUPDATE_512/8]),databitlen);
	HR=Sph_Crunch_Final_512(hashval);
	return HR;
}
