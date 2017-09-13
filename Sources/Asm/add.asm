; This document contains addition asm funtions

	.def _AddEntierNonSigne32bits
	.def _AddEntierSigne32bits
	.def _AddFractionnaire32bits_Q7_24_Q15_16


	.data

	.text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_AddEntierNonSigne32bits
    .asmfunc

    LDW *+A4[1],A3
    LDW *+A4[0],B4
    MVKL 0xFFFFFFFF, A6
    MVKH 0xFFFFFFFF, A6
    NOP 2

    ADDU A3, B4, A5:A4
	MV A5, B0
    [B0] MV A6, A4	; return max if overflow

    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_AddEntierSigne32bits
    .asmfunc

    LDW *+A4[1],A3
    LDW *+A4[0],B4
    NOP 4

    ; Add Two Signed Integers With Saturation
    SADD A3, B4, A4

    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_AddFractionnaire32bits_Q7_24_Q15_16
    .asmfunc

    LDW *+A4[1],A3 ; Q15.16
    LDW *+A4[0],B4 ; Q7.24
    NOP 4

	ADDK .S2 128, B4
	SHR  .S1 B4, 8, A4

	SADD .L1 A4,A3,A4

    B B3
    NOP 5
    .endasmfunc
