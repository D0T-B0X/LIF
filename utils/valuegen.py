import pandas as pd
import numpy as np

START_NODE = -20
END_NODE = 20
NODE_COUNT = 200

nodes: float = np.linspace(START_NODE, END_NODE, NODE_COUNT)
values: float = []

for node in nodes:
    fn: float = node ** 2
    values.append(fn)

df = pd.DataFrame({
    'x': nodes,
    'y': values
})

df.to_csv("../data/nodes_values.csv", index=False, float_format='%.6f')

