#pragma once

class RobotMath {
public:
	float TrapeziumArea(float a, float b, float h);
	bool IsWithIn(float number, float comparator, float range);
};

extern RobotMath Math;