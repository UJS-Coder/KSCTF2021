#include <cstdio>
#include <unistd.h>
#include<iostream>
#include <stdlib.h>
#include<string>
using namespace std;


int main() {
	string a = "FLAG[xorISeaSY]";
	for (size_t i = 0; i < a.length(); i++)
	{
		a[i] ^= 32; //对32取异或可以用来转换大小写
	}
	cout << a;

	return 0;
}