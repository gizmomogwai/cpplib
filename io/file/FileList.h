#ifndef FileList_h_
#define FileList_h_

#include <io/IoApi.h>

#include <vector>

class File;

/** Klasse, die eine Menge von Files speichert.
 *
 * Dies wird nur gebraucht, weil die Liste bei destruktion zerstoehrt
 * werden muessen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2001-01-05, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/07/05 13:27:23 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API FileList : public std::vector<File*> {

 public:
  /** Raeumt alle Referencen in der Liste auf. */
  virtual ~FileList();
  
  FileList* duplicate();
};

#endif // FileList_h_

