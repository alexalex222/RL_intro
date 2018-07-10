import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

plt.close('all')
stateValue = pd.read_csv('state_values.csv', header=None)
policy = pd.read_csv('optimal_policy.csv', header=None)
states = np.arange(len(policy))

plt.figure(1)
plt.xlabel('Capital')
plt.ylabel('Value estimates')
plt.plot(stateValue)
plt.figure(2)
plt.scatter(states, policy)
plt.xlabel('Capital')
plt.ylabel('Final policy (stake)')
plt.show()
