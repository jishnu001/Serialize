

#ifndef SERIALIZE_H

#define SERIALIZE_H

#include <vector>

class Serialize{


public:
    template<typename T, typename A>
    static void Serialize(std::vector<T,A>& vec, char* buffer)
    {
        char* buf = new char[vec.size() * sizeof(T) + 1];
        buf[vec.size() * sizeof(T) ] = '\0';
        if(!vec.empty()){

#ifdef __linux__
            std::copy( reinterpret_cast<char *>(vec.data()),
                       reinterpret_cast<char *>(vec.data()) + vec.size()
		       * sizeof(T), buf);
#else
            std::copy(reinterpret_cast<char *>(vec.data()),
                      reinterpret_cast<char *>(vec.data()) + vec.size()* sizeof(T),
		      stdext::checked_array_iterator<char *>(buf,vec.size() * sizeof(T)));
#endif
        }

    }




    template<typename T, typename A>
    static void deSerializeVector(std::vector<T,A>& vec, const char* buf,
				      unsigned short count)
    {
        try {
            std::copy( reinterpret_cast<const char *>(buf),
		       reinterpret_cast<const char *>(buf) +
                       count * sizeof(T), reinterpret_cast<char *>(vec.data()) );
        }
        catch(...) {
            return;
        }
    }

    
};



#endif
