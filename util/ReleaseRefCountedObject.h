#ifndef _ReleaseRefCountedObject_h_
#define _ReleaseRefCountedObject_h_

template <class T> class ReleaseRefCountedObject {
	public:
	  ReleaseRefCountedObject() : reference(0) {
	  }

    ReleaseRefCountedObject(T* _reference) : reference(_reference) {
    }
	  
		virtual ~ReleaseRefCountedObject() {
			if (reference != 0) {
				reference->releaseReference();
				reference = 0;	
			}	
		}
		
		void setReference(T* _reference) {
			reference = _reference;
		}
		
		T* operator*() const {
    	return reference;
		}		
	
		T* operator->() const {
			return reference;
		}


	private:
		T* reference;	
	
};


#endif // _ReleaseRefCountedObject_h_
