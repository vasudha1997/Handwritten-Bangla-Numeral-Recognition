# include<stdio.h>
# include<stdlib.h>
# include<math.h>
# include<string.h>

int row, col;
int *image, *boundary;

# include"myfunction_pgm.c"
# include "rccount.c"

void input_image( char* );
void sample_processing( char* );
void build_output( char* );

int main( int argc, char* argv[])
{
	count_rc(argv[1]);			//401-bound
	printf("row=%d col=%d\n", row, col);
	image = (int*) malloc ( row*col*sizeof(int) );
	boundary = (int*) malloc ( row*col*sizeof(int) );
	input_image( argv[1] );
	printf("input");
	sample_processing( argv[1] );
	printf("proessing");
	build_output( argv[1] );
}

void sample_processing( char* s )
{

	for( int i=0; i<row; i++ )
		for (int j=0; j<col; j++ )
			*(boundary+i*col+j) = 255;
	
	// Creating final boundary
	//from left
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			if(*(image+i*col+j) == 0)
			{
				*(boundary+i*col+j) = 0;
				break;
			}
		}
	}
	
	//from right
	for(int i=0; i<row; i++)
	{
		for(int j=col-1; j>=0; j--)
		{
			if(*(image+i*col+j) == 0)
			{
				*(boundary+i*col+j) = 0;
				break;
			}
		}
	}
	
	//from top
	for(int j=0; j<col; j++)
	{
		for(int i=0; i<row; i++)
		{
			if(*(image+i*col+j) == 0)
			{
				*(boundary+i*col+j) = 0;
				break;
			}
		}
	}
	
	//from bottom
	for(int j=0; j<col; j++)
	{
		for(int i=row-1; i>=0; i--)
		{
			if(*(image+i*col+j) == 0)
			{
				*(boundary+i*col+j) = 0;
				break;
			}
		}
	}
}

void input_image( char* s )
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
		*(image+i*col+j) = ch; 
		j++;
		if( j == col )
		{
			i++;
			j=0;
		}
	}
}

void build_output( char *s )
{
	int i,j, mydata;
	char t[50] ;
	FILE *fp1, *fp2 ;
	unsigned char ch;
	
	for( i=0; i<strlen(s) && s[i]!= '-'; i++ )
		t[i] = s[i];
	t[i] = '-';
	t[++i] = '\0';
	strcat(t, "newbound");
	build_my_file( row, col );
	
	fp1 = fopen( t, "wb" );
	fp2 = fopen("myfile.dat", "rb");
	
	while( fread(&ch, sizeof(ch), 1, fp2) == 1 )
		fwrite( &ch, sizeof(ch), 1, fp1);
	for( i=0; i<row; i++)
		for( j=0; j<col; j++ )
		{
			mydata = *(boundary+i*col+j) ;
			fwrite( &mydata, sizeof(ch), 1,fp1 );
		}
			
}
