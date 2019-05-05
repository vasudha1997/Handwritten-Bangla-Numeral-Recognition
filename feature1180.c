
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int row, col;

#include "myfunction_pgm.c"
#include "rccount.c"
#include "Data2CSV.c"
#include "adjMat.c"
#include "Pocket.c"
#include "intersect.c"

int *image;
FILE *file;
void input_image(char*);
void sample_processing(char*, FILE*);

int main ( int argc, char* argv[] )			//401-newbound  401-otsu.pgm  401-hull   401-bound
{
	file = fopen("48+180+12+10+1+31.arff", "a");
	if( file == NULL)
	{
		printf("error\n");
		exit(0);
	}
	count_rc( argv[1] );
	image = (int*) malloc (row*col*sizeof(int) );
	input_image( argv[1] );
	main1(argv[2],file);				// ( Data2CSV.c )   Linear Binary Pattern
	sample_processing ( argv[1], file );		// Projection Profile
	main2( argv[1], file );				// ( adjMat.c )	    Neighbour information and Edges in Graph
	main3( argv[3], argv[4], file );		// ( Pocket.c )	    Convex hull pockets
	main4( argv[4], file );				// ( intersect.c )  Intersection info
}


void sample_processing ( char* S, FILE *fileptr )
{	
	//FILE *fileptr=NULL;
	
	/*fileptr = fopen("Feature0.csv", "a");*/
	
	int length, breadth, minx=col+1, miny=row+1, maxx=0, maxy=0, distance;
	int feature[180] ;
	for(int i=0; i<179; i++ )	feature[i] = 0;
	for (int i=0; i<row; i++)
	{
		for (int j=0; j<col; j++)
		{
			if( *( image+i*col+j) == 0 )
			{
				if( i < miny )	miny = i;
				if( i > maxy )	maxy = i;
				if( j < minx ) 	minx = j;
				if( j > maxx )	maxx = j;
			}
		}
	}
	
	//printf("miny=%d, maxy=%d, minx=%d, maxx=%d\n", miny, maxy, minx, maxx );
	length = maxx - minx ;
	breadth = maxy - miny ;
	//printf("length = %d, breadth=%d\n", length, breadth );
	length = ( length % 3 == 0 ) ? length / 3 : length / 3 + 1;
	breadth = ( breadth % 3 == 0 ) ? breadth / 3 : breadth / 3 + 1;
	//printf("length = %d, breadth=%d\n", length, breadth );
	
	//1st segment -------------------------------------------------------------------------------------
	for ( int j=miny; j<miny+breadth; j++ )
	{
		for ( int i=minx; i<minx+length; i++ )
		{
			//distance from left
			
			if( *(image + j*col + i) == 0 )
			{
				//printf("pixel -> %d,%d\t", i,j );
				distance = i - minx;
				if( distance <= (length/5)-1 )	feature[0]++;
				else if( distance <= ((2*length)/5) )	feature[1]++;
				else if( distance <= ((3*length)/5) )	feature[2]++;
				else if( distance <= ((4*length)/5) )	feature[3]++;
				else if( distance <= (length ))	feature[4]++;
				break;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[0], feature[1], feature[2], feature[3], feature[4] ); 
	for ( int j=miny; j<miny+breadth; j++)
	{
		for ( int i=minx+length-1; i>=minx; i--)
		{
			//distance from right
			if( *(image + j*col + i) == 0 )
			{
				distance = (minx+length-1) - i ;
				if( distance >= ((4*length)/5) )	feature[5]++;
				else if ( distance >= ((3*length)/5) )	feature[6]++;
				else if ( distance >= ((2*length)/5) )	feature[7]++;
				else if ( distance >= (length/5) )	feature[8]++;
				else if ( distance >= 0 )	feature[9]++;	
			}
		}	
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[5], feature[6], feature[7], feature[8], feature[9] ); 
	
	for ( int i=minx; i<minx+length; i++)
	{
		for ( int j=miny; j<miny+breadth; j++)
		{
			//distance from up
			if( *(image + j*col + i) == 0 )
			{
				distance = j - miny ;
				if( distance <= (breadth/5) )	feature[10]++;
				else if( distance <= ((2*breadth)/5) )	feature[11]++;
				else if( distance <= ((3*breadth)/5) )	feature[12]++;
				else if( distance <= ((4*breadth)/5) )	feature[13]++;
				else if( distance <= (breadth ))	feature[14]++;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[10], feature[11], feature[12], feature[13], feature[14] );
	for ( int i=minx+length-1; i>=minx; i--)
	{
		for ( int j=miny+breadth-1; j>=miny; j--)
		{
			//distance from down
			if( *(image + j*col + i) == 0 )
			{
				distance = (miny+breadth-1) - j;
				if ( distance >= ((4*breadth)/5) )	feature[15]++;
				else if ( distance >= ((3*breadth)/5) )	feature[16]++;
				else if ( distance >= ((2*breadth)/5) )	feature[17]++;
				else if ( distance >= (breadth/5) )	feature[18]++;
				else if ( distance >= 0 )	feature[19]++;		
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[15], feature[16], feature[17], feature[18], feature[19] );
	
	
	//2nd segment -------------------------------------------------------------------------------------------------
	for ( int j=miny; j<miny+breadth; j++ )
	{	
		for ( int i=minx+length; i<minx+2*length; i++)
		{	
			//distance from left
			if( *(image + j*col + i) == 0 )
			{
				distance = i - (minx+length);
				if( distance <= (length/5) )	feature[20]++;
				else if( distance <= ((2*length)/5) )	feature[21]++;
				else if( distance <= ((3*length)/5) )	feature[22]++;
				else if( distance <= ((4*length)/5) )	feature[23]++;
				else if( distance <= (length ))	feature[24]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[20], feature[21], feature[22], feature[23], feature[24] );
	for ( int j=miny; j<miny+breadth; j++ )
	{	
		for ( int i=minx+2*length-1; i>=minx+length; i--)
		{	
			//distance from right
			if( *(image + j*col + i) == 0 )
			{
				distance = (minx+2*length-1) - i;
				if( distance >= ((4*length)/5) )	feature[25]++;
				else if ( distance >= ((3*length)/5) )	feature[26]++;
				else if ( distance >= ((2*length)/5) )	feature[27]++;
				else if ( distance >= (length/5) )	feature[28]++;
				else if ( distance >= 0 )	feature[29]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[25], feature[26], feature[27], feature[28], feature[29] );
	for ( int i=minx+length; i<minx+2*length; i++ )
	{	
		for ( int j=miny; j<miny+breadth; j++ )
		{	
			//distance from up
			if( *(image + j*col + i) == 0 )
			{
				distance = j - miny;
				if( distance <= (breadth/5)-1 )	feature[30]++;
				else if( distance <= ((2*breadth)/5) )	feature[31]++;
				else if( distance <= ((3*breadth)/5) )	feature[32]++;
				else if( distance <= ((4*breadth)/5) )	feature[33]++;
				else if( distance <= (breadth ))	feature[34]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[30], feature[31], feature[32], feature[33], feature[34] );
	for ( int i=minx+2*length-1; i>=minx+length; i-- )
	{	
		for ( int j=miny+breadth-1; j>=miny; j-- )
		{	
			//distance from down
			if( *(image + j*col + i) == 0 )
			{
				distance = (miny+breadth-1) - j;
				if ( distance >= ((4*breadth)/5) )	feature[35]++;
				else if ( distance >= ((3*breadth)/5) )	feature[36]++;
				else if ( distance >= ((2*breadth)/5) )	feature[37]++;
				else if ( distance >= (breadth/5) )	feature[38]++;
				else if ( distance >= 0 )	feature[39]++;	
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[35], feature[36], feature[37], feature[38], feature[39] );	
	//3rd segment--------------------------------------------------------------------------------------------------------
	for (  int j=miny; j<miny+breadth; j++ )
	{	for ( int i=minx+2*length; i<minx+3*length; i++ )
		{
			//distance from left
			if( *(image + j*col + i) == 0 )
			{
				distance = i - (minx+2*length);
				if( distance <= (length/5) )	feature[40]++;
				else if( distance <= ((2*length)/5) )	feature[41]++;
				else if( distance <= ((3*length)/5) )	feature[42]++;
				else if( distance <= ((4*length)/5) )	feature[43]++;
				else if( distance <= (length ))	feature[44]++;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[40], feature[41], feature[42], feature[43], feature[44] );
	for ( int j=miny; j<miny+breadth; j++ )
	{	
		for ( int i=minx+3*length-1; i>=minx+2*length; i--)
		{	
			//distance from right
			if( *(image + j*col + i) == 0 )
			{
				distance = (minx+3*length-1) - i;
				if( distance >= ((4*length)/5) )	feature[45]++;
				else if ( distance >= ((3*length)/5) )	feature[46]++;
				else if ( distance >= ((2*length)/5) )	feature[47]++;
				else if ( distance >= (length/5) )	feature[48]++;
				else if ( distance >= 0 )	feature[49]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[45], feature[46], feature[47], feature[48], feature[49] );
	for ( int i=minx+length; i<=minx+2*length; i++ )
	{	
		for ( int j=miny; j<miny+breadth; j++ )
		{	
			//distance from up
			if( *(image + j*col + i) == 0 )
			{
				distance = j - miny;
				if( distance <= (breadth/5) )	feature[50]++;
				else if( distance <= ((2*breadth)/5) )	feature[51]++;
				else if( distance <= ((3*breadth)/5) )	feature[52]++;
				else if( distance <= ((4*breadth)/5) )	feature[53]++;
				else if( distance <= (breadth ))	feature[54]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[50], feature[51], feature[52], feature[53], feature[54] );
	for ( int i=minx+2*length-1; i>=minx+length; i-- )
	{	
		for ( int j=miny+breadth-1; j>=miny; j-- )
		{	
			//distance from down
			if( *(image + j*col + i) == 0 )
			{
				distance = (miny+breadth-1) - j;
				if ( distance >= ((4*breadth)/5) )	feature[55]++;
				else if ( distance >= ((3*breadth)/5) )	feature[56]++;
				else if ( distance >= ((2*breadth)/5) )	feature[57]++;
				else if ( distance >= (breadth/5) )	feature[58]++;
				else if ( distance >= 0 )	feature[59]++;	
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[55], feature[56], feature[57], feature[58], feature[59] );	
	//4th segment------------------------------------------------------------------------------
	for ( int j=miny+breadth; j<miny+2*breadth; j++ )
	{	for ( int i=minx; i<minx+length; i++ )
		{	if( *(image + j*col + i) == 0 )
			{//distance from left
				distance = i - minx;
				if( distance <= (length/5) )	feature[60]++;
				else if( distance <= ((2*length)/5) )	feature[61]++;
				else if( distance <= ((3*length)/5) )	feature[62]++;
				else if( distance <= ((4*length)/5) )	feature[63]++;
				else if( distance <= (length ))	feature[64]++;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[60], feature[61], feature[62], feature[63], feature[64] );
	
	for ( int j=miny+breadth; j<miny+2*breadth; j++ )
	{	
		for ( int i=minx+length-1; i>=minx; i--)
		{	
			//distance from right
			if( *(image + j*col + i) == 0 )
			{
				distance = (minx+length-1) - i;
				if( distance >= ((4*length)/5) )	feature[65]++;
				else if ( distance >= ((3*length)/5) )	feature[66]++;
				else if ( distance >= ((2*length)/5) )	feature[67]++;
				else if ( distance >= (length/5) )	feature[68]++;
				else if ( distance >= 0 )	feature[69]++;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[65], feature[66], feature[67], feature[68], feature[69] );
	
	for ( int i=minx; i<minx+length; i++ )
	{	
		for ( int j=miny+breadth; j<miny+2*breadth; j++ )
		{	
			//distance from up
			if( *(image + j*col + i) == 0 )
			{
				distance = j - (miny+breadth);
				if( distance <= (breadth/5) )	feature[70]++;
				else if( distance <= ((2*breadth)/5) )	feature[71]++;
				else if( distance <= ((3*breadth)/5) )	feature[72]++;
				else if( distance <= ((4*breadth)/5) )	feature[73]++;
				else if( distance <= (breadth ))	feature[74]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[70], feature[71], feature[72], feature[73], feature[74] );
	for ( int i=minx+length-1; i>=minx; i-- )
	{	
		for ( int j=miny+2*breadth-1; j>=miny+breadth; j-- )
		{	
			//distance from down
			if( *(image + j*col + i) == 0 )
			{
				distance = (miny+2*breadth-1) - j;
				if ( distance >= ((4*breadth)/5) )	feature[75]++;
				else if ( distance >= ((3*breadth)/5) )	feature[76]++;
				else if ( distance >= ((2*breadth)/5) )	feature[77]++;
				else if ( distance >= (breadth/5) )	feature[78]++;
				else if ( distance >= 0 )	feature[79]++;	
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[75], feature[76], feature[77], feature[78], feature[79] );
			
	//5th segment------------------------------------------------------------------------------------------
	for ( int j=miny+breadth; j<miny+2*breadth; j++ )
	{	for ( int i=minx+length; i<minx+2*length; i++ )
		{	if( *(image + j*col + i) == 0 )
			{//distance from left
				distance = i - (minx+length);
				if( distance <= (length/5) )	feature[80]++;
				else if( distance <= ((2*length)/5) )	feature[81]++;
				else if( distance <= ((3*length)/5) )	feature[82]++;
				else if( distance <= ((4*length)/5) )	feature[83]++;
				else if( distance <= (length ))	feature[84]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[80], feature[81], feature[82], feature[83], feature[84] );
	
	for ( int j=miny+breadth; j<miny+2*breadth; j++ )
	{	
		for ( int i=minx+2*length-1; i>=minx+length; i--)
		{	
			//distance from right
			if( *(image + j*col + i) == 0 )
			{
				distance = (minx+2*length-1) - i;
				if( distance >= ((4*length)/5))	feature[85]++;
				else if ( distance >= ((3*length)/5) )	feature[86]++;
				else if ( distance >= ((2*length)/5) )	feature[87]++;
				else if ( distance >= (length/5) )	feature[88]++;
				else if ( distance >= 0 )	feature[89]++;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[85], feature[86], feature[87], feature[88], feature[89] );
	
	for ( int i=minx+length; i<minx+2*length; i++ )
	{	
		for ( int j=miny+breadth; j<miny+2*breadth; j++ )
		{	
			//distance from up
			if( *(image + j*col + i) == 0 )
			{
				distance = j - (miny+breadth);
				if( distance <= (breadth/5) )	feature[90]++;
				else if( distance <= ((2*breadth)/5) )	feature[91]++;
				else if( distance <= ((3*breadth)/5))	feature[92]++;
				else if( distance <= ((4*breadth)/5))	feature[93]++;
				else if( distance <= (breadth ))	feature[94]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[90], feature[91], feature[92], feature[93], feature[94] );
	for ( int i=minx+length-1; i>=minx; i-- )
	{	
		for ( int j=miny+2*breadth-1; j>=miny+breadth; j-- )
		{	
			//distance from down
			if( *(image + j*col + i) == 0 )
			{
				distance = (miny+2*breadth-1) - j;
				if ( distance >= ((4*breadth)/5) )	feature[95]++;
				else if ( distance >= ((3*breadth)/5) )	feature[96]++;
				else if ( distance >= ((2*breadth)/5) )	feature[97]++;
				else if ( distance >= (breadth/5) )	feature[98]++;
				else if ( distance >= 0 )	feature[99]++;	
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[95], feature[96], feature[97], feature[98], feature[99] );
		
	//6th segment--------------------------------------------------------------------------------------
	for ( int j=miny+breadth; j<miny+2*breadth; j++ )
	{	for ( int i=minx+2*length; i<minx+3*length; i++ )
		{	if( *(image + j*col + i) == 0 )
			{//distance from left
				distance = i - (minx+2*length);
				if( distance <= (length/5) )	feature[100]++;
				else if( distance <= ((2*length)/5) )	feature[101]++;
				else if( distance <= ((3*length)/5) )	feature[102]++;
				else if( distance <= ((4*length)/5) )	feature[103]++;
				else if( distance <= (length ))	feature[104]++;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[100], feature[101], feature[102], feature[103], feature[104] );
	
	for ( int j=miny+breadth; j<miny+2*breadth; j++ )
	{	
		for ( int i=minx+3*length-1; i>=minx+2*length; i--)
		{	
			//distance from right
			if( *(image + j*col + i) == 0 )
			{
				distance = (minx+3*length-1) - i;
				if( distance >= ((4*length)/5))	feature[105]++;
				else if ( distance >= ((3*length)/5) )	feature[106]++;
				else if ( distance >= ((2*length)/5) )	feature[107]++;
				else if ( distance >= (length/5) )	feature[108]++;
				else if ( distance >= 0 )	feature[109]++;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[105], feature[106], feature[107], feature[108], feature[109] );
	
	for ( int i=minx+2*length; i<minx+3*length; i++ )
	{	
		for ( int j=miny+breadth; j<miny+2*breadth; j++ )
		{	
			//distance from up
			if( *(image + j*col + i) == 0 )
			{
				distance = j - (miny+breadth);
				if( distance <= (breadth/5) )	feature[110]++;
				else if( distance <= ((2*breadth)/5) )	feature[111]++;
				else if( distance <= ((3*breadth)/5) )	feature[112]++;
				else if( distance <= ((4*breadth)/5) )	feature[113]++;
				else if( distance <= (breadth ))	feature[114]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[110], feature[111], feature[112], feature[113], feature[114] );
	
	for ( int i=minx+3*length-1; i>minx+2*length; i-- )
	{	
		for ( int j=miny+2*breadth-1; j>=miny+breadth; j-- )
		{	
			//distance from down
			if( *(image + j*col + i) == 0 )
			{
				distance = (miny+2*breadth-1) - j;
				if ( distance >= ((4*breadth)/5) )	feature[115]++;
				else if ( distance >= ((3*breadth)/5))	feature[116]++;
				else if ( distance >= ((2*breadth)/5))	feature[117]++;
				else if ( distance >= (breadth/5) )	feature[118]++;
				else if ( distance >= 0 )	feature[119]++;	
			}
		}	
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[115], feature[116], feature[117], feature[118], feature[119] );
		
	//7th segment--------------------------------------------------------------------------------
	for ( int j=miny+2*breadth; j<miny+3*breadth; j++ )
	{	for ( int i=minx; i<minx+length; i++ )
		{	if( *(image + j*col + i) == 0 )
			{//distance from left
				distance = i - minx;
				if( distance <= (length/5) )	feature[120]++;
				else if( distance <= ((2*length)/5) )	feature[121]++;
				else if( distance <= ((3*length)/5) )	feature[122]++;
				else if( distance <= ((4*length)/5) )	feature[123]++;
				else if( distance <= (length ))	feature[124]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[120], feature[121], feature[122], feature[123], feature[124] );
	
	for ( int j=miny+2*breadth; j<miny+3*breadth; j++ )
	{	
		for ( int i=minx+length-1; i>=minx; i--)
		{	
			//distance from right
			if( *(image + j*col + i) == 0 )
			{
				distance = (minx+length-1) - i;
				if( distance >= ((4*length)/5))	feature[125]++;
				else if ( distance >= ((3*length)/5))	feature[126]++;
				else if ( distance >= ((2*length)/5))	feature[127]++;
				else if ( distance >= (length/5))	feature[128]++;
				else if ( distance >= 0 )	feature[129]++;
			}
		}
		
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[125], feature[126], feature[127], feature[128], feature[129] );
	
	for ( int i=minx; i<minx+length; i++ )
	{	
		for ( int j=miny+2*breadth; j<miny+3*breadth; j++ )
		{	
			//distance from up
			if( *(image + j*col + i) == 0 )
			{
				distance = j - (miny+2*breadth);
				if( distance <= (breadth/5) )	feature[130]++;
				else if( distance <= ((2*breadth)/5) )	feature[131]++;
				else if( distance <= ((3*breadth)/5) )	feature[132]++;
				else if( distance <= ((4*breadth)/5) )	feature[133]++;
				else if( distance <= (breadth ))	feature[134]++;
			}
		}	
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[130], feature[131], feature[132], feature[133], feature[134] );
	
	for ( int i=minx+length-1; i>minx; i-- )
	{	
		for ( int j=miny+3*breadth-1; j>=miny+2*breadth; j-- )
		{	
			//distance from down
			if( *(image + j*col + i) == 0 )
			{
				distance = (miny+3*breadth-1) - j;
				if ( distance >= ((4*breadth)/5) )	feature[135]++;
				else if ( distance >= ((3*breadth)/5) )	feature[136]++;
				else if ( distance >= ((2*breadth)/5))	feature[137]++;
				else if ( distance >= (breadth/5) )	feature[138]++;
				else if ( distance >= 0 )	feature[139]++;	
			}
		}	
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[135], feature[136], feature[137], feature[138], feature[139] );
		
	//8th segment-----------------------------------------------------------------------------------
	for ( int j=miny+2*breadth; j<miny+3*breadth; j++ )
	{	for ( int i=minx+length; i<minx+2*length; i++ )
		{	if( *(image + j*col + i) == 0 )
			{//distance from left
				distance = i - (minx+length);
				if( distance <= (length/5) )	feature[140]++;
				else if( distance <= ((2*length)/5) )	feature[141]++;
				else if( distance <= ((3*length)/5) )	feature[142]++;
				else if( distance <= ((4*length)/5) )	feature[143]++;
				else if( distance <= (length ))	feature[144]++;
			}
		}	
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[140], feature[141], feature[142], feature[143], feature[144] );
	
	for ( int j=miny+2*breadth; j<miny+3*breadth; j++ )
	{	
		for ( int i=minx+2*length-1; i>=minx+length; i--)
		{	
			//distance from right
			if( *(image + j*col + i) == 0 )
			{
				distance = (minx+2*length-1) - i;
				if( distance >= ((4*length)/5) )	feature[145]++;
				else if ( distance >= ((3*length)/5) )	feature[146]++;
				else if ( distance >= ((2*length)/5) )	feature[147]++;
				else if ( distance >= (length/5) )	feature[148]++;
				else if ( distance >= 0 )	feature[149]++;
			}
		}	
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[145], feature[146], feature[147], feature[148], feature[149] );
	
	for ( int i=minx+length; i<minx+2*length; i++ )
	{	
		for ( int j=miny+2*breadth; j<miny+3*breadth; j++ )
		{	
			//distance from up
			if( *(image + j*col + i) == 0 )
			{
				distance = j - (miny+2*breadth);
				if( distance <= (breadth/5))	feature[150]++;
				else if( distance <= ((2*breadth)/5) )	feature[151]++;
				else if( distance <= ((3*breadth)/5) )	feature[152]++;
				else if( distance <= ((4*breadth)/5) )	feature[153]++;
				else if( distance <= (breadth ))	feature[154]++;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[150], feature[151], feature[152], feature[153], feature[154] );
	
	for ( int i=minx+2*length-1; i>minx+length; i-- )
	{	
		for ( int j=miny+3*breadth-1; j>=miny+2*breadth; j-- )
		{	
			//distance from down
			if( *(image + j*col + i) == 0 )
			{
				distance = (miny+3*breadth-1) - j;
				if ( distance >= ((4*breadth)/5) )	feature[155]++;
				else if ( distance >= ((3*breadth)/5) )	feature[156]++;
				else if ( distance >= ((2*breadth)/5) )	feature[157]++;
				else if ( distance >= (breadth/5))	feature[158]++;
				else if ( distance >= 0 )	feature[159]++;	
			}
		}	
	}	
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[155], feature[156], feature[157], feature[158], feature[159] );
	
	//9th segment
	for ( int j=miny+2*breadth; j<miny+3*breadth; j++ )
	{	for ( int i=minx+2*length; i<minx+3*length; i++ )
		{	if( *(image + j*col + i) == 0 )
			{//distance from left
				distance = i - (minx+2*length);
				if( distance <= (length/5) )	feature[160]++;
				else if( distance <= ((2*length)/5) )	feature[161]++;
				else if( distance <= ((3*length)/5) )	feature[162]++;
				else if( distance <= ((4*length)/5) )	feature[163]++;
				else if( distance <= (length ))	feature[164]++;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[160], feature[161], feature[162], feature[163], feature[164] );
	
	for ( int j=miny+2*breadth; j<miny+3*breadth; j++ )
	{	
		for ( int i=minx+3*length-1; i>=minx+2*length; i--)
		{	
			//distance from right
			if( *(image + j*col + i) == 0 )
			{
				distance = (minx+3*length-1) - i;
				if( distance >= ((4*length)/5) )	feature[165]++;
				else if ( distance >= ((3*length)/5) )	feature[166]++;
				else if ( distance >= ((2*length)/5) )	feature[167]++;
				else if ( distance >= (length/5))	feature[168]++;
				else if ( distance >= 0 )	feature[169]++;
			}
		}	
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[165], feature[166], feature[167], feature[168], feature[169] );
	
	for ( int i=minx+2*length; i<minx+3*length; i++ )
	{	
		for ( int j=miny+2*breadth; j<miny+3*breadth; j++ )
		{	
			//distance from up
			if( *(image + j*col + i) == 0 )
			{
				distance = j - (miny+2*breadth);
				if( distance <= (breadth/5) )	feature[170]++;
				else if( distance <= ((2*breadth)/5) )	feature[171]++;
				else if( distance <= ((3*breadth)/5) )	feature[172]++;
				else if( distance <= ((4*breadth)/5) )	feature[173]++;
				else if( distance <= (breadth ))	feature[174]++;
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[170], feature[171], feature[172], feature[173], feature[174] );
	
	for ( int i=minx+3*length-1; i>minx+2*length; i-- )
	{	
		for ( int j=miny+3*breadth-1; j>=miny+2*breadth; j-- )
		{	
			//distance from down
			if( *(image + j*col + i) == 0 )
			{
				distance = (miny+3*breadth-1) - j;
				if ( distance >= ((4*breadth)/5) )	feature[175]++;
				else if ( distance >= ((3*breadth)/5) )	feature[176]++;
				else if ( distance >= ((2*breadth)/5) )	feature[177]++;
				else if ( distance >= (breadth/5) )	feature[178]++;
				else if ( distance >= 0 )	feature[179]++;	
			}
		}
	}
	fprintf(fileptr,"%d,%d,%d,%d,%d,", feature[175], feature[176], feature[177], feature[178], feature[179] );
	//fprintf(fileptr,"ZERO\n");
	free(image);
}



void input_image ( char* S )
{
	FILE *fp; 
	int line_count=0, r=0, c=0 ;
	unsigned char ch ;
	
	fp = fopen ( S, "rb" );
	
	while( fread(&ch, sizeof(ch), 1, fp) == 1 )
	{
		if(ch == '\n')	++line_count ;
		if(line_count == 4) 	break;
	}
	
	while( fread(&ch, sizeof(ch), 1, fp) == 1)
	{
		*(image+r*col+c) = ch ;
		c++;
		while( c == col)
		{
			r++;
			c = 0;
		}
	}
	fclose(fp);
}
