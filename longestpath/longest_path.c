//EDWARDS AMES
//CSC 220 Algorithms
#include <stdio.h>
#include <math.h>

typedef struct point
{
    double x; double y;
    int line1; int line2;
    double length;
}point;

void bubbleSort(point *p, int length);
void longest_path(int n, int * a, int * b , int * c);
double distanceFormula(point p1, point p2);

void longest_path(int n, int * a, int * b , int * c)
{
    point pnts[210];
    int i = 0, j = 0;
    double tmp_x, tmp_x2;
    double tmp_y, tmp_y2;

    int current = 1;
    //Double "for" loop to calculate all intersection points
    for ( i = 0; i < n; i ++ )
    {
        for (j = i+1 ; j < n ; j++)
        {
            tmp_x = ( b[j]*c[i] ) - ( b[i]*c[j] );
            tmp_x2 = ( a[i]* b[j] ) - ( a[j]*b[i] );
            pnts[current].x = tmp_x / tmp_x2;

            tmp_y = ( a[i]*c[j] ) - ( a[j]*c[i] );
            tmp_y2 = ( a[i]* b[j] ) - ( a[j]*b[i] );
            pnts[current].y =  tmp_y / tmp_y2 ;

            pnts[current].line1 = i;
            pnts[current].line2 = j;

            pnts[current].length = 0;

            current ++;
        }
        j = i+1;
    }

    //bubbleSort to sort them in increasing x coordinate
    bubbleSort(pnts, 191);

    int tmpLine = 0;
    int tmpLine2 = 0;
    point signal;

    //Calculating Length of each intersection point
    for ( i = 0 ; i < 190 ; i++)
    {
        signal = pnts[i];
        tmpLine = pnts[i].line1;
        tmpLine2 = pnts[i].line2;

        for( j = 0 ; j < 190 ; j++)
        {
            if ( tmpLine == pnts[j].line1 && signal.x > pnts[j].x)
            {
                if( pnts[j].length + ( distanceFormula(signal, pnts[j] ) > signal.length ) )
                {
                    pnts[i].length = pnts[j].length + ( distanceFormula( signal, pnts[j] ) );
                }
            }

            if ( tmpLine2 == pnts[j].line2 && signal.x > pnts[j].x)
            {
                if( pnts[j].length + ( distanceFormula(signal, pnts[j] ) > signal.length ) )
                {
                    pnts[i].length = pnts[j].length + ( distanceFormula( signal, pnts[j] ) );
                }
            }
        }
    }

    point pivot;
    pivot = pnts[189];
    point final[37];

    //Loop to find Path
    i = 0;
    for (j = 189; j>=0; j--)
    {
        if( pivot.line1 == pnts[j].line1 || pivot.line2 == pnts[j].line2)
        {
            final[i] = pnts[j];
            pivot = pnts[j];
            i++;
        }
    }
    //Loop to print path
    for (i = 37; i >= 0; i--)
    {
        printf(" x = %f  y = %f  line_1: %d  line_2: %d  length: %f\n", final[i].x, final[i].y, final[i].line1, final[i].line2, final[i].length);
    }
}

void bubbleSort(point *p, int length)
{
    point temp;
    int c, i;
    c = length - 1;

    for ( i = 0; i < c*c; i++ )
    {
        if( (p[i%c].x) > p[(i%c)+1].x)
        {
            temp = p[i%c];
            p[i%c] = p[(i%c)+1];
            p[(i%c)+1] = temp;

        }
    }
}

double distanceFormula(point p1, point p2 )
{
    double result;
    result = (sqrt(pow( p2.x - p1.x, 2)) + pow(p2.y - p1.y, 2) );
    return result;
}

int main(void)
{
    int a[20],b[20],c[20];
    int i;

    for( i=0; i<20; i++)
    {
        a[i] = (20-i);
        b[i] = -1*(i+1);
        c[i] = a[i]*b[i];
    }

    printf("calling longest_path()\n");

    longest_path(20, &(a[0]), &(b[0]), &(c[0]));

    printf(" longest path should start intersection line 18 and 19, then continue\n");
    printf("along line 19 to its intersection with line 0, end at intersection line 0 and line 1.\n");
    printf("End Test\n");

}
