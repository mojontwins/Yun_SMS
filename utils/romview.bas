' This is a quick and dirty solution.
' Code is horrible.

' Copyleft 2015 The Mojon Twins
' Compile with Freebasic

' $ fbc romview.bas

#include "file.bi"
#include "fbpng.bi"
#include "fbgfx.bi"
#include once "crt.bi"

Dim As Integer x, y, x0, y0, c
Dim As Any Ptr img
Dim As Integer r, g, b
Dim As Integer i, fIn, cartlen, banks16, bank
Dim As uByte d

If Command (1) = "" Then ? "$ 32kview input.sg [# of 16k banks]": ? : ? "If omitted, # of 16K banks is calculated.": End

fIn = FreeFile
Open Command (1) For Binary As #fIn
cartlen = lof (fIn)
If Val (Command (2)) > 0 Then banks16 = Val (Command (2)) Else banks16 = cartlen / 16384

screenres 640, 480, 32, , -1
img = ImageCreate (72 * banks16 + 36, 264, rgb (0, 0, 0))

For i = 0 To 16
	Line img, (4, i * 16 + 4)-(72 * banks16 + 3, i * 16 + 4), rgb (255,0,0)
Next i

for bank = 0 To banks16-1
	x = 72 * bank
	line img, (x + 3, 3)-(x + 68, 260), rgb (255, 255, 255), b
next bank

For i = 0 To 16
	Draw String img, (72 * banks16 + 4, i * 16), Hex (i * 1024, 4), rgb (255, 255, 0)
Next i

bank = 0
x = 0: y = 0
While Not Eof (fIn)
	Get #fIn, , d
	If d <> 0 Then Pset img, (72 * bank + 4 + x, 4 + y), rgb (0, 255, 0)
	x = x + 1: If x = 64 Then x = 0: y = y + 1: If y = 256 Then y = 0: bank = bank + 1
Wend

Close #fIn

png_save (Command (1) & ".png", img)
