# Individual Assignment 1 - CSE 031 Lab 5
# Hongzhe Xie

# Description: Given a value in $s0 (set manually in MARS),
#              compute values for registers $t0 through $t7.

.text
main:
    move $t0, $s0          # $t0 = $s0
    addi $t1, $t0, -7      # $t1 = $t0 - 7
    add  $t2, $t1, $t0     # $t2 = $t1 + $t0
    addi $t3, $t2, 2       # $t3 = $t2 + 2
    add  $t4, $t3, $t2     # $t4 = $t3 + $t2
    addi $t5, $t4, -28     # $t5 = $t4 - 28
    sub  $t6, $t4, $t5     # $t6 = $t4 - $t5
    addi $t7, $t6, 12      # $t7 = $t6 + 12

    li $v0, 10             # exit
    syscall
