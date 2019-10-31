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

char message[] = "Hello World!";
char onoff[1024];

char *translate(char *)
{
	char *c;
	char  mcode[1024];

	for( c=message ; *c ; c++ ){ /* c is current character in string */
		switch( *c ) {
			case ' ': /* a space */
				strcat(mcode, "\t"); /* use tabs an inter-word spaces */
				break;
			default:
				const char *m = morse(*c);    /* lookup morse */
				if(m) { /* if morse code founfd */
					strcat(mcode, m);   /* add to buffer */
					strcat(mcode, " "); /* add inter-letter space */
				}
		}
	}

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

