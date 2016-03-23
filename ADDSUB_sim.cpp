#include <stdio.h>
#include <iostream>

#include <verilated.h>
#include "debug/obj_dir/VADDSUB.h"

#define PLUS	0
#define MINUS	1

using namespace std;

VADDSUB *as_i;

unsigned long int pc;

double sc_time_stamp(){
	return pc;
}

void init(){
	as_i->m_clock=0;
	as_i->p_reset=0;
	as_i->eval();
	as_i->m_clock=1;
	as_i->p_reset=1;
	as_i->eval();
	as_i->m_clock=0;
	as_i->p_reset=0;
	as_i->eval();
	pc=0;
}

void falling_clock(){
	as_i->m_clock=0;
	as_i->p_reset=1;
	as_i->eval();
}

void rising_clock(){
	as_i->m_clock=1;
	pc++;
	as_i->eval();
}

void exe_adds(int asin, int ain, int bsin, int bin){
	falling_clock();

	// input
	as_i->as = asin;
	as_i->a = ain;
	as_i->bs = bsin;
	as_i->b = bin;
	as_i->exe = 1;
	
	rising_clock();

	// output
	printf("%d %d\n", as_i->rs, as_i->r);
}

int main(int argv,char *argc[]){
	as_i = new VADDSUB();

	init();

	exe_adds(PLUS, 0, PLUS, 0);
	exe_adds(MINUS, 0, PLUS, 0);
	exe_adds(PLUS, 0, MINUS, 0);
	exe_adds(MINUS, 0, MINUS, 0);

	exe_adds(PLUS, 10, PLUS, 20);
	exe_adds(MINUS, 10, PLUS, 20);
	exe_adds(PLUS, 10, MINUS, 20);
	exe_adds(MINUS, 10, MINUS, 20);

	return 0;
}

