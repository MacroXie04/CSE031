# compare.s
# Compares user input against n using slt, beq, and bne

.data
n:      .word 25
str1:   .asciiz "Less than\n"
str2:   .asciiz "Less than or equal to\n"
str3:   .asciiz "Greater than\n"
str4:   .asciiz "Greater than or equal to\n"
prompt: .asciiz "Enter a number: "

.text
main:
        # Print prompt
        li      $v0, 4
        la      $a0, prompt
        syscall

        # Read integer from user -> stored in $v0
        li      $v0, 5
        syscall
        move    $t0, $v0        # $t0 = user input

        # Load n into $t1
        la      $t1, n
        lw      $t1, 0($t1)     # $t1 = 25

        # --- Less than check (Q5) ---
        # if input < n, print "Less than"
        slt     $t2, $t0, $t1   # $t2 = 1 if input < n
        bne     $t2, $zero, printLess

        # --- Greater than or equal to check (Q6) ---
        # if input >= n, print "Greater than or equal to"
        # (if we reach here, slt was 0, so input >= n)
        beq     $t2, $zero, printGEQ

        j       end

printLess:
        li      $v0, 4
        la      $a0, str1
        syscall
        j       checkGT

printGEQ:
        li      $v0, 4
        la      $a0, str4
        syscall

checkGT:
        # --- Greater than check (Q7) ---
        # if input > n, print "Greater than"
        slt     $t2, $t1, $t0   # $t2 = 1 if n < input, meaning input > n
        bne     $t2, $zero, printGreater

        # --- Less than or equal to check (Q8) ---
        # if input <= n, print "Less than or equal to"
        beq     $t2, $zero, printLEQ

        j       end

printGreater:
        li      $v0, 4
        la      $a0, str3
        syscall
        j       end

printLEQ:
        li      $v0, 4
        la      $a0, str2
        syscall

end:
        # Exit program
        li      $v0, 10
        syscall
