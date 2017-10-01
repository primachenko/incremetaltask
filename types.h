typedef struct arrParam
{
	int 	layers,
			nodes;
	double 	timeStep,
			lineStep,
			length,
			targetTime,
			initTemp,
			averTemp,
			K,
			C;
} initParam;
/*macro*/
#define K 			200.0
#define C 			2400000.0
#define LINE_STEPS 	10
/*prototype*/
int 	initParamStruct(initParam*, char const **, int);
void 	printParam(initParam);
void 	initMtx(double**, initParam*);
void 	printMtx(double**, initParam*);
void	calculating(double**, initParam*);
/*errcode*/
#define ERRNO      0
#define ERRFEWARG -1
#define ERRBADARG -2
#define ERRMEMALL -3
#define ERRINIT   -4