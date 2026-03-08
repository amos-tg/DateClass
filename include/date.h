#ifndef DATE_H
#define DATE_H

#define NUM_MONTHS 12

#include <string>
#include <array>

enum Months 
{
  JANUARY = 1, FEBRUARY, MARCH,
  APRIL, MAY, JUNE,
  JULY, AUGUST, SEPTEMBER,
  OCTOBER, NOVEMBER, DECEMBER,
};

const std::array<int, NUM_MONTHS> month_num_days 
{
  31, 28, 31, 
  30, 31, 30, 
  31, 31, 30,
  31, 30, 31, 
};

class Date 
{
  int year_m, month_m, day_m;
public: 
  Date(int year = 1900, int month = JANUARY, int day = 1);

  void setDate(int year, int month, int day);

  int getMonth() const;
  int getDay() const;
  int getYear() const;

  std::string getDateMDYNum() const;
  std::string getDateMDYAlphNum() const;
  std::string getDateDMYAlphNum() const;

  bool isLeapYear() const;
  bool isLeapYear(int year) const;

  int lastDay() const;
  int lastDay(int year, int month) const;
private:
  bool ymdValidate(int year, int month, int day) const; 

  std::string toStrMonth(int month) const;
};

#endif
