/**
 * @file RobotMath.cpp
 * @author IDPros
 * @brief Methods for math that are commly used
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <RobotMath.h>

 /**
  * @brief Checks if a number is within a tolerance
  *
  * @param number
  * @param comparator number to compare to
  * @param tolerance
  * @return true
  * @return false
  */
bool RobotMath::IsWithIn(float number, float comparator, float tolerance) {
	return (number > comparator - tolerance) && (number < comparator + tolerance);
}

/**
 * @brief Calculates the area of a trapezium
 *
 * @param a base
 * @param b base
 * @param h height
 * @return float area
 */
float RobotMath::TrapeziumArea(float a, float b, float h) {
	return 0.5 * (a + b) * h;
}