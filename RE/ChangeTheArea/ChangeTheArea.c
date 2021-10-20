//gcc re1.c -o re -no-pie -z norelro -fvisibility=hidden -s
//tokameine

#include<stdio.h>
#include <string.h>
#include <stdint.h>  

#include <fcntl.h>
#include <stdbool.h>
#define DELTA 0x9e3779b9  
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))  
void btea(uint32_t* v, int n, uint32_t const key[4]);
int change(char* p, uint32_t* key);
char* base64_encode(const unsigned char* bindata, char* base64, int binlength);
int justachange()__attribute__((constructor));
int a_change(char* p,char* p2);
const char* base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned int *test1=a_change;
unsigned int *test2=strcmp;
int justachange()
{

	
	unsigned int *test3=0x602030;
	*test3=test1;
	
}

int a_change(char* p,char* p2)
{
	int k=0;
	for(int i=0;i<strlen(p)-1;i++)
	{
        if (k == 1)
        {
            p[i] += k;
            k--;
        }
        else
        {
            k++;
        }

	}

	for(int i=0;i<strlen(p);i++)
	{
		if(p[i]!=p2[i])
		{
			return 2;
		}
	}
	return 0;

}


int main()
{
	char buf[32];

	printf("Tell me flag:");
	scanf("%s", buf);
    unsigned int key[4] = { 0x28371234,0x19283543,0x19384721,0x98372612 };
    if (change(buf, key))
    {
        printf("Win");
    }
    else
    {
        printf("Error");
    }

}
void btea(uint32_t* v, int n, uint32_t const key[4])
{
    uint32_t y, z, sum;
    unsigned p, rounds, e;
    if (n > 1)            /* Coding Part */
    {
        rounds = 6 + 52 / n;
        sum = 0;
        z = v[n - 1];
        do
        {
            sum += DELTA;
            e = (sum >> 2) & 3;
            for (p = 0; p < n - 1; p++)
            {
                y = v[p + 1];
                z = v[p] += MX;
            }
            y = v[0];
            z = v[n - 1] += MX;
        } while (--rounds);
    }
    else if (n < -1)      /* Decoding Part */
    {
        n = -n;
        rounds = 6 + 52 / n;
        sum = rounds * DELTA;
        y = v[0];
        do
        {
            e = (sum >> 2) & 3;
            for (p = n - 1; p > 0; p--)
            {
                z = v[p - 1];
                y = v[p] -= MX;
            }
            z = v[n - 1];
            y = v[0] -= MX;
            sum -= DELTA;
        } while (--rounds);
    }
}

int change(char* p, uint32_t*key)
{
    unsigned int enc[8];
    unsigned char base[32];
    unsigned char baseend[45];

    int k = 0;
    for (int i = 0;i<32; i+=4)
    {
        enc[k] = p[i]*0x1000000 + p[i + 1] * 0x10000 + p[i + 2] * 0x100 + p[i + 3];
        k++;
    }
    k = 0;

    btea(enc, 8, (unsigned int*)key);

    k = 0;
    for (int i = 0; i < 32; i+=4)
    {
        
        base[i] = enc[k]&0xff;
        base[i+1] = (enc[k]&0xff00)/0x100;
        base[i+2] = (enc[k]&0xff0000)/0x10000;
        base[i+3] = (enc[k]&0xff000000)/0x1000000;
        k++;
    }
    base64_encode(base, baseend,32);


    int judge = false;
    judge = !strcmp(baseend, "kK+dstc7nbiy4v1kgsQxzPOXcTxpa,H:6rfBJnsNJTk=");

    return judge;
}





char* base64_encode(const unsigned char* bindata, char* base64, int binlength)
{
    int i, j;
    unsigned char current;

    for (i = 0, j = 0; i < binlength; i += 3)
    {
        current = (bindata[i] >> 2);
        current &= (unsigned char)0x3F;
        base64[j++] = base64char[(int)current];

        current = ((unsigned char)(bindata[i] << 4)) & ((unsigned char)0x30);
        if (i + 1 >= binlength)
        {
            base64[j++] = base64char[(int)current];
            base64[j++] = '=';
            base64[j++] = '=';
            break;
        }
        current |= ((unsigned char)(bindata[i + 1] >> 4)) & ((unsigned char)0x0F);
        base64[j++] = base64char[(int)current];

        current = ((unsigned char)(bindata[i + 1] << 2)) & ((unsigned char)0x3C);
        if (i + 2 >= binlength)
        {
            base64[j++] = base64char[(int)current];
            base64[j++] = '=';
            break;
        }
        current |= ((unsigned char)(bindata[i + 2] >> 6)) & ((unsigned char)0x03);
        base64[j++] = base64char[(int)current];

        current = ((unsigned char)bindata[i + 2]) & ((unsigned char)0x3F);
        base64[j++] = base64char[(int)current];
    }
    base64[j] = '\0';
    return base64;
}
