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
  #with open('log.txt', 'wa') as outfile:
    os.system("> log.txt")
    for i in range (0,5):
        # os.system("/usr/bin/time ./disk_sort "+ filenames_dat[i] + " "+ str(mem)+" "+block_size+"")
        command = "/usr/bin/time -lp ./disk_sort "+ filenames_dat[i] + " "+ str(mem/num[i])+" "+str(block_size) + " 2>>log.txt"
        #outfile.write(os.popen(command).read()+"\n")
        #subprocess.call(command, stderr=outfile,stdout=outfile,shell=True)
        #f = open("log.txt","a")
        os.system(command)
        os.system("rm -f *sorted*")
part2_1()

def plot_part2():
    y=[13.39, 12.83, 12.98, 13.02, 14.00]
    x=[209715200,209715200/2,209715200/4,209715200/8,209715200/16]    
    x = np.log10(x)
    fig = plt.figure()

    width = .35
    ind = np.arange(len(y))
    result = plt.bar(ind, y, width=width, color=(0.2588, 0.4433, 1.0))
    plt.xticks(ind + width / 2, x)

    fig.autofmt_xdate()


    #write seq
    # plt.xlabel('Block size(Bytes)')
    # plt.ylabel('Write Speed(BPS)')
    # plt.title('Write Speed by different block sizes')

    plt.xlabel('main memory size ')
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

        # if (int(line.split(",")[0]) != 0 and int(line.split(",")[1]) != 0):
        x.append(int(line.split(",")[0]))
        y.append(int(line.split(",")[1]))
    plot(x, y, '.')
    show()
#exp_3("megered.txt")
def power_law(filename):
    x = []
    y = []

    f = open(filename, "r")
    for line in f:
        line = line.strip('\n')

        #if (int(line.split(",")[0]) != 0 and int(line.split(",")[1]) != 0):
        x.append(int(line.split(",")[0]))
        y.append(int(line.split(",")[1]))

    y = np.log(y)
    x = np.log(x)

    # Perform fit
    #(aCoeff, bCoeff, rVal, pVal, stdError) = stats.linregress(x,y)
    c, stats = P.polyfit(x, y, 1, full=True)
    print(c)
    predictY = (c[1] * x) + c[0]

    plot(x, y, '.')
    plot(x, predictY)
    xlabel('log(out-degrees)')
    ylabel('number of followers')
    show()

#power_law("megered2.txt")