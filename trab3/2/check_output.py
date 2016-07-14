file = open('output.txt')
file = file.readlines()
isCorrect = True
for line in file[0:(len(file)-1)]: 
	if(isCorrect):
		try:
			values = line.split("::")
			if ((values[0] != values[2]) or (len(values[2]) != 4) or (len(values) != 4)):
				isCorrect = False
		except:
			isCorrect = False
	else:
		break
if (isCorrect):
	print ("FILE IS OK")
else:
	print ("ERROR IN FILE")