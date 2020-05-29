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
*/

template <class T>
class T_wrapper
{
public:
    // ctor
    T_wrapper(T&& t)
        : m_Owned(std::move(t))
    {
            
    }
    
    ~T_wrapper()
    {
        
    }
    
    void    Destroy(void)
    {
        // delete m_Owned
    }
        
private:
    
    unique_ptr<T>   m_Owned;
};

void do_op(T* data)
{
    (void)data;
}

int main(int argc, char **argv)
{
    T* data = acquire_resource();

    auto workers = vector<thread>();

    // create a couple worker threads
    for (int i = 0; i < 2; i++)
    {
        workers.emplace_back(do_op, data);
    };

    for (auto &w : workers)
    {
        w.join();
    }

    return 0; 
}
/*
{
	cout << "hello world" << endl;
    
	return 0;
}
*/