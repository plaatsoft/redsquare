.rodata
.balign 32
.globl pic1length
.globl pic1data

pic1length:	.long	picdataend - pic1data
pic1data:
.incbin "../images/logo1.jpg"
picdataend:


