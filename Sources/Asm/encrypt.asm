; La fonction d'encryption ASM

	.def _EncrypterDonnees

	.data

	.text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_EncrypterDonnees
	.asmfunc

	; Context protection CSR & AMR
	MVC	CSR, B5
	MVC	AMR, B6

	MVKH 0x00000003, A1	; Load number of iterations
||	MVKH 0xFFFFFFFF, B0	; Load cryptographic key
	MVKL 0x00000003, A1
||	MVKL 0xFFFFFFFF, B0

	; Setting up cicular addressing
	MVKL 0x00040001,A7
	MVKH 0x00040001,A7
	MVC A7,AMR

NextEncryption:
	LDW *A4++, B8
	SHL A4, 27, B1		; Determiner si la fin du block est atteinte
	[!B1] SUB A1, 1, A1
	NOP 2

	XOR B8, B0, B8

	[A1] B NextEncryption
	STW B8, *-A4[1]
	NOP 4

	; Restauration of context
	MVC B6, AMR
	MVC B5, CSR

	B B3
	NOP 5
	.endasmfunc
