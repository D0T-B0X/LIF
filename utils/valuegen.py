import pandas as pd
import numpy as np

START_NODE: float = -1
END_NODE: float = 1
NODE_COUNT_APPROX: int = 21
NODE_COUNT_TRUE: int = 301

nodes_approx: float = np.linspace(START_NODE, END_NODE, NODE_COUNT_APPROX)
values_approx: float = []

for node in nodes_approx:
    fn: float = 1 / (1 + (25 * (node ** 2)))
    values_approx.append(fn)

df_approx = pd.DataFrame({
    'x': nodes_approx,
    'y': values_approx
})

df_approx.to_csv("../data/nodes_values.csv", index=False, float_format='%.16f')

nodes_true: float = np.linspace(START_NODE, END_NODE, NODE_COUNT_TRUE)
values_true: float = []

for node in nodes_true:
    fn: float = 1 / (1 + (25 * (node ** 2)))
    values_true.append(fn)

df_true = pd.DataFrame({
    'x': nodes_true,
    'y': values_true
})

df_true.to_csv("../data/nodes_values_true.csv", index=False, float_format='%.10f')

