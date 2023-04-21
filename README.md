# Simple Pendulum simulation using C++
This document involves a simple model of a pendulum programmed in C++. The main purpose of this is praciticing scientific programming as well as practicing my C++ skills. The mathematical derivation for the pendulum is given below.

## The Mathetmatical Derivation
Starting with a simple FBD we find that the sum of all the moments acting on the origin of the pendulum are given as

$\Circlearrowleft \sum M = -lmg \sin(\theta) + lF_{a} = I \ddot{\theta}.$

Assuming the air resistance force $F_{a}$ can be modeled as being proportional to velocity (Middle of the road assumption, in practice it is proportional to the velocity squared but this is simpler to model) we can write the following homogeneous nonlinear second order differential equation

$\ddot{\theta} - \frac{\mu}{ml}\dot{\theta} - \frac{g}{l}\sin(\theta)$
written in terms of a state-space model we end up with the following 2 equations

$\dot{\theta} = \dot{\theta}$

and

$\ddot{\theta} = \frac{\mu}{ml}\dot{\theta} - \frac{g}{l}\sin(\theta)$

which we can simulate using whatever numerical method we choose as we now have them in the stadard form

$\dot x = f(x, t)$

where $x \in \mathbb{R}^{n}$ and $f: \mathbb{R}^{n} \rightarrow \mathbb{R}^{n}$ is a vector valued function.
