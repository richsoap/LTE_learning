#include <stdio.h>
#include <sys/types.h>
#include <Circle.h>

static int write_out(const void *buffer, size_t size, void *app_key) {
	FILE* fp = app_key;
	size_t outSize = fwrite(buffer, 1, size, fp);
	return outSize==size?0:-1;
}

int main(int argc, char** argv) {
	Circle_t *circle;
	asn_enc_rval_t encoderReturn;
	circle = calloc(1, sizeof(Circle_t));
	assert(circle);
	circle->position_x = 25;
	circle->position_y = 14;
	circle->radius = 10;
	//////////////////////////////////
	FILE *fp = fopen("result.txt","wb");
	assert(fp);
	encoderReturn = der_encode(&asn_DEF_Circle, circle, write_out, fp);
	fclose(fp);
	if(encoderReturn.encoded == -1) {
		fprintf(stderr, "Something wrong!%s", encoderReturn.failed_type?encoderReturn.failed_type->name: "unknown");
		exit(1);
	}
	xer_fprint(stdout, &asn_DEF_Circle, circle);
	return 0;
}
