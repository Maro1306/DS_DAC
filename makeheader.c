#include <stdio.h>
#include <math.h>

#define FPGAFREQ	50000000.0
#define COUNT		16.0

#define IWIDTH		3	// 整数部ビット幅
#define DWIDTH		17	// 小数部ビット幅
#define WIDTH		IWIDTH+DWIDTH
#define RESO		4.0	// 分解能

#define CUT_BEGIN	(WIDTH)*2-1-IWIDTH
#define CUT_END		DWIDTH

#define VCC			3.3
#define GND			0.0

#define R			1000.0		// 1kΩ
#define C			0.0000001	// 0.1μF

int roundOff(double x){
	return (int)(x + 0.5);
}

int int2bin(int x){
	if(x==0) return 0;
	else return int2bin(x/2) * 10 + (x % 2);	
}

char *dec2bin(double x){
	static char result[DWIDTH] = {0};
	double y = x;
	int i;

	for(i=0 ; i<DWIDTH ; i++){
		y = y * 2.0;
		if(y >= 1.0){
			result[i] = '1';
			y = y - 1.0;
		}
		else result[i] = '0';
	}
	
	return result;
}

int main(void){
	FILE *fps, *fpc;
	char *filenames = "sound.h";
	char *filenamec = "constant.h";

	double sound_do = FPGAFREQ/(261.6*COUNT);
	double sound_re = FPGAFREQ/(293.7*COUNT);
	double sound_mi = FPGAFREQ/(329.6*COUNT);
	double sound_fa = FPGAFREQ/(349.2*COUNT);
	double sound_so = FPGAFREQ/(392.0*COUNT);
	double sound_la = FPGAFREQ/(440.0*COUNT);
	double sound_ti = FPGAFREQ/(493.9*COUNT);

	double coef_ct     = VCC / (pow(2.0, RESO) - 1);
	double coef_cv1    = 1.0 / FPGAFREQ / (R * C);
	double coef_cv2    = 1.0 - coef_cv1;

	fps = fopen(filenames, "w");

	fprintf(fps, "#define DO	3'd0\n");
	fprintf(fps, "#define RE	3'd1\n");
	fprintf(fps, "#define MI	3'd2\n");
	fprintf(fps, "#define FA	3'd3\n");
	fprintf(fps, "#define SO	3'd4\n");
	fprintf(fps, "#define LA	3'd5\n");
	fprintf(fps, "#define TI	3'd6\n\n");

	fprintf(fps, "#define CYCLE_DO	14'd%d\n", roundOff(sound_do));
	fprintf(fps, "#define CYCLE_RE	14'd%d\n", roundOff(sound_re));
	fprintf(fps, "#define CYCLE_MI	14'd%d\n", roundOff(sound_mi));
	fprintf(fps, "#define CYCLE_FA	14'd%d\n", roundOff(sound_fa));
	fprintf(fps, "#define CYCLE_SO	14'd%d\n", roundOff(sound_so));
	fprintf(fps, "#define CYCLE_LA	14'd%d\n", roundOff(sound_la));
	fprintf(fps, "#define CYCLE_TI	14'd%d\n", roundOff(sound_ti));

	fclose(fps);
	printf("sound.h生成完了\n");

	fpc = fopen(filenamec, "w");

	fprintf(fpc, "#define IWIDTH		%d\n", IWIDTH);
	fprintf(fpc, "#define DWIDTH		%d\n", DWIDTH);
	fprintf(fpc, "#define WIDTH		%d\n", WIDTH);
	fprintf(fpc, "#define RESO		%d\n\n", (int)RESO);

	fprintf(fpc, "#define PLUS		1'b0\n");
	fprintf(fpc, "#define MINUS		1'b1\n\n");

	fprintf(fpc, "#define CUT_BEGIN	%d\n", CUT_BEGIN);
	fprintf(fpc, "#define CUT_END		%d\n\n", CUT_END);

	fprintf(fpc, "#define VCC			%d'b%03d", WIDTH, int2bin((int)VCC));
	fprintf(fpc, "%s", dec2bin(VCC-(int)VCC));
	fprintf(fpc, "	// %lf\n", VCC);
	fprintf(fpc, "#define GND			%d'b%03d", WIDTH, int2bin((int)GND));
	fprintf(fpc, "%s", dec2bin(GND-(int)GND));
	fprintf(fpc, "	// %lf\n\n", GND);

	fprintf(fpc, "#define COEF_CT		%d'b%03d", WIDTH, int2bin((int)coef_ct));
	fprintf(fpc, "%s", dec2bin(coef_ct-(int)coef_ct));
	fprintf(fpc, "	// %lf\n", coef_ct);
	fprintf(fpc, "#define COEF_CV1	%d'b%03d", WIDTH, int2bin((int)coef_cv1));
	fprintf(fpc, "%s", dec2bin(coef_cv1-(int)coef_cv1));
	fprintf(fpc, "	// %lf\n", coef_cv1);
	fprintf(fpc, "#define COEF_CV2	%d'b%03d", WIDTH, int2bin((int)coef_cv2));
	fprintf(fpc, "%s", dec2bin(coef_cv2-(int)coef_cv2));
	fprintf(fpc, "	// %lf\n", coef_cv2);
	
	fclose(fpc);
	printf("constant.h生成完了\n");

	return 0;
}
