#pragma once

#include <Windows.h>

#pragma comment(lib, "str_mem")

#define INT_DIGITS	19

int nt_strlen( PCHAR pStr );

PCHAR nt_strcpy( PCHAR pDst , PCHAR pSrc );
PCHAR nt_strcat( PCHAR pDst , PCHAR pSrc );

PCHAR nt_itoa( int Value );

int nt_strcmp( PCHAR pStr1 , PCHAR pStr2 );
int nt_atoi( PCHAR pStr1 );

void nt_memset( PVOID pBuffer , DWORD dwLen , DWORD dwSym );
void nt_memcpy( PVOID pDst , PVOID pSrc , size_t Count );

DWORD FindPushString( DWORD dwStart , DWORD dwEnd , DWORD dwAddress );

DWORD FindPattern( PCHAR pPattern , PCHAR pszMask , DWORD dwStart , DWORD dwEnd , DWORD dwOffset );
DWORD FindPattern( PCHAR pPattern , DWORD dwPatternLen , DWORD dwStart , DWORD dwEnd , DWORD dwOffset );

float nt_sqrt( float x );
double nt_atan( double x , int n );
double nt_atan2( double y , double x );
double nt_powx( double a , int x );
double nt_fact( double x );
double nt_sin( double x );
double nt_cos( double x );
float nt_fabs( float x );