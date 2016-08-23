#ifndef _ZipArchive_h_
#define _ZipArchive_h_

#include <string>

class File;
class ZipCentralDirectory;
class InputStream;

/** Klasse um aus ZipArchiven zu lesen.
 *
 * <p>
 * Usage:
 * ZipArchive zip(File("test.zip"));
 * InputStream* in = zip.getStream("test.txt", 0);
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-13, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2001/07/16 09:58:52 $
 *
 * @author cK, $Author: koestlin $
 */
class ZipArchive {

  public:
    /** Bereitet ein ZipArchive mit dem File f vor.
     *
     * @param f Das File, das als Zip-Archive betrachtet werden soll. 
     *          f bleibt im Besitz des Callers.
     */
	  ZipArchive(File* f);

  	/** Raeumt auf. */
	  virtual ~ZipArchive();

    /** Liefert die Daten zu einem File in dem Zip-Archive.
     *
     * @param fileName Name des Files.
     * @param passwd Optionales Zip-Passwort, falls das File encrypted ist.
     *
     * @return InputStream* Datenstrom.
     */
	  InputStream* getStream(std::string fileName, std::string* passwd=0);

  private:
    /** Zip-File. */
	  File* file;

    /** Directory des Zip-Files. */
    ZipCentralDirectory* dir;

};

#endif // _ZipArchive_h_
