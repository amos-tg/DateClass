#include "date.h"
#include <iostream>
#include <cassert>
#include <string>
#include <format>

using namespace std;

const char *TEST_PASS = "Passed";

const char *DEFAULT_CONSTRUCTOR_TEST = 
  "Test (Default Date class constructor): ";
const char *PARAM_CONSTRUCTOR_TEST = 
  "Test (Parameterized Date class constructor): ";
const char *INVALID_CONSTRUCTOR_TEST = 
  "Test (Invalid Parameterized Date class constructor): ";
const char *LEAP_YEAR_TEST = "Test (Date class isLeapYear methods): ";
const char *EDGE_CASE_TEST = "Test (Date class common edge cases): ";
const char *LAST_DAY_TEST = "Test (Date class lastDay methods): ";
const char *SET_DATE_TEST = "Test (Date Class setDate method): ";

/// asserts that the output of all string returning output methods for the Date
/// class align with expectations based on the given year month and day.
void testOutput(Date &date, int year, int month, int day);

/// tests the default constructor for the Date class
void defaultConstructorTest(void);

/// tests the parameterized constructor for the Date class.
void paramConstructorTest(void);

/// tests to ensure invalid arguments to Date class constructor produce the
/// default date.
void invalidConstructorTest(void); 

/// tests the setDate(...) method from the Date class
void setDateTest(void); 

/// tests the isLeapYear methods from the Date class
void leapYearTest(void);

/// tests the lastDay methods from the Date class
void lastDayTest(void);

/// tests a variety of edge cases from the instructions
void edgeCaseTest(void);

int main(void) 
{
  defaultConstructorTest();
  paramConstructorTest();
  invalidConstructorTest();

  setDateTest();

  leapYearTest();

  lastDayTest();

  edgeCaseTest();

  // Date class getters are tested in almost all of the above tests because 
  // they are used internally.
  
  // Date class output functions are all tested in testOutput which is called 
  // frequently in the above tests internally.
  
  // Overloading Extension Tests
  // create a date using the default constructor and display it.
  cout << Date {} << endl;

  // create a date using the parameterized constructor and display it
  cout << Date { 2005, AUGUST, 1 } << endl;


  return 0;
}

// the int args for ymd are a bit redundant but reduce coupling with the class
// and seem appropriate since performance isn't important here.
void testOutput(Date &date, int year, int month, int day) 
{
  // asserts that output of the string producing methods matches the expected
  // behavior of the string formatting based on the year, month, and day.
  string month_str = Date::toStrMonth(month);
  assert(date.getDateMDYNum() == format("{}/{}/{}", month, day, year));
  assert(date.getDateMDYAlphNum() == format("{} {}, {}", month_str, day, year));
  assert(date.getDateDMYAlphNum() == format("{} {}, {}", day, month_str, year));
}

void defaultConstructorTest(void) 
{
  cout << DEFAULT_CONSTRUCTOR_TEST;
  // make sure the default constructor sets the date to:
  // year: 1900,
  // month: January,
  // day: 1,
  Date tested {};
  assert(tested.getYear() == 1900);
  assert(tested.getMonth() == JANUARY);
  assert(tested.getDay() == 1);
  cout << TEST_PASS << endl;
}

void paramConstructorTest(void) 
{
  cout << PARAM_CONSTRUCTOR_TEST;
  Date tested[]
  { 
    Date(2021, FEBRUARY, 28), 
    Date(2243, AUGUST, 1), 
    Date(9999, MAY, 17),
  };

  // mirror of the values inside the tested dates array, ordered
  int test_vals[]
  {
    2021, FEBRUARY, 28,
    2243, AUGUST, 1,
    9999, MAY, 17,
  };
 
  // for each Date make sure that the values are set properly using the getters
  // and the string outputting methods.
  for (int i {}; Date &dref: tested)
  {
    // set the year month and day for clarity
    int year { test_vals[i++] }; 
    int month { test_vals[i++] };
    int day { test_vals[i++] };

    // check the values with the getters
    assert(dref.getYear() == year);
    assert(dref.getMonth() == month);
    assert(dref.getDay() == day);

    // check the values with the string outputters
    testOutput(dref, year, month, day);
  }
  cout << TEST_PASS << endl;
}

void invalidConstructorTest(void) 
{
  cout << INVALID_CONSTRUCTOR_TEST;
  // invalid month test
  Date tested { 1900, 0, 1 };
  assert(tested.getMonth() == JANUARY);
  Date tested1 { 1900, 13, 1 };
  assert(tested1.getMonth() == JANUARY);
  
  // invalid day test
  Date tested2 { 1900, JANUARY, 0 };
  assert(tested2.getDay() == 1);
  Date tested3 { 1900, JANUARY, 40 };
  assert(tested3.getDay() == 1);

  // no invalid years defined for the project. 
  
  // output validation and reset test
  testOutput(tested1, 1900, JANUARY, 1); 
  cout << TEST_PASS << endl;
}

void setDateTest(void) 
{
  // valid tests
  cout << SET_DATE_TEST;
  Date tested {};  
  tested.setDate(1901, MAY, 3);
  assert(tested.getYear() == 1901);
  assert(tested.getMonth() == MAY);
  assert(tested.getDay() == 3);
  testOutput(tested, 1901, MAY, 3);

  // invalid tests
  
  // invalid month -- too small
  tested.setDate(1901, 0, 3);
  assert(tested.getMonth() == JANUARY);

  // invalid month -- too large
  tested.setDate(1901, 13, 3); 
  assert(tested.getMonth() == JANUARY);

  // invalid day test 
  tested.setDate(1901, APRIL, 32);
  assert(tested.getDay() == 1);

  // invalid day test for 30 day month 
  tested.setDate(1901, APRIL, 31);
  assert(tested.getDay() == 1);

  // invalid february day test
  tested.setDate(1901, FEBRUARY, 30);
  assert(tested.getDay() == 1);

  // confirm the object returns to default date
  testOutput(tested, 1900, JANUARY, 1);
  
  cout << tested.getDateMDYNum() << " : " << TEST_PASS << endl;
}

void leapYearTest(void)
{
  cout << LEAP_YEAR_TEST;
  // should be a leap year
  assert(Date::isLeapYear(2024));

  // shouldn't be a leap year
  assert(!Date::isLeapYear(2023));

  // century rule tests
  assert(!Date::isLeapYear(1900));
  assert(Date::isLeapYear(2000));

  // isLeapYear() calls isLeapYear(int year) internally with the year_m member
  // as the int year argument, so there is no need to test it seperately unless
  // that changes.

  cout << TEST_PASS << endl;
}

void lastDayTest(void) 
{
  cout << LAST_DAY_TEST;

  // check that lastDay returns the right day for a variety of leap year and non
  // leap year dates.
  assert(Date::lastDay(2024, JANUARY) == 31);
  assert(Date::lastDay(2024, APRIL) == 30);
  assert(Date::lastDay(1900, FEBRUARY) == 28);
  assert(Date::lastDay(2000, FEBRUARY) == 29);

  // don't need to test the no param overload because it uses the parameterized
  // overload internally by passing through the class member variables.
  cout << TEST_PASS << endl;
} 

void edgeCaseTest(void)
{
  cout << EDGE_CASE_TEST;

  // check that 4/30 valid; 4/31 invalid
  Date tested { 1900, APRIL, 30 };
  testOutput(tested, 1900, APRIL, 30);
  tested.setDate(1900, APRIL, 31);
  testOutput(tested, 1900, JANUARY, 1);

  // check that 6/30 valid; 6/31 invalid
  tested.setDate(1900, JUNE, 30);
  testOutput(tested, 1900, JUNE, 30);
  tested.setDate(1900, JUNE, 31);
  testOutput(tested, 1900, JANUARY, 1);

  // check that 2/28 is valid in non-leap year
  tested.setDate(1900, FEBRUARY, 28);
  testOutput(tested, 1900, FEBRUARY, 28);
  // check that 2/29 is invalid in non-leap year
  tested.setDate(1900, FEBRUARY, 29);
  testOutput(tested, 1900, JANUARY, 1);

  // check that 2/29 is valid in leap year
  tested.setDate(2000, FEBRUARY, 29);
  testOutput(tested, 2000, FEBRUARY, 29);

  // check that 2/30 is always invalid
  tested.setDate(2000, FEBRUARY, 30);
  testOutput(tested, 1900, JANUARY, 1);
  cout << TEST_PASS << endl;
}
