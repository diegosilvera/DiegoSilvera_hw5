import numpy as np
import matplotlib.pyplot as plt
archivo=open("CurvaRotacion.txt")
archivo2=open("RadialVelocities.dat")
x=[]
v=[]
vmodel=[]
b1=0
b2=0
b3=0
contador=0
b_b=0.2497
b_d=5.16
a_d=0.3105
a_h=64.3
for line in archivo:
    lol=line.split()
    b1=float(lol[0])
    b2=float(lol[1])
    b3=float(lol[2])
print(b1," ",b2,"",b3)
a1=b1**(.5)
a2=b2**(.5)
a3=b3**(.5)
for line in archivo2:
    if(contador==0):
        contador=contador+1
        lol=line.split()
    elif(contador<301):
        lol=line.split()
        x.append(float(lol[0]))
        v.append(float(lol[1]))
        x1=float(lol[0])
        vmodel.append(a1*x1/((x1**2.0+b_b**2.0)**0.75) +a2*x1/((x1**2.0+(b_d+a_d)**2.0)**0.75)+a3/((x1**2.0+a_h**2.0)**0.25))
        contador=contador+1

plt.plot(x,v,label="Datos medidos velocidad en kpc.")
plt.plot(x,vmodel,label='Modelo de velocidad/Bayes en kpc')
plt.legend()
plt.savefig("Modelo")
