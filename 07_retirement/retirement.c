#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double update_balance(retire_info ri, double balance){
  balance *= 1 + ri.rate_of_return;
  balance += ri.contribution;
  return balance;
}

void get_age_from_months(int *age, int months){
  age[0] = months / 12;
  age[1] = months % 12;
}

void print_balance(int *age, double balance){
  printf("Age %3d month %2d you have $%.2lf\n",age[0], age[1], balance);
}

void retirement(int startAge, // In months
		double initial, // Initial savings in dollars
		retire_info working, // Info about working
		retire_info retired // Info about being retired
		){
  double balance = initial;
  int age[2];
  for (int m_work = 0; m_work < working.months; m_work++){
    get_age_from_months(age, startAge);
    print_balance(age, balance);
    balance = update_balance(working, balance);
    startAge++;
  }

  for (int m_ret = 0; m_ret < retired.months; m_ret++){
    get_age_from_months(age, startAge);
    print_balance(age, balance);
    balance = update_balance(retired, balance);
    startAge++;
  }

}

int main(void){
  retire_info working = {489, 1000.0, 0.045/12};
  retire_info retired = {384, -4000.0, 0.01/12};

  retirement(327, 21345.0, working, retired);
  return EXIT_SUCCESS;
}
