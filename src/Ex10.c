/* 实现遗传算法，并求解方程 f(x1,x2,x3)=x1^2-x1*x2+x3的最大值 */
/* 在Linux下用gcc编译请使用gcc Ex10.c -lm -o Ex10命令 */
/* 数据请从同级目录下的gadata.txt输入，gadata.txt需要自己创建 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define POPSIZE 50
#define MAXGENS 1000
#define NVARS 3
#define PXOVER 0.8
#define PMUTATION 0.15
#define TRUE 1
#define FALSE 0

int generation;
int cur_best;
FILE *galog;

struct genotype
{
	double gene[NVARS];
	double fitness;
	double upper[NVARS];
	double lower[NVARS];
	double rfitness;
	double cfitness;
};

struct genotype population[POPSIZE+1];
struct genotype newpopulation[POPSIZE+1];

void initialize(void);
double randval(double, double);
void evaluate(void);
void keep_the_best(void);
void elitist(void);
void _select(void);
void crossover(void);
void Xover(int,int);
void swap(double *, double *);
void mutate(void);
void report(void);

void initialize(void)
{
	FILE *infile;
	int i, j;
	double lbound, ubound;
	
	if ((infile = fopen("gadata.txt","r"))==NULL)
	{
		fprintf(galog,"/nCannot open input file!/n");
		exit(1);
	}
	
	/* initialize variables within the bounds */
	
	for (i = 0; i < NVARS; i++)
	{
		fscanf(infile, "%lf",&lbound);
		fscanf(infile, "%lf",&ubound);
		
		for (j = 0; j < POPSIZE; j++)
		{
			population[j].fitness = 0;
			population[j].rfitness = 0;
			population[j].cfitness = 0;
			population[j].lower[i] = lbound;
			population[j].upper[i]= ubound;
			population[j].gene[i] = randval(population[j].lower[i],
				population[j].upper[i]);
		}
	}
	
	fclose(infile);
}

double randval(double low, double high)
{
	double val;
	val = ((double)(rand()%1000)/1000.0)*(high - low) + low;
	//	val = ((double)(rand()%(1000+1))/1000.0)*(high - low) + low;
	return(val);
}

void evaluate(void)
{
	int mem;
	int i;
	double x[NVARS+1];
	
	for (mem = 0; mem < POPSIZE; mem++)
	{
		for (i = 0; i < NVARS; i++)
            x[i+1] = population[mem].gene[i];
		
		population[mem].fitness = (x[1]*x[1]) - (x[1]*x[2]) + x[3];
	}
}

void keep_the_best()
{
	int mem;
	int i;
	cur_best = 0; /* stores the index of the best individual */
	
	for (mem = 0; mem < POPSIZE; mem++)
	{
		if (population[mem].fitness > population[POPSIZE].fitness)
		{
            cur_best = mem;
            population[POPSIZE].fitness = population[mem].fitness;
		}
	}
	/* once the best member in the population is found, copy the genes */
	for (i = 0; i < NVARS; i++)
		population[POPSIZE].gene[i] = population[cur_best].gene[i];
}

void elitist()
{
	int i;
	double best, worst;
	int best_mem, worst_mem;
	
	best = population[0].fitness;
	worst = population[0].fitness;
	for (i = 0; i < POPSIZE - 1; ++i)
	{
		if(population[i].fitness > population[i+1].fitness)
		{      
            if (population[i].fitness >= best)
			{
				best = population[i].fitness;
				best_mem = i;
			}
            if (population[i+1].fitness <= worst)
			{
				worst = population[i+1].fitness;
				worst_mem = i + 1;
			}
		}
		else
		{
            if (population[i].fitness <= worst)
			{
				worst = population[i].fitness;
				worst_mem = i;
			}
            if (population[i+1].fitness >= best)
			{
				best = population[i+1].fitness;
				best_mem = i + 1;
			}
		}
	}

	if (best >= population[POPSIZE].fitness)
    {
		for (i = 0; i < NVARS; i++)
			population[POPSIZE].gene[i] = population[best_mem].gene[i];
		population[POPSIZE].fitness = population[best_mem].fitness;
    }
	else
    {
		for (i = 0; i < NVARS; i++)
			population[worst_mem].gene[i] = population[POPSIZE].gene[i];
		population[worst_mem].fitness = population[POPSIZE].fitness;
    } 
}

void _select(void)
{
	int mem, i, j, k;
	double sum = 0;
	double p;
	

	for (mem = 0; mem < POPSIZE; mem++)
	{
		sum += population[mem].fitness;
	}
	

	for (mem = 0; mem < POPSIZE; mem++)
	{
		population[mem].rfitness =  population[mem].fitness/sum;
	}
	population[0].cfitness = population[0].rfitness;
	

	for (mem = 1; mem < POPSIZE; mem++)
	{
		population[mem].cfitness =  population[mem-1].cfitness +       
			population[mem].rfitness;
	}
	

	
	for (i = 0; i < POPSIZE; i++)
	{ 
		p = rand()%1000/1000.0;
		if (p < population[0].cfitness)
            newpopulation[i] = population[0];      
		else
		{
            for (j = 0; j < POPSIZE;j++)      
				if (p >= population[j].cfitness && 
					p<population[j+1].cfitness)
					newpopulation[i] = population[j+1];
		}
	}

	
	for (i = 0; i < POPSIZE; i++)
		population[i] = newpopulation[i];      
}

void crossover(void)
{
	int i, mem, one;
	int first  =  0;
	double x;
	
	for (mem = 0; mem < POPSIZE; ++mem)
	{
		x = rand()%1000/1000.0;
		if (x < PXOVER)
		{
            ++first;
            if (first % 2 == 0)
				Xover(one, mem);
            else
				one = mem;
		}
	}
}

void Xover(int one, int two)
{
	int i;
	int point;

	if(NVARS > 1)
	{
		if(NVARS == 2)
			point = 1;
		else
			point = (rand() % (NVARS - 1)) + 1;
		
		for (i = 0; i < point; i++)
			swap(&population[one].gene[i], &population[two].gene[i]);
		
	}
}

void swap(double *x, double *y)
{
	double temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
	
}

void mutate(void)
{
	int i, j;
	double lbound, hbound;
	double x;
	
	for (i = 0; i < POPSIZE; i++)
		for (j = 0; j < NVARS; j++)
		{
            x = rand()%1000/1000.0;
            if (x < PMUTATION)
			{
				lbound = population[i].lower[j];
				hbound = population[i].upper[j];  
				population[i].gene[j] = randval(lbound, hbound);
			}
		}
}

void report(void)
{
	int i;
	double best_val;
	double avg;
	double stddev;
	double sum_square;
	double square_sum;
	double sum;
	
	sum = 0.0;
	sum_square = 0.0;
	
	for (i = 0; i < POPSIZE; i++)
	{
		sum += population[i].fitness;
		sum_square += population[i].fitness * population[i].fitness;
	}
	
	avg = sum/(double)POPSIZE;
	square_sum = avg * avg * POPSIZE;
	stddev = sqrt((sum_square - square_sum)/(POPSIZE - 1));
	best_val = population[POPSIZE].fitness;
	
	fprintf(galog, "\n%5d,      %6.3f, %6.3f, %6.3f %6.3f, %6.3f\n\n", generation,best_val, avg, 
		square_sum,sum_square,stddev);
}

void main(void)
{
	int i;
	
	if ((galog = fopen("galog.txt","w"))==NULL)
	{
		exit(1);
	}
	generation = 0;
	
	fprintf(galog, "\n generation  best  average  standard \n");
	fprintf(galog, " number      value fitness  deviation \n");
	
	initialize();
	evaluate();
	keep_the_best();
	while(generation<MAXGENS)
	{
		generation++;
		_select();
		crossover();
		mutate();
		report();
		evaluate();
		elitist();
	}
	fprintf(galog,"\n\n Simulation completed\n");
	fprintf(galog,"\n Best member: \n");
	
	for (i = 0; i < NVARS; i++)
	{
		fprintf (galog,"\n var(%d) = %3.3f",i,population[POPSIZE].gene[i]);
	}
	fprintf(galog,"\n\n Best fitness = %3.3f",population[POPSIZE].fitness);
	fclose(galog);
	printf("Success\n");
}