
.section .text
	.globl start_game

start_game:
	call nibbles_init
	call nibbles_run
	call nibbles_end

