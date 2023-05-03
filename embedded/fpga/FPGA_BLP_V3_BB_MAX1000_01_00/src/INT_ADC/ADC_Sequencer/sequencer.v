module sequencer ( 
	Clock_qsys,
	Reset,
   AdcCsrAddress,            //Address to CSR for ADC for setup
   AdcCsrReadEn,             //Read enable for CSR for ADC for setup
   AdcCsrReadData,           //Read data for CSR for ADC for setup
   AdcCsrWriteEn,         //Write enable for CSR for ADC for setup
  	AdcCsrWriteData          //Write data for CSR for ADC for setup
  );
  
  
  input           			Clock_qsys;  
	input           			Reset;                    //Synchronous Reset  
	output reg              AdcCsrAddress;            //Address to CSR for ADC for setup
	output reg              AdcCsrReadEn;             //Read enable for CSR for ADC for setup
	output reg      [31: 0] AdcCsrReadData;           //Read data for CSR for ADC for setup
	output reg              AdcCsrWriteEn;            //Write enable for CSR for ADC for setup
	output reg      [31: 0] AdcCsrWriteData;          //Write data for CSR for ADC for setup
	

    //State Machine to setup the ADC module
  parameter [2:0]
    RESET              =  0,
    DELAY0               =  1,
    DELAY1               =  2,
    DELAY2               =  3,
    DELAY3               =  4,
    DELAY4               =  5,
    WRITE              =  6,
    DONE               =  7;
    
  reg [2:0] CurrentState, NextState;
  
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      CurrentState <= RESET;
    else
      CurrentState <= NextState;
  end
  
  //Next state logic
  always @(CurrentState)
  begin
    case(CurrentState)
      RESET :
        //As soon as we are out of reset start to write
//        NextState <= WRITE;
		  NextState <= DELAY0;

         
      DELAY0 :
        //Go through delay chain to let ADC module finish reset
        NextState <= DELAY1;
        
      DELAY1 :
        //Go through delay chain to let ADC module finish reset
        NextState <= DELAY2;
        
      DELAY2 :
        //Go through delay chain to let ADC module finish reset
        NextState <= DELAY3;
        
      DELAY3 :
        //Go through delay chain to let ADC module finish reset
        NextState <= DELAY4;
        
      DELAY4 :
        //Go through delay chain to let ADC module finish reset
        NextState <= WRITE;
        
      WRITE :
        //Write enable bit and finish
        NextState <= DONE;
        
      DONE :
        //Just stay here for all time
        NextState <= DONE;
        
      default
        begin
          NextState <= RESET;
        end
    endcase
  end
  
  //Decode state for control signals
  always @(CurrentState)
  begin
    //Default to not asserted
    AdcCsrAddress     <= 1'b0;
    AdcCsrReadEn      <= 1'b0;
    AdcCsrReadData    <= 32'b0;
    AdcCsrWriteEn     <= 1'b0;
    AdcCsrWriteData   <= 32'b0;
    
    case (CurrentState)
      RESET :
        begin
          //Defaults are fine
        end
        
      DELAY0 :
        begin
          //Defaults are fine
        end
        
      DELAY1 :
        begin
          //Defaults are fine
        end
        
      DELAY2 :
        begin
          //Defaults are fine
        end
        
      DELAY3 :
        begin
          //Defaults are fine
        end
        
      DELAY4 :
        begin
          //Defaults are fine
        end
        
      WRITE :
        begin
          AdcCsrWriteEn         <= 1'b1;                      //Write data to CSR
          AdcCsrWriteData       <= 32'h00000001;              //Enable continuous run mode
        end

      DONE :
        begin
          //Defaults are fine
        end
        
    endcase
  end
  
  endmodule