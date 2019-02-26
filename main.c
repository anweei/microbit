#include <stdio.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"


int main() {
	
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	//Configure A-button event
	GPIOTE->CONFIG[0] = (2 << 16) | (17 << 8) | 1; //Polarity = HiToLo | PSEL = 17 | Mode = Event 

	//configure led-pin tasks
	GPIOTE->CONFIG[1] = (0 << 20) | (3 << 16)| (13 << 8) | 3; //OUTINIT = 0 | Polarity = toggle | PSEL = 13 | Mode = Task 
	GPIOTE->CONFIG[2] = (0 << 20) | (3 << 16)| (14 << 8) | 3; //OUTINIT = 0 | Polarity = toggle | PSEL = 14 | Mode = Task 
	GPIOTE->CONFIG[3] = (0 << 20) | (3 << 16)| (15 << 8) | 3; //OUTINIT = 0 | Polarity = toggle | PSEL = 15 | Mode = Task 

	PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);

	PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);

	PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);

	PPI->CHENSET = (1 << 0) | (1 << 1) | (1 << 2);



	return 0;
}
