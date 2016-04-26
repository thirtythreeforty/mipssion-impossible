lbl_while:
	beq $zero $a1 lbl_do_return
	j lbl_noreturn
lbl_do_return:
	j lbl_return
lbl_noreturn:
	addi $a1 $a1 -1
	lw $t0 0($a0)
	blt $t0 $t1 lbl_else
	beq $t0 $t1 lbl_else
	srl $v0 $v0 3
	or $v1 $v1 $v0
	sw $t2 0($a0)
	j lbl_end_else
lbl_else:
	sll $v2 $v2 2
	xor $v3 $v3 $v2
	sw $t3 0($a0)
lbl_end_else:
	addi $a0 $a0 2
	j lbl_while
lbl_return:
	addi $zero $zero 0
	addi $zero $zero 0
	addi $zero $zero 0
	addi $zero $zero 0
lbl_halt:
	beq $zero $zero lbl_halt
