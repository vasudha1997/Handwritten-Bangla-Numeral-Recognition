
//---------------------------- ./a.out 401-bound.pgm -------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int row, col;
int* image;

void input_image_4( char* );

int main4( char* s, FILE* fp )
{
	int i, j, index, h1v1, h1v2, h1v3, h2v1, h2v2, h2v3, h3v1, h3v2, h3v3 ;
	h1v1 = h1v2 = h1v3 = h2v1 = h2v2 = h2v3 = h3v1 = h3v2 = h3v3 = 0;
	count_rc( s );
	image = (int*) malloc ( row*col*sizeof(int) );
	input_image_4( s );
	
	int horizontal[row][col];
	int vertical[row][col];
	int arrHor[7] = {0} ;
	int arrVer[7] = {0} ;
	
	for(i=0; i<row; i++)
		for(j=0; j<col; j++)
		{
			horizontal[i][j] = 0;
			vertical[i][j] = 0;
		}
		
	
	for(i=0; i<row; i++)
	{
		index = 1;
		for(j=0; j<col; j++)
		{
			if( ( *(image+i*col+j)==0 && j==0 ) || ( *(image+i*col+j)==0 && *(image+i*col+(j-1))!=0 && j>0) ) 
			{
				horizontal[i][j] = index;
				++arrHor[index] ;
				index++;
			}
		}
	}
	
	
	for(j=0; j<col; j++)
	{
		index = 1;
		for(i=0; i<row; i++)
		{
			if( ( *(image+i*col+j)==0 && i==0 ) || ( *(image+i*col+j)==0 && *(image+(i-1)*col+j)!=0 && i>0) )
			{
				vertical[i][j] = index;
				++arrVer[index] ;
				index++;
				
				if( horizontal[i][j]==1 && vertical[i][j]==1 )	++h1v1;
				else if( horizontal[i][j]==1 && vertical[i][j]==2 ) 	++h1v2;
				else if( horizontal[i][j]==1 && vertical[i][j]==3 )	++h1v3;
				else if( horizontal[i][j]==2 && vertical[i][j]==1 ) 	++h2v1;
				else if( horizontal[i][j]==2 && vertical[i][j]==2 )	++h2v2;
				else if( horizontal[i][j]==2 && vertical[i][j]==3 ) 	++h2v3;
				else if( horizontal[i][j]==3 && vertical[i][j]==1 )	++h3v1;
				else if( horizontal[i][j]==3 && vertical[i][j]==2 )	++h3v2;
				else if( horizontal[i][j]==3 && vertical[i][j]==3 )	++h3v3;
			}
		}
	}
	
	/*printf("horizontal-\n");
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
			printf("%d", horizontal[i][j] );
		printf("\n");
	}
	
	printf("vertical-\n");
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
			printf("%d", vertical[i][j] );
		printf("\n");
	}*/
	
	for(int i=1; i<=6; i++)	fprintf(fp,"%f,",(float)arrHor[i]/(float)(row*col) );
	for(int i=1; i<=6; i++) fprintf(fp,"%f,",(float)arrVer[i]/(float)(row*col) );
	//printf("-----%d-----\n", row*col);
	fprintf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,",h1v1,h1v2,h1v3,h2v1,h2v2,h2v3,h3v1,h3v2,h3v3 );
	
	//------------------------Region 1-----------------------------------
	int r1[7] = {0};
	
	for( i=0; i<row/2; i++ )
		for( j=0; j<col/2; j++ )
		{
			if( horizontal[i][j] >= 1 && horizontal[i][j] <=3 )
				++r1[horizontal[i][j]];
			
			if( vertical[i][j] >=1 && vertical[i][j] <=3 )
				++r1[vertical[i][j] + 3];
		}
	
	
	//--------------------------Region 2 ---------------------------------------
	int r2[7] = {0};
	
	for( i=row/2; i<row; i++ )
		for( j=0; j<col/2; j++ )
		{
			if( horizontal[i][j] >= 1 && horizontal[i][j] <=3 )
				++r2[horizontal[i][j]];
			
			if( vertical[i][j] >=1 && vertical[i][j] <=3 )
				++r2[vertical[i][j] + 3];
		}	
	
	
	//---------------------------Region 3--------------------------------------
	int r3[7] = {0};
	
	for( i=0; i<row/2; i++ )
		for( j=col/2; j<col; j++ )
		{
			if( horizontal[i][j] >= 1 && horizontal[i][j] <=3 )
				++r3[horizontal[i][j]];
			
			if( vertical[i][j] >=1 && vertical[i][j] <=3 )
				++r3[vertical[i][j] + 3];
		}
		
		
	//---------------------------Region 4-----------------------------------------
	int r4[7] = {0};
	
	for( i=row/2; i<row; i++ )
		for( j=col/2; j<col; j++ )
		{
			if( horizontal[i][j] >= 1 && horizontal[i][j] <=3 )
				++r4[horizontal[i][j]];
			
			if( vertical[i][j] >=1 && vertical[i][j] <=3 )
				++r4[vertical[i][j] + 3];
		}
		
		
	/*printf("\n");	
	for( int i=1; i<=6; i++ )
		printf("%d  ",r1[i] );
		
	printf("\n");	
	for( int i=1; i<=6; i++ )
		printf("%d  ",r2[i] );
		
	fprintf(fp,"\n");	
	for( int i=1; i<=6; i++ )
		fprintf(fp,"%d  ",r3[i] );
	
	fprintf(fp,"\n");	
	for( int i=1; i<=6; i++ )
		fprintf(fp,"%d  ",r4[i] );*/
		
	
	//--------------------finding maximum------------------------------------------
	
	int value = 0, region = 0;
	for( int i=1; i<=6; i++ )
	{
		value = 0, region = 0;
		if( value < r1[i] )	{ value=r1[i]; region=1; }
		if( value < r2[i] )	{ value=r2[i]; region=2; }
		if( value < r3[i] )	{ value=r3[i]; region=3; }
		if( value < r4[i] )	{ value=r4[i]; region=4; }
		fprintf(fp,"%d,", region);
		
	}
	
	
	//-------------Which class is maximum in different regions-------------------------
	// LABEl - h1=1, h2=2, h3=3, v1=4, v2=5, v3=6 -------------------------------------------
	
	int label=0;
	value=0;
	for( int i=1; i<7; i++ )
		if(value < r1[i]){ value = r1[i]; label=i; }
	fprintf(fp,"%d,",label);
	
	value = 0;
	for( int i=1; i<7; i++ )
		if(value < r2[i]){ value = r2[i]; label=i; }
	fprintf(fp,"%d,",label);
	
	value = 0;
	for( int i=1; i<7; i++ )
		if(value < r3[i]){ value = r3[i]; label=i; }
	fprintf(fp,"%d,",label);
	
	value = 0;
	for( int i=1; i<7; i++ )
		if(value < r4[i]){ value = r4[i]; label=i; }
	fprintf(fp,"%d,",label);
	
	fprintf(fp,"NINE\n");
		
}

void input_image_4( char* s )
{
	FILE* fp;
	int linecount = 0, i=0, j=0;
	unsigned char ch;
	fp = fopen( s, "rb" );
	
	while( fread(&ch, sizeof(ch), 1, fp) == 1 )
	{
		if( ch == '\n' )	linecount++;
		if( linecount == 4 )
			break;
	}
	
	while( fread(&ch, sizeof(ch), 1, fp) == 1 )
	{
		*(image+i*col+j) = ch;
		j++;
		if( j==col)
		{
			j=0;
			i++;
		}
	}
}
