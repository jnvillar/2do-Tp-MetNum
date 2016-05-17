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

conf_arr = [[488, 0, 0, 0, 0, 0, 3, 0, 2, 1],
[0, 547, 1, 2, 0, 0, 4, 0, 3, 1],
[12, 3, 509, 2, 1, 0, 2, 4, 11, 1],
[7, 3, 7, 431, 0, 8, 1, 1, 21, 1],
[8, 1, 1, 0, 413, 0, 8, 1, 0, 45],
[11, 1, 0, 28, 1, 385, 10, 0, 25, 8],
[11, 0, 0, 0, 2, 0, 501, 0, 2, 0],
[5, 4, 10, 3, 4, 0, 1, 445, 1, 33 ],
[8, 3, 2, 19, 2, 3, 8, 1, 431, 0 ],
[11, 3, 2, 7, 8, 2, 0, 10, 4, 431]]

conf_arr = [[489, 0, 0, 0, 0, 0, 2, 0, 2, 1 ],
[0, 545, 2, 1, 0, 0, 5, 0, 4, 1 ],
[13, 3, 506, 3, 1, 0, 2, 4, 12, 1 ],
[5, 3, 8, 434, 0, 7, 1, 1, 20, 1 ],
[7, 1, 2, 2, 408, 0, 9, 1, 1, 46 ],
[12, 1, 0, 27, 1, 384, 9, 0, 29, 6 ],
[13, 0, 0, 0, 2, 1, 498, 0, 2, 0 ],
[6, 4 ,10, 5, 1, 0, 1 ,447, 1 ,31 ],
[8, 3, 1, 27, 1, 4, 7, 1, 425, 0 ],
[12, 3, 1, 8, 10, 2, 0, 9, 7, 426 ],]


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
                    verticalalignment='center',
                    color='#eeefff')




cb = fig.colorbar(res)
#alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
alphabet = '012345678910111213141516'
plt.xticks(range(10), alphabet[:10])
plt.yticks(range(10), alphabet[:10])
plt.savefig('confusion_matrix.png', format='png')
