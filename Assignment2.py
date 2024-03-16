''' Assignment 2
    Code to calculate the kth Discrete Fourier 
    Coefficient
    
    Name = Umanshiva
    Roll NO.= AI22BTECH11016
'''



import numpy as np

N = int(input("Enter length of vector: \n"))   #length of signal
print("Enter "+str(N)+" values")

x = []
for i in range(N):
    x.append(int(input()))

x = np.array(x)       # input vector/signal

k = int(input("Enter the harmonic order: \n"))   #harmonic order

O = 2*(np.pi)/N          # fundamental frequency

w_k = []                   
for n in range(N):
    w_k.append(np.exp(-1j*k*O*n))

w_k = np.array(w_k)        #Basis vector
print(w_k)

X_k = (np.dot(x,w_k))/N
print("The Fourier coefficient is: ", X_k)
