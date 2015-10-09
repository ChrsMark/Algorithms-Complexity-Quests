#!/usr/bin/env python
import re
import os


results = open("results.txt", "w")
for case in range(1,31):
	love = open("myRes.txt","w")
	print "Running for testcase "+str(case)+" now"
	#run your executable here, mine is "meeting" in that case
	#os.system('time ./rob < input'+str(case)+'.txt | tee myRes.txt') 
	os.system('time ./rob < input'+str(case)+'.txt') 
	print "\n"
	'''	
	love.close()

	love1 = open("myRes.txt","r")
	
	print "\n"	
	for line in love1:
		print >>results,line
		
		'''
