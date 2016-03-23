#include <stdio.h>

#define FPGAFREQ	50000000.0
#define COUNT		16.0

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

	fprintf(fp, "#define DO	3'd0\n");
	fprintf(fp, "#define RE	3'd1\n");
	fprintf(fp, "#define MI	3'd2\n");
	fprintf(fp, "#define FA	3'd3\n");
	fprintf(fp, "#define SO	3'd4\n");
	fprintf(fp, "#define LA	3'd5\n");
	fprintf(fp, "#define TI	3'd6\n\n");

	fprintf(fp, "#define CYCLE_DO	14'd%d\n", roundOff(sound_do));
	fprintf(fp, "#define CYCLE_RE	14'd%d\n", roundOff(sound_re));
	fprintf(fp, "#define CYCLE_MI	14'd%d\n", roundOff(sound_mi));
	fprintf(fp, "#define CYCLE_FA	14'd%d\n", roundOff(sound_fa));
	fprintf(fp, "#define CYCLE_SO	14'd%d\n", roundOff(sound_so));
	fprintf(fp, "#define CYCLE_LA	14'd%d\n", roundOff(sound_la));
	fprintf(fp, "#define CYCLE_TI	14'd%d\n", roundOff(sound_ti));

	fclose(fp);

	return 0;
}
