import os
import numpy as np
from matplotlib import pyplot as plt

res_dir = 'D:\\master\\satelite_image_compression\\output\\encoder_lowdelay_main_rext_sat'
res_file_name = 'global_enc_results.txt'
image_file_name = 'global_enc_results.jpg'
num_frames = 12

#QP = np.loadtxt('results.txt', dtype=int, delimiter='\t', usecols=0)
PSNR = np.loadtxt(os.path.join(res_dir, res_file_name), dtype=float, delimiter='\t', usecols=2)
compressed_size = np.loadtxt(os.path.join(res_dir, res_file_name), dtype=int, delimiter='\t', usecols=1)
original_size = 7911*7811*16*num_frames / 8
ratio = original_size / compressed_size

fig = plt.figure('Results')
plt.plot(ratio, PSNR, label='')
plt.xlim(0, 100)
plt.xlabel('Ratio')
plt.ylabel('PSNR')
plt.legend()
plt.show()
plt.savefig(os.path.join(res_dir, image_file_name))
