.data
str_pq: .asciiz "p + q: "
nl:     .asciiz "\n"

.text
MAIN:
    # Prologue for MAIN
    addiu $sp, $sp, -16
    sw $ra, 12($sp)
    sw $s0, 8($sp)
    sw $s1, 4($sp)
    sw $s2, 0($sp)

    # int x = 2, y = 4, z = 6;
    li $s0, 2		# x -> $s0
    li $s1, 4		# y -> $s1
    li $s2, 6		# z -> $s2

    # prepare to call foo(x, y, z)
    move $a0, $s0	# m -> $a0
    move $a1, $s1	# n -> $a1
    move $a2, $s2	# o -> $a2

    jal FOO

    # z = x + y + z + foo(x, y, z)
    # v0 has result of foo
    add $t0, $s0, $s1	# x + y
    add $t0, $t0, $s2	# x + y + z
    add $s2, $t0, $v0	# z = x + y + z + foo

    # printf("%d\n", z);
    move $a0, $s2
    li $v0, 1
    syscall

    la $a0, nl
    li $v0, 4
    syscall

    # Epilogue for MAIN
    lw $ra, 12($sp)
    lw $s0, 8($sp)
    lw $s1, 4($sp)
    lw $s2, 0($sp)
    addiu $sp, $sp, 16

    # return 0;
    li $v0, 10
    syscall

FOO:
    # Prologue
    # Save $ra, $s0, $s1 (for p and q), $a0, $a1, $a2 (to preserve args across calls)
    addiu $sp, $sp, -24
    sw $ra, 20($sp)
    sw $s0, 16($sp)
    sw $s1, 12($sp)
    sw $a0, 8($sp)
    sw $a1, 4($sp)
    sw $a2, 0($sp)

    # int p = bar(m + o, n + o, m + n);
    # m is $a0, n is $a1, o is $a2
    add $t0, $a0, $a2	# m + o
    add $t1, $a1, $a2	# n + o
    add $t2, $a0, $a1	# m + n
    move $a0, $t0
    move $a1, $t1
    move $a2, $t2
    jal BAR
    move $s0, $v0		# p -> $s0

    # Restore $a0, $a1, $a2
    lw $a0, 8($sp)
    lw $a1, 4($sp)
    lw $a2, 0($sp)

    # int q = bar(m - o, n - m, n + n);
    sub $t0, $a0, $a2	# m - o
    sub $t1, $a1, $a0	# n - m
    add $t2, $a1, $a1	# n + n
    move $a0, $t0
    move $a1, $t1
    move $a2, $t2
    jal BAR
    move $s1, $v0		# q -> $s1

    # printf("p + q: %d\n", p + q);
    add $t0, $s0, $s1	# p + q

    la $a0, str_pq
    li $v0, 4
    syscall

    move $a0, $t0
    li $v0, 1
    syscall

    la $a0, nl
    li $v0, 4
    syscall

    # return p + q;
    add $v0, $s0, $s1

    # Epilogue
    lw $ra, 20($sp)
    lw $s0, 16($sp)
    lw $s1, 12($sp)
    addiu $sp, $sp, 24

    jr $ra

BAR:
    # return (b - a) << (c);
    # a -> $a0, b -> $a1, c -> $a2
    # Leaf procedure, doesn't need to save $ra
    sub $t0, $a1, $a0	# b - a
    sllv $v0, $t0, $a2	# (b - a) << c
    jr $ra
