#include <stdio.h>;
#include <conio.h>;
#define NOTHING 0xFFFFFFFF;
#define ENDOFFILE 0x3;
void main(void) {

	char writemode[] = "wb";	
	char readmode[] = "rb";
	char filename[] = "H:\\ASM\\encrypteddata.txt";
	char filename2[] = "H:\\ASM\\datarecieved.txt";
	char pname[] = "COM1";
	char pa[] = "H:\\ASM\\alphabet.txt";
	char c1a[] = "H:\\ASM\\cipher1.txt";
	char fileerror[] = "Error finding file!\n";
	char porterror[] = "Error opening port!\n";
	char listening[] = "Listening on COM Port 1..\n";
	char endmessage[] = "Press any key to exit:\n";
	char retreiving[] = "\b\b\b\b\b\b\b\b\b\b\b\b\bRetreiving...";
	char retreiving2[] = "\b\b\b\b\b\b\b\b\b\b\b\b\bRetreiving.. ";
	char retreiving3[] = "\b\b\b\b\b\b\b\b\b\b\b\b\bRetreiving.  ";
	char done[] = "\n..Done.\n";
	char decrypting[] = "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bDecrypting file...";
	char decrypting2[] = "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bDecrypting file.. ";
	char decrypting3[] = "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bDecrypting file.  ";
	int loadcounter;
	int loadcycle1 = 100;
	int loadcycle2 = 200;
	int loadcycle3 = 300;
	int loadcycle4 = 400;

	FILE * fileptr; //Message to be sent
	FILE * portptr; //Encoded message
	FILE * fileptr3; //Plaintext alphabet
	FILE * fileptr4; //Cipher alphabet
	FILE * fileptr5; //Receiving
	FILE * fileptr6; //Decoding

		__asm {

			/* open message file */
			lea eax, writemode
			push eax
			lea eax, filename
			push eax
			call dword ptr(fopen)
			add esp, 8
			or eax, eax
			jnz fileOK

			lea eax, fileerror
			push eax
			call dword ptr(printf)
			add esp, 4
			jmp endit


fileOK:		mov dword ptr(fileptr), eax

			/* open the port */
			lea eax, readmode
			push eax
			lea eax, pname
			push eax
			call dword ptr(fopen)
			add esp, 8
			or eax, eax
			jnz portOK
			
			lea eax, porterror
			push eax
			call dword ptr(printf)
			add esp, 4

			mov eax, dword ptr(fileptr)
			push eax
			call dword ptr(fclose)
			add esp, 4
			jmp endit

portOK:		mov dword ptr(portptr), eax
			lea eax, listening
			push eax
			call dword ptr printf
			add esp, 4
			/* get char from message file */
			mov esi, 0
checkport:	
			mov dword ptr(loadcounter), esi
			mov eax, dword ptr(portptr)
			push eax
			call dword ptr(fgetc)
			add esp, 4
			cmp eax, NOTHING
			je checkport
			cmp eax, ENDOFFILE
			je nomore
			mov ebx, eax
			mov esi, dword ptr(loadcounter)
			inc esi
			cmp esi, dword ptr(loadcycle1)
			jle rtrvng3
			cmp esi, dword ptr(loadcycle2)
			jle rtrvng2
			cmp esi, dword ptr(loadcycle3)
			jle rtrvng
			cmp esi, dword ptr(loadcycle4)
			jle rtrvngreset
			
rtrvng3:	lea eax, retreiving3
			push eax
			call dword ptr printf
			add esp, 4
			jmp chkprtjmp

rtrvng2:	lea eax, retreiving2
			push eax
			call dword ptr printf
			add esp, 4
			jmp chkprtjmp

rtrvng:		lea eax, retreiving
			push eax
			call dword ptr printf
			add esp, 4
			jmp chkprtjmp
			
rtrvngreset:	mov esi, 0
			

chkprtjmp:	mov eax, dword ptr(fileptr)
			push eax
			push ebx
			call dword ptr(fputc)
			add esp, 8
			
			jmp checkport
			


nomore:		lea eax, done
			push eax
			call dword ptr printf
			add esp, 4
			mov eax, dword ptr(fileptr)
			push eax
			mov ebx, ENDOFFILE
			push ebx
			call dword ptr(fputc)
			add esp, 8
			
			mov eax, dword ptr(portptr)
			push eax
			call dword ptr(fclose)
			add esp, 4

			mov eax, dword ptr(fileptr)
			push eax
			call dword ptr(fclose)
			add esp, 4

			lea eax, readmode
			push eax
			lea eax, filename
			push eax
			call dword ptr(fopen)
			add esp, 8
			mov dword ptr(fileptr5), eax

			lea eax, writemode
			push eax
			lea eax, filename2
			push eax
			call dword ptr(fopen)
			add esp, 8
			mov dword ptr(fileptr6), eax
			lea eax, decrypting
			push eax
			call dword ptr printf
			add esp, 4

			mov edi, 0
more2:		mov dword ptr(loadcounter), edi
			mov eax, dword ptr(fileptr5)
			push eax
			call dword ptr(fgetc)
			add esp, 4
			cmp eax, ENDOFFILE
			je nomore2 
			mov ebx, eax
			mov edi, dword ptr(loadcounter)
			inc edi
			cmp edi, dword ptr(loadcycle1)
			jle dcrptng3
			cmp edi, dword ptr(loadcycle2)
			jle dcrptng2
			cmp edi, dword ptr(loadcycle3)
			jle dcrptng
			cmp edi, dword ptr(loadcycle4)
			jle dcrptngreset
			
dcrptng3:	lea eax, decrypting3
			push eax
			call dword ptr printf
			add esp, 4
			jmp rdmdjmp

dcrptng2:	lea eax, decrypting2
			push eax
			call dword ptr printf
			add esp, 4
			jmp rdmdjmp

dcrptng:		lea eax, decrypting
			push eax
			call dword ptr printf
			add esp, 4
			jmp rdmdjmp
			
dcrptngreset:	mov edi, 0

rdmdjmp:	lea eax, readmode
			push eax
			lea eax, c1a
			push eax
			call dword ptr(fopen)
			add esp, 8
			mov dword ptr(fileptr4), eax

			mov esi, 0
cipher1a:	inc esi
			mov eax, dword ptr(fileptr4)
			push eax
			call dword ptr(fgetc)
			add esp, 4
			cmp eax, ebx
			jne cipher1a

			lea eax, readmode
			push eax
			lea eax, pa
			push eax
			call dword ptr(fopen)
			add esp, 8
			mov dword ptr(fileptr3), eax

plaina:		dec esi
			mov eax, dword ptr(fileptr3)
			push eax
			call dword ptr(fgetc)
			add esp, 4
			cmp esi, 0
			jnz plaina
			mov ebx, eax

			mov eax, dword ptr(fileptr6)
			push eax
			push ebx
			call dword ptr(fputc)
			add esp, 8
			
			mov eax, dword ptr(fileptr3)
			push eax
			call dword ptr(fclose)
			add esp, 4

			mov eax, dword ptr(fileptr4)
			push eax
			call dword ptr(fclose)
			add esp, 4

			jmp more2

nomore2:	mov eax, dword ptr(fileptr3)
			push eax
			call dword ptr(fclose)
			add esp, 4

			mov eax, dword ptr(fileptr4)
			push eax
			call dword ptr(fclose)
			add esp, 4

			mov eax, dword ptr(fileptr5)
			push eax
			call dword ptr(fclose)
			add esp, 4

			mov eax, dword ptr(fileptr6)
			push eax
			call dword ptr(fclose)
			add esp, 4
			lea eax, done
			push eax
			call dword ptr printf
			add esp, 4

endit:
			lea eax, endmessage
			push eax
			call dword ptr printf
			add esp, 4
	
			call dword ptr getchar
	}
}