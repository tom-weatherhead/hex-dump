/* hex-dump.c - 2022-10-07 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char * argv[]) {
  FILE * fp;
  const int inputSourceIsStdin = argc < 2;
  const int numBytesPerRow = 8;
  char buf[numBytesPerRow];
  unsigned long offset = 0;
  int i;
  
  if (inputSourceIsStdin) {
    fp = stdin;
  } else {
    fp = fopen(argv[1], "rb");
    
    if (fp == NULL) {
      fprintf(stderr, "Could not open file '%s'\n", argv[1]);
      
      return 1;
    }
  }
  
  while (!feof(fp)) {
    const int numBytesInThisChunk = fread(buf, 1, numBytesPerRow, fp);

    printf("%08lx    ", offset);
    
    for (i = 0; i < numBytesPerRow; ++i) {
      
      if (i < numBytesInThisChunk) {
        printf("%02x ", (unsigned int)(buf[i]));
      } else {
        printf("  ");
      }
    }
    
    printf("   ");
      
    for (i = 0; i < numBytesPerRow; ++i) {
      
      if (i < numBytesInThisChunk && isprint(buf[i])) {
        printf("%c", buf[i]);
      } else {
        printf(" ");
      }
    }
    
    printf("\n");
      
    offset += numBytesPerRow;
  }
  
  if (!inputSourceIsStdin) {
    fclose(fp);
  }
  
  return 0; /* Zero (as a Unix exit code) means success. */
}

/* **** The End **** */
