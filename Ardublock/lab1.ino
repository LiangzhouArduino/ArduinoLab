#include <TinkerKit.h>

void setup()
{
pinMode( O3 , OUTPUT);
pinMode( 1 , INPUT);
}

void loop()
{
if (digitalRead( 1))
{
digitalWrite( O3 , HIGH );
}
delayMicroseconds( 1000 );
}


