#include "date.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

const char *TEST_PASS = "Passed";

const char *DEFAULT_TEST = "Test (Default Constructor): ";
const char *SET_DATE_TEST = "Test (setDate method): ";
const char *GET_DATE_MDY_NUM_TEST = "Test (getDateMDYNum method): ";

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

  return 0;
}
