#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fi = fopen(argv[1], "r");
	FILE *fo = fopen(argv[2], "w");
	fprintf(fo, "This is a demo\n");
	fclose(fi); fclose(fo);
	return 0;
}
