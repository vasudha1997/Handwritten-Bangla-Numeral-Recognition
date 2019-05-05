

//-------------------------./a.out <image>.newbound ----------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
int row, col;
int *image;

#include "myfunction_pgm.c"
#include "rccount.c"

typedef struct tPoint {
    int x, y;
} Point;
 
typedef struct tNode {
    Point data;
    struct tNode *next;
} Node;

void input_image( char* );
bool ccw(const Point *a, const Point *b, const Point *c);
int comp(const void *lhs, const void *rhs);
void freeNode(Node *ptr);
Node* pushBack(Node *ptr, Point data);
Node* popBack(Node *ptr);
Node* convexHull(int len, Point p[]) 
void print(Node *ptr) ;
void bresenham_line(int ,int ,int ,int ,int ); 
void build_output( char* );



int main(int argc, char* argv[]) 
{
	printf("hello ");
	count_rc( argv[1] );
	image = (int*) malloc (row*col*sizeof(int) );
	input_image( argv[1] );
	printf("done\n");
	int index = 0;
	
	Point points[300];
	for (int i=0; i<row; i++)
		for(int j=0; j<col; j++)
			if( *(image+i*col+j) == 0 )
			{
				points[index].x = i;
				points[index++].y = j;
				j+=2;
			}
	printf("index = %d\n", index);
    /*Point points[] = {
        {16,  3}, {12, 17}, { 0,  6}, {-4, -6}, {16,  6},
        {16, -7}, {16, -3}, {17, -4}, { 5, 19}, {19, -8},
        { 3, 16}, {12, 13}, { 3, -4}, {17,  5}, {-3, 15},
        {-3, -9}, { 0, 11}, {-9, -3}, {-4, -2}, {12, 10}
    };*/
 
    Node *hull = convexHull(sizeof(points) / sizeof(Point), points);
    printf("Convex Hull: ");
    print(hull);
    printf("\n");
    printf("hello");
    build_output(argv[1]);
    free(hull);
    //hull = NULL;
 
    return 0;
}

 
bool ccw(const Point *a, const Point *b, const Point *c) {
    return (b->x - a->x) * (c->y - a->y)
         > (b->y - a->y) * (c->x - a->x);
}
 
int comp(const void *lhs, const void *rhs) {
    Point lp = *((Point *)lhs);
    Point rp = *((Point *)rhs);
    if (lp.x < rp.x) return -1;
    if (rp.x < lp.x) return 1;
    return 0;
}
 
void freeNode(Node *ptr) {
    if (ptr == NULL) {
        return;
    }
 
    freeNode(ptr->next);
    ptr->next = NULL;
    free(ptr);
}
 
Node* pushBack(Node *ptr, Point data) {
    Node *tmp = ptr;
 
    if (ptr == NULL) {
        ptr = (Node*)malloc(sizeof(Node));
        ptr->data = data;
        ptr->next = NULL;
        return ptr;
    }
 
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
 
    tmp->next = (Node*)malloc(sizeof(Node));
    tmp->next->data = data;
    tmp->next->next = NULL;
    return ptr;
}
 
Node* popBack(Node *ptr) {
    Node *tmp = ptr;
 
    if (ptr == NULL) {
        return NULL;
    }
    if (ptr->next == NULL) {
        free(ptr);
        return NULL;
    }
 
    while (tmp->next->next != NULL) {
        tmp = tmp->next;
    }
 
    free(tmp->next);
    tmp->next = NULL;
    return ptr;
}
 
void print(Node *ptr) {
    int x1,y1,x2,y2,diffx,diffy,c=0;
    printf("[");
    if (ptr != NULL) {
        printf("(%d, %d)", ptr->data.x, ptr->data.y);
        x1 = ptr->data.x;
        y1 = ptr->data.y;
        ptr = ptr->next;
    }
    while (ptr != NULL) 
    {
    	c++;
        printf(", (%d, %d)", ptr->data.x, ptr->data.y);
        x2 = ptr->data.x;
        y2 = ptr->data.y;
        bresenham_line(x1,y1,x2,y2,col);
        ptr = ptr->next;
        
        x1 = x2;
        y1 = y2;
    }
    printf("]");
    printf("over");
  
    return ;
}

 
Node* convexHull(int len, Point p[]) {
    Node *h = NULL;
    Node *hptr = NULL;
    size_t hLen = 0;
    int i;
 
    qsort(p, len, sizeof(Point), comp);
 
    /* lower hull */
    for (i = 0; i < len; ++i) {
        while (hLen >= 2) {
            hptr = h;
            while (hptr->next->next != NULL) {
                hptr = hptr->next;
            }
            if (ccw(&hptr->data, &hptr->next->data, &p[i])) {
                break;
            }
 
            h = popBack(h);
            hLen--;
        }
 
        h = pushBack(h, p[i]);
        hLen++;
    }
 
    /* upper hull */
    for (i = len - 1; i >= 0; i--) {
        while (hLen >= 2) {
            hptr = h;
            while (hptr->next->next != NULL) {
                hptr = hptr->next;
            }
            if (ccw(&hptr->data, &hptr->next->data, &p[i])) {
                break;
            }
 
            h = popBack(h);
            hLen--;
        }
 
        h = pushBack(h, p[i]);
        hLen++;
    }
 
    popBack(h);
    return h;
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
	strcat(t, "hull");
	build_my_file( row, col );
	
	fp1 = fopen( t, "wb" );
	fp2 = fopen("myfile.dat", "rb");
	
	while( fread(&ch, sizeof(ch), 1, fp2) == 1 )
		fwrite( &ch, sizeof(ch), 1, fp1);
	for( i=0; i<row; i++)
		for( j=0; j<col; j++ )
		{
			mydata = *(image+i*col+j) ;
			fwrite( &mydata, sizeof(ch), 1,fp1 );
		}
			
}



void bresenham_line(int x1,int y1,int x2,int y2,int c)
{
	int dx,dy,x,y,d,dE,dNE; int i,j; 
	dx=(x1-x2<0)?x2-x1:x1-x2;
	dy=(y1-y2<0)?y2-y1:y1-y2;
  //printf("%d %d %d %d \n", x1, y1, x2, y2);
	if(dx>=dy)
	{
		if(y1<y2)
		{
			x1=x1+x2;
			x2=x1-x2;
			x1=x1-x2;

			y1=y1+y2;
			y2=y1-y2;
			y1=y1-y2;
		}

		if(x1<x2)	/* quad 1 */
		{
			d=2*dy+dx;
			dx=x2-x1;
			dy=y2-y1;
			dE=2*dy;
			dNE=2*(dy+dx);
			x=x1,y=y1;
                     
                        for(i=x-2;i<x+2;i++)
                          for(j=y-2;j<y+2;j++)
                           {
			    if (*(image+i*c+j)==255)  /* 0 = background */ 
			       *(image+i*c+j)=0;      /* 1 = foreground */
                           }

			while(x<x2)
			{
				if(d>=0)
				{
					x++;
					d+=dE;
				}
				else
				{
					x++;
					y--;
					d+=dNE;
				}
		        //if (*(image_out+x*c+y)==255) 
			//  *(image_out+x*c+y)=0;
                         for(i=x-2;i<x+2;i++)
                          for(j=y-2;j<y+2;j++)
                           {
			    if (*(image+i*c+j)==255)  /* 0 = background */ 
			       *(image+i*c+j)=0;      /* 1 = foreground */
                           }
			}

		}
		else		
		{
			dx=x2-x1;
			dy=y2-y1;
			d=dx-2*dy;
			dE=(2)*(-dy);
			dNE=2*(dx-dy);
			x=x1,y=y1;
			
                    for(i=x-2;i<x+2;i++)
                          for(j=y-2;j<y+2;j++)
                           {
			    if (*(image+i*c+j)==255)  /* 0 = background */ 
			       *(image+i*c+j)=0;      /* 1 = foreground */
                           }
			while(x>x2)
			{
				if(d<=0)	/* W */
				{
					x--;
					d+=dE;
				}
				else		/* NW*/
				{
					x--;
					y--;
					d+=dNE;
				}
                		for(i=x-2;i<x+2;i++)
                          for(j=y-2;j<y+2;j++)
                           {
			    if (*(image+i*c+j)==255)  /* 0 = background */ 
			       *(image+i*c+j)=0;      /* 1 = foreground */
                           }
			}
		}

	}

	else
	{
		if(y1<y2)
		{
			x1=x1+x2;
			x2=x1-x2;
			x1=x1-x2;

			y1=y1+y2;
			y2=y1-y2;
			y1=y1-y2;
		
		}
		
		if(x1<=x2)
		{
			dx=x2-x1;
			dy=y2-y1;
			d=dy+2*dx;
			dE=2*dx;
			dNE=2*(dy+dx);
			x=x1,y=y1;
			
                   for(i=x-2;i<x+2;i++)
                          for(j=y-2;j<y+2;j++)
                           {
			    if (*(image+i*c+j)==255)  /* 0 = background */ 
			       *(image+i*c+j)=0;      /* 1 = foreground */
                           }
			while(y>y2)
			{
				if(d<=0)
				{
					y--;
					d+=dE;
				}

				else
				{
					x++;
					y--;
					d+=dNE;
				}

				
				for(i=x-2;i<x+2;i++)
                          for(j=y-2;j<y+2;j++)
                           {
			    if (*(image+i*c+j)==255)  /* 0 = background */ 
			       *(image+i*c+j)=0;      /* 1 = foreground */
                           }
			}

		}
		else
		{
			dx=x2-x1;
			dy=y2-y1;
			d=2*dx-dy;
			dE=2*dx;
			dNE=2*(dx-dy);
			x=x1,y=y1;
			
			for(i=x-2;i<x+2;i++)
                          for(j=y-2;j<y+2;j++)
                           {
			    if (*(image+i*c+j)==255)  /* 0 = background */ 
			       *(image+i*c+j)=0;      /* 1 = foreground */
                           }

			while(y>y2)
			{
				if(d>=0)
				{
					y--;
					d+=dE;
				}
				else
				{
					x--;
					y--;
					d+=dNE;
				}
				
			for(i=x-2;i<x+2;i++)
                          for(j=y-2;j<y+2;j++)
                           {
			    if (*(image+i*c+j)==255)  /* 0 = background */ 
			       *(image+i*c+j)=0;      /* 1 = foreground */
                           }
			}

		}
	}

}



//drawHull(

