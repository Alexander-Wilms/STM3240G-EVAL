/*
 * timer.h
 *
 *  Created on: 26.10.2015
 *      Author: stfawilm
 */

#include <string>

#ifndef TIME_H_OFF_
#define TIME_H_OFF_

class Timer
{
  public:
    Timer(int stu_input, int min_input, int sec_input, int hun_input);

    int getStu();
    int getMin();
    int getSec();
    int getHun();
    void setStu(int min_input);
    void setMin(int min_input);
    void setSec(int min_input);
    void setHun(int min_input);
    std::string printtime();
 private:
    int stu;
    int min;
    int sec;
    int hun;
};

#endif /* TIME_H_OFF_ */

