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
  static bool isLeapYear(int year);

  int lastDay() const;
  static int lastDay(int year, int month);

  /// - int month: month number (1-12).
  ///
  /// Invalid month numbers will cause program termination with an appropriate
  /// error message.
  ///
  /// returns the string format of the month number passed in, i.e. 1 is
  /// returned as a string containing "January". 
  static std::string toStrMonth(int month);
private:
  bool ymdValidate(int year, int month, int day) const; 
};

#endif
