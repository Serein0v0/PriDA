#include "emp-sh2pc/emp-sh2pc.h"
using namespace emp;
using namespace std;

Integer calculateZ(Integer ffs, Integer m, Integer deltaT, Integer r, int party) {
    Integer product = ffs * m * deltaT;
    Integer square = product * product;
    return square - r;
}

void test_compare(int party, int ffs_value, int m_value, int deltaT_value, int r_value, int s_value) {
    Integer ffs(32, ffs_value, ALICE);
    Integer m(32, m_value, ALICE);
    Integer deltaT(32, deltaT_value, ALICE);
    Integer r(32, r_value, ALICE);

    Integer z = calculateZ(ffs, m, deltaT, r, ALICE);

    Integer s(32, s_value, BOB);

    Bit res = z > s;

    cout << "Is ALICE's z greater than BOB's s?\t" << res.reveal<bool>() << endl;
}

void test_sort(int party) {
	int size = 100;
	Integer *A = new Integer[size];
	Integer *B = new Integer[size];
	Integer *res = new Integer[size];

	for(int i = 0; i < size; ++i)
		A[i] = Integer(32, rand()%102400, ALICE);


	for(int i = 0; i < size; ++i)
		B[i] = Integer(32, rand()%102400, BOB);

	for(int i = 0; i < size; ++i)
		res[i] = A[i] ^ B[i];
	

	sort(res, size);
	for(int i = 0; i < 100; ++i)
		cout << res[i].reveal<int32_t>()<<endl;

	delete[] A;
	delete[] B;
	delete[] res;
}

int main(int argc, char** argv) {
	int port, party;
	parse_party_and_port(argv, &party, &port);
	// Default values for ffs, m, deltaT, r, and s
    int ffs_value = 60;
    int m_value = 1;
    int deltaT_value = 1;
    int r_value = 180;
    int s_value = 80;
	if(argc > 3){
        // Update values if provided
        ffs_value = atoi(argv[3]);
        m_value = atoi(argv[4]);
        deltaT_value = atoi(argv[5]);
        r_value = atoi(argv[6]);
		s_value = atoi(argv[7]);
	}
	NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);

	setup_semi_honest(io, party);
	auto start = clock_start();
	test_compare(party, ffs_value, m_value, deltaT_value, r_value, s_value);
//	test_sort(party);
	long long t = time_from(start);
	std::cout << "Tests passed.\t";
	cout<< t<<endl;
	cout << CircuitExecution::circ_exec->num_and()<<endl;
	finalize_semi_honest();
	delete io;
}
