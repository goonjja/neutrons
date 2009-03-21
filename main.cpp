/*
 * Neutrons shuffler
 *
 *  Created on: 21.03.2009
 *      Author: ultor
 */

#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include "lib/mt19937ar.h"
/*just comfortable*/
#define ulong unsigned long
#define rnd genrand_real1

//debug messages
//#define DEBUG_NEUTRONS

/*parameters*/
ulong H	= 1.7;				//толщина пластины
const float Es = 0.06;		//сечение рассеяния
const float Ec = 0.03;		//сечение поглощения
const float E = Ec + Es;	//полное сечение
const long N = 10000;		//число нейтронов
long Np=0,Nm=0,N0=0;		//N+,N-,N0

//проверка того, что распределение равномерное, чисто визуально (:
void test_randomizer(){int i=0;while(i<20){printf("%0.2f\n",2*rnd()-1);}}

//судьба нейтрона
void fly(float x0,float m0)
{
	float x1,m1,l;
	while(1)
	{
		l = -(1/E)*log(rnd());//длина свободного пробега
		x1 = x0 + l*m0;//считаем новую координату
		#ifdef DEBUG_NEUTRONS
			printf("x0=%5.1f,x1=%5.1f l=%5.3f m0=%5.3f\n",x0,x1,l,m0);
		#endif
		if(0<x1 && x1<H)//если нейтрон еще внутри пластины
		{
			if(rnd()<(Ec/E))//и он не поглотился
			{N0++;return;}
			else
			{
				m0 = 2*rnd()-1;//считаем новую траекторию
				x0=x1;
			}
		}
		else
		{
			if(x1<=0) Nm++;
			else Np++;
			return;
		}
	}
}

int main(void)
{
    int i;
    init_genrand(time(NULL));
    printf("MT init complete...\n");
    for(i=0;i<N;i++)
    {
    	fly(0,rnd());
    	printf("Neutron#%i completed...\n",i);
	}
	printf("==Result: N+=%10lu N-=%10lu N0=%10lu\n",Np,Nm,N0);
	printf("==Result: W+=%10.2f W-=%10.2f W0=%10.2f\n",(float)Np/N,(float)Nm/N,(float)N0/N);
    return 0;
}
