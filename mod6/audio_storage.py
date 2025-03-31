import numpy as np
from scipy.fft import fft, ifft
import scipy.io.wavfile as wav
import matplotlib.pyplot as plt

def hash_indices(row, col):
    return (row * 31 + col * 17) % 20000 + 200

def create_wave(matrix, duration=1.0, sampling_rate=192000):
    t = np.linspace(0, duration, int(sampling_rate * duration), endpoint=False)
    signal = np.zeros_like(t)
    
    for (row, col), value in np.ndenumerate(matrix):
        if value != 0:
            frequency = hash_indices(row, col)
            signal += value * np.sin(2 * np.pi * frequency * t)
    
    return signal

def save_wave(filename, signal, sampling_rate=192000):
    wav.write(filename, sampling_rate, signal.astype(np.float32))

def recover_matrix(signal, shape, duration=1.0, sampling_rate=192000):
    t = np.linspace(0, duration, int(sampling_rate * duration), endpoint=False)
    recovered_matrix = np.zeros(shape)
    
    for row in range(shape[0]):
        for col in range(shape[1]):
            frequency = hash_indices(row, col)
            wave = np.sin(2 * np.pi * frequency * t)
            amplitude = 2 * np.sum(signal * wave) / len(t)
            recovered_matrix[row, col] = amplitude
    
    return recovered_matrix

def plot_matrix(matrix, title):
    plt.imshow(matrix, cmap='viridis', interpolation='none')
    plt.colorbar()
    plt.title(title)
    plt.show()

def plot_waveform(signal, sampling_rate):
    t = np.linspace(0, len(signal) / sampling_rate, num=len(signal))
    plt.figure(figsize=(12, 6))
    plt.plot(t, signal)
    plt.title('Waveform')
    plt.xlabel('Time [s]')
    plt.ylabel('Amplitude')
    plt.show()

def plot_fft(signal, sampling_rate):
    N = len(signal)
    T = 1.0 / sampling_rate
    yf = fft(signal)
    xf = np.fft.fftfreq(N, T)[:N//2]
    plt.figure(figsize=(12, 6))
    plt.plot(xf, 2.0/N * np.abs(yf[:N//2]))
    plt.title('FFT of the Signal')
    plt.xlabel('Frequency [Hz]')
    plt.ylabel('Amplitude')
    plt.show()

matrix = np.array([
    [0, 3, 0],
    [4, 0, 0],
    [0, 0, 5]
])

signal = create_wave(matrix)
save_wave('sparse_matrix.wav', signal)
sampling_rate, signal = wav.read('sparse_matrix.wav')
recovered_matrix = recover_matrix(signal, matrix.shape)
plot_waveform(signal, sampling_rate)
plot_fft(signal, sampling_rate)
print("Original Matrix:")
recovered_matrix[np.abs(recovered_matrix) < 1e-5] = 0
print(matrix)
print("Recovered Matrix:")
print(recovered_matrix)
matrix = np.zeros((100, 100))
matrix[10, 20] = 3
matrix[30, 40] = 4
matrix[50, 60] = 5
signal = create_wave(matrix)
save_wave('sparse_matrix.wav', signal)
sampling_rate, signal = wav.read('sparse_matrix.wav')
recovered_matrix = recover_matrix(signal, matrix.shape)
plot_waveform(signal, sampling_rate)
plot_fft(signal, sampling_rate)
print("Original Matrix:")
recovered_matrix[np.abs(recovered_matrix) < 1e-5] = 0
print(matrix)
print("Recovered Matrix:")
print(recovered_matrix)