#ifndef _FileOutputStream_h_
#define _FileOutputStream_h_

#include <string>

#include <stdio.h>

#include <io/IOException.h>
#include <io/OutputStream.h>

class File;

/** Einfacher Adapter um c-files an outputstreams anzupassen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-05-14, cK, Created.
 *   <li> 2000-11-19, cK, Commented, auf c-files angepasst.
 *   <li> 2001-04-27, cK, Append eingebaut.
 * </ul>
 *
 * @author cK, $Author: koestlin $
 *
 * @version $Revision: 1.2 $, $Date: 2001/09/13 13:11:10 $
 */
class FileOutputStream : public OutputStream {

 public:
  /** Erzeugt einen neuen FileOutputStream.
   *
   * @param fileName Filename.
   * @param append soll angehaengt werden.
	 *
	 * @exception IOException wenn was schief geht.
   */
  FileOutputStream(const char* fileName, bool append=false) throw (IOException);

  /** Erzeugt einen neuen FileOutputStream.
   *
   * @param fileName Filename.
   * @param append soll angehaengt werden.
   *
   * @exception IOException wenn was schief geht.
   */
  FileOutputStream(const std::string fileName, bool append=false) throw (IOException);
  
  /** Erzeugt einen neuen FileOutputStream aus einem File.
   *
   * @param f File.
   * @param append soll angehaengt werden.
	 *
	 * @exception IOException wenn etwas nicht klappt (readonly).
   */
  FileOutputStream(File *f, bool append=false) throw (IOException);
  
  /** Schliesst den Ausgabestrom. 
	 *
	 * @exception IOException wenn etwas nicht klappt.
	 */
  ~FileOutputStream() throw (IOException);
  
  void write(int b) throw (IOException);
  
  void write(DataBuffer* b, int offset, int length) 
		throw (IOException);

  void flush() throw (IOException);
  
 private:
  /** Initialisiert den FILE-Handle. 
	 *
	 * @param fileName Name des Files.
   * @param append soll angehaengt werden.
	 *
	 * @exception IOException wenn etwas nicht klappt.
	 */
  void init(const std::string fileName, bool append) throw (IOException);
  
  /** Ausgabefile. */
  FILE* out;

};

#endif // _FileOutputStream_h_
