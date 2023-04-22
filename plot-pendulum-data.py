#!/usr/bin/python3
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


def main():
    data = pd.read_csv('data_fe.csv')

    fig, ax = plt.subplots(1, 2, figsize=(16, 5))
    time_plot = ax[0]
    phase_space = ax[1]
    time_plot.plot(data['t'], data['theta'], label=r'$\theta$')
    time_plot.plot(data['t'], data['theta_dot'], label=r'$\frac{d \theta}{dt}$')
    time_plot.plot(data['t'], data['theta_ddot'], label=r'$\frac{d^2 \theta}{dt^2}$')
    time_plot.set(title = 'Angle, angular velocity and angular acceleration vs time',
              xlabel = r'$t$')
    time_plot.legend()
    time_plot.grid()

    phase_space.plot(data['theta'], data['theta_dot'])
    phase_space.set(title = 'Phase portrait',
              xlabel=r'$\theta$',
              ylabel = r'$\frac{d\theta}{dt}$')
    phase_space.grid()

    plt.show()


if __name__ == "__main__":
    main()
