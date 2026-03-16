#include "date.h"
#include <iostream>
#include <cstdlib>
#include <format>

using namespace std;

const char *ERR_INVALID_DATE = "Error: given date is invalid";

Date::Date(int year, int month, int day) 
{
  setDate(year, month, day);
}

void Date::setDate(int year, int month, int day) 
{
  if (!ymdValidate(year, month, day)) {
    // assign default date on failure
    year_m = 1900;
    month_m = JANUARY;
    day_m = 1; 

    return;
  }

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

bool Date::isLeapYear() const 
{
  return isLeapYear(year_m);
}

bool Date::isLeapYear(int year) const 
{
  if (year % 4) 
  {
    return false;
  }
  else if (year % 100) 
  {
    return true;
  }
  else if (year % 400)
  {
    return false;
  }
  else 
  {
    return true;
  }
}             

int Date::lastDay() const 
{                          
  lastDay(year_m, month_m);
}

int Date::lastDay(int year, int month) const 
{
  if (isLeapYear(year) && month == FEBRUARY) 
  {
    return month_num_days[month] + 1;
  }  

  return month_num_days[month];
}

bool Date::ymdValidate(int year, int month, int day) const 
{
  // check for all invalid months and for days before the first day of the month
  if (month > 12 || month < 1 || day < 1) 
  {
    return false;  
  } 

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

  default:
    cerr << ERR_INVALID_DATE << endl;
    exit(EXIT_FAILURE);
  }
}
