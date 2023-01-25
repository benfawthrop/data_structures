#include <iostream>
#include "time.h"
#include <string>

Time::Time(){
    hour = 0;
    minute = 0;
    second = 0;
}

Time::Time(int ahour, int aminute, int asecond){
    hour = ahour;
    minute = aminute;
    second = asecond;
}
// getters
int Time::getHour() const{
    return hour;
}
int Time::getMinute() const{
    return minute;
}
int Time::getSecond() const{
    return second;
}
// setters
void Time::setHour(int ahour){
    hour = ahour;
}
void Time::setMinute(int aminute){
    minute = aminute;
}
void Time::setSecond(int asecond){
    second = asecond;
}

// extras
void Time::PrintAMPM(){
    std::string ampm;

    if (hour > 12){
        std::cout << hour - 12;
        ampm = " pm";
        
    } else {
        std::cout << hour;
        ampm = " am";
    }

    if (minute < 10){
        std::cout << ':' << '0' << minute << ':';
    } else {
        std::cout << ':' << minute << ':';
    }

    if (second < 10){
        std::cout << '0' << second;
    } else{
        std::cout << second;
    }
    std::cout << ampm << std::endl;
}

bool IsEarlierThan(const Time& t1, const Time& t2){
    if (t1.getHour() != t2.getHour()){
        return t1.getHour() > t2.getHour();
    } else if (t1.getMinute() != t2.getMinute()){
        return t1.getMinute() > t2.getMinute();
    } else {
        return t1.getSecond() > t2.getSecond();
    }
}