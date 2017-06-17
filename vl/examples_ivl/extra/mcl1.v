/*
 * Copyright (c) 2001 Eric Brombaugh <ebrombau@intersil.com>
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

// test_simple.v - testbench for simple.mcl behavioral output
// 01-22-01 E. Brombaugh

/*
 * The ``simple'' module was generated by the synopsis module compiler
 * and is typical of the modules it generates. The testbench was hand
 * coded. This file was merged into a single file using the Verilog
 * preprocessor.
 */

`timescale 1ns / 10 ps
module simple( y, a, b, c );
input [3:0] a;
input [3:0] b;
input [7:0] c;
output [8:0] y;
wire  dpa_zero, dpa_one;
wire [8:0] y_1_;
assign dpa_zero= 1024'h0;
assign dpa_one= 1024'h1;

/* simple.mcl:4 module simple (y, a, b, c); */ 

/* simple.mcl:6 input signed [3:0] a, b; */ 

/* simple.mcl:7 input signed [7:0] c; */ 

/* simple.mcl:9 y = a*b+c; */ 

assign y_1_= ((a[2:0]-(a[3]<<3))*(b[2:0]-(b[3]<<3))+(c[6:0]-(c[7]<<7)));

/* simple.mcl:5 output signed [8:0] y; */ 

assign y = y_1_[8:0];

/* simple.mcl:4 module simple (y, a, b, c); */ 

/* simple.mcl:9 y = a*b+c; */ 

/*User Defined Aliases */
endmodule

module test_simple;

  reg [15:0] count;
  
  reg clk;
  reg [3:0] a, b;
  reg [7:0] c;
  
  wire [8:0] y;
  
  simple u1(y, a, b, c);
  
  initial
  begin
    count = 0;
    clk = 0;
    a = 0;
    b = 0;
    c = 0;
  end
  
  always
    #10 clk = ~clk;
  
  always @(posedge clk)
  begin
    a = count[3:0];
    b = count[7:4];
    c = count[15:8];
    
    #10
    $display("%x %x %x %x", a, b, c, y);
    
    count = count + 1;
    if(count == 0)
      $finish;
  end
endmodule
  
  