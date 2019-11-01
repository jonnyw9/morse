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
char  mcode[1024];
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
				strcat(mcode, "\t"); /* use tabs an inter-word spaces */
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

char *morsetobinary(char *morse, char *binbuffer)
	for( c = mcode ; *c ; c++) {
		switch( *c ) {
			case '.': 
				strcat(onoff, dot);
				break;
			case '-':
				strcat(onoff, dash);
				break;
			case ' ':
				strcat(onoff, lettersp);
				break;
			case '\t':
				strcat(onoff, wordsp);
				break;
		}
	}
	return onoff;
}

void morseblink(void)
{
	static char *s = onoff;
	switch(*s++){
		case '0':
			red = 1;
			break;
		case '1':
			red = 0;
			break;
		case '\0':
			s = onoff;
			break;
	}
}

int main () {
    red = 1;
    green = 1;
    led_app_red = 1;
    led_app_green = 1;

    schInit();

	translate(message);

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

