.data

#0002 Decl: result int
result: .space 4

#0023 Decl: result1 int
result1: .space 4

#0033 Decl: result2 int
result2: .space 4

newline: .asciiz "\n"

.text

#0000 Function: main
main:

#0001 BeginFunc 0


#0002 Decl: result int


#0003 _TEMP1 := 3
li $s0, 3
move $t0, $s0

#0004 PushParam _TEMP1
move $a0, $t0

#0005 _TEMP2 := FuncCall square 4
jal square
move $t1, $v0

#0006 result := _TEMP2
move $s1, $t1
sw $s1, result

#0007 _TEMP3 := result
la $s2, result
lw $s2, ($s2)
move $t2, $s2

#0008 PushParam _TEMP3
move $a0, $t2

#0009 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0010 _TEMP4 := 3
li $s3, 3
move $t3, $s3

#0011 PushParam _TEMP4
move $a0, $t3

#0012 _TEMP5 := 6
li $s4, 6
move $t4, $s4

#0013 PushParam _TEMP5
move $a1, $t4

#0014 _TEMP6 := FuncCall sum 8
jal sum
move $t5, $v0

#0015 result := _TEMP6
move $s5, $t5
sw $s5, result

#0016 _TEMP7 := result
la $s6, result
lw $s6, ($s6)
move $t6, $s6

#0017 PushParam _TEMP7
move $a0, $t6

#0018 FuncCall print_int 4
li $v0, 1
syscall
li $v0, 4
la $a0, newline
syscall

#0019 EndFunc
_end_main:
li $v0, 10     # set up for exit
syscall        # exit

#0020 Function: square
square:

#0021 BeginFunc 4
sw $fp, -4($sp)
sw $ra, -8($sp)
la $fp, 0($sp)
la $sp, -8($sp)
sw $a0, -4($sp)
la $sp, -4($sp)

#0022 PopParam x


#0023 Decl: result1 int


#0024 _TEMP8 := x * x
mul $t7, $a0, $a0

#0025 result1 := _TEMP8
move $s7, $t7
sw $s7, result1

#0026 _TEMP9 := result1
la $s0, result1
lw $s0, ($s0)
move $t8, $s0

#0027 return _TEMP9
move $v0, $t8
j _end_square

#0028 EndFunc
_end_square:
la $sp, 0($fp)
lw $ra, -8($sp)
lw $fp, -4($sp)
jr $ra   # return

#0029 Function: sum
sum:

#0030 BeginFunc 8
sw $fp, -4($sp)
sw $ra, -8($sp)
la $fp, 0($sp)
la $sp, -8($sp)
sw $a0, -4($sp)
la $sp, -4($sp)
sw $a1, -4($sp)
la $sp, -4($sp)

#0031 PopParam y


#0032 PopParam x


#0033 Decl: result2 int


#0034 _TEMP10 := x + y
add $t9, $a1, $a0

#0035 result2 := _TEMP10
move $s1, $t9
sw $s1, result2

#0036 _TEMP11 := result2
la $s2, result2
lw $s2, ($s2)
move $t0, $s2

#0037 return _TEMP11
move $v0, $t0
j _end_sum

#0038 EndFunc
_end_sum:
la $sp, 0($fp)
lw $ra, -8($sp)
lw $fp, -4($sp)
jr $ra   # return

