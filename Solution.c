
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void Identation(int cnt) {
	
	for (int i = 0; i < cnt; i++)
		printf("\t");
}


int main(int argc, char **argv) { 
	
	int H, C, i, cid, maxH;
	char temp1[10], temp2[10], temp3[10];

	if (argc == 3 || argc == 4) {
		H = atoi(argv[1]);
		C = atoi(argv[2]);	
	}
	else {
		printf("Please provide valid inputs! Exiting..\n");
		exit(0);
	}


	if (argc == 3) {
		if (H < 0 || C < 0) {
			printf("Invalid Height or Child count!\n");
			exit (0);
		}
		else
			maxH = H;
	}
	else if (argc == 4) {
		if (H < 0 || C < 0) {
			printf("Invalid Height or Child count!\n");
			exit (0);
		}
		else
			maxH = atoi(argv[3]);
	}
		

	if(H >= 1) {
	
		Identation(maxH - H + 1);		
		printf("%d : Process starting\n", getpid()); 
		Identation(maxH - H + 1);	
		printf("%d : Parent's id = %d\n", getpid(), getppid()); 
		Identation(maxH - H + 1);	
		printf("%d : Height in the tree = %d\n", getpid(), H);		
		
		if (H > 1) {
			Identation(maxH - H + 1);	
			printf("%d : Creating %d children at height %d\n", getpid(), C, H-1);

			for (i = C; i >= 1; i--) {
			
				cid = fork();

				if(cid < 0) {			
					Identation(maxH - H + 1);	
					printf("\nError while forking..\n");		
					exit(1);
				}				

				if(cid == 0) {								
					Identation(maxH - H + 2);	
					printf("%d : I am child no. %d  of %d, at height %d\n", getpid(), C-i+1, getppid(), H-1);
					sprintf(temp1, "%d", H-1);
					sprintf(temp2, "%d", C);
					sprintf(temp3, "%d", maxH);
					char *args[]={"./Solution", temp1, temp2, temp3, NULL};
					execvp(args[0], args);
				}							
			}

			for (i = 1; i <= C && cid > 0; i++) {
				int status;
				int temp = wait(&status);
			}
		}			
	}
	
	Identation(maxH - H + 1);	
	printf("%d : Terminating at height %d\n", getpid(), H);	
	exit(0); 
}

