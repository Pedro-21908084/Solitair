#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MSG_WIN "You Win! Congratulations!"
#define MSG_LOSE "You Lost! Better luck next time!"

#define ARG_MIN 5
#define MED 0
#define MAX_RAND 10
#define MIN_RAND -10

typedef struct solitair
{
    int  *hl;
    int *hr;
    int *left;
    int *right;
}solitair;

/* needed functions */
double uniRand(void);
double randn(double, double);
int randn_sat(double, double, int, int);

void deckGenerator(solitair *deck, int max, int desv)
{
    int i;
    for(i=0;i<max;i++)
    {
        deck->left[i]=randn_sat(MED, desv, MIN_RAND, MAX_RAND);
        deck->right[i]=randn_sat(MED, desv, MIN_RAND, MAX_RAND);
    }
}

solitair *deckMaker(int row, int hold)
{
    solitair *deck;
    deck = calloc(2*hold+2*row,sizeof(int));

    deck->hl = calloc(hold, sizeof(int));
    deck->hr = calloc(hold, sizeof(int));
    deck->left = calloc(row, sizeof(int));
    deck->right = calloc(row, sizeof(int));
    
    return deck;
}

int main(int argc, char ** argv)
{	
	long seed = 7;
	int level = 3, nrows = 12, nhold = 2;
    char comand;
    solitair *baralho;
    int sum =10;

	/* verify command line arguments */
    if(argc >= ARG_MIN)
    {
        sscanf(argv[1], "%ld", &seed);
        sscanf(argv[2], "%d", &level);
        sscanf(argv[3], "%d", &nrows);
        sscanf(argv[4], "%d", &nhold);
    }

    printf("seed:%ld\nlevel:%d\nrows:%d\nhold:%d\n", seed, level, nrows, nhold);

	/* initialize random seed */
	srand(seed);

    /*deck generation*/
    baralho = deckMaker(nrows, nhold);
    deckGenerator(baralho, nrows, level);

    while(1)
    {
        scanf("%c", &comand);

        switch(comand)
        {
            case'a':
            case's':
            case'q':
            case'w':
            case'z':
            case'x':
            default:
                break;
        }


        if(sum<0||sum>21)
        {
            printf(MSG_LOSE);
            return 0;
        }
        /*read \n*/
        scanf("%c", &comand);
    }

	return 0;
}






/* function: uniRand()
 * return: double
 * parameters: none
 * description:
 * 	generate random number between within [0 - 1] 
 */
double uniRand()
{
	return (double) rand() / RAND_MAX;
}


/* function: randn()
 * return: double
 * parameters:
 * 	double mean - the mean of the normal distribution
 * 	double std - the standard deviation of the normal distribution
 * description:
 * 	generate random number following a normal distribuition using
 *	Box–Muller transform.
 */
#define PI 3.14159265358979
double randn(double mean, double std)
{
	double u1, u2, z;

	u1 = uniRand();
	u2 = uniRand();

	z =  sqrt(-2*log(u1))*cos(2*PI*u2);

	/* Multiply by the standard deviation and add the mean.*/
	return std * z + mean;
}


/* function: randn_sat()
 * return: int
 * parameters:
 * 	double mean - the mean of the normal distribution
 * 	double std - the standard deviation of the normal distribution
  * 	int min - the minimum value
 * 	int max - the maximum value
 * description:
 * 	generate random number following a normal distribuition and saturated
 * 	to the interval [min, max]
 */
int randn_sat(double mean, double std, int min, int max)
{
	double r = randn(mean, std);
	return (int) (r > max ? max : r < min ? min : r);
}

