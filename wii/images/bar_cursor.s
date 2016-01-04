.rodata
.balign 32
.globl pic18length
.globl pic18data

pic18length:	.long	picdataend - pic18data
pic18data:
.incbin "../images/bar_cursor.png"
picdataend:


