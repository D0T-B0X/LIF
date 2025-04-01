import pandas as pd
import numpy as np

START_NODE: float = -1
END_NODE: float = 1
NODE_COUNT: int = 201

nodes: float = np.linspace(START_NODE, END_NODE, NODE_COUNT)
values: float = []

for node in nodes:
    fn: float = 1 / (1 + (25 * np.pow(node, 2)))
    values.append(fn)

df = pd.DataFrame({
    'x': nodes,
    'y': values
})

df.to_csv("../data/nodes_values.csv", index=False, float_format='%.10f')

