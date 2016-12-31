' Simple command line parser
' Copyleft 2015 The Mojon Twins

' Commands are in the form key=value. No spaces. Please.

Declare Sub sclpParseAttrs ()
Declare Function sclpGetValue (key As String) As String
Declare Function sclpGIsDef (key As String) As Integer
Declare Function sclpCheck (mandatory () As String) As Integer
