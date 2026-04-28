.data

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded down) with dropped scores removed: "
str6: .asciiz "All scores dropped!\n"
space: .asciiz " "
newline: .asciiz "\n"

.text

# This is the main program.
# It first asks user to enter the number of assignments.
# It then asks user to input the scores, one at a time.
# It then calls selSort to perform selection sort.
# It then calls printArray twice to print out contents of the original and sorted scores.
# It then asks user to enter the number of (lowest) scores to drop.
# It then calls calcSum on the sorted array with the adjusted length (to account for dropped scores).
# It then prints out average score with the specified number of (lowest) scores dropped from the calculation.
main:
	addi $sp, $sp -4
	sw $ra, 0($sp)
input_num:
	la $a0, str0
	li $v0, 4
	syscall
	li $v0, 5	# Read the number of scores from user
	syscall

	# Your code here to handle invalid number of scores (can't be less than 1 or greater than 25)
	blt $v0, 1, input_num
	bgt $v0, 25, input_num

	move $s0, $v0	# $s0 = numScores
	move $t0, $0
	la $s1, orig	# $s1 = orig
	la $s2, sorted	# $s2 = sorted
loop_in:
	li $v0, 4
	la $a0, str1
	syscall
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	# Read elements from user
	syscall
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in

	move $a0, $s0
	jal selSort	# Call selSort to perform selection sort in original array

	li $v0, 4
	la $a0, str2
	syscall
	move $a0, $s1	# More efficient than la $a0, orig
	move $a1, $s0
	jal printArray	# Print original scores
	li $v0, 4
	la $a0, str3
	syscall
	move $a0, $s2	# More efficient than la $a0, sorted
	move $a1, $s0
	jal printArray	# Print sorted scores

input_drop:
	li $v0, 4
	la $a0, str4
	syscall
	li $v0, 5	# Read the number of (lowest) scores to drop
	syscall

	# Your code here to handle invalid number of (lowest) scores to drop (can't be less than 0, or
	# greater than the number of scores). Also, handle the case when number of (lowest) scores to drop
	# equals the number of scores.
	bltz $v0, input_drop
	bgt $v0, $s0, input_drop

	move $s3, $v0		# $s3 = drop
	beq $s3, $s0, all_dropped

	move $a1, $v0
	sub $a1, $s0, $a1	# numScores - drop
	move $a0, $s2
	jal calcSum	# Call calcSum to RECURSIVELY compute the sum of scores that are not dropped

	# Your code here to compute average and print it (you may also end up having some code here to help
	# handle the case when number of (lowest) scores to drop equals the number of scores
	sub $t0, $s0, $s3	# numScores - drop
	div $v0, $t0
	mflo $t1		# average = sum / (numScores - drop)

	li $v0, 4
	la $a0, str5
	syscall

	move $a0, $t1
	li $v0, 1
	syscall

	la $a0, newline
	li $v0, 4
	syscall
	j end

all_dropped:
	li $v0, 4
	la $a0, str6
	syscall

end:	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10
	syscall


# printList takes in an array and its size as arguments.
# It prints all the elements in one line with a newline at the end.
printArray:
	# $a0 = array base, $a1 = size
	move $t0, $0		# i = 0
	move $t9, $a0		# save array base
pa_loop:
	beq $t0, $a1, pa_end
	sll $t1, $t0, 2
	add $t1, $t1, $t9
	lw $t2, 0($t1)		# arr[i]

	move $a0, $t2
	li $v0, 1
	syscall			# print int

	la $a0, space
	li $v0, 4
	syscall			# print space

	addi $t0, $t0, 1
	j pa_loop
pa_end:
	la $a0, newline
	li $v0, 4
	syscall			# print newline
	jr $ra


# selSort takes in the number of scores as argument.
# It performs SELECTION sort in descending order and populates the sorted array
selSort:
	# $a0 = length
	# Copy orig into sorted
	la $t0, orig
	la $t1, sorted
	move $t2, $0		# i = 0
ss_copy:
	beq $t2, $a0, ss_copy_done
	sll $t3, $t2, 2
	add $t4, $t0, $t3
	add $t5, $t1, $t3
	lw $t6, 0($t4)
	sw $t6, 0($t5)
	addi $t2, $t2, 1
	j ss_copy
ss_copy_done:
	# Selection sort (descending) on sorted array
	# for (i = 0; i < len - 1; i++)
	move $t0, $0		# i = 0
	addi $t7, $a0, -1	# len - 1
	la $t8, sorted
ss_outer:
	beq $t0, $t7, ss_done
	move $t1, $t0		# maxIndex = i
	addi $t2, $t0, 1	# j = i + 1
ss_inner:
	beq $t2, $a0, ss_inner_done
	sll $t3, $t2, 2
	add $t3, $t3, $t8
	lw $t4, 0($t3)		# sorted[j]
	sll $t5, $t1, 2
	add $t5, $t5, $t8
	lw $t6, 0($t5)		# sorted[maxIndex]
	ble $t4, $t6, ss_no_update
	move $t1, $t2		# maxIndex = j
ss_no_update:
	addi $t2, $t2, 1
	j ss_inner
ss_inner_done:
	# swap sorted[i] and sorted[maxIndex]
	sll $t3, $t1, 2
	add $t3, $t3, $t8	# &sorted[maxIndex]
	sll $t5, $t0, 2
	add $t5, $t5, $t8	# &sorted[i]
	lw $t4, 0($t3)
	lw $t6, 0($t5)
	sw $t4, 0($t5)
	sw $t6, 0($t3)

	addi $t0, $t0, 1
	j ss_outer
ss_done:
	jr $ra


# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
# Note: you MUST NOT use iterative approach in this function.
calcSum:
	# $a0 = array, $a1 = size
	bgtz $a1, cs_recurse
	li $v0, 0
	jr $ra
cs_recurse:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $a1, 4($sp)

	addi $a1, $a1, -1	# size - 1
	jal calcSum

	lw $ra, 0($sp)
	lw $a1, 4($sp)
	addi $sp, $sp, 8

	addi $t0, $a1, -1	# index = size - 1
	sll $t0, $t0, 2
	add $t0, $t0, $a0
	lw $t1, 0($t0)		# arr[size - 1]
	add $v0, $v0, $t1

	jr $ra
