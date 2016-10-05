#include <stdio.h>
#include <conio.h>
#define FEND 0
void main(void) {

	char writemode[] = "wb";
	char readmode[] = "rb";
	char filename[] = "H:\\ASM\\lol.txt";
	char ctext[] = "H:\\ASM\\ctext.txt";
	char pa[] = "H:\\ASM\\pa.txt";
	char c1a[]= "H:\\ASM\\c1a.txt";


	FILE * fileptr; //Message to be sent
	FILE * fileptr2; //Encoded message
	FILE * fileptr3; //Plaintext alphabet
	FILE * fileptr4; //Cipher alphabet

		__asm {

			/* Initialising of Message FILE */
			lea eax, readmode
			push eax
			lea eax, filename
			push eax
			call dword ptr(fopen)
			add esp, 8

			mov dword ptr(fileptr), eax
			/* ------ */

			/* Initialising of the output ciphertext FILE */
			lea eax, writemode
			push eax
			lea eax, ctext
			push eax
			call dword ptr(fopen)
			add esp, 8

			mov dword ptr(fileptr2), eax
			/* ------ */

			/* Initialising of the plaintext alphabet FILE */
			lea eax, readmode
			push eax
			lea eax, pa
			push eax
			call dword ptr(fopen)
			add esp, 8
			
			mov dword ptr(fileptr3), eax
			/* ------ */

more:		mov eax, dword ptr(fileptr)
			push eax
			call dword ptr(fgetc)
			cmp eax, EOF
			jz nomore
			add esp, 4
			mov ebx, eax

			/* ENCRYPTION */
			mov esi, 0
plaina:		inc esi
			mov eax, dword ptr(fileptr3)
			push eax
			call dword ptr(fgetc)
			add esp, 4
			cmp eax, ebx
			jnz plaina

			// it gets stuck on the [plaina] loop on the last letter of the message string.

			lea eax, readmode
			push eax
			lea eax, c1a
			push eax
			call dword ptr(fopen)
			add esp, 8

			mov dword ptr(fileptr4), eax

cipher1a:	dec esi
			mov eax, dword ptr(fileptr4)
			push eax
			call dword ptr(fgetc)
			add esp, 4
			cmp esi, 0
			jnz cipher1a
			mov ebx, eax
			/* ENCRYPTION DONE */

			mov eax, dword ptr(fileptr2)
			push eax
			push ebx
			call dword ptr(fputc)
			add esp, 8
			jmp more

nomore:		mov eax, dword ptr(fileptr2)
			push eax
			call dword ptr(fclose)
			add esp, 4

			mov eax, dword ptr(fileptr)
			push eax
			call dword ptr(fclose)
			add esp, 8 
	}
}