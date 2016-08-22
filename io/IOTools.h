#ifndef _IOTools_h_
#define _IOTools_h_

#include <io/IoApi.h>

#include <iostream>
#include <io/InputStream.h>
#include <io/OutputStream.h>
#include <lang/ByteDataBuffer.h>

#include <lang/HPStopWatch.h>

/** Einfache Operationen auf Input und Outputstreams.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/09/13 13:11:10 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API IOTools {

 public:
	/** Kopiert alle Daten von in nach out.
	 *
	 * Der ganze Strom wird kopiert (solange bis read -1 liefert).
	 *
	 * @param in Datenquelle.
	 * @param out Datensenke.
	 * @param bufferSize Groesse des verwendeten Puffers.
	 *
	 * @exception Exception falls was beim kopieren nicht klappt.
	 */
	static void copy(InputStream* in, OutputStream* out, int bufferSize)
		throw (IOException) {
		ByteDataBuffer buffer(bufferSize);
		int red = in->read(buffer);
		while (red != -1) {
			out->write(&buffer, 0, red);
			red = in->read(buffer);
		}
	}

	/** Kopiert eine gewisse Datenmenge von in nacht out.
	 *
	 * Es werden momentan noch testweise stopuhren an den start gebracht.
	 *
	 * @param in Datenquelle.
	 * @param out Datensenke.
	 * @param numBytes Anzahl zu kopierender Byte.
	 * @param bufferSize Groesse des zu verwendenden Puffers.
	 *
	 * @exception Exception falls was nicht klappt.
	 */
	static void copy(InputStream* in, OutputStream* out, 
										long numBytes, int bufferSize) 
		throw (IOException) {

		std::cout << "IOTools.copy" << std::endl;
		HPStopWatch reader;
		HPStopWatch writer;
		HPStopWatch totalTime;
		totalTime.start();
      
		double allRead = 0;
		double allWrite = 0;
		ByteDataBuffer buffer(bufferSize);
		reader.start();
		int red = in->read(buffer);
		reader.stop();
		allRead += reader.getDelta();

		long alltogether = 0;
		while (red != -1) {
			writer.start();
			out->write(&buffer, 0, red);
			writer.stop();
			allWrite += writer.getDelta();
			alltogether += red;
			red = -1;
			if (alltogether < numBytes) {
				reader.start();
				red = in->read(buffer);
				reader.stop();
				allRead += reader.getDelta();
			}
		}

		std::cout << "writer: " << allWrite << std::endl
							<< "reader: " << allRead << std::endl;
		totalTime.stop();
		std::cout << "speed: " << (alltogether / totalTime.getDelta() * 1000)
							<< std::endl; 
	}
      
};

#endif // _IOTools_h_
