Imports System
Imports EnvDTE
Imports EnvDTE80
Imports EnvDTE90
Imports System.Diagnostics
Imports Microsoft.VisualBasic
Imports Microsoft.VisualBasic.ControlChars
Imports System.Text.RegularExpressions

Public Module CommentGenerator
    '--- Constant Declaration
    Const C_AUTHOR_NAME = "heidong"
    Const C_CONTACT_EMAIL = "buf1024@gmail.com"
    Const C_COPYRIGHT_NAME = "HEIDONG"
    Const C_TIME_FORMAT = "yyyy-MM-dd (HH:mm)"
    Const C_LOGO_LINE1 = "Filekeeper Project"
    Const C_LOGO_LINE2 = " "
    Const C_LOGO_LINE3 = " "
    Const C_LOGO_LINE4 = " "

    '--- Variable Declaration
    Dim strFunctionLine As String
    Dim strFunctionName As String
    Dim strClassName As String
    Dim strParamList As String

    Dim NamePos1, NamePos2 As Integer
    Dim ClassPos1, ClassPos2 As Integer
    Dim ParamsPos1, ParamsPos2 As Integer

    Dim i, j As Integer
    Dim NumParams As Integer
    Dim MaxParamLen As Integer
    Dim strParams() As String = Nothing
    Dim strDilimiter As String = ",;"
    Dim delimiter As Char() = strDilimiter.ToCharArray()
    Dim s As String
    Dim strDate As String

    Function RemoveNewLines(ByVal strIn As String) As String
        Return Regex.Replace(strIn, "[\r\n\t\\]", "")
    End Function

    Function CleanParams(ByVal strIn As String) As String
        Return Regex.Replace(strIn, "[&\*\[\]]", "")
    End Function

    Function GetParam(ByVal strIn As String) As String
        Dim pos As Integer
        strIn = Trim(strIn)
        pos = InStrRev(strIn, " ")
        Return Right(strIn, Len(strIn) - pos)
    End Function

    Function WriteLn(ByVal strIn)
        ActiveDocument.Selection.StartOfLine()
        ActiveDocument.Selection.Text() = strIn
        ActiveDocument.Selection.NewLine()
    End Function

    Sub GenerateFileComment()
        If (TypeOf (ActiveWindow) Is TextWindow) Then
            MsgBox("This macro can only be done if a code editor window is active!")
            Exit Sub
        End If

        strDate = Format(Now(), C_TIME_FORMAT)

        DTE.UndoContext.Open("File Description for " & DTE.ActiveDocument.Name)
        Try
            ActiveDocument.Selection.GotoLine(1, False)
            WriteLn("////////////////////////////////////////////////////////////////////////////////////////")
            WriteLn("// ")
            WriteLn("// " & C_LOGO_LINE1)
            WriteLn("// ")
            WriteLn("// FileName    : " & DTE.ActiveDocument.Name)
            WriteLn("// Purpose     : ")
            WriteLn("// Version     : " & strDate & " 1.0 Created")
            WriteLn("// Author      : " & C_AUTHOR_NAME)
            WriteLn("// Contact     : " & C_CONTACT_EMAIL)
            WriteLn("// Copyright(c): " & C_COPYRIGHT_NAME)
            WriteLn("////////////////////////////////////////////////////////////////////////////////////////")
            ActiveDocument.Selection.FindText("// Purpose     : ", vsFindOptions.vsFindOptionsBackwards)
            ActiveDocument.Selection.EndOfLine()
        Finally
            DTE.UndoContext.Close()
        End Try
    End Sub

    Sub GernerateFunctionComment()
        If (TypeOf (ActiveWindow) Is TextWindow) Then
            MsgBox("This macro can only be done if a code editor window is active")
            Exit Sub
        End If

        If ActiveDocument.Selection.IsEmpty Then
            ActiveDocument.Selection.SelectLine()
        End If

        strFunctionLine = Trim(ActiveDocument.Selection.Text)
        i = ActiveDocument.Selection.TopPoint.Line
        ActiveDocument.Selection.MoveToLineAndOffset(i, 1)
        strFunctionLine = RemoveNewLines(strFunctionLine)
        If Len(strFunctionLine) = 0 Then
            MsgBox("No new valid function line selected!")
            Exit Sub
        End If

        strFunctionName = ""
        strClassName = ""

        NamePos2 = InStr(1, strFunctionLine, "(", vbTextCompare)
        If NamePos2 < 2 Then
            MsgBox("No function name is found!")
            Exit Sub
        End If

        i = InStrRev(strFunctionLine, ":", NamePos2)
        j = InStrRev(strFunctionLine, " ", NamePos2)

        If (i > j) Then
            NamePos1 = i + 1
        Else
            NamePos1 = j + 1
        End If

        strFunctionName = Trim(Mid(strFunctionLine, NamePos1, NamePos2 - NamePos1))

        If (i > 1) Then
            ClassPos2 = NamePos1 - 3
            i = InStrRev(strFunctionLine, ":", ClassPos2)
            j = InStrRev(strFunctionLine, " ", ClassPos2)

            If (i > j) Then
                ClassPos1 = i + 1
            Else
                ClassPos1 = j + 1
            End If
            strClassName = Trim(Mid(strFunctionLine, ClassPos1, ClassPos2 + 1 - ClassPos1))
        End If

        ParamsPos1 = NamePos2 + 1
        ParamsPos2 = InStr(ParamsPos1, strFunctionLine, ")", vbTextCompare)
        If (ParamsPos2 < 1) Then
            MsgBox("No new valid parameter list found!")
            Exit Sub
        End If

        strParamList = Mid(strFunctionLine, ParamsPos1, ParamsPos2 - ParamsPos1)
        strParamList = CleanParams(strParamList)
        strParamList = strParamList.Replace("void", "")
        strParamList = strParamList.Replace("VOID", "")
        strParams = strParamList.Split(delimiter, 255)

        MaxParamLen = 0
        NumParams = 0
        For i = 0 To strParams.Length() - 1
            Dim len As Integer
            strParams(i) = GetParam(strParams(i))
            len = strParams(i).Length
            If len > MaxParamLen Then
                MaxParamLen = len
            End If
            If len > 0 Then
                NumParams = NumParams + 1
            End If
        Next

        strDate = Format(Now(), C_TIME_FORMAT)

        DTE.UndoContext.Open("Functions for " & strFunctionName & "()")
        Try
            For i = 0 To 3
                ActiveDocument.Selection.LineUp()
                ActiveDocument.Selection.SelectLine()
                If ((InStr(1, ActiveDocument.Selection.Text, "Modified:", vbTextCompare) > 0) Or (InStr(1, ActiveDocument.Selection.Text, "Created:", vbTextCompare) > 0)) Then
                    WriteLn("     * Modified: " & strDate & ", by " & C_AUTHOR_NAME)
                    Exit Sub
                End If
            Next i

            ActiveDocument.Selection.LineDown(False, 3)

            WriteLn("    /**")
            WriteLn("     * Method: " & strFunctionName)
            If (strClassName.Length > 0) Then
                WriteLn("     * Class:    " & strClassName);
            End If
            WriteLn("     * <summary></summary>")
            WriteLn("     * <remarks></remarks>")
            WriteLn("     * <returns></returns>")


            If (NumParams > 0) Then
                WriteLn("     * ")
                For i = 0 To NumParams - 1
                    WriteLn("     * <param name = """ & strParams(i) & """></param>")
                Next i
            End If
            WriteLn("     * ")
            WriteLn("     * Created:    " & strDate & ", by " & C_AUTHOR_NAME)
            WriteLn("     */")

            ActiveDocument.Selection.FindText("     * <summary>", vsFindOptions.vsFindOptionsBackwards)
            ActiveDocument.Selection.CharRight()
            ActiveDocument.Selection.EndOfLine()

        Finally
            DTE.UndoContext.Close()
        End Try

    End Sub
End Module
