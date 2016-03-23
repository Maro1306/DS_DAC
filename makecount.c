#include <stdio.h>

#define FPGAFREQ	50000000.0
#define COUNT		30.0

int roundOff(double x){
	return (int)(x + 0.5);
}

int main(void){
	FILE *fp;
	char *filename = "sound.h";

	double sound_do = FPGAFREQ/(261.6*COUNT);
	double sound_re = FPGAFREQ/(293.7*COUNT);
	double sound_mi = FPGAFREQ/(329.6*COUNT);
	double sound_fa = FPGAFREQ/(349.2*COUNT);
	double sound_so = FPGAFREQ/(392.0*COUNT);
	double sound_la = FPGAFREQ/(440.0*COUNT);
	double sound_ti = FPGAFREQ/(493.9*COUNT);

	fp = fopen(filename, "w");

	fprintf(fp, "#define DO	13'd%d\n", roundOff(sound_do));
	fprintf(fp, "#define RE	13'd%d\n", roundOff(sound_re));
	fprintf(fp, "#define MI	13'd%d\n", roundOff(sound_mi));
	fprintf(fp, "#define FA	13'd%d\n", roundOff(sound_fa));
	fprintf(fp, "#define SO	13'd%d\n", roundOff(sound_so));
	fprintf(fp, "#define LA	13'd%d\n", roundOff(sound_la));
	fprintf(fp, "#define TI	13'd%d\n", roundOff(sound_ti));

	fclose(fp);

	return 0;
}
