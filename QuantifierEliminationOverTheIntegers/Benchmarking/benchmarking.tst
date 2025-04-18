print("We are in test", LoopI, "with method =", MethodCall, "and mode =", ModeCall);

fd := fopen(LoopI, READ);
line1 := eval(parse(readline(fd)));
line2 := eval(parse(readline(fd)));
fclose(fd);

if MethodCall = numberofintegerpoints and ModeCall = onequantifieratatime then

	print("Time taken for test", LoopI, "is", CodeTools:-Usage(QuantifierEliminationOverZ:-QEoverZ(line1, line2, method = numberofintegerpoints, mode = onequantifieratatime), output = ['cputime', 'bytesused']));

elif MethodCall = numberofintegerpoints and ModeCall = byblockofquantifiers then

	print("Time taken for test", LoopI, "is", CodeTools:-Usage(QuantifierEliminationOverZ:-QEoverZ(line1, line2, method = numberofintegerpoints, mode = byblockofquantifiers), output = ['cputime', 'bytesused']));
	
elif MethodCall = integerpointdecomposition and ModeCall = byblockofquantifiers then

	print("Time taken for test", LoopI, "is", CodeTools:-Usage(QuantifierEliminationOverZ:-QEoverZ(line1, line2, method = integerpointdecomposition, mode = byblockofquantifiers), output = ['cputime', 'bytesused']));
	
else
	print("Time taken for test", LoopI, "is", CodeTools:-Usage(QuantifierEliminationOverZ:-QEoverZ(line1, line2, method = integerpointdecomposition, mode = onequantifieratatime), output = ['cputime', 'bytesused']));
	
end if;
