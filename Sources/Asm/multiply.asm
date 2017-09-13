; This document contains the multiplication assembly functions

	.def _MpyEntierNonSigneOp32bitsRes64bits
	.def _MpyEntierSigneOp32bitsRes64bits
	.def _MpyFlottant64bits

	.data

	.text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_MpyEntierNonSigneOp32bitsRes64bits
	.asmfunc

	LDW *A4, A6
	LDW *+A4[1], B5

	NOP 4 	;LDW needs 4 delay slots

	; The multiplication is split into 4

	; MSB * LSB -> A0
	MPYHLU	.M1X A6, B5, A0

	; LSB * MSB -> B0
||	MPYLHU	.M2X A6, B5, B0

	NOP

	; Add the crossed terms together
	ADDU 	.L2X A0, B0, B11:B10

	; LSB * LSB -> A1
||	MPYU	.M1X A6, B5, A1

	; Shift right LSB carriover -> B0
	SHRU	.S2 B10, 0x10, B0

	; Shift left LSB remainer -> A0
||	SHL 	.S1X B10, 0x10, A0

	; Sum of LSB terms
	ADDU	.L1 A0, A1, A5:A4

	; MSB * MSB -> B6
||	MPYHU 	.M2X A6, B5, B6

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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_MpyEntierSigneOp32bitsRes64bits
	.asmfunc

	LDW *A4, A0
	LDW *+A4[1], B0
	NOP 4

	MPYID A0, B0, A5:A4
	NOP 9

	B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_MpyFlottant64bits
    .asmfunc

	LDDW *+A4[0],B1:B0
	LDDW *+A4[1],A3:A2

	NOP 4

	;Multiplier two Double-Precision Floating-Point Values
	MPYDP B1:B0,A3:A2,A5:A4
	NOP 9



    B B3
    NOP 5
    .endasmfunc
