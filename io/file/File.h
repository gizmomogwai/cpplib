#ifndef _File_h_
#define _File_h_

#include <io/IoApi.h>

#include <stdio.h>
#include <string>
#include <util/ListIterator.h>
#include <util/Date.h>

#include <io/IOException.h>
#include <io/file/FileInputStream.h>
#include <io/file/FileOutputStream.h>

#include <io/file/FileList.h>

/** Klasse, die ein File kapselt.
 *
 * <h2>Linux</h2>
 * getSize funktioniert unter linux und win32 unterschiedlich ...
 * unter linux funktioniert File::getSize(..) und liefert 4096 und
 * unter win32 eine exception.
 *
 * Will man ein File ab einer bestimmten Position lesen, so biete
 * FileInputStream entsprechende Konstruktoren an um dort hinzuspringen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 *   <li> 2001-01-05, cK, list implemented.
 *   <li> 2001-01-05, cK, neuer constructor hinzugefuegt.
 * </ul>
 *
 * @todo ueberlegen, ob man so krasse sachen wie das jdk machen 
 *       sollte mit relativen, absoluten etc pfadnamen
 *
 * @version $Revision: 1.6 $, $Date: 2001/09/13 13:11:10 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API File {

 public:
	/** Erzeugt ein neues File.
	 *
	 * @param _pathName pfad zum file mit filenamen
	 */
        File(std::string _pathName);
  
        
	/** Copy-constructor.
	 *
	 * @param f File.
	 */
        File(File* f);
        File(const File& f);

	/** Erzeugt ein neues File aus einem Basisfile und einem Kind.
	 *
	 * @param base Basis.
	 * @param std::string childName
	 */
	File(File* base, std::string childName);
    
	/** Raeumt auf. */
	virtual ~File() {
	}

  /** Liefert zu einem File das Verzeichnis in dem das File steht.
   *
   * @return File* neues File.
   */
  File* getParent();

	/** Liefert eine Stringrepraesentation des Files.
	 *
	 * @return std::string stringrepraesentation.
	 */ 
	std::string toString() {
		return getPathName();
	}

	/** Liefert die Filegroesse. 
	 *
	 * @return long Filegroesse.
	 */
	virtual long getSize() throw (IOException);
    
	/** Loescht eine Datei.
	 *
	 * @exception IOException, falls etwas nicht geklappt hat.
	 */
	virtual void remove() throw (IOException);
    
	/** Benennt this in target um.
	 *
	 * @param target Zielfilename.
	 * 
	 * @exception IOException, falls etwas nicht klappt.
	 */
	virtual void rename(File* target) throw (IOException);

	/** Kopiert this in target.
	 *
	 * @param target Zielfile.
	 *
	 * @exception IOException wenn etwas nicht klappt.
	 */
	virtual void copy(File* target) throw (IOException);

	/** Liefert den Pfadnamen.
	 *
	 * @return std::string pfadname.
	 */
	virtual std::string getPathName() const {
		return pathName;
	}
    
	/** Dumme exists implementierung.
	 *
	 * @return bool true falls das file als solches existiert.
	 */
	virtual bool exists();

	//    virtual bool isFile();
    
	/** Testet, ob das File ein Verzeichnis ist.
	 *
	 * @return bool true falls das file ein Verzeichnis ist.
	 */
	virtual bool isDirectory() const;

	/**
	 * Erzeugt ein Verzeichnis.
	 * Momentan werden die parents nicht recursiv erzeugt.
	 * @return bool konnte das verzeichnis angelegt werden.
	 */
	virtual bool mkdir();
    
	/** Liefert alle File in dem Verzeichnis.
	 *
	 * @return FileList* Liefert eine Liste von File zurueck. Diese muss von
	 *         der Applikation aufgeraeumt werden.
	 */
	FileList* list();
	
	/**
	 * Liefert den reinen Filenamen (z.b. /test/wasgeht.txt -> wasgeht.txt)
	 * @return std::string filename or ""
	 */
	std::string getFileName();
	
	/**
	 * Liefert das last modified datum.
	 * @return Date* bitte deleten.
	 */
	Date* getModificationDate();
	
	/**
	 * Liefert das last accessed datum.
	 * @return Date* bitte deleten.
	 */
	Date* getLastAccessDate();
	
	/**
	 * setzt die datums eines files.
	 *
	 * @param accessDate neues accessdate darf auch 0 sein (dann wird das datum nicht geaendert).
	 * @param modificationDate neues modification date darf auch 0 sein (dann wird das datum nicht geaendert).
	 */
	void setDates(Date* accessDate, Date* modificationDate);
  
  static File getCwd();
    
 private:
	/** Pfadname des files. */
	std::string pathName;    

	/** Hackt von hinten Teile des Pfades ab.
	 *
	 * @param s Anzahl von Slashes die abgehackt werden sollen.
	 */
  std::string chopSlashes(unsigned int s);

	/** Beendet dirs immer mit Slash am Ende. */
  void unifyName();
    
};

#endif // _File_h_

