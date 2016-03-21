#include <stdio.h>
#include <math.h>
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

double int2dec(int x){
	int i;
	double s = 0;

	for(i=-17 ; i<=2 ; i++){
		if(x % 2) s += pow(2.0, (double)i);
		x = x / 2;
	}

	return s;
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
	

	for(i=5000 ; i<6000 ; i++){
		falling_clock();
		dac_i->targetd = TARGET;
		dac_i->exe = 1;
		rising_clock();

		printf("%2d ", dac_i->targetd);
		printf("%5x ", dac_i->v__DOT___ct_targeta);
		printf("%1d %5x ", dac_i->vi, dac_i->v__DOT___cvo_vo);
		printf("%1.7lf\n", int2dec(dac_i->v__DOT___cvo_vo));
	}

	return 0;
}

