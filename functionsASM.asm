;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; Les directives ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	.def _Addition8IntASM
	.def _AdditionFloatASM

	.data


	.text

_Addition8IntASM
    .asmfunc

	ADD	.L1	A4,B4,A4
	ADD	.L1	A4,A6,A4
	ADD	.L1	A4,B6,A4
	ADD	.L1	A4,A8,A4
	ADD	.L1	A4,B8,A4
	ADD	.L1	A4,A10,A4
	ADD	.L1	A4,B10,A4

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5

    .endasmfunc

_AdditionFloatASM
    .asmfunc

	MVKL 0x3f000000, B4
	MVKH 0x3f000000, B4
	ADDSP .L1 A4,B4,A4

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5

    .endasmfunc

_AddSatureASM
	.asmfunc

	ADD	.L1	A4,B4,A4

	.endasmfunc
