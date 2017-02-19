from pylab import *
import os
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

filenames_dat = ["data1.dat","data2.dat","data3.dat","data4.dat","data5.dat"]
num =[1,2,4,16,32]
block_size =16384 
mem = 209715200
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
#part2_1()

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

def power_law(filename):
    x = []
    y = []
    f = open(filename, "r")
    for line in f:
        line = line.strip('\n')
        if(int(line.split(",")[0]) != 0 and int(line.split(",")[1]) != 0):
            x.append(int(line.split(",")[0]))
            y.append(int(line.split(",")[1]))



    y = np.log(y)
    x = np.log(x)


    # Perform fit
    (aCoeff, bCoeff, rVal, pVal, stdError) = stats.linregress(x,y)

    # Use fits to predict height for a range of diameters
    testDiameter = x
    predictHeight = (aCoeff * testDiameter) + bCoeff

    # Create a string, showing the form of the equation (with fitted coefficients)
    # and r squared value
    # Coefficients are rounded to two decimal places.
    #equation = str(round(np.log10(aCoeff), 2)) + 'log10(D) + ' + str(round(bCoeff, 2)) + ' (r$^2$ = ' + str(round(rVal ** 2, 2)) + ')'

    # Plot fit against origional data
    plot(x, y, '.')
    plot(testDiameter, predictHeight)
    xlabel('Diameter (cm)')
    ylabel('Height (m)')
    show()

power_law("megered.txt")