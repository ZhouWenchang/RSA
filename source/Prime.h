#ifndef __PRIME_H__
#define __PRIME_H__

#include "BigInt.h"





CBigInt RsaTrans(const CBigInt& N, const CBigInt& A, const CBigInt& B);


CBigInt ExtEuclid(const CBigInt& a, const CBigInt& b, CBigInt& x, CBigInt& y);
CBigInt CongruenceEquation(const CBigInt& a, const CBigInt& n);
__int64 CongruenceEquation64(__int64 a, __int64 n);
CBigInt ModularPower(const CBigInt& M, const CBigInt& E, const CBigInt& N);
CBigInt MontgomeryModularPower(const CBigInt& M, const CBigInt& E, const CBigInt& N);
bool MillerRabin(const CBigInt& n);
bool IsPrimeNumber(const CBigInt& n);
CBigInt GeneratePrime(int bits);
CBigInt GeneratePrime_v2(int bits);
CBigInt GeneratePrime_v3(int bits, int k);

#endif //__PRIME_H__
