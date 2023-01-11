#pragma once
#include "BigInt.h"
#include <iostream>
#include <time.h>
#include <ctime>
#include <fstream>
#include <bitset>
#include <string>
using namespace std;


struct Rsa
{
    BigInt n, e, d; // e为公钥，d为私钥
    Rsa();
    Rsa(BigInt& N, BigInt& E);
    Rsa(BigInt& N, BigInt& E, BigInt& D);
};

void SortPrime(BigInt &n);
bool RabinMiller(const BigInt &n);
BigInt GeneratePrime();
BigInt Gcd(const BigInt &m, const BigInt &n);
BigInt ExtendedGcd(const BigInt &a, const BigInt &b, BigInt &x, BigInt &y);
BigInt StringToBigInt(string str);
string BigIntToString(BigInt num);
string BigIntToHex(BigInt &num);
BigInt HexToBigInt(string hex);

