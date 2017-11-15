#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*This is a simple book register, dynamically allocated every time the user call the function 'book()'. In the main function few examples of testing*/

char *start[0];
int dim=0;

void destroy()				//local function, better not to call it in the main
{
	int i;
	if(dim!=0)
	{
		for(i=0;i<dim;i++)
		{
			free(start[i]);
		}
		dim=0;
	}

}



void newBook(int n)			//creation of a new register, if one already exist, newBook() overwrites it
{
	int i;	
	if(dim==0) 
	{
		for(i=0; i<n; i++)
		{
			start[i]=(char*) malloc(1);
			*start[i]='\0';
		}
		dim=n;
	
	}else {
		destroy();
		newBook(n);
	}
}


void printlist()			//displaying the current situation
{
	int i;

	if(dim>0)
	{
		printf("\nREGISTER[0..%d]: \n", dim);
	
		for(i=0; i<dim; i++)
		{
			if(*start[i]!='\0')
				printf("%d --> %s\n", i, start[i]);
		}
		printf("\n");
	}

	else printf("error: The register does not exist!\n");
}


void book(int k, char* name)		//booking (an index) in the register
{
	
	if(*start[k]=='\0')
	{
		start[k]=malloc(strlen(name)+1);
		strcpy(start[k], name);
		
	}
		
	else printf("error: The place you want to book is occupied.\n");
}



void cancel(int k)			//erase a booking
{
	if(*start[k]=='\0')
		printf("error: the booking you want to cancel does not exist\n");

	else free(start[k]);
}



void move(int from, int to)		//moving a booking
{
	if (*start[from]!='\0' && *start[to]=='\0')
	{
		strcpy(start[to], start[from]);
		free(start[from]);
	}else{

		printf("error: impossible to complete operation," 
			" empty place-from or occupied place-to.");
	}		
}




int main()
{
	char *an= "andrea";
	char *lu= "luca";

	newBook(3);
	book(0, lu);
	book(1,an);
	printlist();
	
	newBook(4);
	book(3,lu);
	printlist();
	


}
