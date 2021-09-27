#pragma once

#include <lang/Mutex.h>
#include <util/RefCountedObject.h>

/** Hilfs-Objekt um Aenderungen zu cachen und in einem Updatedurchgang zu
 * setzen.
 *
 * Templateklasse.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-27, cK, Created.
 *   <li> 2001-07-05, cK, ruecklieferung-bei-update-todo entfernt.
 * </ul>
 *
 * @todo Ueberlegen, wie man das mit den std. stl-listen machen kann???!!!
 *       oder sollte man die jetzt endgueltig wrappen???? momentan ist die
 *       loesung ueber von std::list abgeleitete klassen (z.b. group)
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:50 $
 *
 * @author cK, $Author: gizmo $
 */
template <class T> class UpdateObject {

 public:
  /** Erzeugt ein neues UpdateObject, dass keine Objekte eingetragen
   * hat.
   */
  UpdateObject() : m(new Mutex()) {
    AutoMutex lock(m);
    current = 0;
    newOne = 0;
  }

  /** Raeumt auf. */
  ~UpdateObject() {
    m->lock();
    if (newOne != 0) {
      newOne->releaseReference();
      newOne = 0;
    }

    if (current != 0) {
      current->releaseReference();
      current = 0;
    }
    m->unlock();
    delete m;
  }

  /** Teste ob UpdateObject veraendert wurde.
   *
   * @return bool Wurde das Objekt veraendert.
   */
  bool hasChanged() {
    AutoMutex lock(m);

    bool res = (newOne != 0);
    return res;
  }

  /** Untersucht, ob eine Aenderung vorliegt und nimmt diese Aenderung
   * evtl. vor.
   *
   * @return bool true falls eine Aenderung vorgenommen wurde.
   */
  bool hasChangedAndUpdate() {
    AutoMutex lock(m);

    bool res = hasChanged();
    if (res == true) {
      update();
    }
    return res;
  }

  /** Liefert das aktuelle Objekt.
   *
   * @return T* Objekt.
   */
  T* get() {
    AutoMutex lock(m);
    if (current != 0) {
      current->addReference();
    }
    return current;
  }

  /** Liefert das neue Object zurueck.
   *
   * @return T* Neues Object. evtl. auch 0
   */
  T* getNew() {
    AutoMutex lock(m);

    if (newOne != 0) {
      newOne->addReference();
    }
    return newOne;
  }

  /** Setzt das neue Objekt.
   *
   * @param _newOne Neues Objekt.
   */
  void set(T* _newOne) {
    AutoMutex lock(m);

    if (_newOne != newOne) {
      if (_newOne != 0) {
        _newOne->addReference();
      }

      if (newOne != 0) {
        newOne->releaseReference();
      }

      newOne = _newOne;
    }
  }

  /** Updates das Objekt (das aktuell Objekt wird aufgeraeumt, falls
   * vorhanden), das aktuelle wird auf das neue gesetzt, das neue wird auf
   * leer gesetzt.
   */
  void update() {
    AutoMutex lock(m);

    if (hasChanged() == false) {
      return;
    }

    if ((current != 0) && (current != newOne)) {
      current->releaseReference();
      current = 0;
    }

    current = newOne;

    newOne = 0;
  }

  /** Lock um gets, updates, und sets zu synchen. */
  Mutex* m;

 private:
  /** Aktuelles Objekt. */
  T* current;

  /** Neues Objekt. */
  T* newOne;

};
