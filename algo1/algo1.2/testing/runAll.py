#!/usr/bin/env python
import re
import os


results = open("results.txt", "w")
for case in range(1,31):
	love = open("myRes"+str(case)+".txt","w")
	print "Running for testcase "+str(case)+" now"
	#run your executable here, mine is "chocolate" in that case
	os.system('./chocolate < input'+str(case)+'.txt | tee myRes'+str(case)+'.txt')  
	love.close()

	love1 = open("myRes"+str(case)+".txt","r")
	love2 = open("output"+str(case)+".txt","r")
		
	for line in love1:
		token1 = line.split()
	for line in love2:
		token2 = line.split()	
	
	if(token1==token2):
		print >>results,"tescase" +str(case) + " finished with success !!! "
		print "tescase" +str(case) + " finished with success !!! \n\n"
	else:
		print >>results,"tescase" +str(case) + " gave wrong output !!! "
		print "WARNING:\ntescase" +str(case) + " gave wrong output !!! \n\n"
