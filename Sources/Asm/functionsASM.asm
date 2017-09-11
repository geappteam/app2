;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; Les directives ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	.def _AddEntierNonSigne32bits
	.def _AddEntierSigne32bits
	.def _AddFractionnaire32bits_Q7_24_Q15_16
	.def _MpyEntierNonSigneOp32bitsRes64bits
	.def _MpyEntierSigneOp32bitsRes64bits
	.def _SubEntierNonSigne32bits
	.def _SubEntierSigne32bits
	.def _SubFlottant64bits
	.def _DivIncrementation
	.def _DivSubc
	.def _DivFlottant32bits
	.def _MpyFlottant64bits



	.data


	.text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_AddEntierNonSigne32bits
    .asmfunc

    LDW *+A4[1],A3
    LDW *+A4[0],B4
    NOP 4

    ADDU A3, B4, A5:A4
	OR B0, A5, B0
    [B0] CLR A4,A4, A5
    [B0] MVKL 0xFFFFFFFF, A4


    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_AddEntierSigne32bits
    .asmfunc

    LDW *+A4[1],A3
    LDW *+A4[0],B4
    NOP 4



    SADD A3, B4, B5

    NOP 1

	MVC CSR, B6



    B B3
    NOP 5
    .endasmfunc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_AddFractionnaire32bits_Q7_24_Q15_16
    .asmfunc

    LDW *+A4[1],A3 ; Q15.16
    LDW *+A4[0],B4 ; Q7.24
    NOP 4

	ADDK	.S2	128,B4
	SHR .S1	B4,8,A4

	SADD .L1 A4,A3,A4

    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_SubEntierNonSigne32bits
    .asmfunc
	LDW *+A4[1], A3
	LDW *A4, B4
	NOP 4

	SUBU .L1 A3,B4,A5:A4

    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_SubEntierSigne32bits
    .asmfunc
	
    LDW *+A4[1],A3
    LDW *+A4[0],B4
    NOP 4

    SSUB B4, A3, A4

    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_SubFlottant64bits
    .asmfunc

	LDDW *+A4[0],B1:B0
	LDDW *+A4[1],A3:A2

	NOP 4

	SUBDP B1:B0,A3:A2,A5:A4



    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_DivSubc
    .asmfunc

    LDW *+A4[0],A1 ;Num
    LDW *+A4[1],A2 ;Den
    NOP 4

	MVK 1, A0

	LMBD A0, A1, A3
	LMBD A0, A2, A4

	;SUBU A4, A3, A0
	SUBU A4, A3, A7:A6

	;SHL A2, A0, A2
	SHL A2, A6, A2

	MV A1, A5
	MVK 0, A3

CSL:
	;SUBC A1, A2, A1
	SUBC A5, A2, A5

	ADD A3, 1, A3
	;CMPGTU A3, A0, A4
	CMPGTU A3, A6, A4

	;[!A4] B CSL
	[!A1] B CSL

	B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_MpyFlottant64bits
    .asmfunc

	LDDW *+A4[0],B1:B0
	LDDW *+A4[1],A3:A2

	NOP 4

	MPYDP B1:B0,A3:A2,A5:A4
	NOP 9



    B B3
    NOP 5
    .endasmfunc


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_DivFlottant32bits
	.asmfunc

	LDW *+A4[1], B1	; Divisor
	LDW *A4, A5
	NOP 4

	; Check if the divider is 0
	[!B1] B termDiv
	ZERO A4
	NOP 4

	; Check for same values
	CMPEQSP B1, A5, B2
	[B2] B termDiv
	ZERO A4
	MVKH 0x3f800000, A4
	NOP 3

	; Estimating the inverse divider
	RCPSP B1, B5

	; Increasing the accuracy with Newton-Raphson
	MPYSP B1, B5, B6
	ZERO B0
	MVKH 0x40000000, B0
	NOP
	SUBSP B0, B6, B7
	NOP 3
	MPYSP B5, B7, B5
	NOP 3
	; Another round for full accuracy
	MPYSP B1, B5, B6
	NOP 3
	SUBSP B0, B6, B7
	NOP 3
	MPYSP B5, B7, B5
	NOP 3

	; Performing the multiplication by 1/divider
	MPYSP B5, A5, A4
	NOP 3

termDiv:
	B B3
    NOP 5
	.endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_DivIncrementation
    .asmfunc

    LDW *+A4[1],A3
    NOP 5
    LDW *+A4[0],B2
    NOP 5
	MVK 0x00000000, A2
	NOP 5
	MVK 0x00000000, A1
	NOP 5


LOOP:

	SUB A3, B2, A3
	NOP 6
	ADD 1,A2,A2
	NOP 5
	CMPGT -1,A3,A1
	NOP 5
	[!A1] B LOOP
	NOP 5
	ADD -2,A2,A2


    B B3
    NOP 5
    .endasmfunc
