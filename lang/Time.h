#ifndef _Time_h_
#define _Time_h_

/** Klasse um moeglichst genaue Zeitinformationen vom System zu erfragen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-13, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2002/10/28 23:27:36 $
 *
 * @author cK $Author: gizmo $
 */
class Time {
	/** Erzeugt ein Time-Objekt. */
	Time();

	/** Raeumt auf. */
	virtual ~Time();

	/** Liefert die aktuelle Zeit in Microsekunden.
	 *
	 * @return double Aktuelle Zeit in Microsekunden.
	 */
	virtual double getCurrentTimeMicros();

private:
	/** Faktor der benoetigt wird um die timeticks in microsekunden
	 * umzurechnen. 
	 */
	double f;

};

#endif // _Time_h_

