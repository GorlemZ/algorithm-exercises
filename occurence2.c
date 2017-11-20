#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define WORD 15
#define TEXT "text.txt" //name of the text file
FILE *f;

struct occurrence					//structure of the occurence 
{
	char word[WORD];
	int n;
};

typedef struct occurrence * Occ ;

struct bit_node						//structure of the node, in the binary tree 
{
	Occ item ;
	struct bit_node *l , *r;

};

typedef struct bit_node * Bit_node ;


Bit_node bit_new (Occ ite)				//creates and allocates a node
{
	Bit_node bn;
	bn= malloc(sizeof(struct bit_node));
	bn -> item = ite;
	bn ->l= NULL;
	bn ->r= NULL;

	return bn;
}

Occ occ_new(char * wordread)				//creates and allocates an occurence sructure
{
	Occ oc;
	oc= malloc(sizeof(struct occurrence));
	strcpy( oc -> word, wordread);
	oc -> n= 1;

	return oc;
}

Bit_node search_node(char * string, Bit_node head)	//binary search 
{
	Bit_node notfound=NULL;
	Bit_node bn;
	bn = head;

	int i=strcmp(bn->item->word, string);

	if(i==0)
	{
		return bn;
	}
	else if(i<0 && bn->r!=NULL)
	{
		bn=search_node(string, bn->r);
	}
	else if(i>0 && bn->l != NULL)
	{
		bn=search_node(string, bn->l);
	}
	else
		return notfound;
}


Bit_node insert_node(Bit_node toinsert, Bit_node head)	//recursive insert
{
	Bit_node bnfound;
	Bit_node bn= head;
	int i;

	if(bn==NULL)
	{
		return toinsert;
	}
	else
	{

		if((bnfound=search_node(toinsert->item->word, bn))!=NULL)
		{
				bnfound->item->n++;
		}
		else
		{
			i=strcmp(bn->item->word, toinsert->item->word);
			if(i<0)//string comparing<0)
			{
				if(bn->r ==NULL)
				{
					bn->r=toinsert;
				}
				else
				{
					insert_node(toinsert, bn->r);
				}
			}
			else if (i>0)
			{
				if(bn->l ==NULL)
				{
					bn->l=toinsert;
				}
				else
				{

					insert_node(toinsert, bn->l);
				}
			}
		}
	}
	return bn;
}


void bist_orderprint (Bit_node p) 				//print the tree in alphabetical order
{

	if(p)
	{
		bist_orderprint (p -> l);
		printf("*%s ---> %d\n", p->item->word, p->item->n);
		bist_orderprint (p -> r);
	}

}

void bist_invorderprint (Bit_node p) //void bist_orderprint ( Bit_node p );
{

	if(p)
	{
		bist_invorderprint (p -> r);
		printf("* %s ---> %d\n", p->item->word, p->item->n);
		bist_invorderprint (p -> l);
	}
}


void bit_printassummary (Bit_node p, int spaces)		//print the tree highlighting nodes structure
{
	Bit_node q=p;
	char sp=' ';
	int i;


	if(!q)
	{
		for(i=0; i<spaces*4; i++)
		{
			printf("%c", sp);
		}
		printf("*\n");
	}


	if(q)
	{
		for(i=0; i<spaces*4; i++)
		{
			printf("%c", sp);
		}

		printf("* %s ---> %d\n",q->item->word, q->item->n);

		if(q->l||q->r)
		{
			bit_printassummary(q->l, spaces+1);
			bit_printassummary(q->r, spaces+1);
		}
	}
}

Bit_node mainfirst (char *textname, Bit_node rt)		//creates the tree of word/occurence from the text
{
	Bit_node root=rt;
	char *stop= "STOP";

	char c;

	//from text to strings
	int i=0;
	char str[WORD]="\0";
	f=fopen(textname,"rt");

	while((c=fgetc(f))!=EOF)
	{
		if(c==' '|| c=='\n')
		{
				str[i]='\0';

				if(strcmp(str,stop)!=0)
				{
					for (i=0; str[i]; i++)
					{
						str[i] = tolower((unsigned char)str[i]);
					}

					i=0;
					//qui variabile str pronta
					//	bit_new( occ_new(str)) funziona, controllare insert_node

					root=insert_node ((bit_new(occ_new(str))),root);
				}
				else break;
		}
		else if((c>64&&c<91) || (c>96&&c<123))
		{
			*(str+i)=c;
			i++;
		}
	}


	//fclose(f);
	return root;
}

void mainsnd (Bit_node root)					//print occurences of words
{
	int i=0;
	Bit_node bn;
	char str[WORD]="\0";
	char c;
	char *stop= "STOP";

	while((c=fgetc(f))!=EOF)
	{
		if(c==' '|| c=='\n')
		{
				str[i]='\0';

				if(strcmp(str,stop)!=0)
				{
					for (i=0; str[i]; i++)
					{
						str[i] = tolower((unsigned char)str[i]);
					}

					i=0;
					//qui variabile str pronta
					bn=search_node(str,root);
					if(bn==NULL)
					{
						printf("*%s---> 0\n", str);
					}
					else
						printf("*%s---> %d\n", bn->item->word, bn->item->n) ;
				}
				else break;
		}
		else if((c>64&&c<91) || (c>96&&c<123))
		{
			*(str+i)=c;
			i++;
		}
	}
}



int main()
{

	Bit_node root=NULL;


	root=mainfirst(TEXT, root);

	printf("\nOCCORRENZE DI PAROLE NEL TESTO IN ORDINE ALFABETICO:\n");
	printf("****************************************************\n");

	bist_orderprint (root);

	printf("\nOCCORRENZE DI PAROLE NEL TESTO IN ORDINE INVERSO:\n");
	printf("*************************************************\n");

	bist_invorderprint (root);

	printf("\nRICERCA DI PAROLE:\n");
	printf("******************\n");

	mainsnd(root);

	fclose(f);

}
