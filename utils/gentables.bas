' Generic table generation
' Tweak to fit your needs

Dim As Integer i

Open "tableout.h" For Output As #1

'' Table 1: shift left 0-15 -> 0-240.
Print #1, "const unsigned char shl4 [] = {"
Print #1, "	";
For i = 0 To 16
	Print #1, "0x" & Lcase (Hex (i*16, 2));
	If i < 16 Then Print #1, ", ";
Next i
Print #1, "};"
Print #1, ""

'' Table 2: shift right 0-255->0-15
Print #1, "const unsigned char shr4 [] = {"
Print #1, "	";
For i = 0 To 255
	Print #1, "0x" & Lcase (Hex (i\16, 2));
	If i < 255 Then Print #1, ", ";
	If i Mod 16 = 15 Then Print #1, "": Print #1, "	";
Next i
Print #1, "};"
Print #1, ""

Close #1
