# sumAll.s
# Reads integers from user until 0 is entered.
# Calculates the sum of all even numbers and the sum of all odd numbers.
# Does NOT use: div, and, or, andi, ori
#
# Pseudocode:
#   even_sum = 0
#   odd_sum = 0
#   loop:
#       print "Please enter a number: "
#       read num
#       if num == 0, goto done
#       temp = (num >> 1) << 1     # clear the LSB
#       if temp == num, it's even  # LSB was 0
#       else it's odd              # LSB was 1
#       add to appropriate sum
#       goto loop
#   done:
#       print even_sum
#       print odd_sum

.data
prompt:     .asciiz "Please enter a number: "
even_msg:   .asciiz "Sum of even numbers is: "
odd_msg:    .asciiz "Sum of odd numbers is: "
newline:    .asciiz "\n"

.text
main:
        # Initialize sums
        li      $s0, 0          # $s0 = even_sum
        li      $s1, 0          # $s1 = odd_sum

loop:
        # Print prompt
        li      $v0, 4
        la      $a0, prompt
        syscall

        # Read integer
        li      $v0, 5
        syscall
        move    $t0, $v0        # $t0 = user input

        # If input == 0, exit loop
        beq     $t0, $zero, done

        # Check if even or odd using shift (no div/and/or allowed)
        # Shift right by 1, then left by 1 — this clears the LSB
        srl     $t1, $t0, 1     # $t1 = input >> 1 (logical shift right)
        sll     $t1, $t1, 1     # $t1 = (input >> 1) << 1

        # If $t1 == $t0, the LSB was 0, so the number is even
        beq     $t1, $t0, is_even

        # Otherwise, it's odd
        add     $s1, $s1, $t0   # odd_sum += input
        j       loop

is_even:
        add     $s0, $s0, $t0   # even_sum += input
        j       loop

done:
        # Print "Sum of even numbers is: "
        li      $v0, 4
        la      $a0, even_msg
        syscall

        # Print even_sum
        li      $v0, 1
        move    $a0, $s0
        syscall

        # Print newline
        li      $v0, 4
        la      $a0, newline
        syscall

        # Print "Sum of odd numbers is: "
        li      $v0, 4
        la      $a0, odd_msg
        syscall

        # Print odd_sum
        li      $v0, 1
        move    $a0, $s1
        syscall

        # Print newline
        li      $v0, 4
        la      $a0, newline
        syscall

        # Exit
        li      $v0, 10
        syscall
