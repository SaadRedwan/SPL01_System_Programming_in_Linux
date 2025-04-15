#include <unistd.h>   
#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>  


int myecho_main(int argc, char** argv);


int main(int argc, char** argv)
{
	myecho_main(argc, argv);	
	return 0;
}

int myecho_main(int argc, char** argv) {
	
	int i, j;


	if(argc != 1)                    //if argv is empty or not
	{
		if(strcmp("-n", argv[1]) == 0 || strcmp("-nE", argv[1]) == 0 || strcmp("-En", argv[1]) == 0)
                {
                       	if(strcmp("-E", argv[2]) == 0)
                        {
                                i=3;
                        }
                        else if(strcmp("-e", argv[2]) != 0 || strcmp("-E", argv[2]) != 0)
                        {
                                i=2;
                        }

                        for(; i < argc; i++)             //loop on argv elements 
                        {
                                for(j=0; argv[i][j] != '\0'; j++)  //print one element
                                {
                                        putchar(argv[i][j]);       //print char in the element
                                }
                               if(i != (argc-1)) 
			       {	
					putchar(' ');                      // print space between elements if we have more than one srting seperated with spaces
			       }
                        }
                }
		else if(strcmp("-n", argv[1]) != 0 && strcmp("-e", argv[1]) != 0)        //to check if user using a flag for echo command
		{
			if(strcmp("-E", argv[1]) == 0)
			{
				i=2;
			}
			else
			{
				i=1;
			}

			for(; i < argc; i++)             //loop on argv elements 
			{
				for(j=0; argv[i][j] != '\0'; j++)  //print one element
				{
					putchar(argv[i][j]);       //print char in the element
				}
			        if(i != (argc-1))
                                {
                                        putchar(' ');                      // print space between elements if we have more than one srting seperated with spaces
                                }
			}
			putchar('\n');                           //new line to start shell line from new line
		}
		else if((strcmp("-e", argv[1]) == 0 || strcmp("-en", argv[1]) == 0 || strcmp("ne", argv[1]) == 0) || (strcmp("-n", argv[1]) == 0 && strcmp("-e", argv[2]) == 0))
		{                             
	                if(strcmp("-n", argv[2]) == 0 || strcmp("-e", argv[2]) == 0)
                        {
                                i=3;
                        }
                        else
                        {
                                i=2;
                        }
			

			for(; i < argc; i++) 
			{     
				for(j=0; argv[i][j] != '\0'; j++)
                        	{
                                	if (argv[i][j] == '\\' && argv[i][j+1] == 'n')
                                	{
                                		putchar('\n');
                                       		j++;
                              		}
                               		else
                                	{
                                 		putchar(argv[i][j]);
                                	}
                        	}
                                if(i != (argc-1))
                                {
                                        putchar(' ');                      // print space between elements if we have more than one srting seperated with spaces
                                }

			}
			if(strcmp("-en", argv[1]) != 0 || strcmp("ne", argv[1]) != 0 || strcmp("-n", argv[2]) != 0)
			{
				putchar('\n');
			}
		}
	}
	else
	{
		putchar('\n');        //print a new line if there is no elements in the argv
	}
	
	return 0;
}
