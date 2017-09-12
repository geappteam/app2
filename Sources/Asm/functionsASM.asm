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
	.def _EncrypterDonnees


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
    [B0] MV A6, A4

    B B3
    NOP 5
    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_AddEntierSigne32bits
    .asmfunc

    LDW *+A4[1],A3
    LDW *+A4[0],B4
    NOP 4

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

	; Loading the numbers from the array in the memory.
    LDW *+A4[0],A1 ;Num
    LDW *+A4[1],A2 ;Den
    NOP 4

	; Placing temporarily the numerator in an another register (A4).
	MV A1, A4

	; Verifying if the denominator is greater than the numerator.
	CMPGTU A2, A4, A1
	[A1] B Error   ; !A1 = No Error , A1 = Error.
	NOP 5

	; Verifying if the denominator is equal to 0.
	CMPEQ A2, 0, A1
	[A1] B Error   ; !A1 = No Error , A1 = Error.
	NOP 5

	; Verifying if the numerator is equal to 0.
	CMPEQ A4, 0, A1
	[A1] B Error   ; !A1 = No Error , A1 = Error.
	NOP 5

	MV A4, A1

	; Defining the value of the bit used (MSB), to search the number of zeroes on the left side of MSB.
	MVK 1, A0

	; Searching the number of zeroes on the left side of the MSB of the two numbers (num and den).
	LMBD A0, A1, A3
	LMBD A0, A2, A4

	; Verifying the difference of the number of zeroes of the num and den numbers
	SUBU A4, A3, A7:A6

	; Shifting on the left the denominator, for alignment purpose with numerator.
	SHL A2, A6, A2

	; Placing value of A1 (Num) in A5 because A1 will be use for conditional loop.
	MV A1, A4

	; Iterator set to 0 before conditional loop.
	MVK 0, A0

ConditionalSubLoop:
	; Performing substraction for division.
	SUBC A4, A2, A4

	; Incrementing iterator.
	ADD A0, 1, A0

	; Verifying if iterator at max wanted value.
	CMPGTU A0, A6, A1

	; Stops loop if number of iterations is equal to the number of shift done to denominator.
	[!A1] B ConditionalSubLoop
	NOP 5

	; Isolating the result
	MVK 32, A9
	SUB A9, A6, A10
	ADDK -1, A10
	SHL A4, A10, A4
	SHRU A4, A10, A4

	B B3
    NOP 5

Error:
	; Returning 0 (denominator is greater than the numerator OR denominator is equal to 0 OR numerator is equal to 0).
	MVK 0, A4

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

    LDW *+A4[1], B2	; Diviseur
    LDW *A4, B6
	ZERO A4
	ZERO A1
	MVKH 0x00000001, A2	; Write head
	MVKL 0x00000001, A2

	LMBD 1, B6, A5
||	LMBD 1, B2, B5
	SUB B5, A5, B4
	CMPGT B5, A5, B0
||  MV B4, A5
	[B0]SHL .S2 B2, B4, B2	; Shifting divider left
||	[B0]SHL .S1 A2, A5, A2	; Shifting write head left
	CMPGT B2, B6, B0
	[B0]SHRU B2, 1, B2	; Shifting divider
||	[B0]SHRU A2, 1, A2	; Shifting write head

Iteration:

	[!A2]B B3			; If the write head is flushed
||	[A2]B Iteration
||	[A2]SUB B6, B2, B6
||	[A2]ADD A2, A4, A4

	LMBD 1, B6, A5
||	LMBD 1, B2, B5
	SUB A5, B5, B4
||	SUB A5, B5, A5
	SHRU .S2 B2, B4, B2	; Shifting divider right
||	SHRU .S1 A2, A5, A2	; Shifting write head right
	CMPGT B2, B6, B0
	[B0]SHRU B2, 1, B2
||	[B0]SHRU A2, 1, A2


    .endasmfunc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
