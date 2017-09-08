;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; Les directives ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	.def _AddEntierNonSigne32bits
	.def _AddEntierSigne32bits
	;.def _AddFractionnaire32bits_Q7.24_Q15.16
	.data


	.text

_AddEntierNonSigne32bits
    .asmfunc

    LDW *+A4[1],A3
    LDW *+A4[0],B4
    NOP 4

    SADD A3, B4, B5

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


    B B3
    NOP 5

    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;_AddFractionnaire32bits_Q7.24_Q15.16
    ;.asmfunc



    ;.endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_SubEntierNonSigne32bits
	.asmfunc

	LDW *+A4[1],A3
    LDW *+A4[0],B4
    NOP 4

	SUB A3, B4, B10:B11


	B B3
    NOP 5

    .endasmfunc








