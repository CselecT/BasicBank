#include "Bank.h"

Bank::Bank(){
  _bank_name="not_defined";
  _user_count=0;
  _users=nullptr;
}
Bank::Bank(std::string bank_name, Account* const users, int user_count){
  _bank_name=bank_name;
  _user_count=user_count;
  _users=new Account[user_count];
  for(int i=0;i<user_count;i++){
    _users[i]=users[i];
  }
}
Bank::~Bank(){
  delete [] _users;
}

Bank::Bank(const Bank& rhs){
  _bank_name=rhs._bank_name;
  _user_count=rhs._user_count;
  _users=new Account[_user_count];
  for(int i=0;i<_user_count;i++){
    _users[i]=rhs._users[i];
  }
}


Bank& Bank::operator+=(const Bank &rhs){

  for(int i=0;i<rhs._user_count;i++){
    int flag=0;
    for(int j=0; j<_user_count; j++) if(rhs._users[i]==_users[j]) flag=1;
    if(flag){
      Account * p = _users;
      while(!((*p)==rhs._users[i])) p++;
      *p += rhs._users[i];
    }
    else{
      Account * temp = new Account[_user_count];
      for(int i=0;i<_user_count;i++) temp[i]=_users[i];
      delete [] _users;
      _user_count++;
      _users=new Account[_user_count];
      for(int i=0;i<_user_count-1;i++) _users[i]=temp[i];
      _users[_user_count-1]=rhs._users[i];
      delete [] temp;
    }
  }
  return *this;
}

Bank& Bank::operator+=(const Account &new_acc){
    int flag=0;
    for(int j=0; j<_user_count; j++) if(new_acc==_users[j]) flag=1;
    if(flag){
      Account * p = _users;
      while(!((*p)==new_acc)) p++;
      *p += new_acc;
    }
    else{
      Account * temp = new Account[_user_count];
      for(int i=0;i<_user_count;i++) temp[i]=_users[i];
      delete [] _users;
      _user_count++;
      _users=new Account[_user_count];
      for(int i=0;i<_user_count-1;i++) _users[i]=temp[i];
      _users[_user_count-1]=new_acc;
      delete [] temp;
    }
    return *this;
}

Account& Bank::operator[](int account_id){
  for(int i=0;i<_user_count;i++){
    if(_users[i]==account_id) return _users[i];
  }
  return _users[0];
}

std::ostream& operator<<(std::ostream& os, const Bank& bank){
  int elig=0;
  int balance=0;
  struct tm time0;
  time0.tm_hour=0;
  time0.tm_min=0;
  time0.tm_sec=0;
  time0.tm_mon=0;
  time0.tm_mday=1;
  time0.tm_year=119;

  for(int i=0;i<bank._user_count;i++){
    int flag=0;
    for(int j=0;j<12;j++){
      struct tm start, end;
      start=time0;
      end=time0;
      start.tm_mon += j;
      if(j==11){
        end.tm_mon=0;
        end.tm_year=120;
      }
      else end.tm_mon += j+1;

      if(bank._users[i].balance(mktime(&start),mktime(&end))<0) flag++;
      else if(flag==1) flag --;
      if(flag==2) break;
    }
    if(flag!=2) elig++;
    balance += bank._users[i].balance();
  }
  os<<bank._bank_name<<"\t"<<elig<<"\t"<<balance<<"\n";
  return os;
}
