import numpy as np
import matplotlib.pyplot as plt


conf_arr = [[744,0,21,8,10,16,16,6,12,13],
[0,892,26,19,22,16,8,22,24,24],
[3,3,697,33,11,6,7,14,18,2],
[1,2,44,672,4,113,1,4,51,8],
[8,0,21,9,661,15,20,32,24,106],
[9,1,10,38,8,529,13,5,33,6],
[15,2,16,12,38,12,711,2,16,25],
[1,2,14,15,7,9,1,770,1,31],
[4,4,29,39,16,29,15,7,612,18],
[1,1,4,15,71,18,2,34,23,617]]

conf_arr = [[825,0,4,1,1,4,3,1,4,2],
[0,927,3,3,2,0,0,13,1,4],
[3,6,761,22,3,2,1,7,7,1],
[1,2,6,761,1,36,0,0,18,10],
[0,0,2,1,684,2,2,6,3,56],
[1,2,5,15,1,691,6,3,25,6],
[10,0,10,2,9,15,868,0,4,5],
[0,0,11,7,6,0,0,811,1,21],
[0,3,7,44,2,7,2,1,717,6],
[0,2,1,10,66,10,2,29,13,741]]


norm_conf = []
for i in conf_arr:
    a = 0
    tmp_arr = []
    a = sum(i, 0)
    for j in i:
        tmp_arr.append(float(j)/float(a))
    norm_conf.append(tmp_arr)

fig = plt.figure()
plt.clf()
ax = fig.add_subplot(111)
ax.set_aspect(1)
res = ax.imshow(np.array(norm_conf), cmap=plt.cm.jet, 
                interpolation='nearest')

#width, height = conf_arr.shape
#, height = 10
#for x in xrange(width):
#    for y in xrange(height):
#        ax.annotate(str(conf_arr[x][y]), xy=(y, x), 
#                    horizontalalignment='center',
#                    verticalalignment='center')

for x in range(10):
    for y in range(10):
        ax.annotate(str(conf_arr[x][y]), xy=(y, x), 
                    horizontalalignment='center',
                    verticalalignment='center')




cb = fig.colorbar(res)
#alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
alphabet = '012345678910111213141516'
plt.xticks(range(10), alphabet[:10])
plt.yticks(range(10), alphabet[:10])
plt.savefig('confusion_matrix.png', format='png')
