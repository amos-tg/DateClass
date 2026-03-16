#include "date.h"
#include <iostream>
#include <cassert>
#include <string>
#include <format>

using namespace std;

const char *TEST_PASS = "Passed";

const char *DEFAULT_TEST = "Test (Default Date class constructor): ";
const char *PARAM_TEST = "Test (Parameterized Date class constructor): ";

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

int main(void) 
{
  cout << YMD_VALIDATE_TEST;
  Date manual; 
  manual.setDate(2004, FEBRUARY, 29);
  assert(manual.getDateMDYNum() == string("2/29/2004"));
  cout << TEST_PASS << endl;

  defaultConstructorTest();
  paramConstructorTest();

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

void defaultConstructorTest(void) 
{
  cout << DEFAULT_TEST;
  Date tested {};
  assert(tested.getYear() == 1900);
  assert(tested.getMonth() == JANUARY);
  assert(tested.getDay() == 1);
  cout << TEST_PASS << endl;


  return;
}

void paramConstructorTest(void) 
{
  cout << PARAM_TEST;
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

// the int args for ymd are a bit redundant but reduce coupling with the class
// and seem appropriate since performance isn't important here.
bool testOutput(Date &date, int year, int month, int day) 
{
  string month_str = Date::toStrMonth(month);
  assert(date.getDateMDYNum() == format("{}/{}/{}", month, day, year));
  assert(date.getDateMDYAlphNum() == format("{} {}, {}", month_str, day, year));
  assert(date.getDateDMYAlphNum() == format("{} {}, {}", day, month_str, year));
}
