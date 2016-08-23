#ifndef _StringTokenizer_h_
#define _StringTokenizer_h_

#include <string>
#include <memory>

/** StringTokenizer.
 *
 * An den Java-Stringtokenizer angelehnt.
 * Interessant auch thinking in c++ 2. teil. Da macht eckel auch 
 * etwas sehr aehnliches generell auf streams.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-30, cK, Created.
 * </ul>
 *
 * @todo ueberlegen, ob man ein countTokens braucht!
 * @todo evtl. inlinen, aber erst benchmarks dafuer!
 * @todo evtl. ueberlegen, ob man gepointerte strings reingibt
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:50 $
 *
 * @author cK, $Author: gizmo $
 */
class StringTokenizer {
  
 public:
  /** Erzeugt einen Stringtokenizer.
   *
   * @param _source Zu zerlegender String.
   * @param _delimiters string, der alle zeichen enthaelt, die als 
   *        delimiter zu behandeln sind.
   */
  StringTokenizer(std::string _source, std::string _delimiters);

  /** Raeumt auf. */
  virtual ~StringTokenizer();

  /** Liefert den naechsten String.
   *
   * @return std::string* pointer auf einen string (bitte deleten) 
   *         oder 0, falls nichts mehr da ist! der string muss von der
   *         applikation freigegeben werden.
   */
  std::auto_ptr<std::string> next();

  /** Liefert den rest des strings, vom letzten nicht mehr gelieferten
   * zeichen an.
   *
   * delimiters werden hier nicht mehr beachtet.
   *
   * @return std::string* rest des zu tokenifierenden strings oder 0. 
   *         der string muss von der applikation freigegeben werden.
   */
  std::auto_ptr<std::string> rest();

 private:
  /** Untersucht, ob ein charachter ein delimiter ist. 
   *
   * @param v Character.
   *
   * @return true falls im delimiterstring enthalten.
   */
  bool isDelimiter(char v);
    
  /** string, der zerlegt werden soll. */
  std::string source;
    
  /** string mit trennzeichen. */ 
  std::string delimiters;

  /** start des tokens. */
  std::string::const_iterator start;

  /** ende des tokens. */
  std::string::const_iterator end;
  
};

#endif // _StringTokenizer_h_
