; The subtraction ASM functions

	.def _SubEntierNonSigne32bits
	.def _SubEntierSigne32bits
	.def _SubFlottant64bits


	.data

	.text

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

	;Subtract Two Double-Precision Floating-Point Values
	SUBDP B1:B0,A3:A2,A5:A4

    B B3
    NOP 5
    .endasmfunc
