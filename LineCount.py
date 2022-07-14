def getFileNames():
	with open('Blobfish\CMakeLists.txt', 'r') as f:
		for line in f:
			if 'set(SOURCE_FILES' in line:
				words = line.split()
				words.pop(0)
				words[-1] = words[-1][:-1]
	return words

def numberOfLines(file):
	with open(file, 'r') as f:
		l = sum(1 for line in f if (len(line)>2 and not line.strip().startswith("/")))
	return l

if __name__=="__main__":
	lengths = [(file, numberOfLines('Blobfish/'+file)) for file in getFileNames()]
	lengths.sort(key=lambda x: x[1], reverse=True)
	total = 0
	for filename, length in lengths:
		total += length
		print(length, filename)
	print(f'\nTOTAL: {total}')
