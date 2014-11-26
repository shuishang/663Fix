#include "Spi.h"

#define SPI_Simulation	   	0
#define SPI_ModeSet			SPI_Simulation		//SPI_ModeSet=SPI_Simulation为使用模拟SPI方式，
	 					  						//SPI_ModeSet=1为使用内部硬件SPI1方式，
												//SPI_ModeSet=2为使用内部硬件SPI2方式，

/**
 *	@brief  SPIx_NCS端口初始化
 *  @param  SPIx : where x can be 1, 2 or 3 to select the SPI peripheral
 *  @return None 
 */
void SPIx_NCS_Init(SPI_TypeDef* SPIx)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	if(SPI1 == SPIx)
	{
		RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	//PORTA时钟使能 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  				// PA4 推挽 
	 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  		//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置GPIO口速度
	 	GPIO_Init(GPIOA, &GPIO_InitStructure);

	 	GPIO_SetBits(GPIOA,GPIO_Pin_4);	   						//拉高SPI_NCS
	}
	else if(SPI2 == SPIx)
	{
		RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//PORTA时钟使能 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  			// PB12 推挽 
	 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  		//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置GPIO口速度
	 	GPIO_Init(GPIOB, &GPIO_InitStructure);

	 	GPIO_SetBits(GPIOB,GPIO_Pin_12);		  				//拉高SPI_NCS		
	}
	else 
	{
		;
	}

}
/**
 *	@brief  SPIx初始化
 *  @param  SPIx : where x can be 1, 2 or 3 to select the SPI peripheral
 *  @return None 
 */
SPI_InitTypeDef  SPI_InitStructure;
void SPIx_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;										    //定义GPIO结构体
  	if(SPI1 == SPI_ModeSet)
	{
		RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );	//使能GPIOA和SPI1时钟
	 												 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;			//使能SPI1_SCK、SPI1_MISO、SPI1_MOSI
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  							//复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//设置GPIO口速度
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);	  					//拉高SPI1_SCK、SPI1_MISO、SPI1_MOSI端口
	
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  		//设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;								//设置SPI工作模式:设置为主SPI
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;							//设置SPI的数据大小:SPI发送接收8位帧结构
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;									//选择了串行时钟的稳态:时钟悬空高
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;								//数据捕获于第二个时钟沿
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;									//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;							//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
		SPI_InitStructure.SPI_CRCPolynomial = 7;									//CRC值计算的多项式

		SPI_Init(SPI_ModeSet, &SPI_InitStructure);  	//根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	 
		SPI_Cmd(SPI_ModeSet, ENABLE); 					//使能SPI外设
	
		SPIx_NCS_Init(SPI_ModeSet);					//使能SPIx_NCS口
			
	//	SPIx_ReadWriteByte(SPIx,0xff);			//启动传输		
	 

	}
	else if(SPI2 == SPI_ModeSet)
	{
		RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );					//PORTB时钟使能 
		RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );					//SPI2时钟使能 	
	 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  						//PB13/14/15复用推挽输出 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);									//初始化GPIOB
	
	 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  				//PB13/14/15上拉
	
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  	//设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;							//设置SPI工作模式:设置为主SPI
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;						//设置SPI的数据大小:SPI发送接收8位帧结构
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;								//串行同步时钟的空闲状态为高电平
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;							//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;								//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;	//定义波特率预分频的值:波特率预分频值为256
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;						//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
		SPI_InitStructure.SPI_CRCPolynomial = 7;								//CRC值计算的多项式

		SPI_Init(SPI_ModeSet, &SPI_InitStructure);  	//根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	 
		SPI_Cmd(SPI_ModeSet, ENABLE); 					//使能SPI外设
	
		SPIx_NCS_Init(SPI_ModeSet);					//使能SPIx_NCS口
			
	//	SPIx_ReadWriteByte(SPIx,0xff);			//启动传输		
		 
 	
	}
	else if(SPI_Simulation==SPI_ModeSet)								//模拟SPI口方式
	{						    	
  		RCC_APB2PeriphClockCmd(SPI_GPIO_SCLK, ENABLE);					//模拟SPI口时钟使能
	
		GPIO_InitStructure.GPIO_Pin = SPI_NCS_GPIO_PIN;					// 设置模拟SPI的CS端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 		//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO口速度为50MHz
		GPIO_Init(SPI_NCS_GPIO, &GPIO_InitStructure);					//根据设定参数初始化
		GPIO_SetBits(SPI_NCS_GPIO,SPI_NCS_GPIO_PIN);									//

		GPIO_InitStructure.GPIO_Pin = SPI_SCLK_GPIO_PIN;				// 设置SPI的SCLK端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 		//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO口速度为50MHz
		GPIO_Init(SPI_SCLK_GPIO, &GPIO_InitStructure);					//根据设定参数初始化
		GPIO_SetBits(SPI_SCLK_GPIO,SPI_SCLK_GPIO_PIN);


		GPIO_InitStructure.GPIO_Pin = SPI_MOSI_GPIO_PIN;				// 设置SPI的MOSI端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 		//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO口速度为50MHz
		GPIO_Init(SPI_MOSI_GPIO, &GPIO_InitStructure);					//根据设定参数初始化.5
		GPIO_SetBits(SPI_MOSI_GPIO,SPI_MOSI_GPIO_PIN);

		GPIO_InitStructure.GPIO_Pin  = SPI_MISO_GPIO_PIN;				//设置SPI的MISO端口
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO口速度为50MHz
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 			//设置PA6口为输入浮空模式
		GPIO_Init(SPI_MISO_GPIO, &GPIO_InitStructure);					//根据设定参数初始化GPIOA
		GPIO_ResetBits(SPI_MISO_GPIO,SPI_MISO_GPIO_PIN);
	}
}   

/**
 *	@brief  SPI传送速度分频设置
 *  @param  SPIx : where x can be 1, 2 or 3 to select the SPI peripheral
 *  @param  data : SpeedSet=>	SPI_BaudRatePrescaler_2   2分频   (SPI 36M@sys 72M)
 *								SPI_BaudRatePrescaler_8   8分频   (SPI 9M@sys 72M)
 *								SPI_BaudRatePrescaler_16  16分频  (SPI 4.5M@sys 72M)
 *								SPI_BaudRatePrescaler_64  64分频      
 *								SPI_BaudRatePrescaler_128 128分频      
 *								SPI_BaudRatePrescaler_256 256分频 (SPI 281.25K@sys 72M)
 *  @return None 
 */  
void SPIx_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet)
{
	SPI_InitTypeDef  SPI_InitStructure;

	SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
  	SPI_Init(SPIx, &SPI_InitStructure);
	SPI_Cmd(SPIx,ENABLE);
} 

/**
 *	@brief  Sends one byte over SPI.//发送一个字节
 *  @param  SPIx : where x can be 1, 2 or 3 to select the SPI peripheral
 *  @param  data : data to send	(8 bit)
 *  @return None 
 */
void SPI_SendByte(SPI_TypeDef* SPIx, uint8_t data) 
{	
	/* Wait for SPIx Tx buffer empty */
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);

	/* Send byte through the SPIx peripheral */
	SPI_I2S_SendData(SPIx, data);
}

/**  
 *	@brief  Sends one byte over SPI and recovers a response.//发送一个字节后接收一个字节
 *  @param  SPIx : where x can be 1, 2 or 3 to select the SPI peripheral
 *  @param  data : data to send
 *  @return data response from SPIx 
 */
uint8_t SPI_SendReceiveByte(SPI_TypeDef* SPIx, uint8_t data) 
{	
	/* Wait for SPI1 Tx buffer empty */
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);

	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPIx, data);	

	/* Wait for SPI1 data reception	*/
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);

	/* Read & return SPI1 received data	*/
	return SPI_I2S_ReceiveData(SPIx);
}

/**
 *	@brief  Send a byte array over SPI.//发送一组数据后接收一组数据
 *  @param  SPIx	 	: where x can be 1, 2 or 3 to select the SPI peripheral
 *  @param  pCommand  	: pointer on the buffer to send
 *  @param  length	 	: length of the buffer to send
 *  @param  pResponse 	: pointer on the buffer response
 *  @return None 
 */
void SPI_SendReceiveBuffer(SPI_TypeDef* SPIx, uc8 *pCommand, uint16_t length, uint8_t *pResponse) 
{
	uint16_t i;

	for(i=0; i<length; i++)
	{
		pResponse[i] = SPI_SendReceiveByte(SPIx, pCommand[i]);
	}

}

//使用模拟SPI方式函数//
/*********************************************************/
//解释： 这是spi总线的读写时序，所有的寄存器操作基于此时序，非常重要
//		 无奇偶校验
//输入：要写入的16进制参数
//
//输出：内部传回的16进制参数
//
/********************************************************/
uint8_t SPI_Send(uint8_t data)
{
	uint8_t i=0,temp=0;
	uint8_t MISO=0;
	for(i=0;i<8;i++)
	{
		SPI_SCLK_0;			//时钟拉低
		if(data&0x80)
		{
			SPI_MOSI_1;		//MOSI拉高
		}	
		else
		{
			SPI_MOSI_0;		//MOSI拉低
		}	
		data<<=1;			//数据左移
//		delay_us(1);
		SPI_SCLK_1;			//时钟拉高完成一位数据传输
		temp<<=1;			//
		MISO=Read_MISO();  	//读取MISO口电平
		if(MISO)
		{	
			temp|=0x01;
//			delay_us(1);
		}
	}
	SPI_SCLK_0;			//
	SPI_MOSI_0;			//
	return  temp;
}

//SPI发送,进行奇校验
uint8_t SPI_ParitySend(uint8_t data)
{
	uint8_t i=0,temp=0;
	uint8_t odd=0;		//奇数
	uint8_t even=0;		//偶数
	for(i=0;i<8;i++)
	{
		SPI_SCLK_0;			//时钟拉低
		if(data&0x80)
		{
			SPI_MOSI_1;		//MOSI拉高
			even=~even;
		}	
		else
		{
			SPI_MOSI_0;		//MOSI拉低
			odd=~odd;
		}	
		data<<=1;			//数据左移
		delay_us(10);
		SPI_SCLK_1;			//时钟拉高完成一位数据传输

	}
	if(odd==0)
	{	
		SPI_MOSI_1;		//MOSI拉高
	}	
	else
	{
		SPI_MOSI_0;		//MOSI拉低
	}
	delay_us(10);
	SPI_MOSI_1;		//MOSI拉高
	delay_us(10);
	SPI_SCLK_0;			//
	SPI_MOSI_0;			//
	return  temp;	
}
//SPI读取
uint8_t SPI_Receive(void)
{
	uint8_t i=0,temp=0,MISO=0;
	for(i=0;i<8;i++)
	{
		SPI_SCLK_0;			//时钟拉低
/*		if(data&0x80)
		{
			SPI_MOSI_1;		//MOSI拉高
		}	
		else
		{
			SPI_MOSI_0;		//MOSI拉低
		}	
		data<<=1;			//数据左移
		*/
//		delay_us(1);
		SPI_SCLK_1;			//时钟拉高完成一位数据传输
		temp<<=1;
		MISO=Read_MISO();  //读取MISO口电平
		if(MISO)
		{	
			temp|=0x01;
//			delay_us(1);
		} 
	}
	SPI_SCLK_0;			//
	SPI_MOSI_0;			//
	return  temp;	
}
/*********************************************************/
//解释：写寄存器函数  ，无奇偶校验
//
//输入：寄存器地址 以及要写入的参数
//
//输出：
//
/********************************************************/
void resig_write(uint8_t cmd,uint8_t data)
{
	SPI_SCLK_0;		//时钟拉低
	SPI_NCS_0;		//拉低选通SPI口
	cmd<<=1;		//FM1702通过SPI接口写数据协议：低位为0
	cmd=cmd&0x7e;	//高位为0
//	spi_send(cmd);		//发送cmd地址
//	spi_send(data);		//发送data数据
	SPI_Send(cmd);
	SPI_Send(data);
	SPI_NCS_1;		//拉高禁止SPI口
}


//发送写之前进行奇偶校验
void resig_ParityCheck_write(uint8_t cmd,uint8_t data)
{
	SPI_SCLK_0;		//时钟拉低
	SPI_NCS_0;		//拉低选通SPI口
	cmd<<=1;		//FM1702通过SPI接口写数据协议：低位为0
	cmd=cmd&0x7e;	//高位为0
//	spi_send(cmd);		//发送cmd地址
//	spi_send(data);		//发送data数据
	SPI_ParitySend(cmd);
	SPI_ParitySend(data);
	SPI_NCS_1;		//拉高禁止SPI口
}
/*********************************************************/
//解释：读寄存器函数
//
//输入：寄存器地址 
//
//输出：该寄存器目前的值
//
/********************************************************/
uint8_t resig_read(uint8_t reg)
{
	uint8_t temp;
	SPI_SCLK_0;		//SPI口时钟拉低
//	delay_us(2);
	SPI_NCS_0;		//选通SPI模式
	reg<<=1;		//FM1702SPI的接口协议：低位为0
	reg|=0x80;		//高位为1
//	spi_send(reg);		//SPI口进行发送reg数据
//	temp=spi_receive();	// 读取返回值
	SPI_Send(reg);
	temp=SPI_Send(0x00);
	SPI_NCS_1;		//SPI口选通禁止
	return temp; 
	
}


































