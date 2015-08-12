/*
 * =====================================================================================
 *
 *       Filename:  kmp.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015/05/20 20时40分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

void generatePrefixFunc(char *pattern, int *prefix, int length) {
	prefix[0]=0;
	for(int i=1;i<length;++i) {
		if(pattern[i] == pattern[prefix[i-1]]) {
			prefix[i] = prefix[i-1]+1;
		} else {
			prefix[i] = 0;
		}
	}
}

int kmp(char *pattern, char *text) {
	int m = strlen(pattern);
	int n = strlen(text);

	if(n < m) return -1;

	int *prefix = (int *)malloc(sizeof(int)*m);
	generatePrefixFunc(pattern, prefix, m);

	int i=0,j=0;
	int index = -1;
	for(;i<n;++i) {
		while(j>0 && pattern[j] != text[i]) {
			j = prefix[j-1];
		}

		if(pattern[j] == text[i]) {
			j++;
			if(j == m) {
				index = i-m+1;
				goto end;
			}
		}
	}

end:
	free(prefix);
	return index;
}

void testPrefixFunc(char *pattern) {
	int length = strlen(pattern);
	int *prefix = (int *)malloc(sizeof(int)*length);
	generatePrefixFunc(pattern, prefix, length);
	printf("%s\n", pattern);
	for(int i=0;i<length;++i) {
		printf("%d ", prefix[i]);
	}
	printf("\n");
	free(prefix);
}

void testKmp(char *pattern, char *text) {
	
	printf("%s %s %d\n", pattern, text, kmp(pattern, text));
}

int
main() {
	testPrefixFunc("bbbbbbaa");
	testKmp("bbbbbbaa", "abbabaaaabbbaabaabaabbbaaabaaaaaabbbabbaabbabaabbabaaaaababbabbaaaaabbbbaaabbaaabbbbabbbbaaabbaaaaababbaababbabaaabaabbbbbbbaabaabaabbbbababbbababbaaababbbabaabbaaabbbba");
	/*  
	testKmp("", "");
	testKmp("", "dsf");
	testKmp("fd","fd");
	testKmp("ab", "acaabab");
	testKmp("aab", "acaabab");
	testKmp("a", "acaabab");
	testKmp("ababa", "ababcabcababababababmp");
	*/
}
