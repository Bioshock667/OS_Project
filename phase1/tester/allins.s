! 		 op:rd:i:[rs|addr|const][:unused]
load 0 1  	!00000:00:0:00000001#
loadi 0 1 	!00000:00:1:00000001#
loadi 2 -123    !00000:10:1:10000101
store 0 1	!00001:00:1:00000001#
add 0 1		!00010:00:0:01:000000#
addi 0 1	!00010:00:1:00000001#
addc 0 1	!00011:00:0:01:000000#
addci 0 1	!00011:00:1:00000001#
sub 0 1		!00100:00:0:01:000000#
subi 0 1	!00100:00:1:00000001#
subc 0 1	!00101:00:0:01:000000
subci 0 1	!00101:00:1:00000001
and 0 1		!00110:00:0:01:000000
andi 0 1	!00110:00:1:00000001
xor 0 1		!00111:00:0:01:000000
xori 0 1	!00111:00:1:00000001
compl 0		!01000:00:0:00000000
shl 0		!01001:00:0:00000000
shla 0		!01010:00:0:00000000
shr 0		!01011:00:0:00000000
shra 0		!01100:00:0:00000000
compr 0 1	!01101:00:0:01:000000
compri 0 1	!01101:00:1:00000001
getstat 0	!01110:00:0:00000000
putstat 0	!01111:00:0:00000000
jump 0		!10000:00:1:00000000
jumpl 0		!10001:00:1:00000000
jumpe 0		!10010:00:1:00000000
jumpg 0		!10011:00:1:00000000
call 0		!10100:00:1:00000000
return		!10101:00:0:00000000
read 0		!10110:00:0:00000000
write 0		!10111:00:0:00000000
halt		!11000:00:0:00000000
noop		!11001:00:0:00000000
