
/*	./a.out     401-hull     401-bound           */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

int row, col;
int *image, *image2;




void input_image_3( char* s , int* ii)
{
	FILE *fp;
	int linecount = 0, i=0, j=0; 
	unsigned char ch;
	fp = fopen( s, "rb");
	
	while( fread(&ch, sizeof(ch), 1, fp) == 1 )
	{
		if( ch == '\n' )	++linecount;
		if(linecount == 4)	break;
	}
	
	while( fread(&ch, sizeof(ch), 1, fp) == 1 )
	{
		*(ii+i*col+j) = ch; 
		j++;
		if( j == col )
		{
			i++;
			j=0;
		}
	}
}

//int main(int argc, char* argv[]) 
int main3( char* s1, char* s2, FILE* f)
{
	//printf("hello ");
	int index = 1, value, flag=0, i, j;
	int pockets=0;	
	count_rc( s1 );
	image = (int*) malloc (row*col*sizeof(int) );
	image2 = (int*) malloc (row*col*sizeof(int) );
	input_image_3(s1, image);
	input_image_3(s2, image2);
	int* array = (int*) malloc ( row*col*sizeof(int) );
	
	for ( int i=0; i<row; i++ )
	{
		for ( int j=0; j<col; j++ )
		{
			if( *(image+i*col+j) == 100 )
				*(array+i*col+j) = 2000;
			else if( *(image+i*col+j) == 0 )
				*(array+i*col+j) = 1000;
			else	//if( *(image+i*col+j) == 255 )
				*(array+i*col+j) = 3000;
		}
	}
	//printf("----%d---\n", *(image2+7*col+4));
	//printf("----%d---\n", *(array+53*col+18));
//--------------------------------------------FROM LEFT----------------------------------------------------------------------------	
	for ( i=1; i<row; i++ )
	{
		flag = 0;
		for (  j=1; j<col; j++ )
		{
			if( *(array+i*col+j)  == 1000 || *(image2+i*col+j) == 0)
			{
				//printf("XXX(%d,%d)XXX\n", i,j);
				break;
			}
			if( *(array+i*col+j)==2000)// && flag == 0)
			{
				flag=1;	
				//printf("\n----%d,%d-----",i,j);
				continue;
			}
			else if( *(array+i*col+j)==3000 && flag == 0)
				continue;
			//if(i>50)printf("\n----%d----\n",*(array+i*col+j) );
			if( *(array+i*col+j)!=1000 && *(array+i*col+j)!=2000  )
			{
				
				
				//printf("(%d,%d,%d) ",i,j,*(array+i*col+j));
				value = INT_MAX;
				if( i>=1 && j>=1 && *(array+(i-1)*col+(j-1))<value )	//North-West
					value = *(array+(i-1)*col+(j-1));
				if( i>=1 && *(array+(i-1)*col+j)<value )		//North
					value = *(array+(i-1)*col+j) ;
				if( i>=1 && j<=col-2 && *(array+(i-1)*col+(j+1))<value )//North-East
					value = *(array+(i-1)*col+(j+1));
				if( j>=1 && *(array+i*col+(j-1))<value)			//West
					value = *(array+i*col+(j-1));
				if( *(array+i*col+j)<value)			//Center
					value = *(array+i*col+j);
				if( j<=col-2 && *(array+i*col+(j+1))<value)		//East
					value = *(array+i*col+(j+1));
				if( i<=row-2 && j>=1 && *(array+(i+1)*col+(j-1))<value )//South-West
					value = *(array+(i+1)*col+(j-1));
				if( i<=row-2 && *(array+(i+1)*col+j)<value )		//South
					value = *(array+(i+1)*col+j);
				if( i<=row-2 && j<=col-2 && *(array+(i+1)*col+(j+1))<value )//South-East
					value = *(array+(i+1)*col+(j+1));
					
				//printf("i=%d and j=%d and value=%d\n",i,j,value);
				if(value == 2000||value == 1000)
				{
					value = index++;
					//printf("i=%d and j=%d and value =%d \n",i,j, value);
				}
				*(array+i*col+j) = value;
				
			}
			
		}
	}
	
	//printf("Index = %d\n", index);
	
	
	//---------------------------------------------------FROM TOP----------------------------------------------------------
	for( j=1; j<col; j++ )
	{
		flag = 0;
		for (  i=1; i<row; i++ )
		{
			if( *(array+i*col+j)  == 1000 || *(image2+i*col+j) == 0)
			{
				//printf("XXX(%d,%d)XXX\n", i,j);
				break;
			}
			if( *(array+i*col+j)==2000 )//&& flag == 0)
			{
				flag=1;	
				//printf("\n----%d,%d-----",i,j);
				continue;
			}
			else if( *(array+i*col+j)==3000 && flag == 0)
				continue;
			
			if( *(array+i*col+j)!=1000 && *(array+i*col+j)!=2000 )
			{
				//printf("(%d,%d,%d) ",i,j,*(array+i*col+j));
				value = INT_MAX;
				if( i>=1 && j>=1 && *(array+(i-1)*col+(j-1))<value )	//North-West
					value = *(array+(i-1)*col+(j-1));
				if( i>=1 && *(array+(i-1)*col+j)<value )		//North
					value = *(array+(i-1)*col+j) ;
				if( i>=1 && j<=col-2 && *(array+(i-1)*col+(j+1))<value )//North-East
					value = *(array+(i-1)*col+(j+1));
				if( j>=1 && *(array+i*col+(j-1))<value)			//West
					value = *(array+i*col+(j-1));
				if( *(array+i*col+j)<value)			//Center
					value = *(array+i*col+j);
				if( j<=col-2 && *(array+i*col+(j+1))<value)		//East
					value = *(array+i*col+(j+1));
				if( i<=row-2 && j>=1 && *(array+(i+1)*col+(j-1))<value )//South-West
					value = *(array+(i+1)*col+(j-1));
				if( i<=row-2 && *(array+(i+1)*col+j)<value )		//South
					value = *(array+(i+1)*col+j);
				if( i<=row-2 && j<=col-2 && *(array+(i+1)*col+(j+1))<value )//South-East
					value = *(array+(i+1)*col+(j+1));
				//printf("i=%d and j=%d and value=%d\n",i,j,value);
				if(value == 2000||value == 1000)
				{
					//printf("i=%d and j=%d and value=%d\n",i,j,value);
					value = index++;
				}
				*(array+i*col+j) = value;
				
			}
			if( *(array+i*col+j) == 2000 )
				break;
		}
	}
	//printf("Index = %d\n", index);
	
	//printf("\n\n from right\n");
	//---------------------------------------------------FROM RIGHT----------------------------------------------------------
	for( i=1; i<row; i++ )
	{
		flag = 0;
		for (  j=col-1; j>=1; j-- )
		{
			if( *(array+i*col+j)  == 1000 || *(image2+i*col+j) == 0)
			{
				//printf("XXX(%d,%d)XXX\n", i,j);
				break;
			}
			if( *(array+i*col+j)==2000)// && flag == 0)
			{
				flag=1;	
				//printf("\n----%d,%d-----",i,j);
				continue;
			}
			else if( *(array+i*col+j)==3000 && flag == 0)
				continue;
			
			if( *(array+i*col+j)!=1000 && *(array+i*col+j)!=2000 )
			{
				//printf("(%d,%d,%d) ",i,j,*(array+i*col+j));
				value = INT_MAX;
				if( i>=1 && j>=1 && *(array+(i-1)*col+(j-1))<value )	//North-West
					value = *(array+(i-1)*col+(j-1));
				if( i>=1 && *(array+(i-1)*col+j)<value )		//North
					value = *(array+(i-1)*col+j) ;
				if( i>=1 && j<=col-2 && *(array+(i-1)*col+(j+1))<value )//North-East
					value = *(array+(i-1)*col+(j+1));
				if( j>=1 && *(array+i*col+(j-1))<value)			//West
					value = *(array+i*col+(j-1));
				if( *(array+i*col+j)<value)			//Center
					value = *(array+i*col+j);
				if( j<=col-2 && *(array+i*col+(j+1))<value)		//East
					value = *(array+i*col+(j+1));
				if( i<=row-2 && j>=1 && *(array+(i+1)*col+(j-1))<value )//South-West
					value = *(array+(i+1)*col+(j-1));
				if( i<=row-2 && *(array+(i+1)*col+j)<value )		//South
					value = *(array+(i+1)*col+j);
				if( i<=row-2 && j<=col-2 && *(array+(i+1)*col+(j+1))<value )//South-East
					value = *(array+(i+1)*col+(j+1));
					
				if(value == 2000||value == 1000)
				{
					//printf("i=%d and j=%d and value=%d\n",i,j,value);
					value = index++;
				}
				*(array+i*col+j) = value;
				
			}
			if( *(array+i*col+j) == 2000 )
				break;
		}
	}
	//printf("Index = %d\n", index);



	//---------------------------------------------------FROM BOTTOM----------------------------------------------------------
	for( j=1; j<col; j++ )
	{
		flag = 0;
		for (  i=row-1; i>=1; i-- )
		{
			if( *(array+i*col+j)  == 1000 || *(image2+i*col+j) == 0)
			{
				//printf("XXX(%d,%d)XXX\n", i,j);
				break;
			}
			if( *(array+i*col+j)==2000 )//&& flag == 0)
			{
				flag=1;	
				//printf("\n----%d,%d-----",i,j);
				continue;
			}
			else if( *(array+i*col+j)==3000 && flag == 0)
				continue;
			
			if( *(array+i*col+j)!=1000 && *(array+i*col+j)!=2000 )
			{
				//printf("(%d,%d,%d) ",i,j,*(array+i*col+j));
				value = INT_MAX;
				if( i>=1 && j>=1 && *(array+(i-1)*col+(j-1))<value )	//North-West
					value = *(array+(i-1)*col+(j-1));
				if( i>=1 && *(array+(i-1)*col+j)<value )		//North
					value = *(array+(i-1)*col+j) ;
				if( i>=1 && j<=col-2 && *(array+(i-1)*col+(j+1))<value )//North-East
					value = *(array+(i-1)*col+(j+1));
				if( j>=1 && *(array+i*col+(j-1))<value)			//West
					value = *(array+i*col+(j-1));
				if( *(array+i*col+j)<value)			//Center
					value = *(array+i*col+j);
				if( j<=col-2 && *(array+i*col+(j+1))<value)		//East
					value = *(array+i*col+(j+1));
				if( i<=row-2 && j>=1 && *(array+(i+1)*col+(j-1))<value )//South-West
					value = *(array+(i+1)*col+(j-1));
				if( i<=row-2 && *(array+(i+1)*col+j)<value )		//South
					value = *(array+(i+1)*col+j);
				if( i<=row-2 && j<=col-2 && *(array+(i+1)*col+(j+1))<value )//South-East
					value = *(array+(i+1)*col+(j+1));
					
				if(value == 2000||value == 1000)
				{
					//printf("i=%d and j=%d and value=%d\n",i,j,value);
					value = index++;
				}
				*(array+i*col+j) = value;
				
			}
			if( *(array+i*col+j) == 2000 )
				break;
		}
	}
	//printf("Index = %d\n", index);

	
	int counter[index] ;
	
	for(int i=0; i<index; i++)
		counter[i] = 0;
	
	
	for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
			if(*(array+i*col+j) < index)	++counter[*(array+i*col+j)];
			
		
	for(int i=0; i<index; i++)
	{
		//printf("%d : %d\n", i, counter[i]);
		if( counter[i] >= 100)
			++pockets;
	}
	fprintf(f,"%d,",pockets);
	
        return 0;
}

