#include <stdio.h>
#include <stdbool.h>

int main(){
  printf("give the name of a text file\n");
  FILE * fp;
  char str[128];
  if(scanf("%127s", str) != 1)
    printf("Malformed input\n"); // shouldn't get this but here anyways
  fp = fopen(str, "r"); // read designated file
  if(!fp)
    printf("invalid file");
  char c;
  bool b;
  while(fscanf(fp, "%c", &c) != EOF){
    if(c == ' '){
      b = 0;
      printf("%d", b);
    }
    else if(c == '\n')
      printf("\n");
    else if(c != ' '){
      b = 1;
      printf("%d", b);
    }
  }
  fclose(fp);
  return 0;
}
