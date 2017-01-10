 ABOUT

os9_conv is a small tool used to convert APPLE ][ OS9 Stellation Two "The Mill" DSK image disks (created using ADT tool) to standard RBF OS9 DSK image disks, such as, for example,  those used by the TRS-80 Color Computer, and back.

The aim of this utility is to create an OS9 RBF floppy disk image compatible with the "toolshed" TRS-80 Color Computer utility.
The toolshed utility allows direct manipulation of OS9 RBF disk image content from MS-DOS, allowing to directly read,write OS9 files etc.

With the toolshed and os9_conv tools combination is now possible to transfer files back and forth to the Apple ][ Stellation Two "The Mill" OS9 implementation. 
 
 USE
 
os9_conv syntax is:
 
        os9_conv <source file> <destination file> <option>
 
where options are:
   -a (convert OS9 dsk image to Apple ][ \"The Mill\" format)
   -o (convert Apple ][ \"The Mill\" OS9 DSK image to OS9 format)
 
 EXAMPLE 1
 
Let's say that we want to extract the ECHO executable binary file  from the APPLE ][ OS9 o.s. system disk image (for example OS9BASIC.dsk); we first proceed converting the APPLE ][ OS9 DSK disk image to OS9 RBF standard with the command:
 
       OS9_conv OS9BASIC.dsk OS9BASICRBF.dsk -o
 
OS9_conv will convert the source file OS9BASIC.dsk to OS9 RBF format (-o option)  and write it to the destination file OS9BASICRBF.dsk (or whatever filename you choose).
 
To extract the ECHO executable binary file from OS9BASICRBF.dsk using the toolshed OS9 tool the command would be:
 
       OS9 copy OS9BASICRBF.dsk,CMDS/ECHO ECHO
 
The ECHO binary file will be created under MS-DOS. See toolshed documentation for a list of the available commands.
 
 EXAMPLE 2
 
Lets' say that we want to make the reverse operation of EXAMPLE 1 by writing a binary file ( example MYBINARY file )to the APPLE ][ OS9 OS9BASIC.dsk disk .
We first proceed converting the APPLE ][ OS9 DSK disk image to OS9 RBF standard with the command:
 
       OS9_conv OS9BASIC.dsk OS9BASICRBF.dsk -o
       
OS9_conv will convert the source file OS9BASIC.dsk to OS9 RBF format (-o option)  and write it to the destination file OS9BASICRBF.dsk (or whatever filename you choose).
 
To write the MYBINARY file to OS9BASICRBF.dsk disk using the toolshed OS9 tool the command would be:
 
       OS9 copy MYBINARY OS9BASICRBF.dsk,MYBINARY
       
The MYBINARY binary file will be written in the root directory of OS9BASICRBF.dsk disk. See toolshed documentation for a list of the available commands.

Finally we revert  OS9BASICRBF.dsk back to APPLE ][ Stellation Two "The MILL" OS9 disk format with the command:

       OS9_conv OS9BASICRBF.dsk OS9BASIC.dsk -a
       
The resulting image can be fed in an APPLE ][ emulator (mame can emulate an  APPLE ][ with a Stellation Two "The Mill" card, or an real floppy written with a tool such as ADT. 

NOTE

Due to the a not completely standard  implementation of the RBF file system in the APPLE ][ Stellation Two "The MILL" OS9 disk structure, to maintain disk integrity, any  operation is ALWAYS started from an APPLE ][ OS9 DSK disk image. 

LICENSE

Apple ][ "The Mill" OS9 DSK image to OS9 RBF format converter os9_conv is released under the terms of the MIT License.

Copyright 2017 Luca Ridarelli

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE




