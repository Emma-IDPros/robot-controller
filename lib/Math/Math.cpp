#include <Math.h>

bool RobotMath::IsWithIn(float number, float comparator, float range) {
	return (number > comparator - range) && (number < comparator + range);
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