#ifndef _Behavior_h_
#define _Behavior_h_

#include <lang/Exception.h>

#include <sg/nodes/Leaf.h>

#include <sg/conditions/WakeupCondition.h>

#include <sg/visitors/Visitor.h>

/** Oberklasse aller Behaviors.
 *
 * Ein Behavior kann irgendwo in den Graphen gehaengt werden,
 * koennte gecullt werden (man weiss aber die semantik davon
 * noch nicht genau).
 * Ein Behavior hat eine statisches Condition-Object (das nicht
 * geaendert werden kann), das jedes Frame ausgewertet werden
 * muss. Das Ergebnis dieser Berechnung stoesst die Ausfuehrung
 * des Behaviors an.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-16, cKgS, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author gScK, $Author: koestlin $
 */
class Behavior : public Leaf {

  public:
    /** Erzeugt ein neues Behavior.
     *
     * @param c Condition, die in den Besitz des Behaviors uebergeht.
     */
    Behavior(WakeupCondition* c);

    /** Erzeugt ein neues Behavior ohne Condition.
     *
     * Die Condition kann mit der protecteden Methode setCondition
     * gesetzt werden, wenn man sich darueber klar ist was man macht.
     */
    Behavior();

    /** Raeumt auf. */
    virtual ~Behavior();

    void accept(Visitor* v) {
      v->visit(this);
    }

    /** Methode, die die eigentliche Aufgabe, bei
     * wohlwollender Condition ausfuehrt.
     */
    virtual void processStimulus() = 0;

    /** Condition, die das Behavior steuert (eigentlich
     * private aber fuer die Visitoren public).
     */
    WakeupCondition* condition;

  protected:

    /** Setzt die Condition des Behaviors.
     *
     * @param c Condition, die in den Besitz des Behaviors uebergeht.
     *
     * @exception Exception, falls die Condition schon gesetzt wurde.
     */
    void setCondition(WakeupCondition* c) throw (Exception);

};

#endif // _Behavior_h_
