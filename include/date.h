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
  int year, month, day;
public: 
  Date(int year, int month, int day);

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
  bool ymdValidate(int year, int month, int day); 
};

#endif
