#include <stdio.h>
#include <stdlib.h> // For exit() function
int main()
{
    char c[2];
    FILE *fptr1;
    FILE *fptr2;
    int n;
    int dc;
    float temp;
    do{
  cat:  printf("\n\nEnter 1: PRESSURE    : \n      2: TEMPERATURE : \n      3: EXIT        :\n");
    scanf("%d",&n);
    


  switch(n)
 {

   case 1:
	    if ((fptr1 = fopen("/sys/bus/i2c/drivers/bmp085/1-0077/pressure0_input", "r")) == NULL)
	    {
	        printf("Error! opening file");
	        // Program exits if file pointer returns NULL.
	        exit(1);         
    	    }

	    fscanf(fptr1,"%[^\n]", c);
	
	    printf("BAROMETRIC PRESSURE in (milli pascal) :\n%s", c);

    	    fclose(fptr1);
            break;
	      
   case 2:if ((fptr2 = fopen("/sys/bus/i2c/drivers/bmp085/1-0077/temp0_input", "r")) == NULL)
	    {
	        printf("Error! opening file");
	        // Program exits if file pointer returns NULL.
	        exit(1);         
    	    }


	    fscanf(fptr2,"%[^\n]", c);
	    sscanf(c,"%d",&dc);
            temp = dc/10.0;
	    printf("TEMPERATURE (degree) :\n%.1f", temp);
    	    fclose(fptr2);
	    break;

    case 3:printf("\nTHANK YOU \n");
          break;
	    
   default : printf("ENTER PROPER CHOICE \n");
             n =1;
             break;
		

}
    
}while(n!=3);
    
    return 0;
}