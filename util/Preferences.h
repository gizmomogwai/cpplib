#ifndef _Preferences_h_
#define _Preferences_h_

#include <util/UtilApi.h>

#include <string>
#include <util/NoSuchElementException.h>

/** Oberklasse aller Preferences-klassen.
 *
 * Evtl sind PropertyPreferences oder RegistryPreferences denkbar.
 * Zusaetzlich ist evtl ein systemweites Preferencessingleton denkbar.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 * </ul>
 *
 * @todo genau ueberlegen, wie man hier abgehen sollte .... vor allem 
 *       das mit den defaults ist interessant.
 * @todo auch interessant ist, wie mit den getProperties und fehlerfaellen
 *       verfahren werden sollte.
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
class UTIL_API Preferences {

 public:

	/** Raeumt auf. */
	virtual ~Preferences() {
	}

	/** Liefert zu einem key den zugehoerigen wert 
	 * aus den preferences oder 0.
	 *
	 * @param key Schluessel.
	 * @param v Defaultwert.
	 *
	 * @return std::string* ergebnis oder 0 falls weder default noch
	 *         schluessel gefunden wurde.
	 * 
	 * @exception NoSuchElementException wenn der schluessel nicht gefunden
	 *	 wird und die angabe 0 ist.
	 */
	virtual std::string getString(const std::string& key, const std::string& v) throw (NoSuchElementException);

	/** Liefert einen String.
	 *
	 * @param key Schluessel.
	 *
	 * @return std::string* string bitte befreien.
	 *
	 * @exception NoSuchElementException falls der Schluessel nicht
	 *		 vorhanden ist. 
	 */
	virtual std::string getString(const std::string& key) 
		throw (NoSuchElementException) = 0;

	/** Liefert ein Float
	 *
	 * @param key Schluessel.
	 *
	 * @return float Float.
	 *
	 * @exception NoSuchElementException falls der Schluessel nicht
	 *	 vorhanden. 
	 */
	virtual float getFloat(const std::string& key) 
		throw (NoSuchElementException) = 0;

	/** Liefert ein float.
	 *
	 * @param key Schluessel.
	 * @param v DefaultValue.
	 *
	 * @return float gefundener wert oder default.
	 */
	virtual float getFloat(const std::string& key, float v) {
		try {
			return(getFloat(key));
		} catch (NoSuchElementException) {
			return(v);
		}
	}
    

	/** Liefert ein Int.
	 *
	 * @param key Schluessel.
	 *
	 * @return int Int.
	 *
	 * @exception NoSuchElementException falls der Schluessel nicht
	 *	 vorhanden. 
	 */
	virtual int getInt(const std::string& key) = 0;

	/** Liefert ein int.
	 *
	 * @param key Schluessel.
	 * @param v DefaultValue.
	 *
	 * @return int integer.
	 */
	virtual int getInt(const std::string& key, int v) {
		try { 
			return(getInt(key));
		} catch (NoSuchElementException) {
			return(v);
		}
	}


	/** Liefert ein Long.
	 *
	 * @param key Schluessel.
	 *
	 * @return long Long.
	 *
	 * @exception NoSuchElementException falls der Schluessel nicht
	 *	 vorhanden. 
	 */
	virtual long getLong(const std::string& key) 
		throw (NoSuchElementException) = 0;

	/** Liefert ein long
	 *
	 * @param key Schluessel.
	 * @param v DefaultValue.
	 *
	 * @return long integer.
	 */
	virtual long getLong(const std::string& key, long v) {
		try {
			return(getLong(key));
		} catch (NoSuchElementException) {
			return(v);
		}
	}
  
};


#endif // _Preferences_h_
