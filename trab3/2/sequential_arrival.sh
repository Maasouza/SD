#!/bin/bash
if [ -f "output.txt" ]
then
	rm -v "output.txt"
fi
echo "Iniciando processos <SEQUENTIAL ARRIVAL>"
for i in {1..128};
do
	python member.py &
	sleep 1s
done
echo "Terminei"