#define vgaw 80
#define vgah 25 
#define vidPtr (char*)0xb8000 //video memory starting here
#define vgasz (vgaw * vgah * 2)

void clearScr(char *vidptr);

//function called in bootloader
void kmain(void)
{
	const char *str = "hello,world"; //string will be printed
	char *vidptr = vidPtr;
	unsigned int i = 0;	 
	unsigned int j = 0;	

	clearScr(vidptr);

	j = 0;	//reset j for string
	//in this loop we write a string to the video memory
	while(str[j] != '\0') {//continue until null terminate
		//printing our string (str) to screen
		vidptr[i] = str[j];	//write character from string to video mem
		vidptr[i+1] = 0x0a;	//set attribute byte 
		++j;	//move to next character in str
		i = i+2;	//move to next pos in video mem
	}
	return;	//exit the function
}

void clearScr(char *vidptr){
	for(unsigned int j = 0; j < vgasz; j += 2) {
		vidptr[j] = ' ';	//null symbol
		vidptr[j+1] = 0x07;	//set attribute byte
	}	
}
