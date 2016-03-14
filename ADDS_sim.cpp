#include <stdio.h>
#include <iostream>

#include <verilated.h>
#include "debug/obj_dir/VADDER.h"

using namespace std;

VADDER *adder_i;

unsigned long int pc;

double sc_time_stamp(){
	return pc;
}

void init(){
	adder_i->m_clock=0;
	adder_i->p_reset=0;
	adder_i->eval();
	adder_i->m_clock=1;
	adder_i->p_reset=1;
	adder_i->eval();
	adder_i->m_clock=0;
	adder_i->p_reset=0;
	adder_i->eval();
	pc=0;
}

void falling_clock(){
	adder_i->m_clock=0;
	adder_i->p_reset=1;
	adder_i->eval();
}

void rising_clock(){
	adder_i->m_clock=1;
	pc++;
	adder_i->eval();
}

int main(int argv,char *argc[]){

	int i = 0;
	adder_i = new VADDER();

	init();

	while(i <= 0x5){
		falling_clock();

		//input
		adder_i->a = i;
		adder_i->b = i+1;
		adder_i->exe = 1;

		rising_clock();

		//output
		printf("%d %d\n", adder_i->c, adder_i->s);

		i++;
	}
	return 0;
}

