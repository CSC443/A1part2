from pylab import *
import os
import subprocess

filenames_dat = ["data1.dat","data2.dat","data3.dat","data4.dat","data5.dat"]
num =[1,2,4,16,32]
block_size =16384 
mem = 209715200
def part2_1():
  with open('log.txt', 'wa') as outfile:  
    for i in range (0,5):
        # os.system("/usr/bin/time ./disk_sort "+ filenames_dat[i] + " "+ str(mem)+" "+block_size+"")
        command = "/usr/bin/time ./disk_sort "+ filenames_dat[i] + " "+ str(mem/num[i])+" "+str(block_size)
        outfile.write(os.popen(command).read()+"\n")
        #subprocess.call(command, stderr=outfile,stdout=outfile,shell=True)
        #f = open("log.txt","a")
        os.system("rm *sorted*")


def plot_part2():
    y=[]
    x=[209715200,209715200/2,209715200/4,209715200/8,209715200/16]    
    x = np.log10(x)
    fig = plt.figure()

    width = .35
    ind = np.arange(len(y))
    result = plt.bar(ind, y, width=width, color=(0.2588, 0.4433, 1.0))
    result[len(y) - 1].set_color('r')
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