#include<stdio.h>
#include<string.h>
#include"match.h"

void PatternMatch()
{
	char s1[] = "ababcabcacbab", s2[] = "abcac";
	printf("%d\n", index(s1, s2));
	printf("%d\n", KMP(s1, s2));

	
}
void getNext(char s[], int next[])
{
	int i = 0, j = -1;
	next[0] = -1;
	while (i < strlen(s)-1)
	{
		if (j == -1 || s[i] == s[j])
			next[++i] = ++j;
		else
			j = next[j];
	}
}

int KMP(char s1[], char s2[])
{
	int i = 0, j = 0;
	int len1 = strlen(s1), len2 = strlen(s2);
	int next[50];
	getNext(s2, next);
	while (i < len1 && j < len2)
	{
		if (j == -1 || s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j == len2)
		return i - j;
	else
		return -1;
	
}
int index(char s1[], char s2[])
{
	int i = 0, j = 0;
	while (s1[i] != '\0'&&s2[j] != '\0')
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == strlen(s2))
		return i - j;
	else
		return -1;
}