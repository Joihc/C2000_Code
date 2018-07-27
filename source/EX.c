/*
 * EX.c
 *
 *  Created on: 2018年5月22日
 *      Author: hgisw
 */

#include "EX.h"



int16 clamp(int16 cur,int16 min,int16 max)
{
	if(cur<min)
	{
		return min;
	}
	else if(cur>max)
	{
		return max;
	}
	return cur;
}
int16 my_atoi (char *str)
{
	  int value = 0;
    int flag = 1; //判断符号

    while (*str == ' '||*str == '0')  //跳过字符串前面的空格
    {
        str++;
    }

    if (*str == '-')  //第一个字符若是‘-’，说明可能是负数
    {
        flag = 0;
        str++;
    }
    else if (*str == '+') //第一个字符若是‘+’，说明可能是正数
    {
        flag = 1;
        str++;
    }//第一个字符若不是‘+’‘-’也不是数字字符，直接返回0

		while (*str == ' '||*str == '0')  //跳过字符串前面的空格
    {
        str++;
    }

    if (*str > '9' || *str < '0')
    {
        return 0;
    }

    //当遇到非数字字符或遇到‘/0’时，结束转化
    while (*str != '#' && *str != '\0' && *str <= '9' && *str >= '0')
    {
        value = value * 10 + *str - 0x30; //将数字字符转为对应的整形数
        str++;
    }

    if (flag == 0) //负数的情况
    {
        value = -value;
    }

    return value;
}
char *sstrncpy(char *dest, const char *src, size_t n)
{
    if (n == 0)
        return dest;

    dest[0] = 0;

    return strncat(dest, src, n - 1);
}

