import os
import numpy as np
from matplotlib import pyplot as plt

result_dir = 'g:\\master\\desktop_verzije_programa\\data\\j2k'
result_file = 'total_psnr.txt'
image_file = 'j2k_results_500.jpg'

PSNR = np.loadtxt(os.path.join(result_dir, result_file), dtype=float, delimiter='\t', usecols=1)
compression_ratio = np.loadtxt(os.path.join(result_dir, result_file), dtype=float, delimiter='\t', usecols=2)

fig = plt.figure('Jpeg2000 compression results')
plt.plot(compression_ratio, PSNR, 'r', label='')

plt.xlim(-5, 500)
plt.xlabel('Ratio')
plt.ylabel('PSNR')
plt.title('JPEG 2000')
plt.legend()
plt.savefig(os.path.join(result_dir, image_file))
plt.show()
