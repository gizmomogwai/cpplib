#ifndef _SequenceInputStream_h_
#define _SequenceInputStream_h_

#include <io/InputStream.h>
#include <list>

/** Inputstream auf einer Menge von zugrundeliegenden InputStreams.
 *
 * Normalerweise ist das eignetlich auch so eine art FilterInputStream,
 * da das aber nicht ganz zusammenpasst mit der initialisierungsmethode 
 * jetzt eben so.
 *
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-19, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:31 $
 *
 * @author cK, $Author: koestlin $
 */
class SequenceInputStream : public InputStream {
  
 public:
  /** Erzeugt einen neuen InputStream durch aneinanderhaengen von 2
   * Stroemen. 
   *
   * @param in1 Erster Strom.
   * @param in2 Zweiter Strom.
   */
  SequenceInputStream(InputStream* in1, InputStream* in2);
  
  /** Raeumt auf, die Stroeme werden nicht freigegeben.
   */
  virtual ~SequenceInputStream();
  
  int read() throw (IOException);
  
  int read(DataBuffer& target, int offset, int length) throw (IOException);
  
 private:
  /** Setzt auf den naechsten Stream. Der Strom wird auf 0 gesetzt, wenn
   * kein Strom mehr abzuarbeiten ist.
   */
  void nextStream();
  
  /** Vector mit InputStreams. */
  std::list<InputStream*> streamList;
  
  /** Iterator ueber alle Streams. */
  std::list<InputStream*>::iterator i;
  
  /** Gerade auszulesender InputStream. */
  InputStream* in;
  
};

#endif // _SequenceInputStream_h_
