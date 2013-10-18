
.section .text
	.globl start_game

start_game:
	#movl 8(%ebp), %eax
	#movl 12(%ebp), %ebx
	#movl %eax, 8(%ebp)
	#movl %ebx, 12(%ebp)

	call nibbles_init
	call nibbles_run
	call nibbles_end

