
.bss
	apples: .space 80
	snakes: .space 8000 #Bits of snake!
	snakeHead: .space 8

.data
	snakeSize: 		.long 0
	address: 		.long 0
	numApples: 		.long 0
	numSnakeBits: 	.long 0
	dir:			.long 0
	i:				.long 0
	startX: 		.long 0
	startY:			.long 0
	crawling: 		.long 0
	score: 			.long 0

.section .text
	.globl nibbles_init
	.globl nibbles_run
	.globl nibbles_end

nibbles_init:

	movl 8(%esp), %eax
	movl 12(%esp), %ebx
	movl %ebx, (numApples)
	#movl %eax, (numSnakeBits)
	movl $5, %eax
	movl %eax, (numSnakeBits)

	movl $1, %eax
	movl %eax, (crawling)

	movl $97, %eax
	movl %eax, (dir)

	call nib_init
	call init_snakes
	call spawn_apples

	ret

init_snakes:
	movl $snakes, %eax
	movl %eax, address
	movl $0, %eax
	movl %eax, (i)

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
	call update_snake
	call update_snake_collision
	call update_snake_collision_walls
	call update_snake_collision_apples

	call nib_clear_screen
	call render_apples
	call render_snakes

	movl (score), %eax
	pushl %eax
	call nib_print_score
	addl $4, %esp

	movl (crawling), %eax
	cmpl $1, %eax
	je nibbles_run
	ret

get_input:
	call nib_poll_kbd
	cmpl $97, %eax # left
	je get_input_set_dir_left
    cmpl $119, %eax #up
    je get_input_set_dir_up
    cmpl $100, %eax #right
    je get_input_set_dir_right
    cmpl $115, %eax #down
    je get_input_set_dir_down
    ret

    get_input_set_dir_left:
    movl (dir), %ebx
    cmpl $100, %ebx
    jne get_input_set_dir
    ret

    get_input_set_dir_up:
    movl (dir), %ebx
    cmpl $115, %ebx
    jne get_input_set_dir
    ret

    get_input_set_dir_right:
    movl (dir), %ebx
    cmpl $97, %ebx
    jne get_input_set_dir
    ret

    get_input_set_dir_down:
    movl (dir), %ebx
    cmpl $119, %ebx
    jne get_input_set_dir
    ret

    get_input_set_dir:
    movl %eax, (dir)
    ret

update_snake:

	update_snake_body:
	movl (numSnakeBits), %eax
	movl %eax, (i)
	movl $8, %ecx
	mull %ecx
	movl $snakes, %ebx
	addl %eax, %ebx
	subl $4, %ebx
	movl %ebx, address

	update_snake_loop:
	movl (i), %eax
	cmpl $1, %eax
	je update_snake_finished

	movl address, %eax
	movl %eax, %ebx
	subl $8, %ebx
	movl (%ebx), %ecx
	movl %ecx, (%eax)

	subl $4, %eax
	subl $4, %ebx
	movl (%ebx), %ecx
	movl %ecx, (%eax)

	movl (i), %eax
	subl $1, %eax
	movl %eax, (i)
	movl $8, %eax
	subl %eax, address
	jmp update_snake_loop

	update_snake_finished:

	movl $snakes, %eax
	movl $snakes, %ebx
	addl $4, %ebx

	movl (dir), %ecx
	cmpl $97, %ecx # left
	je update_snake_left 
    cmpl $119, %ecx #up
    je update_snake_up
    cmpl $100, %ecx #right
    je update_snake_right
    cmpl $115, %ecx #down
    je update_snake_down

    update_snake_left:
    movl $1, %ebx
    subl %ebx, (%eax)
 	ret
    update_snake_up:
    movl $1, %eax
    subl %eax, (%ebx)
    ret
    update_snake_right:
    movl $1, %ebx
    addl %ebx, (%eax)
    ret
    update_snake_down:
    movl $1, %eax
    addl %eax, (%ebx)
    ret

update_snake_collision:

	movl $snakes, %eax
	movl $snakeHead, %ecx
	movl (%eax), %ebx
	movl %ebx, (%ecx)
	addl $4, %eax
	addl $4, %ecx
	movl (%eax), %ebx
	movl %ebx, (%ecx)

	movl $snakes, %eax
	addl $8, %eax
	movl %eax, address

	movl $0, i

	update_snake_collision_loop:
	movl address, %eax
	movl (%eax), %ebx
	addl $4, %eax
	movl (%eax), %ecx
	addl $4, %eax
	movl %eax, address

	movl $snakeHead, %eax
	movl (%eax), %edx
	cmpl %ebx, %edx
	jne snake_collision_loop_continue
	addl $4, %eax
	movl (%eax), %edx
	cmpl %ecx, %edx
	jne snake_collision_loop_continue

	call end_game

	snake_collision_loop_continue:
	movl (i), %eax
	addl $1, %eax
	cmpl (numSnakeBits), %eax
	movl %eax, (i)
	jne update_snake_collision_loop
	ret

update_snake_collision_walls:
	call get_x
	movl %eax, %ecx # X Max
	call get_y
	movl %eax, %edx # Y Max

	movl $snakes, %eax
	movl (%eax), %ebx # X
	addl $4, %eax
	movl (%eax), %eax # Y

	cmpl %ebx, %ecx
	je end_game
	cmpl %eax, %edx
	je end_game

	cmpl $0, %ebx
	je end_game
	cmpl $0, %eax
	je end_game
	
	ret

update_snake_collision_apples:
	movl $snakes, %eax
	movl (%eax), %ebx # X
	addl $4, %eax
	movl (%eax), %eax # Y

	movl $snakeHead, %ecx
	movl %ebx, (%ecx)
	addl $4, %ecx
	movl %eax, (%ecx)

	movl $apples, %eax
	movl %eax, address
	movl $0, i

	snake_collision_apples_loop:
	movl address, %eax
	movl (%eax), %ebx #X
	addl $4, %eax
	movl (%eax), %ecx #Y
	addl $4, %eax
	movl %eax, (address)

	movl $snakeHead, %eax
	movl (%eax), %edx
	
	cmpl %ebx, %edx
	jne snake_collision_apples_loop_continue

	addl $4, %eax
	movl (%eax), %edx

	cmpl %ecx, %edx
	jne snake_collision_apples_loop_continue

	call nib_rand_x
	movl %eax, %ebx
	call nib_rand_y
	movl address, %ecx
	subl $4, %ecx
	movl %eax, (%ecx)
	subl $4, %ecx
	movl %ebx, (%ecx) 

	movl $1, %eax
	addl %eax, (numSnakeBits)
	addl %eax, (score)

	snake_collision_apples_loop_continue:
	movl (i), %eax
	addl $1, %eax
	cmpl (numApples), %eax
	movl %eax, (i)
	jne snake_collision_apples_loop
	ret
	
	ret

end_game:
	movl $0, %eax
	movl %eax, (crawling)
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
