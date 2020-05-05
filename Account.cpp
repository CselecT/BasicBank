#include "Account.h"

void swap(Transaction *xp, Transaction *yp)  
{  
    Transaction temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
void bubbleSort(Transaction arr[], int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)        
    for (j = 0; j < n-i-1; j++)  
        if (arr[j] > arr[j+1])  
            swap(&arr[j], &arr[j+1]);  
}  

Account::Account(){
  _id=-1;
  _activity=nullptr;
  _monthly_activity_frequency=nullptr;
}

Account::Account(int id, Transaction** const activity, int* monthly_activity_frequency){
  _id=id;
  _activity=new Transaction*[12];
  _monthly_activity_frequency= new int[12];
  for(int i=0;i<12;i++){
    int len=monthly_activity_frequency[i];
    if(len){
    _activity[i]=new Transaction[len];
    for(int k=0;k<len;k++){
      _activity[i][k]=activity[i][k];
    }
    bubbleSort(_activity[i], len);
    }
    else{
      _activity[i]=nullptr;
    }
    _monthly_activity_frequency[i]=len;
  }
}

Account::~Account(){
  if(_activity){
  for(int i=0;i<12;i++) delete [] _activity[i];
  delete [] _activity;
  }
  delete [] _monthly_activity_frequency;
}

Account::Account(const Account& rhs){
  _id=rhs._id;
  if(rhs._activity==nullptr){
    _activity=nullptr;
    _monthly_activity_frequency=nullptr;
  }
  else{
  _activity=new Transaction*[12];
  _monthly_activity_frequency= new int[12];
  for(int i=0;i<12;i++){
    int len=rhs._monthly_activity_frequency[i];
    if(len){
    _activity[i]=new Transaction[len];
    for(int k=0;k<len;k++){
      _activity[i][k]=rhs._activity[i][k];
    }
    bubbleSort(_activity[i], len);
    }
    else{
      _activity[i]=nullptr;
    }
    _monthly_activity_frequency[i]=len;
  }
  }
}

Account::Account(const Account& rhs, time_t start_date, time_t end_date){
  _id=rhs._id;
  _activity=new Transaction*[12];
  _monthly_activity_frequency= new int[12];
  int check=0;
  for(int i=0;i<12;i++){
    int wanted_len=0;
    int len=rhs._monthly_activity_frequency[i];
    for(int j=0;  j<len ;j++){
      if(rhs._activity[i][j]<end_date && rhs._activity[i][j]>start_date)
      wanted_len++;
      check++;
    }
    if(wanted_len){
    _activity[i]=new Transaction[wanted_len];
    for(int k=0;k<wanted_len;k++){
      for(int j=k;j<len;j++){
        if(rhs._activity[i][j]<end_date && rhs._activity[i][j]>start_date){
          _activity[i][k]=rhs._activity[i][j];
          break;
        }
      }
    }
    bubbleSort(_activity[i], wanted_len);
    }
    else{
      _activity[i]=nullptr;
    }
    _monthly_activity_frequency[i]=wanted_len;
  }
  if(check==0){
    delete[] _activity;
    _activity=nullptr;
  }
}

Account& Account::operator=(const Account& rhs){
  if(&rhs==this) return *this;
  else{
    _id=rhs._id;
    if(_activity){
      for(int i=0;i<12;i++) delete [] _activity[i];
      delete [] _activity;
    }
    if(_monthly_activity_frequency) delete [] _monthly_activity_frequency;
    _activity=new Transaction*[12];
    _monthly_activity_frequency= new int[12];
    for(int i=0;i<12;i++){
      int len=rhs._monthly_activity_frequency[i];
      if(len){
      _activity[i]=new Transaction[len];
      for(int k=0;k<len;k++){
        _activity[i][k]=rhs._activity[i][k];
      }
      }
      else{
      _activity[i]=nullptr;
    }
    _monthly_activity_frequency[i]=len;
    }
  return *this;
  }
}

bool Account::operator==(const Account& rhs) const{
  if(_id==rhs._id) return true;
  else return false;
}

bool Account::operator==(int id) const{
  if(_id==id) return true;
  else return false;
}

Account& Account::operator+=(const Account &rhs){
  int len1,len2,total;
  if(_activity==nullptr){
    int help=_id;
    *this=rhs;
    _id=help;
  }
  else{
  for(int i=0;i<12;i++){
    len1=_monthly_activity_frequency[i];
    len2=rhs._monthly_activity_frequency[i];
    total=len1+len2;
    Transaction* p = new Transaction[total];
    for(int j=0;j<len1;j++) p[j]=_activity[i][j];
    for(int j=0;j<len2;j++) p[j+len1]=rhs._activity[i][j];
    if(_activity[i]) delete [] _activity[i];
    _activity[i] = new Transaction[total];
    for(int j=0;j<total;j++) _activity[i][j]=p[j];
    delete [] p;
    bubbleSort(_activity[i], total);
    _monthly_activity_frequency[i]=total;
  }
  }
  return *this;
}

double Account::balance(){
  double total=0;
  for(int i=0;i<12;i++){
    for(int j=0;j<_monthly_activity_frequency[i];j++) total=_activity[i][j] + total;
  }
  return total;
}
double Account::balance(time_t end_date){
   struct tm * end;
   end=localtime(&(end_date));
   int mon = end->tm_mon;
   int total=0;
   for(int i=0;i<=mon;i++)
     for(int j=0;j<_monthly_activity_frequency[i];j++){
      if(_activity[i][j]<end_date) total=_activity[i][j] + total;
      else break;
    }
  return total;
 }

double Account::balance(time_t start_date, time_t end_date){
  struct tm* helper;
  int end,start;
  int total=0;
  helper=localtime(&(end_date));
  end=helper->tm_mon;
  helper=localtime(&(start_date));
  start=helper->tm_mon;
  for(int i=start;i<=end;i++){
    for(int j=0;j<_monthly_activity_frequency[i];j++){
      if(_activity[i][j]>start_date && _activity[i][j]<end_date) total=_activity[i][j] + total;
    }
  }
  return total;
}

std::ostream& operator<<(std::ostream& os, const Account& account){
  struct tm* date;
  if(account._activity==nullptr || account._monthly_activity_frequency==nullptr) os<<-1;
  else{
    for(int i=0;i<12;i++){
      bubbleSort(account._activity[i], account._monthly_activity_frequency[i]);
      for(int j=0;j<account._monthly_activity_frequency[i];j++){
        os<<account._activity[i][j];
      }
    }
  }
  return os;
}
Account::Account(Account&& rhs){
  _activity=rhs._activity;
  _id=rhs._id;
  _monthly_activity_frequency=rhs._monthly_activity_frequency;
  rhs._activity=nullptr;
  rhs._monthly_activity_frequency=nullptr;
}

Account& Account::operator=(Account &&rhs){
  if(&rhs==this) {
    rhs._activity=nullptr;
    rhs._monthly_activity_frequency=nullptr;
    return *this;}
    else{
    for(int i=0;i<12;i++) delete [] _activity[i];
    delete [] _activity;
    delete [] _monthly_activity_frequency;
    _activity=rhs._activity;
    _id=rhs._id;
    _monthly_activity_frequency=rhs._monthly_activity_frequency;
    rhs._activity=nullptr;
    rhs._monthly_activity_frequency=nullptr;
    return *this; 
  }
}
