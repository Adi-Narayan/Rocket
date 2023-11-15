#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

//temperature is taken as 16C or 299K

const double atmpressure = 1;

struct RocketMeter
{
    double pressure;
    double velocity;
    double acceleration;
    double distance;
    double temperature1;
};
double pressure(struct RocketMeter t, double d2)
{
    //t.pressure = t.pressure * exp((-9.81 * 28.96 * (d2-d1))/(t.temperature1*0.0821));
if(t.pressure > 0)
{
    if (t.distance <= 11000)
        t.pressure = atmpressure * pow(1 - ((0.0065 * d2) / 299), (0.034 / 0.0065));
    if (t.distance > 11000 && t.distance <= 32000)
        t.pressure = atmpressure * pow(1 - ((0.001 * d2) / 299), (0.034 / 0.001));
    if (t.distance > 32000 && t.distance <= 47000)
        t.pressure = atmpressure * pow(1 - ((0.028 * d2) / 299), (0.034 / 0.0028));
    if (t.distance > 47000 && t.distance <= 71000)
        t.pressure = atmpressure * pow(1 - ((0.028 * d2) / 299), (30.034 / 0.0028));
    if (t.distance > 71000 && t.distance <= 100000)
        t.pressure = atmpressure * pow(1 - ((0.02 * d2) / 299), (0.034 / 0.002));
    if (t.distance > 100000)
        t.pressure = 0;
}
else
    t.pressure = 0;
return t.pressure;

}
double temperature(struct RocketMeter t, double d2)
{
    if (t.temperature1 > 0)
    {
        if (t.distance <= 11000)
            t.temperature1 = t.temperature1 - (d2 * 0.0065);
        if (t.distance > 20000 && t.distance <= 32000)
            t.temperature1 = t.temperature1 + (d2 * 0.001);
        if (t.distance > 32000 && t.distance <= 47000)
            t.temperature1 = t.temperature1 + (d2 * 0.0028);
        if (t.distance > 51000 && t.distance <= 71000)
            t.temperature1 = t.temperature1 - (d2 * 0.0028);
        if (t.distance > 71000 && t.distance <= 100000)
            t.temperature1 = t.temperature1 - (d2 * 0.002);
        if(t.distance > 100000)
            t.temperature1 = 3;
    }
    if(t.temperature1<0)
        t.temperature1 = 3;

    return t.temperature1;

}

void rocket1(struct RocketMeter t, int time)
{

    if (time > 30)
    {
        printf("\n***************************\n");
        printf("Elapsed time: 30 seconds \n");
        exit(0);
    }
    else {
        printf("Time = %d\n\n", time);
        if (t.distance >= 100000) {
            printf("Pressure = 0.00 atm\n");
            printf("temperature = 3 K\n");
        } else {
            printf("Pressure = %.2lf atm\n", t.pressure);
            printf("temperature = %.2lf K\n", t.temperature1);
        }
        printf("Altitude = %.2lf m\n", t.distance);
        printf("Velocity = %.2lf m/s\n", t.velocity);
        printf("Acceleration = %.2lf m/s^2\n", t.acceleration);

        time += 5;

        sleep(5);
        double d1, d2;
        d1 = t.distance;
        t.velocity = t.velocity + 5 * t.acceleration;
        d2 = t.distance + 5 * t.velocity;
        t.distance = d2;
        if(time>5)
        {
            printf("Total altitude is %.2lf km\n\n\n", d2 / 1000);
        }
        else
        {
            printf("Total altitude is 0 km\n\n\n");
        }
        d2 = d2-d1;
        //temperature
        t.temperature1 = temperature(t, d2);

        //pressure
        t.pressure = pressure(t, d2);

        rocket1(t, time);
    }
}

int rocket2(struct RocketMeter t)
{
    int t1, t2;
    double d1, d2, avgd;
    printf("Burn time is 30 seconds\n");
    printf("Enter first time stamp\n");
    scanf("%d", &t1);
    printf("Enter second time stamp\n");
    scanf("%d", &t2);

    t.distance = 0.5*t.acceleration*t1*t1;
    t.velocity = t.acceleration*t1;
    d2 = t.distance + t1 * t.velocity;
    t.distance = d2;
    d1 = t.distance;

    printf("Altitude at first timestamp = %.2lf m\n", t.distance);
    printf("Velocity at first timestamp = %.2lf m/s\n", t.velocity);
    printf("Pressure at first timestamp = %.2lf atm\n", pressure(t, d2));
    printf("Temperature at first timestamp = %.2lf K\n\n\n", temperature(t, d2));

    t.distance = 0.5*t.acceleration*t2*t2;
    avgd = (d1 + t.distance)/2.0;
    t.velocity = t.acceleration*t2;
    d1 = t.distance;
    d2 = t.distance + t2 * t.velocity;
    t.distance = d2;
    d2 = d2 - d1;

    printf("Altitude at second timestamp = %.2lf m\n", t.distance);
    printf("Velocity at second timestamp = %.2lf m/s\n", t.velocity);
    printf("Pressure at second timestamp = %.2lf atm\n", pressure(t, d2));
    printf("Temperature at second timestamp = %.2lf K\n\n\n", temperature(t, d2));

    printf("Average altitude is: %lf\n", avgd);
    printf("***************************\n");

    return 0;
}

int main()
{
    struct RocketMeter t;

    t.velocity = 0;
    t.distance = 0;
    t.acceleration = 0; // initial acceleration of 17m/s^2 is taken
    t.pressure = 1; //atm
    t.temperature1 = 299;

    int time = 0;
    printf("Enter initial acceleration of rocket: \n");
    scanf("%lf", &t.acceleration);
    printf("User Input or Simulated report? Reply with U or S\n");
    char ch;
    scanf("%c", &ch);
    printf("***************************\n");
    printf("         TELEMETRY         \n");
    printf("***************************\n\n");
    if(ch == 'S' || ch == 's')
        rocket1(t, time);
    else if(ch == 'U' || ch == 'u')
        rocket2(t);

    return 0;
}