#coding=utf-8
import sys
import numpy as np
import matplotlib.pyplot as plt
import json

belong_dict = {}

def belongs(item):
	item = item.upper()
	belong = "ELSE"
	for key in belong_dict.keys():
		contains = False
		for val in belong_dict[key]:
			if item.find(val)!=-1:
				contains = True
				break
		if contains is True:
			belong = key
			break

	return belong

# read raw list from raw_fn
# read belongs from belongs_fn
# count the occurance of belongs, and plot bar chart
if __name__ == "__main__":
	title = u"使用次数"
	try: 
		raw_fn = sys.argv[1]
		title = u"用户个数"
	except: raw_fn = "raw.log"
	raw_list = open(raw_fn).readlines()
	
	with open('belongs.log', 'r') as fd:
		belong_dict = json.loads(fd.read())
	print belong_dict
	belong_list = []

	for item in raw_list:
		belong_list.append(belongs(item))
	d = {}
	for i in range(len(raw_list)):
		raw_list[i] = raw_list[i].strip('\n')
		if belong_list[i] in d.keys():
			cnt = int(d[belong_list[i]])+1
			d[belong_list[i]] = int(cnt)
		else:
			d[belong_list[i]] = int(0)
	print d
	print sum(d.values())
	x = range(len(d.keys()))
	plt.title(u"{1}, total {0}".format(sum(d.values()), title))
	plt.xticks(x, d.keys(), rotation="vertical")
	plt.bar(left=x, height=d.values())
	plt.show()
