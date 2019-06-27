/* File:    md6_nist.c
** Author:  Ronald L. Rivest
** Address: Room 32G-692 Stata Center 
**          32 Vassar Street 
**          Cambridge,MA 02139
** Email:   rivest@mit.edu
** Date:    9/25/2008
**
** (The following license is known as "The MIT License")
** 
** Copyright (c) 2008 Ronald L. Rivest
** 
** Permission is hereby granted,free of charge,to any person obtaining a copy
** of this software and associated documentation files (the "Software"),to deal
** in the Software without restriction,including without limitation the rights
** to use,copy,modify,merge,publish,distribute,sublicense,and/or sell
** copies of the Software,and to permit persons to whom the Software is
** furnished to do so,subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS",WITHOUT WARRANTY OF ANY KIND,EXPRESS OR
** IMPLIED,INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,DAMAGES OR OTHER
** LIABILITY,WHETHER IN AN ACTION OF CONTRACT,TORT OR OTHERWISE,ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
**
** (end of license)
**
** This is part of the definition of the MD6 hash function.
** The files defining the MD6 hash function are:
**    md6.h
**    md6_compress.c
**    md6_mode.c
**
** The files defining the interface between MD6 and the NIST SHA-3
** API are:
**    md6_nist.h
**    md6_nist.c
** The NIST SHA-3 API is defined in:
**    http://www.csrc.nist.gov/groups/ST/hash/documents/SHA3-C-API.pdf
**
** See  http://groups.csail.mit.edu/cis/md6  for more information.
*/

#include <stdio.h>
#include "Fns_Md6.h"
#include "Fns_Md6_Nist.h"

#pragma warn(disable:2030)

int Md6_Init(Md6_HashState *state,int hashbitlen)
{
	int	err ;

	if ((err = md6_init((Md6_HashState *) state,hashbitlen)))
		return err ;

	state->hashbitlen = hashbitlen ;

	return MD6_SUCCESS ;
}

int Md6_Update(Md6_HashState *state,const BitSequence *data,DataLength databitlen)
{
	return md6_update((Md6_HashState *) state,(unsigned char *)data,(uint64_t) databitlen) ;
}

int Md6_Final(Md6_HashState *state,BitSequence *hashval)
{
	return md6_final((Md6_HashState *) state,(unsigned char *) hashval) ;
}

int Md6_Hash(int hashbitlen,const BitSequence *data,DataLength databitlen,BitSequence *hashval)
{
	int err ;
	Md6_HashState state ;

	if ((err = Md6_Init(&state,hashbitlen))) 
		return err ;

	if ((err = Md6_Update(&state,data,databitlen))) 
		return err ;

	return Md6_Final(&state,hashval) ;
}


