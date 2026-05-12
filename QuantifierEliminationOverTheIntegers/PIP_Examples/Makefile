MAPLE_EXEC := maple

samplePoint:
	@for file in SamplePoint/*; do \
		echo "Running test: $$file"; \
		ulimit -t 1800; \
		$(MAPLE_EXEC) < $$file; \
	done


locus:
	@for file in Locus/*; do \
		echo "Running test: $$file"; \
		ulimit -t 1800; \
		$(MAPLE_EXEC) < $$file; \
	done