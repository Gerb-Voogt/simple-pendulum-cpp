# Simple Pendulum simulation using C++
This document involves a simple model of a pendulum programmed in C++. This is mainly just a kata for practicing both C++ and Scientific Programming. The mathematical derivation for the equations of motion of the pendulum using Newton's formalism can be found below.

In the future I might want to write a more generic engine for solving nonlinear differential equations which implements an abstract base class for dynamical systems with a virtual ```equations_of_motion()``` method. The idea is then to have some specific dynamical system be a derived class from this abstract base class for easy interfacing and implementation.

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
