#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define vgaw 80
#define vgah 25 
#define vidPtr (char*)0xb8000 //video memory starting here
#define vgasz (vgaw * vgah * 2)

void clearScr(char *vidptr);
void printString(const char *str);

enum vgacols{
	black=0,
	blue=1,
	green=2,
	cyan=3,
	red=4,
	magenta=5,
	brown=6,
	lightgrey=7,
	darkgrey=8,
	lightblue=9,
	lightgreen=10,
	lightcyan=11,
	lightred=12,
	lightmagenta=13,
	lightbrown=14,
	white=15,
};

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)vidPtr;

static inline uint8_t vgaEntryCol(enum vgacols fg, enum vgacols bg){
	return fg | bg << 4;
}

static inline uint16_t vgaEntry(unsigned char uc,uint8_t color){
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str){
	size_t len=0;
	while(str[len])
		len++;
	return len;
}

void termInit(void){
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vgaEntryCol(lightcyan,black);
	
	for(size_t y=0;y<vgah;y++){
		for(size_t x=0;x<vgaw;x++){
			const size_t index = y * vgaw + x;
			terminal_buffer[index] = vgaEntry(' ', terminal_color);
		}
	}
}

void termSetCol(uint8_t color)
{
	terminal_color = color;
}

void termPutEntryAt(char c,uint8_t color,size_t x,size_t y){
	const size_t index = y * vgaw + x;
	terminal_buffer[index] = vgaEntry(c,color);
}

void termPutC(char c){
	if(c=='\n'){
		terminal_column = 0;
		if(++terminal_row==vgah){
			terminal_row=0;
		}
	} else {
		termPutEntryAt(c,terminal_color,terminal_column,terminal_row);
		if(++terminal_column == vgaw){
			terminal_column = 0;
			if(++terminal_row == vgah)
				terminal_row = 0;
		}
	}	
}

void termWrite(const char* data,size_t size){
	for(size_t i=0;i<size;i++)
		termPutC(data[i]);
}	

//function called in bootloader
void kmain(void)
{
	char *vidptr = vidPtr;
	unsigned int i=0;
	termInit();

	clearScr(vidptr);	//clearing screen
	printString("kakashka\n");	//printing 'kakashka' to screen
	printString("test\n");	//printing test message to screen
}

void printString(const char *str){
	termWrite(str, strlen(str));
}

void clearScr(char *vidptr){
	for(unsigned int j = 0; j < vgasz; j += 2) {
		vidptr[j] = ' ';	//null symbol
		vidptr[j+1] = 0x07;	//set attribute byte
	}	
}
