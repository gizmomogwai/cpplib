#ifndef _Properties_h_
#define _Properties_h_

#include <string>
#include <map>

#include <io/DataInputStream.h>
#include <io/DataOutputStream.h>
#include <util/NoSuchElementException.h>

/** Inifilemaessige Properties.
 *
 * Um genauer zu sein eher Java-maessige Properties :)).
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-29, cK, Created.
 *   <li> 2001-02-08, cK, Kommentare ignoriert.
 *   <li> 2001-02-08, cK, Leak gestopft (kommentarzeilen wurden nicht befreit).
 *   <li> 2001-02-08, cK, bei read wurde falls nur einer von 
 *        key oder value != 0 ist ein leak erzeugt. 
 *        (wie kann das eigentlich vorkommen???).
 *   <li> 2001-02-13, cK, Debugausgabe raus.
 * </ul>
 *
 * @todo Von Datainputstream wegkommen!
 * @todo Schoenwaere, wenn man key kommentieren koennte???!!!
 * @todo Ist map wirklich das richtige????!!! eher hash_map gibts aber nur
 *       bei sgi????!!! dafuer muss man nicht sortieren :))
 * @todo Ich hab jetzt ueberall pointer auf strings .. evtl sind hier aber 
 *       references besser??? mit dem fabian abtesten .. vorteil waere
 *       eignetlich nur, dass man const besser definieren kann.
 * @todo Evtl. ist das mit den reads nicht so schoen .. lieber codecs an
 *       den start bringen??? Vortail evtl. xml config, aber so ists auch ganz ok :))
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
class Properties {
  
 public:
  /** Erzeugt neue Properties. */
  Properties();
  
  /** Raeumt auf. */
  virtual ~Properties();
  
  /** Liest die Properties aus einem DataInputStream.
   *
   * @param in Datenquelle. 
   */
  void read(DataInputStream& in);
  
  /** Schreibt die Properties in einen Ausgabestrom.
   *
   * @param out Datensenke.
   */
  void write(DataOutputStream& out);
  
  /** Liefert das Property zu einem string.
   *
   * @param key Das gesucht Property.
   *
   * @return std::string
   *
   * @exception NoSuchElementException falls der key 
   *            nicht gefunden werden kann.
   */
  std::string getProperty(const std::string& key) 
		throw (NoSuchElementException);
	
	/**
	 * Liefert das Property zu einem String.
	 * 
	 * @param key std::string das gesuchte property.
	 * @param defaultValue std::string kopie dieses strings wird geliefert wenn kein wert vorhanden ist.
	 * @return std::string
	 */
	std::string getProperty(const std::string& key, const std::string& defaultValue);
  
  /** Setzt ein Property.
   *
   * @param key Schluessel, unter dem der Wert aufgefunden werden kann.
   * @param value Wert des SChluessels.
   */
  void setProperty(const std::string& key, const std::string& value);
  
  /** Liefert eine Stringrepraesentation.
   *
   * @return std::string stringrep.
   */
  std::string toString();
  
 private:
  /** Hashmap um die Zuordnung schluessel-wert schnell zu machen. */
  std::map<std::string, std::string> theMap;
  
};

#endif // _Properties_h_
