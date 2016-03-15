#include <stdio.h>
#include <iostream>

#include <verilated.h>
#include "debug/obj_dir/VMULS_FIXP.h"

#define PLUS	0
#define MINUS	1

using namespace std;

VMULS_FIXP *mulf_i;

unsigned long int pc;

double sc_time_stamp(){
	return pc;
}

void init(){
	mulf_i->m_clock=0;
	mulf_i->p_reset=0;
	mulf_i->eval();
	mulf_i->m_clock=1;
	mulf_i->p_reset=1;
	mulf_i->eval();
	mulf_i->m_clock=0;
	mulf_i->p_reset=0;
	mulf_i->eval();
	pc=0;
}

void falling_clock(){
	mulf_i->m_clock=0;
	mulf_i->p_reset=1;
	mulf_i->eval();
}

void rising_clock(){
	mulf_i->m_clock=1;
	pc++;
	mulf_i->eval();
}

void exe_mulf(int asin, int ain, int bsin, int bin){
	falling_clock();

	// input
	mulf_i->as = asin;
	mulf_i->a = ain;
	mulf_i->bs = bsin;
	mulf_i->b = bin;
	mulf_i->exe = 1;
	
	rising_clock();

	// output
	printf("%d %x\n", mulf_i->rs, mulf_i->r);
}

int main(int argv,char *argc[]){
	mulf_i = new VMULS_FIXP();

	init();

	exe_mulf(PLUS, 0x10000, PLUS, 0x20000);
	exe_mulf(MINUS, 0x10000, PLUS, 0x20000);
	exe_mulf(PLUS, 0x10000, MINUS, 0x20000);
	exe_mulf(MINUS, 0x10000, MINUS, 0x20000);
	exe_mulf(PLUS, 100, PLUS, 0);
	exe_mulf(MINUS, 100, PLUS, 0);
	exe_mulf(PLUS, 100, MINUS, 0);
	exe_mulf(MINUS, 100, MINUS, 0);


	return 0;
}

