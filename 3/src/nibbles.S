
.bss
	apples: .space 800  #Pairs of x and y coordinates for the apples.
	snakes: .space 8000 #Pairs of x and y coordinates for the snake.
	snakeHead: .space 8

.data
	snakeSize: 		.long 0 
	address: 		.long 0 #Used to save address of current element.
	numApples: 		.long 0
	numSnakeBits: 	.long 0
	dir:			.long 0 #The direction the snake is currently moving in.
	i:				.long 0 #Loop counter.
	startX: 		.long 0	#Starting x-coordinate for snake.
	startY:			.long 0	#Starting y-coordinate for snake.
	crawling: 		.long 0 #Wether or not the game is running.
	score: 			.long 0

.section .text
	.globl nibbles_init
	.globl nibbles_run
	.globl nibbles_end

nibbles_init:

	#Pop the stack and store the programs arguments.
	movl 8(%esp), %eax
	movl 12(%esp), %ebx
	movl %ebx, (numApples)
	movl %eax, (numSnakeBits)

	#Initialize crawling to true.
	movl $1, %eax
	movl %eax, (crawling)

	#Initialize dir so the snake moves to the left
	#when the program starts.
	movl $97, %eax
	movl %eax, (dir)

	call nib_init
	call init_snakes
	call spawn_apples

	ret

init_snakes:
	#Find starting address of the array snakes.
	movl $snakes, %eax
	movl %eax, address
	#Initialize loop counter i to zero.
	movl $0, %eax
	movl %eax, (i)

	#Find the center of the playing field.
	call get_x_half
	movl %eax, (startX)
	call get_y_half
	movl %eax, (startY)

	init_snake_loop:
	
	#Write starting x-cooridnate to current element in snakes.
	movl (startX), %eax
	movl address, %ebx
	movl %eax, (%ebx)
	addl $4, %ebx
	movl %ebx, (address)
	#Write starting y-coordinate to current element in snakes.
	movl (startY), %eax
	movl address, %ebx
	movl %eax, (%ebx)
	addl $4, %ebx
	movl %ebx, (address)

	#Increment startX so that the next bit of snake will be located
	#to the right of the current one.
	movl (startX), %eax
	addl $1, %eax
	movl %eax, (startX)

	#Increment loop counter.
	movl (i), %eax
	addl $1, %eax
	#If loop counter i is less than numSnakeBits iterate once more.
	#Else return.
	cmpl (numSnakeBits), %eax
	movl %eax, (i)
	jne init_snake_loop
	ret	

spawn_apples:
	#Find starting address of array apples.
	movl $apples, %eax
	movl %eax, address
	#Initialze loop counter i to zero.
	movl $0, (i)

	spawn_apple_loop:
	#Get a random coordinate on the x-axis and write it to the
	#current apple.
	call nib_rand_x
	movl address, %ebx
	movl %eax, (%ebx)
	addl $4, %ebx
	movl %ebx, (address)
	
	#Get a random coordinate on the y-axis and write it to the
	#current apple.
	call nib_rand_y
	movl address, %ebx
	movl %eax, (%ebx)
	addl $4, %ebx
	movl %ebx, (address)

	#If i is less than numApples iterate once more.
	#Else return.
	movl (i), %eax
	addl $1, %eax
	cmpl (numApples), %eax
	movl %eax, (i)
	jne spawn_apple_loop
	ret

nibbles_run:
	#Use sleep to slow down the update frequency
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

	#Print the score
	movl (score), %eax
	pushl %eax
	call nib_print_score
	addl $4, %esp

	#Check if the snake is still crawling otherwise exit.
	movl (crawling), %eax
	cmpl $1, %eax
	je nibbles_run
	ret

get_input:
	#Get input and check if it matches wasd.
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

    #If new direction is left, current direction can't be right
    get_input_set_dir_left:
    movl (dir), %ebx
    cmpl $100, %ebx
    jne get_input_set_dir
    ret

    #If new direction is up, current direction can't be down
    get_input_set_dir_up:
    movl (dir), %ebx
    cmpl $115, %ebx
    jne get_input_set_dir
    ret

    #If new direction is right, current direction can't be left.
    get_input_set_dir_right:
    movl (dir), %ebx
    cmpl $97, %ebx
    jne get_input_set_dir
    ret

    #If new direction is down, current direction can't be up.
    get_input_set_dir_down:
    movl (dir), %ebx
    cmpl $119, %ebx
    jne get_input_set_dir
    ret

    #Write new direction to variable dir.
    get_input_set_dir:
    movl %eax, (dir)
    ret

update_snake:

	#Start from the last bit of snake and assign its position to
	#be that of the bit before it.

	update_snake_body:
	#Get number of snake bits.
	movl (numSnakeBits), %eax
	#Initialize loop counter i.
	movl %eax, (i)
	#Multiply number of snake bits by snake size
	movl $8, %ecx
	mull %ecx
	#Calculate address of last element in snake.
	movl $snakes, %ebx
	addl %eax, %ebx
	subl $4, %ebx
	movl %ebx, address

	update_snake_loop:
	#If loop counter is 1 exit loop.
	#We do not want to update the head here.
	movl (i), %eax
	cmpl $1, %eax
	je update_snake_finished

	#Overwrite current y-coordinate with the one before it. 
	movl address, %eax
	movl %eax, %ebx
	subl $8, %ebx
	movl (%ebx), %ecx
	movl %ecx, (%eax)

	#Overwrite current x-coordinate with the one before it.
	subl $4, %eax
	subl $4, %ebx
	movl (%ebx), %ecx
	movl %ecx, (%eax)

	#Decrement loop counter and current address.
	movl (i), %eax
	subl $1, %eax
	movl %eax, (i)
	movl $8, %eax
	subl %eax, address
	jmp update_snake_loop

	update_snake_finished:

	#Get the address of the snake's head.
	movl $snakes, %eax
	movl $snakes, %ebx
	addl $4, %ebx

	#Check the current direction.
	movl (dir), %ecx
	cmpl $97, %ecx # left
	je update_snake_left 
    cmpl $119, %ecx #up
    je update_snake_up
    cmpl $100, %ecx #right
    je update_snake_right
    cmpl $115, %ecx #down
    je update_snake_down

    #Move snake head in current direction.
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

	#Retrieve x and y-coordinate of snake head.
	movl $snakes, %eax
	movl $snakeHead, %ecx
	movl (%eax), %ebx
	movl %ebx, (%ecx)
	addl $4, %eax
	addl $4, %ecx
	movl (%eax), %ebx
	movl %ebx, (%ecx)

	#Write address of second bit of snake to variable address.
	movl $snakes, %eax
	addl $8, %eax
	movl %eax, address

	#Initialize loop counter
	movl $0, (i)

	#Iterate over all bits of snake and check for
	#collision with the head.
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
	#Get extremes of playing field.
	call get_x
	movl %eax, %ecx # X Max
	call get_y
	movl %eax, %edx # Y Max

	#Get snake head.
	movl $snakes, %eax
	movl (%eax), %ebx # X
	addl $4, %eax
	movl (%eax), %eax # Y

	#Check snake head against borders: x_min, x_max, y_min and y_max
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
	#Get address of snake head.
	movl $snakes, %eax
	movl (%eax), %ebx # X
	addl $4, %eax
	movl (%eax), %eax # Y

	#Write address of snake head to variable snakeHead.
	movl $snakeHead, %ecx
	movl %ebx, (%ecx)
	addl $4, %ecx
	movl %eax, (%ecx)

	#Initialze starting address and loop counter.
	movl $apples, %eax
	movl %eax, address
	movl $0, i

	#Iterate over all apples and check for collision with snake head.
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

	#Colliison has occured.
	#Spawn new apple.
	call nib_rand_x
	movl %eax, %ebx
	call nib_rand_y
	movl address, %ecx
	subl $4, %ecx
	movl %eax, (%ecx)
	subl $4, %ecx
	movl %ebx, (%ecx) 

	#Increment size of snake and score.
	movl $1, %eax
	addl %eax, (numSnakeBits)
	addl %eax, (score)

	snake_collision_apples_loop_continue:
	#Check loop counter and either do another iteration or return.
	movl (i), %eax
	incl %eax
	cmpl (numApples), %eax
	movl %eax, (i)
	jne snake_collision_apples_loop
	ret
	
	ret

end_game:
	#Set variable crawling to false.
	movl $0, %eax
	movl %eax, (crawling)
	ret

render_snakes:
	#Iterate over all the bits of snake and draw them on the screen.

	#Find starting adress.
	movl $snakes, %eax
	movl %eax, address
	#Init loop counter
	movl $0, (i)

	render_snake_loop:
	#Get x- and y-coordinate of current bit of snake
	movl address, %eax
	movl (%eax), %ebx
	addl $4, %eax
	movl (%eax), %ecx
	addl $4, %eax
	movl %eax, (address)

	#Push parameters to the stack and call nib_put_scr from helpers.c
	pushl $43
	pushl %ecx
	pushl %ebx
	call nib_put_scr
	addl $12, %esp

	#Increment loop counter and check loop conditions.
	movl (i), %eax
	addl $1, %eax
	cmpl (numSnakeBits), %eax
	movl %eax, (i)
	jne render_snake_loop
	ret

render_apples:
	#Iterate over all apples and draw them to the screen.
	
	#Find starting address.
	movl $apples, %eax
	movl %eax, address
	#Init loop counter
	movl (numApples), %ecx

	render_apple_loop:
	#Find x- and y-coordinates for current element.
	movl address, %eax
	movl (%eax), %ebx
	addl $4, %eax
	movl (%eax), %edx
	addl $4, %eax
	movl %eax, (address)

	#Save loop counter to prevenet it from being overwritten during
	#function call to nib_put_scr.
	movl %ecx, (i)

	#Push parameters to the stack and call nib_put_scr from helpers.c
	pushl $111
	pushl %edx
	pushl %ebx
	call nib_put_scr
	addl $12, %esp
	movl (i), %ecx

	loopnz render_apple_loop
	ret

nibbles_end:
	#Close down ncurses.
	call nib_end
	ret
