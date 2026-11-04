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

class Sync_esp : Uart<SyncEsp> {
private:
    pc_uart_config_t uartCfg ; 
    uart_port_t  uartNum ;  
    int buffsize ; 
    int rxPin  ;
    int txPin ;
    int queSize ;
    QueueHandle_t queHandle { nullptr }; 

    FREETask task{  nullptr } ;

    static void uart_task(void *arg)
    {   
        auto instance = *static_cast< Camera* > arg ;

        int8_t dtmp[64];
        uart_event_t  event;  
        
        

        while ( !FREETask::waitForNotify( FREETask::stopBit , 0 )) 
        {
            while ( FREETask::waitForNotify( FREETask::pauseBit , FREETask::MAX_DELAY )){}

            if ( ! xQueueReceive( queHandle,   &event, portMAX_DELAY ))
                continue;

            if ( event.type != UART_PATTERN_DET){
                uart_flush_input(uartNum);
                continue;
            }

            int pos = uart_pattern_pop_pos(uartNum);
            if (pos == -1)
                continue ;
            
            if (pos >= sizeof(dtmp)){
                uart_flush(uartNum);
                continue;
            }
            
            int readLen = uart_read_bytes(uartNum,  dtmp,  pos + 1 ,  pdMS_TO_TICKS(100));
            dtmp[readLen] = '\0';

            etl::string<32> tmpString{(char*)dtmp};
            last_word = tmpString ;

            eventGroup.setBits( colorSensorBit  );
        }

         
        
    }

 
public:

    int send( etl::string<message_buffor_size> *arg  ) {

        uart_write_bytes( uartNum , arg , 


    } 
    int recieve( ... ) ; 
};







