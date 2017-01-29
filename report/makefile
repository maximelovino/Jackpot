all: report.pdf

report.pdf: report.tex
	xelatex -shell-escape report.tex
	rm -r _minted-report
	rm *.log *.aux
clean:
	rm report.pdf
