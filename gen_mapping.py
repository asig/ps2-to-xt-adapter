#!/usr/bin/env python3

import csv

def dumpMap(map, name):
	print("const uint8_t %s[] PROGMEM = {" % name);
	for i in range(0,8):
		print("    ",end='')
		for j in range(0,16):
			mapped = map.get(i*16+j,0)
			print(str.format("0x{:02X}",mapped), end='');
			if i*16+j != 127:
				print(",", end='')
		print("");
	print("};");


map = {}
mapE0 = {}
with open('ScanCodeMapping.tsv', newline='') as csvfile:
	reader = csv.reader(csvfile, delimiter='\t', quotechar='"')
	# Skip 2 header rows
	next(reader)
	next(reader)
	for row in reader:
		# Check that we talk about the same:
		if row[0] != row[3]:
			print("BAD ROW! %s" % ', '.join(row))			
		make = row[1].lower()
		mapped = row[4].lower();
		if make[0:2] == "e0":
			# escape 1 byte
			make = make[3:]
			mapped = mapped[3:]
			mapE0[int(make, 16)] = int(mapped, 16)

		elif make[0:2] != "e1":
			# regular single byte mapping
			map[int(make, 16)] = row
			map[int(make, 16)] = int(mapped, 16)
		# else
		#	# escape 2 bytes
		#	# no table handling, implemented manually

dumpMap(map, "mapping")
dumpMap(mapE0, "mappingE0")
