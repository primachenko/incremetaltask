#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"

int main(int argc, char const *argv[])
{
	if (argc != 7)
	{
		printf("too few arg\nuse ./calc timeStep lineStep targetTime length initTemp averTemp");
		return ERRFEWARG;
	}
	initParam param;
	if (ERRINIT == initParamStruct(&param, argv, argc)) return ERRBADARG;
	printParam(param);
	printf("init of the matrix taking into account the initial parameters..\n");
	double **data = NULL;
	data = (double**)malloc(param.layers*sizeof(double*));
	if (!data) return ERRMEMALL;
	for(int i = 0; i <= param.layers; i++)
	{
		data[i] = (double*)malloc(param.nodes*sizeof(double));
		if (!data[i]) return ERRMEMALL;
	}
	initMtx(data, &param);
	printMtx(data, &param);
	calculating(data, &param);
	printMtx(data, &param);
	freeMem(data, &param);
	return ERRNO;
}

int initParamStruct(initParam *param, char const *argv[], int argc)
{
	param->lineStep = atof(argv[1]);
	param->timeStep = atof(argv[2]);
	param->targetTime = atof(argv[3]);
	param->length = atof(argv[4]);
	param->initTemp = atof(argv[5]);
	param->averTemp = atof(argv[6]);
	if (param->targetTime <= 0 || param->length <= 0 
		|| param->lineStep <= 0 || param->timeStep <= 0 
		|| param->initTemp < -273 || param->averTemp < -273) 
		return ERRINIT;
	printf("\ncalculating matrix parametrs..\n");
	param->nodes = (int) ceil(param->length/param->lineStep);
	param->layers = (int) ceil(param->targetTime / param->timeStep);
	return ERRNO;
}

void initMtx(double **data, initParam* param)
{
	for(int l = param->layers; l >= 0 ; l--)
	{
		for(int n = param->nodes-1; n >= 0; n--)
		{
			data[l][n] = 0.0;
			if(l == 0 || n == 0) data[l][n] = param->averTemp;
			if(n == param->nodes-1) data[l][n] = param->initTemp;
		}
	}
}

void calculating(double **data, initParam *param)
{
	printf("\n\ncalculating..\n\n");
	double multiplier;
	multiplier = (K * param->timeStep)/(C * param->lineStep * param->lineStep);
	for(int l = 1; l <= param->layers; l++)
		for(int n = 1; n < param->nodes-1; n++)
			data[l][n] = data[l-1][n] + multiplier * (data[l-1][n+1] - 2 * data[l-1][n] + data[l-1][n-1]);
}

void printMtx(double **data, initParam* param)
{
	for(int i = param->nodes-1; i >= 0; i--)
		printf("n = %-3d\t", i);
	printf("\n-------------------------------------------------------------------------\n");
	for(int l = param->layers; l >= 0 ; l--)
	{
		for(int n = param->nodes-1; n >= 0; n--)
			printf("%5.3f\t", data[l][n]);
		printf("| t = %2.1f\n", l * param->timeStep);
	}
}

void printParam(initParam param)
{
	printf("targetTime = \t%.2f\n", param.targetTime);
	printf("length = \t%.2f\n", param.length);
	printf("initTemp = \t%.2f\n", param.initTemp);
	printf("averTemp = \t%.2f\n", param.averTemp);
	printf("lineStep = \t%.2f\n", param.lineStep);
	printf("timeStep = \t%.2f\n", param.timeStep);
	printf("nodes = \t%d\n", param.nodes);
	printf("layers = \t%d\n\n", param.layers);
}

void freeMem(double** data, initParam *param)
{
	for(int l = 0; l < param->layers; l++)
		free(data[l]);
	free(data);
}