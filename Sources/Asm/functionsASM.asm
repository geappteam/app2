;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; Les directives ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	.def _AddEntierNonSigne32bits
	.def _AddEntierSigne32bits
	;.def _AddFractionnaire32bits_Q7.24_Q15.16
<<<<<<< HEAD
	;.def _SubEntierNonSigne32bits
=======
	.def _SubEntierNonSigne32bits
>>>>>>> 9ae696efe24bae88dc0d3a34d19ad5b25d3cc874
	.def _SubEntierSigne32
	.def _SubFlottant64bits
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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;_AddFractionnaire32bits_Q7.24_Q15.16
    ;.asmfunc


;    B B3
;    NOP 5
    ;.endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

<<<<<<< HEAD
;_SubEntierNonSigne32bits
;	.asmfunc

;	LDW *+A4[1],A3
;    LDW *+A4[0],B4
;    NOP 4

;	SUB A3, B4, B7:B6


;	B B3
;    NOP 5

;    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_SubEntierSigne32
	.asmfunc
=======
_SubEntierNonSigne32bits
    .asmfunc
	LDW *+A4[1], A3
	LDW *A4, B4
	NOP 4
>>>>>>> 9ae696efe24bae88dc0d3a34d19ad5b25d3cc874

	SUBU .L1 A3,B4,A5:A4

<<<<<<< HEAD
	SSUB A3, B4, B6
=======
    B B3
    NOP 5
    .endasmfunc
>>>>>>> 9ae696efe24bae88dc0d3a34d19ad5b25d3cc874

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_SubEntierSigne32
    .asmfunc

    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
<<<<<<< HEAD

_SubFlottant64bits
	.asmfunc

	LDW *+A4[1],B0
    LDW *+A4[0],A3
    NOP 4

	SUBDP B1:B0,A3:A2,A5:A4


	B B3
    NOP 5

    .endasmfunc













=======
>>>>>>> 9ae696efe24bae88dc0d3a34d19ad5b25d3cc874

_SubFlottant64bits
    .asmfunc

    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




