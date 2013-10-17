
.bss
	apples: .space 80

.data
	snakeSize: 	.long 0
	address: 	.long 0
	numApples: 	.long 0

	i:			.long 0

.section .text
	.globl nibbles_init
	.globl nibbles_run
	.globl nibbles_end

nibbles_init:
	#popl %eax
	#popl %ebx

	movl 8(%esp), %eax
	movl 12(%esp), %ebx
	movl %ebx, (numApples)

	call nib_init

	#movl 8(%ebp), %eax
	#movl %eax, (numApples)

	call spawn_apples


	ret

spawn_apples:
	movl $apples, %eax
	movl %eax, address
	movl $0, i

	spawn_apple_loop:
	
	call nib_rand_x
	movl address, %ebx
	movl %eax, (%ebx)
	addl $4, %ebx
	movl %ebx, (address)
	
	call nib_rand_y
	movl address, %ebx
	movl %eax, (%ebx)
	addl $4, %ebx
	movl %ebx, (address)

	movl (i), %eax
	addl $1, %eax
	cmpl (numApples), %eax
	movl %eax, (i)
	jne spawn_apple_loop
	ret

nibbles_run:
	pushl $200000
	call usleep
	addl $4, %esp

	call nib_clear_screen
	call render_apples
	jmp nibbles_run
	ret

render_apples:
	movl $apples, %eax
	movl %eax, address
	movl $0, i

	render_apple_loop:
	movl address, %eax
	movl (%eax), %ebx
	addl $4, %eax
	movl (%eax), %ecx
	addl $4, %eax
	movl %eax, (address)

	pushl $111
	pushl %ecx
	pushl %ebx
	call nib_put_scr
	addl $12, %esp

	movl (i), %eax
	addl $1, %eax
	cmpl (numApples), %eax
	movl %eax, (i)
	jne render_apple_loop
	ret

nibbles_end:
	call nib_end
	ret
