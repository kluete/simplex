// zama dag challenge

#include <cstdio>
#include <iostream>

#include <thread>
#include <memory>   // unique_ptr


#include "simplx.h"

using namespace std;
using namespace tredzone;

using namespace std;
using T = char;

// 3rd party library function
// T is a type defined in that library
inline
T* acquire_resource(void)
{
    static
    char    dummy = 0;
    
    return &dummy;
}

/*
template <class T>
using owning_pointer = T*;

// wrt to the above I recomend explicit method forwarding through function (even though there may be many) over a blanket pass-thru template
*/

//---- T owner/custodian -------------------------------------------------------

template <class T>
class owner
{
public:
    // ctor
    owner(T *t)
        : m_Owned(t)
    {
    }
    
    ~owner()
    {   // has been manually released?
        assert(!m_Owned.get());
        
        // nothing to do here
    }
    
    void    Destroy(void)
    {
        // mwasn't already released?
        assert(m_Owned.get());

        // m_Owned->release();
        
        m_Owned.reset();
    }
        
private:
    
    unique_ptr<T>   m_Owned;
};

using owned_data = owner<T>;

//---- output interface --------------------------------------------------------

class IThreadOutput
{
public:

    IThreadOutput()
    {
    }

private:

};
    
//---- dummy data op -----------------------------------------------------------

void do_op(const owned_data &data_in, IThreadOutput &iout)
{
    // nop
    (void)data_in;
    (void)iout;
}

//---- MAIN --------------------------------------------------------------------

int main(int argc, char **argv)
{
    owned_data      data_in(acquire_resource());
    IThreadOutput   data_out;

    vector<thread>  workers = vector<thread>();

    // create a couple worker threads
    for (int i = 0; i < 2; i++)
    {
        //workers.emplace_back({do_op, data_in, data_out});
        workers.emplace_back(thread{do_op, data_in, data_out});
    };

    for (auto &w : workers)
    {
        w.join();
    }

    return 0; 
}
