;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; Les directives ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	.def _AddEntierNonSigne32bits
	.def _AddEntierSigne32bits
	;.def _AddFractionnaire32bits_Q7.24_Q15.16
	.def _SubEntierNonSigne32bits
	.def _SubEntierSigne32
	.def _SubFlottant64bits
	.def _MpyEntierNonSigneOp32bitsRes64bits
	.def _MpyFlottant64bits

	.data


	.text

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

    ;MVC CSR, B6



    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_MpyEntierNonSigneOp32bitsRes64bits
	.asmfunc

	LDW *A4, A5
	LDW *+A4[1], B5

	NOP 4 	;LDW needs 4 delay slots

	; La multiplication doit être décomposée en 4 opérations

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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;_AddFractionnaire32bits_Q7.24_Q15.16
    ;.asmfunc


;    B B3
;    NOP 5
    ;.endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

_SubEntierSigne32
    .asmfunc
	
    LDW *+A4[1],A3
    LDW *+A4[0],B4
    NOP 4

    SSUB A3, B4, B6

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


