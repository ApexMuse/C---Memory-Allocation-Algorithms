/*
 * FirstFit.c
 *
 *  Created on: Nov 18, 2015
 *      Author: Todd Twiggs
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "firstFit.h"
#include "nextFit.h"
#include "worstFit.h"
#include "bestFit.h"

#define SIZE 10

int main() {

	int *memSlot, *processRand, *processLH, *processHL, *tempArray;
	int numMemSlots=SIZE, numProcesses=SIZE, selection;

	memSlot = (int *)malloc(sizeof(int)*SIZE);
	processRand = (int *)malloc(sizeof(int)*SIZE);
	processLH = (int *)malloc(sizeof(int)*SIZE);
	processHL = (int *)malloc(sizeof(int)*SIZE);
	tempArray = (int *)malloc(sizeof(int)*SIZE);

	int i,j, temp;

	// Create random sized memory slots
	for(i=0; i<SIZE; i++) {
		memSlot[i] = rand() % 500 + 1;
	}

	// Create a random array of processes
	for(i=0; i<SIZE; i++) {
		processRand[i] = rand() % 500 + 1;
		processLH[i] = processRand[i];
		processHL[i] = processRand[i];
	}

	// Order the processes from low to high
	for(i = 0; i < SIZE; i++) {
		for (j = i + 1; j < SIZE; ++j) {
			if (processLH[i] > processLH[j]) {
				temp = processLH[i];
				processLH[i] = processLH[j];
				processLH[j] = temp;
			}
		}
	}

	// Order the processes from high to low
	for (i = 0; i < SIZE; ++i) {
		for (j = i + 1; j < SIZE; ++j) {
			if (processHL[i] < processHL[j]) {
				temp = processHL[i];
				processHL[i] = processHL[j];
				processHL[j] = temp;
			}
		}
	}

	// Get menu selection from user
	do {
		printf("\n\n-----------------MENU-----------------\n"
				"1.  First Fit - Random Size Requests\n"
				"2.  First Fit - Increasingly Larger Requests\n"
				"3.  First Fit - Decreasingly Smaller Requests\n"
				"4.  Best Fit  - Random Size Requests\n"
				"5.  Best Fit  - Increasingly Larger Requests\n"
				"6.  Best Fit  - Decreasingly Smaller Requests\n"
				"7.  Next Fit  - Random Size Requests\n"
				"8.  Next Fit  - Increasingly Larger Requests\n"
				"9.  Next Fit  - Decreasingly Smaller Requests\n"
				"10. Worst Fit - Random Size Requests\n"
				"11. Worst Fit - Increasingly Larger Requests\n"
				"12. Worst Fit - Decreasingly Smaller Requests\n"
				"13. EXIT PROGRAM\n\n"
				"Please Enter Your Choice: ");
		scanf("%d", &selection);

		for(i=0; i<numMemSlots; i++) {
			tempArray[i]=memSlot[i];
		}

		switch(selection) {
			case 1:  firstFit(numProcesses,tempArray,processRand,numMemSlots);
                 	 break;
			case 2:  firstFit(numProcesses,tempArray,processLH,numMemSlots);
			         break;
			case 3:  firstFit(numProcesses,tempArray,processHL,numMemSlots);
			         break;
			case 4:  bestFit(numProcesses,tempArray,processRand,numMemSlots);
                 	 break;
			case 5:  bestFit(numProcesses,tempArray,processLH,numMemSlots);
			         break;
			case 6:  bestFit(numProcesses,tempArray,processHL,numMemSlots);
			         break;
			case 7:  nextFit(numProcesses,tempArray,processRand,numMemSlots);
                 	 break;
			case 8:  nextFit(numProcesses,tempArray,processLH,numMemSlots);
			         break;
			case 9:  nextFit(numProcesses,tempArray,processHL,numMemSlots);
				     break;
			case 10: worstFit(numProcesses,tempArray,processRand,numMemSlots);
                 	 break;
            case 11: worstFit(numProcesses,tempArray,processLH,numMemSlots);
                 	 break;
            case 12: worstFit(numProcesses,tempArray,processHL,numMemSlots);
                 	 break;
			case 13:  exit(0);
			default: printf("\n***** Invalid Selection! Try Again. *****");
		} // End of switch statement
	} while(selection != 13);

	free (memSlot);
	free (processRand);
	free (processLH);
	free (processHL);
	free (tempArray);

	return 0;

} // End of main()
