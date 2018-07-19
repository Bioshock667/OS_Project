noop !largest 16bit pos number
noop !lowest 16 bit neg number
read 0
store 0 0
read 0
store 0 1
jump 35
getstat 1 !line 7: Carry and Overflow print
andi 1 1 !get the value of the carry bit
write 1 !output carry bit
getstat 1
shr 1
shr 1
shr 1
shr 1 !+4
andi 1 1
write 1 !output overflow bit
write 0 !output result of operation
return
getstat 1 !line 19: G,E,L print
shr 1 1
andi 1 1
write 1 !output greater than flag
getstat 1
shr 1 1
shr 1 1
andi 1 1
write 1 !output equal flag
getstat 1
shr 1 1
shr 1 1
shr 1 1
andi 1 1
write 1 !output less than flag
return
load 0 0 !line 35 case 1: add two pos numbers and OF and C flag should be set to 1 as a result
addi 0 1
call 7 
load 0 1 !case 2: add two neg numbers and OF flag should be set to 1
addi 0 -2 
call 7
load 0 0 !case 3: sub a pos with a neg
subi 0 -2
call 7
load 0 1 !case 4: sub a neg with a pos
subi 0 -1
call 7
!Now checking G, E, L Flags
loadi 0 5
compri 0 6
call 19
compri 0 5
call 19
compri 0 4
call 19
halt

