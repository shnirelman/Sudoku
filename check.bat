@for %%f in (sample*in.txt) do @(
	@solve.exe %%f > output.txt
	@compare.exe %%f
)

@pause