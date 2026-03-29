#ifndef DATE_H
#define DATE_H

#define NUM_MONTHS 12

#include <string>
#include <array>
#include <iostream>

/// 1-12 month to integer enumeration, JANUARY = 1, FEBRUARY = 2, etc... 
enum Months 
{
  JANUARY = 1, FEBRUARY, MARCH,
  APRIL, MAY, JUNE,
  JULY, AUGUST, SEPTEMBER,
  OCTOBER, NOVEMBER, DECEMBER,
};

/// array of the number of days in a month, 0 based indexing, i.e. january is at
/// index zero, february is at index 1, etc...
const std::array<int, NUM_MONTHS> month_num_days 
{
  31, 28, 31, 
  30, 31, 30, 
  31, 31, 30,
  31, 30, 31, 
};

class Date 
{
  /// time specificer storage members
  int year_m, month_m, day_m;
public: 
  /// - optional parameters:
  ///   - int year : the year portion of the date
  ///   - int month : the month portion of the date
  ///   - int day : the day portion of the date
  ///
  /// Instantiates a Date instance with input validation on the month and day
  /// based on the number of days in each month, with leap years taken into
  /// consideration. If the month or day is invalid, the default date, January
  /// 1st, 1900 is set. 
  Date(int year = 1900, int month = JANUARY, int day = 1);

  Date& operator++(void);
  Date operator++(int);

  Date& operator--(void);
  Date operator--(int);

  friend Date operator-(Date& lhs, Date& rhs);

  friend void operator<<(std::ostream ostream, Date& date);

  friend void operator>>(std::istream istream, Date& date);  

  /// - int year : the year portion of the date
  /// - int month : the month portion of the date
  /// - int day : the day portion of the date
  ///
  /// Sets the date on a Date instance based on the arguments passed, where the
  /// month, and day are validated, if the month or day are invalid, the default
  /// date will be set, which is January 1st, 1900.
  void setDate(int year, int month, int day);

  /// returns the currently stored month member, that is guarenteed to be valid.
  /// month is [1, 12] <- interval notated
  int getMonth() const;

  /// returns the currently stored day member, that is guarenteed to be valid.
  /// day is [1, max_day_in_month] <- interval notated, based on the array of
  /// max number of days in a month.
  int getDay() const;

  /// returns the currently stored year member.
  int getYear() const;

  /// returns a string date in the following format: 
  /// MonthNumber/DayNumber/YearNumber
  std::string getDateMDYNum() const;

  /// returns a string date in the following format:
  /// Month DayNumber, YearNumber
  std::string getDateMDYAlphNum() const;

  /// returns a string date in the following format:
  /// DayNumber Month, YearNumber
  std::string getDateDMYAlphNum() const;

  /// returns true if it's the currently stored year member is a leap year;
  /// returns false if the year is not a leap year.
  bool isLeapYear() const;

  /// returns true if the year argument passed is a leap year; returns false
  /// if the year is not a leap year.
  static bool isLeapYear(int year);

  /// returns the total number of days in the month of the stored month member
  /// variable.
  int lastDay() const;

  /// returns the total number of days in the month of the passed month
  /// argument, that is influenced based on whether the year is a leap year. 
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
  /// - int year : the year checked
  /// - int month : the month checked
  /// - int day : the day checked
  ///
  /// Takes a year, month, and day argument and determines whether or not it
  /// represents a valid gregorian calendar date. Returns true for a valid
  /// date, and false for an invalid date.  
  bool ymdValidate(int year, int month, int day) const; 

  /// helper function for prefixed and postfixed ++ operators that adds a day
  /// to thedate.
  void addOneDay(void);

  /// helper function for prefixed and postfixed -- operators that subtracts a
  /// day from the date. 
  void subOneDay(void);
};

#endif
