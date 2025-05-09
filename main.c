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

	clearScr(vidptr);
	printString(vidptr,"hello,world",&i);
	return;	//exit the function
}

void printString(char *vidptr, const char *str, unsigned int *i){
	unsigned int j = 0;
	while(str[j] != '\0' && *i < vgasz){
		vidptr[*i] = str[j];
		vidptr[*i + 1] = 0x0a;
		++j;
		*i += 2;
	}
}

void clearScr(char *vidptr){
	for(unsigned int j = 0; j < vgasz; j += 2) {
		vidptr[j] = ' ';	//null symbol
		vidptr[j+1] = 0x07;	//set attribute byte
	}	
}
