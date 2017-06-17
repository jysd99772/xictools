/*
 * Copyright (c) 2000 Stephen Williams (steve@icarus.com)
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

module test;
   reg [31:0] arr[1:0];

   task writeInto;
      output [31:0] into;
      begin
	 into = 1;
      end
   endtask

   initial begin
      writeInto(arr[1]);
// SRW looks like an error here
//      if (arr[1] !== 32'd0) begin
if (arr[1] !== 32'd1) begin
	 $display("FAILED -- arr[1] = %h", arr[1]);
	 $finish;
      end
      $display("PASSED");
   end
endmodule
