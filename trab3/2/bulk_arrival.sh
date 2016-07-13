#!/bin/bash
if [ -f "output.txt" ]
then
	rm -v "output.txt"
fi
echo Iniciando processos...
for i in {1..2};
do
	python member.py &
done
echo Terminei