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
    int cycle = 0;
    int i;



    FILE* pFile;
    long lSize;
    FILE* dFile;
    long dSize;
    FILE* snap;
  //unsigned char* buffer;
    size_t result;
    InstruM* m = new InstruM();
    Memory* n = new Memory();

  pFile = fopen ( "iimage.bin" , "rb" );
  dFile = fopen ( "dimage.bin" , "rb" );
  snap = fopen("snapshot.rpt" , "w");

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

  fread (&(m->InM)[PC],sizeof(unsigned char),lSize-8,pFile);
  fread (n->mem,sizeof(unsigned char),dSize-8,dFile);

  cout <<lSize<< ' '<<result;
  //if (result+64 != lSize) {fputs ("Reading error",stderr); exit (3);}

 cout << endl;

  m->storetoIns(PC);


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




//int i = PC+4;
Reg* reg = new Reg();
Function* func = new Function();


//func->add(m,i,reg,n);

reg->reg[29] = SP;

    printf("TTTT: %08x\n", m->rtopcode(PC) == 0x00);


   while((m->rtopcode(PC))!= 0x3F){

        fprintf(snap, "cycle %d\n",cycle);
        cycle++;
        for(i=0;i<32;i++){
            fprintf(snap, "$%02d: 0x%08X\n", i, reg->reg[i]);
        }
        fprintf(snap,"PC: 0x%08X\n\n\n", PC);




        if(m->rtopcode(PC) == 0x00){
            switch(m->rtfunct(PC)){
        case 0x20:
            func->add(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x21:
            func->addu(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x22:
            func->sub(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x24:
            func->And(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x25:
            func->Or(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x26:
            func->Xor(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x27:
            func->nor(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x28:
            func->nand(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x2A:
            func->slt(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x00:
            func->sll(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x05:
            func->srl(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x03:
            func->sra(m,PC,reg);
            PC = PC + 4;
            break;
        case 0x08:
            PC = reg->reg[m->rtrs(PC)];
            break;
        default:
                PC = PC + 4;
                break;
            }
        }else{
            switch(m->rtopcode(PC)){
            case 0x08:{
                func->addi(m,PC,reg);
                PC = PC + 4;
                break;
            }
            case 0x09:
                func->addiu(m,PC,reg);
                PC = PC + 4;
                break;
            case 0x23:
                func->lw(m,PC,reg,n);
                PC = PC + 4;
                break;
            case 0x21:
                func->lh(m,PC,reg,n);
                PC = PC + 4;
                break;
            case 0x25:
                func->lhu(m,PC,reg,n);
                PC = PC + 4;
                break;
            case 0x20:
                func->lb(m,PC,reg,n);
                PC = PC + 4;
                break;
            case 0x24:
                func->lbu(m,PC,reg,n);
                PC = PC + 4;
                break;
            case 0x2B:
                func->sw(m,PC,reg,n);
                PC = PC + 4;
                break;
            case 0x29:
                func->sh(m,PC,reg,n);
                PC = PC + 4;
                break;
            case 0x28:
                func->sb(m,PC,reg,n);
                PC = PC + 4;
                break;
            case 0x0F:
                func->lui(m,PC,reg,n);
                PC = PC + 4;
                break;
            case 0x0C:
                func->andi(m,PC,reg);
                PC = PC + 4;
                break;
            case 0x0D:
                func->ori(m,PC,reg);
                PC = PC + 4;
                break;
            case 0x0E:
                func->nori(m,PC, reg);
                PC = PC + 4;
                break;
            case 0x0A:
                func->slti(m,PC, reg);
                PC = PC + 4;
                break;
            case 0x04:
                PC = func->beq(m,PC, reg);
                break;
            case 0x05:
                PC = func->bne(m,PC, reg);
                break;
            case 0x07:
                PC = func->bgtz(m,PC,reg);
                break;
            case 0x02:
                PC = func->j(m,PC,reg);
                break;
            case 0x03:
                PC = func->jal(m,PC,reg);
                break;
            default:
                PC = PC +4;
                break;
            }

        }






   }
    fprintf(snap, "cycle %d\n",cycle);
        cycle++;
        for(i=0;i<32;i++){
            fprintf(snap, "$%02d: 0x%08X\n", i, reg->reg[i]);
        }
        fprintf(snap,"PC: 0x%08X\n\n\n", PC);




    unsigned short aa = 0xFFFF;
    unsigned int a = 0xF1234567;
    unsigned int b;
    b =aa;
    unsigned char a1,a2,a3,a4;
    a1 = a;
    a=a>>8;
    a2 = a;
    a = a>>8;
    a3 = a;
    a =a>>8;
    a4 =a;

    unsigned int aaa = 0xFFFFFFFF;
    int bbb = 0xFFFFFFFF;
    printf("%08x\n",a1);
    printf("%08x\n",a2);
    printf("%08x\n",a3);
    printf("%08x\n",a4);
    printf("%08x\n",b);
    printf("%08x\n",aaa>>28);
    printf("%08x\n",bbb>>28);

    fclose(snap);

  return 0;




}
