' Bytecounter.bas

#include "mtparser.bi"

Sub usage
	Print "bytecounter v0.1 - counts data bytes in a pure-data C source. "
	Print
	Print "usage: "
	print "$ bytecounter.exe file.c"
End Sub

Dim As Integer total, it
Dim As String codeLine, tokens (255), purehex

If Command (1) = "" Then usage: End

Open Command (1) For Input As #1

While Not Eof (1)
	Line Input #1, codeLine
	parseTokenizeString codeLine, tokens (), ".,{}-=[]*_", "/"
	For it = 0 To 255
		If Instr (tokens (it), "0x") Then
			purehex = Right (tokens (it), Len (tokens (it)) - 2)
			total = total + (Len (purehex) \ 2)
		End If
	Next it
Wend

Close #1

Print total
