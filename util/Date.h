#ifndef Date_h_
#define Date_h_

#include <string>
#include <time.h>
#include <assert.h>
#include <memory.h>

/** Kapselt Datum und Uhrzeit.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-05-26, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
class Date {

 public:
	/** Erzeugt ein Datum, das mit der aktuellen Uhrzeit initialisiert ist.
	 */
	Date() {
	  time_t help;
	  ::time(&help);
	  initFromTimeT(&help);
	}
	
	Date(Date* date) {
	  memcpy(&fCurrentTime, &(date->fCurrentTime), sizeof(struct tm));
	}

	
	Date(time_t* timeT) {
	  initFromTimeT(timeT);
	}
	
	void initFromTimeT(time_t* timeT) {
	  struct tm* helpTM = localtime(timeT);
	  assert(helpTM != 0);
	  memcpy(&fCurrentTime, helpTM, sizeof(struct tm));
	}
	
	Date(int year, int month, int day, int hour, int minute, int sec);

  Date add(int year, int month, int day, int hour, int minute, int sec);
	
	/** Raeumt auf. */
	virtual ~Date() {
	}
	
	/** Liefert das jahr.
	 *
	 * @return int jahr.
	 */
	int getYear() const {
	  return fCurrentTime.tm_year + 1900;
	}
	
	/** Liefert den monat.
	 *
	 * @return int monat.
	 */
	int getMonth() const {
	  return fCurrentTime.tm_mon + 1;
	}
	
	/** Liefert das Tagesdatum.
	 *
	 * @return int tagesdatum
	 */
	int getDay() const {
	  return fCurrentTime.tm_mday;
	}
	
	/** Liefert die Stundenzahl von 0-23.
	 *
	 * @return int Stundenzahl.
	 */
	int getHours() const {
	  return fCurrentTime.tm_hour;
	}
	
	/** Liefert Anzahl von minuten von 0-59.
	 *
	 * @return int Minutenanzahl.
	 */
	int getMinutes() const {
	  return fCurrentTime.tm_min;
	}
	
	/** Liefert Anzahl von Secunden von 0-59.
	 *
	 * @return int Sekundenzahl.
	 */
	int getSeconds() const {
	  return fCurrentTime.tm_sec;
	}
	
	std::string toString() const;
	
	bool equals(Date* other, long delta) const;
	
	long getAsLong() const;
	
	/** Corrects the Time e.g. 40.10 -> 9.11. */
	time_t getTimeT();
	
 private:
	/** aktuelle locale Uhrzeit. */
	struct tm fCurrentTime;
	
};

#endif // Date_h_
