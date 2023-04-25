# Simple Pendulum simulation using C++
This document involves a simple model of a pendulum programmed in C++. This is mainly just a kata for practicing C++, numerical mathematics and Scientific Programming. The mathematical derivation for the equations of motion of the pendulum using Newton's formalism can be found below. A derivation for the numerical methods used can be found below as well (with the exception of RK4 as the derivation is rather involved).

In the future I might want to write a more generic engine for solving nonlinear differential equations which implements an abstract base class for dynamical systems with a virtual `equations_of_motion()` method. The idea is then to have some specific dynamical system be a derived class from this abstract base class for easy interfacing and implementation.

Another next step would be possible implementing the data visualisation in C++ rather then in Python. This opens up the opportunity to work with dataviz libraries in C++ as well as possibly rendering out some fancy pendulum animations.

# The Mathematics
## Deriving the equation of motion
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
First and foremost the obvious choice for a numerical scheme is the forward Euler integration scheme. It's the most simple numerical scheme to implement. It generally has good stability and is fast to compute however it does not deal well with stiff systems and may require more sophisticated techniques such as adaptive step size to deal with these problems. The accuracy of Forward Euler is also poor compared to more sophisticated numerical methods.

A simple derivation for the forward Euler scheme is given below. We start by noting that we can write the derivative as a first order finite difference scheme

$\frac{dx}{dt} = \frac{x(t+h) - x(t)}{h} + \mathcal{O}(h^{2})$

We then substitute back in the fact that this is equal to the vector valued function describing the state derivative

$\frac{x(t+h) - x(t)}{h} + \mathcal{O}(h^{2}) = f(t, x)$

which then after some simple algebraic manipulation shows that

$x(t+h) = x(t) + hf(x, t) +  \mathcal{O}(h^{2})$

Which is the forward Euler finite difference scheme.

### Modified Euler
A natural extension of the basics of Euler's method is the modified Euler method. This numerical method consists of a 2 step process: prediction and correction. We first start with a forward Euler step, generating a predictor for the next time step. This is then applied to the another forward Euler step which uses the predictor as input to generate the output. The idea is the use of both an overestimate and underestimate of the real solution and then taking the average of those 2. This naturally produces a result which is close to the exact solution then either of our bad approximations individually.

$\alpha_{low} = f(t, x(t))$

We then find a predictor term by applying a Forward Euler step

$x^{*}(t) = x(t) + f(t, x(t))$

and then _overestimate_ the slope using 

$\alpha_{high} = f(t, x^{*}(t))$

We then take the average of these 2 slopes as the average of an overestimate and underestimate will produce something more accurate then either method individually. This then gives us the ideal slope for our numerical scheme

$\alpha_{ideal} = \frac{1}{2}(\alpha_{low} + \alpha_{high})$

which shows that

$x(t+h) = x(t) + \frac{1}{2}(f(t, x(t)) + f(t, x^{*}(t)))$

which is the Modified Euler method.


### Runge-Kutta 4
RK4 is one of the most widely applied explicit integration schemes. It's wide application is largely due to the fact that the method is very accurate while still remaining relatively cheap computationally speaking. The method is also relatively simple when compared to other higher order schemes, making it very easy to implement. It also boasts good stability over a wide range of step sizes. The main drawback of the method is that it does not deal well with stiff equations, requiring a very (potentially local if using adapative step size) small step size to produce accurate results.

The Runge-kutta 4 method follows from generalizing the notion of the prediction-correction scheme from the Modified Euler method. I will however refrain from writing down the complete derivation as this process is rather involved. The classic RK4 scheme is given using 4 predictors which are combined to find an approximation for our final result

$k_{1} = f(t, x(t))$

$k_{2} = f\left(t+\frac{h}{2}, x(t) + \frac{h}{2}k_{1}\right)$

$k_{3} = f\left(t+\frac{h}{2}, x(t) + \frac{h}{2}k_{2}\right)$

$k_{4} = f(t + h, x(t) + hk_{3})$

Which are then finally combined to the following expression 

$x(t+h) = x(t) + \frac{1}{6}(k_{1} + k_{2} + k_{3} + k_{4})$
