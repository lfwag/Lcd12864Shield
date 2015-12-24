

#include "Lcd12864Shield.h"


/*!
* @brief Class LCD
*
* @brief  Class LCD
*
* @return void
*/ 
void Lcd12864Shield::initialLcd(void)
{
  digitalWrite(cs_,LOW);
  digitalWrite(rst_,LOW);
  delay(100); 
  digitalWrite(rst_,HIGH);
  delay(20);
  transferCommand(0xe2);
  delay(5);
  transferCommand(0x2c);
  delay(5);
  transferCommand(0x2e);
  delay(5);
  transferCommand(0x2f);
  delay(5);
  transferCommand(0x23);  
  transferCommand(0x81);
  transferCommand(0x28);
  transferCommand(0xa2);
  transferCommand(0xc8);
  transferCommand(0xa0);
  transferCommand(0x40);
  transferCommand(0xaf);
  digitalWrite(cs_,HIGH);
}

/*!
* @brief  Send command
*
* @brief  LCD12864 Send command
*
* @return void
*/ 
void Lcd12864Shield::transferCommand(int data)
{
  digitalWrite(cs_,LOW);
  digitalWrite(rs_,LOW);
  delayMicroseconds(500);
  for(int i=0;i<8;i++){
	digitalWrite(clk_,LOW);
    if(data&0x80)digitalWrite(mosi_,HIGH);
    else digitalWrite(mosi_,LOW);
    digitalWrite(clk_,HIGH);
    data <<= 1;  
  }
}

/*!
* @brief Send data
*
* @brief    LCD12864 Send data
*
* @return void
*/ 
void Lcd12864Shield::transferData(int data)
{
  digitalWrite(cs_,LOW);
  digitalWrite(rs_,HIGH);
  for(int i=0;i<8;i++){
	digitalWrite(clk_,LOW);
    if(data&0x80)digitalWrite(mosi_,HIGH);
    else digitalWrite(mosi_,LOW);
    digitalWrite(clk_,HIGH);
    data <<= 1;  
  }
}

/*!
* @brief LCD original for the address
*
* @brief  LCD original for the address
*
* @return void
*/ 
void Lcd12864Shield::lcdAddress(unsigned char page,unsigned char column)
{
  digitalWrite(cs_,HIGH);
  transferCommand(0xb0+page);
  transferCommand(((column>>4)&0x0f) + 0x10);
  transferCommand(column&0x0f);
}

/*!
* @brief clear screen
*
* @brief  clear screen
*
* @return void
*/ 
void Lcd12864Shield::clearScreen(void)
{
  digitalWrite(cs_,LOW);
  for(int i=0;i<8;i++)
  {
    lcdAddress(i,0);
    for(int j=0;j<128;j++)
    {
      transferData(0x00);
    }
  }
  digitalWrite(cs_,HIGH);
}

/*!
* @brief Draw a horizontal line
*
* @brief  Draw a horizontal line
*
* @return void
*/ 
void Lcd12864Shield::drawXLine(char line)
{
	unsigned char line1,line2;
	line1 = line/8;
	line2 = line%8;
	line2 = 1<<line2;
	digitalWrite(cs_,LOW);
	lcdAddress(line1,0);
	for(int j=0;j<120;j++)
    {
      transferData(line2);
    }
	digitalWrite(cs_,HIGH);
}

/*!
* @brief Draw a vertical line
*
* @brief  Draw a vertical line
*
* @return void
*/ 
void Lcd12864Shield::drawYLine(char line)
{
	for(int i=0;i<8;i++){
		lcdAddress(i,line);
		transferData(0xff);
	}		
}

/*!
* @brief Draw a vertical line
*
* @brief  Draw a vertical line
*
* @return void
*/ 
void Lcd12864Shield::drawYLine(unsigned char x,unsigned char dot1,unsigned char dot2)
{
	unsigned char maxline,minline;
	unsigned char temp1,temp2;
	unsigned char max,min,mid;
	
	if(dot1>dot2){
		max = dot1;
		min = dot2;
	}else{
		max = dot2;
		min = dot1;
	}
	
	mid = 47-min;
	min = 47-max;
	max = mid;	
	
	maxline = max%8;
	max /= 8;
	minline = min%8;
	min /= 8;
	
	for(int i=0;i<6;i++){
		unsigned char data=0;
		if(i<min){
			temp1 = 8;
			temp2 = 0;
		}else if(i==min){			
			temp1 = minline;
			if(i==max){
				temp2 = maxline;
			}else{
				temp2 = 8;
			}			
		}
		else if(i<max){
			temp1 = 0;
			temp2 = 8;	
		}else if(i==max){
			temp1 = 0;
			temp2 = maxline;
		}else{
			temp1 = 8;
			temp2 = 0;
		}	

		for(unsigned char j=temp1;j<=temp2;j++){
			data +=(1<<j);
		}
		lcdAddress(i,x);
		transferData(data);
	}
}

/*!
* @brief Write a Word
*
* @brief  Write a Word
*
* @return void
*/ 	
void Lcd12864Shield::drawWord(unsigned char x,unsigned char y,int data,char *spr)
{

	for(int i=0;i<2;i++){
		lcdAddress(x-i,y);
		for(int j=0;j<16;j++){
		unsigned char datanow = *((spr++) + data*32);
		if(x-i==6){
			datanow += 1;
		}
		transferData(datanow);	
		}
	}	
}

/*!
* @brief Displays a letter
*
* @brief  Displays a letter
*
* @return void
*/ 
void Lcd12864Shield::drawLetter(unsigned char  x,unsigned char y,int data,char *spr)
{
	for(int i=0;i<2;i++){
		lcdAddress(x+i-1,y);
		for(int j=0;j<8;j++){
		unsigned char datanow = *( (spr++) +  data*16);
		if(x+i-1==6){
			datanow += 1;
		}
		transferData(datanow);	
		}
	}	
}
/*!
* @brief Write more characters
*
* @brief  Write more characters
*
* @return void
*/ 
void Lcd12864Shield::drawLetter(unsigned char  x,unsigned char y,char number,int data,char *spr)
{
	
	int datanow[10];
	for(int i=number;i>0;i--){
		datanow[i-1] = data%10;
		data /= 10;
	}	
	for(int i=0;i<number;i++){		
		drawLetter(x,y+i*8,datanow[i],spr);
	}
}


/******************************************************************************
  Copyright (C) <2015>  <linfeng>
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  Contact: 490289303@qq.com
 ******************************************************************************/
 
