/* -*-c++-*-
 *  ----------------------------------------------------------------------------
 *
 *       PlantGL: The Plant Graphic Library
 *
 *       Copyright CIRAD/INRIA/INRA
 *
 *       File author(s): F. Boudon (frederic.boudon@cirad.fr) et al. 
 *
 *  ----------------------------------------------------------------------------
 *
 *   This software is governed by the CeCILL-C license under French law and
 *   abiding by the rules of distribution of free software.  You can  use, 
 *   modify and/ or redistribute the software under the terms of the CeCILL-C
 *   license as circulated by CEA, CNRS and INRIA at the following URL
 *   "http://www.cecill.info". 
 *
 *   As a counterpart to the access to the source code and  rights to copy,
 *   modify and redistribute granted by the license, users are provided only
 *   with a limited warranty  and the software's author,  the holder of the
 *   economic rights,  and the successive licensors  have only  limited
 *   liability. 
 *       
 *   In this respect, the user's attention is drawn to the risks associated
 *   with loading,  using,  modifying and/or developing or reproducing the
 *   software by the user in light of its specific status of free software,
 *   that may mean  that it is complicated to manipulate,  and  that  also
 *   therefore means  that it is reserved for developers  and  experienced
 *   professionals having in-depth computer knowledge. Users are therefore
 *   encouraged to load and test the software's suitability as regards their
 *   requirements in conditions enabling the security of their systems and/or 
 *   data to be ensured and,  more generally, to use and operate it in the 
 *   same conditions as regards security. 
 *
 *   The fact that you are presently reading this means that you have had
 *   knowledge of the CeCILL-C license and that you accept its terms.
 *
 *  ----------------------------------------------------------------------------
 */



#ifndef __threaded_data_h__
#define __threaded_data_h__

#include "../gui_config.h"
#include <QtGlobal>

#ifdef QT_THREAD_SUPPORT

#include <QtCore/qmutex.h>

template <class T>
class ThreadedData {

public:

  typedef T data_type;

  typedef QMutex Lock;
  typedef QMutexLocker ReadLocker;
  typedef QMutexLocker WriteLocker;

  ThreadedData(data_type * val):
      __val(val){
    }

  inline void deleteData()
  {
    WriteLocker l(&lock);
    if (__val != NULL) delete __val;
    __val = NULL;
  }

  inline ThreadedData operator = (data_type * val) {
    set(val);
    return *this;
  }

  inline void set(data_type * val) {
    ReadLocker l(&lock);
    __val = val;
  }

  inline operator const data_type * () { return getConst(); }

  inline data_type * get( ) {
    ReadLocker l(&lock);
    data_type * val = __val;
    return val;
  }

  inline const data_type * getConst( ) {
    ReadLocker l(&lock);
    data_type * val = __val;
    return val;
  }

private:
    ThreadedData(ThreadedData<T>& copy): __val(copy.get()){};
    ThreadedData<T>& operator=(ThreadedData<T>& copy){ WriteLocker l(&lock); __val = copy.get(); }

  data_type * __val;
  Lock lock;

};

#endif

#endif

