# -*- coding: utf-8 -*-
"""
Created on Tue Jul 24 10:06:45 2018

@author: kchen
"""

import pandas as pd
import matplotlib.pyplot as plt


if __name__ == "__main__":
    plt.close('all')
    plt.style.use('ggplot')
    
    fig, axes = plt.subplots(2, 1, figsize=(18, 10))
    df = pd.read_csv('Semi_Gradient_Off_Policy_TD.csv', sep=',', header=None)    
    axes[0].plot(df)
    axes[0].legend(['theta 1', 'theta 2', 'theta 3', 'theta 4', 'theta 5', 'theta 6', 'theta 7', 'theta 8'])
    axes[0].set_xlabel('Steps')
    axes[0].set_ylabel('Theta value')
    axes[0].set_title('semi-gradient off-policy TD')
    
    df = pd.read_csv('Semi_Gradient_DP.csv', sep=',', header=None)
    axes[1].plot(df)
    axes[1].legend(['theta 1', 'theta 2', 'theta 3', 'theta 4', 'theta 5', 'theta 6', 'theta 7', 'theta 8'])
    axes[1].set_xlabel('Sweeps')
    axes[1].set_ylabel('Theta value')
    axes[1].set_title('semi-gradient DP')
    plt.tight_layout()
    
    fig, axes = plt.subplots(2, 1, figsize=(18, 10))
    df = pd.read_csv('tdc.csv', sep=',', header=None)    
    axes[0].plot(df)
    axes[0].legend(['theta 1', 'theta 2', 'theta 3', 'theta 4', 'theta 5', 'theta 6', 'theta 7', 'theta 8', 'RMSVE', 'RMSPBE'])
    axes[0].set_xlabel('Steps')
    axes[0].set_title('TDC')
    
    df = pd.read_csv('expected_tdc.csv', sep=',', header=None)
    axes[1].plot(df)
    axes[1].legend(['theta 1', 'theta 2', 'theta 3', 'theta 4', 'theta 5', 'theta 6', 'theta 7', 'theta 8', 'RMSVE', 'RMSPBE'])
    axes[1].set_xlabel('Sweeps')
    axes[1].set_title('Expected TDC')
    plt.tight_layout()
    
    fig, ax = plt.subplots(1, 1, figsize=(18, 10))
    df = pd.read_csv('emphatic_td.csv', sep=',', header=None)    
    ax.plot(df)
    ax.legend(['theta 1', 'theta 2', 'theta 3', 'theta 4', 'theta 5', 'theta 6', 'theta 7', 'theta 8', 'RMSVE'])
    ax.set_xlabel('Steps')
    ax.set_title('Emphatic TDC')

    plt.show()