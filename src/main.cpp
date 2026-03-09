#include "date.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

const char *TEST_PASS = "Passed";

const char *YMD_VALIDATE_TEST = "Test (ymdValidate method): ";
const char *DEFAULT_TEST = "Test (Default Constructor): ";
const char *SET_DATE_TEST = "Test (setDate method): ";
const char *GET_DATE_MDY_NUM_TEST = "Test (getDateMDYNum method): ";
const char *GET_DATE_MDY_ALPH_NUM_TEST = "Test (getDateMDYAlphNum): ";
const char *GET_DATE_DMY_ALPH_NUM_TEST = "Test (getDateDMYAlphNum): ";
const char *SET_DATE_LEAP_TEST = "Test (setDate method on leap year): ";
const char *LAST_DAY_TEST = "Test (lastDay method): ";
const char *LAST_DAY_LEAP_TEST = "Test (lastDay method on leap year): ";
const char *TO_STR_MONTH_TEST = "Test (toStrMonth method): ";

int main(void) {
  cout << DEFAULT_TEST;
  Date tested {};
  assert(tested.getYear() == 1900);
  assert(tested.getMonth() == JANUARY);
  assert(tested.getDay() == 1);
  cout << TEST_PASS << endl;

  cout << SET_DATE_TEST;
  tested.setDate(2026, AUGUST, 5);
  assert(tested.getYear() == 2026);
  assert(tested.getMonth() == AUGUST);
  assert(tested.getDay() == 5);
  cout << TEST_PASS << endl;

  cout << GET_DATE_MDY_NUM_TEST;
  assert(tested.getDateMDYNum() == string("8/5/2026"));
  cout << TEST_PASS << endl;

  cout << GET_DATE_MDY_ALPH_NUM_TEST;
  assert(tested.getDateMDYAlphNum() == string("August 5, 2026"));
  cout << TEST_PASS << endl;

  cout << GET_DATE_DMY_ALPH_NUM_TEST;
  assert(tested.getDateDMYAlphNum() == string("5 August, 2026"));
  cout << TEST_PASS << endl;

  // this internally tests the isLeapYear function which has the same logic in
  // it's overload, so I will omit the tests for those.
  cout << SET_DATE_LEAP_TEST;
  tested.setDate(2004, FEBRUARY, 29);
  assert(tested.getDateMDYNum() == string("2/29/2004"));
  cout << TEST_PASS << endl;

  int lastDay

  return 0;
}
