# Define the Maple executable and the files to be processed
MAPLE_EXEC := maple
INPUT_FILES := $(wildcard Input/*)
OUTPUT_FILE_NIP_one := results_NIP_one.output
OUTPUT_FILE_NIP_block := results_NIP_block.output
OUTPUT_FILE_IPD_one := results_IPD_one.output
OUTPUT_FILE_IPD_block := results_IPD_block.output
BENCHMARKING_FILE_NIP_one := BENCHMARKING_results_NIP_one.output
BENCHMARKING_FILE_NIP_block := BENCHMARKING_results_NIP_block.output
BENCHMARKING_FILE_IPD_one := BENCHMARKING_results_IPD_one.output
BENCHMARKING_FILE_IPD_block := BENCHMARKING_results_IPD_block.output
CRASH_LOG := crash_log.txt

# Ensure input files exist
ifeq ($(strip $(INPUT_FILES)),)
$(error "No input files found in Input/")
endif

.PHONY: all test_NIP_one test_NIP_block test_IPD_one test_IPD_block clean

# Target to run all input files through Maple for both procedures
all: test_NIP_one test_NIP_block test_IPD_one test_IPD_block

# Rule to run Maple with the given input files for test_NIP_one
test_NIP_one: $(OUTPUT_FILE_NIP_one) $(BENCHMARKING_FILE_NIP_one)

$(OUTPUT_FILE_NIP_one): $(INPUT_FILES)
	@echo "Running tests using method = NumberOfIntegerPoints and mode = onequantifieratatime"
	@rm -f $(OUTPUT_FILE_NIP_one) $(BENCHMARKING_FILE_NIP_one) $(CRASH_LOG)
	@for file in $(INPUT_FILES); do \
		echo "Running test: $$file"; \
		ulimit -t 300; \
		ulimit -m 8388608; \
		echo "LoopI := \"$$file\"; MethodCall := numberofintegerpoints; ModeCall := onequantifieratatime;" | cat - benchmarking.tst > temp.tst; \
		$(MAPLE_EXEC) < temp.tst > temp_output 2>&1; \
		cat temp_output >> $(OUTPUT_FILE_NIP_one); \
		if grep -q "Error," temp_output; then \
			echo "Crash detected for file: $$file" >> $(CRASH_LOG); \
			echo "Method: NumberOfIntegerPoints" >> $(CRASH_LOG); \
			echo "Mode: onequantifieratatime" >> $(CRASH_LOG); \
			grep "Error," temp_output >> $(CRASH_LOG); \
			echo "------------------------------------" >> $(CRASH_LOG); \
		fi; \
		rm -f temp.tst temp_output; \
	done

# Rule to filter results for test_NIP_one
$(BENCHMARKING_FILE_NIP_one): $(OUTPUT_FILE_NIP_one)
	@echo "Benchmark for tests using method = NumberOfIntegerPoints and mode = onequantifieratatime"
	@grep "\"Time taken for test\", \"" $(OUTPUT_FILE_NIP_one) > $(BENCHMARKING_FILE_NIP_one)
	@rm -f $(OUTPUT_FILE_NIP_one)

# Rule to run Maple with the given input files for test_NIP_block
test_NIP_block: $(OUTPUT_FILE_NIP_block) $(BENCHMARKING_FILE_NIP_block)

$(OUTPUT_FILE_NIP_block): $(INPUT_FILES)
	@echo "Running tests using method = NumberOfIntegerPoints and mode = byblockofquantifiers"
	@rm -f $(OUTPUT_FILE_NIP_block) $(BENCHMARKING_FILE_NIP_block) $(CRASH_LOG)
	@for file in $(INPUT_FILES); do \
		echo "Running test: $$file"; \
		ulimit -t 300; \
		ulimit -m 8388608; \
		echo "LoopI := \"$$file\"; MethodCall := numberofintegerpoints; ModeCall := byblockofquantifiers;" | cat - benchmarking.tst > temp.tst; \
		$(MAPLE_EXEC) < temp.tst > temp_output 2>&1; \
		cat temp_output >> $(OUTPUT_FILE_NIP_block); \
		if grep -q "Error," temp_output; then \
			echo "Crash detected for file: $$file" >> $(CRASH_LOG); \
			echo "Method: NumberOfIntegerPoints" >> $(CRASH_LOG); \
			echo "Mode: byblockofquantifiers" >> $(CRASH_LOG); \
			grep "Error," temp_output >> $(CRASH_LOG); \
			echo "------------------------------------" >> $(CRASH_LOG); \
		fi; \
		rm -f temp.tst temp_output; \
	done

# Rule to filter results for test_NIP_block
$(BENCHMARKING_FILE_NIP_block): $(OUTPUT_FILE_NIP_block)
	@echo "Benchmark for tests using method = NumberOfIntegerPoints and mode = byblockofquantifiers"
	@grep "\"Time taken for test\", \"" $(OUTPUT_FILE_NIP_block) > $(BENCHMARKING_FILE_NIP_block)
	@rm -f $(OUTPUT_FILE_NIP_block)

# Rule to run Maple with the given input files for test_IPD_one
test_IPD_one: $(OUTPUT_FILE_IPD_one) $(BENCHMARKING_FILE_IPD_one)

$(OUTPUT_FILE_IPD_one): $(INPUT_FILES)
	@echo "Running tests using method = IntegerPointDecomposition and mode = onequantifieratatime"
	@rm -f $(OUTPUT_FILE_IPD_one) $(BENCHMARKING_FILE_IPD_one) $(CRASH_LOG)
	@for file in $(INPUT_FILES); do \
		echo "Running test: $$file"; \
		ulimit -t 300; \
		ulimit -m 8388608; \
		echo "LoopI := \"$$file\"; MethodCall := integerpointdecomposition; ModeCall := onequantifieratatime;" | cat - benchmarking.tst > temp.tst; \
		$(MAPLE_EXEC) < temp.tst > temp_output 2>&1; \
		cat temp_output >> $(OUTPUT_FILE_IPD_one); \
		if grep -q "Error," temp_output; then \
			echo "Crash detected for file: $$file" >> $(CRASH_LOG); \
			echo "Method: IntegerPointDecomposition" >> $(CRASH_LOG); \
			echo "Mode: onequantifieratatime" >> $(CRASH_LOG); \
			grep "Error," temp_output >> $(CRASH_LOG); \
			echo "------------------------------------" >> $(CRASH_LOG); \
		fi; \
		rm -f temp.tst temp_output; \
	done
# Rule to filter results for test_IPD_one
$(BENCHMARKING_FILE_IPD_one): $(OUTPUT_FILE_IPD_one)
	@echo "Benchmark for tests using method = IntegerPointDecomposition and mode = onequantifieratatime"
	@grep "\"Time taken for test\", \"" $(OUTPUT_FILE_IPD_one) > $(BENCHMARKING_FILE_IPD_one)
	@rm -f $(OUTPUT_FILE_IPD_one)

# Rule to run Maple with the given input files for test_IPD_block
test_IPD_block: $(OUTPUT_FILE_IPD_block) $(BENCHMARKING_FILE_IPD_block)

$(OUTPUT_FILE_IPD_block): $(INPUT_FILES)
	@echo "Running tests using method = IntegerPointDecomposition and mode = byblockofquantifiers"
	@rm -f $(OUTPUT_FILE_IPD_block) $(BENCHMARKING_FILE_IPD_block) $(CRASH_LOG)
	@for file in $(INPUT_FILES); do \
		echo "Running test: $$file"; \
		ulimit -t 300; \
		ulimit -m 8388608; \
		echo "LoopI := \"$$file\"; MethodCall := integerpointdecomposition; ModeCall := byblockofquantifiers;" | cat - benchmarking.tst > temp.tst; \
		$(MAPLE_EXEC) < temp.tst > temp_output 2>&1; \
		cat temp_output >> $(OUTPUT_FILE_IPD_block); \
		if grep -q "Error," temp_output; then \
			echo "Crash detected for file: $$file" >> $(CRASH_LOG); \
			echo "Method: IntegerPointDecomposition" >> $(CRASH_LOG); \
			echo "Mode: byblockofquantifiers" >> $(CRASH_LOG); \
			grep "Error," temp_output >> $(CRASH_LOG); \
			echo "------------------------------------" >> $(CRASH_LOG); \
		fi; \
		rm -f temp.tst temp_output; \
	done

# Rule to filter results for test_IPD_block
$(BENCHMARKING_FILE_IPD_block): $(OUTPUT_FILE_IPD_block)
	@echo "Benchmark for tests using method = IntegerPointDecomposition and mode = byblockofquantifiers"
	@grep "\"Time taken for test\", \"" $(OUTPUT_FILE_IPD_block) > $(BENCHMARKING_FILE_IPD_block)
	@rm -f $(OUTPUT_FILE_IPD_block)

# Clean up any generated files
clean:
	rm -f $(BENCHMARKING_FILE_NIP_one) $(OUTPUT_FILE_NIP_one) $(BENCHMARKING_FILE_NIP_block) $(OUTPUT_FILE_NIP_block) \
	      $(BENCHMARKING_FILE_IPD_one) $(OUTPUT_FILE_IPD_one) $(BENCHMARKING_FILE_IPD_block) $(OUTPUT_FILE_IPD_block) $(CRASH_LOG) temp.tst temp_output

