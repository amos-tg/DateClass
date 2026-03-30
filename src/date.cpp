#include "date.h"
#include <iostream>
#include <cstdlib>
#include <format>

using namespace std;

Date::Date(int year, int month, int day) 
{
  setDate(year, month, day);
}

Date& Date::operator++(void) 
{
  addOneDay();
  return *this;
}

Date Date::operator++(int) 
{
  Date copy = *this;
  addOneDay();
  return copy;
}

Date& Date::operator--(void) 
{
  subOneDay();
  return *this;
}

Date Date::operator--(int) 
{
  Date copy = *this;
  subOneDay();
  return copy;
}

long int operator-(Date& lhs, Date& rhs) 
{
  // convert each date into a total number of days and subtract the smaller one
  // from the larger one  to get the number of days between them.
  return Date::getTotalDays(lhs) - Date::getTotalDays(rhs);
} 

ostream& operator<<(ostream& ostream, const Date& date) 
{
  if (ostream) ostream.clear();
  ostream << date.getDateMDYAlphNum();
  return ostream;
}

istream& operator>>(istream& istream, Date& date)
{
  if (istream) istream.clear();
  if (cout) cout.clear();

  int date_val {};

  for (; date_val > 0 && date_val <= date.lastDay();) 
  {
    cout << "What is the current day of the Month?: ";
    cout.flush();
    if (istream) istream.clear();
    istream >> date_val;
  }
  date.day_m = date_val;  
  date_val = 0;

  for (; date_val > 0 && date_val <= 12;)
  {
    cout << "What is the current month of the year?: ";
    cout.flush();
    istream >> date_val;
  }
  date.month_m = date_val;

  for (; date_val > 0 && date.year_m > 0;)
  {
    cout << "What is the current year?: ";
    cout.flush();
    istream >> date_val;
  }
  date.year_m = date_val;

  return istream;
}

void Date::setDate(int year, int month, int day) 
{
  // check if it's an invalid date
  if (!ymdValidate(year, month, day)) {
    // assign default date to an invalid input
    year_m = 1900;
    month_m = JANUARY;
    day_m = 1; 

    return;
  }

  // assign the date based on the arguments
  year_m = year;
  month_m = month; 
  day_m = day;
}

int Date::getMonth() const 
{
  return month_m;
}

int Date::getDay() const 
{
  return day_m;
}

int Date::getYear() const 
{
  return year_m;
}

long int Date::getTotalDays(const Date& date)
{
  // account for days into current month
  long int total_days = date.day_m;  

  // -2 because, 1->0 based indexing && current month account for^^^
  for (int month { date.month_m - 2 }; month > 0; --month)
    total_days += month_num_days[month];    

  // get the number of days into the year
  if (date.isLeapYear() && date.month_m >= FEBRUARY) 
    ++total_days;

  // get the number of days from the number of years
  for (int year { date.year_m }; year > 0; --year)
  {
    // handle leap years
    if (date.isLeapYear())
      total_days += 366;
    else 
      total_days += 365;
  }

  return total_days;
}

std::string Date::getDateMDYNum() const 
{
  return format("{}/{}/{}", month_m, day_m, year_m);
}

std::string Date::getDateMDYAlphNum() const 
{
  return format("{} {}, {}", toStrMonth(month_m), day_m, year_m);
}

std::string Date::getDateDMYAlphNum() const 
{
  return format("{} {}, {}", day_m, toStrMonth(month_m), year_m);
}

// wrapper
bool Date::isLeapYear() const 
{
  return isLeapYear(year_m);
}

bool Date::isLeapYear(int year)
{
  if (year % 4) 
  {
    // if there is a remainder when divided by 4 it is not a leap year
    return false;
  }
  else if (year % 100) 
  {
    // if there is no remainder when divided by 4 and a remainder when divided
    // by 100 it is a leap year
    return true;
  }
  else if (year % 400)
  {
    // if there is no remainder when divided by 4 and 100, but there is a
    // remainder when divided by 400, then it is not a leap year.
    return false;
  }
  else 
  {
    // If there's no remainder when divided by 4, 100, and 400, it's a leap year
    return true;
  }
}             

int Date::lastDay() const 
{                          
  return lastDay(year_m, month_m);
}

int Date::lastDay(int year, int month)
{
  // month - 1 to account for one based month enum conversion to zero based
  // month days enum. 
  
  // if it's a leap year and february their is one more day than usual
  if (isLeapYear(year) && month == FEBRUARY) 
  {
    return month_num_days[month - 1] + 1;
  }  

  // index into the total number of days in a month array.
  return month_num_days[month - 1];
}

bool Date::ymdValidate(int year, int month, int day)
{
  // check for all invalid months and for days before the first day of the month
  if (month > 12 || month < 1 || day < 1) 
  {
    return false;  
  } 

  // store the leap year conditional output for reuse so month var can be
  // manipulated more clearly.
  bool leap_feb { isLeapYear(year) && month == FEBRUARY };

  // account for zero based indexing on month_num_days array in terms of the 
  // one based enum of month names.
  --month;

  // check if greater than the top end of the day range for non leap years
  if (day > month_num_days[month] && !leap_feb ) {
    return false;
  } 

  // check if greater than the top end of the day range for leap years
  if (leap_feb && day > month_num_days[month] + 1)
  {
    return false;
  }

  return true;
}

string Date::toStrMonth(int month) 
{
  const char *ERR_INVALID_DATE = "Error: given date is invalid";

  // convert the Months enum values into their string equivalents 
  switch (month)
  {
  case JANUARY:
    return string("January");

  case FEBRUARY:
    return string("February");

  case MARCH: 
    return string("March");

  case APRIL:
    return string("April");

  case MAY:
    return string("May");

  case JUNE:
    return string("June");

  case JULY:
    return string("July");

  case AUGUST:
    return string("August");

  case SEPTEMBER:
    return string("September");

  case OCTOBER:
    return string("October");

  case NOVEMBER:
    return string("November");

  case DECEMBER:
    return string("December");

  // exit if it's an invalid month
  default:
    cerr << ERR_INVALID_DATE << endl;
    exit(EXIT_FAILURE);
  }
}

void Date::addOneDay(void) 
{
  if (day_m == this->lastDay() && month_m == 12) 
  {
    day_m = 1;
    month_m = 1;
    ++year_m;

    return;
  } 
  else if (day_m == this->lastDay())
  {
    day_m = 1;
    ++month_m;

    return;
  }

  ++day_m;
}

void Date::subOneDay(void)
{
  if (day_m == 1 && month_m == 1)
  {
    --year_m;
    month_m = 12;
    day_m = month_num_days[month_m - 1];
  }
  else if (day_m == 1)
  {
    --month_m;
    day_m = month_num_days[month_m -1];
  }

  --day_m;
}

