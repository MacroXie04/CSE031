#
# recursion1.s - MIPS translation of recursion1.c
#
# int recursion(int m) {
#     if(m == -1)            return 3;
#     else if(m <= -2) {
#         if (m < -2)        return 2;
#         else               return 1;          // m == -2
#     }
#     else                   return recursion(m - 3) + m + recursion(m - 2);
# }
#
# Follows MIPS register/calling conventions:
#   - Arguments passed in $a0
#   - Return value in $v0
#   - Caller saves $ra, $a0, and the first return value across the second call
#

	.data
prompt:  .asciiz "Please enter a number: "
newline: .asciiz "\n"

	.text
	.globl main

# ------------------------- main -------------------------
main:
	# Print prompt
	li   $v0, 4
	la   $a0, prompt
	syscall

	# Read integer from user
	li   $v0, 5
	syscall
	move $a0, $v0		# place input in $a0 as argument for recursion

	# Call recursion(x)
	jal  recursion

	# Print returned value
	move $a0, $v0
	li   $v0, 1
	syscall

	# Print newline
	la   $a0, newline
	li   $v0, 4
	syscall

	# Exit
	li   $v0, 10
	syscall

# ---------------------- recursion(m) --------------------
# Stack frame layout (12 bytes, 3 words):
#   0($sp) : saved $ra
#   4($sp) : saved $a0 (m)
#   8($sp) : saved $v0 from first recursive call
recursion:
	addi $sp, $sp, -12
	sw   $ra, 0($sp)

	# if (m == -1) return 3;
	li   $t0, -1
	bne  $a0, $t0, check_leq_neg2
	li   $v0, 3
	j    end_recur

check_leq_neg2:
	# else if (m <= -2)
	li   $t0, -2
	bgt  $a0, $t0, recur_case

	# if (m < -2) return 2; else (m == -2) return 1;
	blt  $a0, $t0, ret_2
	li   $v0, 1
	j    end_recur

ret_2:
	li   $v0, 2
	j    end_recur

recur_case:
	# Save m so we can use it after the first recursive call
	sw   $a0, 4($sp)

	# recursion(m - 3)
	addi $a0, $a0, -3
	jal  recursion

	# Save first return value so second call does not overwrite it
	sw   $v0, 8($sp)

	# recursion(m - 2)
	lw   $a0, 4($sp)	# restore m
	addi $a0, $a0, -2
	jal  recursion

	# $v0 = recursion(m-3) + m + recursion(m-2)
	lw   $t0, 8($sp)	# first recursive result
	lw   $t1, 4($sp)	# m
	add  $v0, $v0, $t0
	add  $v0, $v0, $t1

end_recur:
	lw   $ra, 0($sp)
	addi $sp, $sp, 12
	jr   $ra
