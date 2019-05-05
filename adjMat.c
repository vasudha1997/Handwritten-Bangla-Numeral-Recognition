
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int row, col;

//#include "myfunction_pgm.c"
//#include "rccount.c"

int *image;
void input_image_2(char*);
void sample_processing_2(char*, FILE *f);
//void sample_processing_2( char* );
//void build_output( char*s, int minx, int miny, int maxx, int maxy, int len, int bdth );

//int main ( int argc, char* argv[] ) 
int main2( char *s, FILE *f )
{
	count_rc( s );
	image = (int*) malloc (row*col*sizeof(int) );
	input_image_2( s );
	sample_processing_2 ( s, f );
}

/*void build_output( char *s, int minx, int miny, int maxx, int maxy, int len, int bdth )
{
	unsigned char ch;
	char t[50];
	
	FILE *fp1, *fp2 ;
	int i, j, mydata ;
	build_my_file( row, col );
	
	for( i=0; i<strlen(s); i++ )
		if( s[i] == '-' )break ;
	for( j=0; j<i; j++ )t[j] = s[j];
	t[j] = '\0' ;
	strcat( t, "grid" ) ;
	fp1 = fopen( t, "wb+" );
	fp2 = fopen( "myfile.dat", "rb" );
	while( fread( &ch, sizeof(ch), 1, fp2) == 1 )
		fwrite( &ch, sizeof(ch), 1, fp1 );
	for( i=0; i<row; i++)
		for( j=0; j<col; j++ )
		{
			if( i==miny || i==miny+bdth || i==miny+2*bdth || i==miny+3*bdth || i==miny+4*bdth || i==maxy || j==minx||j==minx+len||j==minx+2*len||j==minx+3*len||j==minx+4*len||j==maxx)
				mydata = 0;
			else
				mydata = *(image+i*col+j) ;
			fwrite( &mydata, sizeof(ch), 1,fp1 );
		}
	fclose( fp1 );
	fclose( fp2 );
	
	return ;
}*/	

void sample_processing_2( char* S , FILE *f)
{
	int j=0,minx=col+1, miny=row+1, maxx=0, maxy=0, len, bdth;
	int adjMat[25][25];
	for( int i=0; i<row; i++ )
	{
		for( int j=0; j<col; j++ )
		{
			if( *(image + i*col +j) == 0 )
			{
				if(i < miny)	miny = i;
				if(i > maxy)	maxy = i;
				if(j < minx) 	minx = j;
				if(j > maxx)	maxx = j; 
			}
		}
	}
	//printf("miny=%d, maxy=%d, minx=%d, maxx=%d\n", miny, maxy, minx, maxx );
	bdth = ((maxy-miny+2)/5);
	len = ((maxx-minx+2)/5);
	//printf("len=%d, bdth=%d\n", len, bdth );
	//build_output( S, minx, miny, maxx, maxy, len, bdth );
	//printf("%d %d %d %d\n", miny+bdth, 2*bdth+miny, 3*bdth+miny, 4*bdth+miny );
	//printf("%d %d %d %d\n", minx+len, 2*len+minx, 3*len+minx, 4*len+minx );
	
	for( int i=0; i<25; i++)
		for( int j=0; j<25; j++)
			adjMat[i][j] = 0;
	j=miny-1;
	for( int i=miny; i<miny+bdth; i++,j++ )
	{
		//printf("i=%d, j=%d\t",i,j);
		if( *(image+minx+len+j*col) == 0 ) { adjMat[0][1] = 1; adjMat[1][0] = 1; printf("(0,1)");   }
		if( *(image+minx+2*len+j*col) == 0 ) { adjMat[1][2] = 1; adjMat[2][1] = 1;  printf("(1,2)");   }
		if( *(image+minx+3*len+j*col) == 0 ) { adjMat[2][3] = 1; adjMat[3][2] = 1;  printf("(2,3)");   }
		if( *(image+minx+4*len+j*col) == 0 ) { adjMat[3][4] = 1; adjMat[4][3] = 1;  printf("(3,4)");   }
		//printf("%d %d %d %d\n", miny+bdth+j, miny+2*bdth+j, miny+3*bdth+j, miny+4*bdth+j );
	}
	for( int i=miny+bdth; i<miny+2*bdth; i++,j++ )
	{
		//printf("i=%d, j=%d\t",i,j);
		if( *(image+minx+len+j*col) == 0 ) { adjMat[5][6] = 1; adjMat[6][5] = 1;  printf("(5,6)");   }
		if( *(image+minx+2*len+j*col) == 0 ) { adjMat[6][7] = 1; adjMat[7][6] = 1;  printf("(6,7)");  }
		if( *(image+minx+3*len+j*col) == 0 ) { adjMat[7][8] = 1; adjMat[8][7] = 1;  printf("(7,8)");  }
		if( *(image+minx+4*len+j*col) == 0 ) { adjMat[8][9] = 1; adjMat[9][8] = 1;  printf("(8,9)");  }
	}
	for( int i=miny+2*bdth; i<miny+3*bdth; i++,j++ )
	{
		//printf("i=%d, j=%d\t",i,j);
		if( *(image+minx+len+j*col) == 0 ) { adjMat[10][11] = 1; adjMat[11][10] = 1;  printf("(10,11)"); }
		if( *(image+minx+2*len+j*col) == 0 ) { adjMat[12][11] = 1; adjMat[11][12] = 1;  printf("(11,12)"); }
		if( *(image+minx+3*len+j*col) == 0 ) { adjMat[12][13] = 1; adjMat[13][12] = 1;  printf("(12,13)"); }
		if( *(image+minx+4*len+j*col) == 0 ) { adjMat[13][14] = 1; adjMat[14][13] = 1;  printf("(13,14)"); }
	}
	for( int i=miny+3*bdth; i<miny+4*bdth; i++,j++ )
	{
		//printf("i=%d, j=%d\t",i,j);
		if( *(image+minx+len+j*col) == 0 ) { adjMat[15][16] = 1; adjMat[16][15] = 1;  printf("(15,16)");  }
		if( *(image+minx+2*len+j*col) == 0 ) { adjMat[16][17] = 1; adjMat[17][16] = 1;  printf("(16,17)");}
		if( *(image+minx+3*len+j*col) == 0 ) { adjMat[17][18] = 1; adjMat[18][17] = 1;  printf("(17,18)");}
		if( *(image+minx+4*len+j*col) == 0 ) { adjMat[18][19] = 1; adjMat[19][18] = 1;  printf("(18,19)");}
	}
	//printf("====[%d]=========\n", *(image+28*col+minx+3*len) );
	for( int i=miny+4*bdth; i<=maxy+1; i++,j++ )
	{
		//printf("i=%d, j=%d\t",i,j);
		if( *(image+minx+len+j*col) == 0 ) { adjMat[20][21] = 1; adjMat[21][20] = 1;  printf("(20,21)");   }
		if( *(image+minx+2*len+j*col) == 0 ) { adjMat[21][22] = 1; adjMat[22][21] = 1;  printf("(21,22)"); }
		if( *(image+minx+3*len+j*col) == 0 ) { adjMat[22][23] = 1; adjMat[23][22] = 1;  printf("(22,23)");  }
		if( *(image+minx+4*len+j*col) == 0 ) { adjMat[23][24] = 1; adjMat[24][23] = 1;  printf("(23,24)");  }
	}
	j=0;
	for( int i=minx; i<minx+len; i++,j++ )
	{
		//printf("i=%d, j=%d, miny+bdth-1 = %d, j+minx=%d \n",i,j, miny+bdth-1, j+minx);
		if( *(image+(miny+bdth)*col+j+minx)==0 ) { adjMat[0][5]=1; adjMat[5][0]=1;  printf("(0,5)");  }
		if( *(image+(miny+2*bdth)*col+j+minx)==0) { adjMat[5][10]=1; adjMat[10][5]=1; printf("(5,10)");   }
		if( *(image+(miny+3*bdth)*col+j+minx)==0) { adjMat[10][15]=1; adjMat[15][10]=1;printf("(10,15)");  }
		if( *(image+(miny+4*bdth)*col+j+minx)==0) { adjMat[15][20]=1; adjMat[20][15]=1;printf("(15,20)");  }
	}
	for( int i=minx+len; i<minx+2*len; i++,j++ )
	{
		//printf("i=%d, j=%d\t",i,j);
		if( *(image+(miny+bdth)*col+j+minx) == 0 ) { adjMat[1][6]=1; adjMat[6][1]=1;  printf("(6,1)");   }
		if( *(image+(miny+2*bdth)*col+j+minx) == 0 ) { adjMat[6][11]=1; adjMat[11][6]=1;printf("(6,11)");   }
		if( *(image+(miny+3*bdth)*col+j+minx)==0) { adjMat[11][16]=1; adjMat[16][11]=1;printf("(11,16)");  }
		if( *(image+(miny+4*bdth)*col+j+minx)==0) { adjMat[16][21]=1; adjMat[21][16]=1;printf("(16,21)");  }
	}
	for( int i=minx+2*len; i<minx+3*len; i++,j++ )
	{
		if( *(image+(miny+bdth)*col+j+minx) == 0 ) { adjMat[2][7]=1; adjMat[7][2]=1;  printf("(2,7)");   }
		if( *(image+(miny+2*bdth)*col+j+minx)==0) { adjMat[7][12]=1; adjMat[12][7]=1;  printf("(7,12)");  }
		if( *(image+(miny+3*bdth)*col+j+minx)==0) { adjMat[12][17]=1; adjMat[17][12]=1;printf("(12,17)");  }
		if( *(image+(miny+4*bdth)*col+j+minx)==0) { adjMat[17][22]=1; adjMat[22][17]=1;printf("(17,22)");  }
	}
	for( int i=minx+3*len; i<minx+4*len; i++,j++ )
	{
		if( *(image+(miny+bdth)*col+j+minx) == 0 ) { adjMat[3][8]=1; adjMat[8][3]=1;  printf("(3,8)");   }
		if( *(image+(miny+2*bdth)*col+j+minx)==0) { adjMat[8][13]=1; adjMat[13][8]=1;  printf("(8,13)"); }
		if( *(image+(miny+3*bdth)*col+j+minx)==0) { adjMat[13][18]=1; adjMat[18][13]=1;printf("(13,18)"); }
		if( *(image+(miny+4*bdth)*col+j+minx)==0) { adjMat[18][23]=1; adjMat[23][18]=1;printf("(18,23)"); }
	}
	for( int i=minx+4*len; i<=maxx; i++,j++ )
	{
		//printf("i=%d, j=%d\t",i,j);
		if( *(image+(miny+bdth)*col+j+minx) == 0 ) { adjMat[4][9]=1; adjMat[9][4]=1;  printf("(4,9)"); }
		if( *(image+(miny+2*bdth)*col+j+minx)==0) { adjMat[9][14]=1; adjMat[14][9]=1;  printf("(9,14)"); }
		if( *(image+(miny+3*bdth)*col+j+minx)==0) { adjMat[14][19]=1; adjMat[19][14]=1;printf("(14,19)"); }
		if( *(image+(miny+4*bdth)*col+j+minx)==0) { adjMat[19][24]=1; adjMat[24][19]=1;printf("(19,24)"); }
	}
	
	//printf("\n");
	/*int degree;
	for( int i=0; i<25; i++)
	{degree = 0;
		for( int j=0; j<25; j++)if(adjMat[i][j] == 1 )	degree++;
		fprintf(f,"%d,",degree);}*/
	//fprintf(f,"ZERO\n");
	
	
	
	int  filled[25];

	for(int i=0;i<25;i++)	  filled[i]=0;
	for (int i=minx; i<=maxx; i++)
	{
		for(int j=miny; j<=maxy; j++)
		{
			
			if( *(image+j*col+i) == 0 )
			{
				
				if(i<=minx+len)
				{
					if(j<=miny+bdth)	  filled[0] = 1;
					else if(j<=miny+2*bdth)  	  filled[5] = 1;
					else if(j<=miny+3*bdth)		  filled[10] = 1;
					else if(j<=miny+4*bdth)		  filled[15] = 1;
					else if(j<=maxy+1)		  filled[20] = 1;
				}
				else if(i<=minx+2*len)
				{
					if(j<=miny+bdth)	  filled[1] = 1;
					else if(j<=miny+2*bdth)  	  filled[6] = 1;
					else if(j<=miny+3*bdth)		  filled[11] = 1;
					else if(j<=miny+4*bdth)		  filled[16] = 1;
					else if(j<=maxy+1)		  filled[21] = 1;
				}
				else if(i<=minx+3*len)
				{
					if(j<=miny+bdth)	  filled[2] = 1;
					else if(j<=miny+2*bdth)  	  filled[7] = 1;
					else if(j<=miny+3*bdth)		  filled[12] = 1;
					else if(j<=miny+4*bdth)		  filled[17] = 1;
					else if(j<=maxy+1)		  filled[22] = 1;
				}
				else if(i<=minx+4*len)
				{
					if(j<=miny+bdth)	  filled[3] = 1;
					else if(j<=miny+2*bdth)  	  filled[8] = 1;
					else if(j<=miny+3*bdth)		  filled[13] = 1;
					else if(j<=miny+4*bdth)		  filled[18] = 1;
					else if(j<=maxy+1)		  filled[23] = 1;
				}
				else if(i<=maxx)
				{
					if(j<=miny+bdth)	  filled[4] = 1;
					else if(j<=miny+2*bdth)  	  filled[9] = 1;
					else if(j<=miny+3*bdth)		  filled[14] = 1;
					else if(j<=miny+4*bdth)		  filled[19] = 1;
					else if(j<=maxy+1)		  filled[24] = 1;
				}
			}
		}
	} 
	/*for(int i=0;i<25;i++)
	{
		if(i%5==0)	printf("\n");
		printf("[%d->%d] ", i,   filled[i] );
	}*/
	
	int fill=0, empty=0, f4=0, e4=0, fLTf[2]={0}, eLRTBf[4]={0}, eLTe[4]={0}, countf, counte;
	for (int i=0; i<25; i++ )
	{
		countf = 0; counte = 0;
		if( filled[i] == 1 )	++fill;
		else ++empty;
		
		if( i%5!=0 ) 	//left neighour present
		{
		  	 if( filled[i-1] && filled[i]) {  countf++; fLTf[0]++; }
		  	 //else if( !filled[i-1] && filled[i] ) 	fLRTBe[0]++;
			 else if( !filled[i-1] && !filled[i] ){ counte++;  eLTe[0]++;}
			 else if( filled[i-1] && !filled[i] ){ eLRTBf[0]++; }	
		}
		if( (i+1)%5 != 0 ) //right neighbour present
		{
			if( filled[i] && filled[i+1] )	{  countf++;  }
			//else if( filled[i] && !filled[i+1] )	fLRTBe[1]++;
			else if( !filled[i] && filled[i+1] )	eLRTBf[1]++;
			else if( !filled[i] && !filled[i+1])	counte++;
		}
		if(i>4)		  //top neighbour present
		{
			if( filled[i] && filled[i-5] )	{  countf++; fLTf[1]++; }
			//else if( filled[i] && !filled[i-5] )	fLRTBe[2]++;
			else if( !filled[i] && filled[i-5] )  	eLRTBf[2]++;
			else if( !filled[i] && !filled[i-5])	{ counte++; eLTe[1]++;}
		}
		if(i<20)	 //bottom neighbour present
		{
			if( filled[i] && filled[i+5] )	{  countf++;  }
			//else if( filled[i] && !filled[i+5] )	fLRTBe[3]++;
			else if( !filled[i] && filled[i+5] )	eLRTBf[3]++;
			else if( !filled[i] && !filled[i+5])	counte++;;
		}
		if(i>4 && i%5!=0 && filled[i-6] && filled[i])	//North-west neighbour present
			++countf;	
		else if(i>4 && i%5!=0 && !filled[i-6] && !filled[i])
			++counte;
			
		if(i>4 && (i+1)%5!=0 && filled[i-4] && filled[i] )	//North-east neightbour present
			++countf;	
		else if(i>4 && (i+1)%5!=0 && !filled[i-4] && !filled[i] )
			++counte;
			
		if(i<20 && i%5!=0 && filled[i+4] && filled[i] )	//South-west neighbour present
			++countf;
		else if(i<20 && i%5!=0 && !filled[i+4] && !filled[i] )
			++counte;
			
		if(i<20 && (i+1)%5!=0 && filled[i+6] && filled[i])	//South-east neighbour present
			++countf;
		else if(i<20 && (i+1)%5!=0 && !filled[i+6] && !filled[i])
			++counte;
		
		if(countf>=4)	
		{
			++f4;
			//printf("(f(%d)) ",i);
		}
		else if(counte>=4)
		{	++e4;	//printf("(e(%d)) ",i);
		}
		
	}
	
	//printf("\nfilled=%d, empty=%d, f4=%d, e4=%d\n", fill, empty,f4, e4 );
	fprintf(f, "%d,%d,%d,%d,", fill, empty, f4, e4);
	for( int i=0; i<2; i++)	 fprintf(f, "%d,", fLTf[i]);

	for( int i=0; i<4; i++)	 fprintf(f,"%d,", eLRTBf[i]);
	
	for( int i=0; i<2; i++ ) fprintf(f,"%d,", eLTe[i]);
	
	
	
	//======================================================================================================================
	
	//TRACING EDGES
	int binary[4], num;

	for(int i=0; i<24; i++)
	{
		//binary[i%5] = adjMat[i][i+1];
		num = num*2 + adjMat[i][i+1];
		if(i%5 == 3)
		{
			fprintf(f,"%d,", num);
			num=0;
			i++;
		}
	}
	num = 0;
	for (int i=0; i<5; i++)
	{
		num = num*2 + adjMat[i][i+5];
		num = num*2 + adjMat[i+5][i+10];
		num = num*2 + adjMat[i+10][i+15];
		num = num*2 + adjMat[i+15][i+20];
		fprintf(f,"%d,", num);
		num = 0;
	}
	//fprintf(f,"ZERO\n");			 
}

void input_image_2( char* S )
{
	FILE *fp;
	int line_count = 0, r=0, c=0;
	unsigned char ch;
	fp = fopen( S, "rb" );
	while( fread( &ch, sizeof(ch), 1, fp) == 1 )
	{
		if( ch == '\n' )	line_count++;
		if( line_count == 4 )	break ;
	}
	
	while( fread(&ch, sizeof(ch), 1, fp ) == 1 )
	{
		*(image + r*col + c) = ch; 
		c++;
		if( c == col )
		{
			r++;
			c=0;
		}
	}
}
