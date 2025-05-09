bits 32	;our system will be in 32 bit mode
section .text
	;multiboot spec
	align 4
	dd 0x1badb002
	dd 0x00
	dd - (0x1badb002 + 0x00)

global start
extern kmain	;import function from other file

start:	
	cli			;disabling interrupts
	mov esp, stack_space	;stack pointer
	call kmain		;calling imported function
	hlt			;stopping cpu when program ended

section .bss
resb 8192
stack_space
