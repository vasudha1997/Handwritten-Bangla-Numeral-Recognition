/* Linear binary pattern */
//gcc -Wall -fno-stack-protector CreateCSV.c


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define GRAYLEVEL 256

int row, col, *image2=NULL;//, *segment;
void input_image2( char*, int, int );
void sample_processing_data( char*, int, int, FILE* );

//#include "rccount.c"
//#include "myfunction_pgm.c"

int main1( char* s, FILE *f )
{
	//(if(argc < 2)
	//{
	//	printf("Error");
	//	exit(0);
	//}
	
	count_rc( s );
	//printf("Row=%d, col=%d-", row, col);
	image2 = (int*) malloc ( row*col*sizeof(int) );
	input_image2( s, row, col );
	sample_processing_data( s, row, col, f );
	//free(image2);
	return 0;
}

void sample_processing_data( char* s, int row, int col, FILE *fileptr )
{
	/*FILE *fileptr=fileptr = fopen("Data0.text", "w");
	
	;
	if( fileptr == NULL)
	{
		printf("error\n");
		exit(0);
	}*/
	
	
	//fprintf(fileptr,"A11, A12, A13, A14, A15, A16, A17, A18, A21, A22, A23, A24, A25, A26, A27, A28, A31, A32, A33, A34, A35, A36, A37, A38, A41, A42, A43, A44, A45, A46, A47, A48, A51, A52, A53, A54, A55, A56, A57, A58, A61, A62, A63, A64, A65, A66, A67, A68, Output  \n");
	
	
	int i, left=0, sum, index=0;
	int p[15][256];
	int q[15][16];
	//int *p = (int*) malloc ( 15*256*sizeof(int) );
	//int *q = (int*) malloc ( 15*16*sizeof(int) );
	//int *r = (int*) malloc ( 15*16*sizeof(int) );
	//for( int i=0; i<256*20; i++ )
	//			p[i] = 0;//*( p+i ) = 0;
	for(int i=0; i<15; i++)
		for( int j=0; j<256; j++)
			p[i][j]=0;
			
	int feature[6][8];
	for(int i=0; i<6; i++)
		for( int j=0; j<8; j++)
			feature[i][j]=0;
			
	int ind1=0, ind2=0;			
	//for(int i=0; i<15*16; i++)
	//	q[i]=0;//*( q+i ) = 0;
	for(int i=0; i<15; i++)
		for( int j=0; j<16; j++)
			q[i][j]=0;
	
	
	sum = 0;
		ind1=0; ind2=-1;
		for(int ii=0; ii<6; ii++)
			for( int jj=0; jj<8; jj++)
				feature[ii][jj]=0;
					
		for( int ii=2; ii<row-2; ii++)
		{
			for( int jj=2; jj<col-2; jj++)
			{
					// For every pixel form Linear binary pattern.
					
				sum = 0;
					//	NORTH-WEST
				if( *(image2+(ii-1)*col+jj-1) == 0 )
						sum = sum + pow(2,0);
					//	NORTH
				if( *(image2+(ii-2)*col+jj) == 0 )
						sum = sum + pow(2,1);
					//	NORTH-EAST
				if( *(image2+(ii-1)*col+jj+1) == 0 )
						sum = sum + pow(2,2);
					//	EAST
				if( *(image2+ ii *col+jj+2) == 0 )
						sum = sum + pow(2,3);
					//	SOUTH-EAST
				if( *(image2+(ii+1)*col+jj+1) == 0 )
						sum = sum + pow(2,4);
					//	SOUTH
				if( *(image2+(ii+2)*col+jj) == 0 )
						sum = sum + pow(2,5);
					//	SOUTH-WEST
				if( *(image2+(ii+1)*col+jj-1) == 0 )
						sum = sum + pow(2,6);
					//	WEST
				if( *(image2+ ii *col+jj-2) == 0 )
						sum = sum + pow(2,7);
					
				//(*(p+index*256+sum))++;
					p[index][sum]++;
					
			}
		}
			
					
		for( int i=0; i<256; i+=8 )
		{
			ind2++;
			
			for( int j=i; j<i+8; j++ )
			{
				feature[ind1][ind2] = feature[ind1][ind2] + p[index][j];//(*(p+index*256+j)) ;
			}
			//printf("%3d ", feature[ind1][ind2] );
			
			//sprintf( buffer, "%d", feature[ind1][ind2]);
			//fprintf(fileptr, "%s,", buffer);
			if(ind2 == 7)
			{
				ind2 = -1;
				ind1++;
			}
		}
			for( int ii=1; ii<row-1; ii++)
			{
				for( int jj=1; jj<col-1; jj++)
				{
					// For every pixel form Linear binary pattern.
					
					sum = 0;
					//	NORTH
					if( *(image2+(ii-1)*col+jj) == 0 )
						sum = sum + pow(2,0);
					//	EAST
					if( *(image2+ ii *col+jj+1) == 0 )
						sum = sum + pow(2,1);
					//	SOUTH
					if( *(image2+(ii+1)*col+jj) == 0 )
						sum = sum + pow(2,2);
					//	WEST
					if( *(image2+ ii *col+jj-1) == 0 )
						sum = sum + pow(2,3);
					
					q[index][sum]++;//(*(q+index*16+sum))++;
					
				}
			}
			ind2=0;
			for( int i=0; i<16; i+=2 )
			{
				feature[4][ind2] = q[index][i] + q[index][i+1];//*(q+index*16+i) + *(q+index*16+i+1) ;
				//printf("%3d ", feature[4][ind2] );
				//itoa( feature[4][ind2], buffer, 10 );
				//sprintf( buffer, "%d", feature[4][ind2] );
				//fprintf(fileptr, "%s," , buffer );
				ind2++;
			}
			
			for(int i=0; i<15; i++)
				for( int j=0; j<16; j++)
					q[i][j]=0;
			for( int ii=1; ii<row-1; ii++)
			{
				for( int jj=1; jj<col-1; jj++)
				{
					// For every pixel form Linear binary pattern.
					
					sum = 0;
					//	NORTH-WEST
					if( *(image2+(ii-1)*col+jj-1) == 0 )
						sum = sum + pow(2,0);
					//	NORTH-EAST
					if( *(image2+(ii-1)*col+jj+1) == 0 )
						sum = sum + pow(2,1);
					//	SOUTH-EAST
					if( *(image2+(ii+1)*col+jj+1) == 0 )
						sum = sum + pow(2,2);
					//	SOUTH-WEST
					if( *(image2+(ii+1)*col+jj-1) == 0 )
						sum = sum + pow(2,3);
					
					q[index][sum]++;//(*(q+index*16+sum))++;
				}
			}
			ind2=0;
			for( int i=0; i<16; i+=2 )
			{
				feature[5][ind2] = q[index][i] + q[index][i+1];//*(q+index*16+i) + *(q+index*16+i+1) ;
				//printf("%3d ", feature[5][ind2]) ;
				//itoa( feature[5][ind2], buffer, 10 );
				//sprintf( buffer, "%d", feature[5][ind2] );
				//fprintf(fileptr, "%s, ", buffer );
				ind2++;
			}
			//fprintf(fileptr,"0,\n");
			
			//index++;
			//printf("\n index=%d and i=%d\n\n", index, i);
			//char buffer[5];
			for( int i=0; i<6; i++ )
			{
				for( int j=0; j<8; j++ )
				{
					//sprintf( buffer, "%d", feature[i][j] );
					//printf("%s,", buffer );
					//fprintf(fileptr, "%s,", buffer );
					//printf("%d,",feature[i][j]);
					fprintf(fileptr, "%d,", feature[i][j]);
					//printf("%s,", buffer );
				}
				//printf("\n");
			}
			//fprintf(fileptr,"0,\n");
			
	//printf("closed");
	//free(p);
	//free(q);
	
	//fclose(fileptr);
}

void input_image2( char* s, int row, int col )
{
	FILE *fp; 
	int line_count=0, r=0, c=0 ;
	unsigned char ch ;
	
	fp = fopen ( s, "rb" );
	
	while( fread(&ch, sizeof(ch), 1, fp) == 1 )
	{
		if(ch == '\n')	++line_count ;
		if(line_count == 4) 	break;
	}
	
	while( fread(&ch, sizeof(ch), 1, fp) == 1)
	{
		*(image2+r*col+c) = ch ;
		c++;
		while( c == col)
		{
			r++;
			c = 0;
		}
	}
	fclose(fp);
}

