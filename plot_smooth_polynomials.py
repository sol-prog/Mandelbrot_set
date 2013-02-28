# Used to test and modify some Bernstein polynomials (order 4)

from pylab import *

t = np.linspace(0, 1, 100)
r = 9*(1-t)*t*t*t
g = 15*(1-t)*(1-t)*t*t
b = 8.5*(1-t)*(1-t)*(1-t)*t

figure(1)
plot(t, r, color="red", linewidth=2.5, label = "r(t)")
plot(t, g, color="green", linewidth=2.5, label = "g(t)")
plot(t, b, color="blue", linewidth=2.5, label = "b(t)")

title('Altered Bernstein polynomials')
xlabel('t')
legend(loc='upper left')
grid()

savefig('rgb_smooth.png', dpi=72)

close()

