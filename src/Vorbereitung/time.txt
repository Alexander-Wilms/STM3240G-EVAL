// g++ -std=c++0x main.cpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

class Time
{
  public:
    Time(int min_input, int sec_input, int hun_input);

    int getMin();
    int getSec();
    int getHun();
    void setMin(int min_input);
    void setSec(int min_input);
    void setHun(int min_input);
    string print();
 private:
    int min;
    int sec;
    int hun;
};

Time::Time(int min_input, int sec_input, int hun_input)
{
	min = min_input%60;
	sec = sec_input%60;
	hun = ((hun_input%100)/10)*10;
}

int Time::getMin()
{
   return min;
}

int Time::getSec()
{
   return sec;
}

int Time::getHun()
{
   return hun;
}

void Time::setMin(int min_input)
{
   min = min_input%60;
}

void Time::setSec(int sec_input)
{
   sec = sec_input%60;
}

void Time::setHun(int hun_input)
{
   hun = ((hun_input%100)/10)*10;
}

string Time::print()
{
   	std::ostringstream output;
	output << min << ":" << sec << ":" << hun;
	string returnvalue = output.str();
	return returnvalue;
}

int main()
{
	int min_input, sec_input, hun_input;
	cin >> min_input;
	cin >> sec_input;
	cin >> hun_input;
	Time timeobject(min_input,sec_input,hun_input);
	cout << timeobject.print() << endl;
	return 0;
}
