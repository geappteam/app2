;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; Les directives ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	.def _MpyEntierNonSigneOp32bitsRes64bits

	.data


	.text




_MpyEntierNonSigneOp32bitsRes64bits
	.asmfunc

	LDW *A4, A5
	LDW *+A4[1], B5

	ZERO A5 ;Clears the register
	NOP 3 	;LDW needs 4 delay slots

	;MPYI A3,B4,A4
	;NOP 8

	; La multiplication doit être décomposée en 4 opérations
	; MSB * LSB -> A0
	MPYHLU	.M1X A5, B5, A0

	; LSB * MSB -> B0
||	MPYLHU	.M2X A5, B5, B0

	; LSB * LSB -> B4
	MPYU	.M2X A5, B5, B4

	; Add the crossed terms together
||	ADDU 	.L1	A0, B0, A1:A0

	; MSB * MSB -> A5
	MPYHU 	.M1X A5, B5, A5

	; Generating LSB shifted result


	; Shift the term left


	B B3
	NOP 5
    .endasmfunc
