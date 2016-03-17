#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<InstruM.h>

using namespace std;

int main()
{
  FILE* pFile;
  long lSize;
  //unsigned char* buffer;
  size_t result;
  InstruM* m = new InstruM();

  pFile = fopen ( "iimage.bin" , "rb" );
  if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell(pFile);
  rewind (pFile);

  cout << lSize << ' ';

  // allocate memory to contain the whole file:
  //buffer = (unsigned char*) malloc (sizeof(unsigned char)*lSize);
  //if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  // copy the file into the buffer:
  result = fread (m->InM,sizeof(unsigned char),lSize,pFile);

  cout <<lSize<< ' '<<result;
  if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

 cout << endl;
  for(int y=0; y<10; y++){
    printf("%x ",m->InM[y]);
  }
  /* the whole file is now loaded in the memory buffer. */

  // terminate
  //fclose (pFile);


  fclose(pFile);
//  free (buffer);
  return 0;




}
