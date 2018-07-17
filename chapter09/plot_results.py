import numpy as np
import matplotlib.pyplot as plt
import sys
import pandas as pd

def draw_monte_carlo():
    df = pd.read_csv('monte_carlo_results.csv')
    fig, axes = plt.subplots(1, 2, figsize=(18, 10))
    axes[0].plot(df['State'], df['True State Value'], label='True value')
    axes[0].plot(df['State'], df['MC State Value'], label='Approximate MC value')
    axes[0].set_xlabel('State')
    axes[0].set_ylabel('Value')
    axes[0].legend()

    axes[1].plot(df['State'], df['State Distribution'], label='State distribution')
    axes[1].set_xlabel('State')
    axes[1].set_ylabel('Distribution')
    axes[1].legend()

    plt.tight_layout()

def draw_TD():
    df = pd.read_csv('TD_results.csv')
    fig, axes = plt.subplots(1, 2, figsize=(18, 10))
    axes[0].plot(df['State'], df['True State Value'], label='True value')
    axes[0].plot(df['State'], df['TD State Value'], label='Approximate TD value')
    axes[0].set_xlabel('State')
    axes[0].set_ylabel('Value')
    axes[0].legend()

    df = pd.read_csv('TD_errors.csv', header=None)
    steps = np.power(2, np.arange(0, 10))
    alphas = np.arange(0, 1.1, 0.1)
    for i in range(0, len(steps)):
        axes[1].plot(alphas, df.iloc[i], label='n = ' + str(steps[i]))
    axes[1].set_xlabel('alpha')
    axes[1].set_ylabel('RMSE')
    axes[1].legend()

    plt.tight_layout()

def draw_basis():
    df = pd.read_csv('poly_errors.csv', header=None)
    orders = [5, 10, 20]

    fig, axes = plt.subplots(1, 2, figsize=(18,10))
    for i in range(0, len(orders)):
        axes[0].plot(df.iloc[i], label='order = ' + str(orders[i]))
    axes[0].set_xlabel('Episode')
    axes[0].set_ylabel('RMSE')
    axes[0].set_ylim(0, 0.6)
    axes[0].legend()
    axes[0].set_title('Polynomial Basis')

    df = pd.read_csv('fourier_errors.csv', header=None)
    for i in range(0, len(orders)):
        axes[1].plot(df.iloc[i], label='order = ' + str(orders[i]))
    axes[1].set_xlabel('Episode')
    axes[1].set_ylabel('RMSE')
    axes[1].set_ylim(0, 0.6)
    axes[1].legend()
    axes[1].set_title('Fourier Basis')

    plt.tight_layout()

def draw_tile():
    df1 = pd.read_csv('tile_errors.csv', header=None)
    df2 = pd.read_csv('aggreg_errors.csv', header=None)
    fig, ax = plt.subplots()
    ax.plot(df1.iloc[0], label='Tile')
    ax.plot(df2.iloc[0], label='Aggregation')
    ax.set_xlabel('Episode')
    ax.set_ylabel('RMSE')
    ax.set_ylim(0, 1.0)
    ax.legend()
    
    
if __name__ == "__main__":
    plt.close('all')
    plt.style.use('ggplot')
    draw_monte_carlo()
    draw_TD()
    draw_basis()
    draw_tile()
    plt.show()