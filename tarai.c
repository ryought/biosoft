#include <stdio.h>
#include <stdlib.h>

int tarai(int x, int y, int z){ // Tarai function by Ikuo Takeuchi
  if(x <= y)
      return y;
  else
    return( tarai( tarai(x-1,y,z), tarai(y-1,z,x), tarai(z-1,x,y) ) );
}


int main(int argc, char* argv[]){

  printf("%d\n", tarai(atoi(argv[1]),atoi(argv[2]),atoi(argv[3])));
  return 0;
}
