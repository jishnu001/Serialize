

#ifndef SERIALIZE_H

#define SERIALIZE_H

#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <utility>

class Serialize{


public:
    template<typename T, typename A>
    static void serializeVector(std::vector<T,A>& vec, char* buffer)
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

  template <class key, class value>
  std::string serializeMap(const std::map<key, value>& v){
    std::stringstream ss;
    std::for_each(v.begin(), v.end(), [&ss](const std::pair<key, value>& s){
            ss.write ((char*)&s, sizeof(std::pair<key,value>));
        });
    return ss.str();
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
	
	
    template <class key, class value>
    void deSerializeMap(const std::string& s, std::map<key, value>& v){
    
	    std::stringstream ss1;

	    ss1<<s;

	    int pos = 0;

	    while(ss1){
		char* ar = new char[sizeof(std::pair<key, value>)];
		ss1.read(ar,(sizeof(std::pair<key, value>)));
		v.insert(*(reinterpret_cast<std::pair<key, value>*>(ar)));
		pos+=sizeof(std::pair<key, value>);
		ss1.seekg(pos);
		delete[] ar;
	    }
    
    }
    
};



#endif
