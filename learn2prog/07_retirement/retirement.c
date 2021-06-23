#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months; //the number of months it is applicable to
  double contribution; //how many dollars are contributed
  double rate_of_return; 
};

typedef struct _retire_info retire_info;

double calculation (int startAge, double balance, retire_info info) {
  for(int i = 0; i < info.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", (startAge + i) / 12, (startAge + i) % 12, balance);
    balance = balance + balance * info.rate_of_return + info.contribution;
  }
  return balance;
}

void retirement (int startAge, //in months
		 double initial, //initial savings in dollars
		 retire_info working, //info about working
		 retire_info retired) { //info about being retired

  double balance = initial;
  double balance_after_working = calculation(startAge, balance, working);
  calculation(startAge + working.months, balance_after_working, retired);
}

int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  int startAge = 327;
  double initial = 21345;

  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}
