
.section .text
	.globl nibbles_init
	.globl nibbles_run
	.globl nibbles_end

nibbles_init:
	call nib_init

nibbles_run:
	pushl $200000
	call usleep
	addl $4, %esp

	call nib_clear_screen
	jmp nibbles_run

nibbles_end:
	call nib_end