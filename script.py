from pylab import *
import os
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
from numpy.polynomial import polynomial as P





filenames_dat = ["data1.dat","data2.dat","data3.dat","data4.dat","data5.dat"]
num =[1,2,4,16,32]
block_size =16384 
mem = 209715200
os.system("rm -f *sorted*")
def part2_1():
    os.system("> log.txt")
    for i in range (0,5):
        command = "/usr/bin/time -v ./disk_sort "+ filenames_dat[i] + " "+ str(mem/num[i])+" "+str(block_size) + " 2>>log.txt"

        os.system(command)
        os.system("rm -f *sorted*")
#part2_1()

def plot_part2():
    y=[39.43, 37.80, 38.98, 37.32, 39.42]
    x=[209715200,209715200/2,209715200/4,209715200/8,209715200/16]    
    x = np.log10(x)
    fig = plt.figure()

    width = .35
    ind = np.arange(len(y))
    result = plt.bar(ind, y, width=width, color=(0.2588, 0.4433, 1.0))
    plt.xticks(ind + width / 2, x)

    fig.autofmt_xdate()

    plt.xlabel('main memory size log()')
    plt.ylabel('run time')
    plt.title('main memory vs time ')

    plt.show()
#plot_part2()

def exp_3(filename):
    x = []
    y = []

    f = open(filename, "r")
    for line in f:
        line = line.strip('\n')
        x.append(int(line.split(",")[0]))
        y.append(int(line.split(",")[1]))
    plot(x, y, '.')
    show()

    fig = plt.figure()

    width = 1000
    result = plt.bar(x, y, width=width, color=(0.2588, 0.4433, 1.0))
    plt.xlabel('out degrees')
    plt.ylabel('number of users')
    plt.show()
#exp_3("megered2.txt")
def power_law(filename):
    x = []
    y = []

    f = open(filename, "r")
    for line in f:
        line = line.strip('\n')
        x.append(int(line.split(",")[0]))
        y.append(int(line.split(",")[1]))
    logx = np.log(x)
    logy = np.log(y)
    (aCoeff, bCoeff, rVal, pVal, stdError) = stats.linregress(logx, logy)
    a = find_best_fit_line(logx, logy, aCoeff)
    predictY = (a * logx) + max(logy)
    plt.axis((min(logx),max(logx),0,max(logy)))
    plot(logx, logy, 'bs')
    plot(logx, predictY,'r-')

    xlabel('log(in-degrees)  $10^x$')
    ylabel('log(number of users)  $10^y$')
    print(a)
    
    show()

def find_best_fit_line(x, y, a):
    best_a = 0
    error = infty
    for i in range(0, 10):
        a = a - 0.1
        predictY = (a * x) + max(y)
        #plot(x, predictY)
        current_e = sum(square(predictY[:len(y)//2] - y[:len(y)//2]))
        if(current_e < error):
            error = current_e
            best_a = a
    return best_a
#power_law("megered2.txt")
power_law("megered.txt")