#include <stdio.h>
#include <iostream>

#include <verilated.h>
#include "debug/obj_dir/VADDS.h"

using namespace std;

VADDS *adds_i;

unsigned long int pc;

double sc_time_stamp(){
	return pc;
}

void init(){
	adds_i->m_clock=0;
	adds_i->p_reset=0;
	adds_i->eval();
	adds_i->m_clock=1;
	adds_i->p_reset=1;
	adds_i->eval();
	adds_i->m_clock=0;
	adds_i->p_reset=0;
	adds_i->eval();
	pc=0;
}

void falling_clock(){
	adds_i->m_clock=0;
	adds_i->p_reset=1;
	adds_i->eval();
}

void rising_clock(){
	adds_i->m_clock=1;
	pc++;
	adds_i->eval();
}

void exe_adds(int ain, int bin){
	falling_clock();

	// input
	adds_i->a = ain;
	adds_i->b = bin;
	adds_i->exe = 1;
	
	rising_clock();

	// output
	printf("%d %d\n", adds_i->rs, adds_i->r);
}

int main(int argv,char *argc[]){
	adds_i = new VADDS();

	init();

	exe_adds(100, 200);
	exe_adds(1000, 2000);
	exe_adds(100000, 200000);

	return 0;
}

