import socket
import threading
import time
import pylab as plt
import numpy as np
import convert as con
#對應Arduino檔案在
#C:\Users\user\Documents\Arduino\ESP32\ESP32_RTOS_ADC_WIFI
contents = 0
# 子執行緒的工作函數

def Chart():
    global contents
    #plt.ion()
    fig = plt.figure()
    Y = np.zeros(100)
    #print(type(Y))
    X = np.linspace(0, 100, 100)
    while True:

        plt.ylim((0,4096))
        plt.xlim((0,100))
        plt.plot(X, Y)
        print(X[0],Y[0])
        #graph.set_ydata(Y)
        Y=np.array(Y).tolist()
        #print(type(Y))
        if(contents==None):
            Y.insert(0, Y[0])
        else:
            Y.insert(0,contents)
        Y.pop()
        np.array(Y)
        plt.draw()
        plt.pause(0.01)
        fig.clear()
# 建立一個子執行緒
t = threading.Thread(target = Chart)
# 執行該子執行緒
t.start()
# 主執行緒繼續執行自己的工作
s = socket.socket()
#10.1.1.10
#172.20.10.3
s.bind(('10.1.1.10', 8090))
s.listen(0)

while True:

    client, addr = s.accept()

    while True:
        content = client.recv(32)
        contents = con.cvt(content)
        #print(contents)
        if len(content) == 0:
            break


    #print("Closing connection")
client.close()
# 等待 t 這個子執行緒結束
t.join()
