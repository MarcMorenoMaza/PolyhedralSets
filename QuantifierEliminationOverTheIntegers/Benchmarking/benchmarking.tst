print("We are in test", LoopI, "with method =", MethodCall, "and mode =", ModeCall);

fd := fopen(LoopI, READ);
line1 := eval(parse(readline(fd)));
line2 := eval(parse(readline(fd)));
fclose(fd);

if MethodCall = numberofintegerpoints and ModeCall = onequantifieratatime then

	print("Time taken for test", LoopI, "is", time(QuantifierEliminationOverZ:-QEoverZ(line1, line2, method = numberofintegerpoints, mode = onequantifieratatime)));

elif MethodCall = numberofintegerpoints and ModeCall = byblockofquantifiers then

	print("Time taken for test", LoopI, "is", time(QuantifierEliminationOverZ:-QEoverZ(line1, line2, method = numberofintegerpoints, mode = byblockofquantifiers)));
	
elif MethodCall = integerpointdecomposition and ModeCall = byblockofquantifiers then

	print("Time taken for test", LoopI, "is", time(QuantifierEliminationOverZ:-QEoverZ(line1, line2, method = integerpointdecomposition, mode = byblockofquantifiers)));
	
else
	print("Time taken for test", LoopI, "is", time(QuantifierEliminationOverZ:-QEoverZ(line1, line2, method = integerpointdecomposition, mode = onequantifieratatime)));
	
end if;
