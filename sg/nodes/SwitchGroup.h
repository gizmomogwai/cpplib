#ifndef SwitchGroup_h_
#define SwitchGroup_h_

#include <sg/nodes/Group.h>

class SwitchGroup : public Group {

	public:
		SwitchGroup();
		virtual ~SwitchGroup() {
		}
		
    void accept(Visitor* v);
		
		int getSwitchedIndex();
		
		void setSwitchedIndex(int index);
		
	  virtual std::string toString() {
	    return "SwitchGroup";
	  }
	private:
		int fSwitchedIndex;
};


#endif // SwitchGroup_h_
