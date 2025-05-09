#define vgaw 80
#define vgah 25 
#define vidPtr (char*)0xb8000 //video memory starting here
#define vgasz (vgaw * vgah * 2)

void clearScr(char *vidptr);
void printString(char *vidptr, const char *str, unsigned int *i);

//function called in bootloader
void kmain(void)
{
	char *vidptr = vidPtr;
	unsigned int i=0;

	clearScr(vidptr);	//clearing screen
	printString(vidptr,"kakashka",&i);	//printing 'kakashka' to screen
	return;	//exit the function
}

void printString(char *vidptr, const char *str, unsigned int *i){
	unsigned int j = 0;
	while(str[j] != '\0' && *i < vgasz){//putting text to video mem until string end
		vidptr[*i] = str[j];	//writing current char to video mem
		vidptr[*i + 1] = 0x0b;	//set attribute byte
		++j;	//incrementing string index to move next character
		*i += 2;	//incrementing video mem index by 2
	}
}

void clearScr(char *vidptr){
	for(unsigned int j = 0; j < vgasz; j += 2) {
		vidptr[j] = ' ';	//null symbol
		vidptr[j+1] = 0x07;	//set attribute byte
	}	
}
