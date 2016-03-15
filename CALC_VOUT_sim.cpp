#include <stdio.h>
#include <iostream>

#include <verilated.h>
#include "debug/obj_dir/VCALC_VOUT.h"

using namespace std;

VCALC_VOUT *cvo_i;

unsigned long int pc;

double sc_time_stamp(){
	return pc;
}

void init(){
	cvo_i->m_clock=0;
	cvo_i->p_reset=0;
	cvo_i->eval();
	cvo_i->m_clock=1;
	cvo_i->p_reset=1;
	cvo_i->eval();
	cvo_i->m_clock=0;
	cvo_i->p_reset=0;
	cvo_i->eval();
	pc=0;
}

void falling_clock(){
	cvo_i->m_clock=0;
	cvo_i->p_reset=1;
	cvo_i->eval();
}

void rising_clock(){
	cvo_i->m_clock=1;
	pc++;
	cvo_i->eval();
}

int main(int argv,char *argc[]){
	cvo_i = new VCALC_VOUT();

	init();

	falling_clock();
	cvo_i->vi = 1;
	cvo_i->exe = 1;
	rising_clock();
	printf("%x %d\n", cvo_i->vo, cvo_i->v__DOT__flag);

	falling_clock();
	cvo_i->vi = 1;
	cvo_i->exe = 1;
	rising_clock();
	printf("%x %d\n", cvo_i->vo, cvo_i->v__DOT__flag);

	falling_clock();
	cvo_i->vi = 1;
	cvo_i->exe = 1;
	rising_clock();
	printf("%x %d\n", cvo_i->vo, cvo_i->v__DOT__flag);

	return 0;
}

