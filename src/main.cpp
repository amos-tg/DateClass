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
const char *LEAP_YEAR_TEST =
  "Test (Date class isLeapYear methods): ";

const char *YMD_VALIDATE_TEST = "Test (ymdValidate method): ";

const char *SET_DATE_TEST = "Test (setDate method): ";
const char *GET_DATE_MDY_NUM_TEST = "Test (getDateMDYNum method): ";
const char *GET_DATE_MDY_ALPH_NUM_TEST = "Test (getDateMDYAlphNum): ";
const char *GET_DATE_DMY_ALPH_NUM_TEST = "Test (getDateDMYAlphNum): ";
const char *SET_DATE_LEAP_TEST = "Test (setDate method on leap year): ";
const char *LAST_DAY_TEST = "Test (lastDay method): ";
const char *LAST_DAY_LEAP_TEST = "Test (lastDay method on leap year): ";
const char *TO_STR_MONTH_TEST = "Test (toStrMonth method): ";

/// asserts that the output of all string returning output methods for the Date
/// class align with expectations based on the given year month and day.
bool testOutput(Date &date, int year, int month, int day);

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
void lastDayTests(void);

int main(void) 
{
  cout << YMD_VALIDATE_TEST;
  Date manual; 
  manual.setDate(2004, FEBRUARY, 29);
  assert(manual.getDateMDYNum() == string("2/29/2004"));
  cout << TEST_PASS << endl;

  defaultConstructorTest();
  paramConstructorTest();
  invalidConstructorTest();


  // this internally tests the isLeapYear function which has the same logic in
  // it's overload, so I will omit the tests for those.
  cout << SET_DATE_LEAP_TEST;
  tested.setDate(2004, FEBRUARY, 29);
  assert(tested.getDateMDYNum() == string("2/29/2004"));
  cout << TEST_PASS << endl;

  const char *month_names[]
  {
    "January", "February", "March", "April",
    "May", "June", "July", "August", 
    "September", "October", "November", "December" 
  }; 

  cout << TO_STR_MONTH_TEST;
  for (int i {}; i < 12; ++i) 
  {
    tested.setDate(2000, i + 1, 1);
    assert(tested.getDateDMYAlphNum() == format("1 {}, 2000", month_names[i]));
  }
  cout << TEST_PASS << endl;

  return 0;
}

// the int args for ymd are a bit redundant but reduce coupling with the class
// and seem appropriate since performance isn't important here.
bool testOutput(Date &date, int year, int month, int day) 
{
  string month_str = Date::toStrMonth(month);
  assert(date.getDateMDYNum() == format("{}/{}/{}", month, day, year));
  assert(date.getDateMDYAlphNum() == format("{} {}, {}", month_str, day, year));
  assert(date.getDateDMYAlphNum() == format("{} {}, {}", day, month_str, year));
}

void defaultConstructorTest(void) 
{
  cout << DEFAULT_CONSTRUCTOR_TEST;
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
    Date(2021, FEBRUARY, 29), 
    Date(2243, AUGUST, 1), 
    Date(9999, MAY, 17),
  };

  int test_vals[]
  {
    2021, FEBRUARY, 29,
    2243, AUGUST, 1,
    9999, MAY, 17,
  };
 
  for (int i {}; Date &dref: tested)
  {
    int year { test_vals[i++] }; 
    int month { test_vals[i++] };
    int day { test_vals[i++] };

    assert(dref.getYear() == year);
    assert(dref.getMonth() == month);
    assert(dref.getDay() == day);

    assert(testOutput(dref, year, month, day));
  }
  cout << TEST_PASS << endl;
}

void invalidConstructorTest(void) 
{
  cout << INVALID_CONSTRUCTOR_TEST;
  Date tested { 1900, 0, 1 };
  assert(tested.getMonth() == JANUARY);
  Date tested1 { 1900, 13, 1 };
  assert(tested1.getMonth() == JANUARY);
  // no invalid years defined for the project. 
  
  // output validation test
  assert(testOutput(tested1, 1900, JANUARY, 1)); 
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
  assert(testOutput(tested, 1901, MAY, 3));

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
  assert(testOutput(tested, 1900, JANUARY, 1));
  
  cout << tested.getDateMDYNum() << " : " << TEST_PASS << endl;
}

void leapYearTests(void)
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

void lastDayTests(void) 
{
  cout << LAST_DAY_TEST;
  assert(Date::lastDay(2024, JANUARY) == 31);
  assert(Date::lastDay(2024, APRIL) == 30);
  assert(Date::lastDay(1900, FEBRUARY) == 28);
  assert(Date::lastDay(2000, FEBRUARY) == 29);

  // don't need to test the no param overload because it uses the parameterized
  // overload internally by passing through the class member variables.
  cout << TEST_PASS << endl;
} 
