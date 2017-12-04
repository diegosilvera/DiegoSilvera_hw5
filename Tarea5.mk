#Reconstruye en caso que algo este outdated

Resultados.hw4.tex: Plots.py 
	pdflatex Resultados_hw5.tex

Plots.py: curvarotacion.x
	./curvarotacion.x

curvarotacion.x: CurvaRotacion.c
	cc CurvaRotacion.c -lm -o curvarotacion.x