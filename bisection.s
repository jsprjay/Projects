// Jasper Tumbokon
// I pledge my honor that I have abided by the Stevens Honor System.

.text
.global _start
.extern printf

function:
	MOV X18, #8			// X18 = 8
	LDR D20, [X10, #0]	// constantly add to this number to get result
	MOV X21, #1			// X21 = 1
l1:	CMP X21, X11		// check if it hits the highest coeff
	B.GT end			// if so, end
	MOV X22, #1			// X22 = 1
	FMOV D25, D19		// set D25 = x
l2:	CMP X22, X21		// check if looped enough times to get the exact power
	B.GE mo				// if so move on
	FMUL D25, D25, D19	// multiply by x to get the power to whatever number is needed
	ADD X22, X22, #1	// add to counter
	B l2				// loop back
mo: MUL X24, X21, X18	// multiply coeffby 8 to get the arr value
	LDR D24, [X10, X24]	// get the coeff from the array
	FMUL D23, D24, D25	// multiply coeff and the x^whatever power
	FADD D20, D20, D23	// add the answer to the total
	ADD X21, X21, #1	// add to counter
	B l1				// loop back to coeff loop
end:RET					// return to next line after bl

_start:
	MOV X18, #0			// set X18 = 0
	SCVTF D18, X18		// convert int to real#
	FMOV D17, #-1		// set D17 = -1
	ADR X8, a 			// load address of a to register X0
	ADR X9, b			// load address of b to register X1
	ADR X10, coeff		// load address of coeff to reg X10
	ADR X11, N			// load address of N to reg X11
	ADR X12, tol		// load address of tol to X12
	LDR D12, [X12]		// load data of tol to D12
	LDR X11, [X11]		// load data of N to D11
	LDR D8, [X8]		// load data of a to D8
	LDR D9, [X9]		// load data of b to D9
	FMOV D14, #2		// set D14 = 2
re:	FADD D10, D8, D9	// D10 = a + b
	FDIV D10, D10, D14	// D10 = D10 / 2
	FMOV D19, D10		// D19 = c
	BL function			// branch w link to function to get f(c) = D20
	FCMP D20, D12		// compare f(c) to tolerance
	B.GT sk				// if greater than, skip check
	FMUL D16, D12, D17	// -t = tol * -1
	FCMP D16, D20		// compare -t to f(c)
	B.LT exit			// if less than, its less that the tolerance so we exit
sk:	FMOV D21, D20		// make sub holder for f(c) to make room for f(a)
	FCMP D20, D18		// compare f(C) and 0
	B.EQ exit			// if equal, we found the root so exit
	FMOV D19, D8		// move a into the fuction call variable
	BL function			// branch w link to function to get f(c)
	FCMP D20, D18		// compare f(a) and 0
	B.GT gt				// if pos then jump to greater than
	B.LT lt				// if neg then jump to less than
gt: FCMP D21, D18		// compare f(c) and 0
	B.GT ea				// if pos then a <- c
	B.LT eb				// if neg then b <- c
lt: FCMP D21, D18		// compare f(c) and 0
	B.GT eb				// if pos then b <- c
ea:	FMOV D8, D10		// a <- c
	B go				// jump to loop
eb:	FMOV D9, D10		// b <- c
go: B re				// loop back to beginning

exit:
	ADR X0, outstr		// load address of outstr to X0
	FMOV D0, D20		// move f(c) to D0 to print
	BL printf			// print
	ADR X0, outstr1		// load address if outstr1 to X0
	FMOV D0, D10		// move c to D0 to print
	BL printf			// print
	MOV X0, 0			/* status := 0 */
	MOV	X8, 93			/* exit is syscall #1 */
	SVC	0				/* invoke syscall */

.data
coeff:		.double	5.3, 0.0, 2.9, -3.1
a:			.double 0
b:			.double 2
tol:		.double 0.0001
N:			.dword	3
outstr:		.string	"f(c) = %lf\n"
outstr1:	.string "c = %lf\n"
