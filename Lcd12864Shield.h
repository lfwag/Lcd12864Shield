/*!
* @file Lcd12864Shield.h
* @brief Lcd12864Shield.h detailed description for Lcd12864Shield.cpp 
*
*  This library file is prepared for the company's LCD12864.
*  Link below:http://www.dfrobot.com.cn/goods-849.html .
*  You can display Chinese characters, letters, and lines
* 
* @author linfeng(490289303@qq.com)
* @version  V1.0
* @date  2015-12-24
*/


#ifndef __LCD12864SHIELD__H
#define __LCD12864SHIELD__H

#include "Arduino.h"


class Lcd12864Shield
{
public:
	Lcd12864Shield(unsigned char CS,unsigned char RS,unsigned char RST,unsigned char CLK,unsigned char MOSI)
	{ cs_ = CS; rs_ = RS; rst_ = RST; clk_ = CLK; mosi_ = MOSI;	
	  pinMode(cs_,OUTPUT); pinMode(rs_,OUTPUT); pinMode(rst_,OUTPUT); pinMode(clk_,OUTPUT); pinMode(mosi_,OUTPUT); }
	void initialLcd(void);
	void transferCommand(int data);
	void transferData(int data);
	void lcdAddress(unsigned char page,unsigned char column);
	void clearScreen(void);
	void drawXLine(char line);
	void drawYLine(char line);
	void drawYLine(unsigned char x,unsigned char dot1,unsigned char dot2);
	void drawWord(unsigned char x,unsigned char y,int data,char *spr);
	void drawLetter(unsigned char  x,unsigned char y,int data,char *spr);
	void drawLetter(unsigned char  x,unsigned char y,char number,int data,char *spr);	
	
public:
	unsigned char cs_,rs_,rst_,clk_,mosi_;	
};


#endif

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
 
 