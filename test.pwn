#include "inline_timers.inc"

main() 
{
    new 
        someInt = 1337,
        someStr[] = "hello world",
        Float: someFloat = 1.337
    ;

    inline TimerTest()
    {
        printf(" TimerTest called! %i, %s, %0.3f", someInt, someStr, someFloat);
    }
    new t = SetInlineTimer(using inline TimerTest, 3000, true);

    inline KillTheTests()
    {
        printf(" Killing the timer!");
        KillInlineTimer(t);

    }
    SetInlineTimer(using inline KillTheTests, 10000, false);
}