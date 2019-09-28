#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#pragma warning(disable:4996)
using namespace std;
int sd[90][90], siz, gl, gw, time, da[10][90][90];
bool judge(int x, int y, int num)
{
	int i, j, t = 0, x1, y1;
	if (gl != 0)
		x1 = x / gl, y1 = y / gw;
	if (sd[x][y] == 0)
	{
		for (i = 0; i < siz; i++)
			if (sd[x][i] == num || sd[i][y] == num)
				return 0;
		if (gl != 0)
		{
			for (i = x1 * gl; i < x1*gl + gl; i++)
				for (j = y1 * gw; j < y1*gw + gw; j++)
					if (sd[i][j] == num)
						return 0;
		}
		return 1;
	}
	else
		return 0;
}
void single()
{
	int i, j, k, l, m, t = 0, x0 = 0, y0 = 0, flag, p = 1;;
	while (1)
	{
		flag = 0;
		for (i = 1; i <= siz; i++)
		{
			for (j = 0; j < siz; j++)
			{
				t = 0; x0 = 0; y0 = 0;
				for (k = 0; k < siz; k++)
				{
					t = t + judge(j, k, i);
					if (judge(j, k, i))
						x0 = j, y0 = k;
				}
				if (t == 1)
				{
					sd[x0][y0] = i;
					flag++;
				}
				t = 0; x0 = 0; y0 = 0;
				for (k = 0; k < siz; k++)
				{
					t = t + judge(k, j, i);
					if (judge(k, j, i))
						x0 = k, y0 = j;
				}
				if (t == 1)
				{
					sd[x0][y0] = i;
					flag++;
				}
			}
			if (gl != 0)
			{
				for (j = 0; j < gl; j++)
				{
					for (k = 0; k < gw; k++)
					{
						t = 0; x0 = 0; y0 = 0;
						for (l = gl * j; l < gl*j + gl; l++)
							for (m = gw * k; m < gw*k + gw; m++)
							{
								t = t + judge(l, m, i);
								if (judge(l, m, i))
									x0 = l, y0 = m;
							}
						if (t == 1)
						{
							sd[x0][y0] = i;
							flag++;
						}
					}
				}
			}
		}
		if (flag == 0)
			break;
	}
}
int find(int s)
{
	int x = s / siz, y = s % siz, n;
	if (s > siz*siz - 1)
		return 1;

	if (sd[x][y] != 0)
		return (find(s + 1));
	else
	{
		for (n = 1; n <= siz; n++)
		{
			if (judge(x, y, n))
			{
				sd[x][y] = n;
				if (find(s + 1))
					return 1;
			}
			sd[x][y] = 0;
		}
	}
	return 0;
}
int main(int argc, char *argv[])
{
	FILE* fp;
	int i, j, k,t = 0, x0 = 0, y0 = 0;
	char *x;
	char *y; 
	for (i = 0; i < argc; i++)//参数读取 
	{
		if (strlen(argv[i]) == 1)
		{
			if (i == 2)
				siz = atoi(argv[i]);//读取规格 
			if (i == 4)
				time = atoi(argv[i]);//读取数独个数 
		}
		if(i==6)
			x=argv[i];
		if(i==8)
			y=argv[i];
	}
	if (siz % 3 == 0)//宫的规格的转化 
	{
		gl = siz / 3;
		if (gl != 0)
			gw = siz / gl;
	}
	if (siz % 2 == 0)
	{
		gl = siz / 2;
		if (gl != 0)
			gw = siz / gl;
	}
	if(siz==6)
		gl=2,gw=3;
	if(argc!=9) 
	{
		cout<<"总参数错误";
		return 0;	
	}
	else
	{
		if(siz>9||siz<3)
		{
			cout<<"规格参数错误";
			return 0;	
		}
	}
	fp = fopen(x, "r");//文件读取 
	if (fp == NULL) //为空时返回错误 
		return -1;
	for (k = 0; k < time; k++)
	{
		i = 0; j = 0;
		while (i != siz) //将每一个数独划开 
		{
			fscanf(fp, "%d", &sd[i][j]);
			j++;
			if (j == siz)
			{
				j = 0;
				i++;
			}
		}
		single();
		t = find(0);
		for (i = 0; i < siz; i++)
			for (j = 0; j < siz; j++)
				da[k][i][j] = sd[i][j];//解决后存入da三维数组 
	}
	fclose(fp);
	fp = fopen(y, "w");
	if (fp == NULL)
		return -1;
	for (k = 0; k < time; k++)
	{
		for (i = 0; i < siz; i++)
		{
			for (j = 0; j < siz; j++)
			{
				fprintf(fp, "%d", da[k][i][j]);//依次递交 
				if (j != siz - 1)
					fprintf(fp, " ");
			}
			if (i != siz - 1)
				fprintf(fp, "\n");
		}
		if (k != time - 1)
			fprintf(fp, "\n\n");
	}
	fclose(fp);
	for(k=0;k<time;k++)//容错性 
	{
		for(i=0;i<siz;i++)
			for(j=0;j<siz;j++)
				if(da[k][i][j]==0)
					cout<<"数独错误"; 
	}
	return 0;
}
