/* lookup table ASCII to MORSE.
   morse representation
	 dot .
	 dah -
	 NULL indicate no morse equivelent
*/
#include <stdlib.h>
#include <string.h>

static const char *morsetable[] = {
	/* nul */ NULL,
	/* soh */ NULL,
	/* stx */ NULL,
	/* etx */ NULL,
	/* eot */ NULL,
	/* enq */ NULL,
	/* ack */ NULL,
	/* bel */ NULL,
	/* bs  */ NULL,
	/* ht  */ NULL,
	/* lf  */ NULL,
	/* vt  */ NULL,
	/* ff  */ NULL,
	/* cr  */ NULL,
	/* so  */ NULL,
	/* si  */ NULL,
	/* dle */ NULL,
	/* dc1 */ NULL,
	/* dc2 */ NULL,
	/* dc3 */ NULL,
	/* dc4 */ NULL,
	/* nak */ NULL,
	/* syn */ NULL,
	/* etb */ NULL,
	/* can */ NULL,
	/* em  */ NULL,
	/* sub */ NULL,
	/* esc */ NULL,
	/* fs  */ NULL,
	/* gs  */ NULL,
	/* rs  */ NULL,
	/* us  */ NULL,

	/* ' ' */ NULL,
	/* '!' */ "-.-.--",
	/* '"' */ NULL,
	/* '#' */ NULL,
	/* '$' */ NULL,
	/* '%' */ NULL,
	/* '&' */ ".-...",
	/* ''' */ ".----.",
	/* '(' */ "-.--.",
	/* ')' */ "-.--.-",
	/* '*' */ NULL,
	/* '+' */ ".-.-.",
	/* ',' */ "--..--",
	/* '-' */ "-....-",
	/* '.' */ ".-.-.-",
	/* '/' */ "-..-.",
	/* '0' */ "-----",
	/* '1' */ ".----",
	/* '2' */ "..---",
	/* '3' */ "...--",
	/* '4' */ "....-",
	/* '5' */ ".....",
	/* '6' */ "-....",
	/* '7' */ "--...",
	/* '8' */ "---..",
	/* '9' */ "----.",
	/* ':' */ "---...",
	/* ';' */ "-.-.-.",
	/* '<' */ NULL,
	/* '=' */ "-...-",
	/* '>' */ NULL,
	/* '?' */ "..--..",
	/* '@' */ ".--.-.",
	/* 'A' */ ".-",
	/* 'B' */ "-...",
	/* 'C' */ "-.-.",
	/* 'D' */ "-..",
	/* 'E' */ ".",
	/* 'F' */ "..-.",
	/* 'G' */ "--.",
	/* 'H' */ "....",
	/* 'I' */ "..",
	/* 'J' */ ".---",
	/* 'K' */ "-.-",
	/* 'L' */ ".-..",
	/* 'M' */ "--",
	/* 'N' */ "-.",
	/* 'O' */ "---",
	/* 'P' */ ".--.",
	/* 'Q' */ "--.-",
	/* 'R' */ ".-.",
	/* 'S' */ "...",
	/* 'T' */ "-",
	/* 'U' */ "..-",
	/* 'V' */ "...-",
	/* 'W' */ ".--",
	/* 'X' */ "-..-",
	/* 'Y' */ "-.--",
	/* 'Z' */ "--..",
	/* '[' */ NULL,
	/* '~' */ NULL,
	/* ']' */ NULL,
	/* '^' */ NULL,
	/* '_' */ "..--.-",
	/* '@' */ ".--.-.",
	/* 'a' */ ".-",
	/* 'b' */ "-...",
	/* 'c' */ "-.-.",
	/* 'd' */ "-..",
	/* 'e' */ ".",
	/* 'f' */ "..-.",
	/* 'g' */ "--.",
	/* 'h' */ "....",
	/* 'i' */ "..",
	/* 'j' */ ".---",
	/* 'k' */ "-.-",
	/* 'l' */ ".-..",
	/* 'm' */ "--",
	/* 'n' */ "-.",
	/* 'o' */ "---",
	/* 'p' */ ".--.",
	/* 'q' */ "--.-",
	/* 'r' */ ".-.",
	/* 's' */ "...",
	/* 't' */ "-",
	/* 'u' */ "..-",
	/* 'v' */ "...-",
	/* 'w' */ ".--",
	/* 'x' */ "-..-",
	/* 'y' */ "-.--",
	/* 'z' */ "--..",
	/* '{' */ NULL,
	/* '|' */ NULL,
	/* '}' */ NULL,
	/* '~' */ NULL,
};


/* Rules
	 tick at transmission rate,
	 dit 1
   dah 111
   gap between dah-dit 0
   gap between letters 000
   gap between words   0000000
*/
const char *dot  = "10"; /* includes  gap */
const char *dash = "1110";
const char *lettersp = "00"; /* extra gap between letters */
const char *wordsp = "0000"; /* extra gap between words */

/* return the morse string for character c*/
const char *morsechar(int c){
	const char *m = NULL;
	if( c>=' ' && c<='~' ){
		m = morsetable[c];
	}
	return m;
}
