'' Simple chr viewer 
'' Just throw a chr file on the exe, sit and watch.

#include "file.bi"
#include "fbpng.bi"
#include "fbgfx.bi"
#include once "crt.bi"

#include "gui.bi"

Dim As Integer fIn, x, y, pattern, row, xx, yy, plane, x0, bank
Dim As uByte d 
Dim As uByte planes (3, 7)
Dim As Integer colours (31)
Dim As Any ptr img
Dim As String k
Dim As Integer offset

If Command (2) = "" Then ? "$ patternsview patterns.bin pals.png": System

OpenWindow 256, 272, "patternsview v0.1"

offset = 0

' Read palette colours
Do
	Do
		k = Inkey 
	Loop While k <> ""

	img = png_load (Command (2))
	For y = 0 To 1: For x = 0 To 15: colours (y*16+x) = Point (x, y, img): Line ((y*16+x)*8,0)-(7+8*(y*16+x),7),colours(y*16+x),bf:Next x, y

	fIn = FreeFile
	Open Command (1) For Binary As #fIn
	If Lof (fIn) = 0 Then
		Close #fIn
		Kill Command (1)
		System
	End If

	x0 = 0
	x = x0: y = 8

	While Not Eof (fIn)
		
		' interlaced
		For row = 0 To 7
			For plane = 0 To 3
				Get #fIn, , planes (plane, row)
			Next plane
		Next row

		For yy = 0 To 7
			For xx = 0 To 7
				d = 0
				If planes (0, yy) And (1 Shl (7 - xx)) Then d = d + 1
				If planes (1, yy) And (1 Shl (7 - xx)) Then d = d + 2
				If planes (2, yy) And (1 Shl (7 - xx)) Then d = d + 4
				If planes (3, yy) And (1 Shl (7 - xx)) Then d = d + 8

				Line (x + xx + xx, y + yy + yy) - (1 + x + xx + xx, 1 + y + yy + yy), colours (offset + d), B
			Next xx
		Next yy

		x = x + 16: If x = x0 + 256 Then x = x0: y = y + 16
	Wend

	Close #fIn

	Do
		k = Inkey
		If k <> "" And k <> Chr (32) Then System
		If k = Chr (32) Then Exit Do
	Loop

	offset = 16 - offset
Loop
