# Robot Controller IDPPros | M102

## Intro

This repo contains all the code for the robot controller.

We used PlatformIO environment instead of the Arduino IDE, due to its vastly superior intellinsense, liniting and debugging.

A software engineer should **always** chose the best tools, and PlatformIO is siginficantly better than Arduino IDE.

## Structure

```
- include/configs.h
- lib/
	 |	LineSensor/ ..
	 |	Robot/..
	 .
	 .
- src/main.cpp
```

The main code is in `main.cpp`.
Pin configs are in `include/configs.h`
The the libaries for each class are found inside the `lib` folder. For each class there is a header `.h` and an implementation `.cpp`.

By splitting our code into seperate modules we have vastly improved our readability.

## Docs

**All methods have docstrings**, these docstrings desribe exactly what they do, what params they take and what they return.
