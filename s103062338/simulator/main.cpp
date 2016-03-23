#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<InstruM.h>
#include<Memory.h>
#include<Reg.h>
#include<Function.h>

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
    int SP=0;
    int MemNum = 0;



    FILE* pFile;
    long lSize;
    FILE* dFile;
    long dSize;
  //unsigned char* buffer;
    size_t result;
    InstruM* m = new InstruM();
    Memory* n = new Memory();

  pFile = fopen ( "iimage.bin" , "rb" );
  dFile = fopen ( "dimage.bin" , "rb" );
  if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell(pFile);
  rewind (pFile);

  fseek (dFile , 0 , SEEK_END);
  dSize = ftell(dFile);
  rewind (dFile);


  cout << lSize << ' ';

  // allocate memory to contain the whole file:
  //buffer = (unsigned char*) malloc (sizeof(unsigned char)*lSize);
  //if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  // copy the file into the buffer:
  result = fread (m->pc_instrunum,sizeof(unsigned char),8,pFile);
  fread (n->sp_memnum,sizeof(unsigned char),8,dFile);

  PC |= m->pc_instrunum[0];
  PC <<= 8;
  PC |= m->pc_instrunum[1];
  PC <<= 8;
  PC |= m->pc_instrunum[2];
  PC <<= 8;
  PC |= m->pc_instrunum[3];

  InstruNum |= m->pc_instrunum[4];
  InstruNum <<= 8;
  InstruNum |= m->pc_instrunum[5];
  InstruNum <<= 8;
  InstruNum |= m->pc_instrunum[6];
  InstruNum <<= 8;
  InstruNum |= m->pc_instrunum[7];

  SP |= n->sp_memnum[0];
  SP <<= 8;
  SP |= n->sp_memnum[1];
  SP <<= 8;
  SP |= n->sp_memnum[2];
  SP <<= 8;
  SP |= n->sp_memnum[3];

  MemNum |= n->sp_memnum[4];
  MemNum <<= 8;
  MemNum |= n->sp_memnum[5];
  MemNum <<= 8;
  MemNum |= n->sp_memnum[6];
  MemNum <<= 8;
  MemNum |= n->sp_memnum[7];

  fread (&(m->InM)[PC+4],sizeof(unsigned char),lSize-8,pFile);
  fread (n->mem,sizeof(unsigned char),dSize-8,dFile);

  cout <<lSize<< ' '<<result;
  if (result+64 != lSize) {fputs ("Reading error",stderr); exit (3);}

 cout << endl;

  m->storetoIns(PC+4);


  printf("%d\n", dSize);
  printf("%d\n", MemNum);

  for(int y=0; y<10; y++){
    printf("%04x\n",n->mem[y]);
  }
  /* the whole file is now loaded in the memory buffer. */



   // terminate
  //fclose (pFile);




  printf("\n%d\n", PC);
  printf("%08x\n", InstruNum);

  printf("%08x\n", m->Ins[0]);

printf("%Test\n");
   printf("%08x\n", m->rtopcode(PC+4));
    printf("%08x\n", m->rtrs(PC+4));
     printf("%08x\n", m->rtrt(PC+4));
      printf("%08x\n", m->rtrd(PC+4));
       printf("%08x\n", m->rtshamt(PC+4));
        printf("%08x\n", m->rtfunct(PC+4));
         printf("%08x\n", m->rtaddress(PC+4));
           printf("%08x\n", m->rtimmediate(PC+4));


  fclose(pFile);
  fclose(dFile);
//  free (buffer);




int i = PC+4;
Reg* reg = new Reg();
Function* func = new Function();


func->add(m,i,reg,n);


   while((m->rtopcode(i))!= 0x3F){

        if(m->rtopcode(i) == 0x00){
            switch(m->rtfunct(i)){
        case 0x20:
            func->add(m,i,reg,n);
        case 0x21:

        case 0x22:

        case 0x24:

        case 0x25:

        case 0x26:

        case 0x27:

        case 0x28:

        case 0x2A:

        case 0x00:

        case 0x05:

        case 0x03:

        case 0x08:

        default:
                ;
            }
        }else{
            switch(m->rtopcode(i)){
            case 0x08:

            case 0x089:

            case 0x23:

            case 0x21:

            case 0x25:

            case 0x20:

            case 0x24:

            case 0x2B:

            case 0x29:

            case 0x28:

            case 0x0F:

            case 0x0C:

            case 0x0D:

            case 0x0E:

            case 0x0A:

            case 0x04:

            case 0x05:

            case 0x07:

            case 0x02:

            case 0x03:

            default:
                ;
            }

        }






        printf("Cycle: %d\n", i );



        i+=4;
   }






  return 0;




}
