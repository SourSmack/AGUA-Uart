#pragma once 
#include <etl/string.h>
#include "driver/uart.h"

#include "FreeRTOSWrapper.hpp"

enum {
    UartSync 
};
#define message_buffor_size 64 

template < class  Mode > 
class Uart{
public:

    template< class T = etl::string<message_buffor_size>*  > 
    int send( T  arg    ) {
        return static_cast<Mode*>( this )->send( arg ) ;
    } 
    int recieve( ... ) ; 


};

template< 
    class transferData , 
   class DestinationAvailable  = nullptr , 
   class SourceAvailable  = nullptr,  
   std::enable_if_t<std::is_invocable_v< transferData , Arg>, int> = 0
       >
class Courier{
private;
    Mission task ;
    static void transfer(){
        while ( !Mission::waitForNotify( Mission::event.stop , 0 )){

            if ( Mission::waitForNotify( Mission::event.pause , 0  ){
                while ( !Mission::waitForNotify( Mission::event.resume , Mission::MAX_DELAY )){}
            }
            // if nullptr delete code 
            while ( SourceAvailable != nullptr &&   ! SourceAvaiable){ Mission::notify( sourceExhaustion ); Mission::waitForNotify( Mission::event.resume , Mission::MAX_DELAY) } 

            while ( DestinationAvailable != nullptr &&  ! DestinationAvaiable){ Mission::notify( destinationExhaustion ); Mission::waitForNotify( Mission::event.resume , Mission::MAX_DELAY) } 
            // if nullptr delete code 

            transferData() ;


        }
    }

public:
    bool pauseTransfer();
    bool stopTransfer();
    bool resumeTransfer(); 
    uint32_t verifyStatus( uint32_t status = nullptr ){
        if (  status  ){
            return Mission::waitForNotify( status , 0 ) ; 
        }
        return Mission::checkOnFlags() ; 
    }

}; 


template< class T >
class EventQueue{
private:
    T *queuePtr { nullptr } ;
public:
    EventQueue( T *ptr){
        if ( ptr)  queuePtr = ptr ;
    }
    T* operator*(){ return queuePtr; } 
    bool recieve( void * event, uint32_t ticksToWait){
        if( xQueueReceive( queuePtr,   event, ticksToWait )  == pdPASS) return true ;
        return false ;
    }
};

template< 
    class T = QueueHandle_t , 
    class Message_t  
    >
class Sync_esp : Uart<SyncEsp> {
private:
    uart_config_t uartCfg ; 
    uart_port_t  uartNum ;  

    int rxPin  ;
    int txPin ;

    // Courier ;
    EventQueue<T> &queHandle ; 
    Mission &task ;
    
    uint16_t messageSize ;
    uint16_t answerBuffSize ;

    enum events : uin32_t {
        ANSWER_BUFF_FULL = 1 << 1 ,


    };

    etl::circular_buffer< Message_t, answerBuffSize> answerBuffer{}; 


    static void uart_task(void *arg){   
        auto self = *static_cast< Sync_esp* > arg ;

        int8_t messageTmp[64];
        uart_event_t  event;  
        
        

        while ( !Mission::waitForNotify( Mission::event.stop , 0 )){
            if ( Mission::waitForNotify( Mission::event.pause , 0  ){
                while ( !Mission::waitForNotify( Mission::event.resume , Mission::MAX_DELAY )){}
            }

            while ( !self.answerBuff.available() )  {
                Mission::notify( self.ANSWER_BUFF_FULL ) ;
                while( !Mission::waitForNotify( Mission::event.resume , Mission::MAX_DELAY){} 
            }

            if ( ! self.queHandle.receive( &event, portMAX_DELAY ))
                continue;

            if ( event.type != UART_PATTERN_DET){
                uart_flush_input(uartNum);
                continue;
            }

            int pos = uart_pattern_pop_pos(uartNum);
            if (pos == -1)
                continue ;
            
            if (pos >= sizeof(messageTmp)){
                uart_flush(uartNum);
                continue;
            }
            
            int readLen = uart_read_bytes(uartNum,  messageTmp,  pos + 1 ,  pdMS_TO_TICKS(100));
            messageTmp[readLen] = '\0';


            self.answerBuffer.push( Message_t{ (char*)messageTmp } ) ;

        }

    }

         
        
    

 
public:

    /*int send( void *arg  ) {

        uart_write_bytes( uartNum , arg , 


    }*/ 
    void check(){ ... } 

    bool recieve( Message_t * destination  ) {
        check() ;
        if( !destination) return false ; 
        if ( !answerBuffer.available() ) return false ;
        *destination  =  answerBuffer.front() ; 
        answerBuffer.pop() ;
        return true ; 
    }
};







