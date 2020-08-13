#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "jsmn.h"

#define INPUT_FILE "input.json"
#define MAX_TOKENS 128
int main()
{
	FILE *fp = fopen(INPUT_FILE, "r");
	assert(fp);
	unsigned long flen = 0;
	char *buf;

	// Determine file length, allocate buffer
	fseek(fp, 0, SEEK_END);
	flen = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buf = (char *) malloc(flen + 1);
	memset(buf, 0, flen+1);
	// Null-terminate buffer
	buf[flen] = '\0';
	// Read file
	fread(buf, 1, flen, fp);
	fclose(fp);
	printf("File length: %lu\n", flen);

	// jsmn the file input
	jsmn_parser p;
	jsmntok_t t[MAX_TOKENS];
	jsmn_init(&p);
	int r = jsmn_parse(&p, buf, strlen(buf), t, MAX_TOKENS);
	
	// Assume top-level element is an object
	if (r < 0) {
		printf("Failed to parse JSON: %d\n", r);
		return 1;
	}
	if (r < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		return 1;
	}
	// Iterate through tokens
	for (int i = 1; i < r; ++i) {
		if (t[i].size == 0) continue;
		//printf("Size: %lu, start: %lu, end: %lu\n", t[i].size, t[i].start, t[i].end);
		printf("%.*s", t[i].end - t[i].start, buf + t[i].start);
		printf(": %.*s\n", t[i+1].end - t[i+1].start, buf + t[i+1].start);
	}	
	
	// Free memory
	free(buf);
			
	return 0;
}
