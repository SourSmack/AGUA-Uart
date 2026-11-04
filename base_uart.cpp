



template < class  Mode > 
class Uart{
public:

    template< class T = etl::string<message_buffor_size>*  > 
    int send( T  arg    ) {
        return static_cast<Mode*>( this )->send( arg ) ;
    } 
    int recieve( ... ) ; 


};
