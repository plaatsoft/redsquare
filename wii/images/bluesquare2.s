.rodata
.balign 32
.globl pic6length
.globl pic6data

pic6length:	.long	picdataend - pic6data
pic6data:
.incbin "../images/bluesquare2.png"
picdataend:


