#ifndef HUGEINT_H
#define HUGEINT_H

#include <iostream>
#include <math.h>
using namespace std;



class HugeInt{

  friend ostream& operator<< (ostream&,const HugeInt &);
  friend istream& operator>> (istream&, HugeInt &);

 private:
  static const int ASCII = 48;           // number for char '0'
  static const int num_size = 2569;      // max digits needed to divide 1000!
  int NUM[num_size];
  static const int prec = 10;            // precision for decimals
  
 public:
  HugeInt();
  HugeInt(int);
  int     number_length();
  void    display() const;
  void    display2() const;
  void    input();
  HugeInt add(HugeInt);
  HugeInt minus(HugeInt);
  HugeInt multiply(HugeInt);
  HugeInt divide(HugeInt);
  HugeInt divide2(HugeInt);
  bool    isGreater(HugeInt);
  bool    isEqual(HugeInt);

  HugeInt operator+  (const HugeInt &);
  HugeInt operator-  (const HugeInt &);
  HugeInt operator*  (const HugeInt &);
  bool    operator>  (const HugeInt &);
  bool    operator== (const HugeInt &);
  bool    operator!= (const HugeInt &);
  bool    operator>= (const HugeInt &);
  bool    operator<  (const HugeInt &);
  bool    operator<= (const HugeInt &);

};


//default to 0
HugeInt::HugeInt(){

  for(int i = 0; i < num_size; i++)
    NUM[i] = 0;
}

// construct to inputed INT
HugeInt::HugeInt(int num){

  int length = 0;

  for(int i = 0; i < 10; i++)
    {
      if( num < pow(10,i) )
	{
	  length = i;
	  break;
	}
    }

  for(int i = 0; i < num_size; i++)
    NUM[i] = 0;
    
  for(int i = num_size - length, k = 1; i < num_size; i++, k++ )
    {
      int temp = num / ( pow(10, length - k) );
      NUM[i] = temp;

      num = num - temp * ( pow(10, length - k) );
    }

}

// input HugeInt number
void HugeInt::input(){

  //digits placed into array as one would write a number
  //ones digit to right of tens digit...ones has highest addresss in array

  string num;
  int digit;
  cin>> num;
 

  /*
    i starts at the ones digit of the array by num_size -1
    i min value of 0 for the array
    k to track which digit of the string we are at
    k max value of string length - 1
  */
  for(int i = num_size - 1, k = 0; i >= 0 && k < num.length(); i--, k++)
    {
      /* 
	 convert the string called num to int type one digit at a time
	 begin at the ones digit by length of the string -1 -0
	 return the ASCII chart number of that digit
	 subtract ASCII=48 from returned number to get desired digit
	 set array digit
      */
      NUM[i] = static_cast<int>(num[num.length() -1 -k]) - ASCII; 
    }

}

int HugeInt::number_length(){
  //length of number after first non-zero 

  int k = 0;
  for(int i = 0; i < num_size; i++)
    {
      k = i;
      if(NUM[i] != 0)
	break;
    }

  int size = num_size - k;

  return size;

}


void HugeInt::display() const{
  
  int k = 0;
  for(int i = 0; i < num_size; i++)
    {
      k = i;
      if(NUM[i] != 0)
	break;
    }

  for(int i = k; i < num_size - 1; i++)
   cout<< NUM[i];
  cout<< NUM[num_size - 1];

}

// display used for decimal part
void HugeInt::display2() const{

  for( int i = num_size - prec; i < num_size; i++)
    cout<< NUM[i];

}



HugeInt HugeInt::add(HugeInt X){
  
  HugeInt temp;
  int rem = 0;
  int tot;

  for(int i = num_size - 1; i >= 0; i--)
    {
      tot = rem + NUM[i] + X.NUM[i];
      rem = tot / 10;//remainedr

      temp.NUM[i] = tot % 10;//add ones digit of total sum

    }
 
  return temp;

}

HugeInt HugeInt::multiply(HugeInt X){

  HugeInt temp1, temp2;
  int rem, tot = 0, k = 0;
  int size1 = number_length(); //length of hugeInt
  int size2 = X.number_length(); //length of inputed hugeInt

  /*
    start at the end of array: maximum size of number - 1
    decrease i till equal to: max size - size of the number
    
    ie number = 234. 
    num_size: 40  size of number: 3
    i start: 39   i end: 37
    
    ---same process for j below
  */




  for(int i = num_size - 1; i >= num_size - size2; i--)
    {
      rem = 0;    //set remainder back to 0 after going to next digit
      tot = 0;
      
      for(int l = 0; l < num_size; l++)
	temp2.NUM[l] = 0;    //set temp2 back to 0 after going to next digit
      
      //same idea as i above
      for(int j = num_size - 1; j >= num_size - size1; j--)
	{
	  tot = (NUM[j] * X.NUM[i]) + rem; //multiply the 2 nums plus prev remainder

	  //take ones digit of tot
	  
	  temp2.NUM[j - k] = tot % 10;//note on k below

	  rem = tot / 10;  //reaminder for next 

	  //when reach end of loop add the reamiander to the next space in array
	  temp2.NUM[num_size - size1 - 1 - k] = rem; //note on k below

	}
      /*
	after j loop, temp1 is sum of temp1 and temp2
	temp1 records progression of sums after each single digit produces
	a product with the entire other number
      */
      temp1 = temp1.add(temp2);

      /*
	k tracks which digit is being multipied through from i loop
	when k=0, at first digit from i loop, temp1 begins in ones
	place of array
	when k=1, multiplying second digit from i loop, temp2 begins
	one place over at the tens digit by -k
	so on so that k serves as a placeholder in temp2 array
      */
      k++;
      
    }
  
  //return the final sum
  return temp1;
}


HugeInt HugeInt::divide(HugeInt X){
  // HugeInt A.divide(X) ==> A / X ==> A divide by X
  // X is divisor

  int sizeD = X.number_length();
  int sizeN = number_length();
  
  HugeInt temp1;
  HugeInt temp2;
  HugeInt result;
  HugeInt one(1);
  HugeInt ten(10);

  for(int j = num_size - sizeN; j < num_size; j++)
    {
      temp1.NUM[num_size - 1] = NUM[j]; 
      
      //find how many times temp1 is divisible by the divisor 
      HugeInt num(1);
      for(int i = 1; i < 11; i++)
	{
	  if( (X * num) > (temp1) )
	    {
	      temp2 = X * (num - one); //greatest multiple less than temp1
	      result.NUM[j] = i-1; //set digit in the result
	      break;
	    }
	  else
	    num = num + one;
	}
      
      //find difference between temp1 and temp2
      //then shift number over one place
      temp1 = (temp1 - temp2) * ten;
    
    }

  return (result);
}

HugeInt HugeInt::divide2(HugeInt X){


  HugeInt remainder = *this - (X * (divide(X)) );

  HugeInt temp1;
  HugeInt temp2;
  HugeInt result;
  HugeInt one(1);
  HugeInt ten(10);

  temp1 = remainder * ten;

  for(int j = num_size - prec; j < num_size; j++)
    {
      //find how many times temp1 is divisible by the divisor 
      HugeInt num(1);
      for(int i = 1; i < 11; i++)
	{
	  if( (X * num) > (temp1) )
	    {
	      temp2 = X * (num - one); //greatest multiple less than temp1
	      result.NUM[j] = i - 1; //set digit in the result
	      break;
	    }
	  else
	    num = num + one;
	}
      
      //find difference between temp1 and temp2
      //then shift number over one place
      temp1 = (temp1 - temp2) * ten;
    
    }

  return (result);

}





bool HugeInt::isGreater(HugeInt X){
  bool value;
  int size1 = number_length();
  int sizeX = X.number_length();


  if(size1 > sizeX) //more digits then greater
    value = true;
  else
    {
      if(size1 < sizeX) //less digits then not greater
	value = false;
      else //compare digits if same number of digits
	{
	  for(int i = num_size - size1; i < num_size; i++)
	    {
	      if(NUM[i] > X.NUM[i])
		{
		  value = true;
		  break;
		}
	      else
		{
		  if(NUM[i] < X.NUM[i])
		    {
		      value = false;
		      break;
		    }
		  else
		    value = false;
		}
	    }
	}
    }

  return value;

}

bool HugeInt::isEqual(HugeInt X){
  bool value;
  int size1 = number_length();
  int sizeX = X.number_length();

  if(size1 == sizeX)//must have same number of digits
    {
      for(int i = 0; i < num_size; i++)
	{
	  if(NUM[i] != X.NUM[i])//once numbers dont match..break
	    {
	      value = false;
	      break;
	    }
	  if(i == num_size - 1)//if reach end then all equal
	    value = true;
	}
    }
  else
    value = false;

  return value;

}


HugeInt HugeInt::operator+(const HugeInt & Y){

  return add(Y);

}

HugeInt HugeInt::operator*(const HugeInt & Y){

  return multiply(Y);

}

bool HugeInt::operator>(const HugeInt & Y){

  bool value;

  //(isGreater(Y))?(value=true):(value=false);
  
  if(isGreater(Y))
    value = true;
  else 
    value = false;
  
  return value;

}

bool HugeInt::operator==(const HugeInt & Y){

  bool value;

  if(isEqual(Y))
    value = true;
  else
    value = false;

  return value;

}

bool HugeInt::operator!=(const HugeInt & Y){

  bool value;

  if(isEqual(Y))
    value = false;
  else
    value = true;

  return value;

}

bool HugeInt::operator>=(const HugeInt & Y){

  bool value;

  if(isEqual(Y) || isGreater(Y))
    value = true;
  else
    value = false;

  return value;

}

bool HugeInt::operator<(const HugeInt & Y){

  bool value;

  if(isEqual(Y) || isGreater(Y))
    value = false;
  else
    value = true;

  return value;

}

bool HugeInt::operator<=(const HugeInt & Y){

  bool value;

  if(isGreater(Y))
    value = false;
  else
    value = true;

  return value;

}

ostream& operator<<(ostream& o, const HugeInt & Y){

  Y.display();

  return o;

}

istream& operator>>(istream& i, HugeInt & Y){

  Y.input();
  
  return i;
  
}


HugeInt HugeInt::minus(HugeInt Y){

  int temp = 0;
  HugeInt result;

  for(int i = num_size - 1; i > num_size - 1 - number_length(); i--)
    {
      if(NUM[i] >= Y.NUM[i])
	{
	  result.NUM[i] = NUM[i] - Y.NUM[i];
	}
      else
	{
	  NUM[i - 1] -= 1;
	  temp = 10 + NUM[i];
       	  result.NUM[i] = temp - Y.NUM[i];
	}
    }
  return result;
}

HugeInt HugeInt::operator- (const HugeInt & Y){

  return minus(Y);

} 



#endif
