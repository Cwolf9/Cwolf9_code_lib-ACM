:again  
suiji > input.txt  
cpp1 < input.txt > biaoda_output.txt  
cpp2 < input.txt > mytest_output.txt  
fc biaoda_output.txt mytest_output.txt  
if not errorlevel 1 goto again  
pause
