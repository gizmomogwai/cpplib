#include <util/Date.h>

#include <sstream>
#include <iostream>
#include <stdlib.h>

Date::Date(int year, int month, int day, int hour, int minute, int sec) {
	fCurrentTime.tm_sec = sec;
	fCurrentTime.tm_min = minute;
	fCurrentTime.tm_hour = hour;
	fCurrentTime.tm_mday = day;
	fCurrentTime.tm_mon = month - 1;
	fCurrentTime.tm_year = year - 1900;
	//fCurrentTime.tm_isdst = 0;
	
	//	time_t ticks = getTimeT();
    /*
<<<<<<< .mine
=======
	Date dstCorrectureDate(&ticks);

	if (dstCorrectureDate.fCurrentTime.tm_hour != fCurrentTime.tm_hour) {
		std::cout << "dst anpassung" << std::endl;
		fCurrentTime.tm_isdst = 0;
	}
>>>>>>> .r141
	*/
	//	Date dstCorrectureDate(&ticks);
}

bool Date::equals(Date* other, long delta=0) const {
	long l1 = getAsLong();
	long l2 = other->getAsLong();
	long diff = l1 - l2;
	diff = ::abs(diff);
	
	return diff <= delta;
}

Date Date::add(int year, int month, int day, int hour, int minute, int sec) {
  time_t ticks = getTimeT();
  ticks += sec;
  ticks += minute * 60;
  ticks += hour * 60 * 60;
  ticks += day * 60 * 60 * 24;
  Date d(&ticks);
  d.fCurrentTime.tm_year += year;
  while (month != 0) {
    if (month >= 12) {
      month -= 12;
      d.fCurrentTime.tm_year++;
    } else if (month <= -12) {
      month += 12;
      d.fCurrentTime.tm_year--;
    } else {
      d.fCurrentTime.tm_mon += month;
      month = 0;
    }
  }
  return d;
}


long Date::getAsLong() const {
	return
	  getYear() * 400 * 24 * 60 * 60 +
	  getMonth() * 31 * 24 * 60 * 60 +
	  getDay() * 24 * 60 * 60 +
	  getHours() * 60 * 60 +
	  getMinutes() * 60 +
	  getSeconds();
}

std::string Date::toString() const {
	std::ostringstream out;
  out << getYear() << "-" << getMonth() << "-" << getDay() << "-" << getHours() << "-" << getMinutes() << "-" << getSeconds();
	return out.str();
}

time_t Date::getTimeT() {
	return mktime(&fCurrentTime);
}
