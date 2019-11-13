/* Naglowek multiboota */
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS) 


.section .multiboot
	.align 4
	.long MAGIC
	.long FLAGS
	.long CHECKSUM
 
/* Ustawienie stosu */
.section .bss
	.align 16
	stack_bottom:
	.skip 16384 # 16 KiB
	stack_top:

gdtr:
.word 0
.long 0

idtr:
.word 0
.long 0

/* Inicjalizacja tablic GDT i IDT */
.global GDT_init
.type GDT_init, @function
GDT_init:
	mov 4(%esp), %eax
	mov %eax, gdtr+2
	mov 8(%esp), %ax
	mov %ax, gdtr
	lgdt gdtr
	ret

.global IDT_init
.type IDT_init, @function
IDT_init:
	mov 4(%esp), %eax
	mov %eax, idtr+2
	mov 8(%esp), %ax
	mov %ax, idtr
	lidt idtr
	sti
	ret

.global reloadSegments
.type reloadSegments, @function
reloadSegments:
	ljmp $0x8, $reloadCS
.global reloadCS
.reloadCS:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ret

.global _start
.type _start, @function
_start:
	

	mov $stack_top, %esp

	call kernel_main
 
	cli
1:	hlt
	jmp 1b
 
.size _start, . - _start
