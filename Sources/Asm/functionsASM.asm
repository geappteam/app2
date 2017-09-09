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

	NOP 4 	;LDW needs 4 delay slots

	; La multiplication doit �tre d�compos�e en 4 op�rations

	; MSB * LSB -> A0
	MPYHLU	.M1X A5, B5, A0

	; LSB * MSB -> B0
||	MPYLHU	.M2X A5, B5, B0

	NOP

	; Add the crossed terms together
	ADDU 	.L2X A0, B0, B11:B10

	; LSB * LSB -> A1
||	MPYU	.M1X A5, B5, A1

	; Shift right LSB carriover -> B0
	SHRU	.S2 B10, 0x10, B0

	; Shift left LSB remainer -> A0
||	SHL 	.S1X B10, 0x10, A2

	; Sum of LSB terms
	ADDU	.L1 A2, A1, A5:A4

	; MSB * MSB -> B6
||	MPYHU 	.M2X A5, B5, B6

	; MSB shift -> B2
||	SHL		.S2 B11, 0x10, B2

	; Computing MSB term -> B6
	OR		.L2 B0, B2, B2
	ADD		.L2 B2, B6, B6

	; Compute total
	ADD		B6, A5, A5

	B B3
	NOP 5
    .endasmfunc
