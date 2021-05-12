#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <openssl/sha.h>  
   
static const char hex_chars[] = "0123456789abcdef";  
   
void convert_hex(unsigned char* md, unsigned char* mdstr) {  
    int i;  
    int j = 0;  
    unsigned int c;  
   
    for (i = 0; i < 20; i++) {  
        c = (md[i] >> 4) & 0x0f;  
        mdstr[j++] = hex_chars[c];  
        mdstr[j++] = hex_chars[md[i] & 0x0f];  
    }  
    mdstr[40] = '\0';  
}
 
int main() { 
    SHA_CTX shactx;  
    char data[] = "This is the text to be hashed";  
    char md[SHA_DIGEST_LENGTH];  
    char mdstr[40];  
    printf("strlen data : %ld\n", strlen(data));
  
    /* whole data */
    SHA1_Init(&shactx);  
    SHA1_Update(&shactx, data, strlen(data));
    SHA1_Final(md, &shactx);  
    convert_hex(md, mdstr);  
    printf ("Result of SHA1 : %s\n", mdstr);  

    /* segments */
    SHA1_Init(&shactx);  
    SHA1_Update(&shactx, data, 6);  
    SHA1_Update(&shactx, data+6, 6);  
    SHA1_Update(&shactx, data+6+6, strlen(data)-6-6);
    SHA1_Final(md, &shactx);  
    convert_hex(md, mdstr);  
    printf ("Result of SHA1 : %s\n", mdstr);  
    return 0;  
}  

