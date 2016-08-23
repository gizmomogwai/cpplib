#ifndef _FileInputStream_h_
#define _FileInputStream_h_

#include <io/IOException.h>

#include <io/InputStream.h>

#include <stdio.h>

class File;

/** Einfacher Adapter um std-c-files zu kapseln.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-05-14, cK, Created.
 *   <li> 2000-11-20, cK, Commented, an c-files angepasst.
 * </ul>
 *
 * @author cK, $Author: koestlin $
 *
 * @version $Revision: 1.2 $, $Date: 2001/05/31 15:19:22 $
 */
class FileInputStream : public InputStream {
  
 public:
  
  /** Oeffnet einen Inputstream auf dem filenamen.
   *
   * @param fileName Name des zu oeffnenden files.
	 *
	 * @exception IOException wenn etwas schiefgeht.
   */
  FileInputStream(const char* fileName, const int offst=0) throw (IOException);

  /** Erzeugt einen FileInputStream anhand eines Filenamenstrings.
   *
   * @param fileName Filename.
   * @param offset Offset vom Fileanfang
   */
  FileInputStream(std::string fileName, const int offset=0) throw (IOException);
  
  /** Oeffnet einen InputStream auf dem File.
   *
   * @param f File.
   * @param offset Offset vom Anfang des Files.
	 *
	 * @exception IOException wenn etwas schiefgeht.
   */
  FileInputStream(File* f, const int offset=0) throw (IOException);
  
	/** Oeffnet einen InputStream auf einem stdio-FILE-descriptor.
	 *
	 * @param stdioFILEin std-filedescriptor.
	 *
	 * @exception IOException wenn etwas schiefgeht.
	 */
  FileInputStream(FILE* stdioFILEin) throw (IOException);

  /** Schliesst den strom und das zugrundeliegende file.
   */
  ~FileInputStream();
  
  int read() throw (IOException);
  
  int read(DataBuffer& b, int offset, int length) throw (IOException);
  
 private:
  /** Initialisiert das FILE-Handle. 
   *
   * @param fileName Name des files.
   * @param offset Offset vom FileAnfang.
   *
   * @exception IOException wenn etwas schiefgeht.
   */
  void init(const char* fileName, int offset) throw (IOException);
  
  /** Soll das File am ende geschlossen werden. */
  bool pleaseClose;
  
  /** Zugrundeliegendes c-file. */
  FILE* in;
  
};

#endif // _FileInputStream_h_
