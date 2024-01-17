2 things need to happen:
1. change the cycle offset
2. change CYCLE_START_PIN

If you do not have the grid sensing sensor connected to the circuit, the following also needs to be changed:
1. line 915   cycleStartTriggerd = 0; //CHANGE WHEN THE GRID SENSING IS NOT CONNECTED
