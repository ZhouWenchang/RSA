#include "stdafx.h"
#include "RsaLib.h"
#include "MD5Hash.h"
#include "Prime.h"


#define PKCS_PAD_LEN          11
#define PKCS_PAD_STRING_LEN   8

static void GeneratePkcsPad(int t, char *pad, int padSize)
{
    if(t == 0)
    {
        memset(pad, 0x00, padSize);
    }
    else if(t == 1)
    {
        memset(pad, 0xFF, padSize);
    }
    else
    {
        for(int i = 0; i < padSize; i++)
        {
            pad[i] = rand() % 0xFF;
        }
    }
}

static int Rsa_Pkcs15_Encrypt_Block(CBigInt& e, CBigInt& n, int kbits,
                                    void *pSrcBlock, int srcSize, CBigInt& c)
{
    int k = kbits / 8;
    int pad_len = k - srcSize - 3;

    char *padBlock = new char[k];
    if(padBlock == NULL)
        return -1;

    padBlock[0] = 0x00;
    padBlock[1] = 0x02;
    GeneratePkcsPad(2, padBlock + 2, pad_len);
    padBlock[pad_len + 2] = 0x00;
    memcpy(padBlock + k - srcSize, pSrcBlock, srcSize);
    CBigInt em;
    em.GetFromData(padBlock, k);
    c = MontgomeryModularPower(em, e, n);

    delete[] padBlock;

    return k;
}

static int Rsa_Pkcs15_Decrypt_Block(CBigInt& d, CBigInt& n, int kbits,
                                    CBigInt& c, void *pDecBlock, int blockSize)
{
    char *padBlock = new char[kbits / 8];
    if(padBlock == NULL)
        return -1;

    CBigInt em = MontgomeryModularPower(c, d, n);
    int dataSize = em.PutToData(padBlock, kbits / 8);
    int pad_len = 2;
    for(int i = 2; i < dataSize; i++)
    {
        pad_len++;
        if(padBlock[i] == 0)
            break;
    }
    memcpy(pDecBlock, padBlock + pad_len, dataSize - pad_len);
    delete[] padBlock;

    return dataSize - pad_len;
}

int Rsa_Pkcs15_Encrypt(CBigInt& e, CBigInt& n, int kbits,
                       void *pSrcData, int dataSize, void *pEncData, int encBufSize)
{
    if(dataSize > (kbits / 8 - PKCS_PAD_LEN))
        return -1;

    CBigInt c;
    int encSize = Rsa_Pkcs15_Encrypt_Block(e, n, kbits, pSrcData, dataSize, c);
    if(encSize > 0)
    {
        if(encSize > encBufSize)
            return -1;
        c.PutToData((char *)pEncData, encSize);
    }

    return encSize;
}

int Rsa_Pkcs15_Decrypt(CBigInt& d, CBigInt& n, int kbits,
                       void *pSrcData, int dataSize, void *pDecData, int decBufSize)
{
    int total = 0;

    if((dataSize % (kbits / 8)) != 0)
        return -1;

    CBigInt c;
    c.GetFromData((const char *)pSrcData, dataSize);
    return Rsa_Pkcs15_Decrypt_Block(d, n, kbits, c, pDecData, decBufSize);
}

const int Md5SignPadSize = 18;
unsigned char Md5SignPadding[] = { 0x30, 0x20, 0x30, 0x0c, 0x06, 0x08,
                                   0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d,
                                   0x02, 0x05, 0x05, 0x00, 0x04, 0x10 };

