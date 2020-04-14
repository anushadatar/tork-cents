"""
phase_shift_demo.py
Demonstrates how to compute phase shift of two sinusoidal input functions in
the context of twist angle magnetic phase shift sensor. 
"""

import numpy as np
import matplotlib.pyplot as plt

# Signal constants, based on max 15kHz sample rate on Arduino analog read.
number_of_samples = 30001
samples_per_second = 15000
# Frequency in Hz of both signals.
frequency = 3
# Phase shift in radians of shifted signal.
phase_shift = np.pi/4

# Generate signals to calculate phase shift of.
# Time axis.
time = np.linspace(0, ((number_of_samples - 1)/samples_per_second), \
       number_of_samples)
# Reference signal.
ref_signal = np.sin((2 * np.pi) * frequency * time)
# Shifted signal.
shifted_signal = np.sin((2 * np.pi) * frequency * time + phase_shift)

# Plot original signals.
# plt.plot(time, ref_signal)
# plt.plot(time, shifted_signal)
# plt.show()

# Determine the phase offset between the two signals using the correlation.
correlation = np.correlate(ref_signal, shifted_signal, 'full')
time_delta = np.linspace(-time[-1], time[-1], (2*number_of_samples)-1)
time_shift = time_delta[correlation.argmax()]
# Constrain to between pi and pi.
calc_phase_shift = ((2* np.pi) * (time_shift/(1/frequency) % 1))
# Prints the actual value of the shift and the adjusted phase shift.
print("Actual phase shift: %f", phase_shift)
print("Computed phase shift: %f", calc_phase_shift)
