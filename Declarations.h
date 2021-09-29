/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

#include <stdint.h>

#define _XTAL_FREQ 20000000

#define select RB4
#define menu RA4
#define up RB5
#define enter RD3
#define reset RD2

#define encoderA RB7
#define encoderB RB6

#define relay2 RE2
#define relay1 RE1

#define A RA2
#define C RA1
#define B RA0
#define D RA3

#define DATA RB1
#define STROBE RB2
#define CLK RB3

#define tk_password 9876

#define dispDelay 1

#define bit_test(d, b) (d & (1<<b))

#define pi UINT32_C(3.14)

uint8_t segCode[10] = {
  0xD7,  // 0
  0x14,  // 1
  0xCE,  // 2
  0x5E,  // 3
  0x1D,  // 4
  0x5B,  // 5
  0XDB,  // 6
  0X16,  // 7
  0XDF,  // 8
  0X1F   // 9
};

const uint8_t FONT_DEFAULT[] = {
    
   //ed.cgbaf
  0b00000000, // (32)  <space>
  0b10000110, // (33)	!
  0b00100010, // (34)	"
  0b01111110, // (35)	#
  0b01101101, // (36)	$
  0b00000000, // (37)	%
  0b00000000, // (38)	&
  0b00000010, // (39)	'
  0b00110000, // (40)	(
  0b00000110, // (41)	)
  0b01100011, // (42)	*
  0b00000000, // (43)	+
  0b00000100, // (44)	,
  0b01000000, // (45)	-
  0b10000000, // (46)	.
  0b01010010, // (47)	/
  0b00111111, // (48)	0
  0b00000110, // (49)	1
  0b01011011, // (50)	2
  0b01001111, // (51)	3
  0b01100110, // (52)	4
  0b01101101, // (53)	5
  0b01111101, // (54)	6
  0b00100111, // (55)	7
  0b01111111, // (56)	8
  0b01101111, // (57)	9
  0b00000000, // (58)	:
  0b00000000, // (59)	;
  0b00000000, // (60)	<
  0b01001000, // (61)	=
  0b00000000, // (62)	>
  0b01010011, // (63)	?
  0b01011111, // (64)	@
  0b10011111, // (65)	A
  0b01111111, // (66)	B
  0b11000011, // (67)	C
  0b00111111, // (68)	D
  0b01111001, // (69)	E
  0b10001011, // (70)	F
  0b00111101, // (71)	G
  0b10011101, // (72)	H
  0b00000110, // (73)	I
  0b00011111, // (74)	J
  0b01101001, // (75)	K
  0b11000001, // (76)	L
  0b00010101, // (77)	M
  0b00110111, // (78)	N
  0b00111111, // (79)	O
  0b10001111, // (80)	P
  0b01100111, // (81)	Q
  0b00110001, // (82)	R
  0b01011011, // (83)	S
  0b01111000, // (84)	T
  0b00111110, // (85)	U
  0b00101010, // (86)	V
  0b00011101, // (87)	W
  0b01110110, // (88)	X
  0b01101110, // (89)	Y
  0b01011011, // (90)	Z
  0b00111001, // (91)	[
  0b01100100, // (92)	\ (this can't be the last char on a line, even in comment or it'll concat)
  0b00001111, // (93)	]
  0b00000000, // (94)	^
  0b00001000, // (95)	_
  0b00100000, // (96)	`
  0b01011111, // (97)	a
  0b01111100, // (98)	b
  0b11001000, // (99)	c
  0b11011100, // (100)	d
  0b11001111, // (101)	e
  0b00110001, // (102)	f
  0b01101111, // (103)	g
  0b01110100, // (104)	h
  0b00010000, // (105)	i
  0b00001110, // (106)	j
  0b01110101, // (107)	k
  0b00110000, // (108)	l
  0b01010101, // (109)	m
  0b01010100, // (110)	n
  0b11011000, // (111)	o
  0b01110011, // (112)	p
  0b01100111, // (113)	q
  0b10001000, // (114)	r
  0b01101101, // (115)	s
  0b11001001, // (116)	t
  0b11010000, // (117)	u
  0b00101010, // (118)	v
  0b00011101, // (119)	w
  0b01110110, // (120)	x
  0b01101110, // (121)	y
  0b01000111, // (122)	z
  0b01000110, // (123)	{
  0b00000110, // (124)	|
  0b01110000, // (125)	}
  0b00000001, // (126)	~
};

volatile uint8_t currentDisplay = 0,last = 0,currentStateCLK,lastPortB;
volatile uint32_t currentClothLength = 1234,actualClothLength = 56789,pulse = 4,circumference = 500,password = 0,previousCurrentClothLength = 0;
volatile uint32_t warningClothLength = 97654,resetCounter = 0,hourMeter = 0;
volatile uint32_t rpm = 123,metrePerMin = 0,metrePerMinCounter = 0;
volatile uint8_t viewMenuPointer = 0,editMenuPointer = 0;
volatile __bit enterFlag = 0,menuFlag = 0,upFlag = 0,selectFlag = 0,resetFlag = 0,encoderFlag = 0,encoderFlag1 = 0,changed;
volatile uint8_t editValue = 0,blinkValue = 0,count;
volatile uint8_t timerCount = 0,skipCount = 0,n;
volatile uint32_t countingPulse = 0;
volatile int rpmCounter = 0,currentClothLengthBalancePlus = 0,currentClothLengthBalanceMinus = 0,encoderSkipCount = 0;
volatile uint16_t hourMeterCounter = 0;