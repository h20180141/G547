#include <stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include<string.h>

#define ACCL_X "/dev/x_axis"
#define ACCL_Y "/dev/y_axis"
#define ACCL_Z "/dev/z_axis"


int main()
{
	int fd;
	char n;
	uint16_t val;
      cat:  printf("Enter	-->'x' for X_axis acceleration \n\t-->'y' for Y_axis acceleration \n\t-->'z' for Z_axis acceleration \n\t-->'e' for EXIT : \n");
	scanf("%c",&n);

	switch(n)
	{
		case 'x':
			fd = open(ACCL_X,O_RDWR);
			if(fd  == -1)
	  		{
	 
	    			printf("give 777 permission for file %s \n",ACCL_X);
	  			exit(-1);
	  		}
		
			read(fd,&val,2);
			printf("X_Axis Acceleration is : %d\n",val);
			break;
		case 'y': 
			fd = open(ACCL_Y,O_RDWR);
			if(fd  == -1)
	  		{
	 
	    			printf("give 777 permission for file %s \n",ACCL_Y);
	  			exit(-1);
	  		}
		
			read(fd,&val,2);
			printf("Y_Axis Acceleration is : %d\n",val);
			break;
		case 'z': 
			fd = open(ACCL_Z,O_RDWR);
			if(fd  == -1)
	  		{
	 
	    			printf("give 777 permission for file %s \n",ACCL_Z);
	  			exit(-1);
	  		}
		
			read(fd,&val,2);
			printf("Z_Axis Acceleration is : %d\n",val);
			break;
		case 'e':
			close(fd); 
			return 0;
			
		default :
			printf("enter valid command... \n");
	  		exit(-1);
			break;
	}


	close(fd); 
	return 0;
}



