#include <stdio.h>
#include <iostream>

#include <verilated.h>
#include "debug/obj_dir/VDS_DAC.h"

#define TARGET	10

using namespace std;

VDS_DAC *dac_i;

unsigned long int pc;

double sc_time_stamp(){
	return pc;
}

void init(){
	dac_i->m_clock=0;
	dac_i->p_reset=0;
	dac_i->eval();
	dac_i->m_clock=1;
	dac_i->p_reset=1;
	dac_i->eval();
	dac_i->m_clock=0;
	dac_i->p_reset=0;
	dac_i->eval();
	pc=0;
}

void falling_clock(){
	dac_i->m_clock=0;
	dac_i->p_reset=1;
	dac_i->eval();
}

void rising_clock(){
	dac_i->m_clock=1;
	pc++;
	dac_i->eval();
}

int main(int argv,char *argc[]){
	dac_i = new VDS_DAC();
	int i;

	init();

	for(i=0 ; i<5000 ; i++){
		falling_clock();
		dac_i->targetd = TARGET;
		dac_i->exe = 1;
		rising_clock();
	}

	for(i=5000 ; i<7000 ; i++){
		falling_clock();
		dac_i->targetd = TARGET;
		dac_i->exe = 1;
		rising_clock();

		printf("%d ", dac_i->targetd);
		printf("%x ", dac_i->v__DOT___ct_targeta);
		printf("%d %x\n", dac_i->vi, dac_i->v__DOT___cvo_vo);
	}

	return 0;
}

