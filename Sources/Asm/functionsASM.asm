;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; Les directives ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	.def _MpyEntierNonSigneOp32bitsRes64bits

	.data


	.text


_MpyEntierNonSigneOp32bitsRes64bits
	.asmfunc

	LDW *A4, A3
	LDW *+A4[1], B4

	ZERO A5 ;Clears the register
	NOP 3 	;LDW needs 4 delay slots

	MPYI A3,B4,A4
	NOP 8

	B B3
	NOP 5
    .endasmfunc
