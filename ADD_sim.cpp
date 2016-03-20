#include <stdio.h>
#include <iostream>

#include <verilated.h>
#include "debug/obj_dir/VADD.h"

using namespace std;

VADD *add_i;

unsigned long int pc;

double sc_time_stamp(){
	return pc;
}

void init(){
	add_i->m_clock=0;
	add_i->p_reset=0;
	add_i->eval();
	add_i->m_clock=1;
	add_i->p_reset=1;
	add_i->eval();
	add_i->m_clock=0;
	add_i->p_reset=0;
	add_i->eval();
	pc=0;
}

void falling_clock(){
	add_i->m_clock=0;
	add_i->p_reset=1;
	add_i->eval();
}

void rising_clock(){
	add_i->m_clock=1;
	pc++;
	add_i->eval();
}

void exe_add(int ain, int bin){
	falling_clock();

	// input
	add_i->a = ain;
	add_i->b = bin;
	add_i->exe = 1;
	
	rising_clock();

	// output
	printf("%4d %4d %1d %6d\n",ain, bin, add_i->carry, add_i->r);
}

int main(int argv,char *argc[]){
	add_i = new VADD();

	init();

	exe_add(100,200);
	exe_add(300,400);
	exe_add(500,600);
	exe_add(700,800);
	exe_add(900,1000);

	return 0;
}

