#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main()
{
    const EVP_MD *sm3_md;
    EVP_MD_CTX *sm3_ctx;
    unsigned char hash_value[64];
    int len;
    
    sm3_md = EVP_sm3(); 
    sm3_ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(sm3_ctx, sm3_md, NULL);

    EVP_DigestUpdate(sm3_ctx, "abc", 3);

    //EVP_DigestUpdate(sm3_ctx, "a", 1);
    //EVP_DigestUpdate(sm3_ctx, "b", 1);
    //EVP_DigestUpdate(sm3_ctx, "c", 1);

    //EVP_DigestUpdate(sm3_ctx, "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        "abcabcabc"\
    //        , 144);

    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);
    //EVP_DigestUpdate(sm3_ctx, "abcabcabc", 9);

    EVP_DigestFinal_ex(sm3_ctx, hash_value, &len);
    EVP_MD_CTX_free(sm3_ctx);
    
    printf("Digest: ");
    for (int i = 0; i < len; i++) {
        unsigned char high = (hash_value[i] >> 4 & 0xf);
        unsigned char low = (hash_value[i] & 0xf);
        printf("%x", high);
        printf("%x", low);
    }
    printf("\n");
    
    return 0;
}

