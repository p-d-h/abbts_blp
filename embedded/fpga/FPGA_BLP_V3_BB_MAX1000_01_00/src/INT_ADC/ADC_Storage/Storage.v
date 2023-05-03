module storage (
	 Reset,
    Clock_qsys,
    AdcValue00,
    AdcValue01,
    AdcValue02,
    AdcValue03,
    AdcValue04,
    AdcValue05,
    AdcValue06,
    AdcValue07,
    AdcValue08,
    AdcFpgaTemp,
    AdcRefresh,
	 
	 AdcResponseValid,         //Indicates ADC data output is valid
	 AdcResponseChannel,       //Channel indicator for pairing data to
	 AdcResponseData          //Data value from ADC for indicated channel
	);

  input           	Reset;                    //Synchronous Reset
  input           	Clock_qsys;               //Qsys Clock 50Mhz
  output reg [11: 0] AdcValue00;               //Analog value for respective channel
  output reg [11: 0] AdcValue01;               //Analog value for respective channel
  output reg [11: 0] AdcValue02;               //Analog value for respective channel
  output reg [11: 0] AdcValue03;               //Analog value for respective channel
  output reg [11: 0] AdcValue04;               //Analog value for respective channel
  output reg [11: 0] AdcValue05;               //Analog value for respective channel
  output reg [11: 0] AdcValue06;               //Analog value for respective channel
  output reg [11: 0] AdcValue07;               //Analog value for respective channel
  output reg [11: 0] AdcValue08;               //Analog value for respective channel
  output reg [11: 0] AdcFpgaTemp;              //FPGA Temperature, direct internal sensor value
  output reg         AdcRefresh;               //New values are available

  input            AdcResponseValid;         //Indicates ADC data output is valid
  input   [ 4: 0] AdcResponseChannel;       //Channel indicator for pairing data to
  input   [11: 0] AdcResponseData;          //Data value from ADC for indicated channel



  //Register to store the ADC value when it is valid
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcValue00 <= 12'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd0))
      AdcValue00 <= AdcResponseData;
    else
      AdcValue00 <= AdcValue00;
  end
  
  //Register to store the ADC value when it is valid
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcValue01 <= 12'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd1))
      AdcValue01 <= AdcResponseData;
    else
      AdcValue01 <= AdcValue01;
  end
  
  //Register to store the ADC value when it is valid
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcValue02 <= 12'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd2))
      AdcValue02 <= AdcResponseData;
    else
      AdcValue02 <= AdcValue02;
  end
  
  //Register to store the ADC value when it is valid
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcValue03 <= 12'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd3))
      AdcValue03 <= AdcResponseData;
    else
      AdcValue03 <= AdcValue03;
  end
  
  //Register to store the ADC value when it is valid
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcValue04 <= 12'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd4))
      AdcValue04 <= AdcResponseData;
    else
      AdcValue04 <= AdcValue04;
  end

  //Register to store the ADC value when it is valid
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcValue05 <= 12'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd5))
      AdcValue05 <= AdcResponseData;
    else
      AdcValue05 <= AdcValue05;
  end
  
  //Register to store the ADC value when it is valid
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcValue06 <= 12'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd6))
      AdcValue06 <= AdcResponseData;
    else
      AdcValue06 <= AdcValue06;
  end
  
  //Register to store the ADC value when it is valid
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcValue07 <= 12'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd7))
      AdcValue07 <= AdcResponseData;
    else
      AdcValue07 <= AdcValue07;
  end
  
  //Register to store the ADC value when it is valid
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcValue08 <= 12'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd8))
      AdcValue08 <= AdcResponseData;
    else
      AdcValue08 <= AdcValue08;
  end
 

  
  //Register to store the ADC value when it is valid
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcFpgaTemp <= 12'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd17))
      AdcFpgaTemp <= AdcResponseData;
    else
      AdcFpgaTemp <= AdcFpgaTemp;
  end
    
  //When we do the final value update that they have all changed
  always @(posedge Clock_qsys)
  begin
    if(Reset)
      AdcRefresh <= 1'b0;
    else if(AdcResponseValid & (AdcResponseChannel == 5'd17))
      AdcRefresh <= 1'b1;
    else
      AdcRefresh <= 1'b0;
  end


















endmodule