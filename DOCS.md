send helpAuctoritate mihi commissa admitto te in Scholarem Discipulum
huius Collegii in nomine Dei omnipotentis

line follower (proportional control)
need to get the front line sensor to work in tandem

```cpp
if (front line sensor = on line && -0.5 < LineSensor.LineFollowSense < 0.5){
robot is on junction
if (carrying box = true){
if (box = metal){
Bot.Rotate into red box
}
else {
Bot.Rotate into blue box
}
}
else {
Bot.MoveAll();
}
}
else if (front line sensor = off line && -0.5 < LineSensor.LineFollowSense < 0.5) {
Bot.StopAll();
run IR sensor and sweep
}
```
