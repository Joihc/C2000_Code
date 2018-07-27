/*
 * EX.c
 *
 *  Created on: 2018��5��22��
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
    int flag = 1; //�жϷ���

    while (*str == ' '||*str == '0')  //�����ַ���ǰ��Ŀո�
    {
        str++;
    }

    if (*str == '-')  //��һ���ַ����ǡ�-����˵�������Ǹ���
    {
        flag = 0;
        str++;
    }
    else if (*str == '+') //��һ���ַ����ǡ�+����˵������������
    {
        flag = 1;
        str++;
    }//��һ���ַ������ǡ�+����-��Ҳ���������ַ���ֱ�ӷ���0

		while (*str == ' '||*str == '0')  //�����ַ���ǰ��Ŀո�
    {
        str++;
    }

    if (*str > '9' || *str < '0')
    {
        return 0;
    }

    //�������������ַ���������/0��ʱ������ת��
    while (*str != '#' && *str != '\0' && *str <= '9' && *str >= '0')
    {
        value = value * 10 + *str - 0x30; //�������ַ�תΪ��Ӧ��������
        str++;
    }

    if (flag == 0) //���������
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

