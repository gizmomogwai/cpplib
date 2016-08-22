#ifndef _FrameRateVisitor_h_
#define _FrameRateVisitor_h_

#include <iostream>
#include <sstream>
#include <lang/HPStopWatch.h>
#include <sg/visitors/Visitor.h>
#include <util/ListIterator.h>


/** Berechnet einen durchschnitt.
 *
 * Es kann angegeben werden wie schnell der neue Wert zum 
 * durchschnitt beitraegt.
 *
 * M = M - M/n + f/n
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-06-27, cK, Created.
 *   <li> 2001-07-05, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/07/05 13:27:23 $
 *
 * @author cK, $Author: koestlin $
 */
class AverageCalculator {


  public:
    /** Erzeugt den Calculator mit der Kennzahl. 
     *
     * @param n Wie stark sollen neue Werte in den Durchschnitt eingehen.
     */
    AverageCalculator(int _n) : n(_n), average(0) {
    }

    /** Raeumt auf. */
    virtual ~AverageCalculator() {
    }

    /** Naechster Wert.
     *
     * @param f Neuer wert.
     */
    void nextValue(float f) {
      average = (average - average/n) + f / n;
    }

    /** Liefert Stringrep. */
    std::string toString() {
      std::ostringstream help;
      help << "AverageCalculator (" << n << "): " << average << std::ends;
      std::string res(help.str());
      return(res);
    }


  private:

    /** Kennwert (siehe oben). */
    int n;

    /** Berechneter Durchschnittswert. */
    float average;

};

/** Visitor um Framertaten zu messen. 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-06-27, cK, Created.
 *   <li> 2001-07-05, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.3 $ $Date: 2001/07/05 13:27:23 $
 *
 * @author cK, $Author: koestlin $
 */
class FrameRateVisitor : public Visitor {

  public:
    /** Erzeugt einen neuen Visitor. 
     */
    FrameRateVisitor() : count(0), printFrequency(50) {  
      averages.push_back(new AverageCalculator(1));
      averages.push_back(new AverageCalculator(50));
      averages.push_back(new AverageCalculator(500));
      stopper.start();
    }

    /** Raeumt auf. */
    virtual ~FrameRateVisitor() {
      ListIterator<AverageCalculator*> i(&averages);
      while (i.hasNext() == true) {
        delete(i.next());
      }
    }

    /** Proforma. wird eignetlich nur benoetigt, um zu erkennen wenn
     * eine Szene besucht wird.
     *
     * @param root Rootknoten.
     */
    void visit(Root* root) {
      stopper.stop();
      ListIterator<AverageCalculator*> i(&averages);
      while (i.hasNext() == true) {
        i.next()->nextValue(1000.0f / stopper.getDelta());
      }
      count++;
      if (count >= printFrequency) {
        count = 0;
        printAverages();
      }
      stopper.start();
    }

  private:

    /** Gibt alle Durschnitte aus. */
    void printAverages() {
      ListIterator<AverageCalculator*> i(&averages);
      while (i.hasNext() == true) {
        std::cout << i.next()->toString() << std::endl;
      }
    }

    /** Stopuhr fuer den letzen Frame. */
    HPStopWatch stopper;

    /** Menge von Durchschnittsberechnern. */
    std::list<AverageCalculator*> averages;

    /** aktueller zaehler. */
    int count;
    
    /** Wie oft sollen die Durchschnitte auf stdout ausgegeben werden. */
    int printFrequency;
};

#endif // _FrameRateVisitor_h_
