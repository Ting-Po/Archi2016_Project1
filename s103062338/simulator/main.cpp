#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<InstruM.h>

using namespace std;



int main()
{
    /*
    int endian = 0x01020304;
    char *ptr = (char *)&endian;
    for(int i=0 ; i<4 ; i++){
        printf("%d ", *ptr);
        ptr++;
    }
    */
    int PC=0;
    int InstruNum = 0;

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

  m->storetoIns();

  for(int y=0; y<10; y++){
    printf("%x ",m->InM[y]);
  }
  /* the whole file is now loaded in the memory buffer. */



   // terminate
  //fclose (pFile);


  PC |= m->InM[0];
  PC <<= 8;
  PC |= m->InM[1];
  PC <<= 8;
  PC |= m->InM[2];
  PC <<= 8;
  PC |= m->InM[3];

  InstruNum |= m->InM[4];
  InstruNum <<= 8;
  InstruNum |= m->InM[5];
  InstruNum <<= 8;
  InstruNum |= m->InM[6];
  InstruNum <<= 8;
  InstruNum |= m->InM[7];

  printf("\n%08x\n", PC);
  printf("%08x\n", InstruNum);

  printf("%08x\n", m->Ins[0]);


  fclose(pFile);
//  free (buffer);


    /*
   int i=0;
   while(i<PC){

       m->Ins;




        i++;
   }
    */
    printf("%08x",m->rtopcode(0));






  return 0;




}
