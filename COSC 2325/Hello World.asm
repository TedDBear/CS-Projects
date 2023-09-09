	.data 
buffer: .space 20
msg1: .asciiz "\n hello world "
msg2: .asciiz "\n Enter your name "
msg3: .asciiz "\n Your name is "
msg4: .asciiz "\n Enter your age "
msg5: .asciiz "\n Your age is "
msg6: .asciiz "\n You can collect on social security"
msg7: .asciiz "\n You are too young to be playing on a computer"
msg8: .asciiz "\n You should be in school"
msg9: .asciiz "\n You should be working now"
	.text

main:
	li 	$v0, 4
	la 	$a0, msg1 
	syscall
	li	$v0, 4	
	la	$a0, msg2
	syscall
	li	$v0, 8
	la 	$a0, buffer	#adds space to insert name
	li 	$a1, 20
	syscall
	move 	$t0, $a0
	li	$v0, 4
	la 	$a0, msg3
	syscall
	li	$v0, 4	
	move 	$a0, $t0
	syscall
	# reads integer and display it
	li	$v0, 4
	la	$a0, msg4
	syscall
	li 	$v0, 5	# reads int age typed in
	syscall
	move 	$t0, $v0 # moves int age to a temporary save state
	li	$v0, 4
	la	$a0, msg5
	syscall
	li	$v0, 1
	move 	$a0, $t0 # moves int age from a temporary save state to an address
	syscall
	# if-then statement
	move	$t0, $a0
	bgt $t0, 62, old	#if true, go to "old"
	blt $t0, 3, baby
	blt $t0, 18, student
	bge $t0, 18, adult
	j	end
	old:		# "old" block
	li	$v0, 4
	la	$a0, msg6
	syscall
	j	end	# jump to end after the statement displays
	baby:
	li	$v0, 4
	la	$a0, msg7
	syscall
	j	end
	student:
	li	$v0, 4
	la	$a0, msg8
	syscall
	j	end
	adult:
	li	$v0, 4
	la	$a0, msg9
	syscall
	j	end
	end:		# ends loop
	li	$v0, 10 # terminates program
	syscall
	
	
	
