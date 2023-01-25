#ifndef __time_h__
#define __time_h__


class Time {

    public:
        Time();
        Time(int ahour, int aminute, int asecond);

        // Accessors
        int getHour() const;
        int getMinute() const;
        int getSecond() const;

        // Modifiers
        void setHour(int ahour);
        void setMinute(int aminute);
        void setSecond(int asecond);

        // other fxns
        void PrintAMPM();


    private:
        int hour;
        int minute;
        int second;
};
bool IsEarlierThan(const Time& t1, const Time& t2);
#endif