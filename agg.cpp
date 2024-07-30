
#include <iostream>
#include <string>
#include "secondary.h"
#include "connect.h"
#include "AESObject.h"
#include "NeuralNetConfig.h"
#include "NeuralNetwork.h"
#include "Functionalities.h"


using namespace std;
extern int partyNum;
int NUM_OF_PARTIES;	


AESObject* aes_common;
AESObject* aes_indep;
AESObject* aes_a_1;
AESObject* aes_a_2;
AESObject* aes_b_1;
AESObject* aes_b_2;
AESObject* aes_c_1;
ParallelAESObject* aes_parallel;



int main(int argc, char** argv)
{

/****************************** PREPROCESSING ******************************/ 
	parseInputs(argc, argv);
	string whichNetwork = "No Network";
	NeuralNetConfig* config = new NeuralNetConfig(NUM_ITERATIONS);


	cout << "debug" << endl;


/****************************** AES SETUP and SYNC ******************************/ 
	aes_indep = new AESObject(argv[4]);
	aes_common = new AESObject(argv[5]);
	cout << "debug" << endl;
	aes_a_1 = new AESObject("files/keyD");
	aes_a_2 = new AESObject("files/keyD");
	aes_b_1 = new AESObject("files/keyD");
	aes_b_2 = new AESObject("files/keyD");
	aes_c_1 = new AESObject("files/keyD");
	cout << "debug" << endl;
	aes_parallel = new ParallelAESObject(argv[5]);
	cout << "debug" << endl;

	if (!STANDALONE)
	{
		initializeCommunication(argv[3], partyNum);
		synchronize(2000000);	
	}
	cout << "debug" << endl;

	if (PARALLEL)
		aes_parallel->precompute();
	cout << "debug" << endl;	


/****************************** RUN NETWORK/BENCHMARKS ******************************/ 
	int NUMDS = 20;
	start_m();

	whichNetwork = "Mat-Mul";
	//testMatMul(NUMDS, NUMDS, NUMDS, 1);
	testMatMul(NUMDS, NUMDS, 34272, 1);
	testRelu(NUMDS, 34272, 1);
	testMatMul(NUMDS, NUMDS, 34272, 1);
	testRelu(NUMDS, 34272, 1);


	
	end_m(whichNetwork);

	cout << "----------------------------------" << endl;  	
	cout << NUM_OF_PARTIES << "PC code, P" << partyNum << endl;
	cout << NUM_ITERATIONS << " iterations, " << whichNetwork << ", batch size " << MINI_BATCH_SIZE << endl;
	cout << "----------------------------------" << endl << endl;  


/****************************** CLEAN-UP ******************************/ 
	delete aes_common;
	delete aes_indep;
	delete aes_a_1;
	delete aes_a_2;
	delete aes_b_1;
	delete aes_b_2;
	delete aes_c_1;
	delete aes_parallel;
	delete config;
	if (partyNum != PARTY_S)
		deleteObjects();

	return 0;
}

