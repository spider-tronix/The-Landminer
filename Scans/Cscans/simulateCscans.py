import os
import h5py
import numpy as np
import cv2
import random
outputdata = []
unnormalized = []
scans = []
folder = r"E:/Prem/scans/"
dir1 = r"E:/Prem/scans/xdir/"
offset1 = "xdir_bscan_"

dir2 = r"E:/Prem/scans/ydir/"
offset2 = "ydir_bscan_"

mu = 127.5
sigma = 31.875
def get_output_data(filename, rxnumber, rxcomponent):

    f = h5py.File(filename, 'r')
    path = '/rxs/rx' + str(rxnumber) + '/'
    outputdata = f[path + '/' + rxcomponent]
    outputdata = np.array(outputdata)
    f.close()
    return outputdata


if __name__ == "__main__":
    for dir in [dir1, dir2]:
        #print(len(os.listdir(dir)))
        rxcomponent = "Ey" if dir == dir1 else "Ex"
        for i in range(1, len(os.listdir(dir))):
            file_name = dir+offset1+str(i)+".out" if dir == dir1 else dir+offset2+str(i)+".out"
            f = h5py.File(file_name, 'r')
            nrx = f.attrs['nrx']
            f.close()
            for rx in range(1, nrx + 1):
                outputdata.append(get_output_data(file_name, rx, rxcomponent))
    for s in outputdata:
        #print(np.amax(s), np.amin(s))
        s = s*sigma + mu
        s = s//1
        s = s.astype("uint8")
        unnormalized.append(s)
        

    for l in range(len(unnormalized)//3):
        image = cv2.merge((unnormalized[l*3], unnormalized[l*3+1], unnormalized[l*3+2]))
        image = cv2.resize(image, (1250, 1250))
        scans.append(image)
        #print(scans[-1].dtype, scans[-1].shape)
        cv2.imwrite(folder+str(len(scans))+".jpg", scans[-1])
        #print(scans[-1].shape)
        #cv2.imshow("img", scans[-1])
        #cv2.waitKey(1000)
        #cv2.destroyAllWindows()


