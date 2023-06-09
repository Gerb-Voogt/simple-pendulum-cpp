#!/usr/bin/python3
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


def main():
    fe_data = pd.read_csv('./data_fe.csv')
    me_data = pd.read_csv('./data_me.csv')
    rk4_data = pd.read_csv('./data_rk4.csv')

    ## Plotting the Forward Euler Results
    fig, ax = plt.subplots(1, 2, figsize=(16, 5))
    time_plot = ax[0]
    phase_space = ax[1]
    time_plot.plot(fe_data['t'], fe_data['theta'], label=r'$\theta$')
    time_plot.plot(fe_data['t'], fe_data['theta_dot'], label=r'$\frac{d \theta}{dt}$')
    time_plot.set(title = 'Angle, angular velocity and angular acceleration vs time',
              xlabel = r'$t$')
    time_plot.legend()
    time_plot.grid()

    phase_space.plot(fe_data['theta'], fe_data['theta_dot'])
    phase_space.set(title = 'Phase portrait',
              xlabel=r'$\theta$',
              ylabel = r'$\frac{d\theta}{dt}$')
    phase_space.grid()
    fig.suptitle('Forward Euler Results', fontsize=16)

    plt.show()

    ## Plotting the Modified Euler Results
    fig, ax = plt.subplots(1, 2, figsize=(16, 5))
    time_plot = ax[0]
    phase_space = ax[1]
    time_plot.plot(me_data['t'], me_data['theta'], label=r'$\theta$')
    time_plot.plot(me_data['t'], me_data['theta_dot'], label=r'$\frac{d \theta}{dt}$')
    time_plot.set(title = 'Angle, angular velocity and angular acceleration vs time',
              xlabel = r'$t$')
    time_plot.legend()
    time_plot.grid()

    phase_space.plot(me_data['theta'], me_data['theta_dot'])
    phase_space.set(title = 'Phase portrait',
              xlabel=r'$\theta$',
              ylabel = r'$\frac{d\theta}{dt}$')
    phase_space.grid()
    fig.suptitle('Modified Euler Results', fontsize=16)
    plt.show()

    ## Plotting the RK4 results
    fig, ax = plt.subplots(1, 2, figsize=(16, 5))
    time_plot = ax[0]
    phase_space = ax[1]
    time_plot.plot(rk4_data['t'], rk4_data['theta'], label=r'$\theta$')
    time_plot.plot(rk4_data['t'], rk4_data['theta_dot'], label=r'$\frac{d \theta}{dt}$')
    time_plot.set(title = 'Angle, angular velocity and angular acceleration vs time',
              xlabel = r'$t$')
    time_plot.legend()
    time_plot.grid()

    phase_space.plot(rk4_data['theta'], rk4_data['theta_dot'])
    phase_space.set(title = 'Phase portrait',
              xlabel=r'$\theta$',
              ylabel = r'$\frac{d\theta}{dt}$')
    phase_space.grid()
    fig.suptitle('RK4 Results', fontsize=16)

    plt.show()

    ## Plotting the difference between Forward Euler and RK4
    eps_fe = np.abs(fe_data['theta'] - rk4_data['theta'])
    eps_fe_dot = np.abs(fe_data['theta_dot'] - rk4_data['theta_dot'])
    eps_me = np.abs(me_data['theta'] - rk4_data['theta'])
    eps_me_dot = np.abs(me_data['theta_dot'] - rk4_data['theta_dot'])
    time = fe_data['t']

    # plt.plot(time, eps_fe, label=r'FE $\varepsilon_{\theta}$', color='red', linestyle='solid')
    # plt.plot(time, eps_fe_dot, label=r'FE $\varepsilon_{d\theta/dt}$', color='red', linestyle='dashed')
    plt.plot(time, eps_me, label=r'ME $\varepsilon_{\theta}$', color='blue', linestyle='solid')
    plt.plot(time, eps_me_dot, label=r'ME $\varepsilon_{d\theta/dt}$', color='blue', linestyle='dashed')
    plt.xlabel('Time')
    plt.ylabel('Local Error')
    plt.title('Local Error defined in terms of difference between FE and RK4 solution.')
    plt.legend()
    plt.show()



if __name__ == "__main__":
    main()
