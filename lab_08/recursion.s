.data

# TPS 2 #3 (input prompt to be displayed)
prompt:  .asciiz "Please enter an integer: "
newline: .asciiz "\n"

.text
main: 	addi $sp, $sp, -4	# Moving stack pointer to make room for storing local variables (push the stack frame)
	# TPS 2 #3 (display input prompt)
	li $v0, 4
	la $a0, prompt
	syscall

	move $s1, $sp

	# TPS 2 #4 (read user input)
	li $v0, 5
	syscall
	move $a0, $v0		# Move user input into $a0 as argument for recursion

	jal recursion	# Call recursion(x)

	# TPS 2 #6 (print out returned value)
	move $a0, $v0		# $v0 held return; move to $a0 to free $v0 for syscall
	li $v0, 1
	syscall

	# Print a newline
	la $a0, newline
	li $v0, 4
	syscall

	j end		# Jump to end of program


# Implementing recursion
recursion: addi $sp, $sp, -12	# Push stack frame for local storage

	# TPS 2 #7 - Save return address (first thing to store)
	sw $ra, 0($sp)


	addi $t0, $a0, 1
	bne $t0, $zero, not_minus_one

	# TPS 2 #8 (update returned value)
	li $v0, 1

	j end_recur

not_minus_one:	bne $a0, $zero, not_zero
	# TPS 2 #9 (update returned value)
	li $v0, 3

	j end_recur

not_zero: sw $a0, 4($sp)
	# TPS 2 #11 (Prepare new input argument, i.e. m - 2)
	addi $a0, $a0, -2


	jal recursion	# Call recursion(m - 2)

	# TPS 2 #12 - Save returned value so next call does not overwrite it
	sw $v0, 8($sp)

	# TPS 2 #13 (Prepare new input argument, i.e. m - 1)
	lw $a0, 4($sp)		# Restore original m
	addi $a0, $a0, -1

	jal recursion	# Call recursion(m - 1)

	# TPS 2 #14 (update returned value = recursion(m-2) + recursion(m-1))
	lw $t0, 8($sp)
	add $v0, $v0, $t0

	j end_recur


# End of recursion function
end_recur: # TPS 2 #15 - Retrieve return address so we can return correctly
	lw $ra, 0($sp)

	addi $sp, $sp, 12	# Pop stack frame
	jr $ra

# Terminating the program
end:	addi $sp, $sp, 4	# Moving stack pointer back (pop the stack frame)
	li $v0, 10
	syscall
