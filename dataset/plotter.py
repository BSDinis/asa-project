import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

fname = "test.log"
data = np.genfromtxt(fname, delimiter=',')

x = data[:, 1]
y = data[:, 0]

slope, intercept, r_value, p_value, std_err = linregress(x, y)
print (f"Determination coeficient: {r_value**2}")
fit = (slope, intercept)
fit_fn=np.poly1d(fit)

plt.ticklabel_format(style='sci',axis='both',scilimits=(0,0), useLocale=True, useMathText=True)
plt.plot(x, y, "bo", ms=0.8)
plt.plot(x, fit_fn(x), '-r', linewidth=2.5, label="reta de regressão")
plt.xlabel("Ligações")
plt.ylabel("Ciclos de Relógio")
plt.savefig("res.pdf")
