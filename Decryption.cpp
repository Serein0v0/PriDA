#include <iostream>
using namespace std;
#include "/usr/local/include/pbc/pbc.h"  //必须包含头文件pbc.h#include <pbc/pbc.h>
//#include<time.h> 
#include<math.h>
#include <chrono>
int main() {
//clock_t startTime,endTime;

  pairing_t pairing;  
  /*
  pairing_t定义： pairings where elements belong本例子用a.param去初始化pairing; a pairing is a map 例如:e:G1×G2->Gt
  a.param是pbc库中标准的参数集，其提供对称的pairing 
  */
  char param[1024];
  size_t count = fread(param, 1, 1024, stdin);//读大小为1的个数最大为1024到param，返回真实读入的个数
  printf("param = %s\n", param);
//  printf("count = %lu\n", count);//size_t是标准C库中定义的，应为unsigned int，在64位系统中为 long unsigned int
  if (!count) pbc_die("input error");
  pairing_init_set_buf(pairing, param, count);
  //pairing 初始化结束

  //定义变量-初始化-用于保存系统参数、公私秘钥以及其他变量
  element_t u[5];
  element_t M[5][3]; //收到的密钥中的M
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

  //定义变量-初始化-用于保存系统参数、公私秘钥以及其他变量
  element_t v[5];
  element_t Q[5][3]; //收到的密钥中的M
  element_t Ddelta[3];
  element_t D0[3];
  element_t bs1[10];
  element_t bs2[10];
  element_t bs3[10];
  element_t bs6[10];
  element_t bs8[10];
  element_t bs10[10];  
  element_t Dpi[5];
  element_t D[5][10];
  
  element_t  Res[5];
  element_t  Restemp[5];
  element_t Fin;
  element_t Restemp0[3];
  element_t Fin0;
  element_t Findiv;
  element_t gt;
  element_t prod;
  


  element_init_G1(g, pairing);
  element_init_G2(h, pairing);//用pairing 初始化g
  //初始化B
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
  for (int i=0; i<5; i++){  
    for (int j=0; j<10; j++){  
       element_init_G1(C[i][j], pairing);
      }
  }

  //初始化Bs
  for (int i=0; i<10; i++){
  element_init_GT(Restemp[i], pairing);
   element_init_Zr(bs1[i], pairing);
   element_init_Zr(bs2[i], pairing);
   element_init_Zr(bs3[i], pairing);
   element_init_Zr(bs6[i], pairing);
   element_init_Zr(bs8[i], pairing);
   element_init_Zr(bs10[i], pairing);               
  }
  for (int i=0; i<5; i++){  
   element_init_Zr(v[i], pairing);
   element_init_Zr(Dpi[i], pairing);  
   element_init_Zr(lam[i], pairing);
   element_init_GT(Res[i], pairing);
  }
  for (int i=0; i<3; i++){
    element_init_Zr(Ddelta[i],pairing);
    element_init_G2(D0[i],pairing);
    element_init_GT(Restemp0[i],pairing);
          for (int j=0; j<5; j++){  
            element_init_Zr(Q[i][j], pairing);
  }}
  for (int i=0; i<5; i++){  
    for (int j=0; j<10; j++){  
       element_init_G2(D[i][j], pairing);
      }
  }
  element_init_GT(Fin,pairing);
  element_set1(Fin);
  element_init_GT(Fin0,pairing);
  element_set1(Fin0);
  element_init_GT(Findiv,pairing);
  element_init_GT(gt,pairing);

  element_init_Zr(temp, pairing);
  element_init_Zr(temp1, pairing);
  element_init_Zr(temp2, pairing);
  element_init_Zr(temp3, pairing);
  element_init_Zr(temp4, pairing);
  element_init_Zr(prod,pairing);

  //element_init_GT(temp1, pairing);
  //element_init_GT(temp2, pairing);

//随机生成矩阵B
  for (int i=0; i<10; i++){
  element_set0(b1[i]);
  element_set0(b2[i]); 
  element_set0(b3[i]); 
  element_set0(b6[i]);
  element_set0(b8[i]);
  element_set0(b10[i]);
  }
  element_set1(b1[0]);
  element_set1(b2[1]);
  element_set1(b3[2]);
  element_set1(b6[5]); 
  element_set1(b8[7]);
  element_set1(b10[9]);

  for (int i=0; i<5; i++){
  element_set1(u[i]);
  element_random(lam[i]); 
  }
  for (int i=0; i<3; i++){  
      for (int j=0; j<5; j++){  
       element_random(M[i][j]);
      }
  }
  element_random(g);
//以上为初始化
//随机生成矩阵B
  for (int i=0; i<10; i++){
  element_set0(bs1[i]);
  element_set0(bs2[i]); 
  element_set0(bs3[i]); 
  element_set0(bs6[i]);
  element_set0(bs8[i]);
  element_set0(bs10[i]);
  }
  element_set1(bs1[0]);
  element_set1(bs2[1]);
  element_set1(bs3[2]);
  element_set1(bs6[5]); 
  element_set1(bs8[7]);
  element_set1(bs10[9]);

  for (int i=0; i<5; i++){
  element_set1(v[i]);
  }
  for (int i=0; i<3; i++){  
      for (int j=0; j<5; j++){  
       element_random(Q[i][j]);
      }
  }
  element_random(h);
  //////////////////////////////////////////////////////////

//enc C0s
// auto begin = std::chrono::high_resolution_clock::now();
for (int j=0; j<3; j++){
  element_random(delta[j]);   //随机采样
  element_pow_zn( C0[j], g, delta[j]) ; 
}

//enc Ci
for (int i=0; i<5; i++){
  element_random(pi[i]); 
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
}
//enc D0s

for (int j=0; j<3; j++){
  element_random(Ddelta[j]);   //随机采样
  element_pow_zn( D0[j], h, Ddelta[j]) ; 
}

//enc Di
for (int i=0; i<5; i++){
  element_random(Dpi[i]); 
  for (int j=0; j<10; j++){
   element_mul(temp1, Dpi[i],bs1[j]) ;
   element_mul(temp2, lam[i],bs2[j]) ;
   element_mul(temp2, Dpi[i], temp2) ;
   element_add(temp, temp1,temp2);
   element_mul(temp3, v[i],bs3[j]);
   element_add(temp, temp,temp3);
   element_mul(temp1, Q[0][i], Ddelta[0]);
   element_mul(temp1,temp1, bs6[j]);
   element_add(temp, temp, temp1);
   element_mul(temp2, Q[1][i], Ddelta[1]);
   element_mul(temp2, temp2, bs8[j]);
   element_add(temp, temp, temp2);   
   element_mul(temp3, Q[2][i], Ddelta[2]);
   element_mul(temp3, temp3, bs10[j]);
   element_add(temp, temp, temp3);   
   element_pow_zn( D[i][j], h, temp) ;
  }
}

//DEC
 auto begin = std::chrono::high_resolution_clock::now();
for (int i=0; i<5; i++){
  pairing_apply(Res[i], C[i][0],D[i][0],pairing);
   for (int j=1; j<10; j++){ 
      pairing_apply(Restemp[j], C[i][j],D[i][j],pairing);  
      element_mul(Res[i], Res[i], Restemp[j]);  //Ci x Di
   }
  element_mul(Fin, Res[i], Fin); //连乘
}
for(int i = 0; i<3; i++){
  pairing_apply(Restemp0[i],C0[i], D0[i], pairing);
  element_mul(Fin0, Restemp0[i], Fin0);
}
element_div(Findiv, Fin,Fin0);
pairing_apply(gt,g,h,pairing);
//element_dlog_brute_force(prod,gt,Findiv);
//element_dlog_pollard_rho(prod,gt,Findiv);  


auto end = std::chrono::high_resolution_clock::now();


auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
cout<<elapsed.count()<<endl;
printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-3);

//cout << "Totle Time : " <<(double)(endTime - startTime) << "ms" << endl;
cout<<C[0][0]<<endl;
cout<<temp2<<endl;
cout<<Res[0]<<endl;

  if (!element_cmp(Fin,Res[0])) { 
    printf(" verifies\n");
  } else {
    printf(" not verify\n");
  }




return 0;
}