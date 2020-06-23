#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
struct SubSet
{
	int data;
	struct SubSet *next;
}**S;

void tableA(int **A,int n)
{
    int i,j;
    for(i=0;i<pow(2,n-1);i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
}

void tableS(int n)
{
    int i;
    struct SubSet *temp;
    for(i=0;i<pow(2,n-1);i++)
	{
		temp = S[i];
		while(temp!= NULL)
		{
			printf("k-%d ",temp->data);
			temp = temp->next;
		}
		printf("f\n");
	}
}

struct SubSet *Create_element_SubSet(int i)	//function to Create an element in a subset		returns {i}
{
	struct SubSet *temp;
	temp = (struct SubSet*)malloc(sizeof(struct SubSet));
	temp->data = i;
	temp->next = NULL;
	return temp;
}

int isHit(int i,int j)				//function to Check if j'th bit is one in i		returns 1/0
{
	while(j > 0)
	{
		i = i/2;
		--j;
	}
	if(i%2 == 1)
		return 1;
	return 0;
}

void Create_SubSet(int n)			//function to create all 2^n subsets
{
	S = (struct SubSet**)malloc(sizeof(struct SubSet*)*pow(2,n-1));
	struct SubSet *temp,*Head = NULL,*Tail = NULL;
	int i,j,k,flag = 0;
	for(i=0;i<pow(2,n-1);i++)
	{
		for(j=0;j<n;j++)
		{
			if(isHit(i,j))
			{
				temp = Create_element_SubSet(j+1);
				if(Head == NULL)
					Head = Tail = temp;
				else
				{
					Tail->next = temp;
					Tail = temp;
				}
			}
		}
		S[i] = Head;
		Head = Tail = NULL;
	}
	//uncomment the below line for printing contents of table S
	//tableS(n);
}

void Solution(int **Sol,int i,int j)		//function to print the Travelling Salesman Optimum path
{
	if(i==0)
	{
		printf("0\n");
		return;
	}
	printf("%d->",Sol[i][j]);
	Solution(Sol,i-(int)pow(2,Sol[i][j]-1),Sol[i][j]);
}

void DP_tsp(int **D,int n)			//function which uses dynamic programming technique to solve Travelling Salesman problem
{

	int i,j,**A,**Sol,minval,x;
	struct SubSet *temp;
	A = (int**)malloc(sizeof(int*)*pow(2,n-1));
	for(i=0;i<pow(2,n);i++)
		A[i] = (int*)malloc(sizeof(int)*n);
	Sol = (int**)malloc(sizeof(int*)*pow(2,n-1));
	for(i=0;i<pow(2,n);i++)
		Sol[i] = (int*)malloc(sizeof(int)*n);
	Create_SubSet(n);
	for(i=0;i<pow(2,n-1);i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==0)
				A[i][j] = D[i][j];
			else
			{
				temp = S[i];
				minval = INT_MAX;
				Sol[i][j] = -1;
				while(temp != NULL)
				{
					x = D[temp->data][j] + A[i-(int)pow(2,temp->data-1)][temp->data];
					if(x < minval)
					{
						minval = x;
						Sol[i][j] = temp->data;
					}
					temp = temp->next;
				}
				A[i][j] = minval;
			}
		}
	}
	//uncomment the below line for printing table entries in A
    //tableA(A,n);
	printf("the shortest possible route that visits every city exactly once and returns to the starting point is:-\n");
	printf("0->");
	Solution(Sol,(int)pow(2,n-1)-1,0);
}

int main()
{
	int n,**D,i,j;
	printf("Enter the number of cities\n");
	scanf("%d",&n);
	printf("Enter the distance between each cities\n");
	D = (int**)malloc(sizeof(int*)*n);
	for(i=0;i<n;i++)
		D[i] = (int*)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&D[i][j]);
	DP_tsp(D,n);
	return 0;
}
