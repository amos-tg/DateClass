#ifndef DATE_H
#define DATE_H

#include <string>

enum Months {
  JANUARY, FEBRUARY, MARCH,
  APRIL, MAY, JUNE,
  JULY, AUGUST, SEPTEMBER,
  OCTOBER, NOVEMBER, DECEMBER,
};

class Date {
  int year_m, month_m, day_m;
public: 
  Date(int year = 1900, int month = 1, int day = 1);

  void setDate(int year, int month, int day);

  inline int getMonth() const;
  inline int getDay() const;
  inline int getYear() const;

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
