#include <stdio.h>
#include <iostream>

#include <verilated.h>
#include "debug/obj_dir/VPLAYTONE_ST.h"

#define DO	0
#define RE	1
#define MI	2
#define FA	3
#define SO	4
#define LA	5
#define TI	6

using namespace std;

VPLAYTONE_ST *ptst_i;

unsigned long int pc;

double sc_time_stamp(){
	return pc;
}

void init(){
	ptst_i->m_clock=0;
	ptst_i->p_reset=0;
	ptst_i->eval();
	ptst_i->m_clock=1;
	ptst_i->p_reset=1;
	ptst_i->eval();
	ptst_i->m_clock=0;
	ptst_i->p_reset=0;
	ptst_i->eval();
	pc=0;
}

void falling_clock(){
	ptst_i->m_clock=0;
	ptst_i->p_reset=1;
	ptst_i->eval();
}

void rising_clock(){
	ptst_i->m_clock=1;
	pc++;
	ptst_i->eval();
}

int main(int argv,char *argc[]){
	ptst_i = new VPLAYTONE_ST();
	int i;

	init();

	for(i=0 ; i<120000 ; i++){
		falling_clock();
		ptst_i->tone = LA;
		ptst_i->play = 1;
		rising_clock();

		printf("count:%5d vd:%3d \n", i, ptst_i->vd);
	}

	return 0;
}

