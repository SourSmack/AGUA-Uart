#include <utility>



template < class  Mode > 
class Uart{
public:

    template<typename... Args>
    bool receive(Args&&... args) {
        return static_cast<Mode*>(this)->receive(std::forward<Args>(args)...);
    }



};
