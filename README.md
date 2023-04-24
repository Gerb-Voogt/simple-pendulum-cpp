# Simple Pendulum simulation using C++
This document involves a simple model of a pendulum programmed in C++. This is mainly just a kata for practicing both C++ and Scientific Programming. The mathematical derivation for the equations of motion of the pendulum using Newton's formalism can be found below.

In the future I might want to write a more generic engine for solving nonlinear differential equations which implements an abstract base class for dynamical systems with a virtual `equations_of_motion()` method. The idea is then to have some specific dynamical system be a derived class from this abstract base class for easy interfacing and implementation.

# The Mathematics
## The Mathetmatical Derivation
Starting with a simple FBD we find that the sum of all the moments acting on the origin of the pendulum are given as

$\sum M = -lmg \sin(\theta) - lF_{a} = I \ddot{\theta}.$

Assuming the air resistance force $F_{a}$ can be modeled as being proportional to velocity we can write the following homogeneous nonlinear second order differential equation

$\ddot{\theta} + \frac{\mu}{ml}\dot{\theta} + \frac{g}{l}\sin(\theta) = 0$

written in terms of a state-space model we end up with the following 2 equations

$\dot{\theta} = \dot{\theta}$

$\ddot{\theta} = -\frac{\mu}{ml}\dot{\theta} - \frac{g}{l}\sin(\theta)$

which we can simulate using whatever numerical method we choose as we now have them in the stadard form

$\dot x = f(x, t)$

where $x \in \mathbb{R}^{n}$ and $f: \mathbb{R}^{n} \rightarrow \mathbb{R}^{n}$ is a vector valued function.

## Numerical Integration Schemes that are implemented
### Forward Euler
First and foremost the obvious choice for a numerical scheme is the forward Euler integration scheme. It's the most simple numerical scheme to implement, generally has good stability and is fast to compute. On the flip side it has mediocre accuracy compared to more sophisticated options.

A simple derivation for the forward Euler scheme is given below. We start by noting that we can write the derivative as a first order finite difference scheme

$\frac{dx}{dt} = \frac{x(t+h) - x(t)}{h} + \mathcal{O}(h^{2})$

We then substitute back in the fact that this is equal to the vector valued function describing the state derivative

$\frac{x(t+h) - x(t)}{h} + \mathcal{O}(h^{2}) = f(t, x)$

which then after some simple algebraic manipulation shows that

$x(t+h) = x(t) + hf(x, t) +  \mathcal{O}(h^{2})$

Which is the forward Euler finite difference scheme.

### Modified Euler


### Runge-Kutta 4
