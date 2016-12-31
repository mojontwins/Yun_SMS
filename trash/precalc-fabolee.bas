' It's about simulating a fabolee
' and recording the X, Y increments in two arrays.
'
' This way I can manage fabolees without the need of complex fixed point, 16 bits maths.

Const FixBits = 4
Const FaboleesVXIni = 42
Const FaboleesVYMax = 32


' We try and simulate the fabolees as closely as possible
Dim As Short fblX, fblY
Dim As Short fblVX, fblVY
Dim As uByte fblrX, fblrY, fblrCX, fblrCY

Dim As Byte fblIncrX (1024)
Dim As Byte fblIncrY (1024)
Dim As Integer index, halfLife, to3, i, count

fblX = 0 
fblY = 192 Shl FixBits

fblVX = FaboleesVXIni
fblVY = 0

fblrCX = fblX Shr FixBits
fblrCY = fblY Shr FixBits

Screen 7

index = 0: halfLife = 0: to3 = 0
While fblY > 0
	If halfLife Then 
		fblVY = fblVY - 1: If fblVY < -FaboleesVYMax Then fblVY = -FaboleesVYMax
		fblVX = fblVX - 1
		If to3 = 0 Then fblVX = fblVX - 1
		If fblVX < 0 Then fblVX = 0
		to3 = to3 + 1: If to3 = 3 Then to3 = 0	
	End If

	fblX = fblX + fblVX
	fblY = fblY + fblVY
	fblrX = fblX Shr FixBits
	fblrY = fblY Shr FixBits

	fblIncrX (index) = fblrX - fblrCX
	fblIncrY (index) = fblrCY - fblrY

	fblrCX = fblrX
	fblrCY = fblrY

	index = index + 1

	Pset (fblrX, fblrY), 15
	halfLife = 1 - halfLife
	
Wend

Open "fabo_incr.h" for output as #1
Print #1, "#define FBL_INCR_MAX " & index
Print #1, ""
Print #1, "const signed char fbl_incr_x [] = {"
count = 0: Print #1, "	";
For i = 0 To index - 1
	Print #1, "0x" & Lcase (Hex (fblIncrX (i), 2));
	If i < index - 1 Then Print #1, ", ";
	count = (count + 1) And 15: If count = 0 And i < index - 1 Then Print #1, "":Print #1, "	";
Next i
Print #1, ""
Print #1, "};"
Print #1, ""
Print #1, "const signed char fbl_incr_y [] = {"
count = 0: Print #1, "	";
For i = 0 To index - 1
	Print #1, "0x" & Lcase (Hex (fblIncrY (i), 2));
	If i < index - 1 Then Print #1, ", ";
	count = (count + 1) And 15: If count = 0 And i < index - 1 Then Print #1, "":Print #1, "	";
Next i
Print #1, ""
Print #1, "};"

Print #1, ""
Print #1, "#define FBL_INCR_MAX " & index
Print #1, ""
Print #1, "const signed char fbl_incr_x [] = {"
count = 0: Print #1, "	";
For i = 0 To index - 1
	Print #1, "" & fblIncrX (i);
	If i < index - 1 Then Print #1, ", ";
	count = (count + 1) And 15: If count = 0 And i < index - 1 Then Print #1, "":Print #1, "	";
Next i
Print #1, ""
Print #1, "};"
Print #1, ""
Print #1, "const signed char fbl_incr_y [] = {"
count = 0: Print #1, "	";
For i = 0 To index - 1
	Print #1, "" & fblIncrY (i);
	If i < index - 1 Then Print #1, ", ";
	count = (count + 1) And 15: If count = 0 And i < index - 1 Then Print #1, "":Print #1, "	";
Next i
Print #1, ""
Print #1, "};"

Close #1

Sleep
Screen 0
End
