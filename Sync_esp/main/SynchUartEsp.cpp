#pragma once 
#include <etl/string.h>
#include <etl/circular_buffer.h>
#include "driver/uart.h"

#include "InlineOS/Mission.hpp"
#include "Courier.hpp"







template< 
    class Message_t  
    >
class Sync_esp : Uart<SyncEsp> {
private:
    uart_config_t uartCfg ; 
    uart_port_t  uartNum ;  
    int rxPin{ 0 }  ;
    int txPin{ 0 } ;
    Courier< Sync_esp > &answerCourier;
    uint16_t messageSize{ 0 } ;
    uint16_t answerBuffSize{ 0 } ;


    etl::circular_buffer< Message_t, answerBuffSize> answerBuffer{}; 

 
public:

    /*int send( void *arg  ) {

        uart_write_bytes( uartNum , arg , 
    }*/ 


    //void check(){ ... } 

    Sync_esp( uart_config_t p_uartCfg , 
              uart_port_t  p_uartNum ,   
              int p_rxPin  , int p_txPin , 
              Courier< Sync_esp > &p_answerCourier , 
              uint16_t p_messageSize , 
              uint16_t p_answerBuffSize )
        : uartCfg( p_uartCfg )  , 
          uartNum( p_uartNum )  ,  
          rxPin( p_rxPin )   ,
          txPin( p_txPin )  ,
          messageSize( p_messageSize )  ,
          answerBuffSize( p_answerBuffSize )  ,
          answerCourier( p_answerCourier ) 
        {}


    bool recieve( Message_t * destination  ) {
        check() ;
        if( !destination) return false ; 
        if ( !answerBuffer.available() ) return false ;
        *destination  =  answerBuffer.front() ; 
        answerBuffer.pop() ;
        return true ; 
    }
};







