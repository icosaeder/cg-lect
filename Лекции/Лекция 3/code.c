const int MAX_SKIP = 1, SKIP_TICKS = 25, TIME_PRECISION_FACTOR = 0;
const float TIME_FACTOR = 1000;
int controlLoops = 0, loops = 0;
int long long nextTick, startTime, endTime;
float delta = 1;
int deltaIsValid = 0;

nextTick = startTime = currentTime();

while (shouldContinue())
{
    controlLoops = 0;
    while (currentTime() > nextTick && controlLoops < MAX_SKIP)
    {
        obtainInformationFromControlDevices();
        
        nextTick += SKIP_TICKS;
        ++controlLoops;
    }
    
    changeScane(delta, deltaIsValid);
    renderScene();
    
    if (loops++ > TIME_PRECISION_FACTOR)
    {
        deltaIsValid = 1;
        endTime = currentTime();
        delta = (endTime - startTime) / (loops * TIME_FACTOR);
        startTime = endTime;
        loops = 0;
    }
}
