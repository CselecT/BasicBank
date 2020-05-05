#include "Transaction.h"

Transaction::Transaction(){
  _amount=-1;
  _date=-1;
}

Transaction::Transaction(double amount, time_t date){
  _amount=amount;
  _date=date;
}

Transaction::Transaction(const Transaction& rhs){
  _amount=rhs._amount;
  _date=rhs._date;
}

bool Transaction::operator<(const Transaction &rhs) const{
  double diff;
  diff=difftime(_date, rhs._date);
  if(diff<0) return true;
  else return false;

}

bool Transaction::operator>(const Transaction &rhs) const{
  double diff;
  diff=difftime(_date, rhs._date);
  if(diff>0) return true;
  else return false;
}

bool Transaction::operator<(const time_t date) const{
  double diff;
  diff=difftime(_date, date);
  if(diff<0) return true;
  else return false;

}

bool Transaction::operator>(const time_t date) const{
  double diff;
  diff=difftime(_date, date);
  if(diff>0) return true;
  else return false;
}

double Transaction::operator+(const Transaction &rhs){
  double result;
  result = _amount + rhs._amount;
  return result;
}

double Transaction::operator+(const double add){
  double result;
  result = _amount + add;
  return result;
}

Transaction& Transaction::operator=(const Transaction &rhs){
  _amount=rhs._amount;
  _date=rhs._date;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Transaction& transaction){
  struct tm * mydate;
  mydate=localtime(&(transaction._date));
  os << transaction._amount << "\t-\t" << mydate->tm_hour <<":"<< mydate->tm_min << ":" << mydate->tm_sec << "-" << mydate->tm_mday << "/" << mydate->tm_mon + 1 << "/" << mydate->tm_year + 1900<<"\n";
  return os;
}
