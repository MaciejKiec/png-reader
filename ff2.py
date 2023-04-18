import numpy as np
import cv2
from matplotlib import pyplot as plt

img=cv2.imread('1.png', cv2.IMREAD_GRAYSCALE)
#img = cv2.cvtColor(img, cv2.IMREAD_GRAYSCALE)
#dft = np.fft.fft2(img)
#dft_shift = np.fft.fftshift(dft)
#phase_spectrum = np.angle(dft_shift)
#ax1 = plt.subplot(1,2,1)
#ax1.imshow(img, cmap='gray')
#ax2 = plt.subplot(1,2,2)
#ax2.imshow(img)
#plt.show()

cv2.imshow('image', img)