regasm /codebase MES2_0_VC6_JSON_Interface.dll
wmic ENVIRONMENT where "name='path' and username='<system>'" set VariableValue="%path%;%~dp0"
set path=test
echo %path%
pause