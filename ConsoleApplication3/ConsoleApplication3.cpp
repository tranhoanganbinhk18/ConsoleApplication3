//#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#define MAXDIGITS 100
#define PLUS 1
#define MINUS -1
using namespace std;
typedef struct
{
	char digits[MAXDIGITS];
	int signbit;
	int lastdigit;

} bignum;
void main();
void print_bignum(bignum n);//
int kiemtra(char s[]);
void scan_bignum(bignum &n);
void zero_justify(bignum n);//
void add_bignum(bignum a, bignum b, bignum& c);//
void subtract_bignum(bignum a, bignum b, bignum& c);//
int max(int a, int b);//
int compare_bignum(bignum a, bignum b);//
void digit_shift(bignum& n, int d);//
void multiply_bignum(bignum a, bignum b, bignum& c);//
void initialize_bignum(bignum& n);//
void int_to_bignum(int s, bignum& n);//
void divide_bignum(bignum a, bignum b, bignum &c);//
void string_to_bignum(string s, bignum& n);
void delete_0(bignum& a);
// cai 
void main()
{
	do {
		bignum a,b,the;
		scan_bignum(a);
		scan_bignum(b);
		subtract_bignum(a, b, the);
		
		print_bignum(the);
	} while (_getch() != 27);
}
void delete_0(bignum &a)
{
	a.signbit = a.signbit;
	while (a.digits[a.lastdigit] == 0)
	{
		a.lastdigit = a.lastdigit - 1;
	}
}
void string_to_bignum(string s, bignum &n) {
	n.signbit = PLUS; // TODO: currently no negative numbers

	for (int i = 0; i < MAXDIGITS; i++) n.digits[i] = (char)0;

	n.lastdigit = -1;

	for (int i = s.size() - 1; i >= 0; i--) {
		n.lastdigit++;
		n.digits[n.lastdigit] = s[i] - 48;
	}

	if (s == "0") n.lastdigit = 0;
}
int max(int a, int b)
{
	return (a > b) ? a : b;
}
void print_bignum(bignum n)
{
	int i;
	if (n.signbit == MINUS) cout << "-";
	if (n.lastdigit == -1 )
		cout << '0';
	else
	for (i = n.lastdigit; i >= 0; i--)
	{
		cout << int(n.digits[i]);
	}
	
}
int kiemtra(char s[])
{
	if (s[0] != '-' && !isdigit(s[0]))
		return 0;
	int len = strlen(s);
	for (int i = 1; i < len; i++)
		if (!isdigit(s[i])) return 0;
	return 1;
}
void scan_bignum(bignum& n)
{
	char temp[256];
	cin.getline(temp, 256);
	if (!kiemtra(temp))
	{	
		n.signbit = PLUS;
		n.lastdigit = 0;
		n.digits[0] = 0;
	}
	else
	{	
		if (temp[0] != '-')
		{	
			n.signbit = PLUS;
			n.lastdigit = strlen(temp) - 1;
			for (int i = 0; i <= n.lastdigit; i++)
				n.digits[i] = temp[n.lastdigit - i] - 48;
		}
		else
		{	
			n.signbit = MINUS;
			n.lastdigit = strlen(temp) - 2;
			for (int i = 0; i <= n.lastdigit; i++)
				n.digits[i] = temp[n.lastdigit + 1 - i] - 48;
		}
	}
}
void zero_justify(bignum n)
{
	while ((n.lastdigit > 0) && (n.digits[n.lastdigit] == 0))
		n.lastdigit--;
	if ((n.lastdigit == 0) && (n.digits[0] == 0))
		n.signbit = PLUS; 
}
void add_bignum(bignum a, bignum b, bignum&c)
{
	int carry; 
	int i; 
	if (a.signbit == b.signbit) c.signbit = a.signbit;
	else
	{
		if (a.signbit == MINUS)
		{
			a.signbit = PLUS;
			subtract_bignum(b, a, c);
			a.signbit = MINUS;
		}
		else
		{
			b.signbit = PLUS;
			subtract_bignum(a, b, c);
			b.signbit = MINUS;
		}
		return;
	}
	c.lastdigit = max(a.lastdigit, b.lastdigit) + 1;
	for (i = a.lastdigit + 1; i <= c.lastdigit; i++)
		a.digits[i] = 0;
	for (i = b.lastdigit + 1; i <= c.lastdigit; i++)
		b.digits[i] = 0;
	carry = 0;
	for (i = 0; i <= (c.lastdigit); i++)
	{
		c.digits[i] = (char)
			(carry + a.digits[i] + b.digits[i]) % 10;
		carry = (carry + a.digits[i] + b.digits[i]) / 10;
	}
	
	zero_justify(c);
	delete_0(c);
}
void subtract_bignum(bignum a, bignum b, bignum& c)
{

	int borrow; /* anything borrowed? */
	int v; /* placeholder digit */
	int i; /* counter */
	if ((a.signbit == MINUS) || (b.signbit == MINUS)) {
		b.signbit = -1 * b.signbit;
		add_bignum(a, b, c);
		b.signbit = -1 * b.signbit;
		return;
	}
	if (compare_bignum(a, b) == PLUS) {
		subtract_bignum(b, a, c);
		c.signbit = MINUS;
		return;
	}
	c.signbit = PLUS;
	c.lastdigit = max(a.lastdigit, b.lastdigit);
	for (i = a.lastdigit + 1; i <= c.lastdigit; i++)
		a.digits[i] = 0;
	for (i = b.lastdigit + 1; i <= c.lastdigit; i++)
		b.digits[i] = 0;
	borrow = 0;

	for (i = 0; i <= (c.lastdigit); i++) {
		v = (a.digits[i] - borrow - b.digits[i]);
		if (a.digits[i] > 0)
			borrow = 0;
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}
		c.digits[i] = (char)v % 10;
	}
	zero_justify(c);
	delete_0(c);
}
int compare_bignum(bignum a, bignum b)
{
	int i; 
	if ((a.signbit == MINUS) && (b.signbit == PLUS)) return(PLUS);
	if ((a.signbit == PLUS) && (b.signbit == MINUS)) return(MINUS);
	if (b.lastdigit > a.lastdigit) return (PLUS * a.signbit);
	if (a.lastdigit > b.lastdigit) return (MINUS * a.signbit);
	for (i = a.lastdigit; i >= 0; i--) {   
		if (a.digits[i] > b.digits[i])
			return(MINUS * a.signbit);
		if (b.digits[i] > a.digits[i])
			return(PLUS * a.signbit);
	}
	return(0);
}
void initialize_bignum(bignum &n)
{
	int_to_bignum(0, n);
}
void multiply_bignum(bignum a, bignum b, bignum &c)
{
	bignum row; /* represent shifted row */
	bignum tmp; /* placeholder bignum */
	int i, j; /* counters */
	initialize_bignum(c);
	row = a;
	for (i = 0; i <= b.lastdigit; i++) {
		for (j = 1; j <= b.digits[i]; j++) {
			add_bignum(c, row, tmp);
			c = tmp;
		}
		digit_shift(row, 1);
	}
	c.signbit = a.signbit * b.signbit;
	zero_justify(c);
	delete_0(a);
}
void digit_shift(bignum &n, int d) 
{
	int i; /* counter */
	if ((n.lastdigit == 0) && (n.digits[0] == 0)) return;
	for (i = n.lastdigit; i >= 0; i--)
		n.digits[i + d] = n.digits[i];
	for (i = 0; i < d; i++) n.digits[i] = 0;
		n.lastdigit = n.lastdigit + d;
}
void int_to_bignum(int s, bignum &n)
{
	int i;				/* counter */
	int t;				/* int to work with */

	if (s >= 0) n.signbit = PLUS;
	else n.signbit = MINUS;
	for (i = 0; i < MAXDIGITS; i++) n.digits[i] = (char)0;
	n.lastdigit = -1;
	t = abs(s);
	while (t > 0) {
		n.lastdigit++;
		n.digits[n.lastdigit] = (t % 10);
		t = t / 10;
	}

	if (s == 0) n.lastdigit = 0;
}
void divide_bignum(bignum a, bignum b, bignum &c)
{
	c.signbit = a.signbit * b.signbit;
	bignum dem, tam;
	if (a.signbit < 0)
		a.signbit = a.signbit *-1;
	if (b.signbit < 0)
		b.signbit = b.signbit *-1;
	dem.digits[0] = 1;
	dem.lastdigit = 0;
	dem.signbit = 1;
	tam.digits[0] = 0;
	tam.lastdigit = 0;
	tam.signbit = 1;
	int g = 1;
	while (g == 1 )
	{
		add_bignum(tam, dem, tam);
		subtract_bignum(a, b, a);
		g = a.signbit;
	}
	subtract_bignum(tam, dem, tam);
	for (int i = 0; i <= tam.lastdigit; i++)
		c.digits[i] = tam.digits[i];
	c.lastdigit = tam.lastdigit;
	delete_0(c);
	
	
}


