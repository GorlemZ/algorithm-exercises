#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	int howmanyelem=0;		//contatore generale numero elementi



	struct element 
	{
		int info ; 		/* valore dell’elemento */
		struct element * next ; /* indirizzo del prossimo elemento */
	};

	
	typedef struct element element ;


	int isMember(int n, element *h)
	{
		element *p;
		int i=0;

		for(p=h; p!=NULL; p=p->next)
		{
			if( p -> info == n)
				i=1;
		}
		return i;
	}

	
	element * insert (int n , element * h)	//inserimento in testa, restituisce puntatore a inizio lista
	{
		element *new_node=NULL;
		
		if (isMember(n, h)<1)
		{
			howmanyelem++;
			new_node = malloc(sizeof(struct element));
			new_node -> info= n;
			new_node -> next = h;
			h =new_node;
		}
		return new_node;
	}


	element * delete (int n , element * h)	//elimina l'elemento con info n (che sia testa o nodo intermedio)	
	{
		element *ret;
		element *cur;
		element *prev;

		ret=h;
	
		if(h -> info == n)
		{	
			ret= h->next;
			free(h);
			howmanyelem--;
		}else{
			
			for ( cur=h, prev=NULL; cur!=NULL && cur->info!=n; prev=cur, cur=cur->next); //cur: nodo cercato a fine ciclo
			if(cur!=NULL)
			{
				prev->next = cur->next;
				free(cur);
				howmanyelem--;
			}		
		}
		return ret;
	}


	void printlist(element *h)		//stampa tutti gli elem
	{
		element *p;
		int i=0;
		if(howmanyelem>0)
		{
			for( p=h; p!=NULL; p= p ->next)
			{
				printf(" valore nodo %d: %d\n", i++, p -> info);
			}
		}
		else printf("la lista è vuota!");
	}


	void inverseprintlist(element *h)		//stampa tutti gli elem in ordine inverso
	{
		int i;
		int list[howmanyelem];
		element *p;
	
		for(i=0, p=h ; i<howmanyelem; i++, p= p->next)
		{
			list[i]= p->info;
		}

		for (i=howmanyelem-1; i>=0; i--)
			printf(" valore nodo %d: %d\n", i, list[i]);
	}



	void destroy ( element * h)
	{
		int i;
		element *cur;
		element *prev;
		
		for(cur=h, prev=NULL; cur!=NULL; prev=cur, cur=cur->next)
		{
			prev->next=NULL;
			free(prev);
		}

		howmanyelem=0;
		

	}
	

	
	const char *FILEADDRESS = "/home/gorl/Desktop/instruction.txt" ;
	FILE *fp;
	char buff[20];	
	
	element *first=NULL; 	//testa

	fp = fopen (FILEADDRESS, "r");

	while (fgets(buff, 100, fp)!=NULL)
	{
		char *c;
		c= &buff[1];

		switch(buff[0])
		{
			case '+':			//aggiunge in testa elemento con info specificata
				first =insert (atoi(c), first);		
				break;
			
			case '-':			//elimina elemento con info specificata
				first= delete(atoi(c), first);
				break;
				
			case '?':			//se appartiene
			
				if(isMember(atoi(c), first)==1)	
					printf("nodo con valore %d presente\n", atoi(c));
				else printf("non presente\n");
				break;
				
			case 'c':			//stampa numero elementi
				printf("numero elementi nella lista: %d\n",howmanyelem); 
				break;
				
			case 'p':			//stampa tutti li elem
				printlist(first);
				break;
				
			case 'o':			//stampa tutti gli elem in ordine inverso
				inverseprintlist(first);
				break;
				
			case 'd':			//distruzione e morte
				destroy(first);
				break;
				
			case '\0':
				break;
				
		}
		printf("////\n");

	}	
	
}
