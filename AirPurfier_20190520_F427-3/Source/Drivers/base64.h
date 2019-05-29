#ifndef __base64_H
#define __base64_H			  	 
int base64_encode(const unsigned char *in,  unsigned long len,unsigned char *out);
int base64_decode(const unsigned char *in, unsigned char *out);
#endif  
