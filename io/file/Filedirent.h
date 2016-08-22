#ifndef _Filedirent_h_
#define _Filedirent_h_

// direct von java geklaut!
#ifdef WIN32
  #ifdef _AFX
    #include <afx.h>
  #endif
  #ifdef _COMMAND
    #include <windows.h>
  #endif

#include <direct.h> // For _getdrive() 
#include <errno.h>


/** structur fuer directoryeintraege. */
struct dirent {
  /** name des eintrags. */
  char d_name[MAX_PATH];
};

/** streamstructur fuer directories.
 */
typedef struct {
  
  /** dirent, dass bei readdir geliefert wird. */
  struct dirent dirent;
  
  /** pfad des files. */
  char *path; 
  
  /** windowshandle. */
  HANDLE handle;
  
  /** finddaten. */
  WIN32_FIND_DATA find_data;
	
} DIR;


/** Oeffnet eine DIR-struktur.
 *
 * @param dirName Name des verzeichnisses.
 *
 * @return DIR* 0 im Fehlerfall und ansonsten eine DIR-struktur.
 */
DIR *opendir(const char *dirName) {

  DIR *dirp = (DIR *)malloc(sizeof(DIR));
  unsigned long fattr;
  char alt_dirname[4] = { 0, 0, 0, 0 };

  if (dirp == 0) {
    errno = ENOMEM;
    return 0;
  }

  /*
   * Win32 accepts "\" in its POSIX stat(), but refuses to treat it
   * as a directory in FindFirstFile().  We detect this case here and
   * prepend the current drive name.
   */
  if (dirName[1] == '\0' && dirName[0] == '\\') {
	  alt_dirname[0] = _getdrive() + 'A' - 1;
	  alt_dirname[1] = ':';
	  alt_dirname[2] = '\\';
	  alt_dirname[3] = '\0';
	  dirName = alt_dirname;
  }

  dirp->path = (char *)malloc(strlen(dirName) + 5);
  if (dirp->path == 0) {
    free(dirp);
    errno = ENOMEM;
    return 0;
  }
  strcpy(dirp->path, dirName);

  fattr = GetFileAttributes(dirp->path);
  if (fattr == -1) {
    free(dirp->path);
    free(dirp);
    errno = ENOENT;
    return 0;
  } else if (fattr & FILE_ATTRIBUTE_DIRECTORY == 0) {
    free(dirp->path);
    free(dirp);
    errno = ENOTDIR;
    return 0;
  }

  /* Append "*.*", or possibly "\\*.*", to path */
  if ((dirp->path[1] == ':') && 
      ( (dirp->path[2] == '\0') || 
        ( (dirp->path[2] == '\\') && 
          (dirp->path[3] == '\0') ) ) ) {
    /* No '\\' needed for cases like "Z:" or "Z:\" */
    strcat(dirp->path, "*.*");
  } else {
    strcat(dirp->path, "\\*.*");
  }

  dirp->handle = FindFirstFile(dirp->path, &dirp->find_data);
  if (dirp->handle == INVALID_HANDLE_VALUE) {
    if (GetLastError() != ERROR_FILE_NOT_FOUND) {
      free(dirp->path);
      free(dirp);
      errno = EACCES;
      return 0;
    }
  }

  return dirp;

}

/** Liesst den naechsten direintrag ein.
 *
 * @param dirp von opendir geliefertes ergebnis.
 *
 * @return struct dirent structur.
 */
struct dirent *readdir(DIR *dirp) {
	
  if (dirp->handle == INVALID_HANDLE_VALUE) {
    return 0;
  }

  strcpy(dirp->dirent.d_name, dirp->find_data.cFileName);

  if (FindNextFile(dirp->handle, &dirp->find_data) == 0) {
	  if (GetLastError() == ERROR_INVALID_HANDLE) {
      errno = EBADF;
      return 0;
    }
    FindClose(dirp->handle);
    dirp->handle = INVALID_HANDLE_VALUE;
  }

  return(&(dirp->dirent));
}

/** Schliesst ein Directory.
 *
 * @param dirp von opendir geliefertes ergebnis.
 *
 * @return 0 im erfolgsfall
 */
int closedir(DIR *dirp) {
  if (dirp->handle != INVALID_HANDLE_VALUE) {
    if (FindClose(dirp->handle) == 0) {
      errno = EBADF;
      return -1;
    }
    dirp->handle = INVALID_HANDLE_VALUE;
  }
  free(dirp->path);
  free(dirp);
  return 0;
}

#endif // WIN32

#endif // _Filedirent_h_
