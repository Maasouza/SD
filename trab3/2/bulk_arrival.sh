#!/bin/bash
if [ -f "output.txt" ]
then
	rm -v "output.txt"
fi
echo "Iniciando processos <BULK ARRIVAL>"
for i in {1..16};
do
	python member.py &
done
echo "Terminei"