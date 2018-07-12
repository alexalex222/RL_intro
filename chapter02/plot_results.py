import numpy as np
import matplotlib.pyplot as plt
import sys
import pandas as pd

def draw_image(type_name):
    rewards_file_name = type_name + '_average_rewards.csv'
    actions_file_name = type_name + '_best_action_count.csv'

    df_rewards = pd.read_csv(rewards_file_name)
    df_actions = pd.read_csv(actions_file_name)

    fig, axes = plt.subplots(1, 2, figsize=(18, 10))
    axes[0].plot(df_rewards)
    axes[0].set_xlabel('Episodes')
    axes[0].set_ylabel('Rewards')
    axes[0].legend(df_rewards.columns.values)

    axes[1].plot(df_actions)
    axes[1].set_xlabel('Episodes')
    axes[1].set_ylabel('Optimal action %')
    axes[1].legend(df_actions.columns.values)
    plt.tight_layout()

    
if __name__ == "__main__":
    plt.close('all')
    plt.style.use('ggplot')
    draw_image(sys.argv[1])
    draw_image(sys.argv[2])
    draw_image(sys.argv[3])
    draw_image(sys.argv[4])
    plt.show()