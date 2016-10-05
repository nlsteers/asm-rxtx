#include <stdio.h>;
#include <conio.h>;
#define FEND 0x3;
#define FLIMIT 200;
void main(void) {

	char writemode[] = "wb";
	char readmode[] = "rb";
	char filename[] = "H:\\ASM\\datatosend.txt";
	char pname[] = "COM1";
	char pa[] = "H:\\ASM\\alphabet.txt";
	char c1a[] = "H:\\ASM\\cipher1.txt";
	char fileerror[] = "Error finding file!\n";
	char porterror[] = "Error opening port!\n";
	char finding[] = "Finding file..\n";
	char done[] = "Done.\n";
	char transfer[] = "\nTransmitting file..\n";
	char endmessage[] = "Press any key to exit:\n";
	char startmessage[] = "Pres any key to begin:\n";
	int flushcounter;
	char encrypting[] = "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bEncrypting file  .";
	char encrypting2[] = "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bEncrypting file . ";
	char encrypting3[] = "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bEncrypting file.  ";
	int encryptcounter;
	int encryptcycle1 = 100;
	int encryptcycle2 = 200;
	int encryptcycle3 = 300;
	int encryptcycle4 = 400;


	FILE * fileptr; //Message to be sent
	FILE * portptr; //Encoded message
	FILE * fileptr3; //Plaintext alphabet
	FILE * fileptr4; //Cipher alphabet

		__asm {
			lea eax, startmessage
			push eax
			call dword ptr(printf)
			add esp, 4
			call dword ptr(getchar)
			/* open message file */
			lea eax, finding
			push eax
			call dword ptr(printf)
			add esp, 4
			lea eax, readmode
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



fileOK:		
			mov dword ptr(fileptr), eax

			/* open the port */
			lea eax, writemode
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
			lea eax, encrypting
			push eax
			call dword ptr(printf)
			add esp, 4

			/* get char from message file */
			mov edi, 0
			mov ecx, 0
more:		
			inc ecx
			mov dword ptr(flushcounter), ecx
			mov eax, dword ptr(portptr)
			push eax
			call dword ptr(fflush)
			add esp,4
			mov eax, dword ptr(fileptr)
			push eax
			call dword ptr(fgetc)
			cmp eax, EOF
			jz nomore
			add esp, 4
			mov ebx, eax


			/* open plaintext alphabet file */
			lea eax, readmode
			push eax
			lea eax, pa
			push eax
			call dword ptr(fopen)
			add esp, 8

			
			mov dword ptr(fileptr3), eax


			/* get and compare from pa file */
			mov esi, 0
plaina:		inc esi
			mov eax, dword ptr(fileptr3)
			push eax
			call dword ptr(fgetc)
			add esp, 4
			cmp eax, ebx
			jnz plaina

			/* open/reset of cipher alphabet file */
			lea eax, readmode
			push eax
			lea eax, c1a
			push eax
			call dword ptr(fopen)
			add esp, 8

			mov dword ptr(fileptr4), eax


			/* get and subsitute loop */
			
cipher1a:	
			dec esi
			mov eax, dword ptr(fileptr4)
			push eax
			call dword ptr(fgetc)
			add esp, 4
			cmp esi, 0
			jnz cipher1a
			mov ebx, eax
			inc edi
			cmp edi, dword ptr(encryptcycle1)
			jle encrptng3
			cmp edi, dword ptr(encryptcycle2)
			jle encrptng2
			cmp edi, dword ptr(encryptcycle3)
			jle encrptng
			cmp edi, dword ptr(encryptcycle4)
			jle encrptngreset
			
encrptng3:	lea eax, encrypting3
			push eax
			call dword ptr printf
			add esp, 4
			jmp portptrjmp

encrptng2:	lea eax, encrypting2
			push eax
			call dword ptr printf
			add esp, 4
			jmp portptrjmp

encrptng:	lea eax, encrypting
			push eax
			call dword ptr printf
			add esp, 4
			jmp portptrjmp
			
encrptngreset:	mov edi, 0

			/* fputc */
portptrjmp:	mov eax, dword ptr(portptr)
			push eax
			push ebx
			call dword ptr(fputc)
			add esp, 8

			/* ptr flush */	
			mov eax, dword ptr(portptr)
			push eax
			call dword ptr(fflush)
			add esp, 4

			mov eax, dword ptr(fileptr4)
			push eax
			call dword ptr(fclose)
			add esp, 4
			
			mov eax, dword ptr(fileptr3)
			push eax
			call dword ptr(fclose)
			add esp, 4
			
			mov ecx, dword ptr(flushcounter)
			cmp ecx, FLIMIT
			je flush
			jmp more
			
flush:		mov eax, dword ptr(portptr)
			push eax
			call dword ptr(fclose)
			add esp, 4
			
			lea eax, writemode
			push eax
			lea eax, pname
			push eax
			call dword ptr(fopen)
			add esp, 8

			mov ecx, 0
			
			jmp more

nomore:		lea eax, transfer
			push eax
			call dword ptr(printf)
			add esp, 4
			mov eax, dword ptr(portptr)
			push eax
			mov ebx, FEND
			push ebx
			call dword ptr(fputc)
			add esp, 8
			
			mov eax, dword ptr(fileptr4)
			push eax
			call dword ptr(fclose)
			add esp, 4 
			
			mov eax, dword ptr(fileptr3)
			push eax
			call dword ptr(fclose)
			add esp, 4 
			
			mov eax, dword ptr(portptr)
			push eax
			call dword ptr(fclose)
			add esp, 4

			mov eax, dword ptr(fileptr)
			push eax
			call dword ptr(fclose)
			add esp, 8 
			lea eax, done
			push eax
			call dword ptr(printf)
			add esp, 4
endit:
			lea eax, endmessage
			push eax
			call dword ptr printf
			add esp, 4
	
			call dword ptr getchar
			

	}
}