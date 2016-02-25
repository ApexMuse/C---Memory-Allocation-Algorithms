/*
 * 	nextFit.h
 *
 *  Created on: Nov 20, 2015
 *      Author: Scott Maner & Todd Twiggs
 */
#include <stdio.h>
 #include <time.h>

//Next Fit Algorithm
void nextFit(int numProcesses,int memSlot[10],int process[10],int numMemSlots) {

	int i, j, k, fit, originalStart=0, startPoint=0, unallocated=0;
	clock_t begin, end;
	double execTime;

	// Make a copy of the original memory slots
	int origMemory[numMemSlots];
	for(i=0; i<numMemSlots; i++) {
		origMemory[i] = memSlot[i];
	}

	// Display the memory slots
	printf("\nMemory Slots (and size): ");
	for(i=0; i<numMemSlots; i++) {
		printf("%d(%d)\t", i+1, memSlot[i]);
	}
	// Display the processes
	printf("\n   Processes (and size): ");
	for(i=0; i<numProcesses; i++) {
		printf("%d(%d)\t", i+1, process[i]);
	}
	printf("\n");

	begin = clock(); // Start the timer

	for(i=0; i<numProcesses; i++) {

		if(startPoint > numMemSlots-1){
			startPoint = 0;
			originalStart = j;
		}

		fit=0;

		// Search the array from the last starting point (which may be the very beginning)
		for(j=startPoint; j<numMemSlots; j++) {
			// If the process is smaller than the slot size, allocate it and adjust the slot size
			if(process[i] < memSlot[j]) {
				// Display where the process was allocated
				printf("\nProcess %d (size %d) allocated to memory slot %d (size %d). New slot size: %d\n", i+1, process[i], j+1, memSlot[j], memSlot[j] - process[i]);
				memSlot[j] = memSlot[j] - process[i];
				fit=1; // The process successfully fit into a memory slot
				startPoint = j+1; // Update the startPoint
				originalStart = j+1;
				break;
			}
			// If the process is the same size as the slot, allocate it and eliminate the slot
			else if(process[i] == memSlot[j]) {
				// Display where the process was allocated
				printf("\nProcess %d (size %d) allocated to memory slot %d (size %d). New slot size: %d\n", i+1, process[i], j+1, memSlot[j], memSlot[j] - process[i]);
				// Remove the memory slot from the array
				for(k=j; k<numMemSlots-1; k++) {
					memSlot[k] = memSlot[k+1];
				}
				fit=1; // The process successfully fit into a memory slot
				numMemSlots--; // Decrement the number of memory slots by 1
				startPoint = j+1; // Update the startPoint
				originalStart = j+1;
				break;
			}
		} // End of for loop

		/*
		 *	If there is no compatible memory slot for the process, go back to the beginning of the array
		 *	to resume the search.  Stop the search at the original starting point.
		 */
		if(fit == 0) {
			// Search the first portion of the array
			if (originalStart != 0) {
				for(j=0; j<startPoint; j++) {
					// If the process is smaller than the slot size, allocate it and adjust the slot size
					if(process[i] < memSlot[j]) {
						// Display where the process was allocated
						printf("\nProcess %d (size %d) allocated to memory slot %d (size %d). New slot size: %d\n", i+1, process[i], j+1, memSlot[j], memSlot[j] - process[i]);
						memSlot[j] = memSlot[j] - process[i];
						fit=1; // The process successfully fit into a memory slot
						startPoint = j+1; // Update the startPoint
						originalStart = j+1;
						break;
					}
					// If the process is the same size as the slot, allocate it and eliminate the slot
					else if(process[i] == memSlot[j]) {
						// Display where the process was allocated
						printf("\nProcess %d (size %d) allocated to memory slot %d (size %d). New slot size: %d\n", i+1, process[i], j+1, memSlot[j], memSlot[j] - process[i]);
						// Remove the memory slot from the array
						for(k=j; k<numMemSlots-1; k++) {
							memSlot[k] = memSlot[k + 1];
						}
						fit=1; // The process successfully fit into a memory slot
						numMemSlots--; // Decrement the number of memory slots by 1
						startPoint = j+1; // Update the startPoint
						originalStart = j+1;
						break;
					}
				} // End of for loop
			} // End of if statement

			if(fit == 0){
				printf("\n***Memory Slot Not Available for process %d (Size %d)\n",i+1,process[i]);
				unallocated++; // Increment the number of unallocated processes
			}
		}

	} // End of outer for loop

	// Calculate the total execution time
	end = clock(); // Get end time
	execTime = (double)(end - begin) / CLOCKS_PER_SEC;

	// Determine the number of unused memory slots & calculate remaining memory in used slots
	int unused=0, fragments=0;
	for(i = 0; i < numMemSlots; i++) {
		if((origMemory[i] - memSlot[i]) == 0) {
			unused++;
		}
		if(origMemory[i] > memSlot[i]) {
			fragments += memSlot[i];
		}
	}

	// Display the results
	printf("\n\n    Time of Execution:\t%g microseconds", execTime*1000000);
	printf("\nUnallocated Processes:\t%d", unallocated);
	printf("\n  Unused Memory Slots:\t%d", unused);
	printf("\n      Total Fragments:\t%d", fragments);

 } // End of function nextFit()
