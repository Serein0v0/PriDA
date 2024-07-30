#include "emp-sh2pc/emp-sh2pc.h"
using namespace emp;
using namespace std;

// 计算 CAl 和 CAz
void computeCAlAndCAz(Integer s, Integer r, Integer kappa, double sigma, Bit &condition, Integer &CAl, Integer &CAz) {
    // 计算 kappa - r
    Integer kappa_minus_r = kappa - r;

    // 条件判断 s <= kappa - r
    condition = s <= kappa_minus_r;

    // 计算 CAl 和 CAz
    Integer exp_s = exp(-s / (sigma * sigma));
    Integer exp_r = exp(-r / (sigma * sigma));

    CAl = condition ? exp_s : 0;
    CAz = condition ? exp_r : 0;
}

void test(int party, int s_value, int r_value, int kappa_value, double sigma_value) {
    Integer s(32, s_value, ALICE);
    Integer r(32, r_value, BOB);
    Integer kappa(32, kappa_value, BOB);

    // Condition bit
    Bit condition;

    // Compute CAl and CAz
    Integer CAl(32, 0, party);
    Integer CAz(32, 0, party);
    computeCAlAndCAz(s, r, kappa, sigma_value, condition, CAl, CAz);

    // Reveal results
    cout << "Condition (s <= kappa - r): " << condition.reveal<bool>() << endl;
    cout << "CAl: " << CAl.reveal<double>() << endl;
    cout << "CAz: " << CAz.reveal<double>() << endl;
}

int main(int argc, char** argv) {
	int port, party;
	parse_party_and_port(argv, &party, &port);
	//test
	int s_value = 5;
    int r_value = 3;
    int kappa_value = 10;
    double sigma_value = 2.0;
	if(argc > 3){
        // Update values if provided
        s_value = atoi(argv[3]);
        r_value = atoi(argv[4]);
        kappa_value = atoi(argv[5]);
        sigma_value = atof(argv[6]);
	}
	NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);

	setup_semi_honest(io, party);
	auto start = clock_start();
	test(party, s_value, r_value, kappa_value, sigma_value);
//	test_sort(party);
	long long t = time_from(start);
	std::cout << "Tests passed.\t";
	cout<< t<<endl;
	cout << CircuitExecution::circ_exec->num_and()<<endl;
	finalize_semi_honest();
	delete io;
}
