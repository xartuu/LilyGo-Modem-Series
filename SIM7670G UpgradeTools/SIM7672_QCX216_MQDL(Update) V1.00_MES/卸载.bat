regasm /unregister MES2_0_VC6_JSON_Interface.dll 

@echo off
set str=%path%
set str2=";%~dp0"
 
:STR_VISTOR
if defined  str (
for /F "delims=; tokens=1,*" %%a in ("%str%") do (
set "str=%%b"
echo %%a|findstr /i "%str2%" &&echo "´æÔÚ%str2%,ÐèÒªÉ¾³ý" &&(goto STR_VISTOR)
set "newPath=%newPath%%%a;"
goto :STR_VISTOR
))

setx PATH "%newPath%" -m