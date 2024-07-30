#include <iostream>
using namespace std;
#include "/usr/local/include/pbc/pbc.h"  
//#include<time.h> 
#include <chrono>
int main() {
//clock_t startTime,endTime;

  pairing_t pairing;  

  char param[1024];
  size_t count = fread(param, 1, 1024, stdin);
  printf("param = %s\n", param);

  if (!count) pbc_die("input error");
  pairing_init_set_buf(pairing, param, count);

  element_t u[5];
  element_t M[5][3]; 
  element_t g, h; 
  element_t delta[3];
  element_t C0[3];
  element_t b1[10];
  element_t b2[10];
  element_t b3[10];
  element_t b6[10];
  element_t b8[10];
  element_t b10[10];  
  element_t pi[5];
  element_t lam[5];
  element_t C[5][10];
  element_t temp;
  element_t temp1;
  element_t temp2;
  element_t temp3;
  element_t temp4;



  element_init_G1(g, pairing);
  element_init_G2(h, pairing);//用pairing 初始化g

  for (int i=0; i<10; i++){
   element_init_Zr(b1[i], pairing);
   element_init_Zr(b2[i], pairing);
   element_init_Zr(b3[i], pairing);
   element_init_Zr(b6[i], pairing);
   element_init_Zr(b8[i], pairing);
   element_init_Zr(b10[i], pairing);               
  }
  for (int i=0; i<5; i++){  
   element_init_Zr(u[i], pairing);
   element_init_Zr(pi[i], pairing);  
   element_init_Zr(lam[i], pairing);
  }
  for (int i=0; i<3; i++){
    element_init_Zr(delta[i],pairing);
    element_init_G1(C0[i],pairing);
          for (int j=0; j<5; j++){  
            element_init_Zr(M[i][j], pairing);
  }}

/*
  for (int i=0; i<5; i++){  
      for (int j=0; j<3; j++){  
       element_init_Zr(M[i][j], pairing);
      }
  }*/
  for (int i=0; i<5; i++){  
    for (int j=0; j<10; j++){  
       element_init_G1(C[i][j], pairing);
      }
  }
  element_init_Zr(temp, pairing);
  element_init_Zr(temp1, pairing);
  element_init_Zr(temp2, pairing);
  element_init_Zr(temp3, pairing);
  element_init_Zr(temp4, pairing);

  //element_init_GT(temp1, pairing);
  //element_init_GT(temp2, pairing);


  for (int i=0; i<10; i++){
  element_random(b1[i]);
  element_random(b2[i]); 
  element_random(b3[i]); 
  element_random(b6[i]);
  element_random(b8[i]);
  element_random(b10[i]);
  }
  for (int i=0; i<5; i++){
  element_random(u[i]);
  element_random(lam[i]); 
  }
  for (int i=0; i<3; i++){  
      for (int j=0; j<5; j++){  
       element_random(M[i][j]);
      }
  }
  element_random(g);
//以上为初始化
 element_t Usr[20];
 for(int a=1;a<20;a++){
    element_init_G1(Usr[a], pairing);
 }




 // Start measuring time

 //for(int a=1; a<100;a++){
//enc C0s
 auto begin = std::chrono::high_resolution_clock::now();
for (int j=0; j<3; j++){
  element_random(delta[j]);   
  element_pow_zn( C0[j], g, delta[j]) ; 
}

//enc Ci
for (int i=0; i<5; i++){
  element_random(pi[i]); 
  //startTime = clock();
  for (int j=0; j<10; j++){
   element_mul(temp1, pi[i],b1[j]) ;
   element_mul(temp2, lam[i],b2[j]) ;
   element_mul(temp2, pi[i], temp2) ;
   element_add(temp, temp1,temp2);
   element_mul(temp3, u[i],b3[j]);
   element_add(temp, temp,temp3);
   element_mul(temp1, M[0][i], delta[0]);
   element_mul(temp1,temp1, b6[j]);
   element_add(temp, temp, temp1);
   element_mul(temp2, M[1][i], delta[1]);
   element_mul(temp2, temp2, b8[j]);
   element_add(temp, temp, temp2);   
   element_mul(temp3, M[2][i], delta[2]);
   element_mul(temp3, temp3, b10[j]);
   element_add(temp, temp, temp3);   
   element_pow_zn( C[i][j], g, temp) ;
  }
 // endTime = clock();
}
//}


auto end = std::chrono::high_resolution_clock::now();
auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
cout<<elapsed.count()<<endl;
printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-3);

//cout << "Totle Time : " <<(double)(endTime - startTime) << "ms" << endl;
cout<<C[0][0]<<endl;
cout<<temp2<<endl;
cout<<temp3<<endl;

  if (!element_cmp(temp2,temp3)) { 
    printf(" verifies\n");
  } else {
    printf(" not verify\n");
  }




return 0;
}
