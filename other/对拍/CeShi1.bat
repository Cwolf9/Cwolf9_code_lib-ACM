:again  
2_randomShuJu.exe > input.txt  
1_ac_cpp.exe < input.txt > biaoda_output.txt  
1_my_cpp.exe < input.txt > mytest_output.txt  
fc biaoda_output.txt mytest_output.txt  
if not errorlevel 1 goto again  
pause
