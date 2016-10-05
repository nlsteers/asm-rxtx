# include <stdio.h>
# include <conio.h>
# include <ctype.h>
# include <string.h>
 
	void vigenereChiper(char *text, char *key){
	    unsigned int i, j;
	   printf("Encrypted text: ");
	   for(i=0,j=0;i<strlen(text);i++, j++)
	   {
	    if(j>=strlen(key))
	      {
	          j = 0;    // j back to nol value when j >= length of string(keyword)
	      }
	 
	    if(text[i] >= 'a' && text[i] <= 'z')
	      {
	          // mod 26, total alphabet
	          printf("%c",97+(((toupper(text[i])-65)+(toupper(key[j])-65))%26));
	      }
	 
	        else if(text[i] >= 'A' && text[i] <= 'Z')
	      {
	          printf("%c",65+(((toupper(text[i])-65)+(toupper(key[j])-97))%26));
	      }
	 
	   }
	}
	void main(){
	    char text[255], keyword[30];
	    printf("Enter the Text you want to Encrypt: ");
	    gets(text);
	    printf("Enter the Keyword: ");
	    gets(keyword);
	    vigenereChiper(text, keyword);
	    getch();
	}