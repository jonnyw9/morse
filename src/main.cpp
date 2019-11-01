/*
 * Simple program to flash the LEDs
 *
 * Implemented using a time-triggered scheduler.
 *
 * DK - 08-June-2018
 */


#include <stdbool.h>
#include <stdint.h>
#include <scheduler.h>
#include <string.h>
#include <morse.h>
#include <mbed.h>

void led1ToggleTask(void);
void led2ToggleTask(void);


static DigitalOut red(LED_RED);
static DigitalOut green(LED_GREEN);
static DigitalOut led_app_red(D5);
static DigitalOut led_app_green(D9);

char message[] = "Hello World!"; /* message to send */
char morse[1024];
char onoff[1024]; /* buffer for string of 01 to control LED */

/* translated ASCII text message into Morse code
 * If the morse(char) function is used the morse will be represented
 * as .- 
 * You will need to indicate gaps between letters and words,
 * I suggest spaces and tabs respectively.
 *
 * parameters:
 *     char * message      string to convert
 *     char * morsebuffer  buffer into which morse is written
 *
 * returns:
 *     char *              pointer to converted morse, 
 */
char *texttomorse(char *messsage, char *morsebuffer)
{
	char *c;

	for( c=messsage ; *c ; c++ ){ /* c is current character in string */
		switch( *c ) {
			case ' ': /* a space */
				strcat(morsebuffer, "\t"); /* use tabs an inter-word spaces */
				break;
			default:
				const char *m = morsechar(*c);    /* lookup morse */
				if(m) { /* if morse code founfd */
					strcat(morsebuffer, m);   /* add to buffer */
					strcat(morsebuffer, " "); /* add inter-letter space */
				}
		}
	}
	return morsebuffer;
}

/* Translate morse in ascii into binary
 * input string is interpreted as follows:
 *   .  dot
 *   -  dash
 *  ' ' inter-letter space
 *  \t  inter-word space
 *
 * output string has
 *    0  off for time unit
 *    1   on for time unit
 *
 *  parameters:
 *      char * morse       morse string
 *      char * binbuffer   buffer for output
 *
 * return:
 *     char *         pointer to binbuffer
 */
char *morsetobinary(char *morse, char *binbuffer)
{
	char *c;
	for( c = morse ; *c ; c++) {
		switch( *c ) {
			case '.': 
				strcat(binbuffer, dot);  /* dot is define in the morse.h and morse.cpp */
				break;
			case '-':
				strcat(binbuffer, dash);
				break;
			case ' ':
				strcat(binbuffer, lettersp);
				break;
			case '\t':
				strcat(binbuffer, wordsp);
				break;
		}
	}
	return binbuffer;
}

/* Task for sending morse.
 * Uses the hard-wired buffer 'onoff' declared above.
 */
void morseblink(void)
{
	enum { on, off };
	static char *s = onoff;
	switch(*s++){
		case '0':
			red = off;
			break;
		case '1':
			red = on;
			break;
		case '\0':
			s = onoff;/* reset to beginning of buffer */
			break;
	}
}

int main () {
    red = 1;
    green = 1;
    led_app_red = 1;
    led_app_green = 1;

    schInit();

	texttomorse(message, morse);
	morsetobinary(morse, onoff);

    schAddTask(morseblink, 0, 200);
    schAddTask(led2ToggleTask, 500, 500);


    schStart();

    while (true) {
        schDispatch();
    }
}


void led1ToggleTask(void) {
    red = 1 - red;
}

void led2ToggleTask(void) {
    led_app_green = 1 - led_app_green;
}

