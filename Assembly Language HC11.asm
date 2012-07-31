/* CMPE12 - Winter 2010
 * Herman Chin
 * hchin@ucsc.edu
 * Lab 7: Justin's section
 * March 7th, 2010
 * lab7.asm
 *
 * A simple program to show 3 distinct light patterns.
 * Pressing interrupt button to move from pattern to pattern.
 */

#include <v2_18g3.asm>

    		.sect .data
pattern:	.byte	0		// variable declaration
track:		.byte	0
sixteen:	.byte	0
greeting:	.asciz	"Welcome to my first HC11 program!!"

		.sect .text
main:	
		ldx	#greeting	// print out a greeting
		jsr	OUTSTRING	
		ldaa	#0
		ldab	#0
		addb	#15
		stab	sixteen		// set "sixteen" = 15
		ldx	#interrupt	// intialize user-defined interrupt vector
		stx	ISR_JUMP15
	
check:		ldab	pattern
		cmpb	#0
		BEQ	pattern1
check1:		clra
		clrb
		addb	#15
		stab	sixteen
		ldab	pattern
		cmpb	#1
		BEQ	pattern2
		ldab	pattern
		cmpb	#2
		BEQ	pattern3
		
interrupt:
       		ldab	pattern
		incb
		stab	pattern
		ldab	pattern
		cmpb	#3
		BEQ	isthree
		rti

isthree:	ldab	pattern
		subb	#3
		stab	pattern
		rti

// This is the first light pattern. The two LEDS in the middle light up first.
// Then the lights move outward until they reach the two outermost LEDS on each side.
// After that, the lights move inward until they reach the two LEDS in the middle.
// The pattern repeat. 

pattern1:	ldaa	#0b11100111
		staa	LEDS
		ldd	#0x80
		jsr	WAIT
		ldaa	#0b11011011
		staa	LEDS
		ldd	#0x80
		jsr	WAIT
		ldaa	#0b10111101
		staa	LEDS
		ldd	#0x80
		jsr	WAIT
		ldaa	#0b01111110
		staa	LEDS
		ldd	#0x80
		jsr	WAIT
		ldaa	#0b10111101
		staa	LEDS
		ldd	#0x80
		jsr	WAIT
		ldaa	#0b11011011
		staa	LEDS
		ldd	#0x80
		jsr	WAIT
		jmp	check

// This is the second light pattern. The light pattern count 1 to 15 in binary

pattern2:	adda	#1
		coma
		staa	LEDS
		psha
		ldd	#0x80
		jsr	WAIT
		pula
		coma
		ldab	sixteen
		decb
		stab	sixteen
		jmp	pattern21

pattern21:	ldab	sixteen
		cmpb	#0
		BEQ	check1
		jmp	pattern2

// This is the third light pattern. It starts of with the first light on the right turn off.
// Then the second light will turn off. And then the third light will turn off. And so on,
// until it reach the left most LEDS and the cycle repeat from the rightmost LEDS.
		
pattern3:	ldaa	#0
		ldab	#0
		addb	#7
		stab	track
		adda	#1
		staa	LEDS
		psha
		ldd	#0x80
		jsr	WAIT
		pula
pattern31:	asla	
		staa	LEDS
		psha
		ldd	#0x80
		jsr	WAIT
		pula
		jmp	check3

check3:		ldab	track
		subb	#1
		BEQ	check
		stab	track
		jmp	pattern31
