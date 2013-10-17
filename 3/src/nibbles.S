
.bss
	apples: .space 80
	snakes: .space 8000 #Bits of snake!

.data
	snakeSize: 		.long 0
	address: 		.long 0
	numApples: 		.long 0
	numSnakeBits: 	.long 0
	dir:			.long 0
	i:				.long 0
	startX: 		.long 0
	startY:			.long 0

.section .text
	.globl nibbles_init
	.globl nibbles_run
	.globl nibbles_end

nibbles_init:

	movl 8(%esp), %eax
	movl 12(%esp), %ebx
	movl %ebx, (numApples)
	movl %eax, (numSnakeBits)

	call nib_init
	call init_snakes
	call spawn_apples

	ret

init_snakes:
	movl $snakes, %eax
	movl %eax, address
	movl $0, i

	call get_x_half
	movl %eax, (startX)
	call get_y_half
	movl %eax, (startY)

	init_snake_loop:
	
	movl (startX), %eax
	movl address, %ebx
	movl %eax, (%ebx)
	addl $4, %ebx
	movl %ebx, (address)
	
	movl (startY), %eax
	movl address, %ebx
	movl %eax, (%ebx)
	addl $4, %ebx
	movl %ebx, (address)

	movl (startX), %eax
	addl $1, %eax
	movl %eax, (startX)

	movl (i), %eax
	addl $1, %eax
	cmpl (numSnakeBits), %eax
	movl %eax, (i)
	jne init_snake_loop
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
	
	call get_input

	call nib_clear_screen
	call render_apples
	call render_snakes
	jmp nibbles_run
	ret

get_input:
	call nib_poll_kbd
    movl %eax, (dir)
    ret

render_snakes:
	movl $snakes, %eax
	movl %eax, address
	movl $0, i

	render_snake_loop:
	movl address, %eax
	movl (%eax), %ebx
	addl $4, %eax
	movl (%eax), %ecx
	addl $4, %eax
	movl %eax, (address)

	pushl $43
	pushl %ecx
	pushl %ebx
	call nib_put_scr
	addl $12, %esp

	movl (i), %eax
	addl $1, %eax
	cmpl (numSnakeBits), %eax
	movl %eax, (i)
	jne render_snake_loop
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
